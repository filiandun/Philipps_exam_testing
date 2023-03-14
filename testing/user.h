#pragma once
#include <iostream>
#include <string>
#include <fstream> // для работы с файлами
#include <filesystem> // для работы с папкам
#include <stdlib.h> // для работы _itoa_s()
#include <exception> // для работы с ошибками
#include <conio.h> // для работы с нажатыми клавишами
#include <windows.h> // для работы с консолью


class User
{
public:
	User() = default;
	User(std::string path); // ДУМАЮ, ЧТО ПРИ ПЕРВОМ ЗАПУСКЕ, У АДМИНА НУЖНО СПРАШИВАТЬ, КУДА СОХРАНЯТЬ ВСЕ ДАННЫЕ
	~User();

	void operator=(const User& user);

public:
	std::string path = "C://Super Duper Mega Testing/";

	std::ifstream input_f;
	std::ofstream output_f;

	std::string fio;
	std::string login;
	std::string password;

public:
	std::string crypt(std::string in, int key) const;

	void write_to_file();
	void read_from_file();

	bool are_files_exist(std::string path) const;
	bool are_tests_names_free(std::string file_name) const;
	bool is_login_free(std::string login) const; // свободен/существует ли логин
	bool is_password_correct(std::string password); // верный ли пароль
	//bool is_password_simple(std::string password); // простой ли пароль

	void old_user();
	void new_user();

	void pass_the_test() const;
	void show_tests_results() const;


	friend class Admin;
	friend class Menu;


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

	void set_color(int text_color, int background_color) const // функция установки цвета
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background_color << 4) | text_color));
	}
};

