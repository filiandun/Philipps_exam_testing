#include "admin.h"


Admin::Admin()
{
	if (this->is_login_free("admin"))
	{
		std::cout << "������� ������� �����, �� ��Ш�� �� ���� ���� ��������������" << std::endl;
		std::cout << "������� ���� ���: "; getline(std::cin, this->fio);
		std::cout << "��� ����� ���������� �������������: admin" << std::endl;
		std::cout << "���������� ���� ������: "; getline(std::cin, this->password);

		this->write_to_file();
	}
	else
	{
		this->login = "admin";
		this->read_from_file();
	}
}

void Admin::operator=(const Admin& admin)
{
	this->fio = admin.fio;
	this->login = admin.login;
	this->password = admin.password;
}







void Admin::new_user() const
{
	std::cout << "�������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User new_user;

	std::cout << "������� ��� ������ ������������: "; std::getline(std::cin, new_user.fio);

	std::cout << "���������� ����� ������ ������������: "; std::cin >> new_user.login;
	while (!this->is_login_free(new_user.login))
	{
		std::cout << "������������ � ����� ������� ��� ����������, ���������� ��� ���: "; std::cin >> new_user.login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "���������� ������ ������ ������������: "; std::cin >> new_user.password;
		break;
	}

	new_user.write_to_file();
}

void Admin::edit_user() const
{
	std::cout << "��������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User edit_user;

	std::cout << "������� ����� ������������, ������ �������� ������ ��������: "; std::cin >> edit_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (this->is_login_free(edit_user.login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin >> edit_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "������� ����� ��� ������������: "; std::getline(std::cin, edit_user.fio);

	while (true) // user.is_password_simple(password)
	{
		std::cout << "������� ����� ������ ������������: "; std::cin >> edit_user.password; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}

	edit_user.write_to_file();

	std::cout << std::endl << "������ ������������ ������� ��������" << std::endl; system("pause");
}


void Admin::delete_user() const
{
	std::cout << "�������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	std::string login_user_to_delete;

	std::cout << "������� ����� ������������, ������ �������� �� ������ �������: "; std::cin >> login_user_to_delete; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (this->is_login_free(login_user_to_delete))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin >> login_user_to_delete; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::filesystem::remove_all(this->path + "users/" + login_user_to_delete);

	std::cout << std::endl << "������������ ������� ���˨�" << std::endl; system("pause");
}






void Admin::new_test() const
{
	std::cout << "�������� ������ ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �������� �����: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); getline(std::cin, file_name);
	while (!this->are_tests_names_free(file_name))
	{
		std::cout << "��� ��� ����� ��� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}

	std::ofstream new_file_with_test(this->path + "tests/" + file_name + ".txt"); // �������� ������ ��� ������ ����� � ������

	std::string description; std::cout << "������� ��������� �������� � �����: "; getline(std::cin, description); new_file_with_test << "&Description: " << description << std::endl << std::endl;
	short int questions_num; std::cout << "������� ���-�� �������� � ������� �����: "; std::cin >> questions_num; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); new_file_with_test << "&Questions num: " << questions_num << std::endl << std::endl;

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

	std::cout << std::endl << "���� ������� ������" << std::endl; system("pause");
}


void Admin::edit_test() const
{
	std::cout << "��������� ������������� ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);
	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}
	std::cout << std::endl << "���� ������" << std::endl; system("pause");
}


void Admin::delete_test() const
{
	std::cout << "�������� ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);

	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ������� �������� ����� ��������: "; getline(std::cin, file_name);
	}
	std::filesystem::remove(this->path + "tests/" + file_name + ".txt"); // ���� �������� �����

	std::cout << std::endl << "���� ������� ���˨�" << std::endl; system("pause");
}


void Admin::show_tests_results() const
{
	std::cout << "���������� ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User temp_user;

	std::cout << "������� ����� ������������, ���������� �������� ������ ����������: "; std::cin >> temp_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (this->is_login_free(temp_user.login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin >> temp_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	temp_user.show_tests_results(); 
}
