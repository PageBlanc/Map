/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Land.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:13:05 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/10 11:21:46 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

#ifndef Land_HPP
#define Land_HPP

class Land
{
	protected:
		std::string _type;
		std::string _symbol;
		long 		_id;
		int 		_size;

	public:
		Land();
		Land(std::string type, long id, int size, std::string symbol);
		Land(Land const &land);


		virtual std::string getType() 	const;
		virtual long 		getId() 	const;
		virtual int 		getSize() 	const;
		virtual std::string getSymbol() const;;

		virtual void 		setType(std::string type);
		virtual void 		setSize(int size);
		virtual void 		setId(long id);
		virtual void 		setSymbol(std::string symbol);

		Land operator=(const Land &land);
		~Land();
};
std::ostream &operator<<(std::ostream &os, Land land);

#endif