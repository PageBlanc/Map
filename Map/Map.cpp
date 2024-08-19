/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:06:46 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/18 17:42:32 by pageblanche      ###   ########.fr       */
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

Cube Map::convertIsoTo3D(float x, float y, float z) const
{
	Cube cube;
	cube.x = (2 * y + x) / 2;
	cube.y = (2 * y - x) / 2;
	cube.z = z;
	return cube;
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

void	DrawCube3D(Cube cube)
{
	glBegin(GL_QUADS);
	
	// Face avant
	glVertex3f(-cube.x, -cube.y,  cube.z);
	glVertex3f( cube.x, -cube.y,  cube.z);
	glVertex3f( cube.x,  cube.y,  cube.z);
	glVertex3f(-cube.x,  cube.y,  cube.z);
	
	// Face arrière
	glVertex3f(-cube.x, -cube.y, -cube.z);
	glVertex3f(-cube.x,  cube.y, -cube.z);
	glVertex3f( cube.x,  cube.y, -cube.z);
	glVertex3f( cube.x, -cube.y, -cube.z);

	// Face supérieure
	glVertex3f(-cube.x,  cube.y, -cube.z);
	glVertex3f(-cube.x,  cube.y,  cube.z);
	glVertex3f( cube.x,  cube.y,  cube.z);
	glVertex3f( cube.x,  cube.y, -cube.z);

	// Face inférieure
	glVertex3f(-cube.x, -cube.y, -cube.z);
	glVertex3f( cube.x, -cube.y, -cube.z);
	glVertex3f( cube.x, -cube.y,  cube.z);
	glVertex3f(-cube.x, -cube.y,  cube.z);

	// Face droite
	glVertex3f( cube.x, -cube.y, -cube.z);
	glVertex3f( cube.x,  cube.y, -cube.z);
	glVertex3f( cube.x,  cube.y,  cube.z);
	glVertex3f( cube.x, -cube.y,  cube.z);

	// Face gauche
	glVertex3f(-cube.x, -cube.y, -cube.z);
	glVertex3f(-cube.x, -cube.y,  cube.z);
	glVertex3f(-cube.x,  cube.y,  cube.z);
	glVertex3f(-cube.x,  cube.y, -cube.z);

	glEnd();
	
}

void Map::renderMap() const
{
    // float tileWidth, tileHeight, titleDeep;

	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t j = 0; j < _map[i].size(); j++)
		{
			glPushMatrix();
			glTranslatef(i * 1.5f, 0.0f, j * 1.5f);
			choiseColor(_map[i][j]);
			for (int k = 0; k < _map[i][j]->getHeight(); k++)
			{
				glTranslatef(0.0f, 1.5f, 0.0f);
				Cube cube = convertIsoTo3D(1.5f, 1.5f, 1.5f);
				DrawCube3D(cube);
			}
			glPopMatrix();
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
    if (keys[SDLK_KP_MINUS] && zoom > 0.19f)
        zoom -= zoom_speed;
}

void	handelMouse(int &x_offset, int &y_offset, float &zoom, int move_speed, float zoom_speed)
{
	(void)move_speed;
	(void)x_offset;
	(void)y_offset;

	
	int x, y;
	SDL_GetMouseState(&x, &y);
	//gestion du zoom avec la molette
	
	if (SDL_BUTTON(SDL_BUTTON_WHEELUP) && zoom < 5.0f)
	{
		zoom += zoom_speed;
		std::cout << "zoom : " << zoom << std::endl;
	}
	if (SDL_BUTTON(SDL_BUTTON_WHEELDOWN) && zoom > 0.19f)
		zoom -= zoom_speed;
}

void	Drawmulticube()
{
	glBegin(GL_QUADS);
    
    // Face avant
    glColor3f(1.0f, 0.0f, 0.0f); // Rouge
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    // Face arrière
    glColor3f(0.0f, 1.0f, 0.0f); // Vert
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Face supérieure
    glColor3f(0.0f, 0.0f, 1.0f); // Bleu
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Face inférieure
    glColor3f(1.0f, 1.0f, 0.0f); // Jaune
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Face droite
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Face gauche
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    
    glEnd();
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

    // Configuration de la matrice de projection pour une projection orthographique
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float mapWidth = _map.size();
    float mapHeight = _map[0].size();
    float aspectRatio  = 800.0f / 600.0f;
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
		
		//gestion des evenements && souris
		while (SDL_PollEvent(&event))
		{
			// escape handel
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					handleInput(x_offset, y_offset, zoom, move_speed, zoom_speed);
					break;
				case SDL_MOUSEBUTTONDOWN:
					handelMouse(x_offset, y_offset, zoom, move_speed, zoom_speed);
					break;
				default:
					break;
			}
		}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

		gluLookAt(2.0, 2.0, 2.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
        // Appliquer les translations pour déplacer la vue isometrique
		glTranslatef(x_offset, y_offset, 1.5f);

        // Appliquer le zoom
        glScalef(zoom, zoom, zoom);
		

		// faire un plan 3D de 10 par 10 par 10 constituer de cube

		// for (int r = 0; r < 10; r++)
		// {
		// 	for (int i = 0; i < 10; i++)
		// 	{
		// 		for (int j = 0; j < 10; j++)
		// 		{
		// 			glMatrixMode(GL_MODELVIEW);
					
		// 			glPushMatrix();
		// 			glTranslatef(i * 1.5f, 0.0f, j * 1.5f);
		// 			for (int k = 0; k < 10; k++)
		// 			{
		// 				glTranslatef(0.0f, 1.5f, 0.0f);
		// 				Drawmulticube();
		// 			}
		// 			glPopMatrix();
					
		// 		}
		// 	}
		// }
				

        // Rendu de la carte
        renderMap();

		//afficher les arete un cube en 3D en isometrique
		

		
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