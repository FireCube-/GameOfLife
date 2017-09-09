#include "Cell.h"

void Cell::show(sf::RenderWindow & window)
{
	//auto borders = drawBorders();
	//window.draw(borders);
	if (alive)
	{
		sf::RectangleShape rect (sf::Vector2f(SCALE, SCALE));
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(x * SCALE, y * SCALE);
		window.draw(rect);
	}
}

sf::VertexArray Cell::drawBorders()
{
	sf::VertexArray tmp_borders(sf::Lines, 8);
	for (int i = 0; i < tmp_borders.getVertexCount(); ++i) tmp_borders[i].color = sf::Color::Black;

	tmp_borders[0].position = sf::Vector2f(x * SCALE, y * SCALE);
	tmp_borders[1].position = sf::Vector2f((x + 1) * SCALE, y * SCALE);

	tmp_borders[2].position = sf::Vector2f((x + 1) * SCALE, y * SCALE);
	tmp_borders[3].position = sf::Vector2f((x + 1) * SCALE, (y + 1) * SCALE);

	tmp_borders[4].position = sf::Vector2f((x + 1) * SCALE, (y + 1) * SCALE);
	tmp_borders[5].position = sf::Vector2f(x * SCALE, (y + 1) * SCALE);

	tmp_borders[6].position = sf::Vector2f(x * SCALE, (y + 1) * SCALE);
	tmp_borders[7].position = sf::Vector2f(x * SCALE, y * SCALE);

	return tmp_borders;
}

