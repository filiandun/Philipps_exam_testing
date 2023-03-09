#include "admin.h"


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

	std::filesystem::remove_all(this->path + "users/" + deleted_user.login);
}






void Admin::new_test()
{
	std::cout << "�������� ������ ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �������� �����: "; getline(std::cin, file_name);
	while (!this->are_tests_names_free(file_name))
	{
		std::cout << "��� ��� ����� ��� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}

	this->output_f.open(this->path + "tests/" + file_name + ".txt");

	short int questions_num; std::cout << "������� ���-�� �������� � ������� �����: "; std::cin >> questions_num; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int i = 0; i < questions_num; ++i)
	{				
		std::string question_or_answer; 

		std::cout << std::endl <<  "������� ������: "; getline(std::cin, question_or_answer); 
		this->output_f << i + 1 << ". " << question_or_answer << std::endl;

		std::cout << "������� ����� �� ������: "; getline(std::cin, question_or_answer);
		i == (questions_num - 1) ? this->output_f << question_or_answer : this->output_f << question_or_answer << std::endl << std::endl; // ��������� ��������� ����� ��� ����, ����� � ��������� ������� �� ��������� ������ ��� endl
		// ���-�� ��� �� ���, �� ������ ��������� ����� ���������, �������������� �� ��������
		// ����� �� ���������, ��� ��� ������� �������� ������
	}
	this->output_f << std::endl << std::endl << questions_num; // ����������� ���-�� �������� � ����� �����

	this->output_f.close();
}


void Admin::edit_test()
{
	std::cout << "��������� ������������� ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);
	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}
	std::cout << "���� ������" << std::endl;
}


void Admin::delete_test()
{
	std::cout << "�������� ����� (����� ��������� �����, ������� backspace)" << std::endl;

	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);

	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ������� �������� ����� ��������: "; getline(std::cin, file_name);
	}
	std::filesystem::remove(this->path + "tests/" + file_name + ".txt");
	std::cout << "���� ������� �����" << std::endl;
	// ���-�� ��� �� ���, ������ ������ ������ ��� ��������, �������������� - ������ ����� �������, ������ ��� ��������� - ���
	// ��������, ����� ��, ������: ����� ����� �������, ������ �� ��������� ���������
}






void Admin::show_tests_results()
{

}
