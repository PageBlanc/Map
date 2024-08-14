/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/14 16:54:15 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.hpp"
#include "Land/Plains.hpp"
#include "Land/Land.hpp"
#include "Map/Map.hpp"
#include <unistd.h>

int main()
{
	// Map *map = new Mainland("Mainland", 50, 50, 1, 57);

	// for (size_t i = 0; i < 6; i++)
	// {
	// 	map->generateMap();
	// }
	// if (EXPORT == 0)
	// 	map->printMap();
	// else
	// 	map->printTopography();
	
	// delete map;
	// return 0;

	std::vector<Mainland> maps;

	for (size_t i = 0; i < 5; i++)
	{
		maps.push_back(Mainland("Mainland", 100, 100, 1, 57));
		maps[i].generateMap();
		usleep(30000);
	}
	if (EXPORT == 0)
	{
		for (size_t i = 0; i < maps.size(); i++)
			maps[i].printMap();
	}
	else
	{
		for (size_t i = 0; i < maps.size(); i++)
			maps[i].printTopography();
	}
	return 0;
}