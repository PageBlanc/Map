/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:01 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/16 16:50:43 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include "../Land/Plains.hpp"

#ifndef MAINLAND_HPP
# define MAINLAND_HPP

class Mainland : public Map
{
	public:
		Mainland();
		Mainland(std::string type, int x, int y);
		Mainland(std::string type, int x, int y, int smoothness, int density);
		Mainland(const Mainland &mainland);

		void	gameMap();
		void	initMap();
		
		void	setAllNearLands();
		int		countNearSameLand(int x, int y, int width, std::string type, int random_value);
		
		void	generatePerlinMap();
		float	perlinNoise(float x, float y);
		float	radialGradient(int x, int y);
		void	connectLand();

		void	PutSand();
		
		Mainland &operator=(const Mainland &mainland);
		~Mainland();
};

#endif