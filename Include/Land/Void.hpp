/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Void.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:15:00 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 00:38:15 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOID_HPP
#define VOID_HPP

#include "Land.hpp"

class Void : public Land
{
public:
    Void();
    Void(long id, int height);
    Void(const Void &voidLand);
    ~Void();
    
    Void &operator=(const Void &voidLand);
    
};

#endif
