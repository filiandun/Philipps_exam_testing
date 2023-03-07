#pragma once
#include <iostream>
#include <string>
#include <fstream> // ��� ������ � �������
#include <filesystem> // ��� ������ � ������
#include <stdlib.h> // ��� ������ _itoa_s()


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

	bool is_login_free(std::string login); // ��������/���������� �� �����
	bool is_password_correct(std::string password); // ������ �� ������
	//bool is_password_simple(std::string password); // ������� �� ������

	void write_to_file();
	void read_from_file();
};

