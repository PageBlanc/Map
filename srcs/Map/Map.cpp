/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:06:46 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/20 09:54:36 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Map.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Map::Map() :  _type("Map"), _smoothness(0), _density(0), _seed(rand()), _width(0), _height(0), _depth(0)
{
	_light = new Light();
	_nearLands = std::map<Land *, std::vector<Land *> >();
}

Map::Map(std::string type, int x, int y) : _type(type), _smoothness(0), _density(0), _seed(rand()), _width(x), _height(y), _depth(0)
{
	_light = new Light();
	_nearLands = std::map<Land *, std::vector<Land *> >();
}

Map::Map(const Map &map) : _type(map._type), _smoothness(map._smoothness), _density(map._density), _seed(map._seed), _width(map._width), _height(map._height), _depth(map._depth), _light(map._light)
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

void Map::renderMap(Vec3 cameraPos) const
{
	(void)cameraPos;
	for (size_t i = _map.size(); i-- > 0;)
	{
		for (size_t j = _map[i].size(); j-- > 0;)
		{
			Land *land = _map[i][j];
			for (size_t k = land->getHeight(); k-- > 0;)
			{
				Vec3 position = Vec3((float)i, (float)j, (float)k);
				Vec3 basecolor = land->getColor();
				glColor3f(basecolor.x, basecolor.y, basecolor.z);
				drawCube(position, 1.0f, 0.0f, NULL, land, _light);
			}
		}
	}
}

/*-------------------------------------OPERATOR-------------------------------------*/

Map &Map::operator=(const Map &map)
{
	_map = map._map;
	return *this;
}

bool Map::operator==(const Map &map) const
{
	return _type == map._type && _width == map._width && _height == map._height;
}

bool  Map::operator!=(const Map &map) const
{
	return !(*this == map);
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/
Map::~Map()
{
	delete _light;
}