//
// Created by Gabriel on 25/09/2024.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <cstdlib>
#include <GL/glut.h>

inline void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 9:
            GRID_PLANE = !GRID_PLANE;
        glutPostRedisplay();
            break;
        case 27:
            exit(0);
        default:
            break;
    }
}

#endif //KEYBOARD_H
