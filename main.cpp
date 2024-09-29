
#include "utils/common.h"
#include "gridplane/gridplane.h"
#include "esphere/esphere.h"
#include "utils/input.h"



void init() {
   // Define a cor de fundo da janela como azul
   glClearColor(0.296875, 0.59375, 0.953125, 0.96);

   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   init_grid_plane();
}



void reshape(int w, int h) {
   
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   display_grid_plane();
   display_esphere();
   
   glFlush();

   glutSwapBuffers();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Our cool project!");

   init();

   // callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutPassiveMotionFunc(mouseMotion);

   // Configurações iniciais da câmera
   updateCamera();
   
   // Definir a janela em modo de tela cheia
   glutFullScreen(); 
   glutMainLoop();
   return 0;
}