/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Land.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:12:37 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 11:12:38 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Land::Land() : _type("Land"), _symbol("🟩"), _id(0), _size(0) {}

Land::Land(Land const &land)
{
	*this = land;
}

/*-------------------------------------GETTERS-------------------------------------*/

std::string Land::getType() const
{
    return _type;
}

long Land::getId() const
{
    return _id;
}

int Land::getSize() const
{
    return _size;
}

std::string Land::getSymbol() const
{
    return _symbol;
}

/*-------------------------------------SETTERS-------------------------------------*/

void Land::setType(std::string type)
{
    _type = type;
}

void Land::setSize(int size)
{
    _size = size;
}

void Land::setId(long id)
{
    _id = id;
}

void Land::setSymbol(std::string symbol)
{
    _symbol = symbol;
}



std::ofstream &operator<<(std::ofstream &os, Land land)
{
	os << land.getSymbol();
	return os;
}

Land Land::operator=(const Land &land)
{
	_type = land._type;
	_id = land._id;
	_size = land._size;
	_symbol = land._symbol;
	return *this;
}

Land::~Land() {}