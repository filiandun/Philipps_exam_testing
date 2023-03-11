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
	void edit_user(); // ��������
	void delete_user(); // ��������

	void new_test(); // ��������
	void edit_test(); // ��������
	void delete_test(); // ��������

	void show_tests_results();

};
