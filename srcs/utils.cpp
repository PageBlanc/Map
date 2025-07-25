/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:03:06 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/25 12:31:03 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/SDL.hpp"
#include "../Include/Define.hpp"
#include "../Include/Object/Light.hpp"

// Fonction pour appliquer une rotation autour de l'axe Z
Vec3 rotateZ(Vec3 point, float angle)
{
	
	Vec3 newPoint;
	float s = sin(angle);
	float c = cos(angle);
	
	newPoint.x = point.x * c - point.y * s;
	newPoint.y = point.x * s + point.y * c;
	newPoint.z = point.z;
	return newPoint;
}

// Fonction pour appliquer une translation
Vec3 translate(Vec3 point, Vec3 translation)
{
	Vec3 newPoint;
	newPoint.x = point.x + translation.x;
	newPoint.y = point.y + translation.y;
	newPoint.z = point.z + translation.z;
	return newPoint;
}

void drawSquareEdge(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4)
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

void drawFace(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4)
{
	glBegin(GL_QUADS);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

float calculateLighting(Vec3 normal, Light *light)
{
    Vec3 lightDir = light->getDirection().normalize();
    float intensity = normal.dot(lightDir * -1.0f);

    if (intensity < 0.2f)
        intensity = 0.2f;
    if (intensity > 1.0f)
        intensity = 1.0f;
    
    return intensity;
}

void drawCube(Vec3 position, float size, float rotationAngle, bool *drawface, Land *land, Light *light)
{
	if (!land) return;
	static const int faces[6][4] =
	{
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{0, 4, 7, 3},
		{1, 5, 6, 2},
		{3, 2, 6, 7},
		{0, 1, 5, 4} 
	};

	static const Vec3 vertices[8] =
	{
		Vec3(-size, -size, -size),
		Vec3(size, -size, -size),
		Vec3(size, size, -size),
		Vec3(-size, size, -size),
		Vec3(-size, -size, size),
		Vec3(size, -size, size),
		Vec3(size, size, size),
		Vec3(-size, size, size)
	};


	static const Vec3 faceNormals[6] = {
		Vec3(0, 0, 1),
		Vec3(0, 0, -1), 
		Vec3(1, 0, 0),
		Vec3(-1, 0, 0), 
		Vec3(0, -1, 0),
		Vec3(0, 1, 0)  
	};

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	if (rotationAngle != 0.0f)
		glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	
	Vec3 BaseColor = land->getColor();
	
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
	    if (drawface && !drawface[i]) continue;

        float lighting = calculateLighting(faceNormals[i], light);
		glColor3f(lighting * BaseColor.x, lighting * BaseColor.y, lighting * BaseColor.z);
		
		for (int j = 0; j < 4; j++)
		{
			const Vec3 vertex = vertices[faces[i][j]];
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
	}
	glEnd();
	glPopMatrix();
}

void drawFPS(Uint32 &lastTime, int &frames, float &fps)
{
	char title[128];
	frames++;
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastTime >= 1000)
	{
		fps = frames * 1000.0f / (currentTime - lastTime);
		snprintf(title, sizeof(title), "Map - FPS: %.1f", fps);
		SDL_WM_SetCaption(title, NULL);
		frames = 0;
		lastTime = currentTime;
	}
}

void drawCoordinates(Vec3 cam_pos, float cam_pitch, float cam_yaw)
{
	char coordinates[256];
	snprintf(coordinates, sizeof(coordinates), 
		"Pos: (%.1f, %.1f, %.1f) Pitch: %.1f° Yaw: %.1f°", 
		cam_pos.x, cam_pos.y, cam_pos.z, cam_pitch, cam_yaw);
	
	static Uint32 lastUpdate = 0;
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastUpdate >= 100)
	{
		SDL_WM_SetCaption(coordinates, NULL);
		lastUpdate = currentTime;
	}
}