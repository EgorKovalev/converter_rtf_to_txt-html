#ifndef C_BASE_CONVERTER__H
#define C_BASE_CONVERTER__H

using namespace std;

class CBaseConverter
{
protected:
	string m_sInputFilePath;
	string m_sOutputFilePath;
	string m_sLastError;

public:
	virtual void SetInputFilePath(const string &sInputFilePath);
	virtual void SetOutputFilePath(const string &sOutputFilePath);
	virtual void Convert() = 0;
	bool HasErrors() const;
	string GetLastError() const;
	
public:
	static string getFileExtension(const string &filePath);
	static string IntToString(int number);

public:
	CBaseConverter();
	virtual ~CBaseConverter();
};
#endif	//C_BASE_CONVERTER__H
