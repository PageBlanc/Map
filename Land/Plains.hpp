/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plains.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:39:21 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 14:56:46 by pageblanche      ###   ########.fr       */
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
        Plains(std::string type, long id, int size);
        Plains(Plains &plains);

        Plains &operator=(const Plains &plains);
        bool operator==(const Plains &plains);
        bool operator!=(const Plains &plains);
        ~Plains();
};

#endif