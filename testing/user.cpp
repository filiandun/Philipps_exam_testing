#include "user.h"


User::User(std::string path)
{
	this->path = path;
}

void User::write_to_file()
{
	std::filesystem::create_directories(this->path + "users/" + this->login); // �������� ����� ������ ������������

	this->output_f.open(this->path + "users/" + this->login + "/" + this->login + ".txt", std::ios::out);

	this->output_f << this->fio << std::endl;
	this->output_f << this->login << std::endl;;
	this->output_f << this->password;

	this->output_f.close();
}


void User::read_from_file()
{
	this->input_f.open(this->path + "users/" + this->login + "/" + this->login + ".txt", std::ios::in);

	getline(this->input_f, this->fio);
	getline(this->input_f, this->login);
	getline(this->input_f, this->password);

	this->input_f.close();
}






bool User::is_login_free(std::string login)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users")) // ���������� ���� �� ���� ������ �� ����������
	{
		if (path == this->path + "users/" + login) // ���������
		{
			return false;
		}
	}
	return true;
}


bool User::is_password_correct(std::string password)
{
	this->read_from_file();
	if (this->password == password)
	{
		return true;
	} 
	return false;
}





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


	std::cout << "������� ���� ���: "; std::getline(std::cin, this->fio);

	std::cout << "���������� ��� �����: "; std::cin >> this->login;
	while (!this->is_login_free(this->login))
	{
		std::cout << "������������ � ����� ������� ��� ����������, ���������� ��� ���: "; std::cin >> this->login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "���������� ��� ������: "; std::cin >> this->password;
		break;
	}

	this->write_to_file();
}






void User::pass_the_test()
{
	std::filesystem::create_directories(this->path + "users/" + this->login + "/tests results"); // �������� ����� tests ��� ���������� ������

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

	this->input_f.open(this->path + "tests/mathematics.txt", std::ios::in);
	this->output_f.open(this->path + "users/" + this->login + "/tests results/" + localtime + ".txt", std::ios::out | std::ios::app);

	std::string question_or_answer;
	std::string user_answer;
	short int questions_num = 0;
	short int correct_user_answer_num = 0;

	std::cout << "������������ �� ����������" << std::endl;
	while (!this->input_f.eof())
	{
		getline(this->input_f, question_or_answer); // ������ ������� �� �����
		this->output_f << question_or_answer << std::endl; // ������ ������� � ����

		std::cout << question_or_answer << std::endl;
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
		++questions_num;
	}

	this->output_f << correct_user_answer_num;
	std::cout << "�� �������� ����� �� " << correct_user_answer_num << " �� " << questions_num << " ��������" << std::endl;

	this->input_f.close();
	this->output_f.close();
}


void User::show_tests_results()
{
	this->input_f.open(this->path + this->login + ".txt", std::ios::in);


}
