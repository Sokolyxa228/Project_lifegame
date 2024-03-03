#include "Grass.h"
#include <SFML/Graphics.hpp>
#include "Obj.h"

#include <ctime>

int main() {
	srand(time(NULL));
	const int ROW = 40;
	const int COL = 60;
	const int SIZE = 20;
	Obj field[ROW][COL];
	const int GRASS_COUNT = 40;

	for (int i = 0; i < GRASS_COUNT;) {
		int x = rand() % ROW;
		int y = rand() % COL;
		if (field[x][y].get_type() == "0") {
			field[x][y] = Obj("grass");
			field[x][y].set_age();
			i++;
		}

	} 
	sf::RenderWindow window(sf::VideoMode(COL*SIZE, ROW*SIZE), "SFML works!");

	int k = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		k += 2;
		window.clear();
		for (int i = 0; i < COL; ++i) {
			for (int j = 0; j < ROW; ++j) {
				if (field[j][i].get_type() == "grass") {
					sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));

					if (field[j][i].check_life()) {
						field[j][i] = Obj();
					}
					shape.setFillColor(sf::Color::Green);
					shape.setPosition(i*SIZE, j*SIZE);
					window.draw(shape);
					field[j][i].update_life();
					
				}
			}
		}
		
		sf::sleep(sf::seconds(1));
		window.display();
	}


	return 0;
}