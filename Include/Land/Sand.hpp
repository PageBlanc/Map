/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sand.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:18:11 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 00:38:50 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Land.hpp"
#include "../Include.hpp"

#ifndef SAND_HPP
# define SAND_HPP

class Sand : public Land
{
	public:
		Sand();
		Sand(long id, int size);
		Sand(const Sand &sand);
		
		Sand &operator=(const Sand &sand);
		bool operator==(const Sand &sand);
		bool operator!=(const Sand &sand);
		~Sand();
};

#endif