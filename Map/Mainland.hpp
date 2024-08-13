/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:01 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/13 15:24:04 by pageblanche      ###   ########.fr       */
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

		void	emptyMapGeneration(int x, int y);
		void	generateMap();
		
		bool	nearCenter(int x, int y, int width, int height);
		bool	nearLand(int x, int y, int width, int height, int random_value);
		
		int		RecursiveNearLand(int x, int y, int width, int height, int random_value);
		
		int		fillLand(int x, int y, int width, int height, int random_value);
		void	fillPound();
		
		int		PutSand(int x, int y, int width, int height);
		
		int     countNearSameLand(int x, int y, int width, std::string type, int random_value);

		void	setHeight();
		
		Mainland &operator=(const Mainland &mainland);
		~Mainland();
};

#endif