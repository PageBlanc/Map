/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/15 17:49:00 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.hpp"
#include "Land/Plains.hpp"
#include "Land/Land.hpp"
#include "Map/Map.hpp"
#include <unistd.h>

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
		{
			std::cout << "Usage: ./a.out [witdh] [height]" << std::endl;
			return (1);
		}
		Map *map = new Mainland("Mainland", std::atoi(av[1]), std::atoi(av[2]), 1, 57);

		for (size_t i = 0; i < 4; i++)
		{
			map->generateMap();
		}
		if (EXPORT == 0)
			map->printMap();
		else
			map->printTopography();
		
		delete map;
		return 0;

		// for (size_t i = 0; i < 5; i++)
		// {
		// 	Map *map = new Mainland("Mainland", 50, 50, 1, 57);
		// 	for (size_t i = 0; i < 6; i++)
		// 	{
		// 		map->generateMap();
		// 	}
		// 	if (EXPORT == 0)
		// 		map->printMap();
		// 	else
		// 		map->printTopography();
		// 	delete map;
		// 	usleep(1000000);
		// }
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}