#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>

#include "admin.h"
#include "user.h"


int main()
{
	setlocale(LC_ALL, "rus");
	system("cls");


	Admin admin;
	//admin.new_user();

	//system("cls");
	//admin.edit_user();

	//system("cls");
	//admin.delete_user();



	//system("cls");
	//admin.new_test();

	//system("cls");
	//admin.edit_test();

	//system("cls");
	//admin.delete_test();



	std::cout << "ТЕСТИРОВАНИЕ" << std::endl;
	std::cout << "> вход" << std::endl;
	std::cout << "  регистрация" << std::endl;

	User user;
	short int button = 0;
	while (true)
	{
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
				system("cls");
				user.old_user();

				system("cls");
				user.pass_the_test();			
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
				user.new_user();

				system("cls");
				user.pass_the_test();

			}
		}
	}




	return 0;
}