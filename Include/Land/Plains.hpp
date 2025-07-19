/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:39:21 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 00:39:01 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAINS_HPP
# define PLAINS_HPP

#include "Land.hpp"

class Plains : public Land
{
    private:
    public:
        Plains();
        Plains(long id, int size);
        Plains(Plains &plains);

        Plains &operator=(const Plains &plains);
        bool operator==(const Plains &plains);
        bool operator!=(const Plains &plains);
        ~Plains();
};

#endif