/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 16:44:52 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mainland.hpp"
#include "../Land/Plains.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Mainland::Mainland() : Map() {}

Mainland::Mainland(std::string type, int x, int y) : Map(type) 
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

void		Mainland::generateMap(int x, int y)
{
	if (!_map.empty())
		_map.clear();
	for (int i = 0; i < x; i++)
	{
		std::vector<Land &> line;
		for (int j = 0; j < y; j++)
		{
			Land &land = new Plains();
			line.push_back(land);
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
			delete &_map[i][j];
	}
}