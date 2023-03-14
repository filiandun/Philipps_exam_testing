#include "menu.h"
#include "user.h"



Menu::Menu()
{
	this->user = nullptr;

	this->current_position = 0;
	this->max_position = 3;
}


Menu::Menu(User* user)
{
	this->user = user;

	this->current_position = 0;
	this->max_position = 3;
}






void Menu::do_it(short int current_position)
{
	switch (current_position)
	{
	case 0: system("cls"); user->old_user(); break;
	case 1: system("cls"); user->new_user(); break;
	case 2: exit(0);
	}
}


void Menu::choice() // функция выбора
{
	short int pressed_button;
	while (true)
	{
		pressed_button = _getch(); // считывание значения нажатой клавиши

		switch (pressed_button)
		{
		case 80: if (this->current_position + 1 < this->max_position) { ++this->current_position; }; this->menu(); return; // нажата клавиша вниз
		case 72: if (this->current_position - 1 >= 0) { --this->current_position; }; this->menu(); return; // нажата клавиша вверх
		case 13: this->do_it(this->current_position); return; // нажата клавиша enter

		default: break;
		}
	}
}


void Menu::menu()
{
	if (current_position == 0)
	{
		system("cls");
		this->set_color(9, 0); std::cout << "ПРОГРАММА ДЛЯ ПРОХОЖДЕНИЯ ТЕСТИРОВАНИЙ" << std::endl; this->set_color(15, 0);

		this->set_color(6, 0); std::cout << "> вход" << std::endl; this->set_color(15, 0);
		std::cout << "  регистрация" << std::endl << std::endl;

		std::cout << "  выход" << std::endl;

		this->choice();
	}

	if (current_position == 1)
	{
		system("cls");
		this->set_color(9, 0); std::cout << "ПРОГРАММА ДЛЯ ПРОХОЖДЕНИЯ ТЕСТИРОВАНИЙ" << std::endl; this->set_color(15, 0);

		std::cout << "  вход" << std::endl;
		this->set_color(6, 0); std::cout << "> регистрация" << std::endl << std::endl; this->set_color(15, 0);

		std::cout << "  выход" << std::endl;

		this->choice();
	}

	if (current_position == 2)
	{
		system("cls");
		this->set_color(9, 0); std::cout << "ПРОГРАММА ДЛЯ ПРОХОЖДЕНИЯ ТЕСТИРОВАНИЙ" << std::endl; this->set_color(15, 0);

		std::cout << "  вход" << std::endl;
		std::cout << "  регистрация" << std::endl << std::endl;

		this->set_color(6, 0); std::cout << "> выход" << std::endl; this->set_color(15, 0);

		this->choice();
	}
}










UserMenu::UserMenu(User* user)
{
	this->user = user;

	this->current_position = 0;
	this->max_position = 3;
}





void UserMenu::do_it(short int current_position)
{
	switch (current_position)
	{
	case 0: system("cls"); user->pass_the_test(); this->menu(); break;
	case 1: system("cls"); user->show_tests_results(); this->menu(); break;
	case 2: exit(0);
	}
}

void UserMenu::choice()
{
	short int pressed_button;
	while (true)
	{
		pressed_button = _getch(); // считывание значения нажатой клавиши

		switch (pressed_button)
		{
		case 80: if (this->current_position + 1 < this->max_position) { ++this->current_position; }; this->menu(); return; // нажата клавиша вниз
		case 72: if (this->current_position - 1 >= 0) { --this->current_position; }; this->menu(); return; // нажата клавиша вверх
		case 13: this->do_it(this->current_position); return; // нажата клавиша enter

		default: break;
		}
	}
}


void UserMenu::menu()
{
	if (this->current_position == 0)
	{
		system("cls");
		this->set_color(9, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << user->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		this->set_color(6, 0); std::cout << "> пройти тестирование" << std::endl; this->set_color(15, 0);
		std::cout << "  посмотреть результаты прошлых тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 1)
	{
		system("cls");
		this->set_color(9, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << user->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  пройти тестирование" << std::endl;
		this->set_color(6, 0); std::cout << "> посмотреть результаты прошлых тестирований" << std::endl << std::endl; this->set_color(15, 0);

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 2)
	{
		system("cls");
		this->set_color(9, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << user->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  пройти тестирование" << std::endl;
		std::cout << "  посмотреть результаты прошлых тестирований" << std::endl << std::endl;

		this->set_color(6, 0); std::cout << "> выйти" << std::endl; this->set_color(15, 0);

		this->choice();
	}
}








AdminMenu::AdminMenu(Admin* admin)
{
	this->admin = admin;

	this->current_position = 0;
	this->max_position = 8;
}





void AdminMenu::do_it(short int current_position)
{
	switch (current_position)
	{
	case 0: system("cls"); admin->new_user(); this->menu(); break;
	case 1: system("cls"); admin->edit_user(); this->menu(); break;
	case 2: system("cls"); admin->delete_user(); this->menu(); break;
	case 3: system("cls"); admin->new_test(); this->menu(); break;
	case 4: system("cls"); admin->edit_test(); this->menu(); break;
	case 5: system("cls"); admin->delete_test(); this->menu(); break;
	case 6: system("cls"); admin->show_tests_results(); this->menu(); break;

	case 7: exit(0);
	}
}


void AdminMenu::choice()
{
	short int pressed_button;
	while (true)
	{
		pressed_button = _getch(); // считывание значения нажатой клавиши

		switch (pressed_button)
		{
		case 80: if (this->current_position + 1 < this->max_position) { ++this->current_position; }; this->menu(); return; // нажата клавиша вниз
		case 72: if (this->current_position - 1 >= 0) { --this->current_position; }; this->menu(); return; // нажата клавиша вверх
		case 13: this->do_it(this->current_position); return; // нажата клавиша enter

		default: break;
		}
	}
}


void AdminMenu::menu()
{
	if (this->current_position == 0)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		this->set_color(6, 0); std::cout << "> зарегистрировать нового подопытного" << std::endl; this->set_color(15, 0);
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		std::cout << "  создать новое тестирование" << std::endl;
		std::cout << "  изменить существующее тестирование" << std::endl;
		std::cout << "  удалить существующее тестирование" << std::endl;
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 1)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		this->set_color(6, 0); std::cout << "> изменить данные существующего подопытного" << std::endl; this->set_color(15, 0);
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		std::cout << "  создать новое тестирование" << std::endl;
		std::cout << "  изменить существующее тестирование" << std::endl;
		std::cout << "  удалить существующее тестирование" << std::endl;
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 2)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		this->set_color(6, 0); std::cout << "> удалить данные существующего подопытного" << std::endl << std::endl; this->set_color(15, 0);

		std::cout << "  создать новое тестирование" << std::endl;
		std::cout << "  изменить существующее тестирование" << std::endl;
		std::cout << "  удалить существующее тестирование" << std::endl;
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 3)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		this->set_color(6, 0); std::cout << "> создать новое тестирование" << std::endl; this->set_color(15, 0);
		std::cout << "  изменить существующее тестирование" << std::endl;
		std::cout << "  удалить существующее тестирование" << std::endl;
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 4)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		std::cout << "  создать новое тестирование" << std::endl;
		this->set_color(6, 0); std::cout << "> изменить существующее тестирование" << std::endl; this->set_color(15, 0);
		std::cout << "  удалить существующее тестирование" << std::endl;
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 5)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		std::cout << "  создать новое тестирование" << std::endl;
		std::cout << "  изменить существующее тестирование" << std::endl;
		this->set_color(6, 0); std::cout << "> удалить существующее тестирование" << std::endl; this->set_color(15, 0);
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 6)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		std::cout << "  создать новое тестирование" << std::endl;
		std::cout << "  изменить существующее тестирование" << std::endl;
		std::cout << "  удалить существующее тестирование" << std::endl; 
		this->set_color(6, 0); std::cout << "> результаты тестирований" << std::endl << std::endl; this->set_color(15, 0);

		std::cout << "  выйти" << std::endl;

		this->choice();
	}

	if (this->current_position == 7)
	{
		system("cls");
		this->set_color(13, 0); std::cout << "ЗДРАВСТВУЙТЕ, " << admin->fio << ", ВЫБЕРИТЕ, ЧТО ВЫ ХОТИТЕ СДЕЛАТЬ: " << std::endl; this->set_color(15, 0);

		std::cout << "  зарегистрировать нового подопытного" << std::endl;
		std::cout << "  изменить данные существующего подопытного" << std::endl;
		std::cout << "  удалить данные существующего подопытного" << std::endl << std::endl;

		std::cout << "  создать новое тестирование" << std::endl;
		std::cout << "  изменить существующее тестирование" << std::endl;
		std::cout << "  удалить существующее тестирование" << std::endl;
		std::cout << "  результаты тестирований" << std::endl << std::endl;

		this->set_color(6, 0); std::cout << "> выйти" << std::endl;  this->set_color(15, 0);

		this->choice();
	}
}