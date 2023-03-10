#include <iostream>
#include <string>
#include <ctime> // для работы со временем
#include <windows.h> // для работы с консолью
#include <conio.h> // для работы _getch()

#include "admin.h"
#include "user.h"


Admin admin;
User user;


int current_position = 0;
int max_position = 3;


enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};


void set_color(int text_color, int background_color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background_color << 4) | text_color));
}


void go(short int current_position)
{
	switch (current_position)
	{
		case 0: system("cls"); user.old_user(); break;
		case 1: system("cls"); user.new_user(); break;
		case 2: exit(0);
	}
}

void menu();

void choice() // функция выбора
{
	short int pressed_button;
	while (true)
	{
		pressed_button = _getch(); // считывание значения нажатой клавиши

		switch (pressed_button)
		{
		case 80: if (current_position + 1 < max_position) { ++current_position; }; menu(); return; // нажта клавиша вниз
		case 72: if (current_position - 1 >= 0) { --current_position; }; menu(); return; // нажата клавиша вверх
		case 13: go(current_position); return; // нажата клавиша enter

		default: break;
		}
	}
}


void menu()
{
	system("cls");
	set_color(2, 0); std::cout << "ПРОГРАММА ДЛЯ ПРОХОЖДЕНИЯ ТЕСТОВ" << std::endl; set_color(15, 0);

	if (current_position == 0)
	{
		set_color(6, 0); std::cout << "> вход" << std::endl; set_color(15, 0);
		std::cout << "  регистрация" << std::endl;
		std::cout << "  выход" << std::endl;

		choice();
	}

	if (current_position == 1)
	{
		std::cout << "  вход" << std::endl;
		set_color(6, 0); std::cout << "> регистрация" << std::endl; set_color(15, 0);
		std::cout << "  выход" << std::endl;

		choice();
	}

	if (current_position == 2)
	{
		std::cout << "  вход" << std::endl;
		std::cout << "  регистрация" << std::endl; 
		set_color(6, 0); std::cout << "> выход" << std::endl; set_color(15, 0);

		choice();
	}
}



int main()
{
	setlocale(LC_ALL, "rus");

	system("cls");

	menu();

	//Admin admin;
	//User user;

	//short int pressed_button = 0; // нажатая кнопка
	//short int current_position = 0; // текущая позиция

	//std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
	//std::cout << "> вход" << std::endl;
	//std::cout << "  регистрация" << std::endl;

	//while (true)
	//{
	//	pressed_button = _getch();

	//	if (pressed_button == 72) // если была нажата клавиша вверх (ВХОД)
	//	{
	//		current_position = 1;

	//		system("cls");
	//		std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
	//		std::cout << "> вход" << std::endl;
	//		std::cout << "  регистрация" << std::endl;

	//		pressed_button = _getch();
	//		if (pressed_button == 13) // если была нажата кнопка enter
	//		{
	//			system("cls");
	//			user.old_user();
	//		}
	//	}

	//	if (pressed_button == 80) // если была нажата клавиша вниз (РЕГИСТРАЦИЯ)
	//	{
	//		current_position = 0;

	//		system("cls");
	//		std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
	//		std::cout << "  вход" << std::endl;
	//		std::cout << "> регистрация" << std::endl;

	//		pressed_button = _getch();
	//		if (pressed_button == 13) // если была нажата кнопка enter
	//		{
	//			system("cls");
	//			user.new_user();
	//		}
	//	}


	//}




	return 0;
}