#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>

#define HSIZE 400
#define VSIZE 400

static ALLEGRO_DISPLAY *display = NULL;


void line1 (int x0, int y0, int x1, int y1){
    int i, temp;
    long double m,b,x,y;
    int vertical = 0;

    if ((x1 != x0)) {
        m = ((long double)(y1 - y0)) / (x1 - x0);
        b = (long double)(y0 - (m * x0));

        printf("m: %Lf ", m);
        printf("b: %Lf \n", b);
    }
    else {
        vertical = 1;
    }

    //Revisar densidad de x > densidad de y, si no cambiar variable independiente (debe hacerse después del paso anterior)
    if (abs(x1-x0)<abs(y1-y0)){
        if (y0>y1) { //Swapeo los puntos para que dibuje de abajo hacia arriba siempre
            temp = x0; x0 = x1; x1 = temp;
            temp = y0; y0 = y1; y1 = temp;
        }
        //Cambiar variable independiente. x = (b+y)/m
        for (i = y0; i<=y1; i++){ //Como hay más densidad de Ys que X, mi variable independiente es la y.
            if (vertical!=1) {
                if (m != 0){
                    x = ((long double)((i-b)/m));
                }
            }
            else {
                x = x0;
            }

            printf("X: %Lf ", x);
            printf("X: %f",round(x));
            printf("Y: %i\n",i);
            plot(round(x),i);
        }
    }

    else { //Más Xs que Ys
        if (x0>x1) { //Para que siempre dibuje de izquierda a derecha
            temp = x0; x0 = x1; x1 = temp;
            temp = y0; y0 = y1; y1 = temp;
        }
        //Ejecución de la ecuación normal de la recta y = mx + b
        for (i = x0; i<=x1; i++){ //Avanza normalmente sobre las x porque hay más densidad de Xs que Ys.
            if ((vertical==1)&&(y0==y1)){
                plot(x0,y0);
            }
            else {
                y = ((long double)(m * i + b));

                printf("Y: %Lf ", y);
                printf("Y: %f ", round(y));
                printf("X: %i \n", i);

                plot(i,round(y));
            }
        }
    }
}
void line2 (int x0, int y0, int x1, int y1){
    int i, temp;
    long double m,x,y;
    int vertical = 0;

    if ((x1 != x0)) {
        m = ((long double)(y1 - y0)) / (x1 - x0);
        printf("m: %Lf \n", m);
    }
    else {
        vertical = 1;
    }

    //Revisar densidad de x > y
    if (abs(x1-x0)<abs(y1-y0)){
        if (y0>y1) { //Swapeo
            temp = x0; x0 = x1; x1 = temp;
            temp = y0; y0 = y1; y1 = temp;
        }

        x = x0;
        //Cambiar variable independiente. x = (b+y)/m, delta = 1/m
        for (i = y0; i<=y1; i++){
            printf("X: %Lf ", x);
            printf("X: %f",round(x));
            printf("Y: %i\n",i);
            plot(round(x),i);

            if (vertical!=1) {
                if (m != 0){
                    x += 1/m;
                }
            }
            else {
                x = x0;
            }
        }
    }

    else { //Más Xs que Ys
        if (x0>x1) { //Para que siempre dibuje de izquierda a derecha
            temp = x0; x0 = x1; x1 = temp;
            temp = y0; y0 = y1; y1 = temp;
        }

        y = y0; //Valor inicial.

        for (i = x0; i<=x1; i++){
            if ((vertical==1)&&(y0==y1)){
                plot(x0,y0);
            }
            else {
                printf("Y: %Lf ", y);
                printf("Y: %f ", round(y));
                printf("X: %i \n", i);

                plot(i,round(y));

                y += m;
            }
        }
    }
}
void line3 (int x0, int y0, int x1, int y1){
    long double x, y;
    double paso_x, paso_y;
    int i, ancho;

    ancho = max(abs(x1 - x0), abs(y1 - y0));
    if (ancho == 0) {
        plot(x0, y0);
    }
    else {
        paso_x = ((long double)(x1-x0))/ancho;
        paso_y = ((long double)(y1-y0))/ancho;

        x = x0;
        y = y0;

        int cordX;
        int cordY;
        for (i = 0; i <= ancho; i++){
            //printf("Xf: %Lf ", x);
            //printf("X: %f ",round(x));
            //printf("Yf: %Lf ", y);
            //printf("Y: %f\n", round(y));
            cordX=round(x);
            cordY=round(y);
            plot(cordX, cordY);
            x += paso_x;
            y += paso_y;
        }
    }
}
void line4 (int x0, int y0, int x1, int y1){

}

void startScreen(){



   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return;
   }

   display = al_create_display(40, 40);
   if(display==NULL) {
      fprintf(stderr, "failed to create display!\n");
      return;
   }

   al_clear_to_color(al_map_rgb(0,0,0));

   al_flip_display();
   return 0;
}

void plot (int x, int y){
    ALLEGRO_COLOR color_blanco=al_map_rgb(0,0,255);
    al_draw_pixel(x, VSIZE-y, color_blanco);
	return 0;
}
int max(int a, int b){
    if (a < b){
        return b;
    }else{
        return a;
    }
}



int main() {
    //El main debe asegurarse que
    //      max(x0,x1) < Xres
    //      min(x0,x0) > 0
    //      max(y0,y1) < Yres
    //      min(y0,y1) > 0

    startScreen();

    int x0 = 3;
    int y0 = 4;

    int x1 = 100;
    int y1 = 70;

    al_rest(10.0);

    al_destroy_display(display);
    line3(x0,y0,x1,y1);
    //printf("(%i,%i) a (%i,%i)\n", x0,y0,x1,y1);
    return 0;
}
