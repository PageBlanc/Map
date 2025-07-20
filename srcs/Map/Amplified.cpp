/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Amplified.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:50:24 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/20 13:45:41 by axdubois         ###   ########.fr       */
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
    _depth = 50; // Set a default depth, can be adjusted as needed
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

double Amplified::createCliffs(double height, int x, int y)
{
    PerlinNoise noise(_seed + 1000);
    
    double cliffNoise = noise.noise((double)x * 0.08, (double)y * 0.08);
    if (cliffNoise > 0.3)
    {
        height = height + (cliffNoise - 0.3) * 25;
        height = floor(height / 4) * 4;
    }
    
    return height;
}


void Amplified::generateColumn(int x, int y)
{
    PerlinNoise noise(_seed);

    double scale[3] = { 0.05, 0.15, 0.3 };
    double height[3] =
    {
        noise.noise(x * scale[0], y * scale[0]) ,
        noise.noise(x * scale[1], y * scale[1]) ,
        noise.noise(x * scale[2], y * scale[2]) 
    };

    double totalHeight = height[0] + height[1] * 0.5 + height[2] * 0.25;
    totalHeight = createCliffs(totalHeight, x, y);

    if (totalHeight < 1) totalHeight = 1;
    if (totalHeight > _depth) totalHeight = _depth;

    for (int z = 0; z < _depth; z++)
	{
        if (z < totalHeight)
            _voxelMap[x][y][z] = createLandByHeight(totalHeight, z, x, y);
		else
            _voxelMap[x][y][z] = new Void(0, 1);
		
    }
    _voxelMap[x][y][0]->setHeight(totalHeight);
    _map[x][y] = _voxelMap[x][y][0];
}

Land* Amplified::createLandByHeight(double height, int currentZ, int x, int y)
{
    (void)currentZ; 
    if (height <= 3)
        return new Water(x + y, 1);
    else if (height <= 6)
        return new Sand(x + y, 1);
    else if (height <= 10)
        return new Plains(x + y, 1);
    else    
        return new Mountain(x + y, 1);
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

void Amplified::renderMap(Vec3 cameraPos) const
{
    Vec3 adjustedCameraPos = Vec3(
        abs(cameraPos.x),
        abs(cameraPos.y),
        abs(cameraPos.z)
    );
    
    int renderDistance = MAX_RENDER_DISTANCE;
    if (DEBUG == 1)
    {
        std::cout << "=== RENDERING AMPLIFIED MAP ===" << std::endl;
        std::cout << "Camera Position: " << adjustedCameraPos.x << ", " << adjustedCameraPos.y << ", " << adjustedCameraPos.z << std::endl;
        std::cout << "Render Distance: " << renderDistance << std::endl;
        std::cout <<  "render area: " << 
            "X: [" << adjustedCameraPos.x - renderDistance << ", " << adjustedCameraPos.x + renderDistance << "], " <<
            "Y: [" << adjustedCameraPos.y - renderDistance << ", " << adjustedCameraPos.y + renderDistance << "], " <<
            "Z: [0, " << _depth - 1 << "]" << std::endl;
        
    }
    for (int x = adjustedCameraPos.x - renderDistance < 0 ? 0 : adjustedCameraPos.x - renderDistance; x < adjustedCameraPos.x + renderDistance && x < _width; ++x)
    {
        for (int y = adjustedCameraPos.y - renderDistance < 0 ? 0 : adjustedCameraPos.y - renderDistance; y < adjustedCameraPos.y + renderDistance && y < _height; ++y)
        {
            for (int z = 0; z < _depth; ++z)
            {
                if (z < 0 || z >= _depth) continue;
                Land* currentVoxel = _voxelMap[x][y][z];
                if (!currentVoxel) continue;

                bool drawface[6] = { true, true, true, true, true, true };
                if (!hasVisibleFace(drawface, currentVoxel))
                    continue;

                Vec3 voxpos = Vec3(
                    x,
                    y,
                    z
                );

                float dist = (voxpos - adjustedCameraPos).length();
                if (dist > renderDistance * VOXEL_SIZE * SCALE) continue;

                Vec3 position = Vec3(
                    x * VOXEL_SIZE * SCALE,
                    y * VOXEL_SIZE * SCALE,
                    z * VOXEL_SIZE * SCALE
                );

                drawCube(position, VOXEL_SIZE * SCALE, 0.0f, drawface, currentVoxel, _light);
            }
        }
    }
}

void Amplified::gameMap()
{
    srand(time(NULL));
    
    std::cout << "=== GENERATING AMPLIFIED MAP ===" << std::endl;
    
    for (size_t x = 0; x < _map.size(); ++x)
	{
        for (size_t y = 0; y < _map[x].size(); ++y)
		{
            generateColumn(x, y);
        }
    }

    for (size_t x = 0; x < _voxelMap.size(); ++x)
        for (size_t y = 0; y < _voxelMap[x].size(); ++y)
            for (size_t z = 0; z < _voxelMap[x][y].size(); ++z)
                SetAllLandNeighbors(x, y, z, _voxelMap[x][y][z]);
}