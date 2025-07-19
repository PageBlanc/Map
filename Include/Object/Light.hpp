/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:13:35 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 14:01:16 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Define.hpp"

#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light
{
	private:
		Vec3 _position;
		Vec3 _direction;
		Vec3 _color;
		float _intensity;
	public:
		Light();
		Light(const Vec3& pos, const Vec3& dir, const Vec3& col, float intensity);
		Light(const Light &light);

		Vec3 getPosition() const;
		Vec3 getDirection() const;
		Vec3 getColor() const;
		
		float getIntensity() const;
		void setPosition(const Vec3& pos);
		void setDirection(const Vec3& dir);
		void setColor(const Vec3& col);
		void setIntensity(float intensity);

		float dot(const Vec3 &v) const;
		Vec3 normalize() const;
		
		Light &operator=(const Light &light);
		~Light();
};

std::ostream &operator<<(std::ostream &os, const Light &light);

#endif