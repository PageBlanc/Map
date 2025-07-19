/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:01 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 11:21:11 by axdubois         ###   ########.fr       */
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
		Mainland(int x, int y);
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