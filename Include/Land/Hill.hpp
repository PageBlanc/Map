/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hill.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:14:54 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 14:41:33 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HILL_HPP
#define HILL_HPP

#include "Land.hpp"

class Hill : public Land
{
	public:
		Hill();
		Hill(int x, int y, int z, int height);
		~Hill();
};

#endif