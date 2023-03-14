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
	std::filesystem::create_directories(this->path + "users/" + crypt(this->login, 10)); // создание папки нового пользователя

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
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "tests/")) // возвращает пути ко всем папкам из директории
	{
		std::filesystem::path files_names = path.filename();
		if (files_names == (file_name + ".txt")) // сравнение
		{
			return false;
		}
	}
	return true;
}


bool User::is_login_free(std::string login) const
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users")) // возвращает пути ко всем папкам из директории
	{
		if (path == this->path + "users/" + this->crypt(login, 10)) // сравнение
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
	this->set_color(9, 0); std::cout << "ВХОД (чтобы вернуться назад, нажмите backspace)" << std::endl; this->set_color(15, 0);


	std::cout << "введите ваш логин: "; getline(std::cin, this->login); 
	while (this->is_login_free(this->login))
	{
		this->set_color(4, 0); std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; this->set_color(15, 0); getline(std::cin, this->login);
	}

	std::cout << "введите ваш пароль: "; getline(std::cin, this->password);
	while (!this->is_password_correct(this->password))
	{
		this->set_color(4, 0); std::cout << "неверный пароль, попробуйте ещё раз: "; this->set_color(15, 0); getline(std::cin, this->password);
	}
}


void User::new_user()
{
	this->set_color(9, 0); std::cout << "РЕГИСТРАЦИЯ (чтобы вернуться назад, нажмите backspace)" << std::endl; this->set_color(15, 0);


	std::cout << "введите ваше ФИО: "; std::getline(std::cin, this->fio);

	std::cout << "придумайте ваш логин: "; std::cin >> this->login;
	while (!this->is_login_free(this->login))
	{
		this->set_color(4, 0); std::cout << "пользователь с таким логином уже существует, попробуйте ещё раз: "; this->set_color(15, 0); std::cin >> this->login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "придумайте ваш пароль: "; std::cin >> this->password; std::cin.ignore(LLONG_MAX, '\n');
		break;
	}

	this->write_to_file();
}







void User::pass_the_test() const
{
	system("cls");
	std::filesystem::create_directories(this->path + "users/" + this->crypt(this->login, 10) + "/tests results"); // создание папки tests для сохранения тестов

// СЧИТЫВАНИЕ ВРЕМЕНИ И ЗАПИСЫВАНИЕ ЕГО В STRING
	time_t now = time(0); // не очень нравится весь этот блок, может с ними ещё что-то можно сделать
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


// ВЫВОД ВСЕХ ТЕСТОВ И ВЫБОР ОДИНОГО ИЗ НИХ
	system("cls");
	this->set_color(9, 0); std::cout << "ДОСТУПНЫЕ ТЕСТЫ: " << std::endl; this->set_color(15, 0);

	// ЕСЛИ ТЕСТЫ НЕ НАЙДЕНЫ
	if (!this->are_files_exist(this->path + "tests/"))
	{
		this->set_color(4, 0); std::cout << std::endl << "тесты не найдено" << std::endl; this->set_color(15, 0);
		system("pause");
		return;
	}

	// ЕСЛИ ТЕСТЫ НАЙДЕНЫ
	std::filesystem::path path;
	for (std::filesystem::path temp_path : std::filesystem::directory_iterator(this->path + "tests/")) // возвращает пути ко всем папкам из директории
	{
		std::cout << temp_path.filename() << std::endl;
		path = temp_path;
	}

	std::string test_name;
	std::cout << std::endl << "введите название теста, который хотите пройти: "; std::cin >> test_name;
	while (this->are_tests_names_free(test_name))
	{
		this->set_color(4, 0); std::cout << "тест не найден, попробуйте ещё раз: "; this->set_color(15, 0); std::cin >> test_name;
	}

	std::ofstream ofs_test_result(this->path + "users/" + this->login + "/tests results/" + test_name + " " + localtime + ".txt", std::ios::out);


// САМО ПРОХОЖДЕНИЕ ТЕСТА
	system("cls");
	this->set_color(9, 0); std::cout << "ТЕСТИРОВАНИЕ" << std::endl; this->set_color(15, 0);
	std::ifstream ifs_test(path, std::ios::in);

	// ВЫВОД ОПИСАНИЯ И КОЛ-ВА ВОПРОСОВ
	std::string description; ifs_test.seekg(14); getline(ifs_test, description); std::cout << "Краткое описание к тесту: " << description << std::endl;
	short int questions_num; ifs_test.seekg(14 + description.size() + 20); ifs_test >> questions_num; std::cout << "Кол-во вопросов в тесте: " << questions_num << std::endl << std::endl;

	// ВЫВОД ВОПРОСОВ
	std::string question_or_answer;
	std::string user_answer;
	short int correct_user_answer_num = 0;

	ifs_test.seekg(14 + description.size() + 20 + 1 + 12);
	while (!ifs_test.eof())
	{
		getline(ifs_test, question_or_answer); // чтение вопроса из файла
		ofs_test_result << question_or_answer << std::endl; // запись вопроса в файл

		std::cout << "Вопрос " << question_or_answer << std::endl;
		std::cout << "Ваш ответ: "; std::cin >> user_answer; std::cin.ignore(LLONG_MAX, '\n'); // ignore - нужен, так как иначе можно будет ввести 2 2 2 2, 
		// и символы после пробелов пойду отвечать на следующий вопросы,
		// не идеально работает, так как, если написать 2 2, то считает только первый символ, 
		// который может быть ответом.

		getline(ifs_test, question_or_answer); // чтение ответа из файла
		ofs_test_result << "Ваш ответ: " << user_answer << std::endl; // запись ответа пользователя в файл
		ofs_test_result << "Правильный ответ: " << question_or_answer << std::endl << std::endl; // запись правильного ответа в файл

		if (question_or_answer == user_answer)
		{
			this->set_color(2, 0); std::cout << "Вы ответили верно!" << std::endl << std::endl; this->set_color(15, 0);
			++correct_user_answer_num;
		}
		else
		{
			this->set_color(4, 0); std::cout << "Вы ответили неверно! " << "Правильный ответ: " << question_or_answer << std::endl << std::endl; this->set_color(15, 0);
		}

		getline(ifs_test, question_or_answer); // чтение переноса строки между одним вопросом с ответом и следующим вопросом с ответом из файла
	}

// ИТОГИ ТЕСТА
	ofs_test_result << correct_user_answer_num << "/" << questions_num;
	std::cout << "Вы ответили верно на " << correct_user_answer_num << " из " << questions_num << " вопросов" << std::endl << std::endl; system("pause");

	ifs_test.close();
	ofs_test_result.close();
}


void User::show_tests_results() const
{
	system("cls");
	this->set_color(9, 0); std::cout << "РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЙ (чтобы вернуться назад, нажмите backspace)"; this->set_color(15, 0);

	if (std::filesystem::is_directory(this->path + "users/" + this->crypt(this->login, 10) + "/tests results/"))
	{
		if (this->are_files_exist(this->path + "users/" + this->crypt(this->login, 10) + "/tests results/"))
		{
			std::string user_results;
			for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users/" + this->crypt(this->login, 10) + "/tests results/")) // возвращает пути ко всем файлам из директории
			{
				std::ifstream ifs_tests_results(path, std::ios::in);
				std::cout << std::endl << std::endl << "Результаты за " << path.filename() << ": " << std::endl; // path.filename() выводится с кавычками, так как оператор >> у path перегружен так
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
	this->set_color(4, 0); std::cout << std::endl << std::endl << "ни одно тестирование не пройдено" << std::endl; this->set_color(15, 0);
	system("pause");
}