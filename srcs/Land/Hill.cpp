/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:19:14 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:42:02 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Land/Hill.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Hill::Hill() : Land("Hill", 0, 0, Vec3(0.59f, 0.29f, 0.0f), Vec3(0, 0, 0), 0)
{
	_symbol = HILL;
}

Hill::Hill(int x, int y, int z, int height) : Land("Hill", x + y + z, 0, Vec3(0.59f, 0.29f, 0.0f), Vec3(x, y, z), height)
{
	_symbol = HILL;
}

Hill::~Hill()
{
	// Destructor logic if needed
}