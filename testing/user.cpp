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
	std::cout << "ВХОД (чтобы вернуться назад, нажмите backspace)" << std::endl;


	std::cout << "введите логин: "; std::cin >> this->login;
	while (this->is_login_free(this->login + ".txt"))
	{
		std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; std::cin >> this->login;
	}

	std::cout << "введите пароль: "; std::cin >> this->password;
	while (!this->is_password_correct(this->password))
	{
		std::cout << "неверный пароль, попробуйте ещё раз: "; std::cin >> this->password;
	}
}


void Users::new_user()
{
	std::cout << "РЕГИСТРАЦИЯ (чтобы вернуться назад, нажмите backspace)" << std::endl;


	std::cout << "введите ваше ФИО: " << std::endl; std::getline(std::cin, this->fio);

	std::cout << "придумайте ваш логин: " << std::endl; std::cin >> this->login;
	while (!this->is_login_free(this->login + ".txt"))
	{
		std::cout << "пользователь с таким логином уже существует, попробуйте ещё раз: " << std::endl; std::cin >> this->login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "придумайте ваш пароль: " << std::endl; std::cin >> this->password;
		break;
	}

	this->write_to_file();
}





bool Users::is_login_free(std::string login)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path)) // возвращает пути ко всем файлам из директории
	{
		std::filesystem::path file_name = path.filename(); // возвращает именно имя файла из пути
		if (file_name == login) // сравнение полученного имени файла и логина, который нужно проверить на свободность
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
	std::string path = this->path; path.append(this->login); path.append(".txt"); // костыль
	this->output_f.open(path, std::ios::out | std::ios::app); // ios::app - для записи в конец файла

	this->output_f << this->fio << std::endl;
	this->output_f << this->login << std::endl;;
	this->output_f << this->password << std::endl << std::endl;;

	this->output_f.close();
}


void Users::read_from_file() // read from file
{
	std::string path = this->path; path.append(this->login); path.append(".txt"); // костыль
	this->input_f.open(path, std::ios::in);

	getline(this->input_f, this->fio);
	getline(this->input_f, this->login);
	getline(this->input_f, this->password);

	this->input_f.close();
}





void Users::testing()
{
	this->input_f.open("D://IT/Repositories/Philipps_exam_testing/testing/direction/mathematics.txt", std::ios::in);
	this->output_f.open(this->path + this->login + ".txt", std::ios::out | std::ios::app);

	short int question_num = 1;
	std::string question_or_answer;
	std::string user_answer;
	short int correct_user_answer = 0;

	std::cout << "ТЕСТИРОВАНИЕ ПО МАТЕМАТИКЕ" << std::endl;
	while (!this->input_f.eof())
	{
		getline(this->input_f, question_or_answer); // считывание вопроса

		std::cout << question_num << ". " << question_or_answer << std::endl;
		std::cout << "Ваш ответ: "; std::cin >> user_answer; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore - нужен, так как иначе можно будет ввести 2 2 2 2, 
																																// и символы после пробелов пойду отвечать на следующий вопросы,
																																// не идеально работает, так как, если написать 2 2, то считает только первый символ, 
																																// который может быть ответом.

		getline(this->input_f, question_or_answer); // считывание ответа

		if (question_or_answer == user_answer)
		{
			std::cout << "Вы ответили верно!" << std::endl << std::endl;
			++correct_user_answer;
		}
		else
		{
			std::cout << "Вы ответили неверно! " << "Правильный ответ: " << question_or_answer << std::endl << std::endl;
		}

		getline(this->input_f, question_or_answer); // считывание переноса строки между одним вопросом с ответом и следующим вопросом с ответом
		++question_num;
	}

	this->output_f << "\n" << correct_user_answer << "/" << 6;
	std::cout << "Вы ответили на " << correct_user_answer << " из 6 вопросов." << std::endl;

	this->input_f.close();
	this->output_f.close();
}
