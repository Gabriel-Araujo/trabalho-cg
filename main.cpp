// main.cpp
#include <GL/glew.h>
#include <GL/glut.h>
#include "utils/common.h"
#include "artifacts/gridplane/gridplane.h"
#include "artifacts/esphere/esphere.h"
#include "utils/input.h"
#include "utils/light.h"
#include "utils/objLoader.h"

std::vector<CustomLoadedObject> objects;

void init() {
    glClearColor(0.296875, 0.59375, 0.953125, 0.96);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    CustomLoadedObject car = loadObj(
        "../models/car/mercedes/car.obj",
        "");
    CustomLoadedObject house = loadObj("house1", "../models/city/02", 0);
    CustomLoadedObject house2 = loadObj("house2", "../models/city/02", 0);
    CustomLoadedObject house3 = loadObj("house3", "../models/city/02", 0);
    CustomLoadedObject house4 = loadObj("house4", "../models/city/02", 0);
    CustomLoadedObject house5 = loadObj("house5", "../models/city/02", 0);
    CustomLoadedObject house6 = loadObj("house6", "../models/city/02", 0);
    CustomLoadedObject a = loadObj("cha", "../models/city/02");


    objects.push_back(car);

    objects.push_back(house);
    objects.push_back(house2);
    objects.push_back(house3);
    objects.push_back(house4);
    objects.push_back(house5);
    objects.push_back(house6);
    objects.push_back(a);
    init_grid_plane();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 0.1, 200.0);
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
    

//     // Carro
//     displayObject(objects[0], carPosition);

    // Casas
    displayObject(objects[1], glm::vec3(0,0,0));
    displayObject(objects[2], glm::vec3(0,0,0));
    displayObject(objects[3], glm::vec3(0,0,0));
    displayObject(objects[4], glm::vec3(0,0,0));
    displayObject(objects[5], glm::vec3(0,0,0));
    displayObject(objects[6], glm::vec3(0,0,0));
    displayObject(objects[7], glm::vec3(0,0,0));

    // Chão
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