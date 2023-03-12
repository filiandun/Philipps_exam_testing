#include <iostream>
#include <string>

#include "menu.h"


int main()
{
	setlocale(LC_ALL, "rus");

	User user;
	Admin admin;


	Menu* menu = new Menu(&user);
	menu->menu();

	if (user.login != admin.login)
	{
		UserMenu user_menu(&user);
		user_menu.menu();
	}
	else
	{
		AdminMenu admin_menu(&admin);
		admin_menu.menu();
	}



	return 0;
}