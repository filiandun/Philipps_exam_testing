#include "user.h"


Users::Users(std::string login)
{
	this->login = login;

	this->read_from_file();
}


Users::Users(std::string fio, std::string login, std::string password)
{
	this->fio = fio;
	this->login = login;
	this->password = password;

	this->write_to_file();
}


Users::~Users()
{
}





void Users::old_user()
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


void Users::new_user()
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





bool Users::is_login_free(std::string login)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path)) // ���������� ���� �� ���� ������ �� ����������
	{
		if (path == this->path + login) // ���������
		{
			return false;
		}
	}
	return true;
}


bool Users::is_password_correct(std::string password)
{
	this->read_from_file();
	if (this->password == password)
	{
		return true;
	} 
	return false;
}





void Users::write_to_file() // write to file
{
	std::filesystem::create_directories(this->path + this->login); // �������� ����� ������ ������������

	std::string path = this->path; path.append(this->login); path.append("/"); path.append(this->login); path.append(".txt"); // �������
	this->output_f.open(path, std::ios::out | std::ios::app); // ios::app - ��� ������ � ����� �����

	this->output_f << this->fio << std::endl;
	this->output_f << this->login << std::endl;;
	this->output_f << this->password;

	this->output_f.close();
}


void Users::read_from_file() // read from file
{
	std::string path = this->path; path.append(this->login); path.append("/"); path.append(this->login); path.append(".txt"); // �������
	this->input_f.open(path, std::ios::in);

	getline(this->input_f, this->fio);
	getline(this->input_f, this->login);
	getline(this->input_f, this->password);

	this->input_f.close();
}





void Users::pass_the_test()
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



void Users::show_test_result()
{
	this->input_f.open(this->path + this->login + ".txt", std::ios::in);


}
