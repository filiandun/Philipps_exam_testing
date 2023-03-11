#pragma once
#include "user.h"


class Admin : public User
{
public:
	Admin();
	~Admin() = default;

	void operator=(const Admin& admin);

private:
	bool are_tests_names_free(std::string file_name);

public:
	void edit_user(); // работает
	void delete_user(); // работает

	void new_test(); // работает
	void edit_test(); // работает
	void delete_test(); // работает

	void show_tests_results();

};
