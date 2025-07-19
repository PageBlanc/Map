/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:52:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 12:05:45 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include.hpp"
#include "../Land/Land.hpp"
#include "../SDL.hpp"
#include "../Noise/PerlinNoise.hpp"

#ifndef MAP_HPP
# define MAP_HPP

class Map
{
	protected:
		std::vector<std::vector<Land *> >		_map;
		std::map<Land *, std::vector<Land *> >	_nearLands;
		const std::string						_type;
		const int								_smoothness;
		const int								_density;
		const int								_seed;
		const int								_width;
		const int								_height;
		const int								_depth;


	public:
		Map();
		Map(std::string type, int x, int y);
		Map(const Map &map);

		virtual std::vector<std::vector<Land *> >		getMap() 				const;
		virtual std::map<Land *, std::vector<Land *> >	getNearLands()			const;
		virtual std::string 							getType() 				const;
		virtual Land									*getLand(int x, int y)	const;
		virtual int 									getSmoothness() 		const;
		virtual int 									getDensity() 			const;
		virtual int 									getSeed() 				const;

		virtual void									setLand(int x, int y, Land &land);
		virtual void									setNearLands(Land &land, std::vector<Land *> nearLands);

		virtual void	renderMap()					const;
		virtual Vec3  	convertIsoTo3D(float x, float y, float z) const;
	
		virtual void	printMap() 					const;
		virtual void	printTopography()			const;
		virtual void    gameMap() = 0;

		Map &operator=(const Map &map);
		bool operator==(const Map &map) const;
		bool operator!=(const Map &map) const;
		virtual ~Map();
};

#endif