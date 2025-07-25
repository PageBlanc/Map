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
#include "../Land/Void.hpp"
#include "../Land/Land.hpp"
#include "../Land/Water.hpp"
#include "../Land/Sand.hpp"
#include "../Land/Plains.hpp"
#include "../Land/Mountain.hpp"
#include "../Land/Hill.hpp"
#include "../Land/Ice.hpp"
#include "../SDL.hpp"
#include "../Noise/PerlinNoise.hpp"
#include "../Object/Light.hpp"

#ifndef MAP_HPP
# define MAP_HPP

class Map
{
	protected:
		std::vector<std::vector<std::vector<Land*> > >	_voxelMap;
		const std::string								_type;
		int												_smoothness;
		int												_density;
		int												_seed;
		int												_width;
		int												_height;
		int												_depth;
		Light											*_light;

	public:
		Map();
		Map(std::string type, int x, int y);
		Map(const Map &map);

		Land												*getLand(int x, int y, int z)	const;
		std::vector<std::vector<std::vector<Land*> > >		getMap() 				const;
		std::string 										getType() 				const;
		int 												getSmoothness() 		const;
		int 												getDensity() 			const;
		int 												getSeed() 				const;

		void	setLand(int x, int y, int z, Land &land);
		void	SetAllLandNeighbors(int x, int y, int z, Land *land) const;

		bool	hasVisibleFace(bool *drawface, Land* currentVoxel) const;
		void	renderMap(Vec3 cameraPos) const;
	
		void    gameMap();
		void 	generateColumn(int x, int y);
		Land*	createLandByDepth(int x, int y, int currentZ, double totalHeight, double temperature);
		double	createCliffs(double height, int x, int y);
		
		Map &operator=(const Map &map);
		bool operator==(const Map &map) const;
		bool operator!=(const Map &map) const;
		~Map();
		void 	cleanup();
};

#endif