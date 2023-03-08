#include "admin.h"


bool Admin::are_tests_names_free(std::string file_name)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator("D://IT/Repositories/Philipps_exam_testing/testing/direction/")) // ���������� ���� �� ���� ������ �� ����������
	{
		std::filesystem::path files_names = path.filename(); std::cout << "PATH: " << path << std::endl;
		if (files_names == (file_name + ".txt")) // ���������
		{
			return false;
		}
	}
	return true;
}

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
	std::string file_name; std::cout << "������� �������� �������� �����: "; getline(std::cin, file_name);
	while (!this->are_tests_names_free(file_name))
	{
		std::cout << "��� ��� ����� ��� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}

	this->output_f.open("D://IT/Repositories/Philipps_exam_testing/testing/direction/" + file_name + ".txt");

	short int questions_num; std::cout << "������� ���-�� �������� � ������� �����: "; std::cin >> questions_num; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int i = 0; i <= questions_num; ++i)
	{				
		std::string question_or_answer; 

		std::cout << "������� ������: "; getline(std::cin, question_or_answer); 
		this->output_f << question_or_answer << std::endl;

		std::cout << "������� ����� �� ������: "; getline(std::cin, question_or_answer); std::cout << std::endl; std::cout << "QORA: " << question_or_answer << std::endl; system("puase");
		i == (questions_num - 1) ? this->output_f << "== " << question_or_answer : this->output_f << "!= " << question_or_answer << std::endl << std::endl; // ��������� ��������� ����� ��� ����, ����� � ��������� ������� �� ��������� ������ ��� endl
		// ���-�� ��� �� ���, �� ������ ��������� ����� ���������, �������������� �� ��������
	}
}


void Admin::edit_test()
{
	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);
	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ���������� ��� ���: "; getline(std::cin, file_name);
	}

	std::cout << "���� ������" << std::endl;
}


void Admin::delete_test()
{
	std::string file_name; std::cout << "������� �������� �����: "; getline(std::cin, file_name);

	while (this->are_tests_names_free(file_name))
	{
		std::cout << "���� �� ������, ������� �������� ����� ��������: "; getline(std::cin, file_name);
	}

	std::filesystem::remove("D://IT/Repositories/Philipps_exam_testing/testing/direction/" + file_name + ".txt");
	std::cout << "���� ������� �����" << std::endl; std::cout << "D://IT/Repositories/Philipps_exam_testing/testing/direction/" + file_name + ".txt" << std::endl;
	// ���-�� ��� �� ���, ������ ������ ������ ��� ��������, �������������� �� ��������
}


void Admin::show_tests_results()
{

}
