
#include "common.h"
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H


// Variáveis para armazenar o ângulo de pitch e yaw
float pitch = 0.0f;
float yaw = -90.0f;  // Inicialmente olhando para o eixo Z negativo

// Variáveis para armazenar a posição anterior do mouse
int lastMouseX, lastMouseY;
bool firstMouse = true;

// Posição da câmera
glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);  // Altura inicial de 1.0f para estar acima do plano
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Função para atualizar a câmera
void updateCamera() {
    glm::mat4 view = glm::lookAt(
        cameraPos,
        cameraPos + cameraFront,
        cameraUp
    );

    // Passar a matriz de visualização para o shader (ou para a matriz de visualização do OpenGL)
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
}

// Função de callback para teclas normais (W, A, S, D)
void keyboard(unsigned char key, int x, int y) {
    const float cameraSpeed = 0.05f;

    switch (key) {
        case 'w':
            cameraPos += cameraSpeed * cameraFront;
            break;
        case 's':
            cameraPos -= cameraSpeed * cameraFront;
            break;
        case 'a':
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        case 'd':
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;

        // TAB
        case 9:
            GRID_PLANE = !GRID_PLANE;
            glutPostRedisplay();
            break;
        
        // ESC
        case 27:
            exit(0);
        default:
            break;
    }

    // Atualizar a câmera após a mudança de posição
    updateCamera();

    // Redesenhar a cena
    glutPostRedisplay();
}

// Função de callback para movimento do mouse
void mouseMotion(int x, int y) {
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    lastMouseX = x;
    lastMouseY = y;

    const float sensitivity = 0.1f;
    yaw += deltaX * sensitivity;
    pitch -= deltaY * sensitivity;

    // Limitar o pitch para evitar a inversão da câmera
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Atualizar a direção da câmera
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    // Atualizar a câmera após a mudança de ângulo
    updateCamera();

    // Redesenhar a cena
    glutPostRedisplay();
}


#endif //INPUT_MANAGER_H
