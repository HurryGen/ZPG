#pragma once
#include "Subject.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

class Light : public Subject, public Observer
{
public:
	Light(const glm::vec3& position, const glm::vec4& color);
	Light(const glm::vec3& position, const glm::vec4& color, glm::vec3 lightDirection, float cutoff);
	Light(const glm::vec4& color, glm::vec3 lightDirection);

	void attach(Observer* observer) override;
	void detach(Observer* observer) override;
	void notify() override;
	glm::vec3 getPosition();
	glm::vec4 getColor();
	void update(Subject* subject) override;
	int getMode();
	float getCutoff();
	glm::vec3 getLightDirection();
	void setId(int id);
	int getId();

	
protected:
	glm::vec3 position;  
	glm::vec4 color; 
	std::vector<Observer*> observers;
	glm::vec3 lightDirection;
	float cutoff;
	int mode;
	int id = -1;
};

