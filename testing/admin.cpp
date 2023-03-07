#include "admin.h"


void Admin::new_user()
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


void Admin::edit_user()
{
	std::cout << "��������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User new_user;

	std::cout << "������� �����: "; std::cin >> new_user.login;
	while (this->is_login_free(new_user.login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin >> new_user.login;
	}

	std::cout << "������� ����� ��� ������������: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::getline(std::cin, new_user.fio);

	while (true) // user.is_password_simple(password)
	{
		std::cout << "���������� ����� ������ ������������: "; std::cin >> new_user.password;
		break;
	}

	new_user.write_to_file();
}


void Admin::delete_user()
{
	std::cout << "�������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User deleted_user;
	std::cout << "������� �����: "; std::cin >> deleted_user.login;
	while (this->is_login_free(deleted_user.login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin >> deleted_user.login;
	}

	std::filesystem::remove_all(this->path + deleted_user.login);
}





void Admin::new_test()
{
}


void Admin::edit_test()
{
}


void Admin::delete_test()
{
}


void Admin::show_tests_results()
{
}
