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
	void new_user() final override; // ��������
	void edit_user(); // ��������
	void delete_user(); // ��������

	void new_test();
	void edit_test();
	void delete_test(); // ��������
	void show_tests_results() final override;

};

