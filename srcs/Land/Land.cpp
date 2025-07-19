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

#include "Land/Land.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Land::Land() : _type("Land"), _symbol(VOID), _id(0), _size(0), _height(0), _color(0.0f, 0.0f, 0.0f)
{
	for (int i = 0; i < 6; i++)
		_neighbors[i] = NULL;
}

Land::Land(std::string type, long id, int size, Vec3 color) : _type(type), _symbol(VOID), _id(id), _size(size), _height(0), _color(color)
{
	for (int i = 0; i < 6; i++)
		_neighbors[i] = NULL;
}

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

int Land::getHeight() const
{
	return _height;
}

Land* Land::getNeighbor(int index) const
{
	if (index < 0 || index >= 6)
		return NULL;
	return _neighbors[index];
}

Vec3 Land::getColor() const
{
	return _color;
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

void Land::setHeight(int height)
{
	_height = height;
}

void Land::setNeighbor(int index, Land *neighbor)
{
	if (index < 0 || index >= 6)
		return;
	_neighbors[index] = neighbor;
}

bool Land::isVoid() const
{
	if (_type == "Void")
		return true;
	return false;
}

void Land::setColor(Vec3 color)
{
	_color = color;
}

/*-------------------------------------OPERATORS-------------------------------------*/

std::ofstream &operator<<(std::ofstream &os, Land *land)
{
	if (!land)
	{
		os << "Land(nullptr)";
		return os;
	}
	os << "Land(type=" << land->getType()
	   << ", id=" << land->getId()
	   << ", size=" << land->getSize()
	   << ", symbol=" << land->getSymbol()
	   << ", height=" << land->getHeight() << ")";
	return os;
}

std::ofstream &operator<<(std::ofstream &os, Land &land)
{
	os << "Land(type=" << land.getType()
	   << ", id=" << land.getId()
	   << ", size=" << land.getSize()
	   << ", symbol=" << land.getSymbol()
	   << ", height=" << land.getHeight() << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, Land *land)
{
	if (!land)
	{
		os << "Land(nullptr)";
		return os;
	}
	os << "Land(type=" << land->getType()
	   << ", id=" << land->getId()
	   << ", size=" << land->getSize()
	   << ", symbol=" << land->getSymbol()
	   << ", height=" << land->getHeight() << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, Land &land)
{
	os << "Land(type=" << land.getType()
	   << ", id=" << land.getId()
	   << ", size=" << land.getSize()
	   << ", symbol=" << land.getSymbol()
	   << ", height=" << land.getHeight() << ")";
	return os;
}

Land Land::operator=(const Land &land)
{
	_type = land.getType();
	_id = land.getId();
	_size = land.getSize();
	_symbol = land.getSymbol();
	_height = land.getHeight();
	return *this;
}

bool Land::operator==(const Land &land)
{
	if (_type != land._type)
		return false;
	if (_id != land._id)
		return false;
	if (_size != land._size)
		return false;
	if (_symbol != land._symbol)
		return false;
	if (_height != land._height)
		return false;
	return true;
}

bool Land::operator!=(const Land &land)
{
	return !(*this == land);
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Land::~Land() {}