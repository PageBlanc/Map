/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:01 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 16:35:38 by pageblanche      ###   ########.fr       */
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
		Mainland(std::string type, int x, int y, int smoothness, int density, int seed);
		Mainland(const Mainland &mainland);

		void	generateMap(int x, int y);
		
		Mainland &operator=(const Mainland &mainland);
		~Mainland();
};

#endif