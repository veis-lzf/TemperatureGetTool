#include "pch.h"
#include "CStringHandle.h"

size_t CStringHandle::_strlen(const char* str)
{
	size_t nlen = 0;

	while (*str++ != '\0') ++nlen;

	return nlen;
}

char* CStringHandle::_strcpy(char* dest, const char* src)
{
	while (*src != '\0') *dest++ = *src++;

	*dest = '\0';

	return dest;
}

char* CStringHandle::_strncpy(char* dest, const char* src, size_t len)
{
	size_t i = 0;
	size_t src_len = _strlen(src);

	if (src_len > len) src_len = len;

	while (i < src_len)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';

	return dest;
}

char* CStringHandle::_strcat(char* dest, const char* src)
{
	int dest_len = _strlen(dest);
	int i = 0;

	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return dest;
}

char* CStringHandle::_strncat(char* dest, const char* src, size_t len)
{
	size_t dest_len = _strlen(dest);
	size_t src_len = _strlen(src);
	size_t i = 0;

	if (src_len > len) src_len = len;

	while (i < src_len)
	{
		dest[dest_len + i] = src[i];
		++i;
	}
	dest[dest_len + i] = '\0';
	return dest;
}

char* CStringHandle::_strchr(const char* s, const int c)
{
	size_t len = _strlen(s);
	size_t i = 0;

	while (i < len) { if (s[i] == c) return (char*)(&(s[i])); ++i; }

	return NULL;
}

char* CStringHandle::_strrchr(const char* s, const int c)
{
	size_t len = _strlen(s);
	size_t i = len - 1;

	while (i >= 0) { if (s[i] == c) return (char*)(&(s[i])); --i; }

	return NULL;
}

int  CStringHandle::_strcmp(const char* s1, const char* s2)
{
	size_t i = 0;
	size_t len = 0;
	size_t s1_len = _strlen(s1);
	size_t s2_len = _strlen(s2);

	if (s1_len > s2_len) len = s2_len;
	else len = s1_len;

	for (i = 0; i < len; ++i)
	{
		if (s1[i] == s2[i]) continue;
		else break;
	}

	if ((i == len) && (s1_len == s2_len)) return 0;

	if (s1[i] > s2[i]) return 1;

	return -1;
}

int CStringHandle::_strncmp(const char* s1, const char* s2, const size_t n)
{
	size_t i = 0;

	for (i = 0; i < n; ++i)
	{
		if (s1[i] == s2[i]) continue;
		else break;
	}

	if (i == n) return 0;
	else if (s1[i] > s2[i]) return 1;

	return -1;
}

char* CStringHandle::_strstr(const char* str, const char* substr)
{
	char* pos = (char*)str; // 待搜索字符串的位置。
	char* pos1 = 0;

	while (1)
	{
		if (pos[0] == 0) break;  // 如果待搜索的字符串已结束，break。

		pos1 = _strchr(pos, substr[0]);  // 在pos中查找子字符串的首字符。

		if (pos1 == 0) return 0;  // 如果没有找到，直接返回0。

		if (_strncmp(pos1, substr, _strlen(substr)) == 0) return pos1; // 如果找到了，返回找到的地址。

		pos++;  // 待搜索的位置后移一个字节。
	}

	return NULL;
}

// 安全版本的字符串拷贝函数
char* CStringHandle::_strcpy_s(char* dest, const size_t destlen, const char* src)
{
	size_t src_len = _strlen(src);
	size_t len = destlen;
	size_t i = 0;

	if (src_len < len) len = src_len;

	memset(dest, 0, destlen);

	for (i = 0; i < len; ++i)
	{
		dest[i] = src[i];
	}
	return dest;
}

// 安全版本的字符串拷贝函数
char* CStringHandle::_strncpy_s(char* dest, const size_t destlen, const char* src, const size_t n)
{
	size_t len = destlen;
	size_t i = 0;

	if (n < len) len = n;

	memset(dest, 0, destlen);

	for (i = 0; i < len; ++i)
	{
		dest[i] = src[i];
	}
	return dest;
}

// 安全版本的字符串连接函数
char* CStringHandle::_strcat_s(char* dest, const size_t destlen, const char* src)
{
	int i = 0;
	int src_len = _strlen(src);
	int len = destlen - _strlen(dest) - 1; // 剩余可用空间
	int start = _strlen(dest);

	memset(dest + start, 0, len);

	if (src_len < len) len = src_len;

	for (i = 0; i < len; ++i)
	{
		dest[start + i] = src[i];
	}

	return dest;
}

// 安全版本的字符串连接函数
char* CStringHandle::_strncat_s(char* dest, const size_t destlen, const char* src, const size_t n)
{
	size_t i = 0;
	size_t len = destlen - _strlen(dest) - 1; // 剩余可用空间
	size_t start = _strlen(dest);

	memset(dest + start, 0, len);

	if (n < len) len = n;

	for (i = 0; i < len; ++i)
	{
		dest[start + i] = src[i];
	}

	return dest;
}

// 删除字符串左边指定的字符
void CStringHandle::delete_lchar(char* str, const char in_char)
{
	int len = _strlen(str);
	char *strTemp = new char[len + 1];
	int iTemp = 0;

	if (str == 0) return;
	if (_strlen(str) == 0) return;

	memset(strTemp, 0, len + 1);
	strcpy(strTemp, str);

	while (strTemp[iTemp] == in_char)  iTemp++;
	memset(str, 0, len + 1);
	strcpy(str, strTemp + iTemp);
	delete []strTemp;
	return;
}

// 删除字符串右边指定的字符
void CStringHandle::delete_rchar(char* str, const char in_char)
{
	size_t len = _strlen(str);
	if (str == NULL) return;

	while (len > 0)
	{
		if (str[--len] == in_char)
			str[len] = '\0';
		else break;
	}
}

// 删除字符串两边指定的字符
void CStringHandle::delete_lr_char(char* str, const char in_char)
{
	delete_lchar(str, in_char);
	delete_rchar(str, in_char);
}

// 删除字符串中间的字符串
void CStringHandle::delete_mid_str(char* str, const char* in_str)
{
	int i = 0;
	int nlen = 0;
	char* p = NULL;

	if (str == NULL || in_str == NULL) return;

	nlen = _strlen(in_str);

	if (_strlen(str) == 0 || nlen == 0) return;

	p = _strstr(str, in_str);

	if (p != NULL) _strcpy(p, p + nlen);
}
