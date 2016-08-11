/*
 * Copyright 2011 Joakim Sindholt <opensource@zhasha.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "resource9.h"
#include "device9.h"
#include "nine_helpers.h"
#include "nine_defines.h"

#include "pipe/p_screen.h"

#include "util/u_hash_table.h"
#include "util/u_inlines.h"
#include "util/u_resource.h"

#include "nine_pdata.h"

#define DBG_CHANNEL DBG_RESOURCE

HRESULT
NineResource9_ctor( struct NineResource9 *This,
                    struct NineUnknownParams *pParams,
                    struct pipe_resource *initResource,
                    BOOL Allocate,
                    D3DRESOURCETYPE Type,
                    D3DPOOL Pool,
                    DWORD Usage)
{
    struct pipe_screen *screen;
    HRESULT hr;

    DBG("This=%p pParams=%p initResource=%p Allocate=%d "
        "Type=%d Pool=%d Usage=%d\n",
        This, pParams, initResource, (int) Allocate,
        Type, Pool, Usage);

    hr = NineUnknown_ctor(&This->base, pParams);
    if (FAILED(hr))
        return hr;

    This->info.screen = screen = This->base.device->screen;
    if (initResource)
        pipe_resource_reference(&This->resource, initResource);

    if (Allocate) {
        assert(!initResource);

        /* On Windows it is possible allocation fails when
         * IDirect3DDevice9::GetAvailableTextureMem() still reports
         * enough free space.
         *
         * Some games allocate surfaces
         * in a loop until they receive D3DERR_OUTOFVIDEOMEMORY to measure
         * the available texture memory size.
         *
         * We are not using the drivers VRAM statistics because:
         *  * This would add overhead to each resource allocation.
         *  * Freeing memory is lazy and takes some time, but applications
         *    expects the memory counter to change immediately after allocating
         *    or freeing memory.
         *
         * Vertexbuffers and indexbuffers are not accounted !
         */
        if (This->info.target != PIPE_BUFFER) {
            This->size = util_resource_size(&This->info);

            This->base.device->available_texture_mem -= This->size;
            if (This->base.device->available_texture_mem <=
                    This->base.device->available_texture_limit) {
                return D3DERR_OUTOFVIDEOMEMORY;
            }
        }

        DBG("(%p) Creating pipe_resource.\n", This);
        This->resource = screen->resource_create(screen, &This->info);
        if (!This->resource)
            return D3DERR_OUTOFVIDEOMEMORY;
    }

    This->type = Type;
    This->pool = Pool;
    This->usage = Usage;
    This->priority = 0;

    This->pdata = util_hash_table_create(ht_guid_hash, ht_guid_compare);
    if (!This->pdata)
        return E_OUTOFMEMORY;

    return D3D_OK;
}

void
NineResource9_dtor( struct NineResource9 *This )
{
    DBG("This=%p\n", This);

    if (This->pdata) {
        util_hash_table_foreach(This->pdata, ht_guid_delete, NULL);
        util_hash_table_destroy(This->pdata);
    }

    /* NOTE: We do have to use refcounting, the driver might
     * still hold a reference. */
    pipe_resource_reference(&This->resource, NULL);

    /* NOTE: size is 0, unless something has actually been allocated */
    if (This->base.device)
        This->base.device->available_texture_mem += This->size;

    NineUnknown_dtor(&This->base);
}

struct pipe_resource *
NineResource9_GetResource( struct NineResource9 *This )
{
    return This->resource;
}

D3DPOOL
NineResource9_GetPool( struct NineResource9 *This )
{
    return This->pool;
}

HRESULT NINE_WINAPI
NineResource9_SetPrivateData( struct NineResource9 *This,
                              REFGUID refguid,
                              const void *pData,
                              DWORD SizeOfData,
                              DWORD Flags )
{
    enum pipe_error err;
    struct pheader *header;
    const void *user_data = pData;
    char guid_str[64];

    DBG("This=%p GUID=%s pData=%p SizeOfData=%u Flags=%x\n",
        This, GUID_sprintf(guid_str, refguid), pData, SizeOfData, Flags);

    if (Flags & D3DSPD_IUNKNOWN)
        user_assert(SizeOfData == sizeof(IUnknown *), D3DERR_INVALIDCALL);

    /* data consists of a header and the actual data. avoiding 2 mallocs */
    header = CALLOC_VARIANT_LENGTH_STRUCT(pheader, SizeOfData-1);
    if (!header) { return E_OUTOFMEMORY; }
    header->unknown = (Flags & D3DSPD_IUNKNOWN) ? TRUE : FALSE;

    /* if the refguid already exists, delete it */
    NineResource9_FreePrivateData(This, refguid);

    /* IUnknown special case */
    if (header->unknown) {
        /* here the pointer doesn't point to the data we want, so point at the
         * pointer making what we eventually copy is the pointer itself */
        user_data = &pData;
    }

    header->size = SizeOfData;
    memcpy(header->data, user_data, header->size);
    memcpy(&header->guid, refguid, sizeof(header->guid));

    err = util_hash_table_set(This->pdata, &header->guid, header);
    if (err == PIPE_OK) {
        if (header->unknown) { IUnknown_AddRef(*(IUnknown **)header->data); }
        return D3D_OK;
    }

    FREE(header);
    if (err == PIPE_ERROR_OUT_OF_MEMORY) { return E_OUTOFMEMORY; }

    return D3DERR_DRIVERINTERNALERROR;
}

HRESULT NINE_WINAPI
NineResource9_GetPrivateData( struct NineResource9 *This,
                              REFGUID refguid,
                              void *pData,
                              DWORD *pSizeOfData )
{
    struct pheader *header;
    DWORD sizeofdata;
    char guid_str[64];

    DBG("This=%p GUID=%s pData=%p pSizeOfData=%p\n",
        This, GUID_sprintf(guid_str, refguid), pData, pSizeOfData);

    header = util_hash_table_get(This->pdata, refguid);
    if (!header) { return D3DERR_NOTFOUND; }

    user_assert(pSizeOfData, E_POINTER);
    sizeofdata = *pSizeOfData;
    *pSizeOfData = header->size;

    if (!pData) {
        return D3D_OK;
    }
    if (sizeofdata < header->size) {
        return D3DERR_MOREDATA;
    }

    if (header->unknown) { IUnknown_AddRef(*(IUnknown **)header->data); }
    memcpy(pData, header->data, header->size);

    return D3D_OK;
}

HRESULT NINE_WINAPI
NineResource9_FreePrivateData( struct NineResource9 *This,
                               REFGUID refguid )
{
    struct pheader *header;
    char guid_str[64];

    DBG("This=%p GUID=%s\n", This, GUID_sprintf(guid_str, refguid));

    header = util_hash_table_get(This->pdata, refguid);
    if (!header)
        return D3DERR_NOTFOUND;

    ht_guid_delete(NULL, header, NULL);
    util_hash_table_remove(This->pdata, refguid);

    return D3D_OK;
}

DWORD NINE_WINAPI
NineResource9_SetPriority( struct NineResource9 *This,
                           DWORD PriorityNew )
{
    DWORD prev;
    DBG("This=%p, PriorityNew=%d\n", This, PriorityNew);

    if (This->pool != D3DPOOL_MANAGED || This->type == D3DRTYPE_SURFACE)
        return 0;

    prev = This->priority;
    This->priority = PriorityNew;
    return prev;
}

DWORD NINE_WINAPI
NineResource9_GetPriority( struct NineResource9 *This )
{
    if (This->pool != D3DPOOL_MANAGED || This->type == D3DRTYPE_SURFACE)
        return 0;

    return This->priority;
}

/* NOTE: Don't forget to adjust locked vtable if you change this ! */
void NINE_WINAPI
NineResource9_PreLoad( struct NineResource9 *This )
{
    if (This->pool != D3DPOOL_MANAGED)
        return;
    /* We don't treat managed vertex or index buffers different from
     * default ones (are managed vertex buffers even allowed ?), and
     * the PreLoad for textures is overridden by superclass.
     */
}

D3DRESOURCETYPE NINE_WINAPI
NineResource9_GetType( struct NineResource9 *This )
{
    return This->type;
}
