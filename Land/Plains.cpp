/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:37:30 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/13 15:22:25 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plains.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Plains::Plains(std::string type, long id, int size)
{
	_type = type;
	_id = id;
	_size = size;
	_height = 0;
	_symbol = PLAINS;
}

Plains::Plains(Plains &plains) : Land(plains)
{
	if (*this != plains)
		delete this;
	*this = plains;
}

/*-------------------------------------OPERATORS-------------------------------------*/

Plains &Plains::operator=(const Plains &plains)
{

	_type = plains.getType();
	_id = plains.getId();
	_size = plains.getSize();
	_symbol = plains.getSymbol();
	return *this;
}

bool Plains::operator==(const Plains &plains)
{
	if (_type != plains._type)
		return false;
	if (_id != plains._id)
		return false;
	if (_size != plains._size)
		return false;
	if (_symbol != plains._symbol)
		return false;
	if (_height != plains._height)
		return false;
	return true;
}

bool Plains::operator!=(const Plains &plains)
{
	return !(*this == plains);
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Plains::~Plains() {}
