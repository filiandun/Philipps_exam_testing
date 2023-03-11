#include "user.h"


User::User(std::string path)
{
	this->path = path;
}

void User::operator=(const User& user)
{
	this->fio = user.fio;
	this->login = user.login;
	this->password = user.password;
}






void User::write_to_file()
{
	std::filesystem::create_directories(this->path + "users/" + this->login); // создание папки нового пользователя

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
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users")) // возвращает пути ко всем папкам из директории
	{
		if (path == this->path + "users/" + login) // сравнение
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
	std::cout << "ВХОД (чтобы вернуться назад, нажмите backspace)" << std::endl;


	std::cout << "введите ваш логин: "; std::cin >> this->login;
	while (this->is_login_free(this->login))
	{
		std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; std::cin >> this->login;
	}

	std::cout << "введите ваш пароль: "; std::cin >> this->password;
	while (!this->is_password_correct(this->password))
	{
		std::cout << "неверный пароль, попробуйте ещё раз: "; std::cin >> this->password;
	}
}


void User::new_user()
{
	std::cout << "РЕГИСТРАЦИЯ (чтобы вернуться назад, нажмите backspace)" << std::endl;


	std::cout << "введите ваше ФИО: "; std::getline(std::cin, this->fio);

	std::cout << "придумайте ваш логин: "; std::cin >> this->login;
	while (!this->is_login_free(this->login))
	{
		std::cout << "пользователь с таким логином уже существует, попробуйте ещё раз: "; std::cin >> this->login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "придумайте ваш пароль: "; std::cin >> this->password;
		break;
	}

	this->write_to_file();
}






void User::pass_the_test()
{
	std::filesystem::create_directories(this->path + "users/" + this->login + "/tests results"); // создание папки tests для сохранения тестов

	time_t now = time(0); // запись текущей даты и времени в строку // не очень нравится весь этот блок, может с ними ещё что-то можно сделать
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

	this->output_f.open(this->path + "users/" + this->login + "/tests results/" + localtime + ".txt", std::ios::out | std::ios::app);

	std::cout << "Тесты: " << std::endl;
	std::filesystem::path path;
	for (std::filesystem::path temp_path : std::filesystem::directory_iterator(this->path + "tests/")) // возвращает пути ко всем папкам из директории
	{
		std::cout << temp_path.filename() << std::endl;
		path = temp_path;
	}

	system("pause"); system("cls");
	std::cout << "ТЕСТИРОВАНИЕ ПО МАТЕМАТИКЕ" << std::endl;
	this->input_f.open(path, std::ios::in);

	std::string description; this->input_f.seekg(14); getline(this->input_f, description); std::cout << "Краткое описание к тесту: " << description << std::endl;
	short int questions_num; this->input_f.seekg(14 + description.size() + 20); this->input_f >> questions_num; std::cout << "Кол-во вопросов в тесте: " << questions_num << std::endl << std::endl;

	std::string question_or_answer;
	std::string user_answer;
	short int correct_user_answer_num = 0;

	this->input_f.seekg(14 + description.size() + 20 + 1 + 12);
	while (!this->input_f.eof())
	{
		getline(this->input_f, question_or_answer); // чтение вопроса из файла
		this->output_f << question_or_answer << std::endl; // запись вопроса в файл

		std::cout << "Вопрос " << question_or_answer << std::endl;
		std::cout << "Ваш ответ: "; std::cin >> user_answer; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore - нужен, так как иначе можно будет ввести 2 2 2 2, 
		// и символы после пробелов пойду отвечать на следующий вопросы,
		// не идеально работает, так как, если написать 2 2, то считает только первый символ, 
		// который может быть ответом.

		getline(this->input_f, question_or_answer); // чтение ответа из файла
		this->output_f << "Ваш ответ: " << user_answer << std::endl; // запись ответа пользователя в файл
		this->output_f << "Правильный ответ: " << question_or_answer << std::endl << std::endl; // запись правильного ответа в файл

		if (question_or_answer == user_answer)
		{
			std::cout << "Вы ответили верно!" << std::endl << std::endl;
			++correct_user_answer_num;
		}
		else
		{
			std::cout << "Вы ответили неверно! " << "Правильный ответ: " << question_or_answer << std::endl << std::endl;
		}

		getline(this->input_f, question_or_answer); // чтение переноса строки между одним вопросом с ответом и следующим вопросом с ответом из файла
	}

	this->output_f << correct_user_answer_num << "/" << questions_num;
	std::cout << "Вы ответили верно на " << correct_user_answer_num << " из " << questions_num << " вопросов" << std::endl;

	this->input_f.close();
	this->output_f.close();
}


void User::show_tests_results()
{
	std::cout << "РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЙ (чтобы вернуться назад, нажмите backspace)";

	std::string user_results;
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path + "users/" + this->login + "/tests results/")) // возвращает пути ко всем файлам из директории
	{
		this->input_f.open(path, std::ios::out);
		std::cout << std::endl << std::endl << "Результаты за  " << path.filename() << ": " << std::endl; // path.filename() выводится с кавычками, так как оператор >> у path перегружен так
		while (!this->input_f.eof())
		{
			getline(this->input_f, user_results);
			std::cout << user_results << std::endl;
		}
		this->input_f.close();
	}
	
	std::cout << std::endl;
	system("pause");
}

//template <class _Elem, class _Traits>
//_STD basic_ostream<_Elem, _Traits>& operator<<(_STD basic_ostream<_Elem, _Traits>& _Ostr, const std::filesystem::path& _Path) {
//	// insert a path into a stream
//	std::cout << "dd";
//	return _Ostr << _STD quoted(_Path.string<_Elem, _Traits>());
//}

