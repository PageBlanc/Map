/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:03:06 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/18 13:45:12 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/SDL.hpp"

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

void drawCube(Vec3 position, float size, float rotationAngle)
{
	// Définir les sommets du cube en iso
	Vec3 vertices[8] = {
		{ -size, -size, -size },
		{  size, -size, -size },
		{  size,  size, -size },
		{ -size,  size, -size },
		{ -size, -size,  size },
		{  size, -size,  size },
		{  size,  size,  size },
		{ -size,  size,  size }
	};

	// Appliquer une rotation autour de l'axe Z
	for (int i = 0; i < 8; i++) {
		vertices[i] = rotateZ(vertices[i], rotationAngle);
	}

	// Appliquer une translation
	for (int i = 0; i < 8; i++) {
		vertices[i] = translate(vertices[i], position);
	}
	
	//dessiner les cubes
	glBegin(GL_QUADS);
	
	// Face avant
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	// Face arrière
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	// Face supérieure
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	// Face inférieure
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	// Face droite
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	// Face gauche
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	glEnd();

	if (DRAW_EDGE)
	{
		// Dessiner les arêtes du cube
		glColor3f(1.0f, 1.0f, 1.0f); // Couleur des arêtes
		drawSquareEdge(vertices[0], vertices[1], vertices[2], vertices[3]);
		drawSquareEdge(vertices[4], vertices[5], vertices[6], vertices[7]);
		drawSquareEdge(vertices[0], vertices[4], vertices[5], vertices[1]);
		drawSquareEdge(vertices[2], vertices[6], vertices[7], vertices[3]);
		drawSquareEdge(vertices[0], vertices[3], vertices[7], vertices[4]);
		drawSquareEdge(vertices[1], vertices[2], vertices[6], vertices[5]);
	}
}

void drawplane(Vec3 position, float width, float height)
{
	Vec3 vertices[4] = {
		{ -width / 2, -height / 2, 0 },
		{  width / 2, -height / 2, 0 },
		{  width / 2,  height / 2, 0 },
		{ -width / 2,  height / 2, 0 }
	};

	for (int i = 0; i < 4; i++) {
		vertices[i] = translate(vertices[i], position);
	}

	glBegin(GL_QUADS);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glEnd();
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