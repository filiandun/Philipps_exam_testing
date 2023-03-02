#include "user.h"

Users::Users()
{
	
}

Users::Users(std::string fio, std::string login, std::string password)
{
	this->fio = fio;
	this->login = login;
	this->password = password;
}

Users::~Users()
{
}



bool Users::is_login_free(std::string login)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path)) // возвращает пути ко всем файлам из директории
	{
		std::filesystem::path file_name = path.filename(); // возвращает именно имя файла из пути

		if (file_name == login) // сравнение полученного имени файла и логин, который нужно проверить на свободность
		{
			return false;
		}
	}
	return true;
}

bool Users::is_password_correct(std::string password)
{
	std::ifstream input_f(this->path + "neloxod" + ".txt", std::ios::in);
	std::string str;
	std::string temp_str;
	while (getline(input_f, temp_str)) // считывае с файла
	{
		str += (temp_str);
	}

	if (str.find(password) == (str.size() - password.size())) // сложно объяснить и я не до конца сам понял, но оно частично работает (если убрать некоторые числа перед паролем, то он всё равно будет угадан)
	{
		std::cout << "true" << std::endl;
		return true;
	}

	std::cout << "false" << std::endl;
	return false;
}




void Users::write_to_file()
{
	// write to file
	std::string path = this->path; path.append(this->login); path.append(".txt"); // костыль
	this->output_f.open(path, std::ios::out | std::ios::app); // ios::app - для записи в конец файла

	this->output_f << this->fio << std::endl;
	this->output_f << this->login << std::endl;;
	this->output_f << this->password << std::endl << std::endl;;

	this->output_f.close();

	// add login
	//this->all_logins += (path + " ");
}
