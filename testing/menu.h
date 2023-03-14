#pragma once
#include <iostream>
#include <windows.h> // для работы с консолью
#include <conio.h> // для работы с нажатыми клавишами

#include "admin.h"
#include "user.h"


class Menu
{
public:
	Menu();
	Menu(User* user);
	virtual ~Menu() = default;

protected:
	User* user;

	short int current_position;
	short int max_position;

protected: // постоянные методы
	enum ConsoleColor // цвета
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

	void set_color(int text_color, int background_color) // функция установки цвета
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background_color << 4) | text_color));
	}

protected: // виртуальные функции
	virtual void do_it(short int current_position); // что будет выполняться при нажатой клавише enter
	virtual void choice(); // функция выбора

public:
	virtual void menu();
};



class UserMenu : public Menu
{
public:
	UserMenu() = default;
	UserMenu(User* user);
	~UserMenu() final override = default;

protected:
	void do_it(short int current_position) final override; // что будет выполняться при нажатой клавише enter
	void choice() final override; // функция выбора

public:
	void menu() final override;
};





class AdminMenu : public Menu
{
public:
	AdminMenu() = default;
	AdminMenu(Admin* admin);

	~AdminMenu() final override = default;

protected:
	Admin* admin;

	void do_it(short int current_position) final override; // что будет выполняться при нажатой клавише enter
	void choice() final override; // функция выбора

public:
	void menu() final override;
};