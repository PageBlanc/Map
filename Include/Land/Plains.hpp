/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:39:21 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/20 14:44:10 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAINS_HPP
# define PLAINS_HPP

#include "Land.hpp"

class Plains : public Land
{
    public:
        Plains();
        Plains(int x, int y, int z, int height);
        Plains(Plains &plains);

        Plains &operator=(const Plains &plains);
        bool operator==(const Plains &plains);
        bool operator!=(const Plains &plains);
        ~Plains();
};

#endif