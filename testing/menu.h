#pragma once
#include <iostream>
#include <windows.h> // ��� ������ � ��������
#include <conio.h> // ��� ������ � �������� ���������

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

protected: // ���������� ������
	enum ConsoleColor // �����
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

	void set_color(int text_color, int background_color) // ������� ��������� �����
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background_color << 4) | text_color));
	}

protected: // ����������� �������
	virtual void do_it(short int current_position); // ��� ����� ����������� ��� ������� ������� enter
	virtual void choice(); // ������� ������

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
	void do_it(short int current_position) final override; // ��� ����� ����������� ��� ������� ������� enter
	void choice() final override; // ������� ������

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

	void do_it(short int current_position) final override; // ��� ����� ����������� ��� ������� ������� enter
	void choice() final override; // ������� ������

public:
	void menu() final override;
};