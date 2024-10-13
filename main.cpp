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
    CustomLoadedObject city = loadOBJ("../models/city/02/city.obj", "../models/city/02/city.mtl");
    CustomLoadedObject myObj1 = loadOBJ(
        "../models/car/mercedes/car.obj",
        "");

        objects.push_back(myObj1);
        objects.push_back(city);

    init_grid_plane();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_grid_plane();
    auto carPosition = cameraPos + glm::vec3(-2.3f, -1.7f, 4.0f);

    displayObject(objects[0], carPosition);
    displayObject(objects[1], glm::vec3(0, 0, 0));
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Our cool project!");
    glutFullScreen(); 

    glewInit();
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMotion);

    updateCamera();
   
    glutMainLoop();
    return 0;
}
