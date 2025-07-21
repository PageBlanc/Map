/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:53:36 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/20 14:47:14 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATER_HPP
# define WATER_HPP

#include "Land.hpp"

class Water : public Land
{
    public:
        Water();
        Water(int x, int y, int z, int height);
        Water(const Water &water);

        Water &operator=(const Water &water);
        bool operator==(const Water &water);
        bool operator!=(const Water &water);
        ~Water();
};

#endif