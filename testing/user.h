#pragma once
#include <iostream>
#include <string>
#include <fstream> // ��� ������ � �������
#include <filesystem> // ��� ������ � ������
#include <stdlib.h> // ��� ������ _itoa_s()
#include <exception> // ��� ������ � ��������
#include <conio.h> // ��� ������ � �������� ���������

class User
{
public:
	User() = default;
	User(std::string path); // �����, ��� ��� ������ �������, � ������ ����� ����������, ���� ��������� ��� ������
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
	bool is_login_free(std::string login) const; // ��������/���������� �� �����
	bool is_password_correct(std::string password); // ������ �� ������
	//bool is_password_simple(std::string password); // ������� �� ������

	void old_user();
	void new_user();

	void pass_the_test() const;
	void show_tests_results() const;


	friend class Admin;
};

