/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:14:44 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:41:51 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "Land.hpp"

class Ice : public Land
{
	public:
		Ice();
		Ice(int x, int y, int z, int height);
		~Ice();
};

#endif