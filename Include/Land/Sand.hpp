/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sand.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:18:11 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 16:29:16 by pageblanche      ###   ########.fr       */
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
		Sand(std::string type, long id, int size);
		Sand(const Sand &sand);
		
		Sand &operator=(const Sand &sand);
		bool operator==(const Sand &sand);
		bool operator!=(const Sand &sand);
		~Sand();
};

#endif