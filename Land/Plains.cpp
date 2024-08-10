/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:37:30 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 21:20:07 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plains.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Plains::Plains(std::string type, long id, int size, std::string symbol)
{
    _type = type;
    _id = id;
    _size = size;
    _symbol = symbol;
}

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
