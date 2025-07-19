/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:53:49 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 12:42:56 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land/Water.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Water::Water() : Land("Water", 0, 0, Vec3(0.0f, 0.0f, 1.0f))
{
	_height = 1;
	_symbol = WATER;
}

Water::Water(long id, int size): Land("Water", id, size , Vec3(0.0f, 0.0f, 1.0f))
{
	_height = 1;
	_symbol = WATER;
}

Water::Water(Water &water) : Land(water)
{
	if (*this != water)
		delete this;
	*this = water;
}

/*-------------------------------------OPERATORS-------------------------------------*/

Water &Water::operator=(const Water &water)
{

	_type = water.getType();
	_id = water.getId();
	_size = water.getSize();
	_symbol = water.getSymbol();
	return *this;
}

bool Water::operator==(const Water &water)
{
	if (_type != water._type)
		return false;
	if (_id != water._id)
		return false;
	if (_size != water._size)
		return false;
	if (_symbol != water._symbol)
		return false;
	if (_height != water._height)
		return false;
	return true;
}

bool Water::operator!=(const Water &water)
{
	return !(*this == water);
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Water::~Water() {}