#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pro0.h"
#include "malloc.h"
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int res;
COLOR **buffer;

void plot0( int x, int y){   
}

void plot (int x, int y){
    COLOR color;

  	glBegin (GL_POINTS);
  	glVertex2i (x,y);
  	glEnd();
}

int max(int a, int b){
    if (a < b) { return b; }
    else { return a; }
}

int genRandLimNumber(int lim){
    static double tiempo;
    tiempo+=time(NULL);
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 50000;
    nanosleep(&tim , &tim2);
    srand(tiempo);
    return (rand() % lim);
}

//Algoritmos
void line1 (int x0, int y0, int x1, int y1, void (*plot)(int,int) ){
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
            (*plot)(((int)round(x)),i);
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
                (*plot)(x0,y0);
            }
            else {
                y = ((long double)(m * i + b));

                //printf("Y: %Lf ", y);
                //printf("Y: %f ", round(y));
                //printf("X: %i \n", i);

                (*plot)(i,((int)round(y)));
            }
        }
    }
}
void line2 (int x0, int y0, int x1, int y1, void (*plot)(int,int) ){
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

            (*plot)(((int)round(x)),i);

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
                (*plot)(x0,y0);
            }
            else {
                //printf("Y: %Lf ", y);
                //printf("Y: %f ", round(y));
                //printf("X: %i \n", i);

                (*plot)(i,((int)round(y)));

                y += m;
            }
        }
    }
}
void line3 (int x0, int y0, int x1, int y1, void (*plot)(int,int)){
    long double x, y;
    double paso_x, paso_y;
    int i, ancho;

    ancho = max(abs(x1 - x0), abs(y1 - y0));
    if (ancho == 0) {
        (*plot)(x0, y0);
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
            (*plot)(cordX, cordY);
            x += paso_x;
            y += paso_y;
        }
    }
}
void line4 (int x0, int y0, int x1, int y1, void (*plot)(int,int)){ //Bresenham (punto medio)

    int d2x,d2y,dx,dy,d,
        Delta_N,Delta_NE,Delta_E,Delta_SE,
        Delta_S,Delta_SW,Delta_W,Delta_NW,
        xp,yp;

    xp = x0; yp = y0;
    (*plot)(xp,yp);

    d2y = 2*(y1-y0);
    d2x = 2*(x1-x0);
    dy  = (y1-y0);
    dx  = (x1-x0);

    if (y1 > y0) { //1,2,3 o 4
        if (x1 > x0) { //1 o 2
            Delta_NE =  d2y-d2x;
            if ( dy <= dx ){ //Octante 1

                Delta_E  =  d2y;
                d = d2y-dx;

                while (xp < x1){ //Avanza en x
                    xp++;
                    if (d<0) {
                        d += Delta_E;
                    }
                    else {
                        yp++;
                        d += Delta_NE;
                    }
                    (*plot)(xp,yp);
                }
            }
            else{ //Octante 2

                Delta_N  = -d2x;
                d = dy -d2x;

                while (yp < y1){ //Avanza en y
                    yp++;
                    if (d<=0) {
                        xp++;
                        d += Delta_NE;
                    }
                    else {
                        d += Delta_N;
                    }
                    (*plot)(xp,yp);
                }
            }
        }
        else { //3 u 4
            Delta_NW = -d2y-d2x;
            if (dx >= -dy){ //Octante 3

                Delta_N  = -d2x;
                d = -dy -d2x;

                while (yp < y1){ //Avanza en y
                    yp++;
                    if (d<=0) {
                        d += Delta_N;
                    }
                    else {
                        xp--;
                        d += Delta_NW;
                    }
                    (*plot)(xp,yp);
                }
            }
            else{ //Octante 4
                Delta_W  = -d2y;
                d = -d2y-dx ;

                while (xp > x1){ //Retrocede en x
                    xp--;
                    if (d<=0) {
                        yp++;
                        d += Delta_NW;
                    }
                    else {
                        d += Delta_W;
                    }
                    (*plot)(xp,yp);
                }
            }
        }
    }
    else { //5,6,7 u 8
        if (x1 < x0) { //5 o 6
            Delta_SW = -d2y+d2x;
            if (dx <= dy){ //Octante 5

                Delta_W  = -d2y   ;
                d = -d2y+dx ;

                while (xp > x1){ //Retrocede en x
                    xp--;
                    if (d<=0) {
                        d += Delta_W;
                    }
                    else {
                        yp--;
                        d += Delta_SW;
                    }
                    (*plot)(xp,yp);

                }
            }
            else{ //Octante 6

                Delta_S  =  d2x;
                d = -dy +d2x;

                while (yp > y1){ //Retrocede en y
                    yp--;
                    if (d<0) {
                        xp--;
                        d += Delta_SW;
                    }
                    else {
                        d += Delta_S;
                    }
                    (*plot)(xp,yp);

                }
            }
        }
        else { //7 u 8
            Delta_SE =  d2y+d2x;
            if (dx <= -dy){ //Octante 7

                Delta_S  =  d2x   ;
                d =  dy +d2x;

                while (yp > y1){ //Retrocede en y
                    yp--;
                    if (d<0) {
                        d += Delta_S;
                    }
                    else {
                        xp++;
                        d += Delta_SE;
                    }
                    (*plot)(xp,yp);

                }
            }
            else{ //Octante 8

                Delta_E  =  d2y;
                d =  d2y+dx;

                while (xp < x1){ //Avanza en x
                    xp++;
                    if (d<0) {
                        yp--;
                        d += Delta_SE;
                    }
                    else {
                        d += Delta_E;
                    }
                    (*plot)(xp,yp);

                }
            }
        }
    }
}

int timeAlgorithms(int numLineas, int numVeces, void (*f)(int,int) , char wplot[] ){
    clock_t start[4], end[4];
    int arregloCorX0[numLineas], arregloCorY0[numLineas], arregloCorX1[numLineas], arregloCorY1[numLineas];
    int i,veces;

    for (i=0; i<numLineas; i++){
        arregloCorX0[i] = genRandLimNumber(res);
        arregloCorY0[i] = genRandLimNumber(res);
        arregloCorX1[i] = genRandLimNumber(res);
        arregloCorY1[i] = genRandLimNumber(res);
    }

    //Algoritmo 1
    glColor3f (0,1,0);
    start[0]=clock();
    for (i=0; i<numLineas; i++){
        for (veces=0; veces<numVeces; veces++){
            line1(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i],(*f));
        }
    }
    end[0]=clock();

    glColor3f (0,1,1);
    //Algoritmo 2
    start[1]=clock();
    for (i=0; i<numLineas; i++){
        for (veces=0; veces<numVeces; veces++){
            line2(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i], (*f));
        }
    }
    end[1]=clock();

    glColor3f (1,0,1);
    //Algoritmo 3
    start[2]=clock();
    for (i=0; i<numLineas; i++){
        for (veces=0; veces<numVeces; veces++){
            line3(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i], (*f));
        }
    }
    end[2]=clock();

    glColor3f (1,0,0);
    //Algoritmo 4
    start[3]=clock();
    for (i=0; i<numLineas; i++){
        for (veces=0; veces<numVeces; veces++){
            line4(arregloCorX0[i],arregloCorY0[i], arregloCorX1[i], arregloCorY1[i], (*f));
        }
    }
    end[3]=clock();

    printf("Duraciones %s plot.\n \t\tAlgoritmo \tDuración\n", wplot);
    for (i=0;i<=3;i++){
        printf("\t\t %i. \t\t %lf segundos \n",(i+1),((double) end[i]-start[i])/CLOCKS_PER_SEC);
    }
}

int main(int argc, char *argv[]) {

    int lineas, veces; 
    if( argc != 4 ) {
      printf("Se espera 3 parametros. \n Introduzca los parametros de forma <programa> <resolucion> <# lineas> <# veces>");
      return 0;
    }

    if (sscanf (argv[1], "%i", &res)!=1) {
        printf ("error - <resolucion> no es un entero");
        return 0;
    }
    if (sscanf (argv[2], "%i", &lineas)!=1) { 
        printf ("error - <# lineas> no es un entero");
        return 0;
    }
    if (sscanf (argv[3], "%i", &veces)!=1) {
        printf ("error - <# veces> no es un enteror");
        return 0;
    }

    buffer = (COLOR **)malloc(res * sizeof(COLOR*));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(res,res);
    glutCreateWindow("CG Proyecto 0");
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-0.5, res +0.5, -0.5, res + 0.5);
    

    printf("Tecnológico de Costa Rica\n IC8019 - Gráficos Por Computadora, PROYECTO 0: Algoritmos de líneas\n");
    printf("\n\n Profesor: Dr. Francisco Torres Rojas\n");
    printf(" Estudiantes:\n\tCarlos Girón Alas\n\tJulián J. Méndez Oconitrillo\n\tDaniel Troyo Garro\n");
    printf("17 agosto 2016\n\n");
     
    timeAlgorithms(lineas, veces, plot0, "sin");
    timeAlgorithms(lineas, veces, plot, "con");
    
    glFlush();
    glutMainLoop();

    return 0;
}
