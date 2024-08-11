/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:53:49 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 15:00:05 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Water.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Water::Water(std::string type, long id, int size)
{
	_type = type;
	_id = id;
	_size = size;
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
	return true;
}

bool Water::operator!=(const Water &water)
{
	return !(*this == water);
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Water::~Water() {}