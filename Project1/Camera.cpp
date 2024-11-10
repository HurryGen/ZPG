#include "Camera.h"



Camera::Camera()
{
    aspect = 4.0f / 3.0f;
    fov = 60.0f;
    projectionMat = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
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
    notify();
}

void Camera::moveRight()
{
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye += right * movementSpeed;
    notify();
}

void Camera::moveForward()
{
    
    glm::vec3 forward = glm::normalize(target);
    eye += forward * movementSpeed;
    notify();
}

void Camera::moveBackward()
{
    
    glm::vec3 forward = glm::normalize(target);
    eye -= forward * movementSpeed;
    notify();
}


void Camera::updateCameraVector()
{
    target.x = cos(glm::radians(alpha)) * cos(glm::radians(fi));
    target.y = sin(glm::radians(fi));
    target.z = sin(glm::radians(alpha)) * cos(glm::radians(fi));

    target = glm::normalize(target);
    notify();
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

glm::vec3 Camera::getPosition()
{
    return eye;
}

void Camera::setProjection(float fov, float aspect, float near, float far)
{
    this->fov = fov;
    this->aspect = aspect;
    projectionMat = glm::perspective(glm::radians(fov), aspect, near, far);
    notify();
}

void Camera::updateAspect(float width, float height)
{
    aspect = width / height;
    setProjection(fov, aspect, 0.1f, 100.0f);
}




void Camera::attach(Observer* observer)
{
    observers.push_back(observer);
}

void Camera::detach(Observer* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notify()
{
    for (auto observer : observers)
    {
        observer->update(this);
    }
}
