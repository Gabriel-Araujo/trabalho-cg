
#include "common.h"

void display_esphere() {
   // Salva a matriz de transformação atual
    glPushMatrix();

   // define a cor da esfera 
   glColor3f(1.0f, 0.0f, 0.0f);
    
   // Move a esfera para cima (e.g., 2 unidades no eixo Y)
   glTranslatef(0.0f, 2.0f, 0.0f);

   // Desenha a esfera
   GLUquadric* quadric = gluNewQuadric();
   gluSphere(quadric, 1.0, 32, 32); // Raio, número de fatias, número de stacks
   gluDeleteQuadric(quadric);

   // Restaura a matriz de transformação
   glPopMatrix();
}