//
// Created by Gabriel on 25/09/2024.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define checkImageWidth 64
#define checkImageHeight 64

static bool GRID_PLANE = false;
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;
static GLfloat plane_color[4] = {0.2109375, 0.57421875, 0.1484375, 0.2265625};

#endif //CONSTANTS_H
