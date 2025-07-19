/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Amplified.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:50:24 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/19 10:50:43 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Map/Amplified.hpp"
#include "../../Include/Noise/PerlinNoise.hpp"

Amplified::Amplified() : Map()
{
	gameMap();
}

Amplified::Amplified(int width, int height) : Map("Amplified", width, height)
{
    _map.resize(width);
    for (int x = 0; x < width; ++x)
    {
        _map[x].resize(height);
    }
    
    // Initialiser la grille 3D
    _depth = 16;
    _voxelMap.resize(width);
    for (int x = 0; x < width; ++x) {
        _voxelMap[x].resize(height);
        for (int y = 0; y < height; ++y) {
            _voxelMap[x][y].resize(_depth);
        }
    }
    
	gameMap();
}

Amplified::Amplified(const Amplified &amplified) : Map(amplified)
{
	if (*this != amplified)
		delete this;
	*this = amplified;
}

Amplified::~Amplified()
{
	// Cleanup if necessary
}

void Amplified::SetAllLandNeighbors(int x, int y, int z, Land *land) const
{
	if (!land) return;

	land->setNeighbor(0, (z > 0)         ? _voxelMap[x][y][z - 1]     : NULL);
	land->setNeighbor(1, (z < _depth-1)  ? _voxelMap[x][y][z + 1]     : NULL);
	land->setNeighbor(3, (x < _width-1)  ? _voxelMap[x + 1][y][z]     : NULL);
	land->setNeighbor(2, (x > 0)         ? _voxelMap[x - 1][y][z]     : NULL);
	land->setNeighbor(4, (y < _height-1) ? _voxelMap[x][y + 1][z]     : NULL);
	land->setNeighbor(5, (y > 0)         ? _voxelMap[x][y - 1][z]     : NULL);
}


void Amplified::generateColumn(int x, int y)
{
    static PerlinNoise pn;
    
    // Utilise plusieurs octaves de bruit pour plus de détail
    float noise1 = pn.noise(x * 0.05f, y * 0.05f, 0) * 6.0f;
    float noise2 = pn.noise(x * 0.1f, y * 0.1f, 0) * 3.0f;
    float noise3 = pn.noise(x * 0.2f, y * 0.2f, 0) * 1.5f;
    
    float totalNoise = noise1 + noise2 + noise3;
    int height = _depth / 2 + (int)totalNoise;
    
    if (height < 1) height = 1;
    if (height >= _depth) height = _depth - 1;
    
    for (int z = 0; z < _depth; z++)
	{
        if (z < height)
            _voxelMap[x][y][z] = createLandByHeight(height, x, y);
		else
            _voxelMap[x][y][z] = new Void(0, 1);
		
    }
    _voxelMap[x][y][0]->setHeight(height);
    _map[x][y] = _voxelMap[x][y][0];
}

Land* Amplified::createLandByHeight(int height, int x, int y)
{
    if (height <= 3)
        return new Water(x + y, 1);
    else if (height <= 7)
        return new Sand(x + y, 1);
    else
        return new Plains(x + y, 1);
}

Land* Amplified::getVoxel(int x, int y, int z) const
{
    if (x < 0 || x >= (int)_voxelMap.size() || 
        y < 0 || y >= (int)_voxelMap[0].size() || 
        z < 0 || z >= _depth)
	{
        return NULL;
    }
    return _voxelMap[x][y][z];
}

bool Amplified::hasVisibleFace(bool *drawface, Land* currentVoxel) const
{
	if (currentVoxel->isVoid())
		return false;

	for (int i = 0; i < 6; ++i)
	{
		if (currentVoxel->getNeighbor(i) == NULL)
			drawface[i] = false;
		else if (currentVoxel->getNeighbor(i)->isVoid())
			drawface[i] = true;
		else
			drawface[i] = false;
	}
	
	for (int i = 0; i < 6; ++i)
	{
		if (drawface[i])
			return true;
	}
	return false;
}

void Amplified::renderMap() const
{
    for (size_t x = 0; x < _voxelMap.size(); ++x)
	{
        for (size_t y = 0; y < _voxelMap[x].size(); ++y)
		{
            for (size_t z = 0; z < _voxelMap[x][y].size(); ++z)
			{
				Land* currentVoxel = _voxelMap[x][y][z];
				SetAllLandNeighbors(x, y, z, currentVoxel);
				if (!currentVoxel)
					continue;
                bool drawface[6] = { true, true, true, true, true, true };
                if (hasVisibleFace(drawface, currentVoxel))
                {
                    Vec3 position = { (float)x, (float)y, (float)z };
                    choiseColor(currentVoxel);
                    drawCube(position, 0.5f, 0.0f, drawface, currentVoxel);
                }
            }
        }
    }
}

void Amplified::gameMap()
{
    srand(time(NULL));
    
    std::cout << "=== GENERATING AMPLIFIED MAP ===" << std::endl;
    
    _depth = 16;
    
    for (size_t x = 0; x < _map.size(); ++x)
	{
        for (size_t y = 0; y < _map[x].size(); ++y)
		{
            generateColumn(x, y);
        }
    }
}