/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 15:56:15 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mainland.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Mainland::Mainland() : Map() {}

Mainland::Mainland(std::vector<std::vector<Land>> map, std::string type)
	: Map(map, type, 0, 0, 0) {}

/*-------------------------------------GENERATE-------------------------------------*/

void		Mainland::generateMap()
{
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t j = 0; j < _map[i].size(); j++)
			_map[i][j] = *new Plains("Plains", 0, 0, "🟩");
	}
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