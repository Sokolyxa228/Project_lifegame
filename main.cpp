#include "Grass.h"
#include "Sheep.h"
#include <SFML/Graphics.hpp>
#include "Obj.h"
#include <vector>
#include <ctime>

const vector<int> dx = {0, 0 , -1, 1};
const vector<int> dy = {-1, 1 , 0, 0};
int main() {
    srand(time(NULL));
    const int ROW = 40;
    const int COL = 60;
    const int SIZE = 20;
    const int COUNT_ALL_GRASS = 200;
    Obj field[ROW][COL];
    const int GRASS_COUNT = 40;
    const int SHEEP_COUNT = 10;
    int now_cnt_grass = 0;

    for (int i = 0; i < GRASS_COUNT;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        int mode = rand() % 2;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("grass", mode);
            now_cnt_grass++;
          //  cout << x << ' ' << y << endl;
            i++;
        }

    }
    for (int i = 0; i < SHEEP_COUNT;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("sheep");
            //now_cnt_grass++;
            //  cout << x << ' ' << y << endl;
            i++;
        }

    }
    sf::RenderWindow window(sf::VideoMode(COL*SIZE, ROW*SIZE), "Life game");

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
   
        //cout<<"1"<<"\n";
        window.clear();
        bool flag = false;
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));

                if (field[i][j].get_type() == "sheep")
                {
                    field[i][j] = Obj();
                    if (field[i][j].check_sheep_life()) {
                        field[i][j] = Obj();
                        continue;
                    }
                    while (true)
                    {
                        int new_x = i + dx[rand()%4];
                        int new_y = j + dy[rand()%4];
                        if (new_x < 0 || new_y < 0 || new_x >= ROW || new_y >= COL)
                        {
                            continue;
                        }

                        if (field[new_x][new_y].get_type() != "grass" && field[new_x][new_y].get_type() != "sheep" ) {
                            //field[i][j] = Obj();
                            field[new_x][new_y] = Obj("sheep");
                            shape.setPosition(new_y * SIZE, new_x * SIZE);
//                            window.draw(shape);
                            break;
                        }
                    }
                    shape.setFillColor(sf::Color::White);
                    shape.setPosition(j*SIZE, i*SIZE);
                    window.draw(shape);
                    field[i][j].sheep_update_life();
                }
                if (field[i][j].get_type() == "grass") {

                    if (field[i][j].check_life()) {
                        field[i][j] = Obj();
                        now_cnt_grass--;
                        continue;
                    }

                    if (field[i][j].get_kind()) {
                        shape.setFillColor(sf::Color::Red);
                    }
                    else {
                        shape.setFillColor(sf::Color::Green);
                    }


                    shape.setPosition(j*SIZE, i*SIZE);
                    window.draw(shape);
                  
                    if (field[i][j].get_age() == 0) {
                        field[i][j].update_life();
                        continue;

                    }
                    for (int k = 0; k < 4; k++)
                    {
                        if (now_cnt_grass == COUNT_ALL_GRASS) break;
                        int new_x = i + dx[k];
                        int new_y = j + dy[k];
                        if (new_x < 0 || new_y < 0 || new_x >= ROW || new_y >= COL || field[new_x][new_y].get_type() !="0")
                        {
                            continue;
                        }
                        
                        if (field[new_x][new_y].get_type() != "grass") {
                            field[new_x][new_y] = Obj("grass", field[i][j].get_kind());
                            shape.setPosition(new_y * SIZE, new_x * SIZE);
                            window.draw(shape);
                            //cout << "NEW " << i << ' ' << j << ' ' << new_x << ' ' << new_y << endl;
                            now_cnt_grass++;
                        }
                            
                        
                       // field[new_x][new_y].update_life();

                    }
                    field[i][j].update_life();

                    

//                    if (i + 1 < ROW && j-1 < COL) {
//                        if (field[i + 1][j-1].get_type() == "0" && field[i][j].get_type()=="grass") {
//                            field[1][j-1] = Obj("grass", field[i][j].get_kind());
//                        }
//                    }

                }
            }
        }

        
        window.display();
        sf::sleep(sf::seconds(1));
    }


    return 0;
}