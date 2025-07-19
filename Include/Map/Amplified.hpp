/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Amplified.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:49:21 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 10:35:42 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include "../Land/Void.hpp"
#include "../Land/Land.hpp"
#include "../Land/Water.hpp"
#include "../Land/Sand.hpp"
#include "../Land/Plains.hpp"

#ifndef AMPLIFIED_HPP
#define AMPLIFIED_HPP


class Amplified : public Map
{
	private:
		int _depth;
		std::vector<std::vector<std::vector<Land*> > > _voxelMap;
		void generateColumn(int x, int y);
		Land* createLandByHeight(int height, int x, int y);
		
		public:
		Amplified();
		Amplified(int width, int height);
		Amplified(const Amplified &amplified);
		~Amplified();
		
		void 	gameMap();
		void 	renderMap() const;
		Land*	getVoxel(int x, int y, int z) const;
		bool	hasVisibleFace(bool *drawface, Land* currentVoxel) const;
		void	SetAllLandNeighbors(int x, int y, int z, Land *land) const;
		std::vector<Land *> setneighborLands(int x, int y, int z);

};

#endif