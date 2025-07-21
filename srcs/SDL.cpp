/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:36:02 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 16:24:38 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/SDL.hpp"
#include "../Include/Map/Mainland.hpp"
#include "../Include/Map/Amplified.hpp"

SDL::SDL() {}

SDL::~SDL()
{
	cleanup();
}

void SDL::init(int mapwidth, int mapheight)
{
	std::cout << "Initializing SDL..." << std::endl;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "SDL_Init successful" << std::endl;
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	std::cout << "Creating video mode " << WIDTH << "x" << HEIGHT << std::endl;
	_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_OPENGL | SDL_RESIZABLE);
	if (!_screen)
	{
		std::cerr << "SDL_SetVideoMode failed: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	std::cout << "Video mode created successfully" << std::endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (double)WIDTH / HEIGHT, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	
	std::cout << "Initializing variables..." << std::endl;
	_map = new Amplified(mapwidth, mapheight);
	_zoom = 0.2f;
	_move_speed = 0.2f;
	_zoom_speed = 0.05f;
	_cam = Vec3(0.0f, 0.0f, -5.0f);
	_cam_pitch = -60.0f;
	_cam_yaw = 45.0f;	
	_event = SDL_Event();
	
	_running = true;
	std::cout << "SDL initialized successfully" << std::endl;
}

void SDL::cleanup()
{
	if (_map)
	{
		delete _map;
		_map = NULL;
	}
	SDL_Quit();
	std::cout << "SDL cleaned up successfully" << std::endl;
}

void SDL::handleInput()
{
	const Uint8 *state = SDL_GetKeyState(NULL);
	
	if (state[SDLK_z])
	{
		_cam.x -= sinf(_cam_yaw * M_PI / 180.0f) * _move_speed;
		_cam.y -= cosf(_cam_yaw * M_PI / 180.0f) * _move_speed;
	}
	if (state[SDLK_s])
	{
		_cam.x += sinf(_cam_yaw * M_PI / 180.0f) * _move_speed;
		_cam.y += cosf(_cam_yaw * M_PI / 180.0f) * _move_speed;
	}
	if (state[SDLK_q])
	{
		_cam.x += cosf(_cam_yaw * M_PI / 180.0f) * _move_speed;
		_cam.y -= sinf(_cam_yaw * M_PI / 180.0f) * _move_speed;
	}
	if (state[SDLK_d])
	{
		_cam.x -= cosf(_cam_yaw * M_PI / 180.0f) * _move_speed;
		_cam.y += sinf(_cam_yaw * M_PI / 180.0f) * _move_speed;
	}
	if (state[SDLK_SPACE])
	{
		_cam.z -= _move_speed;
	}
	if (state[SDLK_LSHIFT])
	{
		_cam.z += _move_speed;
	}
	if (state[SDLK_LEFT])
	{
		_cam_yaw -= 3.0f;
		if (_cam_yaw < 0.0f) _cam_yaw += 360.0f;
		if (_cam_yaw >= 360.0f) _cam_yaw -= 360.0f;
	}
	if (state[SDLK_RIGHT])
	{
		_cam_yaw += 3.0f;
		if (_cam_yaw < 0.0f) _cam_yaw += 360.0f;
		if (_cam_yaw >= 360.0f) _cam_yaw -= 360.0f;
	}
	if (state[SDLK_UP])
	{
		_cam_pitch -= 3.0f;
		if (_cam_pitch < -180.0f) _cam_pitch = -180.0f;
	}
	if (state[SDLK_DOWN])
	{
		_cam_pitch += 3.0f;
		if (_cam_pitch > 0.0f) _cam_pitch = 0.0f;
	}
}

void SDL::handleMouse()
{
	if (_event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		float x_world = (2.0f * x / 800.0f - 1.0f) / _zoom - _cam.x;
		float y_world = (2.0f * y / 600.0f - 1.0f) / _zoom - _cam.y;

		if (_event.button.button == SDL_BUTTON_WHEELUP)
		{
			_zoom += _zoom_speed;
			if (_zoom > 5.0f) _zoom = 5.0f;
			{
				_cam.x += x_world * _zoom_speed;
				_cam.y += y_world * _zoom_speed;
			}
		}
		if (_event.button.button == SDL_BUTTON_WHEELDOWN)
		{
			_zoom -= _zoom_speed;
			if (_zoom < 0.1f) _zoom = 0.1f;
			{
				_cam.x -= x_world * _zoom_speed;
				_cam.y -= y_world * _zoom_speed;
			}
		}
	}
}

void SDL::handleEvents()
{
	while (SDL_PollEvent(&_event))
	{
		if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_ESCAPE)
			_running = false;
		switch (_event.type)
		{
			case SDL_QUIT:
				_running = false;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handleInput();
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handleMouse();
				break;
			default:
				break;
		}
	}
}

void SDL::render()
{
	Uint32 lastTime = SDL_GetTicks();
	int frames = 0;
	float fps = 0.0f;
	
	while (_running)
	{
		handleEvents();
		handleInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glRotatef(_cam_pitch, 1.0f, 0.0f, 0.0f);
		glRotatef(_cam_yaw, 0.0f, 0.0f, 1.0f);
		
		glTranslatef(_cam.x, _cam.y, _cam.z);

    	glScalef(_zoom, _zoom, _zoom);
		
		glEnable(GL_DEPTH_TEST);
		drawFPS(lastTime, frames, fps);
		// drawCoordinates(_cam, _cam_pitch, _cam_yaw);
		_map->renderMap(_cam);
		SDL_GL_SwapBuffers();
	}
}