/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:53:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 16:35:58 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.cpp"
#include "Land/Plains.cpp"
#include "Land/Land.cpp"
#include "Map/Map.cpp"

int main()
{
	Map *map = new Mainland("Mainland", 10, 10);
	
	map->printMap();

	delete map;
	return 0;    
}