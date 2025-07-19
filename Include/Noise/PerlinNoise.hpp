/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PerlinNoise.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:47:52 by axdubois          #+#    #+#             */
/*   Updated: 2025/07/18 18:55:17 by axdubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

class PerlinNoise {
private:
    std::vector<int> p;

public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    ~PerlinNoise();
    
    double noise(double x, double y, double z = 0.0);
    
private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    void shuffle(std::vector<int>& vec, unsigned int seed);
};

#endif

