/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:37:30 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 16:40:19 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plains.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Plains::Plains() : Land("Plains", 0, 0, "🟩") {}

Plains::Plains(std::string type, long id, int size, std::string symbol)
    : Land(type, id, size, symbol) {}

Plains::Plains(Plains &plains) : Land(plains)
{
    *this = plains;
}

/*-------------------------------------OPERATORS-------------------------------------*/

Plains &Plains::operator=(const Plains &plains)
{

    _type = plains._type;
    _id = plains._id;
    _size = plains._size;
    _symbol = plains._symbol;
    return *this;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Plains::~Plains() {}
