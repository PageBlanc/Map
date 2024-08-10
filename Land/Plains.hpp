/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:39:21 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 16:37:17 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land.hpp"

#ifndef PLAINS_HPP
# define PLAINS_HPP

class Plains : public Land
{
    private:
    public:
        Plains();
        Plains(std::string type, long id, int size, std::string symbol);
        Plains(Plains &plains);

        Plains &operator=(const Plains &plains);
        ~Plains();
};

#endif