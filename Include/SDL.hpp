/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:34:18 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/18 12:50:10 by axdubois         ###   ########.fr       */
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
		void handleInput();
		void handleMouse();
		
	private:
		SDL_Surface *_screen;
		SDL_Event _event;

		Vec3 	_cam;
		Map 	*_map;

		float _zoom;
		float _zoom_speed;
		float _move_speed;
		float _cam_pitch;
		float _cam_yaw;

		bool _running;
};

#endif