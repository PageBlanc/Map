/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:37:30 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 01:03:29 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land/Plains.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Plains::Plains() : Land("Plains", 0, 0)
{
	_height = 3;
	_symbol = PLAINS;
}

Plains::Plains(long id, int size) : Land("Plains", id, size)
{
	_height = 3;
	_symbol = PLAINS;
}

Plains::Plains(Plains &plains) : Land(plains)
{
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
