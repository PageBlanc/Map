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

#ifndef MAP_HPP
# define MAP_HPP

class Map
{
	protected:
		std::vector<std::vector<Land *> >	_map;
		const std::string					_type;
		const int							_smoothness;
		const int							_density;
		const int							_seed;
		const int							_width;
		const int							_height;

	public:
		Map();
		Map(std::string type);
		Map(std::string type, int x, int y);
		Map(std::string type, int smoothness, int density, int seed, int x, int y);
		Map(const Map &map);

		virtual std::vector<std::vector<Land *> >	getMap() 				const;
		virtual std::string 						getType() 				const;
		virtual Land								*getLand(int x, int y)	const;
		virtual int 								getSmoothness() 		const;
		virtual int 								getDensity() 			const;
		virtual int 								getSeed() 				const;

		virtual void							setLand(int x, int y, Land &land);
	
		virtual void	printMap() 				const;
		virtual void	generateMap() = 0;


		Map &operator=(const Map &map);
		virtual ~Map();
};

#endif