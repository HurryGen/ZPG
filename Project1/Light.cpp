#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec4& color) : position(position), color(color)
{
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
