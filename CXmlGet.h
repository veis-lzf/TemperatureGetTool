#pragma once
class CXmlGet
{
public:
	int GetXMLBuffer_Str(const char* in_XMLBuffer, const char* in_FieldName, char* out_Value);
	int GetXMLBuffer_Int(const char* in_XMLBuffer, const char* in_FieldName, int* out_Value);
	int GetXMLBuffer_Double(const char* in_XMLBuffer, const char* in_FieldName, double* out_Value);
};

