#include "admin.h"


Admin::Admin()
{
	if (this->is_login_free("admin"))
	{
		std::cout << "ДОБРОГО ВРЕМЕНИ СУТОК, ВЫ БЕРЁТЕ НА СЕБЯ РОЛЬ АДМИНИСТРАТОРА" << std::endl;
		std::cout << "введите ваше ФИО: "; getline(std::cin, this->fio);
		std::cout << "ваш логин установлен автоматически: admin" << std::endl;
		std::cout << "придумайте себе пароль: "; getline(std::cin, this->password);

		this->write_to_file();
	}
	else
	{
		this->login = "admin";
		this->read_from_file();
	}
}

void Admin::operator=(const Admin& admin)
{
	this->fio = admin.fio;
	this->login = admin.login;
	this->password = admin.password;
}







void Admin::new_user() const
{
	std::cout << "СОЗДАНИЕ НОВОГО ПОЛЬЗОВАТЕЛЯ (чтобы вернуться назад, нажмите backspace)" << std::endl;

	User new_user;

	std::cout << "введите ФИО нового пользователя: "; std::getline(std::cin, new_user.fio);

	std::cout << "придумайте логин нового пользователя: "; std::cin >> new_user.login;
	while (!this->is_login_free(new_user.login))
	{
		std::cout << "пользователь с таким логином уже существует, попробуйте ещё раз: "; std::cin >> new_user.login;
	}

	while (true) // user.is_password_simple(password)
	{
		std::cout << "придумайте пароль нового пользователя: "; std::cin >> new_user.password;
		break;
	}

	new_user.write_to_file();
}

void Admin::edit_user() const
{
	std::cout << "ИЗМЕНЕНИЕ ДАННЫХ ПОЛЬЗОВАТЕЛЯ (чтобы вернуться назад, нажмите backspace)" << std::endl;

	User edit_user;

	std::cout << "введите логин пользователя, данные которого хотите изменить: "; std::cin >> edit_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (this->is_login_free(edit_user.login))
	{
		std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; std::cin >> edit_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "введите новые ФИО пользователя: "; std::getline(std::cin, edit_user.fio);

	while (true) // user.is_password_simple(password)
	{
		std::cout << "введите новый пароль пользователя: "; std::cin >> edit_user.password; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}

	edit_user.write_to_file();

	std::cout << std::endl << "ДАННЫЕ ПОЛЬЗОВАТЕЛЯ УСПЕШНО ИЗМЕНЕНЫ" << std::endl; system("pause");
}


void Admin::delete_user() const
{
	std::cout << "УДАЛЕНИЕ ДАННЫХ ПОЛЬЗОВАТЕЛЯ (чтобы вернуться назад, нажмите backspace)" << std::endl;

	std::string login_user_to_delete;

	std::cout << "введите логин пользователя, данные которого вы хотите удалить: "; std::cin >> login_user_to_delete; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (this->is_login_free(login_user_to_delete))
	{
		std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; std::cin >> login_user_to_delete; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::filesystem::remove_all(this->path + "users/" + login_user_to_delete);

	std::cout << std::endl << "ПОЛЬЗОВАТЕЛЬ УСПЕШНО УДАЛЁН" << std::endl; system("pause");
}






void Admin::new_test() const
{
	std::cout << "СОЗДАНИЕ НОВОГО ТЕСТА (чтобы вернуться назад, нажмите backspace)" << std::endl;

	std::string file_name; std::cout << "введите название будущего теста: "; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); getline(std::cin, file_name);
	while (!this->are_tests_names_free(file_name))
	{
		std::cout << "это имя теста уже занято, попробуйте ещё раз: "; getline(std::cin, file_name);
	}

	std::ofstream new_file_with_test(this->path + "tests/" + file_name + ".txt"); // создание потока для нового файла с тестом

	std::string description; std::cout << "введите небольшое описание к тесту: "; getline(std::cin, description); new_file_with_test << "&Description: " << description << std::endl << std::endl;
	short int questions_num; std::cout << "введите кол-во вопросов в будущем тесте: "; std::cin >> questions_num; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); new_file_with_test << "&Questions num: " << questions_num << std::endl << std::endl;

	new_file_with_test << "&Test:" << std::endl;
	std::string question_or_answer; 
	for (int i = 0; i < questions_num; ++i)
	{				
		std::cout << std::endl << "введите вопрос: "; getline(std::cin, question_or_answer); 
		new_file_with_test << i + 1 << ": " << question_or_answer << std::endl;

		std::cout << "введите ответ на вопрос: "; getline(std::cin, question_or_answer);
		i == (questions_num - 1) ? new_file_with_test << question_or_answer : new_file_with_test << question_or_answer << std::endl << std::endl; // тернарный оператора нужен для того, чтобы в последнем вопросе не ставились лишние два endl
	}
	new_file_with_test.close();

	std::cout << std::endl << "ТЕСТ УСПЕШНО СОЗДАН" << std::endl; system("pause");
}


void Admin::edit_test() const
{
	std::cout << "ИЗМЕНЕНИЕ СУЩЕСТВУЮЩЕГО ТЕСТА (чтобы вернуться назад, нажмите backspace)" << std::endl;

	std::string file_name; std::cout << "введите название теста: "; getline(std::cin, file_name);
	while (this->are_tests_names_free(file_name))
	{
		std::cout << "тест не найден, попробуйте ещё раз: "; getline(std::cin, file_name);
	}
	std::cout << std::endl << "ТЕСТ НАЙДЕН" << std::endl; system("pause");
}


void Admin::delete_test() const
{
	std::cout << "УДАЛЕНИЕ ТЕСТА (чтобы вернуться назад, нажмите backspace)" << std::endl;

	std::string file_name; std::cout << "введите название теста: "; getline(std::cin, file_name);

	while (this->are_tests_names_free(file_name))
	{
		std::cout << "тест не найден, введите название теста повторно: "; getline(std::cin, file_name);
	}
	std::filesystem::remove(this->path + "tests/" + file_name + ".txt"); // само удаление теста

	std::cout << std::endl << "ТЕСТ УСПЕШНО УДАЛЁН" << std::endl; system("pause");
}


void Admin::show_tests_results() const
{
	std::cout << "РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЙ (чтобы вернуться назад, нажмите backspace)" << std::endl;

	User temp_user;

	std::cout << "введите логин пользователя, результаты которого хотите посмотреть: "; std::cin >> temp_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (this->is_login_free(temp_user.login))
	{
		std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; std::cin >> temp_user.login; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	temp_user.show_tests_results(); 
}
