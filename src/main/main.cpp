// assignment_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "robot.h"
#include "war_robot.h"

#define sleep Sleep

using namespace std;
using namespace cv;

int main()
{
    float width = 60;
    float lenght = 120;
    Wheel wheel = {20, 80};

    auto robot = WarRobot(width, lenght, wheel);
    robot.setSpeed(10);
    robot.setAngularSpeed(0.1);
    robot.combatModule().setAngularSpeed(0.2);
    cout << robot.combatModule().angularSpeed() << endl;

    auto white = Scalar(0xFF, 0xFF, 0xFF);
    auto size = Size(1080, 720);
    auto area = Mat(size, CV_8UC3, white);
    
    robot.setArea(area);
    robot.setCenter(area);

    while (waitKey(1) != 27)
    {
        char key = waitKey(100);

        auto areaWithRobot = Mat(size, CV_8UC3, white);

        switch (key)
        {
            case 'w':
            case 'W':
            {
                robot.move(Direction::FORWARD);
                break;
            }
            case 's':
            case 'S':
            {
                robot.move(Direction::BACK);
                break;
            }
            case 'a':
            case 'A':
            {
                robot.move(Direction::LEFT);
                break;
            }
            case 'd':
            case 'D':
            {
                robot.move(Direction::RIGHT);
                break;
            }
            case 'q':
            case 'Q':
            {
                robot.go(Direction::FORWARD, Rotation::COUNTER_CLOCKWISE);
                break;
            }
            case 'e':
            case 'E':
            {
                robot.go(Direction::FORWARD, Rotation::CLOCKWISE);
                break;
            }
            case 'z':
            case 'Z':
            {
                robot.go(Direction::BACK, Rotation::CLOCKWISE);
                break;
            }
            case 'x':
            case 'X':
            {
                robot.go(Direction::BACK, Rotation::COUNTER_CLOCKWISE);
                break;
            }
            case '.':
            case '>':
            {
                robot.rotate(Rotation::CLOCKWISE);
                break;
            }
            case ',':
            case '<':
            {
                robot.rotate(Rotation::COUNTER_CLOCKWISE);
                break;
            }
            case ']':
            case '}':
            {
                robot.combatModule().rotate(Rotation::CLOCKWISE);
                break;
            }
            case '[':
            case '{':
            {
                robot.combatModule().rotate(Rotation::COUNTER_CLOCKWISE);
                break;
            }
            default:
            {
                break;
            }
        }

        robot.draw(areaWithRobot);

        imshow("Area", areaWithRobot);
        area = areaWithRobot;

        //cout << key << endl;
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
