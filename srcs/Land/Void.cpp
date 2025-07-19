/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Void.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:15:00 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 12:42:45 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Land/Void.hpp"

Void::Void() : Land()
{
}

Void::Void(long id, int height) : Land("Void", id, height, Vec3(0.0f, 0.0f, 0.0f))
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
