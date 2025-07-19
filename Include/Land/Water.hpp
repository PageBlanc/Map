/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:53:36 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 00:38:00 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATER_HPP
# define WATER_HPP

#include "Land.hpp"

class Water : public Land
{
    private:
    public:
        Water();
        Water(long id, int size);
        Water(Water &water);

        Water &operator=(const Water &water);
        bool operator==(const Water &water);
        bool operator!=(const Water &water);
        ~Water();
};

#endif