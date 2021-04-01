#ifndef STARMAP_H
#define STARMAP_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../config.hpp"
#include <random>
#include <vector>
#include <cmath>

class Starmap {
	private:
		struct Star {
			double x, y, z;
			sf::CircleShape body;
			sf::VertexArray trail;
			Star() = default;
			Star(double x, double y, double z, int p);
			~Star() = default;
		};

		// Mersenne twister for random positions and shapes
		std::mt19937 rd;
		std::uniform_real_distribution<double> dist_x;
		std::uniform_real_distribution<double> dist_y;
		std::uniform_real_distribution<double> dist_z;
		std::uniform_real_distribution<double> dist_p;

		std::vector<Star> stars;
		const std::vector<sf::Color> &palette;

	public:
		Starmap(const int sm_size, const int w_x, const int w_y, const std::vector<sf::Color> &palette);
		~Starmap() = default;
		void update(const sf::RenderWindow &window, const double &velocity, const double &rotation, const double &direction);
		void render(sf::RenderWindow &window, const double &velocity, const double &rotation, const double &direction);
};

#endif