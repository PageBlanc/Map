/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:45:10 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/17 22:20:54 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
# define DEFINE_HPP

# include <vector>
#include <SDL/SDL.h>

struct Vec3 {
	float x, y, z;
};

#define EXPORT 2
#define WIDTH 800
#define HEIGHT 600
#define PI 3.1415
#define DRAW_EDGE 0

#	define VOID    	std::string("⬛")
#	define WATER   	std::string("🟦")
#	define SAND 	std::string("🟨")
#	define PLAINS 	std::string("🟩")
#	define ICE 		std::string("⬜")
#   define MOUNTAIN std::string("⬛")
#   define HILL		std::string("🟫")


void drawCube(Vec3 position, float size, float rotationAngle);
Vec3 rotateZ(Vec3 point, float angle);
Vec3 translate(Vec3 point, Vec3 translation);
void drawFPS(Uint32 &lastTime, int &frames, float &fps);
void drawplane(Vec3 position, float size, float rotationAngle);

#endif