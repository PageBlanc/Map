/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Void.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:15:00 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:46:07 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Land/Void.hpp"

Void::Void() : Land()
{
}

Void::Void(int x, int y, int z, int height) : Land("Void", x + y + z, 0, Vec3(0.0f, 0.0f, 0.0f), Vec3(x, y, z), height)
{
    _symbol = VOID;
}

Void::Void(const Void &voidLand) : Land(voidLand)
{
}

Void::~Void()
{
}

Void &Void::operator=(const Void &voidLand)
{
    if (this != &voidLand)
        Land::operator=(voidLand);
    return *this;
}
