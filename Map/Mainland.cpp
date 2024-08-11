/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 17:48:28 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mainland.hpp"
#include "../Land/Plains.hpp"
#include "../Land/Water.hpp"
#include "../Land/Sand.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Mainland::Mainland() : Map() {}

Mainland::Mainland(std::string type, int x, int y) : Map(type, x, y)
{
	emptyMapGeneration(x, y);
	generateMap();
}

Mainland::Mainland(std::string type, int x, int y, int smoothness, int density) : Map(type, smoothness, density, x, y)
{
	emptyMapGeneration(x, y);
	generateMap();
}

Mainland::Mainland(const Mainland &mainland) : Map(mainland)
{
	*this = mainland;
}

/*-------------------------------------GENERATE-------------------------------------*/

int			Mainland::countNearSameLand(int x, int y, int width, std::string type, int random_value)
{
	int count = 0;
	if (x - 1 >= 0 && _map[x - 1][y]->getType() == type && random_value % 100 < 57)
		count++;
	if (x + 1 < width && _map[x + 1][y]->getType() == type && random_value % 100 < 57)
		count++;
	if (y - 1 >= 0 && _map[x][y - 1]->getType() == type && random_value % 100 < 57)
		count++;
	if (y + 1 < _height && _map[x][y + 1]->getType() == type && random_value % 100 < 57)
		count++;
	if (x - 1 >= 0 && y - 1 >= 0 && _map[x - 1][y - 1]->getType() == type && random_value % 100 < 57)
		count++;
	if (x + 1 < width && y + 1 < _height && _map[x + 1][y + 1]->getType() == type && random_value % 100 < 57)
		count++;
	if (x - 1 >= 0 && y + 1 < _height && _map[x - 1][y + 1]->getType() == type && random_value % 100 < 57)
		count++;
	if (x + 1 < width && y - 1 >= 0 && _map[x + 1][y - 1]->getType() == type && random_value % 100 < 57)
		count++;
	return count;
}

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
	if (countNearSameLand(x, y, width, "Plains", random_value) > 3)
		return true;
	return false;
}

bool		Mainland::nearCenter(int x, int y, int width, int height)
{
	int center_x = width / 2;
	int center_y = height / 2;
	int distance = sqrt(pow(center_x - x, 2) + pow(center_y - y, 2));
	if (distance < _width / 4)
		return true;
	return false;
}

int		Mainland::fillLand(int x, int y, int width, int height, int random_value)
{
	if (x >= width || y >= height || x < 0 || y < 0)
		return 0;
	if (countNearSameLand(x, y, width, "Plains", random_value) > 3)
	{
		delete _map[x][y];
		_map[x][y] = new Plains("Plains", y, 10);
	}
	if (x == width - 1)
		return fillLand(0, y + 1, width, height, std::rand());
	return fillLand(x + 1, y, width, height, std::rand());
}

int			Mainland::PutSand(int x, int y, int width, int height)
{
	if (x >= width || y >= height || x < 0 || y < 0)
		return 0;
	if (_map[x][y]->getType() != "Water" && (countNearSameLand(x, y, width, "Water", 100) > 1 || (countNearSameLand(x, y, width, "Sand", 100) > 0 && countNearSameLand(x, y, width, "Water", 100) > 0)))
	{
		delete _map[x][y];
		_map[x][y] = new Sand("Sand", y, 10);
	}
	if (x == width - 1)
		return PutSand(0, y + 1, width, height);
	return PutSand(x + 1, y, width, height);
}

void		Mainland::generateMap()
{
    std::srand(std::time(0));
	std::cout << "Generating Mainland..." << std::endl;
	for (size_t i = 0; i < _map.size(); i++)
			RecursiveNearLand(0, 0, _map.size(), _map[i].size(), std::rand());
	for (size_t i = 0; i < 8; i++)
		fillLand(0, 0, _map.size(), _map[0].size(), std::rand());
	PutSand(0, 0, _map.size(), _map[0].size());
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