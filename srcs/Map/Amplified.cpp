/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Amplified.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:50:24 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/21 13:51:07 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Map/Amplified.hpp"
#include "../../Include/Noise/PerlinNoise.hpp"

Amplified::Amplified() : Map()
{
	//calculate time to generate the map c++98
	clock_t start = clock();
	gameMap();
	clock_t end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken to generate map: " << time_taken << " seconds" << std::endl;
}

Amplified::Amplified(int width, int height) : Map("Amplified", width, height)
{
	_depth = 25;
	
    _map.resize(width);
    for (int x = 0; x < width; ++x)
    {
        _map[x].resize(height);
    }
    
    _voxelMap.resize(width);
    for (int x = 0; x < width; ++x)
	{
        _voxelMap[x].resize(height);
        for (int y = 0; y < height; ++y)
		{
            _voxelMap[x][y].resize(_depth);
        }
    }
    
	clock_t start = clock();
	gameMap();
	clock_t end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken to generate map: " << time_taken << " seconds" << std::endl;
}

Amplified::Amplified(const Amplified &amplified) : Map(amplified)
{
	if (*this != amplified)
		delete this;
	*this = amplified;
}

void Amplified::cleanup()
{
	for (int x = 0; x < _width; ++x)
		for (int y = 0; y < _height; ++y)
			for (int z = 0; z < _depth; ++z)
				delete _voxelMap[x][y][z];
}

Amplified::~Amplified()
{
	cleanup();
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
    
    double cliffNoise = noise.noise((double)x * 0.05, (double)y * 0.05);
    double ridgeNoise = noise.noise((double)x * 0.12, (double)y * 0.12);
    
    if (cliffNoise > 0.2)
    {
        double intensity = (cliffNoise - 0.2) * 2.0;
        height += intensity * 15;
        
        if (ridgeNoise > 0.4)
            height = floor(height / 3) * 3;
    }
    
    return height;
}

void Amplified::generateColumn(int x, int y)
{
    static PerlinNoise noise(_seed + 5000);
	static PerlinNoise biomeNoise(_seed + 6000);
	static PerlinNoise caveNoise(_seed + 3000);
	
    if (DEBUG == 1)
        std::cout << "seed" << _seed << std::endl;

    double scale[3] = { 0.01, 0.03, 0.07 };
        
    double height[3] =
    {
        noise.noise(x * scale[0], y * scale[0]) ,
        noise.noise(x * scale[1], y * scale[1]) ,
        noise.noise(x * scale[2], y * scale[2]) 
    };

	double temperature = biomeNoise.noise(x * 0.02, y * 0.02);

    double totalHeight = height[0] - 1.2 + height[1] * 0.4 + height[2] * 0.1;
    totalHeight = (totalHeight + 1.0) * 0.5;
    totalHeight *= (_depth * 0.8);
    totalHeight = createCliffs(totalHeight, x, y);

    if (totalHeight < 1) totalHeight = 1;
    if (totalHeight > _depth) totalHeight = _depth;

    for (int z = 0; z < _depth; ++z)
    {
        if (z < totalHeight)
        {
            if (caveNoise.noise(x * 0.08, y * 0.08, z * 0.08) > 0.5 && z > 2 && z < _depth - 2)
                _voxelMap[x][y][z] = new Void(x, y, z, 0);
            else
                _voxelMap[x][y][z] = createLandByDepth(x, y, z, totalHeight, temperature);
        }
        else
            _voxelMap[x][y][z] = new Void(x, y, z, 0);
    }
}

Land* Amplified::createLandByDepth(int x, int y, int currentZ, double totalHeight, double temperature)
{
    // Génération par couches selon la profondeur
    if (currentZ == 0)
    {
        // Couche de surface selon la hauteur totale
        if (totalHeight <= 2)
            return new Water(x, y, currentZ, totalHeight);
        else if (totalHeight <= 5)
            return new Sand(x, y, currentZ, totalHeight);
        else if (totalHeight <= 12)
        {
            if (temperature > 0.3)
                return new Plains(x, y, currentZ, totalHeight);
            else
                return new Ice(x, y, currentZ, totalHeight);
        }
        else if (totalHeight <= 20)
            return new Hill(x, y, currentZ, totalHeight);
        else
            return new Mountain(x, y, currentZ, totalHeight);
    }
    else if (currentZ < totalHeight * 0.1) // 10% supérieur = terre/sable
    {
        return new Sand(x, y, currentZ, totalHeight);
    }
    else if (currentZ < totalHeight * 0.8) // 80% = roche
    {
        return new Hill(x, y, currentZ, totalHeight); // ou Stone si tu en as
    }
    else // Fond = montagne/roche dure
    {
        return new Mountain(x, y, currentZ, totalHeight);
    }
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
        abs(cameraPos.x) / VOXEL_SIZE * SCALE / 2,
        abs(cameraPos.y) / VOXEL_SIZE * SCALE / 2,
        abs(cameraPos.z) / VOXEL_SIZE * SCALE / 2
    );

    int renderDistance = MAX_RENDER_DISTANCE * VOXEL_SIZE; // Adjust render distance based on scale
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
    for (int x = std::max(0, (int)(adjustedCameraPos.x) - renderDistance); x < std::min(_width, (int)(adjustedCameraPos.x) + renderDistance); ++x)
    {
        for (int y = std::max(0, (int)(adjustedCameraPos.y) - renderDistance); y < std::min(_height, (int)(adjustedCameraPos.y) + renderDistance); ++y)
        {
            for (int z = 0; z < _depth; ++z)
            {
                Land* currentVoxel = _voxelMap[x][y][z];
                if (!currentVoxel) continue;

                Vec3 voxpos = Vec3( x, y, z );
                float dist = (voxpos - adjustedCameraPos).length();
                if (dist > renderDistance) continue;
                
                bool drawface[6] = { true, true, true, true, true, true };
                if (!hasVisibleFace(drawface, currentVoxel))
                    continue;

                drawCube(voxpos * (2 * VOXEL_SIZE), VOXEL_SIZE, 0.0f, drawface, currentVoxel, _light);
            }
        }
    }
}

void Amplified::gameMap()
{
    srand(time(NULL));
    _seed = rand() % 10000;
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