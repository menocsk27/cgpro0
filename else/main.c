/*
 * Instituto Tecnologico de Costa Rica
 * Escuela de Ingenieria en Computacion
 * Computer Graphics
 *
 * Programa: Mesa Example
 * Archivo:  mesa_example.c
 */

#include "mesa_example.h"
#include "malloc.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void draw_scene ();

COLOR **buffer;

int main(int argc, char** argv) 
{

  buffer = (COLOR **)malloc(H_SIZE * sizeof(COLOR*));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(H_SIZE,V_SIZE);
  glutCreateWindow("Mesa Example");
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-0.5, H_SIZE +0.5, -0.5, V_SIZE + 0.5);
  glutDisplayFunc(draw_scene);
  draw_scene();
  glutMainLoop();

}


void draw_scene() {
  int i, j;
  COLOR color;

  glColor3f (1,0,0);
  glBegin (GL_POINTS);
  glVertex2i (10,10);
  glEnd();


  glFlush();
}




