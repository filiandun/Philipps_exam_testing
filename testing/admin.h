#pragma once
#include "users.h"
#include "user.h"


class Admin : protected Users
{
public:
	Admin() = default;
	~Admin() = default;

public:
	void new_user() final override; // работает
	void edit_user(); // работает
	void delete_user(); // работает

	void new_test();
	void edit_test();
	void delete_test();
	void show_tests_results() final override;

};

