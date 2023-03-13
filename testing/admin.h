#pragma once
#include "user.h"


class Admin : public User
{
public:
	Admin();
	~Admin() = default;

	void operator=(const Admin& admin);

public:
	void new_user() const;
	void edit_user() const;
	void delete_user() const;

	void new_test() const;
	void edit_test() const;
	void delete_test() const;
	void show_tests_results() const;
};
