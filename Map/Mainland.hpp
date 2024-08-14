/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:01 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/14 16:48:14 by pageblanche      ###   ########.fr       */
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
		
		void	setAllNearLands();
		void	emptyMapGeneration(int x, int y);
		void	generateMap();
		
		bool	nearCenter(int x, int y, int width, int height);
		bool	nearLand(int x, int y, int width, int height, int random_value);
		int     averageHeight(int x, int y);
		int		maxHeight(int x, int y);
		
		int		RecursiveNearLand(int x, int y, int width, int height, int random_value);
		
		int		fillLand(int x, int y, int width, int height, int random_value);
		void	fillPound();
		void	fillHeight(int random_value);
		
		int		PutSand(int x, int y, int width, int height);
		
		int     countNearSameLand(int x, int y, int width, std::string type, int random_value);
		int		countMaxHeight(int x, int y, int random_value);

		void	setHeight();
		void	smoothingHeight();
		void	smoothPartofMap(int x, int y);

		
		Mainland &operator=(const Mainland &mainland);
		~Mainland();
};

#endif