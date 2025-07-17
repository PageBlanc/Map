/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/16 17:48:40 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.hpp"
#include "Land/Plains.hpp"
#include "Land/Land.hpp"
#include "Map/Map.hpp"
#include "../Include/SDL.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
		{
			std::cout << "Usage: ./a.out [width] [height]" << std::endl;
			return (1);
		}
		
		SDL sdl;
		int width = std::atoi(av[1]);
		int height = std::atoi(av[2]);
		sdl.init(width, height);
		sdl.render();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}