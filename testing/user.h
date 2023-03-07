#pragma once
#include "users.h"

class User : protected Users
{
public:
	User() = default;
	~User() = default;

public:
	void new_user() final override;
	void old_user();

	void pass_the_test();
	void show_tests_results() final override;

	friend class Admin;
};

