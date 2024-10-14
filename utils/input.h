
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include "common.h"


// Variáveis para armazenar o ângulo de pitch e yaw
inline float pitch = 0.0f;
inline float yaw = 90.0f;  // Inicialmente olhando para o eixo Z negativo


// Variáveis para armazenar a posição anterior do mouse
inline int lastMouseX, lastMouseY;
inline bool firstMouse = true;

// Posição da câmera
inline auto cameraPos = glm::vec3(0.0f, 4.0f, 0.0f);  // Altura inicial de 1.0f para estar acima do plano
inline auto cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
inline auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Velocidade na qual a câmera se move.
constexpr float cameraSpeed = 0.5f;

// Função para atualizar a câmera
inline void updateCamera() {
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
inline void keyboard(const unsigned char key, int x, int y) {

    switch (key) {
        case 'w':
            cameraPos += cameraSpeed * cameraFront;
            break;
        case 's':
            cameraPos -= cameraSpeed * cameraFront;
            break;
        case 'a':
            cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        case 'd':
            cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        
        // Atualiza a posição do carro conforme a câmera se move
        cameraPos += cameraSpeed * cameraFront;

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
    cameraPos[1] = 4;

    // Atualizar a câmera após a mudança de posição
    updateCamera();

    // Redesenhar a cena
    glutPostRedisplay();
}

// Função de callback para movimento do mouse
inline void mouseMotion(const int x, const int y) {
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    const int deltaX = x - lastMouseX;
    const int deltaY = y - lastMouseY;

    lastMouseX = x;
    lastMouseY = y;

    constexpr float sensitivity = 0.1f;
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
