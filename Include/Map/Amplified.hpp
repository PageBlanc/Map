/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Amplified.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:49:21 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 16:10:21 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include "../Define.hpp"
#include "../Land/Void.hpp"
#include "../Land/Land.hpp"
#include "../Land/Water.hpp"
#include "../Land/Sand.hpp"
#include "../Land/Plains.hpp"
#include "../Land/Mountain.hpp"
#include "../Land/Hill.hpp"
#include "../Land/Ice.hpp"
#include <algorithm>


#ifndef AMPLIFIED_HPP
#define AMPLIFIED_HPP


class Amplified : public Map
{
	private:
		std::vector<std::vector<std::vector<Land*> > > _voxelMap;
		
	public:
		Amplified();
		Amplified(int width, int height);
		Amplified(const Amplified &amplified);
		~Amplified();
		
		void 	gameMap();
		void 	cleanup();
		void 	renderMap(Vec3 cameraPos) const;
		void 	generateColumn(int x, int y);
		Land*	createLandByDepth(int x, int y, int currentZ, double totalHeight, double temperature);
		Land*	getVoxel(int x, int y, int z) const;
		bool	hasVisibleFace(bool *drawface, Land* currentVoxel) const;
		void	SetAllLandNeighbors(int x, int y, int z, Land *land) const;
		double	createCliffs(double height, int x, int y);
		
		std::vector<Land *> setneighborLands(int x, int y, int z);

};

#endif