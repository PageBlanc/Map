/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:19:17 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:42:47 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Land/Ice.hpp"
/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Ice::Ice() : Land("Ice", 0, 0, Vec3(0.8f, 0.8f, 1.0f), Vec3(0, 0, 0), 0)
{
	_symbol = ICE;
}

Ice::Ice(int x, int y, int z, int height) : Land("Ice", x + y + z, 0, Vec3(0.8f, 0.8f, 1.0f), Vec3(x, y, z), height)
{
	_symbol = ICE;
}

Ice::~Ice()
{
	// Destructor logic if needed
}