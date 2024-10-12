#include <GL/glew.h>
#include <GL/glut.h>
#include "utils/common.h"
#include "gridplane/gridplane.h"
// #include "esphere/esphere.h"
#include "utils/input.h"
#include "light.h"
#include "utils/objLoader.h"

std::vector<CustomLoadedObject> objects;

void init() {
    glClearColor(0.296875, 0.59375, 0.953125, 0.96);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    CustomLoadedObject myObj1 = loadOBJ("/home/luccas/CG/trabalho-cg/Models/Jeep_Renegade_2016.obj", "/home/luccas/CG/trabalho-cg/Models/Jeep_Renegade_2016/car_jeep_ren.jpg");
    for(int i = 0; i < 30; i++){
        objects.push_back(myObj1);
    }

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
    glm::vec3 obj1Pos = glm::vec3(0.0f, 0.0f, 0.0f);
    for (const auto& obj : objects) {
        displayObject(obj, obj1Pos);
        obj1Pos.x += 2.0f;
    }
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
