#include "admin.h"


Admin::Admin()
{
	if (this->is_login_free("admin"))
	{
		std::cout << "������� ������� �����, �� ��Ш�� �� ���� ���� ��������������" << std::endl;
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

void Admin::operator=(const Admin& admin)
{
	this->fio = admin.fio;
	this->login = admin.login;
	this->password = admin.password;
}






bool Admin::are_tests_names_free(std::string file_name)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "tests/")) // ���������� ���� �� ���� ������ �� ����������
	{
		std::filesystem::path files_names = path.filename();
		if (files_names == (file_name + ".txt")) // ���������
		{
			return false;
		}
	}
	return true;
}





void Admin::edit_user()
{
	std::cout << "��������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User new_user;

	std::cout << "������� ����� ������������, ������ �������� ������ ��������: "; std::cin >> new_user.login;
	while (this->is_login_free(new_user.login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin >> new_user.login;
	}

	std::cout << "������� ����� ��� ������������: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::getline(std::cin, new_user.fio);

	while (true) // user.is_password_simple(password)
	{
		std::cout << "������� ����� ������ ������������: "; std::cin >> new_user.password;
		break;
	}

	new_user.write_to_file();

	std::cout << "������ ������������ ������� ��������" << std::endl << std::endl; system("pause");
}


void Admin::delete_user()
{
	std::cout << "�������� ������ ������������ (����� ��������� �����, ������� backspace)" << std::endl;

	User deleted_user;
	std::cout << "������� ����� ������������, ������ �������� �� ������ �������: "; std::cin >> deleted_user.login;
	while (this->is_login_free(deleted_user.login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin >> deleted_user.login;
	}

	std::filesystem::remove_all(this->path + "users/" + deleted_user.login);

	std::cout << "������������ ������� ���˨�" << std::endl << std::endl; system("pause");
}






void Admin::new_test()
{
	std::cout << "�������� ������ ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �������� �����: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); getline(std::cin, file_name);
	while (!this->are_tests_names_free(file_name))
	{
		std::cout << "��� ��� ����� ��� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}
	this->output_f.open(this->path + "tests/" + file_name + ".txt");

	std::string description; std::cout << "������� ��������� �������� � �����: "; getline(std::cin, description); this->output_f << "&Description: " << description << std::endl << std::endl;
	short int questions_num; std::cout << "������� ���-�� �������� � ������� �����: "; std::cin >> questions_num; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); this->output_f << "&Questions num: " << questions_num << std::endl << std::endl;
	this->output_f << "&Test:" << std::endl;

	std::string question_or_answer; 
	for (int i = 0; i < questions_num; ++i)
	{				

		std::cout << std::endl << "������� ������: "; getline(std::cin, question_or_answer); 
		this->output_f << i + 1 << ": " << question_or_answer << std::endl;

		std::cout << "������� ����� �� ������: "; getline(std::cin, question_or_answer);
		i == (questions_num - 1) ? this->output_f << question_or_answer : this->output_f << question_or_answer << std::endl << std::endl; // ��������� ��������� ����� ��� ����, ����� � ��������� ������� �� ��������� ������ ��� endl
		// ���-�� ��� �� ���, �� ������ ��������� ����� ���������, �������������� �� ��������
		// ����� �� ���������, ��� ��� ������� �������� ������
	}
	this->output_f.close();

	std::cout << "���� ������� ������" << std::endl << std::endl; system("pause");
}


void Admin::edit_test()
{
	std::cout << "��������� ������������� ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);
	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}
	std::cout << "���� ������" << std::endl << std::endl; system("pause");
}


void Admin::delete_test()
{
	std::cout << "�������� ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);

	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ������� �������� ����� ��������: "; getline(std::cin, file_name);
	}
	std::filesystem::remove(this->path + "tests/" + file_name + ".txt"); // ���� �������� �����

	std::cout << "���� ������� ���˨�" << std::endl << std::endl; system("pause");
}






void Admin::show_tests_results()
{

}
