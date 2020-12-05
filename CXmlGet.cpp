#include "pch.h"
#include "CXmlGet.h"
#include "CStringHandle.h"

CStringHandle strHandl;

int CXmlGet::GetXMLBuffer_Str(const char* in_XMLBuffer, const char* in_FieldName, char* out_Value)
{
	if (in_XMLBuffer == NULL ||
		in_FieldName == NULL ||
		out_Value == NULL) {
		return -1;
	}
	char* p_start, * p_end;
	p_start = p_end = NULL;

	char start_buf[51], end_buf[51];
	memset(start_buf, 0, sizeof(start_buf));
	memset(end_buf, 0, sizeof(end_buf));

	snprintf(start_buf, 50, "<%s>", in_FieldName);
	snprintf(end_buf, 50, "</%s>", in_FieldName);

	p_start = (char*)strstr(in_XMLBuffer, start_buf);
	if (p_start != NULL)
		p_end = (char*)strstr(p_start, end_buf);

	if (p_start == NULL || p_end == NULL)
		return -1;

	int m_NameLen = strlen(in_FieldName);
	int m_ValueLen = p_end - p_start - m_NameLen - 2 + 1;

	strHandl._strncpy(out_Value, p_start + m_NameLen + 2, m_ValueLen - 1);
	out_Value[m_ValueLen - 1] = 0;

	strHandl.delete_lr_char(out_Value, ' ');

	return (int)(p_end+m_NameLen + 3);
}

int CXmlGet::GetXMLBuffer_Int(const char* in_XMLBuffer, const char* in_FieldName, int* out_Value)
{
	if (in_XMLBuffer == NULL ||
		in_FieldName == NULL ||
		out_Value == NULL) {
		return -1;
	}

	int ret = -1;
	char value[25]; // 字段内容缓冲区大小
	memset(value, 0, sizeof(value));

	ret = GetXMLBuffer_Str(in_XMLBuffer, in_FieldName, value);

	if (ret == -1)
		return -1;

	*out_Value = atoi(value);

	return 0;
}

int CXmlGet::GetXMLBuffer_Double(const char* in_XMLBuffer, const char* in_FieldName, double* out_Value)
{
	if (in_XMLBuffer == NULL ||
		in_FieldName == NULL ||
		out_Value == NULL) {
		return -1;
	}

	int ret = -1;
	char value[51]; // 字段内容缓冲区大小
	memset(value, 0, sizeof(value));

	ret = GetXMLBuffer_Str(in_XMLBuffer, in_FieldName, value);

	if (ret == -1)
		return -1;

	*out_Value = atof(value);

	return 0;
}
