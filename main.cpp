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
	const int GRASS_COUNT = 5;

	for (int i = 0; i < GRASS_COUNT;) {
		int x = rand() % ROW;
		int y = rand() % COL;
		int mode = rand() % 2;
		if (field[x][y].get_type() == "0") {
			field[x][y] = Obj("grass", mode);
			i++;
		}

	} 
	sf::RenderWindow window(sf::VideoMode(COL*SIZE, ROW*SIZE), "Life game");

	int k = 0;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		k += 1;
		window.clear();
		bool flag = false;
		for (int j = 0; j < COL; ++j) {
			for (int i = 0; i < ROW; ++i) {
				if (field[i][j].get_type() == "grass") {
					sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
	
					if (field[i][j].check_life()) {
						field[i][j] = Obj();
                        continue;
					}
					if (field[i][j].get_type() != "0") {
						if (field[i][j].get_kind()) {
							shape.setFillColor(sf::Color::Red);
						}
						else {
							shape.setFillColor(sf::Color::Green);
						}
					}


					shape.setPosition(i*SIZE, j*SIZE);
					window.draw(shape);
					

					if (i + 1 < ROW && j-1 < COL) {
						if (field[i + 1][j-1].get_type() == "0" && field[i][j].get_type()=="grass") {
							field[i + 1][j-1] = Obj("grass", field[i][j].get_kind());
						}
					}
					field[i][j].update_life();
				}
			}
		}
		
		sf::sleep(sf::seconds(1));
		window.display();
	}


	return 0;
}