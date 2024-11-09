#pragma once
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Subject.h"
#include <vector>

class Camera : public Subject
{
public:
	Camera();
	glm::mat4 getCamera();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();
	void updateCameraVector();
	glm::mat4 getProjection();
	void updatePosition(float x, float y);
	glm::vec3 getPosition();

	void attach(Observer* observer) override;
	void detach(Observer* observer) override;
	void notify() override;



private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 projectionMat;
	std::vector<Observer*> observers;
	float alpha;
	float fi;
	float movementSpeed;
	
};

