#include "user.h"


void User::old_user()
{
	std::cout << "���� (����� ��������� �����, ������� backspace)" << std::endl;


	std::cout << "������� �����: "; std::cin >> this->login;
	while (this->is_login_free(this->login))
	{
		std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; std::cin >> this->login;
	}

	std::cout << "������� ������: "; std::cin >> this->password;
	while (!this->is_password_correct(this->password))
	{
		std::cout << "�������� ������, ���������� ��� ���: "; std::cin >> this->password;
	}
}


void User::new_user()
{
	std::cout << "����������� (����� ��������� �����, ������� backspace)" << std::endl;


	std::cout << "������� ���� ���: " << std::endl; std::getline(std::cin, this->fio);

	std::cout << "���������� ��� �����: " << std::endl; std::cin >> this->login;
	while (!this->is_login_free(this->login))
	{
		std::cout << "������������ � ����� ������� ��� ����������, ���������� ��� ���: " << std::endl; std::cin >> this->login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "���������� ��� ������: " << std::endl; std::cin >> this->password;
		break;
	}

	this->write_to_file();
}




void User::pass_the_test()
{
	std::filesystem::create_directories(this->path + this->login + "/" + "tests"); // �������� ����� tests ��� ���������� ������

	time_t now = time(0); // ������ ������� ���� � ������� � ������ // �� ����� �������� ���� ���� ����, ����� � ���� ��� ���-�� ����� �������
	tm ltm;
	localtime_s(&ltm, &now);
	char buff[10];
	std::string localtime;
	_itoa_s(ltm.tm_mday, buff, 10); localtime.append(buff); localtime.push_back('.');
	_itoa_s(ltm.tm_mon + 1, buff, 10); localtime.append(buff); localtime.push_back('.');
	_itoa_s(ltm.tm_year + 1900, buff, 10); localtime.append(buff); localtime.push_back(' ');
	_itoa_s(ltm.tm_hour, buff, 10); localtime.append(buff); localtime.push_back(';');
	_itoa_s(ltm.tm_min, buff, 10); localtime.append(buff); localtime.push_back(';');
	_itoa_s(ltm.tm_sec, buff, 10); localtime.append(buff);

	this->input_f.open("D://IT/Repositories/Philipps_exam_testing/testing/direction/mathematics.txt", std::ios::in);
	this->output_f.open(this->path + this->login + "/tests/" + localtime + ".txt", std::ios::out | std::ios::app);

	short int question_num = 1;
	std::string question_or_answer;
	std::string user_answer;
	short int correct_user_answer_num = 0;

	std::cout << "������������ �� ����������" << std::endl;
	while (!this->input_f.eof())
	{
		getline(this->input_f, question_or_answer); // ������ ������� �� �����
		this->output_f << question_or_answer << std::endl; // ������ ������� � ����

		std::cout << question_num << ". " << question_or_answer << std::endl;
		std::cout << "��� �����: "; std::cin >> user_answer; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore - �����, ��� ��� ����� ����� ����� ������ 2 2 2 2, 
		// � ������� ����� �������� ����� �������� �� ��������� �������,
		// �� �������� ��������, ��� ���, ���� �������� 2 2, �� ������� ������ ������ ������, 
		// ������� ����� ���� �������.

		getline(this->input_f, question_or_answer); // ������ ������ �� �����
		this->output_f << "��� �����: " << user_answer << std::endl; // ������ ������ ������������ � ����
		this->output_f << "���������� �����: " << question_or_answer << std::endl << std::endl; // ������ ����������� ������ � ����

		if (question_or_answer == user_answer)
		{
			std::cout << "�� �������� �����!" << std::endl << std::endl;
			++correct_user_answer_num;
		}
		else
		{
			std::cout << "�� �������� �������! " << "���������� �����: " << question_or_answer << std::endl << std::endl;
		}

		getline(this->input_f, question_or_answer); // ������ �������� ������ ����� ����� �������� � ������� � ��������� �������� � ������� �� �����
		++question_num;
	}

	this->output_f << correct_user_answer_num << "/" << 6;
	std::cout << "�� �������� ����� �� " << correct_user_answer_num << " �� 6 ��������." << std::endl;

	this->input_f.close();
	this->output_f.close();
}


void User::show_tests_results()
{
	std::cout << "�����" << std::endl;
}
