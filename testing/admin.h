#pragma once
#include "users.h"
#include "user.h"


class Admin : protected Users
{
public:
	Admin() = default;
	~Admin() = default;

private:
	bool are_tests_names_free(std::string file_name);

public:
	void new_user() final override; // работает
	void edit_user(); // работает
	void delete_user(); // работает

	void new_test();
	void edit_test();
	void delete_test(); // работает
	void show_tests_results() final override;

};

