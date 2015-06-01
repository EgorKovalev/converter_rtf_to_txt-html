#include "stdafx.h"
#include "CBaseConverter.h"

CBaseConverter::CBaseConverter()
{
	
}

CBaseConverter::~CBaseConverter()
{

}

bool CBaseConverter::HasErrors() const
{
	return !m_sLastError.empty();
}

string CBaseConverter::GetLastError() const
{
	return m_sLastError;
}

string CBaseConverter::IntToString(int number)
{
    stringstream ss;
    ss << number;
    return string(ss.str());
}

void CBaseConverter::SetInputFilePath(const string &sInputFilePath)
{
	m_sInputFilePath = sInputFilePath;
	//TODO: check, if file exist on disk
	//TODO: check supported file formats
}

void CBaseConverter::SetOutputFilePath(const string &sOutputFilePath)
{
	m_sOutputFilePath = sOutputFilePath;
	//TODO: check supported file formats
}

string CBaseConverter::getFileExtension(const string &filePath)
{
	const size_t lastPointPosition = filePath.rfind(".");
	const string extension = lastPointPosition == string::npos ? "" : filePath.substr(lastPointPosition + 1);
	return extension;
}