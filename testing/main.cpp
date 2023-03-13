#include <iostream>
#include <string>

#include "menu.h"


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		std::filesystem::create_directories("C://Super Duper Mega Testing/");
		std::filesystem::create_directories("C://Super Duper Mega Testing/Tests/");
		std::filesystem::create_directories("C://Super Duper Mega Testing/Users/");
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		std::cout
			<< "what():  " << ex.what() << '\n'
			<< "path1(): " << ex.path1() << '\n'
			<< "path2(): " << ex.path2() << '\n'
			<< "code().value():	   " << ex.code().value() << '\n'
			<< "code().message():  " << ex.code().message() << '\n'
			<< "code().category(): " << ex.code().category().name() << '\n';
	}

	Admin admin;
	User user;

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