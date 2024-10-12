#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

struct Light {
    glm::vec3 position;   // Posição da luz
    glm::vec3 ambient;    // Cor de luz ambiente
    glm::vec3 diffuse;    // Cor de luz difusa
    glm::vec3 specular;   // Cor de luz especular

    Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
        : position(pos), ambient(amb), diffuse(diff), specular(spec) {}
};

#endif // LIGHT_H
