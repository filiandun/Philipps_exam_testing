#include <iostream>
#include <string>
#include <ctime> // для работы со временем

//#include "admin.h"
//#include "user.h"
#include "menu.h"



int main()
{
	setlocale(LC_ALL, "rus");

	system("cls");

	Admin admin;
	User user;

// ПРИ СОЗДАНИИ ОБЪЕКТОВ КЛАССОВ, ДЛЯ КАЖДОГО ОТДЕЛЬНО СОЗДАЁТСЯ ОБЪЕКТ КЛАССА MENU, ИЗ-ЗА ЭТОГО USER И ADMIN В MAIN ПОСТОЯННО ОЧИЩАЮТСЯ И СОЗДАЮТСЯ НОВЫМИ
	MainMenu main_menu(&user, &admin);
	main_menu.menu();

	UserMenu user_menu(&user, &admin);
	user_menu.menu();

	AdminMenu admin_menu(&user, &admin);
	admin_menu.menu();


	return 0;
}