/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorLand.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:45:10 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/11 15:07:20 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORLAND_HPP
# define COLORLAND_HPP

#define EXPORT 1

#if EXPORT
#	define VOID    	std::string(" ")
#	define WATER  	std::string("W")
#	define DESERT 	std::string("D")
#	define PLAINS 	std::string("P")
#	define ICE 		std::string("I")
#else
#	define VOID    	std::string("⬛")
#	define WATER   	std::string("🟦")
#	define DESERT 	std::string("🟨")
#	define PLAINS 	std::string("🟩")
#	define ICE 		std::string("⬜")
#endif
	
#endif