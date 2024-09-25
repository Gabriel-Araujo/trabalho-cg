#include <GL/glut.h>

#include "utils/camera.h"
#include "utils/gridplane.h"
#include "utils/keyboard.h"


void init() {
   glClearColor(0.296875, 0.59375, 0.953125, 0.96);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   init_grid_plane();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   display_grid_plane();
   glFlush();
}

void reshape(const GLsizei w, const GLsizei h) {
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(0.0, 0.0, -1);

   // Move a câmera para o ponto (0, 0, 1) e faz ela olhar para o plano XZ
   gluLookAt(position[0], position[1], position[2], // Posição da câmera
             look_at[0], look_at[1], look_at[2],   // Ponto para onde a câmera olha (eixo Y)
             up[0], up[1], up[2]);  // Vetor "para cima" (direção do eixo Z)
}



int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}