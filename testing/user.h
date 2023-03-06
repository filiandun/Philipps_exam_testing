#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdlib.h>



class Users
{
public:
	Users() = default;
	Users(std::string login);
	Users(std::string fio, std::string login, std::string password);

	~Users();


private:
	std::string path = "D://IT/Repositories/Philipps_exam_testing/testing/users/";

	std::string fio;

	std::string login;
	std::string password;


	std::ifstream input_f;
	std::ofstream output_f;


public:
	void new_user();
	void old_user();

	bool is_login_free(std::string login); // свободен/существует ли логин
	bool is_password_correct(std::string password); // корректный ли пароль
	//bool is_password_simple(std::string password); // простой ли пароль

	void write_to_file();
	void read_from_file();

	void pass_the_test();
	void show_test_result();

};

