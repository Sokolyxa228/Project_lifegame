﻿#include "Grass.h"
#include "Sheep.h"
#include <SFML/Graphics.hpp>
#include "Obj.h"
#include <vector>
#include <ctime>
using namespace std;
const vector<int> dx = {0, 0 , -1, 1};
const vector<int> dy = {-1, 1 , 0, 0};
const int ROW =17;
const int COL = 30;

//проверка на выход за границы массива
bool check_borders(int x, int y) {
    if (x < 0 || y < 0 || x >= ROW || y >= COL)
    {
        return true;
    }
    return false;
}


int main() {
    srand(time(NULL));
    const int SIZE = 50;
    const int COUNT_ALL_GRASS = 500;
    Obj field[ROW][COL];
    const int GRASS_COUNT = 200;
    const int SHEEP_COUNT_BOYS = 120; //gender=1
    const int SHEEP_COUNT_GIRLS = 120;//gender=0
    const int WOLF_COUNT_BOYS = 10; //gender=1
    const int WOLF_COUNT_GIRLS = 10;//gender=0
    int now_cnt_grass = 0, now_cnt_sheep = 0;
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
            now_cnt_sheep++;
            i++;
        }
    }
    for (int i = 0; i < SHEEP_COUNT_BOYS;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("sheep",0,1);
            field[x][y].set_sheep_flag(0);
            now_cnt_sheep++;
            i++;
        }
    }
    for (int i = 0; i < WOLF_COUNT_GIRLS;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("wolf", 0, 0);
            field[x][y].set_wolf_flag(0);
            i++;
        }
    }
    for (int i = 0; i < WOLF_COUNT_BOYS;) {
        int x = rand() % ROW;
        int y = rand() % COL;
        if (field[x][y].get_type() == "0") {
            field[x][y] = Obj("wolf",0,1);
            field[x][y].set_wolf_flag(0);
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
   
        
        window.clear(sf::Color{ 38, 32, 24 });
        
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
                sf::Texture image;
                sf::Sprite sprite;
                bool flag = true;
                int sheep_fail = 0;
                int wolf_fail = 0;
                string target = "";
                if (field[i][j].get_type() == "wolf")
                {
                    //cout << field[i][j].get_satiety() << endl;
                    if (field[i][j].check_wolf_life() || field[i][j].get_satiety_wolf() == 0) {
                        field[i][j] = Obj();
                        continue;
                    }
                    if (field[i][j].get_wolf_flag()==STEP && field[i][j].get_wolf_age() != 0) {
                        field[i][j].set_wolf_flag(0);
                        continue;
                    }

                    if (field[i][j].get_wolf_gender())
                        image.loadFromFile("image\\wolf_male.png");
                    else
                        image.loadFromFile("image\\wolf_female.png");
                    sprite.setTexture(image);
                    if (!field[i][j].ready_for_babes_wolf()) {
                        target = "sheep";
                    }
                    else {
                        target = "wolf";
                    }

                    while (true)
                    {
                        wolf_fail++;
                        int new_x = i + dx[rand()%4];
                        int new_y = j + dy[rand()%4];
                        if (wolf_fail == 16)
                        {
                            wolf_fail = 0;
                            if (target == "sheep") {
                                if (field[i][j].ready_for_babes_wolf())
                                    target = "sheep";
                                else
                                    target = "0";
                            }
                            else if (target == "wolf") {
                                target = "0";
                            }

                            else {
                                break;
                            }
                        }
                        if (check_borders(new_x,new_y))
                        {
                            continue;
                        }
                        if (field[new_x][new_y].get_type() != target) {
                            continue;
                        }
                        if (target == "sheep" || target=="0") {
                            field[new_x][new_y] = Obj("wolf", field[i][j].get_wolf_age(), field[i][j].get_wolf_gender());
                            if (target == "sheep") {
                                field[new_x][new_y].wolf_update_satiety();
                                now_cnt_sheep--;
                            }
                            field[new_x][new_y].set_wolf_flag(STEP);
                            sprite.setPosition(j* SIZE, i* SIZE);
                            window.draw(sprite);
                            flag = false;
                            field[new_x][new_y].wolf_update_life();
                            field[i][j] = Obj();
                            break;
                        }
                        else {
                            if (field[i][j].get_wolf_gender() == field[new_x][new_y].get_wolf_gender()) {
                                continue;
                            }
                            bool child_flag = false; //флаг для проверки есть ли место для рождения ребенка
                            for (int k = 0; k < 4; ++k) {
                                // координаты ребенка вокруг одного или другого родителя
                                int child_x1 = i + dx[k];
                                int child_y1 = j + dy[k];
                                int child_x2 = i + dx[k];
                                int child_y2 = j + dy[k];
                                if (check_borders(child_x1,child_y1))
                                {
                                    if (check_borders(child_x2, child_y2)) {
                                        continue;
                                    }
                                    else if (field[child_x2][child_y2].get_type() == "0") {
                                        field[child_x2][child_y2] = Obj("wolf", 0, rand() % 2);
                                        field[child_x2][child_y2].set_wolf_flag(0);
                                        child_flag = true;
                                        flag = false;
                                        field[i][j].wolf_update_life();
                                        break;
                                    }
                                }
                                else if (field[child_x1][child_y1].get_type() == "0") {
                                    field[child_x1][child_y1] =  Obj("wolf", 0, rand()%2);
                                    field[child_x1][child_y1].set_wolf_flag(0);

                                    child_flag = true;
                                    flag = false;
                                    field[i][j].wolf_update_life();
                                    break;
                                }

                            }

                            if (!child_flag)
                                continue;
                            else
                                break;
                        }
                    }



                    if (flag) {
                        sprite.setPosition(j* SIZE, i* SIZE);
                        window.draw(sprite);
                        field[i][j].wolf_update_life();

                    }



                }
                if (field[i][j].get_type() == "sheep")
                {
                    //cout << field[i][j].get_satiety() << endl;
                    if (field[i][j].check_sheep_life() || field[i][j].get_satiety() == 0) {
                        field[i][j] = Obj();
                        continue;
                    }
                    if (field[i][j].get_sheep_flag()==STEP && field[i][j].get_sheep_age() != 0) {
                        field[i][j].set_sheep_flag(0);
                        continue;
                    }
  
                    if (field[i][j].get_sheep_gender())
                        image.loadFromFile("image\\sheep_male.png");
                    else
                        image.loadFromFile("image\\sheep_female.png");
                    sprite.setTexture(image);

                    if (!field[i][j].ready_for_babes()) {
                        target = "grass";
                    }
                    else {
                        target = "sheep";
                    }

                    while (true)
                    {
                        sheep_fail++;
                        int new_x = i + dx[rand()%4];
                        int new_y = j + dy[rand()%4];
                        if (sheep_fail == 16)
                        {
                            sheep_fail = 0;
                            if (target == "grass") {
                                if (field[i][j].ready_for_babes())
                                    target = "sheep";
                                else
                                    target = "0";
                            }
                            else if (target == "sheep") {
                                target = "0";
                            }

                            else {
                                break;
                            }                                                       
                        }
                        if (check_borders(new_x,new_y))
                        {
                            continue;
                        }
                        if (field[new_x][new_y].get_type() != target) {
                            continue;
                        }
                        
                        
                        if (target == "grass" || target=="0") {
                            field[new_x][new_y] = Obj("sheep", field[i][j].get_sheep_age(), field[i][j].get_sheep_gender());
                            if (target == "grass") {
                                field[new_x][new_y].sheep_update_satiety(field[new_x][new_y].get_kind());
                                now_cnt_grass--;
                            }
                            field[new_x][new_y].set_sheep_flag(STEP);
                            sprite.setPosition(j* SIZE, i* SIZE);
                            window.draw(sprite);
                            flag = false;
                            field[new_x][new_y].sheep_update_life();
                            field[i][j] = Obj();
                            break;
                        }
                        else {
                            if (field[i][j].get_sheep_gender() == field[new_x][new_y].get_sheep_gender()) {
                                continue;
                            }
                            bool child_flag = false; //флаг для проверки есть ли место для рождения ребенка
                            for (int k = 0; k < 4; ++k) {
                                // координаты ребенка вокруг одного или другого родителя
                                int child_x1 = i + dx[k]; 
                                int child_y1 = j + dy[k];
                                int child_x2 = i + dx[k];
                                int child_y2 = j + dy[k];
                                if (check_borders(child_x1,child_y1))
                                {
                                    if (check_borders(child_x2, child_y2)) {
                                        continue;
                                    }
                                    else if (field[child_x2][child_y2].get_type() == "0") {
                                        field[child_x2][child_y2] = Obj("sheep", 0, rand() % 2);
                                        field[child_x2][child_y2].set_sheep_flag(0);
//                                        shape.setFillColor(sf::Color::Blue);
//                                        shape.setPosition(child_x2 * SIZE, child_y2* SIZE);
//                                        window.draw(shape);
                                        child_flag = true;
                                        flag = false;
                                        field[i][j].sheep_update_life();
                                        break;
                                    }
                                }
                                else if (field[child_x1][child_y1].get_type() == "0") {
                                    field[child_x1][child_y1] =  Obj("sheep", 0, rand()%2);
                                    field[child_x1][child_y1].set_sheep_flag(0);
//                                    shape.setFillColor(sf::Color::Blue);
//                                    shape.setPosition(child_x1 * SIZE, child_y1* SIZE);
//                                    window.draw(shape);
                                    child_flag = true;
                                    flag = false;
                                    field[i][j].sheep_update_life();
                                    break;
                                }

                            }
                            
                            if (!child_flag)
                                continue;
                            else
                                break;
                        }
                    }
                    

 
                    if (flag) {
                        sprite.setPosition(j* SIZE, i* SIZE);
                        window.draw(sprite);
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
                        image.loadFromFile("image\\grass_red.png");
                    }
                    else {
                        image.loadFromFile("image\\grass.png");
                    }


                    //shape.setPosition(j*SIZE, i*SIZE);
                    //window.draw(shape);
                                    
                                    
                   
                   sprite.setTexture(image);
                   sprite.setPosition(j* SIZE, i* SIZE);
                   window.draw(sprite);
                   if (field[i][j].get_age() == 0) {
                        field[i][j].update_life();
                        continue;

                    }
                    int grass_trap = 0;
                    while (true)
                    {
                        
                        if (grass_trap == 16)
                            break;
                        
                        if (now_cnt_grass == COUNT_ALL_GRASS) break;
                        int new_x = i + dx[rand() % 4];
                        int new_y = j + dy[rand() % 4];
                        if (check_borders(new_x,new_y) || field[new_x][new_y].get_type() != "0")
                        {
                            grass_trap++;
                            continue;
                        }
                        
                        if (field[new_x][new_y].get_type() != "grass") {
                            field[new_x][new_y] = Obj("grass", field[i][j].get_kind());
                            sprite.setPosition(j* SIZE, i* SIZE);
                            window.draw(sprite);
                            //cout << "NEW " << i << ' ' << j << ' ' << new_x << ' ' << new_y << endl;
                            now_cnt_grass++;
                            
                        }
                        grass_trap++;
                    }
                    field[i][j].update_life();                   
                }
            }
        }
        STEP++;

        //cout << STEP << "\n";
        window.display();
        sf::sleep(sf::seconds(1));
    }


    return 0;
}