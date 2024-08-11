/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 11:08:15 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.hpp"
#include "Land/Plains.hpp"
#include "Land/Land.hpp"
#include "Map/Map.hpp"

int main()
{
	Map *map = new Mainland("Mainland", 50, 50, 10, 40, 42);
	
	map->printMap();

	delete map;
	return 0;    
}