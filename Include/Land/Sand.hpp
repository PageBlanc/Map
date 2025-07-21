/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sand.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:18:11 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/20 14:37:20 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land.hpp"
#include "../Include.hpp"

#ifndef SAND_HPP
# define SAND_HPP

class Sand : public Land
{
	public:
		Sand();
		Sand(int x, int y, int z, int height);
		Sand(const Sand &sand);
		
		Sand &operator=(const Sand &sand);
		bool operator==(const Sand &sand);
		bool operator!=(const Sand &sand);
		~Sand();
};

#endif