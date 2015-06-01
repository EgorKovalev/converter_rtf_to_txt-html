#include "stdafx.h"
#include "CRtfToTxtConverter.h"
#include "CRtfToHtmlConverter.h"

using namespace std;

CRtfToTxtConverter* createConverter(const string &inputFileExtension, const string &outputFileExtension);

int _tmain(int argc, _TCHAR* argv[])
{
	//check number of input parameters
	if (argc != 3)
	{
		cout << "Incorrect command format!\n" << endl;
		cout << "Command format must be: \n\"converter.exe \'InputFilePath\\InputFileName.rtf\' \'OutputFilePath\\OutputFileName.ext\'\",\n where ext = {txt, html}\n" << endl;
		return -1;
	}

	//get input parameters
	const string sInputFilePath = ConvertToString(argv[1]);
	const string sOutputFilePath = ConvertToString(argv[2]);

	cout << "Source file: "  << sInputFilePath.c_str() << "\n" << endl;
	cout << "Destination file: " << sOutputFilePath.c_str() << "\n" << endl;

	const string sInputFileExtension = CBaseConverter::getFileExtension(sInputFilePath);
	const string sOutputFileExtension = CBaseConverter::getFileExtension(sOutputFilePath);
	cout << "Source file extension: "  << sInputFileExtension.c_str() << "\n" << endl;
	cout << "Destination file extension: " << sOutputFileExtension.c_str() << "\n" << endl;

	CRtfToTxtConverter *pConverter = createConverter(sInputFileExtension, sOutputFileExtension);
	if (pConverter)
	{
		cout << "Conversion started, please wait\n" << endl;
		pConverter->SetInputFilePath(sInputFilePath);
		pConverter->SetOutputFilePath(sOutputFilePath);
		pConverter->Convert();
		if (pConverter->HasErrors())
		{
			cout << "Error:" << pConverter->GetLastError().c_str();
		}
		delete pConverter;
		pConverter = 0;
		cout << "Conversion finished\n" << endl;
	}
	else
	{
		cout << "Conversion impossible!\n" << endl;
	}

	cout << "Press any key to exit\n";
	_getch();
	return 0;
}

CRtfToTxtConverter* createConverter(const string &inputFileExtension, const string &outputFileExtension)
{
	if (!inputFileExtension.compare("rtf"))
	{
		if (!outputFileExtension.compare("txt"))
		{
			return new CRtfToTxtConverter();
		}
		else if (!outputFileExtension.compare("html"))
		{
			return new CRtfToHtmlConverter();
		}
		else
		{
			cout << "Unsupported output file format!\n" << endl;
		}
	}
	else
	{
		cout << "Unsupported input file format!\n" << endl;
	}

	return 0;
}