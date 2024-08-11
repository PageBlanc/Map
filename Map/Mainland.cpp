/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 11:17:54 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mainland.hpp"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "../Land/Plains.hpp"
#include "../Land/Water.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Mainland::Mainland() : Map() {}

Mainland::Mainland(std::string type, int x, int y) : Map(type, x, y)
{
	emptyMapGeneration(x, y);
	generateMap();
}

Mainland::Mainland(std::string type, int x, int y, int smoothness, int density, int seed) : Map(type, smoothness, density, seed, x, y)
{
	emptyMapGeneration(x, y);
	generateMap();
}

Mainland::Mainland(const Mainland &mainland) : Map(mainland)
{
	*this = mainland;
}

/*-------------------------------------GENERATE-------------------------------------*/

void		Mainland::emptyMapGeneration(int x, int y)
{
	if (!_map.empty())
		_map.clear();
	for (int i = 0; i < x; i++)
	{
		std::vector<Land *> line;
		for (int j = 0; j < y; j++)
			line.push_back(new Land());
		_map.push_back(line);
	}
}

int		Mainland::RecursiveNearLand(int x, int y, int width, int height, int random_value)
{
	if (x >= width || y >= height  || x < 0 || y < 0)
		return 0;
	if (nearCenter(x, y, width, height))
	{
		delete _map[x][y];
		_map[x][y] = new Plains("Plains", y, 10);
	}
	else if (nearLand(x - 1, y, width, height, random_value) || nearLand(x + 1, y, width, height, random_value) || nearLand(x, y - 1, width, height, random_value) || nearLand(x, y + 1, width, height, random_value))
	{
		delete _map[x][y];
		_map[x][y] = new Plains("Plains", y, 10);
	}
	else
	{
		delete _map[x][y];
		_map[x][y] = new Water("Water", y, 10);
	}
	if (x == width - 1)
		return RecursiveNearLand(0, y + 1, width, height, std::rand());
	return RecursiveNearLand(x + 1, y, width, height, std::rand());
}

bool		Mainland::nearLand(int x, int y, int width, int height, int random_value)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return false;
	if (_map[x][y]->getType() == "Plains" && random_value % 100 < _density)
		return true;
	return false;
}

bool		Mainland::nearCenter(int x, int y, int width, int height)
{
	int center_x = width / 2;
	int center_y = height / 2;
	int distance = sqrt(pow(center_x - x, 2) + pow(center_y - y, 2));
	if (distance < 10)
		return true;
	return false;
}

void		Mainland::generateMap()
{
    std::srand(std::time(0));
	std::cout << "Generating Mainland..." << std::endl;
	for (size_t i = 0; i < _map.size(); i++)
			RecursiveNearLand(0, 0, _map.size(), _map[i].size(), std::rand());
}

/*-------------------------------------OPERATOR-------------------------------------*/

Mainland &Mainland::operator=(const Mainland &mainland)
{
	if (this != &mainland)
	{
		_map = mainland._map;
	}
	return *this;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Mainland::~Mainland()
{
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t j = 0; j < _map[i].size(); j++)
			delete _map[i][j];
	}
	
}