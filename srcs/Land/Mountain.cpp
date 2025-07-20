/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mountain.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:40:08 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 18:40:56 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Land/Mountain.hpp"

Mountain::Mountain() : Land("Mountain", 0, 0, Vec3(0.5f, 0.5f, 0.5f))
{
	_height = 5;
	_symbol = std::string("⛰️");
}

Mountain::Mountain(int x, int y) : Land("Mountain", x, y, Vec3(0.5f, 0.5f, 0.5f))
{
	_height = 5;
	_symbol = std::string("⛰️");
}

Mountain::~Mountain()
{
}