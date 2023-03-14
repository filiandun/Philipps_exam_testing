#include "user.h"


User::User(std::string path)
{
	this->path = path;
}

User::~User()
{
	this->output_f.close();
	this->input_f.close();
}

void User::operator=(const User& user)
{
	this->fio = user.fio;
	this->login = user.login;
	this->password = user.password;
}





std::string User::crypt(std::string in, int key) const
{
	int in_length = in.length();

	std::string out; out.resize(in_length);

	for (int i = 0; i < in_length; ++i)
	{
		out[i] = in[i] ^ key;
	}

	return out;
	//return in;
}






void User::write_to_file()
{
	std::filesystem::create_directories(this->path + "users/" + crypt(this->login, 10)); // �������� ����� ������ ������������

	this->output_f.open(this->path + "users/" + this->crypt(this->login, 10) + "/" + this->crypt(this->login, 10) + ".txt", std::ios::out);

	this->output_f << this->crypt(this->fio, 10) << std::endl;
	this->output_f << this->crypt(this->login, 10) << std::endl;
	this->output_f << this->crypt(this->password, 10);

	this->output_f.close();
}


void User::read_from_file()
{
	this->input_f.open(this->path + "users/" + this->crypt(this->login, 10) + "/" + this->crypt(this->login, 10) + ".txt", std::ios::in);

	getline(this->input_f, this->fio); this->fio = this->crypt(this->fio, 10);
	getline(this->input_f, this->login); this->login = this->crypt(this->login, 10);
	getline(this->input_f, this->password); this->password = this->crypt(this->password, 10);

	this->input_f.close();
}








bool User::are_files_exist(std::string path) const
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(path))
	{
		return true;
	}
	return false;

}

bool User::are_tests_names_free(std::string file_name) const
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


bool User::is_login_free(std::string login) const
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users")) // ���������� ���� �� ���� ������ �� ����������
	{
		if (path == this->path + "users/" + this->crypt(login, 10)) // ���������
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
	this->set_color(9, 0); std::cout << "���� (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);


	std::cout << "������� ��� �����: "; getline(std::cin, this->login); 
	while (this->is_login_free(this->login))
	{
		this->set_color(4, 0); std::cout << "������������ � ����� ������� �� ����������, ���������� ��� ���: "; this->set_color(15, 0); getline(std::cin, this->login);
	}

	std::cout << "������� ��� ������: "; getline(std::cin, this->password);
	while (!this->is_password_correct(this->password))
	{
		this->set_color(4, 0); std::cout << "�������� ������, ���������� ��� ���: "; this->set_color(15, 0); getline(std::cin, this->password);
	}
}


void User::new_user()
{
	this->set_color(9, 0); std::cout << "����������� (����� ��������� �����, ������� backspace)" << std::endl; this->set_color(15, 0);


	std::cout << "������� ���� ���: "; std::getline(std::cin, this->fio);

	std::cout << "���������� ��� �����: "; std::cin >> this->login;
	while (!this->is_login_free(this->login))
	{
		this->set_color(4, 0); std::cout << "������������ � ����� ������� ��� ����������, ���������� ��� ���: "; this->set_color(15, 0); std::cin >> this->login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "���������� ��� ������: "; std::cin >> this->password; std::cin.ignore(LLONG_MAX, '\n');
		break;
	}

	this->write_to_file();
}







void User::pass_the_test() const
{
	system("cls");
	std::filesystem::create_directories(this->path + "users/" + this->crypt(this->login, 10) + "/tests results"); // �������� ����� tests ��� ���������� ������

// ���������� ������� � ����������� ��� � STRING
	time_t now = time(0); // �� ����� �������� ���� ���� ����, ����� � ���� ��� ���-�� ����� �������
	tm ltm;
	localtime_s(&ltm, &now);
	char buff[10];
	std::string localtime;
	_itoa_s(ltm.tm_mday, buff, 10); buff[9] = '\0'; localtime.append(buff); localtime.push_back('.');
	_itoa_s(ltm.tm_mon + 1, buff, 10); localtime.append(buff); localtime.push_back('.');
	_itoa_s(ltm.tm_year + 1900, buff, 10); localtime.append(buff); localtime.push_back(' ');
	_itoa_s(ltm.tm_hour, buff, 10); localtime.append(buff); localtime.push_back(';');
	_itoa_s(ltm.tm_min, buff, 10); localtime.append(buff); localtime.push_back(';');
	_itoa_s(ltm.tm_sec, buff, 10); localtime.append(buff);


// ����� ���� ������ � ����� ������� �� ���
	system("cls");
	this->set_color(9, 0); std::cout << "��������� �����: " << std::endl; this->set_color(15, 0);

	// ���� ����� �� �������
	if (!this->are_files_exist(this->path + "tests/"))
	{
		this->set_color(4, 0); std::cout << std::endl << "����� �� �������" << std::endl; this->set_color(15, 0);
		system("pause");
		return;
	}

	// ���� ����� �������
	std::filesystem::path path;
	for (std::filesystem::path temp_path : std::filesystem::directory_iterator(this->path + "tests/")) // ���������� ���� �� ���� ������ �� ����������
	{
		std::cout << temp_path.filename() << std::endl;
		path = temp_path;
	}

	std::string test_name;
	std::cout << std::endl << "������� �������� �����, ������� ������ ������: "; std::cin >> test_name;
	while (this->are_tests_names_free(test_name))
	{
		this->set_color(4, 0); std::cout << "���� �� ������, ���������� ��� ���: "; this->set_color(15, 0); std::cin >> test_name;
	}

	std::ofstream ofs_test_result(this->path + "users/" + this->login + "/tests results/" + test_name + " " + localtime + ".txt", std::ios::out);


// ���� ����������� �����
	system("cls");
	this->set_color(9, 0); std::cout << "������������" << std::endl; this->set_color(15, 0);
	std::ifstream ifs_test(path, std::ios::in);

	// ����� �������� � ���-�� ��������
	std::string description; ifs_test.seekg(14); getline(ifs_test, description); std::cout << "������� �������� � �����: " << description << std::endl;
	short int questions_num; ifs_test.seekg(14 + description.size() + 20); ifs_test >> questions_num; std::cout << "���-�� �������� � �����: " << questions_num << std::endl << std::endl;

	// ����� ��������
	std::string question_or_answer;
	std::string user_answer;
	short int correct_user_answer_num = 0;

	ifs_test.seekg(14 + description.size() + 20 + 1 + 12);
	while (!ifs_test.eof())
	{
		getline(ifs_test, question_or_answer); // ������ ������� �� �����
		ofs_test_result << question_or_answer << std::endl; // ������ ������� � ����

		std::cout << "������ " << question_or_answer << std::endl;
		std::cout << "��� �����: "; std::cin >> user_answer; std::cin.ignore(LLONG_MAX, '\n'); // ignore - �����, ��� ��� ����� ����� ����� ������ 2 2 2 2, 
		// � ������� ����� �������� ����� �������� �� ��������� �������,
		// �� �������� ��������, ��� ���, ���� �������� 2 2, �� ������� ������ ������ ������, 
		// ������� ����� ���� �������.

		getline(ifs_test, question_or_answer); // ������ ������ �� �����
		ofs_test_result << "��� �����: " << user_answer << std::endl; // ������ ������ ������������ � ����
		ofs_test_result << "���������� �����: " << question_or_answer << std::endl << std::endl; // ������ ����������� ������ � ����

		if (question_or_answer == user_answer)
		{
			this->set_color(2, 0); std::cout << "�� �������� �����!" << std::endl << std::endl; this->set_color(15, 0);
			++correct_user_answer_num;
		}
		else
		{
			this->set_color(4, 0); std::cout << "�� �������� �������! " << "���������� �����: " << question_or_answer << std::endl << std::endl; this->set_color(15, 0);
		}

		getline(ifs_test, question_or_answer); // ������ �������� ������ ����� ����� �������� � ������� � ��������� �������� � ������� �� �����
	}

// ����� �����
	ofs_test_result << correct_user_answer_num << "/" << questions_num;
	std::cout << "�� �������� ����� �� " << correct_user_answer_num << " �� " << questions_num << " ��������" << std::endl << std::endl; system("pause");

	ifs_test.close();
	ofs_test_result.close();
}


void User::show_tests_results() const
{
	system("cls");
	this->set_color(9, 0); std::cout << "���������� ������������ (����� ��������� �����, ������� backspace)"; this->set_color(15, 0);

	if (std::filesystem::is_directory(this->path + "users/" + this->crypt(this->login, 10) + "/tests results/"))
	{
		if (this->are_files_exist(this->path + "users/" + this->crypt(this->login, 10) + "/tests results/"))
		{
			std::string user_results;
			for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users/" + this->crypt(this->login, 10) + "/tests results/")) // ���������� ���� �� ���� ������ �� ����������
			{
				std::ifstream ifs_tests_results(path, std::ios::in);
				std::cout << std::endl << std::endl << "���������� �� " << path.filename() << ": " << std::endl; // path.filename() ��������� � ���������, ��� ��� �������� >> � path ���������� ���
				while (!ifs_tests_results.eof())
				{
					getline(ifs_tests_results, user_results);
					std::cout << user_results << std::endl;
				}
				ifs_tests_results.close();
			}

			std::cout << std::endl;
			system("pause");
			return;
		}
	}
	this->set_color(4, 0); std::cout << std::endl << std::endl << "�� ���� ������������ �� ��������" << std::endl; this->set_color(15, 0);
	system("pause");
}