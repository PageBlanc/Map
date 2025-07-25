/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Void.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:15:00 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:44:21 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOID_HPP
#define VOID_HPP

#include "Land.hpp"

class Void : public Land
{
    public:
        Void();
        Void(int x, int y, int z, int height);
        Void(const Void &voidLand);
        ~Void();
        
        Void &operator=(const Void &voidLand);
        
};

#endif
