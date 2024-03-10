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
    const int SHEEP_COUNT_BOYS = 10; //gender=1
    const int SHEEP_COUNT_GIRLS = 10; //gender=0
    int now_cnt_grass = 0;
    int STEP = 1;//для проверки хода овцы
    for (int i = 0; i < GRASS_COUNT;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        int mode = rand() % 2;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("grass", mode);
            now_cnt_grass++;
            i++;
        }

    }
    for (int i = 0; i < SHEEP_COUNT_GIRLS;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("sheep", 0, 0);
            field[x][y].set_sheep_flag(0);
            i++;
        }
    }
    for (int i = 0; i < SHEEP_COUNT_BOYS;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("sheep",0,1);
            field[x][y].set_sheep_flag(0);
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
   
       // cout<<"1"<<"\n";
        window.clear(sf::Color{ 38, 32, 24 });
        
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
                bool flag = true;
                int sheep_trap = 0, did_not_eat = 0;
                if (field[i][j].get_type() == "sheep")
                {
                    if (field[i][j].check_sheep_life() || field[i][j].get_satiety() == 0) {
                        field[i][j] = Obj();
                        continue;
                    }
                    if (field[i][j].get_sheep_flag()==STEP && field[i][j].get_sheep_age() != 0) {
                        field[i][j].set_sheep_flag(0);
                        continue;
                    }
                    if (field[i][j].get_satiety() > 7)
                    {
                        field[i][j].change_in_love(1);
                    }
                    if (field[i][j].get_sheep_gender())
                        shape.setFillColor(sf::Color::White);
                    else
                        shape.setFillColor(sf::Color{ 209, 23, 178 });
                    if (field[i][j].get_satiety() < 5)
                    {
                        int check = 0;
                        while (true)
                        {
                            check++;
                            int new_x = i + dx[rand()%4];
                            int new_y = j + dy[rand()%4];
                            if (check == 16)
                            {
                                did_not_eat = 1;
                                break;
                            }
                            if (new_x < 0 || new_y < 0 || new_x >= ROW || new_y >= COL || field[new_x][new_y].get_type() != "grass")
                            {
                                continue;
                            }
                            field[new_x][new_y] = Obj("sheep",field[i][j].get_sheep_age(),field[i][j].get_sheep_gender());
                            field[i][j].sheep_update_satiety();
                            field[new_x][new_y].set_sheep_flag(STEP);
                            shape.setPosition(new_y * SIZE, new_x * SIZE);
                            //cout << new_y << ' ' << new_x << ' ' << j << ' ' << i << endl;
                            window.draw(shape);
                            flag = false;
//                          window.draw(shape);
                            field[new_x][new_y].sheep_update_life();
                            field[i][j] = Obj();
                        }
                    }
                    if (field[i][j].ready_for_babes())
                    {
                        int check = 0;
                        while (true)
                        {
                            check++;
                            int new_x = i + dx[rand()%4];
                            int new_y = j + dy[rand()%4];
                            if (check == 16)
                            {
                                did_not_eat = 1;
                                break;
                            }
                            if (new_x < 0 || new_y < 0 || new_x >= ROW || new_y >= COL || field[new_x][new_y].get_type() != "sheep")
                            {
                                continue;
                            }
                            field[new_x][new_y] = Obj("sheep",field[i][j].get_sheep_age(),field[i][j].get_sheep_gender());
                            field[i][j].change_in_love(0);
                            field[new_x][new_y].set_sheep_flag(STEP);
                            shape.setPosition(new_y * SIZE, new_x * SIZE);
                            //cout << new_y << ' ' << new_x << ' ' << j << ' ' << i << endl;
                            window.draw(shape);
                            flag = false;
//                          window.draw(shape);
                            field[new_x][new_y].sheep_update_life();
                            field[i][j] = Obj();
                        }
                    }
                    if ( (field[i][j].get_satiety() > 5 && field[i][j].ready_for_babes() == 0) || (did_not_eat)) {
                        while (true) {
                            //тут надо менять
                            int new_x = i + dx[rand() % 4];
                            int new_y = j + dy[rand() % 4];
                            sheep_trap++;
                            if (sheep_trap == 16) {
                                break;

                            }
                            if (new_x < 0 || new_y < 0 || new_x >= ROW || new_y >= COL) {
                                continue;
                            }
                            field[new_x][new_y] = Obj("sheep", field[i][j].get_sheep_age(),
                                                      field[i][j].get_sheep_gender());
                            field[new_x][new_y].set_sheep_flag(STEP);
                            shape.setPosition(new_y * SIZE, new_x * SIZE);
                            window.draw(shape);
                            flag = false;
//                            window.draw(shape);
                            field[new_x][new_y].sheep_update_life();
                            field[i][j] = Obj();
                            break;
                        }
                    }
                    if (flag) {
                        shape.setPosition(j * SIZE, i * SIZE);
                        window.draw(shape);
                        field[i][j].sheep_update_life();
                        
                    }
                    

                    
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
                    int grass_trap = 0;
                    while (true)
                    {
                        if (grass_trap == 10)
                            break;
                        
                        if (now_cnt_grass == COUNT_ALL_GRASS) break;
                        int new_x = i + dx[rand() % 4];
                        int new_y = j + dy[rand() % 4];
                        if (new_x < 0 || new_y < 0 || new_x >= ROW || new_y >= COL || field[new_x][new_y].get_type() !="0")
                        {
                            grass_trap++;
                            continue;
                        }
                        
                        if (field[new_x][new_y].get_type() != "grass") {
                            field[new_x][new_y] = Obj("grass", field[i][j].get_kind());
                            shape.setPosition(new_y * SIZE, new_x * SIZE);
                            window.draw(shape);
                            //cout << "NEW " << i << ' ' << j << ' ' << new_x << ' ' << new_y << endl;
                            now_cnt_grass++;
                            break;
                        }
                        grass_trap++;

                        
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
        STEP++;

        
        window.display();
        sf::sleep(sf::seconds(0.5));
    }


    return 0;
}