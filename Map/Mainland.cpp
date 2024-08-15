/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/15 17:06:14 by pageblanche      ###   ########.fr       */
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
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i < 0 || j < 0 || i >= width || j >= _height)
				continue;
			if (_map[i][j]->getType() == type && random_value % 100 < 57)
				count++;
		}
	}
	return count;
}

void		PrintNearland(std::map<Land *, std::vector<Land *> > nearLands)
{
	for (std::map<Land *, std::vector<Land *> >::iterator it = nearLands.begin(); it != nearLands.end(); it++)
	{
		std::cout << "Land : " << it->first->getType() << std::endl;
		std::cout << "Near Lands : " << std::endl;
		std::cout << it->second[0]->getType() << std::endl;
		for (size_t i = 0; i < it->second.size(); i++)
		{
			std::cout << it->second[i]->getType() << std::endl;
		}
	}
}

void		Mainland::setAllNearLands()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			std::vector<Land *> nearLands;
			if (i - 1 >= 0)
				nearLands.push_back(_map[i - 1][j]);
			if (i + 1 < _width)
				nearLands.push_back(_map[i + 1][j]);
			if (j - 1 >= 0)
				nearLands.push_back(_map[i][j - 1]);
			if (j + 1 < _height)
				nearLands.push_back(_map[i][j + 1]);
			if (i - 1 >= 0 && j - 1 >= 0)
				nearLands.push_back(_map[i - 1][j - 1]);
			if (i + 1 < _width && j + 1 < _height)
				nearLands.push_back(_map[i + 1][j + 1]);
			if (i - 1 >= 0 && j + 1 < _height)
				nearLands.push_back(_map[i - 1][j + 1]);
			if (i + 1 < _width && j - 1 >= 0)
				nearLands.push_back(_map[i + 1][j - 1]);
			setNearLands(*_map[i][j], nearLands);
		}
	}
}

void		Mainland::emptyMapGeneration(int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		std::vector<Land *> line;
		for (int j = 0; j < y; j++)
		{
			Land *land;
			if (nearCenter(i, j, x, y))
				land = new Plains("Plains", j, 10);
			else
				land = new Water("Water", j, 10);
			line.push_back(land);
		}
		_map.push_back(line);
	}
}

int		Mainland::RecursiveNearLand(int x, int y, int width, int height, int random_value)
{
	if (x >= width || y >= height  || x < 0 || y < 0)
		return 0;
	if (!nearCenter(x, y, width, height))
	{
		if (nearLand(x - 1, y, width, height, random_value) || nearLand(x + 1, y, width, height, random_value) || nearLand(x, y - 1, width, height, random_value) || nearLand(x, y + 1, width, height, random_value))
		{
			delete _map[x][y];
			_map[x][y] = new Plains("Plains", y, 10);
		}
		else
		{
			delete _map[x][y];
			_map[x][y] = new Water("Water", y, 10);
		}
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
	int distance = std::sqrt(std::pow(center_x - x, 2) + std::pow(center_y - y, 2));
	if (distance < width / 4)
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
	if (_map[x][y]->getType() != "Water" && (countNearSameLand(x, y, width, "Water", 100) > 0))
	{
		delete _map[x][y];
		_map[x][y] = new Sand("Sand", y, 10);
	}
	if (x == width - 1)
		return PutSand(0, y + 1, width, height);
	return PutSand(x + 1, y, width, height);
}

void		Mainland::fillPound()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_map[i][j]->getType() == "Water" && countNearSameLand(i, j, _width, "Water", 100) < 1)
			{
				delete _map[i][j];
				_map[i][j] = new Plains("Plains", j, 10);
			}
		}
	}
}

void		Mainland::setHeight()
{
	
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_map[i][j]->getType() == "Water")
				_map[i][j]->setHeight(0);
			else if (_map[i][j]->getType() == "Sand")
				_map[i][j]->setHeight(1);
			else if (_map[i][j]->getType() == "Plains")
			{
				if (i == 0)
					continue;
				int random_value = std::rand() % 5 + 1;
				if (random_value == 3)
					_map[i][j]->setHeight(rand() % random_value * 10);
				else
					_map[i][j]->setHeight(rand() % 15);
				if (_map[i][j]->getHeight() < 2)
					_map[i][j]->setHeight(2);
			}
		}
	}

}

int			Mainland::averageHeight(int x, int y)
{
	int average = 0;
	int count = 0;

	// PrintNearland(_nearLands);
	for (size_t i = 0; i < _nearLands[_map[x][y]].size(); i++)
	{
		average += _nearLands[_map[x][y]][i]->getHeight();
		count++;
	}
	if (count == 0)
		return 0;
	return average / count;
}

void		Mainland::smoothingHeight()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_map[i][j]->getType() == "Plains")
			{
				int average = averageHeight(i, j);
				_map[i][j]->setHeight(average);
			}
		}
	}
}




void		Mainland::smoothPartofMap(int x, int y)
{
	if (x >= _width || y >= _height || x < 0 || y < 0)
		return;
	if (_map[x][y]->getType() == "Plains")
	{
		int average = averageHeight(x, y);
		_map[x][y]->setHeight(average);
	}
	if (x == _width - 1)
		smoothPartofMap(0, y + 1);
	else
		smoothPartofMap(x + 1, y);
}


int			Mainland::maxHeight(int x, int y)
{
	int max = 0;
	for (size_t i = 0; i < _nearLands[_map[x][y]].size(); i++)
	{
		if (_nearLands[_map[x][y]][i]->getHeight() > max)
			max = _nearLands[_map[x][y]][i]->getHeight();
	}
	return max;
}

int			Mainland::countMaxHeight(int x, int y, int random_value)
{
	int count = 0;
	int max = maxHeight(x, y);
	for (size_t i = 0; i < _nearLands[_map[x][y]].size(); i++)
	{
		if (_nearLands[_map[x][y]][i]->getHeight() == max && random_value % 100 < 57)
			count++;
	}
	return count;
}


void		Mainland::fillHeight(int random_value)
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_map[i][j]->getType() == "Plains")
			{
				if (countMaxHeight(i, j, random_value) > 2)
					_map[i][j]->setHeight(maxHeight(i, j));
			}
		}
	}
}

void		Mainland::generateMap()
{
    std::srand(std::time(0));
	if (EXPORT == 0)
		std::cout << "Generating Mainland..." << std::endl;
	for (int i = 0; i < _width - (rand() % _width * 0.7); i++)
			RecursiveNearLand(0, 0, _width, _height, std::rand());
	for (int i = 0; i < 5; i++)
		fillLand(0, 0, _width, _map[0].size(), std::rand());
	fillPound();
	PutSand(0, 0, _width, _map[0].size());
	setHeight();
	setAllNearLands();
	for (int i = 0; i < _smoothness; i++)
		smoothingHeight();
	for (int i = 0; i < _smoothness * 2; i++)
		smoothPartofMap(rand() % _width, rand() % _height);
	fillHeight(rand());
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
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
			delete _map[i][j];
	}
}