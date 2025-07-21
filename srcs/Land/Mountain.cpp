/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mountain.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:40:08 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:43:15 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Land/Mountain.hpp"

Mountain::Mountain() : Land("Mountain", 0, 0, Vec3(0.5f, 0.5f, 0.5f), Vec3(0, 0, 0), 0)
{
	_symbol = std::string("⛰️");
}

Mountain::Mountain(int x, int y, int z, int height) : Land("Mountain", x + y + z, 0, Vec3(0.5f, 0.5f, 0.5f), Vec3(x, y, z), height)
{
	_symbol = std::string("⛰️");
}

Mountain::~Mountain()
{
}