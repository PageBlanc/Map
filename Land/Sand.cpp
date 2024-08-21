/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sand.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:19:21 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/19 15:02:15 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sand.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Sand::Sand() : Land("Sand", 0, 0)
{
	_height = 2;
	_symbol = SAND;
}

Sand::Sand(std::string type, long id, int size) : Land(type, id, size)
{
	_height =  2;
	_symbol = SAND;
}

Sand::Sand(const Sand &sand) : Land(sand)
{
	if (*this != sand)
		delete this;
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
