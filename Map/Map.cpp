/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:06:46 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/17 20:45:30 by pageblanche      ###   ########.fr       */
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

void Map::renderMap() const
{
    float tileWidth = 1.0f;  // Largeur de chaque cellule
    float tileHeight = 0.5f; // Hauteur de chaque cellule

    // Centre la carte dans la vue
    float mapOffsetX = _map.size() * tileWidth / 2.0f;
    float mapOffsetY = _map[0].size() * tileHeight / 2.0f;

    for (size_t i = 0; i < _map.size(); ++i) {
        for (size_t j = 0; j < _map[i].size(); ++j) {
            Land* land = _map[i][j];
            if (land)
            {
                // Conversion des coordonnées de la grille en coordonnées isométriques
                float x = (i - j) * tileWidth / 2.0f - mapOffsetX;
                float y = (i + j) * tileHeight / 2.0f - mapOffsetY;
                float z = land->getHeight() * 1.0f;

                glPushMatrix();
                glTranslatef(x, y, z);

                // Choisir la couleur en fonction du type de terrain
                if (land->getType() == "Water") {
                    glColor3f(0.0f, 0.0f, 1.0f); // Bleu pour l'eau
                } else if (land->getType() == "Sand") {
                    glColor3f(1.0f, 1.0f, 0.0f); // Jaune pour le sable
                } else if (land->getType() == "Plains") {
                    glColor3f(0.0f, 1.0f, 0.0f); // Vert pour les plaines
                } else {
                    glColor3f(1.0f, 1.0f, 1.0f); // Blanc pour les autres types
                }

                // Dessiner un cube (cellule de la carte)
                glBegin(GL_QUADS);

                // Faces du cube
                // Face avant
                glVertex3f(-0.5f, -0.5f, -0.5f);
                glVertex3f(0.5f, -0.5f, -0.5f);
                glVertex3f(0.5f, 0.5f, -0.5f);
                glVertex3f(-0.5f, 0.5f, -0.5f);

                // Face arrière
                glVertex3f(-0.5f, -0.5f, 0.5f);
                glVertex3f(0.5f, -0.5f, 0.5f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(-0.5f, 0.5f, 0.5f);

                // Face gauche
                glVertex3f(-0.5f, -0.5f, -0.5f);
                glVertex3f(-0.5f, -0.5f, 0.5f);
                glVertex3f(-0.5f, 0.5f, 0.5f);
                glVertex3f(-0.5f, 0.5f, -0.5f);

                // Face droite
                glVertex3f(0.5f, -0.5f, -0.5f);
                glVertex3f(0.5f, -0.5f, 0.5f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(0.5f, 0.5f, -0.5f);

                // Face supérieure
                glVertex3f(-0.5f, 0.5f, -0.5f);
                glVertex3f(0.5f, 0.5f, -0.5f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(-0.5f, 0.5f, 0.5f);

                // Face inférieure
                glVertex3f(-0.5f, -0.5f, -0.5f);
                glVertex3f(0.5f, -0.5f, -0.5f);
                glVertex3f(0.5f, -0.5f, 0.5f);
                glVertex3f(-0.5f, -0.5f, 0.5f);

                glEnd();

                glPopMatrix();
            }
        }
    }
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

    // Appliquer la transformation isométrique (rotation)
    glRotatef(35.264f, 1, 0, 0); // Rotation de 35.264° autour de l'axe X
    glRotatef(45.0f, 0, 1, 0);   // Rotation de 45° autour de l'axe Y

    bool running = true;

    // Variables pour gérer le zoom et le déplacement
    float zoom = 1.0f;
    int x_offset = 0, y_offset = 0;
    int move_speed = 10;     // Vitesse de déplacement
    float zoom_speed = 0.1f; // Vitesse de zoom
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                running = false;

            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_z: // Z - Déplacement vers le haut
                    y_offset -= move_speed;
                    break;
                case SDLK_s: // S - Déplacement vers le bas
                    y_offset += move_speed;
                    break;
                case SDLK_d: // Q - Déplacement vers la gauche
                    x_offset -= move_speed;
                    break;
                case SDLK_q: // D - Déplacement vers la droite
                    x_offset += move_speed;
                    break;
                case SDLK_p: // + - Zoomer
                    zoom += zoom_speed;
                    break;
                case SDLK_m: // - - Dézoomer
                    zoom -= zoom_speed;
                    if (zoom < 0.1f)
                        zoom = 0.1f; // Empêcher le zoom négatif
                    break;
                case SDLK_ESCAPE: // Quitter avec Echap
                    running = false;
                    break;
                default:
                    break;
                }
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Appliquer le zoom
        glScalef(zoom, zoom, zoom);

        // Appliquer les translations pour déplacer la vue
        glTranslatef(x_offset * 0.1f, y_offset * 0.1f, 0);

        // Rendu de la carte
        renderMap();

        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
}



void	Map::initDisplay() const
{
	SDL_Init(SDL_INIT_VIDEO);
	
}

/*-------------------------------------OPERATOR-------------------------------------*/

Map &Map::operator=(const Map &map)
{
	_map = map._map;
	return *this;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/
	
Map::~Map() {}