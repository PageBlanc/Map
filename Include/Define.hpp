/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:45:10 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 14:07:31 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
# define DEFINE_HPP

# include <vector>
# include <math.h>
# include <SDL/SDL.h>

struct Vec3 {
	float x, y, z;
	
	Vec3 operator+(const Vec3 &v) const
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}
	Vec3 operator-(const Vec3 &v) const
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}
	Vec3 operator*(float scalar) const {
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

    float dot(const Vec3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3 normalize() const
	{
	    float len = sqrt(x*x + y*y + z*z);
	    return len > 0 ? Vec3(x / len, y / len, z / len) : Vec3(0, 0, 0);
	}
	
	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

# include "Land/Land.hpp"
# include "Object/Light.hpp"

#define EXPORT 2
#define WIDTH 800
#define HEIGHT 600
#define DRAW_EDGE 0

#	define VOID    	std::string("⬛")
#	define WATER   	std::string("🟦")
#	define SAND 	std::string("🟨")
#	define PLAINS 	std::string("🟩")
#	define ICE 		std::string("⬜")
#   define MOUNTAIN std::string("⬛")
#   define HILL		std::string("🟫")


void drawCube(Vec3 position, float size, float rotationAngle, bool *drawface, Land *land, Light *light);
Vec3 rotateZ(Vec3 point, float angle);
Vec3 translate(Vec3 point, Vec3 translation);
void drawFPS(Uint32 &lastTime, int &frames, float &fps);
void drawCoordinates(Vec3 cam_pos, float cam_pitch, float cam_yaw);
void drawplane(Vec3 position, float size, float rotationAngle);
void choiseColor(Land *land);


#endif