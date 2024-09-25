//
// Created by Gabriel on 25/09/2024.
//

#ifndef GRIDPLANE_H
#define GRIDPLANE_H
#include <GL/gl.h>

#include "constants.h"

inline void makeCheckImages() {
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

inline void init_grid_plane() {
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

inline void display_grid_plane() {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);

    if (!GRID_PLANE) {
        glColor4f(plane_color[0],plane_color[1],plane_color[2],plane_color[3]);
        glDisable(GL_TEXTURE_2D);
    }


    // Retângulo centralizado no ponto (0, 0, 0) e paralelo ao plano XY
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, -100.0, 0.0);  // Vértice inferior esquerdo
    glTexCoord2f(0.0, 1.0); glVertex3f(-100.0, 100.0, 0.0);   // Vértice superior esquerdo
    glTexCoord2f(1.0, 1.0); glVertex3f(100.0, 100.0, 0.0);    // Vértice superior direito
    glTexCoord2f(1.0, 0.0); glVertex3f(100.0, -100.0, 0.0);   // Vértice inferior direito
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

#endif //GRIDPLANE_H
