#ifndef CUSTOM_LOADED_OBJECT_H
#define CUSTOM_LOADED_OBJECT_H

#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <tiny_obj_loader.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include <optional>
#include <sstream>


struct CustomLoadedObject {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    GLuint textureID;
};

inline CustomLoadedObject loadObj(const std::string& pathToObj) {
    CustomLoadedObject obj;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;


    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, pathToObj.c_str())) {
        std::cerr << "Error loading .obj: " << err << std::endl;
        return obj;
    }
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            obj.vertices.emplace_back(attrib.vertices[3 * index.vertex_index + 0],
                                      attrib.vertices[3 * index.vertex_index + 1],
                                      attrib.vertices[3 * index.vertex_index + 2]);

            if (index.texcoord_index >= 0) {
                obj.uvs.emplace_back(attrib.texcoords[2 * index.texcoord_index + 0],
                                     1.0f - attrib.texcoords[2 * index.texcoord_index + 1]); // Inverter Y
            }

            if (index.normal_index >= 0) {
                obj.normals.emplace_back(attrib.normals[3 * index.normal_index + 0],
                                         attrib.normals[3 * index.normal_index + 1],
                                         attrib.normals[3 * index.normal_index + 2]);
            }
        }
    }

    std::cout << "Object loaded successfully!" << std::endl;
    return obj;
}


inline CustomLoadedObject loadObj(const std::string& pathToObj, const std::string& pathToTexture) {
    CustomLoadedObject obj;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;


    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, pathToObj.c_str())) {
        std::cerr << "Error loading .obj: " << err << std::endl;
        return obj;
    }
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            obj.vertices.emplace_back(attrib.vertices[3 * index.vertex_index + 0],
                                      attrib.vertices[3 * index.vertex_index + 1],
                                      attrib.vertices[3 * index.vertex_index + 2]);

            if (index.texcoord_index >= 0) {
                obj.uvs.emplace_back(attrib.texcoords[2 * index.texcoord_index + 0],
                                     1.0f - attrib.texcoords[2 * index.texcoord_index + 1]); // Inverter Y
            }

            if (index.normal_index >= 0) {
                obj.normals.emplace_back(attrib.normals[3 * index.normal_index + 0],
                                         attrib.normals[3 * index.normal_index + 1],
                                         attrib.normals[3 * index.normal_index + 2]);
            }
        }
    }

    // Aplicando textura
    glGenTextures(1, &obj.textureID);
    glBindTexture(GL_TEXTURE_2D, obj.textureID);

    int width, height, channels;
    unsigned char* data = stbi_load(pathToTexture.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error loading texture." << std::endl;
        return obj;
    }

    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    std::cout << "Object loaded successfully!" << std::endl;
    return obj;
}


GLuint LoadTexture(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    return texture;
}


inline CustomLoadedObject loadObj(const std::string& object_name, const std::string& basePath, int a) {
    CustomLoadedObject obj;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    const auto obj_path = basePath + "/" + object_name + ".obj";

    if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_path.c_str(), basePath.c_str())) {
        std::cerr << "Error loading .obj: " << err << std::endl;
        return obj;
    }

    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }


    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            obj.vertices.emplace_back(attrib.vertices[3 * index.vertex_index + 0],
                                      attrib.vertices[3 * index.vertex_index + 1],
                                      attrib.vertices[3 * index.vertex_index + 2]);

            if (index.texcoord_index >= 0) {
                obj.uvs.emplace_back(attrib.texcoords[2 * index.texcoord_index + 0],
                                     1.0f - attrib.texcoords[2 * index.texcoord_index + 1]); // Inverter Y
            }

            if (index.normal_index >= 0) {
                obj.normals.emplace_back(attrib.normals[3 * index.normal_index + 0],
                                         attrib.normals[3 * index.normal_index + 1],
                                         attrib.normals[3 * index.normal_index + 2]);
            }
        }
    }


    for (const auto& material : materials) {
        std::cout << "Material name: " << material.name << std::endl;
        std::string texture_path = basePath + "/" +material.diffuse_texname;

        if (!material.diffuse_texname.empty()) {
            int width, height, channels;
            unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);
            if (!data) {
                std::cerr << "Error loading texture." << std::endl;
                return obj;
            }
            glGenTextures(1, &obj.textureID);
            glBindTexture(GL_TEXTURE_2D, obj.textureID);

            GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);

            std::cout << "Diffuse texture: " << material.diffuse_texname << std::endl;
        }
    }

    // Exibir informações sobre a geometria carregada
    std::cout << "Número de vértices: " << (attrib.vertices.size() / 3) << std::endl;
    std::cout << "Número de normais: " << (attrib.normals.size() / 3) << std::endl;
    std::cout << "Número de coordenadas de textura: " << (attrib.texcoords.size() / 2) << std::endl;




    std::cout << "Object loaded successfully!" << std::endl;
    return obj;
}

inline void copyTexture(GLuint sourceTextureID, GLuint& destTextureID) {
    glGenTextures(1, &destTextureID);
    glBindTexture(GL_TEXTURE_2D, sourceTextureID);

    int width, height, channels;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &channels);

    unsigned char* data = new unsigned char[width * height * (channels == GL_RGB ? 3 : 4)];
    glGetTexImage(GL_TEXTURE_2D, 0, channels, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, destTextureID);
    GLenum format = (channels == GL_RGB) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] data;
}

inline CustomLoadedObject copyObject(const CustomLoadedObject& source) {
    CustomLoadedObject copy;
    copy.vertices = source.vertices;
    copy.uvs = source.uvs;
    copy.normals = source.normals;
    copyTexture(source.textureID, copy.textureID);
    return copy;
}

// recebe o objeto e a posição do objeto
inline void displayObject(const CustomLoadedObject& obj, const glm::vec3& position) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, obj.textureID);

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < obj.vertices.size(); i++) {
        glTexCoord2f(obj.uvs[i].x, obj.uvs[i].y);
        glNormal3f(obj.normals[i].x, obj.normals[i].y, obj.normals[i].z);
        glVertex3f(obj.vertices[i].x, obj.vertices[i].y, obj.vertices[i].z);
    }
    glEnd();

    glPopMatrix();
}

#endif //CUSTOM_LOADED_OBJECT_H