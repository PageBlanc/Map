/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:06:46 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 15:18:18 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Map::Map() : _type("Map"), _smoothness(0), _density(0), _seed(0), _width(0), _height(0) {}

Map::Map(std::string type) : _type(type), _smoothness(0), _density(0), _seed(0), _width(0), _height(0) {}

Map::Map(std::string type, int x, int y) : _type(type), _smoothness(0), _density(0), _seed(0), _width(x), _height(y) {}

Map::Map(std::string type, int smoothness, int density, int x, int y) : _type(type), _smoothness(smoothness), _density(density), _seed(std::rand()), _width(x), _height(y) {}

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

/*-------------------------------------SETTER-------------------------------------*/

void		Map::setLand(int x, int y, Land &land)
{
	_map[x][y] = &land;
}

/*-------------------------------------PRINT-------------------------------------*/

void		Map::printMap() const
{
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t j = 0; j < _map[i].size(); j++)
			std::cout << _map[i][j]->getSymbol();
		std::cout << std::endl;
	}
}

/*-------------------------------------OPERATOR-------------------------------------*/

Map &Map::operator=(const Map &map)
{
	_map = map._map;
	return *this;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/
	
Map::~Map() {}