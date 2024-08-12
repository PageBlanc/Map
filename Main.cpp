/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/12 17:16:51 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.hpp"
#include "Land/Plains.hpp"
#include "Land/Land.hpp"
#include "Map/Map.hpp"
#include <unistd.h>

int main()
{
	Map *map = new Mainland("Mainland", 50, 50, 10, 57);

	// for (size_t i = 0; i < 3; i++)
	// {
	// 	map->generateMap();
	// }
	if (EXPORT == 0)
		map->printMap();
	else
		map->printTopography();
	
	delete map;
	return 0;
}