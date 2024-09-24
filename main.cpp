#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

/*  Create checkerboard textures  */
#define checkImageWidth 64
#define checkImageHeight 64

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;

void makeCheckImages() {
   for (int line = 0; line < checkImageHeight; line++) {
      for (int column = 0; column < checkImageWidth; column++) {
         const int pixel_color = ((line & 0x1) == 0^(column & 0x1) == 0) * 255;

         checkImage[line][column][0] = static_cast<GLubyte>(pixel_color); // red
         checkImage[line][column][1] = static_cast<GLubyte>(pixel_color); // green
         checkImage[line][column][2] = static_cast<GLubyte>(pixel_color); // blue
         checkImage[line][column][3] = static_cast<GLubyte>(255);
      }
   }
}

void init()
{
   glClearColor(0.296875, 0.59375, 0.953125, 0.96);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);

   // Retângulo centralizado no ponto (0, 0, 0) e paralelo ao plano XY
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-40.0, -40.0, 0.0);  // Vértice inferior esquerdo
   glTexCoord2f(0.0, 1.0); glVertex3f(-40.0, 40.0, 0.0);   // Vértice superior esquerdo
   glTexCoord2f(1.0, 1.0); glVertex3f(40.0, 40.0, 0.0);    // Vértice superior direito
   glTexCoord2f(1.0, 0.0); glVertex3f(40.0, -40.0, 0.0);   // Vértice inferior direito
   glEnd();

   glFlush();
   glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(0.0, 0.0, -1);

   // Mover a câmera para (0, 0, 1) e fazer ela olhar para o plano XZ
   gluLookAt(0.0, 0.0, 1.0,   // Posição da câmera
             0.0, 1.0, 1.0,   // Ponto para onde a câmera olha (eixo Y)
             0.0, 0.0, 1.0);  // Vetor "para cima" (direção do eixo Z)
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}