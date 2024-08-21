/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:06:46 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/21 15:55:36 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Map::Map() : _type("Map"), _smoothness(0), _density(0), _seed(0), _width(0), _height(0) {}

Map::Map(std::string type) : _type(type), _smoothness(0), _density(0), _seed(0), _width(0), _height(0)
{
	// initMap(rand() % 150 + 50, rand() % 150 + 50);
	// initNearLand();
}

Map::Map(std::string type, int x, int y) : _type(type), _smoothness(0), _density(0), _seed(0), _width(x), _height(y)
{
	// initMap(x, y);
	// initNearLand();
}

Map::Map(std::string type, int smoothness, int density, int x, int y) : _type(type), _smoothness(smoothness), _density(density), _seed(std::rand()), _width(x), _height(y)
{
	// initMap(x, y);
	// initNearLand();
}

Map::Map(Map const &map) : _type(map._type), _smoothness(map._smoothness), _density(map._density), _seed(map._seed), _width(map._width), _height(map._height)
{
	*this = map;
}
	
/*-------------------------------------GETTER-------------------------------------*/

std::vector<std::vector<Land *> >	Map::getMap() const
{
	return _map;
}

std::string	Map::getType() const
{
	return _type;
}

Land		*Map::getLand(int x, int y) const
{
	return _map[x][y];
}

int			Map::getSmoothness() const
{
	return _smoothness;
}

int			Map::getDensity() const
{
	return _density;
}

int			Map::getSeed() const
{
	return _seed;
}

std::map<Land *, std::vector<Land *> >	Map::getNearLands() const
{
	return _nearLands;
}

/*-------------------------------------SETTER-------------------------------------*/

void		Map::setLand(int x, int y, Land &land)
{
	_map[x][y] = &land;
}

void		Map::setNearLands(Land &land, std::vector<Land *> nearLands)
{
	_nearLands[&land] = nearLands;
	
}

/*-------------------------------------PRINT-------------------------------------*/

void		Map::printMap() const
{
	if (_map.size() == 0)
	{
		std::cout << "Map is empty" << std::endl;
		return;
	}
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
			std::cout << _map[i][j]->getSymbol();
		std::cout << std::endl;
	}
}

void	Map::printTopography() const
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
			std::cout << _map[i][j]->getHeight(), std::cout << ",";
		std::cout << std::endl;
	}
}


/*-------------------------------------DISPLAY-------------------------------------*/

Vec3 Map::convertIsoTo3D(float x, float y, float z) const
{
	Vec3 newPoint;
	newPoint.x = (2 * y + x) / 2;
	newPoint.y = (2 * y - x) / 2;
	newPoint.z = z;
	return newPoint;
}

void	choiseColor(Land *land)
{
	if (land->getType() == "Water")
		glColor3f(0.0f, 0.0f, 1.0f);
	else if (land->getType() == "Plains")
		glColor3f(0.0f, 1.0f, 0.0f);
	else if (land->getType() == "Sand")
		glColor3f(1.0f, 1.0f, 0.0f);
	else if (land->getType() == "Mountain")
		glColor3f(0.5f, 0.5f, 0.5f);
	else if (land->getType() == "Forest")
		glColor3f(0.0f, 0.5f, 0.0f);
	else if (land->getType() == "Desert")
		glColor3f(1.0f, 0.5f, 0.0f);
	else if (land->getType() == "Snow")
		glColor3f(1.0f, 1.0f, 1.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
}



// Fonction pour appliquer une rotation autour de l'axe Z
Vec3 rotateZ(Vec3 point, float angle) {
	
	Vec3 newPoint;
    float s = sin(angle);
    float c = cos(angle);
	
	newPoint.x = point.x * c - point.y * s;
	newPoint.y = point.x * s + point.y * c;
	newPoint.z = point.z;
	return newPoint;
}

// Fonction pour appliquer une translation
Vec3 translate(Vec3 point, Vec3 translation) {
	Vec3 newPoint;
	newPoint.x = point.x + translation.x;
	newPoint.y = point.y + translation.y;
	newPoint.z = point.z + translation.z;
	return newPoint;
}

// Fonction pour dessiner les arêtes d'un cube en isométrie en fonction des voisins
void hilightEdgeNearLand(Vec3 vertices[8], std::vector<Land *> nearLands) {
	(void) nearLands;
	//dispay all edge
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Face avant
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

	// Face arrière
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	// Face supérieure
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	// Face inférieure
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

	// Face droite
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

	// Face gauche
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

	glEnd();
}

void drawCube(Vec3 position, float size, float rotationAngle, std::vector<Land *> nearLands) {
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
	
	// Dessiner les arêtes des cubes
	(void) nearLands;
	// hilightEdgeNearLand(vertices, nearLands);
}

void Map::renderMap() const
{
	// for (size_t i = _map.size(); i-- > 0;)
	// {
	// 	for (size_t j = _map[i].size(); j-- > 0;)
	// 	{
	// 		Land *land = _map[i][j];
	// 		for (size_t k = land->getHeight(); k-- > 0;)
	// 		{
	// 			Vec3 position = { (float) i, (float) j, (float) k };
	// 			choiseColor(land);
	// 			drawCube(position, 0.5f, 0.0f, _nearLands.at(land));
	// 		}
	// 	}
	// }
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t j = 0; j < _map[i].size(); j++)
		{
			Land *land = _map[i][j];
			Vec3 position = { (float) i, (float) j, 0.0f };
			choiseColor(land);
			drawCube(position, 0.5f, 0.0f, _nearLands.at(land));
			for (int k = 0; k < land->getHeight(); k++)
			{
				Vec3 position = { (float) i, (float) j, (float) k };
				choiseColor(land);
				drawCube(position, 0.5f, 0.0f, _nearLands.at(land));
			}
		}
	}
}

void handleInput(Vec3& translation, float move_speed)
{
    const Uint8* state = SDL_GetKeyState(NULL);

    // Déplacement continu avec les touches fléchées / en fonction de la vue isometrique
	if (state[SDLK_z]) {
		translation.y -= move_speed;
		// translation.z += move_speed * cos(45.0f * M_PI / 180.0f);
	}
	if (state[SDLK_s]) {
		translation.y += move_speed;
		// translation.z -= move_speed * cos(45.0f * M_PI / 180.0f);
	}
	if (state[SDLK_q]) {
		translation.x += move_speed;
	}
	if (state[SDLK_d]) {
		translation.x -= move_speed;
	}
}


void handelMouse(Vec3& translation, float& zoom, float zoom_speed, SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
		int x, y;
		SDL_GetMouseState(&x, &y);

		float x_world = (2.0f * x / 800.0f - 1.0f) / zoom - translation.x;
		float y_world = (2.0f * y / 600.0f - 1.0f) / zoom - translation.y;

        // Convertir la position de la souris en coordonnées du monde

        if (event.button.button == SDL_BUTTON_WHEELUP) {
            // Zoom avant
            zoom += zoom_speed;

            // Ajuster la translation pour centrer le zoom sur la position de la souris
			translation.x += x_world * zoom_speed;
			translation.y += y_world * zoom_speed;
			
        }
        if (event.button.button == SDL_BUTTON_WHEELDOWN) {
            // Zoom arrière
            zoom -= zoom_speed;
            if (zoom < 0.1f) zoom = 0.1f;  // Empêcher le zoom négatif ou trop petit

            // Ajuster la translation pour centrer le zoom sur la position de la souris
			translation.x -= x_world * zoom_speed;
			translation.y -= y_world * zoom_speed;
        }
    }
}


void Map::visualDisplay() const
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_RESIZABLE);
    if (!screen)
    {
        std::cerr << "Impossible d'initialiser la SDL" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Variables pour gérer le zoom et le déplacement
    float zoom = 0.5f;  // Moins zoomé initialement
    float move_speed = _map.size() / 500.0f;  // Vitesse de déplacement ajustée
    float zoom_speed = 0.05f; // Vitesse de zoom réduite
    SDL_Event event;
    Vec3 translation;
    translation.x = 0.0f;
    translation.y = 0.0f;
    translation.z = -10.0f;  // Position initiale en Z pour éloigner la caméra

    bool running = true;

    while (running)
    {
        // Gestion des événements
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    handleInput(translation, move_speed);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    handelMouse(translation, zoom, zoom_speed, event);
                    break;
                default:
                    break;
            }
        }

        // Déplacement continu
        handleInput(translation, move_speed);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Configuration de la projection en perspective
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, 800.0f / 600.0f, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Appliquer les translations pour déplacer la caméra
        glTranslatef(translation.x, translation.y , translation.z);

        // Appliquer la vue isométrique avec des rotatef
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  // Tourner de 45° sur l'axe Z
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);  // Incliner de 35.264° sur l'axe X
		glRotatef(30.0f, 0.0f, 1.0f, 0.0f);  // Incliner de 35.264° sur l'axe X
		
		
        // Appliquer le zoom
        glScalef(zoom, zoom, zoom);

        // Rendu de la carte
        renderMap();

        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
}







void	Map::initDisplay() const
{
	
}

/*-------------------------------------OPERATOR-------------------------------------*/

Map &Map::operator=(const Map &map)
{
	_map = map._map;
	return *this;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/
	
Map::~Map() {}