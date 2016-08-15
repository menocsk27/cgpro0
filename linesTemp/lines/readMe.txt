







sudo apt-get install build-essential


sudo apt-get install libsdl2-dev


---- ESTO NO ------sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev guile-1.8   guile-1.8-dev libsdl1.2debian libart-2.0-dev libaudiofile-dev   libesd0-dev libdirectfb-dev libdirectfb-extra libfreetype6-dev   libxext-dev x11proto-xext-dev libfreetype6 libaa1 libaa1-dev   libslang2-dev libasound2 libasound2-dev

Extraer libgraph-1.0.2.tar.gz y ejecutar cd /lugar/de/extracción

Ejecutar estos comandos

./configure
make
sudo make install
sudo cp /usr/local/lib/libgraph.* /usr/lib


Extraer SDL_bgi-2.0.6.tar.gz y ejecutar cd /lugar/de/extracción


Ejecutar estos comandos
cd src
make
sudo make install







