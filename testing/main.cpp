#include <iostream>
#include <string>
#include <conio.h>

#include "user.h"
#include "functions.h"


int main()
{
	setlocale(LC_ALL, "rus");
	system("cls");

	std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
	std::cout << "> вход" << std::endl;
	std::cout << "  регистрация" << std::endl;

	while (true)
	{
		short int button = 0;
		button = _getch();

		if (button == 72) // если была нажата клавиша вверх (ВХОД)
		{
			system("cls");
			std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
			std::cout << "> вход" << std::endl;
			std::cout << "  регистрация" << std::endl;

			button = _getch();
			if (button == 13) // если была нажата кнопка enter
			{
				// В ИДЕАЛЕ, ПЕРЕБРОСИТЬ ЭТОТ ВХОД И РЕГИСТРАЦИЮ НИЖЕ В ОТДЕЛЬНЫЕ ФУНКЦИИ В КЛАССЕ USERS
				system("cls");
				std::cout << "ВХОД (чтобы вернуться назад, нажмите backspace)" << std::endl;

				Users user;

				std::string login;
				std::string password;

				std::cout << "введите логин: "; std::cin >> login;
				while (user.is_login_free(login + ".txt"))
				{
					std::cout << "пользователя с таким логином не существует, попробуйте ещё раз: "; std::cin >> login;
				}

				std::cout << "введите пароль: "; std::cin >> password;
				while (!user.is_password_correct(password)) // user.is_password_correct(password)
				{
					std::cout << "неверный пароль, попробуйте ещё раз: "; std::cin >> password;
				}
			}
		}

		if (button == 80) // если была нажата клавиша вниз (РЕГИСТРАЦИЯ)
		{
			system("cls");
			std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
			std::cout << "  вход" << std::endl;
			std::cout << "> регистрация" << std::endl;

			button = _getch();
			if (button == 13) // если была нажата кнопка enter
			{
				system("cls");
				std::cout << "РЕГИСТРАЦИЯ (чтобы вернуться назад, нажмите backspace)" << std::endl;

				Users user;

				std::string fio;

				std::string login;
				std::string password;

				std::cout << "введите ваше ФИО: " << std::endl; std::getline(std::cin, fio);

				std::cout << "придумайте ваш логин: " << std::endl; std::cin >> login;
				while (!user.is_login_free(login + ".txt"))
				{
					std::cout << "пользователь с таким логином уже существует, попробуйте ещё раз: " << std::endl; std::cin >> login;
				}

				while (true) // user.is_password_simple(password)
				{
					std::cout << "придумайте ваш пароль: " << std::endl; std::cin >> password;
					break;
				}
			}
		}
	}






// ТЕСТ ФУНКЦИИ НА КОРРЕКТНОСТЬ ПАРОЛЯ (НЕ ОЧЕНЬ УДАЧНАЯ ФУНКЦИЯ)
	//Users users;
	//users.is_password_correct("1234415");
	//users.is_password_correct("234415");
	//users.is_password_correct("34415");

	//users.is_password_correct("123441");


	return 0;
}