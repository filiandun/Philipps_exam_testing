#pragma once
#include <iostream>
#include <string>
#include <fstream> // для работы с файлами
#include <filesystem> // для работы с папкам
#include <stdlib.h> // для работы _itoa_s()
#include <exception> // для работы с ошибками
#include <conio.h> // для работы с нажатыми клавишами

class User
{
public:
	User() = default;
	User(std::string path); // ДУМАЮ, ЧТО ПРИ ПЕРВОМ ЗАПУСКЕ, У АДМИНА НУЖНО СПРАШИВАТЬ, КУДА СОХРАНЯТЬ ВСЕ ДАННЫЕ
	~User() = default;

	void operator=(const User& user);

public:
	std::string path = "C://Super Duper Mega Testing/";

	std::ifstream input_f;
	std::ofstream output_f;

	std::string fio;
	std::string login;
	std::string password;

public:
	std::string crypt(std::string in, int key) const
	{
		int in_length = in.length();

		std::string out; out.resize(in_length);

		for (int i = 0; i < in_length; ++i)
		{
			out[i] = in[i] ^ key;
		}

		return out;
	}


	void write_to_file();
	void read_from_file();

	bool are_tests_names_free(std::string file_name) const;
	bool is_login_free(std::string login) const; // свободен/существует ли логин
	bool is_password_correct(std::string password); // верный ли пароль
	//bool is_password_simple(std::string password); // простой ли пароль

	void old_user();
	void new_user();

	void pass_the_test() const;
	void show_tests_results() const;


	friend class Admin;
};

