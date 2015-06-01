#include "stdafx.h"
#include "CRtfToHtmlConverter.h"


CRtfToHtmlConverter::CRtfToHtmlConverter()
{
}


CRtfToHtmlConverter::~CRtfToHtmlConverter()
{
}

int CRtfToHtmlConverter::ecApplyPropChange(IPROP iprop, int val)
{
	CRtfToTxtConverter::ecApplyPropChange(iprop, val);

	if (m_rgPropertyDescription[iprop].prop == propChp)
	{
		if (iprop == ipropBold)
		{
			char* str = "<b>";
			puts(str);
		}
		if (iprop == ipropItalic)
		{
			char* str = "<i>";
			puts(str);
		}
		if (iprop == ipropUnderline)
		{
			char* str = "<u>";
			puts(str);
		}
	}
	return ecOK;
}

int CRtfToHtmlConverter::ecPopRtfState()
{
	if (m_PropertiesCharacter.fBold == 1)
	{
		char* str = "</b>";
		puts(str);
	}
	if (m_PropertiesCharacter.fItalic == 1)
	{
		char* str = "</i>";
		puts(str);
	}
	if (m_PropertiesCharacter.fUnderline == 1)
	{
		char* str = "</u>";
		puts(str);
	}

	CRtfToTxtConverter::ecPopRtfState();
	return ecOK;
}

void CRtfToHtmlConverter::ecParseChar(int ch)
{
	CRtfToTxtConverter::ecParseChar(ch);

	if ((IDEST)ch == 0x0a/*"par"*/)
	{
		char* str = "<p>";
		puts(str);
	}
}
