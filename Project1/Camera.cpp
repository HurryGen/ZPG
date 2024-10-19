#include "Camera.h"



Camera::Camera()
{
    projectionMat = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    eye = glm::vec3(0.0f, 0.0f, 5.0f);
    target = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    movementSpeed = 0.1f;
    alpha = 0.f;
    fi = 0.f;
}

glm::mat4 Camera::getCamera()
{
    return glm::lookAt(eye, eye + target, up);
}

void Camera::moveLeft()
{
    glm::vec3 left = glm::normalize(glm::cross(up, target));
    eye += left * movementSpeed;
    notifyShaders();
}

void Camera::moveRight()
{
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye += right * movementSpeed;
    notifyShaders();
}

void Camera::moveForward()
{
    
    glm::vec3 forward = glm::normalize(target);
    eye += forward * movementSpeed;
    notifyShaders();
}

void Camera::moveBackward()
{
    
    glm::vec3 forward = glm::normalize(target);
    eye -= forward * movementSpeed;
    notifyShaders();
}


void Camera::updateCameraVector()
{
    target.x = cos(glm::radians(alpha)) * cos(glm::radians(fi));
    target.y = sin(glm::radians(fi));
    target.z = sin(glm::radians(alpha)) * cos(glm::radians(fi));

    target = glm::normalize(target);
    notifyShaders();
}

glm::mat4 Camera::getProjection()
{
    return projectionMat;
}

void Camera::updatePosition(float x, float y)
{
    x *= 0.1f; 
    y *= 0.1f;

    alpha += x;
    fi += y;

  
    if (fi > 89.f)
        fi = 89.f;
    if (fi < -89.f)
        fi = -89.f;

  
    updateCameraVector();



}

void Camera::registerShader(Shader* shader)
{
    shaders.push_back(shader);
}

void Camera::notifyShaders()
{
    for (auto shader : shaders) {
        shader->updateCameraPosition();
    }
}
