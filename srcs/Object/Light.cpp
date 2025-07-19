/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:13:56 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 13:59:27 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Object/Light.hpp"

Light::Light()
{
	_position = Vec3(-0.3f, 0.5f, -0.3f);
	_direction = Vec3(1.0f, 1.0f, 2.0f);
	_color = Vec3(1.0f, 1.0f, 1.0f);
	_intensity = 1.0f;
}

Light::Light(const Vec3& pos, const Vec3& dir, const Vec3& col, float intensity)
{
	_position = pos;
	_direction = dir;
	_color = col;
	_intensity = intensity;
}

Light::Light(const Light &light)
{
	*this = light;
}

Vec3 Light::getPosition() const
{
	return _position;
}

Vec3 Light::getDirection() const
{
	return _direction;
}

Vec3 Light::getColor() const
{
	return _color;
}

float Light::getIntensity() const
{
	return _intensity;
}

void Light::setPosition(const Vec3& pos)
{
	_position = pos;
}

void Light::setDirection(const Vec3& dir)
{
	_direction = dir;
}

void Light::setColor(const Vec3& col)
{
	_color = col;
}

void Light::setIntensity(float intensity)
{
	_intensity = intensity;
}

float Light::dot(const Vec3 &v) const
{
	return _direction.x * v.x + _direction.y * v.y + _direction.z * v.z;
}

Vec3 Light::normalize() const
{
	Vec3 normalized;
	float length = sqrt(_direction.x * _direction.x + _direction.y * _direction.y + _direction.z * _direction.z);
	if (length == 0.0f)
	{
		normalized.x = 0.0f;
		normalized.y = 0.0f;
		normalized.z = 0.0f;
	}
	else
	{
		normalized.x = _direction.x / length;
		normalized.y = _direction.y / length;
		normalized.z = _direction.z / length;
	}
	return normalized;
}

Light &Light::operator=(const Light &light)
{
	if (this != &light)
	{
		_position = light._position;
		_direction = light._direction;
		_color = light._color;
		_intensity = light._intensity;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Light &light)
{
	os << "Light Position: (" << light.getPosition().x << ", " << light.getPosition().y << ", " << light.getPosition().z << ") "
	   << "Direction: (" << light.getDirection().x << ", " << light.getDirection().y << ", " << light.getDirection().z << ") "
	   << "Color: (" << light.getColor().x << ", " << light.getColor().y << ", " << light.getColor().z << ") "
	   << "Intensity: " << light.getIntensity();
	return os;
}

Light::~Light() {}