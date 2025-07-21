/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sand.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:19:21 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/20 14:45:51 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land/Sand.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Sand::Sand() : Land("Sand", 0, 0, Vec3(1.0f, 1.0f, 0.0f), Vec3(0, 0, 0), 0)
{
	_symbol = SAND;
}

Sand::Sand(int x, int y, int z, int height) : Land("Sand", x + y + z, 0, Vec3(1.0f, 1.0f, 0.0f), Vec3(x, y, z), height)
{
	_symbol = SAND;
}

Sand::Sand(const Sand &sand) : Land(sand)
{
	*this = sand;
}

/*-------------------------------------OPERATORS-------------------------------------*/

Sand &Sand::operator=(const Sand &sand)
{
	_type = sand.getType();
	_id = sand.getId();
	_size = sand.getSize();
	_symbol = sand.getSymbol();
	_height = sand.getHeight();
	return *this;
}

bool Sand::operator==(const Sand &sand)
{
	if (_type != sand._type)
		return false;
	if (_id != sand._id)
		return false;
	if (_size != sand._size)
		return false;
	if (_symbol != sand._symbol)
		return false;
	if (_height != sand._height)
		return false;
	return true;
}

bool Sand::operator!=(const Sand &sand)
{
	if (_type != sand._type)
		return true;
	if (_id != sand._id)
		return true;
	if (_size != sand._size)
		return true;
	if (_symbol != sand._symbol)
		return true;
	if (_height != sand._height)
		return true;
	return false;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Sand::~Sand() {}
