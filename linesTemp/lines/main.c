#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <time.h>

#define HSIZE 400
#define VSIZE 400

void line1 (int x0, int y0, int x1, int y1){
    int i, temp;
    long double m,b,x,y;
    int vertical = 0;

    if ((x1 != x0)) {
        m = ((long double)(y1 - y0)) / (x1 - x0);
        b = (long double)(y0 - (m * x0));

        //printf("m: %Lf ", m);
        //printf("b: %Lf \n", b);
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

            //printf("X: %Lf ", x);
            //printf("X: %f",round(x));
            //printf("Y: %i\n",i);
            plot(((int)round(x)),i);
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

                //printf("Y: %Lf ", y);
                //printf("Y: %f ", round(y));
                //printf("X: %i \n", i);

                plot(i,((int)round(y)));
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
        //printf("m: %Lf \n", m);
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
            //printf("X: %Lf ", x);
            //printf("X: %f",round(x));
            //printf("Y: %i\n",i);

            plot(((int)round(x)),i);

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
                //printf("Y: %Lf ", y);
                //printf("Y: %f ", round(y));
                //printf("X: %i \n", i);

                plot(i,((int)round(y)));

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
void line4 (int x0, int y0, int x1, int y1){ //Bresenham (punto medio)

    int d2x,d2y,dx,dy,d,
        Delta_N,Delta_NE,Delta_E,Delta_SE,
        Delta_S,Delta_SW,Delta_W,Delta_NW,
        xp,yp;

    xp = x0; yp = y0;
    plot(xp,yp);

    d2y = 2*(y1-y0);
    d2x = 2*(x1-x0);
    dy  = (y1-y0);
    dx  = (x1-x0);

    if (y1 > y0) { //1,2,3 o 4
        if (x1 > x0) { //1 o 2
            Delta_NE =  dy-dx;
            if ( dy <= dx ){ //Octante 1

                Delta_E  =  dy;
                d = d2y-dy;

                while (xp <= x1){ //Avanza en x
                    xp++;
                    if (d<=0) {
                        d += Delta_E;
                    }
                    else {
                        yp++;
                        d += Delta_NE;
                    }
                    plot(xp,yp);
                }
            }
            else{ //Octante 2

                Delta_N  = -dx;
                d = dy -d2x;

                while (yp <= y1){ //Avanza en y
                    yp++;
                    if (d<=0) {
                        xp++;
                        d += Delta_NE;
                    }
                    else {
                        d += Delta_N;
                    }
                    plot(xp,yp);
                }
            }
        }
        else { //3 u 4
            Delta_NW = -dy-dx;
            if (dx >= -dy){ //Octante 3

                Delta_N  = -dx;
                d = -dy -d2x;

                while (yp <= y1){ //Avanza en y
                    yp++;
                    if (d<=0) {
                        d += Delta_N;
                    }
                    else {
                        xp--;
                        d += Delta_NW;
                    }
                    plot(xp,yp);
                }
            }
            else{ //Octante 4
                Delta_W  = -dy;
                d = -d2y-dx ;

                while (xp >= x1){ //Retrocede en x
                    xp--;
                    if (d<=0) {
                        yp++;
                        d += Delta_NW;
                    }
                    else {
                        d += Delta_W;
                    }
                    plot(xp,yp);
                }
            }
        }
    }
    else { //5,6,7 u 8
        if (x1 < x0) { //5 o 6
            Delta_SW = -dy+dx;
            if (dx <= dy){ //Octante 5

                Delta_W  = -dy   ;
                d = -d2y+dx ;

                while (xp >= x1){ //Retrocede en x
                    xp--;
                    if (d<=0) {
                        d += Delta_W;
                    }
                    else {
                        yp--;
                        d += Delta_SW;
                    }
                    plot(xp,yp);

                }
            }
            else{ //Octante 6

                Delta_S  =  dx;
                d = -dy +d2x;

                while (yp >= y1){ //Retrocede en y
                    yp--;
                    if (d<=0) {
                        xp--;
                        d += Delta_SW;
                    }
                    else {
                        d += Delta_S;
                    }
                    plot(xp,yp);

                }
            }
        }
        else { //7 u 8
            Delta_SE =  dy+dx;
            if (dx <= -dy){ //Octante 7

                Delta_S  =  dx   ;
                d =  dy +d2x;

                while (yp >= y1){ //Retrocede en y
                    yp--;
                    if (d<=0) {
                        d += Delta_S;
                    }
                    else {
                        xp++;
                        d += Delta_SE;
                    }
                    plot(xp,yp);

                }
            }
            else{ //Octante 8

                Delta_E  =  dy;
                d =  d2y+dx;

                while (xp <= x1){ //Avanza en x
                    xp++;
                    if (d<=0) {
                        yp--;
                        d += Delta_SE;
                    }
                    else {
                        d += Delta_E;
                    }
                    plot(xp,yp);

                }
            }
        }
    }
}



//Algoritmos sin plot

void line1noPlot (int x0, int y0, int x1, int y1){
    int i, temp;
    long double m,b,x,y;
    int vertical = 0;

    if ((x1 != x0)) {
        m = ((long double)(y1 - y0)) / (x1 - x0);
        b = (long double)(y0 - (m * x0));

        //printf("m: %Lf ", m);
        //printf("b: %Lf \n", b);
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

            //printf("X: %Lf ", x);
            //printf("X: %f",round(x));
            //printf("Y: %i\n",i);
            plot0();
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
                plot0();
            }
            else {
                y = ((long double)(m * i + b));

                //printf("Y: %Lf ", y);
                //printf("Y: %f ", round(y));
                //printf("X: %i \n", i);

                plot0();
            }
        }
    }
}
void line2noPlot (int x0, int y0, int x1, int y1){
    int i, temp;
    long double m,x,y;
    int vertical = 0;

    if ((x1 != x0)) {
        m = ((long double)(y1 - y0)) / (x1 - x0);
        //printf("m: %Lf \n", m);
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
            //printf("X: %Lf ", x);
            //printf("X: %f",round(x));
            //printf("Y: %i\n",i);

            plot0();

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
                //printf("Y: %Lf ", y);
                //printf("Y: %f ", round(y));
                //printf("X: %i \n", i);

                plot0();

                y += m;
            }
        }
    }
}
void line3noPlot (int x0, int y0, int x1, int y1){
    long double x, y;
    double paso_x, paso_y;
    int i, ancho;

    ancho = max(abs(x1 - x0), abs(y1 - y0));
    if (ancho == 0) {
        plot0();
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
            plot0();
            x += paso_x;
            y += paso_y;
        }
    }
}
void line4noPlot (int x0, int y0, int x1, int y1){ //Bresenham (punto medio)

    int d2x,d2y,dx,dy,d,
        Delta_N,Delta_NE,Delta_E,Delta_SE,
        Delta_S,Delta_SW,Delta_W,Delta_NW,
        xp,yp;

    xp = x0; yp = y0;
    plot0();

    d2y = 2*(y1-y0);
    d2x = 2*(x1-x0);
    dy  = (y1-y0);
    dx  = (x1-x0);

    if (y1 > y0) { //1,2,3 o 4
        if (x1 > x0) { //1 o 2
            Delta_NE =  dy-dx;
            if ( dy <= dx ){ //Octante 1

                Delta_E  =  dy;
                d = d2y-dy;

                while (xp <= x1){ //Avanza en x
                    xp++;
                    if (d<=0) {
                        d += Delta_E;
                    }
                    else {
                        yp++;
                        d += Delta_NE;
                    }
                    plot0();
                }
            }
            else{ //Octante 2

                Delta_N  = -dx;
                d = dy -d2x;

                while (yp <= y1){ //Avanza en y
                    yp++;
                    if (d<=0) {
                        xp++;
                        d += Delta_NE;
                    }
                    else {
                        d += Delta_N;
                    }
                    plot0();
                }
            }
        }
        else { //3 u 4
            Delta_NW = -dy-dx;
            if (dx >= -dy){ //Octante 3

                Delta_N  = -dx;
                d = -dy -d2x;

                while (yp <= y1){ //Avanza en y
                    yp++;
                    if (d<=0) {
                        d += Delta_N;
                    }
                    else {
                        xp--;
                        d += Delta_NW;
                    }
                    plot0();
                }
            }
            else{ //Octante 4
                Delta_W  = -dy;
                d = -d2y-dx ;

                while (xp >= x1){ //Retrocede en x
                    xp--;
                    if (d<=0) {
                        yp++;
                        d += Delta_NW;
                    }
                    else {
                        d += Delta_W;
                    }
                    plot0();
                }
            }
        }
    }
    else { //5,6,7 u 8
        if (x1 < x0) { //5 o 6
            Delta_SW = -dy+dx;
            if (dx <= dy){ //Octante 5

                Delta_W  = -dy   ;
                d = -d2y+dx ;

                while (xp >= x1){ //Retrocede en x
                    xp--;
                    if (d<=0) {
                        d += Delta_W;
                    }
                    else {
                        yp--;
                        d += Delta_SW;
                    }
                    plot0();

                }
            }
            else{ //Octante 6

                Delta_S  =  dx;
                d = -dy +d2x;

                while (yp >= y1){ //Retrocede en y
                    yp--;
                    if (d<=0) {
                        xp--;
                        d += Delta_SW;
                    }
                    else {
                        d += Delta_S;
                    }
                    plot0();

                }
            }
        }
        else { //7 u 8
            Delta_SE =  dy+dx;
            if (dx <= -dy){ //Octante 7

                Delta_S  =  dx   ;
                d =  dy +d2x;

                while (yp >= y1){ //Retrocede en y
                    yp--;
                    if (d<=0) {
                        d += Delta_S;
                    }
                    else {
                        xp++;
                        d += Delta_SE;
                    }
                    plot0();

                }
            }
            else{ //Octante 8

                Delta_E  =  dy;
                d =  d2y+dx;

                while (xp <= x1){ //Avanza en x
                    xp++;
                    if (d<=0) {
                        yp--;
                        d += Delta_SE;
                    }
                    else {
                        d += Delta_E;
                    }
                    plot0();

                }
            }
        }
    }
}



void startScreen(){
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, NULL);
    closegraph();

    initwindow (HSIZE,VSIZE);
}


void plot0(){}

void plot (int x, int y){
    putpixel(x,getmaxy()-y,4);
}

int max(int a, int b){
    if (a < b) { return b; }
    else { return a; }
}

int genRandLimNumber(int lim){
    srand(time(NULL));
    int r = rand() % lim;
    return r;
}

int runPlotlessAlgorithms(int numCor, int numVeces){
    clock_t start_a1, start_a2, start_a3, start_a4, end_a1, end_a2, end_a3, end_a4;
    int arregloCorX0[numCor];
    int arregloCorY0[numCor];
    int arregloCorX1[numCor];
    int arregloCorY1[numCor];
    int i,veces;

    for (i=0; i<numCor; i++){

        arregloCorX0[i] = genRandLimNumber(HSIZE);
        arregloCorY0[i] = genRandLimNumber(VSIZE);
        arregloCorX1[i] = genRandLimNumber(HSIZE);
        arregloCorY1[i] = genRandLimNumber(VSIZE);
    }

    printf("Ejecucion algoritmo 1 sin plot con %d lineas: \n", numCor);

    start_a1=clock();
    for (i=0; i<numCor; i++){
        for (veces=0; veces<numVeces; veces++){
            line1noPlot(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }


    }
    end_a1=clock();
    printf("Fin del algoritmo 1. Duracion: %lf segundos \n\n",((double) end_a1-start_a1)/CLOCKS_PER_SEC);

    printf("Ejecucion algoritmo 2 sin plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a2=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line2noPlot(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }
    }
    end_a2=clock();
    printf("Fin del algoritmo 2. Duracion: %lf segundos \n\n ",((double) end_a2-start_a2)/CLOCKS_PER_SEC);

    printf("Ejecucion algoritmo 3 sin plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a3=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line3noPlot(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }

    }
    end_a3=clock();
    printf("Fin del algoritmo 3. Duracion: %lf segundos \n \n",((double) end_a3-start_a3)/CLOCKS_PER_SEC);

    printf("Ejecucion algoritmo de Bressenhan sin plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a4=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line4noPlot(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }


    }
    end_a4=clock();
    printf("Fin del algoritmo de Bressenhan. Duracion: %lf segundos \n \n",((double) end_a4-start_a4)/CLOCKS_PER_SEC);


}


int runPlotAlgorithms(int numCor, int numVeces){
    clock_t start_a1, start_a2, start_a3, start_a4,end_a1, end_a2, end_a3, end_a4;
    int arregloCorX0[numCor];
    int arregloCorY0[numCor];
    int arregloCorX1[numCor];
    int arregloCorY1[numCor];
    int i, veces;

    startScreen();

    for (i=0; i<numCor; i++){

        arregloCorX0[i] = genRandLimNumber(HSIZE);
        arregloCorY0[i] = genRandLimNumber(VSIZE);
        arregloCorX1[i] = genRandLimNumber(HSIZE);
        arregloCorY1[i] = genRandLimNumber(VSIZE);
    }

    printf("Ejecucion algoritmo 1 con plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a1=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line1(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }
    }
    end_a1=clock();
    printf("Fin del algoritmo 1. Duracion: %lf segundos \n\n",((double) end_a1-start_a1)/CLOCKS_PER_SEC);
    delay(2000);
    printf("Ejecucion algoritmo 2 con plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a2=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line2(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }
    }
    end_a2=clock();
    printf("Fin del algoritmo 2. Duracion: %lf segundos \n\n ",((double) end_a2-start_a2)/CLOCKS_PER_SEC);
    delay(2000);
    printf("Ejecucion algoritmo 3 con plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a3=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line3(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }
    }
    end_a3=clock();
    printf("Fin del algoritmo 3. Duracion: %lf segundos \n \n",((double) end_a3-start_a3)/CLOCKS_PER_SEC);
    delay(2000);
    printf("Ejecucion algoritmo de Bressenhan con plot con %d lineas dibujadas %d veces: \n \n", numCor, numVeces);

    start_a4=clock();
    for (i=0; i<numCor; i++){

        for (veces=0; veces<numVeces; veces++){
            line4(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i]);
        }
    }
    end_a4=clock();
    printf("Fin del algoritmo de Bressenhan. Duracion: %lf segundos \n \n",((double) end_a4-start_a4)/CLOCKS_PER_SEC);

}

int main() {
    //El main debe asegurarse que
    //      max(x0,x1) < Xres
    //      min(x0,x0) > 0
    //      max(y0,y1) < Yres
    //      min(y0,y1) > 0

    runPlotlessAlgorithms(10000, 3000);

    //runPlotAlgorithms(1000);
    /*

    startScreen();

    int x0 = 150;
    int y0 = 150;

    int x1 = 190;
    int y1 = 190;

    int x1s[8] = {150, 110, 110, 110, 150, 190, 190, 190};
    int y1s[8] = {190, 190, 150, 110, 110, 110, 150, 190};

    for (int i = 0; i<8; i++){
        line1(x0     ,y0     ,x1s[i]     ,y1s[i]);
        line2(x0     ,y0+100 ,x1s[i]     ,y1s[i]+100);
        line3(x0+100 ,y0+100 ,x1s[i]+100 ,y1s[i]+100);
        line4(x0+100 ,y0     ,x1s[i]+100 ,y1s[i]);
    }
    */

    //delay(6000);
    return 0;
}
