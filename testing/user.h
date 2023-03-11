#pragma once
#include <iostream>
#include <string>
#include <fstream> // ��� ������ � �������
#include <filesystem> // ��� ������ � ������
#include <stdlib.h> // ��� ������ _itoa_s()


class User
{
public:
	User() = default;
	User(std::string path); // �����, ��� ��� ������ �������, � ������ ����� ����������, ���� ��������� ��� ������
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

	bool is_login_free(std::string login); // ��������/���������� �� �����
	bool is_password_correct(std::string password); // ������ �� ������
	//bool is_password_simple(std::string password); // ������� �� ������

	void new_user();
	void old_user();

	void pass_the_test();
	void show_tests_results();


	friend class Admin;
};

