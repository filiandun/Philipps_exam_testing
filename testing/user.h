#pragma once
#include <iostream>
#include <string>
#include <fstream> // для работы с файлами
#include <filesystem> // для работы с папкам
#include <stdlib.h> // для работы _itoa_s()


class User
{
public:
	User() = default;
	User(std::string path); // ДУМАЮ, ЧТО ПРИ ПЕРВОМ ЗАПУСКЕ, У АДМИНА НУЖНО СПРАШИВАТЬ, КУДА СОХРАНЯТЬ ВСЕ ДАННЫЕ
	~User()
	{
		std::cout << "~USER" << std::endl; system("pause");
	}

	void operator=(const User& user);

public:
	std::string path = "D://IT/Repositories/Philipps_exam_testing/testing/";

	std::ifstream input_f;
	std::ofstream output_f;

	std::string fio;
	std::string login;
	std::string password;

public:
	void write_to_file();
	void read_from_file();

	bool is_login_free(std::string login); // свободен/существует ли логин
	bool is_password_correct(std::string password); // верный ли пароль
	//bool is_password_simple(std::string password); // простой ли пароль

	void new_user();
	void old_user();

	void pass_the_test();
	void show_tests_results();


	friend class Admin;
};

