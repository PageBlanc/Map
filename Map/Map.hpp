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

#include "../Land/Land.hpp"
#include <vector>
#include <map>

#ifndef AMAP_HPP
# define AMAP_HPP

class Map
{
	protected:
		std::vector<std::vector<Land>>	_map;
		const std::string				_type;
		const int						_smoothness;
		const int						_density;
		const int						_seed;

		Map();
	public:
		Map(std::vector<std::vector<Land>> map, std::string type, int smoothness, int density, int seed);
		Map(const Map &map);

		virtual std::vector<std::vector<Land>>	getMap() 				const;
		virtual std::string 					getType() 				const;
		virtual Land							getLand(int x, int y)	const;
		virtual int 							getSmoothness() 		const;
		virtual int 							getDensity() 			const;
		virtual int 							getSeed() 				const;
	
		virtual void							setLand(int x, int y, Land land);
	
		virtual void	printMap() 				const;
		virtual void	generateMap() = 0;


		Map &operator=(const Map &map);	
		virtual ~Map();
};

#endif