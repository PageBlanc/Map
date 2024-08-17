/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/16 15:01:09 by pageblanche      ###   ########.fr       */
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
		int width = std::atoi(av[1]);
		int height = std::atoi(av[2]);
		Mainland map("Mainland", width, height);

		if (EXPORT)
			map.printTopography();
		else
			map.printMap();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}