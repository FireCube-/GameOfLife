#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Constants.h"

struct Cell
{
	int x = 0, y = 0;
	bool alive = false, alive_next = false;

	void show(sf::RenderWindow &window);

private:
	sf::VertexArray drawBorders();

};
