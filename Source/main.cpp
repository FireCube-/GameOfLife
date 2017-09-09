#include <SFML\Graphics.hpp>
#include <vector>

#include "Constants.h"
#include "Cell.h"

std::vector<std::vector<Cell>> setupCells();
int getAliveCount(const Cell & curr, const std::vector<std::vector<Cell>>& cells);
void determineNextState(Cell & curr, const std::vector<std::vector<Cell>>& cells);
void updateAlive(Cell &curr);
sf::VertexArray setupGrid();

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");
	window.setFramerateLimit(15);

	auto cells = setupCells();
	auto grid = setupGrid();
	bool on = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!on && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			on = true;
		else if (on && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			on = false;
		
		if (!on)
		{
			window.clear(sf::Color::White);
			window.draw(grid);

			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			int x = (mousePos.x - mousePos.x % 10) / SCALE;
			int y = (mousePos.y - mousePos.y % 10) / SCALE;

			if (x >= 0 && y >= 0 && x <= GRID_X - 1 && y <= GRID_Y - 1)
			{
				if (!cells[y][x].alive && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					cells[y][x].alive = true;
				else if (cells[y][x].alive && sf::Mouse::isButtonPressed(sf::Mouse::Right))
					cells[y][x].alive = false;
			}

			for (auto &row : cells)
				for (auto &col : row)
					col.show(window);

			window.display();
		}
		
		if (on)
		{
			window.clear(sf::Color::White);
			window.draw(grid);

			for (auto &row : cells) {
				for (auto &col : row) {
					determineNextState(col, cells);
					col.show(window);
				}
			}

			for (auto &row : cells)
				for (auto &col : row)
					updateAlive(col);

			window.display();
		}
		
	}

}

int getAliveCount(const Cell & curr, const std::vector<std::vector<Cell>>& cells)
{
	int xx = curr.x, yy = curr.y;
	int n = 0;

	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (xx + dx < 0 || xx + dx > GRID_X - 1 || yy + dy < 0 || yy + dy > GRID_Y - 1 || (dx == 0 && dy == 0)) continue;
			if (cells[yy + dy][xx + dx].alive) ++n;
		}
	}
	return n;
}

void determineNextState(Cell & curr, const std::vector<std::vector<Cell>>& cells)
{
	int n = getAliveCount(curr, cells);
	if (curr.alive && n < 2)
		curr.alive_next = false;
	else if (curr.alive && (n == 2 || n == 3))
		curr.alive_next = true;
	else if (curr.alive && n > 3)
		curr.alive_next = false;
	else if (!curr.alive && n == 3)
		curr.alive_next = true;
}

void updateAlive(Cell &curr)
{
	curr.alive = curr.alive_next;
	curr.alive_next = false;
}

sf::VertexArray setupGrid()
{
	sf::VertexArray tmp(sf::Lines, 2 * (GRID_X + GRID_Y));
	int n = 0;
	for (int i = 0; i < 2 * GRID_X; i+=2)
	{
		tmp[i].color = sf::Color::Black;
		tmp[i].position = sf::Vector2f(n * SCALE, 0);
		tmp[i + 1].color = sf::Color::Black;
		tmp[i + 1].position = sf::Vector2f(n * SCALE, HEIGHT);
		++n;
	}
	n = 0;
	for (int j = 0; j < 2 * GRID_Y - 1; j+=2)
	{
		tmp[2 * GRID_X + j].color = sf::Color::Black;
		tmp[2 * GRID_X + j].position = sf::Vector2f(0, n * SCALE);
		tmp[2 * GRID_X + j + 1].color = sf::Color::Black;
		tmp[2 * GRID_X + j + 1].position = sf::Vector2f(WIDTH, n * SCALE);
		++n;
	}
	return tmp;
}

std::vector<std::vector<Cell>> setupCells()
{
	std::vector<Cell> tmp_cells(GRID_X);
	std::vector<std::vector<Cell>> cells(GRID_Y, tmp_cells);

	for (int row = 0; row < cells.size(); row++)
	{
		for (int col = 0; col < cells[row].size(); col++)
		{
			cells[row][col].x = col;
			cells[row][col].y = row;
		}
	}

	return cells;
}
