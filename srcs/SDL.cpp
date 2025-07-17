/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:36:02 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/17 01:05:32 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/SDL.hpp"
#include "../Include/Map/Mainland.hpp"

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
	_map = new Mainland("Mainland", mapwidth, mapheight);

	std::cout << "Initializing variables..." << std::endl;
	_zoom = 0.2f;
	_move_speed = 0.2f;
	_zoom_speed = 0.05f;
	_mv_translation.x = 0.0f;
	_mv_translation.y = 0.0f;
	_mv_translation.z = -10.0f;

	_rotation_angle = 1.0f;
	_camera_translation.x = 0.0f;
	_camera_translation.y = 0.0f;
	_camera_translation.z = 0.0f;

	memset(&_event, 0, sizeof(SDL_Event)); // Initialize the SDL_Event structure
	
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

void SDL::handleInput(Vec3 &translation, float move_speed)
{
	const Uint8 *state = SDL_GetKeyState(NULL);
	if (state[SDLK_z])
		translation.y -= move_speed;
	if (state[SDLK_s])
		translation.y += move_speed;
	if (state[SDLK_q])
		translation.x += move_speed;
	if (state[SDLK_d])
		translation.x -= move_speed;
	if (state[SDLK_LEFT])
	{
		_camera_translation.y -= move_speed;
		_rotation_angle -= 1.0f;
	}
	if (state[SDLK_RIGHT])
	{
		_camera_translation.y += move_speed;
		_rotation_angle += 1.0f;
	}
	if (state[SDLK_UP])
	{
		_camera_translation.x += move_speed;
		_rotation_angle -= 1.0f;
	}
	if (state[SDLK_DOWN])
	{
		_camera_translation.x -= move_speed;
		_rotation_angle += 1.0f;
	}
	if (state[SDLK_SPACE])
	{
		_camera_translation.z += move_speed;
		_rotation_angle += 1.0f;
	}
	if (state[SDLK_RSHIFT])
	{
		_camera_translation.z -= move_speed;
		_rotation_angle -= 1.0f;
	}
}

void SDL::handleMouse(Vec3 &translation, float &zoom, float &zoom_speed, SDL_Event &event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		float x_world = (2.0f * x / 800.0f - 1.0f) / zoom - translation.x;
		float y_world = (2.0f * y / 600.0f - 1.0f) / zoom - translation.y;

		if (event.button.button == SDL_BUTTON_WHEELUP) {
			zoom += zoom_speed;

			translation.x += x_world * zoom_speed;
			translation.y += y_world * zoom_speed;
			
		}
		if (event.button.button == SDL_BUTTON_WHEELDOWN) {
			zoom -= zoom_speed;
			if (zoom < 0.1f) zoom = 0.1f;

			translation.x -= x_world * zoom_speed;
			translation.y -= y_world * zoom_speed;
		}
	}
}

void SDL::handleEvents()
{
	memset(&_event, 0, sizeof(SDL_Event)); // Reset the SDL_Event structure
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
				handleInput(_mv_translation, _move_speed);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handleMouse(_mv_translation, _zoom, _zoom_speed, _event);
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
		handleInput(_mv_translation, _move_speed);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glRotatef(_rotation_angle, _camera_translation.x, _camera_translation.y, _camera_translation.z);
		
		glTranslatef(_mv_translation.x, _mv_translation.y, _mv_translation.z);
		glScalef(_zoom, _zoom, _zoom);
		
		glEnable(GL_DEPTH_TEST);
		drawFPS(lastTime, frames, fps);
		glColor3f(1.0f, 0.0f, 1.0f);
		Vec3 plane_position = {0.0f, 0.0f, 0.0f};
		drawplane(plane_position, 10.0f, 0.0f );
		glColor3f(1.0f, 0.0f, 0.0f);
		Vec3 position = {0.0f, 0.0f, 0.0f};
		drawCube(position, 10.0f, 0.f);
		// _map->renderMap();
		SDL_GL_SwapBuffers();
	}
}