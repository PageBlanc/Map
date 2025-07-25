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

#include "../Include.hpp"

#ifndef Land_HPP
#define Land_HPP

class Land
{
	protected:
		std::string _type;
		std::string _symbol;
		Land 		*_neighbors[6];
		long 		_id;
		int 		_size;
		int			_height;
		Vec3		_color;
		Vec3		_position;

	public:
		Land();
		Land(std::string type, long id, int size, Vec3 color, Vec3 position, int height);
		Land(Land const &land);

		virtual std::string getType() 	const;
		virtual long 		getId() 	const;
		virtual int 		getSize() 	const;
		virtual std::string getSymbol() const;
		virtual int 		getHeight() const;
		virtual Land*		getNeighbor(int index) const;
		virtual Vec3		getColor() const;
		virtual Vec3		getPosition() const;

		virtual void 		setType(std::string type);
		virtual void 		setSize(int size);
		virtual void 		setId(long id);
		virtual void 		setSymbol(std::string symbol);
		virtual void 		setHeight(int height);
		virtual void 		setNeighbor(int index, Land *neighbor);
		virtual void 		setColor(Vec3 color);
		virtual void 		setPosition(Vec3 position);
		virtual void 		setPosition(int x, int y, int z);

		virtual bool 		isVoid() const;


		Land operator=(const Land &land);
		bool operator==(const Land &land);
		bool operator!=(const Land &land);
		virtual ~Land();
};

std::ostream &operator<<(std::ostream &os, Land *land);
std::ostream &operator<<(std::ostream &os, Land &land);

#endif