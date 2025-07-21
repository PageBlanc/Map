/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mountain.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:38:58 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:37:07 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUNTAIN_HPP
#define MOUNTAIN_HPP

#include "Land.hpp"

class Mountain : public Land
{
    public:
    	Mountain();
        Mountain(int x, int y, int z, int height);
        virtual ~Mountain();

};

#endif