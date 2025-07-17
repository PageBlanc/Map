/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:34:18 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/16 19:36:32 by axdubois         ###   ########.fr       */
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
		Vec3 	_camera_translation;
		Map 	*_map;

		float _zoom;
		float _move_speed;
		float _zoom_speed;
		
		float _rotation_angle;

		bool _running;
};

#endif