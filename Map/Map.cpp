/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:06:46 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/18 12:32:52 by pageblanche      ###   ########.fr       */
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

Point Map::convertIsoTo2D(float x, float y) const
{
    Point point;
    point.x = (x - y) * 0.5f;
    point.y = (x + y) * 0.5f;
    return point;
}

void Map::renderMap() const
{
    float tileWidth, tileHeight;

    for (size_t i = 0; i < _map.size(); ++i) {
        for (size_t j = 0; j < _map[i].size(); ++j) {
            Land* land = _map[i][j];
            if (land)
            {
                tileWidth = land->getSize() * 0.5f;
                tileHeight = land->getSize() * 0.5f;

                // Définir la couleur en fonction du type de terrain
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

                // Convertir les coordonnées en isométrique
                Point screen = convertIsoTo2D(i * tileWidth, j * tileHeight);
                screen.x *= 1.5f;
                screen.y *= 1.5f;

                // Dessiner le polygone représentant la tuile
                glBegin(GL_POLYGON);

				glVertex2f(screen.x, screen.y + tileHeight);
				glVertex2f(screen.x + tileWidth, screen.y);
				glVertex2f(screen.x, screen.y - tileHeight);
				glVertex2f(screen.x - tileWidth, screen.y);
				
				glEnd();
            }
        }
    }
}

void handleInput(int &x_offset, int &y_offset, float &zoom, int move_speed, float zoom_speed)
{
    const Uint8* keys = SDL_GetKeyState(NULL);
    if (keys[SDLK_s])
        y_offset += move_speed;
    if (keys[SDLK_z])
        y_offset -= move_speed;
    if (keys[SDLK_q])
        x_offset += move_speed;
    if (keys[SDLK_d])
        x_offset -= move_speed;
    if (keys[SDLK_KP_PLUS] && zoom < 5.0f)
        zoom += zoom_speed;
    if (keys[SDLK_KP_MINUS] && zoom > 0.2f)
        zoom -= zoom_speed;
}

void Map::visualDisplay() const
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);
    if (!screen)
    {
        std::cerr << "Impossible d'initialiser la SDL" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Configuration de la matrice de projection pour une projection orthographique
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float mapWidth = _map.size();
    float mapHeight = _map[0].size();
    float aspectRatio = 800.0f / 600.0f;
    float halfWidth = (mapWidth * 1.5f) / 2.0f;
    float halfHeight = (mapHeight * 1.5f) / 2.0f;

    glOrtho(-halfWidth, halfWidth, -halfHeight / aspectRatio, halfHeight / aspectRatio, -100.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Variables pour gérer le zoom et le déplacement
    float zoom = 0.2f;
    int x_offset = 0, y_offset = 0;
    int move_speed = _width / 10; // Vitesse de déplacement
    float zoom_speed = 0.1f; // Vitesse de zoom
    SDL_Event event;

    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                running = false;
            handleInput(x_offset, y_offset, zoom, move_speed, zoom_speed);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Appliquer les translations pour déplacer la vue
        glTranslatef(x_offset, y_offset, 0);

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