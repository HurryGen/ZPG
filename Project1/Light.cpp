#include "Light.h"

#include "Camera.h"

Light::Light(const glm::vec3& position, const glm::vec4& color) : position(position), color(color)
{
	mode = 0;
}

Light::Light(const glm::vec3& position, const glm::vec4& color, glm::vec3 lightDirection, float cutoff)
{
	this->position = position;
	this->color = color;
	this->lightDirection = lightDirection;
	this->cutoff = cutoff;
	this->mode = 1;
}

void Light::attach(Observer* observer)
{
	observers.push_back(observer);
}

void Light::detach(Observer* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notify()
{
	for (auto observer : observers) {
		observer->update(this);
	}
}

glm::vec3 Light::getPosition()
{
	return position;
}

glm::vec4 Light::getColor()
{
	return color;
}

void Light::update(Subject* subject)
{
	if(auto camera = dynamic_cast<Camera*>(subject))
	{
		lightDirection = camera->getTarget();
		position = camera->getPosition();
	}
	notify();
}

int Light::getMode()
{
	return mode;
}

float Light::getCutoff()
{
	return cutoff;
}

glm::vec3 Light::getLightDirection()
{
	return lightDirection;
}
