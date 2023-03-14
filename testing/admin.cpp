#include "admin.h"


Admin::Admin()
{
	if (!std::filesystem::is_directory(this->path))
	{
		try
		{
			std::filesystem::create_directories(this->path);
			std::filesystem::create_directories(this->path + "Tests/");
			std::filesystem::create_directories(this->path + "Users/");
		}
		catch (std::filesystem::filesystem_error const& ex)
		{
			std::cout
				<< "what():  " << ex.what() << '\n'
				<< "path1(): " << ex.path1() << '\n'
				<< "path2(): " << ex.path2() << '\n'
				<< "code().value():	   " << ex.code().value() << '\n'
				<< "code().message():  " << ex.code().message() << '\n'
				<< "code().category(): " << ex.code().category().name() << '\n';
		}
	}
	if (this->is_login_free("admin"))
	{
		this->set_color(13, 0); std::cout << "������� ������� �����, �� ��Ш�� �� ���� ���� ��������������" << std::endl; this->set_color(15, 0);
		std::cout << "������� ���� ���: "; getline(std::cin, this->fio);
		std::cout << "��� ����� ���������� �������������: admin" << std::endl; this->login = "admin";
		std::cout << "���������� ���� ������: "; getline(std::cin, this->password);

		this->write_to_file();
	}
	else
	{
		this->login = "admin";
		this->read_from_file();
	}
}






void Admin::new_user() const
{
	this->set_color(13, 0); std::cout << "�������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

	User new_user;

	std::cout << "������� ��� ������ ������������: "; std::getline(std::cin, new_user.fio);

	std::cout << "���������� ����� ������ ������������: "; std::cin >> new_user.login;
	while (!this->is_login_free(new_user.login))
	{
		this->set_color(4, 0); std::cout << "������������ � ����� ������� ��� ����������, ���������� ��� ���: "; this->set_color(15, 0); std::cin >> new_user.login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "���������� ������ ������ ������������: "; std::cin >> new_user.password; std::cin.ignore(LLONG_MAX, '\n');
		break;
	}

	new_user.write_to_file();

	this->set_color(2, 0); std::cout << std::endl << "������������ ������� ������" << std::endl; this->set_color(15, 0); system("pause");
}


void Admin::edit_user() const
{
	this->set_color(13, 0); std::cout << "��������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

	User edit_user;

	std::cout << "������� ����� ������������, ������ �������� ������ ��������: "; getline(std::cin, edit_user.login);
	while (this->is_login_free(edit_user.login))
	{
		this->set_color(4, 0); std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; this->set_color(15, 0); getline(std::cin, edit_user.login);
	}
	std::cout << "������� ����� ��� ������������: "; getline(std::cin, edit_user.fio);

	while (true) // user.is_password_simple(password)
	{
		std::cout << "������� ����� ������ ������������: "; std::cin >> edit_user.password; std::cin.ignore(LLONG_MAX, '\n');
		break; 
	}

	edit_user.write_to_file();

	this->set_color(2, 0); std::cout << std::endl << "������ ������������ ������� ��������" << std::endl; this->set_color(15, 0); system("pause");
}


void Admin::delete_user() const
{
	this->set_color(13, 0); std::cout << "�������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

	std::string login_user_to_delete;

	std::cout << "������� ����� ������������, ������ �������� �� ������ �������: "; getline(std::cin, login_user_to_delete);
	while (this->is_login_free(login_user_to_delete))
	{
		this->set_color(4, 0); std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; this->set_color(15, 0); getline(std::cin, login_user_to_delete);
	}

	std::filesystem::remove_all(this->path + "users/" + this->crypt(login_user_to_delete, 10));

	this->set_color(2, 0); std::cout << std::endl << "������������ ������� ���˨�" << std::endl; this->set_color(15, 0); system("pause");
}







void Admin::new_test() const
{
	this->set_color(13, 0); std::cout << "�������� ������ ����� (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

// ������� ����� �����
	std::string file_name; std::cout << "������� �������� �������� �����: "; std::cin >> file_name; std::cin.ignore(LLONG_MAX, '\n');
	while (!this->are_tests_names_free(file_name))
	{
		this->set_color(4, 0); std::cout << "��� ��� ����� ��� ������, ���������� ��� ���: "; this->set_color(15, 0); getline(std::cin, file_name);
	}

// ������� �������� � ���-�� �������� � �����
	std::ofstream new_file_with_test(this->path + "tests/" + file_name + ".txt"); // �������� ������ ��� ������ ����� � ������

	std::string description; std::cout << "������� ��������� �������� � �����: "; getline(std::cin, description); new_file_with_test << "&Description: " << description << std::endl << std::endl;

	short int questions_num; std::cout << "������� ���-�� �������� � ������� �����: "; std::cin >> questions_num; std::cin.ignore(LLONG_MAX, '\n');
	while (questions_num < 0 && questions_num > 100)
	{
		this->set_color(4, 0); std::cout << "���-�� �������� ������� �� �������� �����, ���������� ��� ���: "; this->set_color(15, 0); std::cin >> questions_num; std::cin.ignore(LLONG_MAX, '\n');
	}
	new_file_with_test << "&Questions num: " << questions_num << std::endl << std::endl;

// ���������� � ������ �������� � ����
	new_file_with_test << "&Test:" << std::endl;
	std::string question_or_answer; 
	for (int i = 0; i < questions_num; ++i)
	{				
		std::cout << std::endl << "������� ������: "; getline(std::cin, question_or_answer);
		new_file_with_test << i + 1 << ": " << question_or_answer << std::endl;

		std::cout << "������� ����� �� ������: "; getline(std::cin, question_or_answer);
		i == (questions_num - 1) ? new_file_with_test << question_or_answer : new_file_with_test << question_or_answer << std::endl << std::endl; // ��������� ��������� ����� ��� ����, ����� � ��������� ������� �� ��������� ������ ��� endl
	}

	new_file_with_test.close();

	this->set_color(2, 0); std::cout << std::endl << "���� ������� ������" << std::endl; this->set_color(15, 0); system("pause");
}


void Admin::edit_test() const
{ 
	this->set_color(13, 0); std::cout << "��������� ������������� ����� (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);
	while (this->are_tests_names_free(file_name))
	{
		this->set_color(4, 0); std::cout << "���� �� ������, ���������� ��� ���: "; this->set_color(15, 0); getline(std::cin, file_name);
	}

	this->set_color(2, 0); std::cout << std::endl << "���� ������" << std::endl; this->set_color(15, 0); system("pause");
}


void Admin::delete_test() const
{
	this->set_color(4, 0); std::cout << "�������� ����� (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);

	while (this->are_tests_names_free(file_name))
	{
		this->set_color(4, 0); std::cout << "���� �� ������, ������� �������� ����� ��������: "; this->set_color(15, 0); getline(std::cin, file_name);
	}
	std::filesystem::remove(this->path + "tests/" + file_name + ".txt"); // ���� �������� �����

	this->set_color(2, 0); std::cout << std::endl << "���� ������� ���˨�" << std::endl; this->set_color(15, 0); system("pause");
}


void Admin::show_tests_results() const
{
	this->set_color(13, 0); std::cout << "���������� ������������ (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);

	User temp_user;

	std::cout << "������� ����� ������������, ���������� �������� ������ ����������: "; std::cin >> temp_user.login;
	while (this->is_login_free(temp_user.login))
	{
		this->set_color(4, 0); std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; this->set_color(15, 0); std::cin >> temp_user.login; std::cin.ignore(LLONG_MAX, '\n');
	}

	temp_user.show_tests_results();
}
