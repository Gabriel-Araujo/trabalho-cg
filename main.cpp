// main.cpp
#include <GL/glew.h>
#include <GL/glut.h>
#include "utils/common.h"
#include "gridplane/gridplane.h"
#include "utils/input.h"
#include "light.h"
#include "utils/objLoader.h"

std::vector<CustomLoadedObject> objects;

void init() {
    glClearColor(0.296875, 0.59375, 0.953125, 0.96);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    CustomLoadedObject car = loadOBJ("/home/luccas/CG/trabalho-cg/Models/uploads_files_2787791_Mercedes+Benz+GLS+580.obj", ".");
    objects.push_back(car);
    init_grid_plane();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    display_grid_plane();

    // Atualizando a posição do carro de acordo com a posição da câmera
    auto carPosition = cameraPos + glm::vec3(-2.3f, -1.7f, 10.0f) + cameraFront;

    // Calcular a rotação do carro
    float angle = atan2(cameraFront.x, cameraFront.z) * 180.0f / M_PI;

    // Salvar o estado atual da matriz
    glPushMatrix();
    
    // Transladar para a posição do carro
    glTranslatef(carPosition.x, carPosition.y, carPosition.z);
    
    // Rotacionar o carro
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Desenhar o carro
    displayObject(objects[0], glm::vec3(0.0f, 0.0f, 0.0f)); // o carro é desenhado na origem local
    
    // Restaurar a matriz
    glPopMatrix();
    
    glutSwapBuffers();
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Our cool project!");
    glutFullScreen();

    glewInit();
    init();

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(render);
    glutPassiveMotionFunc(mouseMotion);

    updateCamera();
    glutMainLoop();
    return 0;
}