/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:34:18 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/17 22:12:12 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_HPP
# define SDL_HPP

#include "Include.hpp"

#include "Map/Map.hpp"

class SDL
{
	public:
		SDL();
		~SDL();

		void init(int mapwidth, int mapheight);
		void render();
		void cleanup();

		void handleEvents();
		void handleInput(Vec3& translation, float move_speed);
		void handleMouse(Vec3& translation, float& zoom, float& zoom_speed, SDL_Event& event);
		
	private:
		SDL_Surface *_screen;
		SDL_Event _event;

		Vec3 	_mv_translation;
		Map 	*_map;

		float _zoom;
		float _move_speed;
		float _zoom_speed;
		
		float _rotation_angle_x;
		float _rotation_angle_y;

		bool _running;
};

#endif