#pragma once
#include <iostream>
#include <string>
#include <fstream> // для работы с файлами
#include <filesystem> // для работы с папкам
#include <stdlib.h> // для работы _itoa_s()


class Users
{
public:
	Users() = default;
	~Users() = default;

protected:
	std::string path = "D://IT/Repositories/Philipps_exam_testing/testing/users/";

	std::ifstream input_f;
	std::ofstream output_f;

	std::string fio;
	std::string login;
	std::string password;

protected:
	virtual void new_user() = 0;

	virtual void show_tests_results() = 0;

	bool is_login_free(std::string login); // свободен/существует ли логин
	bool is_password_correct(std::string password); // верный ли пароль
	//bool is_password_simple(std::string password); // простой ли пароль

	void write_to_file();
	void read_from_file();
};

