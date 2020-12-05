#pragma once
class CStringHandle
{
public:
	size_t _strlen(const char* str);

	char* _strcpy(char* dest, const char* src);

	char* _strncpy(char* dest, const char* src, size_t len);

	char* _strcat(char* dest, const char* src);

	char* _strncat(char* dest, const char* src, size_t len);

	char* _strchr(const char* s, const int c);

	char* _strrchr(const char* s, const int c);

	int _strcmp(const char* s1, const char* s2);

	int _strncmp(const char* s1, const char* s2, const size_t n);

	char* _strstr(const char* str, const char* substr);

	char* _strcpy_s(char* dest, const size_t destlen, const char* src);

	char* _strncpy_s(char* dest, const size_t destlen, const char* src, const size_t n);

	char* _strcat_s(char* dest, const size_t destlen, const char* src);

	char* _strncat_s(char* dest, const size_t destlen, const char* src, const size_t n);

	void delete_lchar(char* str, const char in_char);

	void delete_rchar(char* str, const char in_char);

	void delete_lr_char(char* str, const char in_char);

	void delete_mid_str(char* str, const char* in_str);


};

