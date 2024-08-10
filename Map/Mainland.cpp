/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 23:40:48 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mainland.hpp"
#include <ctime>
#include <cstdlib>
#include "../Land/Plains.hpp"

#define WATER std::string("🟦")
#define PLAINS std::string("🟩")
#define VOID std::string("⬛")

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Mainland::Mainland() : Map() {}

Mainland::Mainland(std::string type, int x, int y) : Map(type, x, y)
{
	generateMap(x, y);
}

Mainland::Mainland(std::string type, int x, int y, int smoothness, int density, int seed) : Map(type, smoothness, density, seed)
{
	generateMap(x, y);
}

Mainland::Mainland(const Mainland &mainland) : Map(mainland)
{
	*this = mainland;
}

/*-------------------------------------GENERATE-------------------------------------*/

bool		Mainland::nearLand(int x, int y, int width, int height, int random_value)
{
	(void)random_value;
	if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
		return false;
	return true;

}

void		Mainland::generateMap(int x, int y)
{
	if (!_map.empty())
		_map.clear();
    std::srand(std::time(0));
	for (int i = 0; i < x; i++)
	{
		std::vector<Land *> line;
		for (int j = 0; j < y; j++)
		{	
			if (nearLand(i, j, x, y, std::rand() % 100))
				line.push_back(new Plains("Plains", j, 0, PLAINS));
			else
				line.push_back(new Plains("Water", j, 0, WATER));
		}
		_map.push_back(line);
	}
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