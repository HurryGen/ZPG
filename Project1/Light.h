#pragma once
#include "Subject.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

class Light : public Subject
{
public:
	Light(const glm::vec3& position, const glm::vec4& color);

	void attach(Observer* observer) override;
	void detach(Observer* observer) override;
	void notify() override;
	glm::vec3 getPosition();
	glm::vec4 getColor();


private:
	glm::vec3 position;  
	glm::vec4 color; 
	std::vector<Observer*> observers;
};

