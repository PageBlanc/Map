/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mainland.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:35:20 by pageblanche       #+#    #+#             */
/*   Updated: 2025/07/19 01:03:29 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map/Mainland.hpp"
#include "Land/Plains.hpp"
#include "Land/Water.hpp"
#include "Land/Sand.hpp"

/*-------------------------------------CONSTRUCTORS-------------------------------------*/

Mainland::Mainland() : Map()
{
	gameMap();
}

Mainland::Mainland(int x, int y) : Map("Mainland", x, y)
{
	gameMap();
}

Mainland::Mainland(const Mainland &mainland) : Map(mainland)
{
	*this = mainland;
}

/*-------------------------------------SETTERS-------------------------------------*/


void		Mainland::setAllNearLands()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			std::vector<Land *> nearLands;
			if (i - 1 >= 0)
				nearLands.push_back(_map[i - 1][j]);
			if (i + 1 < _width)
				nearLands.push_back(_map[i + 1][j]);
			if (j - 1 >= 0)
				nearLands.push_back(_map[i][j - 1]);
			if (j + 1 < _height)
				nearLands.push_back(_map[i][j + 1]);
			if (i - 1 >= 0 && j - 1 >= 0)
				nearLands.push_back(_map[i - 1][j - 1]);
			if (i + 1 < _width && j + 1 < _height)
				nearLands.push_back(_map[i + 1][j + 1]);
			if (i - 1 >= 0 && j + 1 < _height)
				nearLands.push_back(_map[i - 1][j + 1]);
			if (i + 1 < _width && j - 1 >= 0)
				nearLands.push_back(_map[i + 1][j - 1]);
			setNearLands(*_map[i][j], nearLands);
		}
	}
}

/*-------------------------------------GENERATE-------------------------------------*/


void		Mainland::gameMap()
{
	srand(static_cast<unsigned int>(time(0)));
	initMap();
	generatePerlinMap();
	setAllNearLands();
	for (int i = 0; i < _width / (rand() % 10 + 1); i++)
		connectLand();
	PutSand();
}

int			Mainland::countNearSameLand(int x, int y, int width, std::string type, int random_value)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i < 0 || j < 0 || i >= width || j >= _height)
				continue;
			if (_map[i][j]->getType() == type && random_value % 100 < 57)
				count++;
		}
	}
	return count;
}

void		Mainland::initMap()
{
	_map.resize(_width);
	for (int i = 0; i < _width; i++)
	{
		_map[i].resize(_height);
		for (int j = 0; j < _height; j++)
			_map[i][j] = new Land();
	}
}

void	Mainland::connectLand()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_map[i][j]->getType() == "Water")
			{
				if (countNearSameLand(i, j, _width, "Plains", rand()) > 2)
				{
					delete _map[i][j];
					_map[i][j] = new Plains(i, 10);
				}
			}
			else if (_map[i][j]->getType() == "Plains")
			{
				if (countNearSameLand(i, j, _width, "Water", rand()) > 3)
				{
					delete _map[i][j];
					_map[i][j] = new Water(i, 10);
				}
			}
		}
	}
}

float Mainland::radialGradient(int x, int y) {
	// Calcul de la distance depuis le centre
	float dx = (2.0f * x / _width) - 1.0f;
	float dy = (2.0f * y / _height) - 1.0f;
	float distance = sqrt(dx * dx + dy * dy);

	// Créer un dégradé qui diminue vers les bords
	return 1.0f - pow(distance, 4.0f);  // Carré pour un dégradé plus doux
}

float Mainland::perlinNoise(float x, float y) {
	float p = 0.3f + static_cast<float>(rand()) / RAND_MAX * 0.2f;
	int n = 5;
	float freq = 1.0f;
	float amp = 1.0f;
	float total = 0.0f;
	float max = 0.0f;

	for (int i = 0; i < n; i++) {
		total += glm::perlin(glm::vec2(x, y) * freq) * amp;
		max += amp;
		amp *= p;
		freq *= 2.0f;
	}
	if (max == 0.0f)
		return 0.0f;
	return total / max;
}

void Mainland::generatePerlinMap() {
	float frequency = 0.05f + static_cast<float>(rand()) / RAND_MAX * 0.05f;
	float amplitude = 1.0f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
	float distortionStrength = 0.02f + static_cast<float>(rand()) / RAND_MAX * 0.03f;
	glm::vec2 center(_width / 2.0f + rand() % 11 - 5, _height / 2.0f + rand() % 11 - 5);

	for (int x = 0; x < _width; ++x) {
		for (int y = 0; y < _height; ++y) {
			glm::vec2 pos(y, x);
			float distance = glm::length(center - pos);
			float noiseX = y + glm::perlin(glm::vec2(y * distortionStrength, x * distortionStrength));
			float noiseY = x + glm::perlin(glm::vec2(y * distortionStrength, x * distortionStrength));
			float perlinValue = glm::perlin(glm::vec2(noiseX, noiseY) * frequency) * amplitude;

			// Application du dégradé radial
			float gradient = radialGradient(x, y);
			float heightValue = perlinValue * gradient;

			// Utilisation d'une valeur de contrôle pour influencer les zones hautes/basses
			float controlValue = 1.0f - (distance / glm::length(glm::vec2(_width, _height) / 2.0f));
			heightValue *= controlValue;

			if (heightValue > 0.1f) {
				delete _map[x][y];
				_map[x][y] = new Plains(y, 10);
			} else {
				delete _map[x][y];
				_map[x][y] = new Water(y, 10);
			}
		}
	}
}

void	Mainland::PutSand()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_map[i][j]->getType() == "Water")
			{
				if (i > 0 && _map[i - 1][j]->getType() == "Plains")
				{
					delete _map[i][j];
					_map[i][j] = new Sand(i, 10);
				}
				if (i < _width - 1 && _map[i + 1][j]->getType() == "Plains")
				{
					delete _map[i][j];
					_map[i][j] = new Sand(i, 10);
				}
				if (j > 0 && _map[i][j - 1]->getType() == "Plains")
				{
					delete _map[i][j];
					_map[i][j] = new Sand(i, 10);
				}
				if (j < _height - 1 && _map[i][j + 1]->getType() == "Plains")
				{
					delete _map[i][j];
					_map[i][j] = new Sand(i, 10);
				}
			}
		}
	}
}

/*-------------------------------------OPERATOR-------------------------------------*/

Mainland &Mainland::operator=(const Mainland &mainland)
{
	if (this != &mainland)
	{
		_map = mainland._map;
	}
	return *this;
}

/*-------------------------------------DESTRUCTOR-------------------------------------*/

Mainland::~Mainland()
{
	if (_map.size() == 0)
		return;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
			delete _map[i][j];
	}
}