#include "users.h"


bool Users::is_login_free(std::string login)
{
	for (std::filesystem::path path : std::filesystem::directory_iterator(this->path)) // возвращает пути ко всем папкам из директории
	{
		if (path == this->path + login) // сравнение
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
	std::filesystem::create_directories(this->path + this->login); // создание папки нового пользователя

	std::string path = this->path; path.append(this->login); path.append("/"); path.append(this->login); path.append(".txt"); // костыль
	this->output_f.open(path, std::ios::out);

	this->output_f << this->fio << std::endl;
	this->output_f << this->login << std::endl;;
	this->output_f << this->password;

	this->output_f.close();
}


void Users::read_from_file() // read from file
{
	std::string path = this->path; path.append(this->login); path.append("/"); path.append(this->login); path.append(".txt"); // костыль
	this->input_f.open(path, std::ios::in);

	getline(this->input_f, this->fio);
	getline(this->input_f, this->login);
	getline(this->input_f, this->password);

	this->input_f.close();
}


void Users::show_tests_results()
{
	this->input_f.open(this->path + this->login + ".txt", std::ios::in);


}
