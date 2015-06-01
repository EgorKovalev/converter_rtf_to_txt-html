#include "stdafx.h"
#include "CRtfToTxtConverter.h"

const PROP CRtfToTxtConverter::m_rgPropertyDescription[ipropMax] = {
	actnByte, propChp, offsetof(CHP, fBold),       // ipropBold
	actnByte, propChp, offsetof(CHP, fItalic),     // ipropItalic
	actnByte, propChp, offsetof(CHP, fUnderline),  // ipropUnderline
	actnWord, propPap, offsetof(PAP, xaLeft),      // ipropLeftInd
	actnWord, propPap, offsetof(PAP, xaRight),     // ipropRightInd
	actnWord, propPap, offsetof(PAP, xaFirst),     // ipropFirstInd
	actnWord, propSep, offsetof(SEP, cCols),       // ipropCols
	actnWord, propSep, offsetof(SEP, xaPgn),       // ipropPgnX
	actnWord, propSep, offsetof(SEP, yaPgn),       // ipropPgnY
	actnWord, propDop, offsetof(DOP, xaPage),      // ipropXaPage
	actnWord, propDop, offsetof(DOP, yaPage),      // ipropYaPage
	actnWord, propDop, offsetof(DOP, xaLeft),      // ipropXaLeft
	actnWord, propDop, offsetof(DOP, xaRight),     // ipropXaRight
	actnWord, propDop, offsetof(DOP, yaTop),       // ipropYaTop
	actnWord, propDop, offsetof(DOP, yaBottom),    // ipropYaBottom
	actnWord, propDop, offsetof(DOP, pgnStart),    // ipropPgnStart
	actnByte, propSep, offsetof(SEP, sbk),         // ipropSbk
	actnByte, propSep, offsetof(SEP, pgnFormat),   // ipropPgnFormat
	actnByte, propDop, offsetof(DOP, fFacingp),    // ipropFacingp
	actnByte, propDop, offsetof(DOP, fLandscape),  // ipropLandscape
	actnByte, propPap, offsetof(PAP, just),        // ipropJust
	actnSpec, propPap, 0,                          // ipropPard
	actnSpec, propChp, 0,                          // ipropPlain
	actnSpec, propSep, 0,                          // ipropSectd
};

const SYM CRtfToTxtConverter::m_rgKeywordDescription[] = {
	//  keyword     dflt    fPassDflt   kwd         idx
	"b", 1, fFalse, kwdProp, ipropBold,
	"ul", 1, fFalse, kwdProp, ipropUnderline,
	"i", 1, fFalse, kwdProp, ipropItalic,
	"li", 0, fFalse, kwdProp, ipropLeftInd,
	"ri", 0, fFalse, kwdProp, ipropRightInd,
	"fi", 0, fFalse, kwdProp, ipropFirstInd,
	"cols", 1, fFalse, kwdProp, ipropCols,
	"sbknone", sbkNon, fTrue, kwdProp, ipropSbk,
	"sbkcol", sbkCol, fTrue, kwdProp, ipropSbk,
	"sbkeven", sbkEvn, fTrue, kwdProp, ipropSbk,
	"sbkodd", sbkOdd, fTrue, kwdProp, ipropSbk,
	"sbkpage", sbkPg, fTrue, kwdProp, ipropSbk,
	"pgnx", 0, fFalse, kwdProp, ipropPgnX,
	"pgny", 0, fFalse, kwdProp, ipropPgnY,
	"pgndec", pgDec, fTrue, kwdProp, ipropPgnFormat,
	"pgnucrm", pgURom, fTrue, kwdProp, ipropPgnFormat,
	"pgnlcrm", pgLRom, fTrue, kwdProp, ipropPgnFormat,
	"pgnucltr", pgULtr, fTrue, kwdProp, ipropPgnFormat,
	"pgnlcltr", pgLLtr, fTrue, kwdProp, ipropPgnFormat,
	"qc", justC, fTrue, kwdProp, ipropJust,
	"ql", justL, fTrue, kwdProp, ipropJust,
	"qr", justR, fTrue, kwdProp, ipropJust,
	"qj", justF, fTrue, kwdProp, ipropJust,
	"paperw", 12240, fFalse, kwdProp, ipropXaPage,
	"paperh", 15480, fFalse, kwdProp, ipropYaPage,
	"margl", 1800, fFalse, kwdProp, ipropXaLeft,
	"margr", 1800, fFalse, kwdProp, ipropXaRight,
	"margt", 1440, fFalse, kwdProp, ipropYaTop,
	"margb", 1440, fFalse, kwdProp, ipropYaBottom,
	"pgnstart", 1, fTrue, kwdProp, ipropPgnStart,
	"facingp", 1, fTrue, kwdProp, ipropFacingp,
	"landscape", 1, fTrue, kwdProp, ipropLandscape,
	"par", 0, fFalse, kwdChar, 0x0a,
	"\0x0a", 0, fFalse, kwdChar, 0x0a,
	"\0x0d", 0, fFalse, kwdChar, 0x0a,
	"tab", 0, fFalse, kwdChar, 0x09,
	"ldblquote", 0, fFalse, kwdChar, '"',
	"rdblquote", 0, fFalse, kwdChar, '"',
	"bin", 0, fFalse, kwdSpec, ipfnBin,
	"*", 0, fFalse, kwdSpec, ipfnSkipDest,
	"'", 0, fFalse, kwdSpec, ipfnHex,
	"author", 0, fFalse, kwdDest, idestSkip,
	"buptim", 0, fFalse, kwdDest, idestSkip,
	"colortbl", 0, fFalse, kwdDest, idestSkip,
	"comment", 0, fFalse, kwdDest, idestSkip,
	"creatim", 0, fFalse, kwdDest, idestSkip,
	"doccomm", 0, fFalse, kwdDest, idestSkip,
	"fonttbl", 0, fFalse, kwdDest, idestSkip,
	"footer", 0, fFalse, kwdDest, idestSkip,
	"footerf", 0, fFalse, kwdDest, idestSkip,
	"footerl", 0, fFalse, kwdDest, idestSkip,
	"footerr", 0, fFalse, kwdDest, idestSkip,
	"footnote", 0, fFalse, kwdDest, idestSkip,
	"ftncn", 0, fFalse, kwdDest, idestSkip,
	"ftnsep", 0, fFalse, kwdDest, idestSkip,
	"ftnsepc", 0, fFalse, kwdDest, idestSkip,
	"header", 0, fFalse, kwdDest, idestSkip,
	"headerf", 0, fFalse, kwdDest, idestSkip,
	"headerl", 0, fFalse, kwdDest, idestSkip,
	"headerr", 0, fFalse, kwdDest, idestSkip,
	"info", 0, fFalse, kwdDest, idestSkip,
	"keywords", 0, fFalse, kwdDest, idestSkip,
	"operator", 0, fFalse, kwdDest, idestSkip,
	"pict", 0, fFalse, kwdDest, idestSkip,
	"printim", 0, fFalse, kwdDest, idestSkip,
	"private1", 0, fFalse, kwdDest, idestSkip,
	"revtim", 0, fFalse, kwdDest, idestSkip,
	"rxe", 0, fFalse, kwdDest, idestSkip,
	"stylesheet", 0, fFalse, kwdDest, idestSkip,
	"subject", 0, fFalse, kwdDest, idestSkip,
	"tc", 0, fFalse, kwdDest, idestSkip,
	"title", 0, fFalse, kwdDest, idestSkip,
	"txe", 0, fFalse, kwdDest, idestSkip,
	"xe", 0, fFalse, kwdDest, idestSkip,
	"{", 0, fFalse, kwdChar, '{',
	"}", 0, fFalse, kwdChar, '}',
	"\\", 0, fFalse, kwdChar, '\\'
};

CRtfToTxtConverter::CRtfToTxtConverter()
{
	m_cGroup = 0;
}

CRtfToTxtConverter::~CRtfToTxtConverter()
{
}

int CRtfToTxtConverter::RTFParser(ifstream &fIn)
{
	int prevCh, ec, cNibble = 2, b = 0;
	char ch;

	while (fIn.get(ch)) //get one by one character from input stream
	{
		if (m_cGroup < 0)
			return ecStackUnderflow;
		if (m_ParserInternalState == risBin)                      // if we're parsing binary data, handle it directly
		{
			ecParseChar(ch);
		}
		else
		{
			switch (ch)
			{
			case '{':
				if ((ec = ecPushRtfState()) != ecOK)
					return ec;
				break;
			case '}':
				if ((ec = ecPopRtfState()) != ecOK)
					return ec;
				break;
			case '\\':
				if ((ec = ecParseRtfKeyword(fIn)) != ecOK)
					return ec;
				break;
			case 0x0d:
			case 0x0a:          // cr and lf are noise characters...
				break;

			default:
				if (m_ParserInternalState == risNorm)
				{
					ecParseChar(ch);
				}
				else
				{               // parsing hex data
					if (m_ParserInternalState != risHex)
						return ecAssertion;
					b = b << 4;
					if (isdigit(ch))
						b += (char)ch - '0';
					else
					{
						if (islower(ch))
						{
							if (ch < 'a' || ch > 'f')
								return ecInvalidHex;
							b += (char)ch - 'a';
						}
						else
						{
							if (ch < 'A' || ch > 'F')
								return ecInvalidHex;
							b += (char)ch - 'A';
						}
					}
					cNibble--;
					if (!cNibble)
					{
						ecParseChar(b);
						cNibble = 2;
						b = 0;
						m_ParserInternalState = risNorm;
					}
				}                   // end else (ris != risNorm)
				break;
			}       // switch
		}           // else (ris != risBin)
		prevCh = ch;
	} // while
	
	if (m_cGroup < 0)
		return ecStackUnderflow;
	if (m_cGroup > 0)
		return ecUnmatchedBrace;
	
	return ecOK;
}

int CRtfToTxtConverter::ecPushRtfState()
{
	SAVE *pSaveNew = new SAVE[sizeof(SAVE)];
	
	if (!pSaveNew)
		return ecStackOverflow;

	pSaveNew->pNext = m_pStateSave;
	pSaveNew->chp = m_PropertiesCharacter;
	pSaveNew->pap = m_ParagraphProperties;
	pSaveNew->sep = m_SectionProperties;
	pSaveNew->dop = m_DocumantProperties;
	pSaveNew->rds = m_TextDestination;
	pSaveNew->ris = m_ParserInternalState;
	
	m_ParserInternalState = risNorm;
	m_pStateSave = pSaveNew;
	++m_cGroup;

	return ecOK;

	//memory will be freed in ecPopRtfState()
}

int CRtfToTxtConverter::ecPopRtfState()
{
	SAVE *pSaveOld;

	if (!m_pStateSave)
		return ecStackUnderflow;

	m_PropertiesCharacter = m_pStateSave->chp;
	m_ParagraphProperties = m_pStateSave->pap;
	m_SectionProperties = m_pStateSave->sep;
	m_DocumantProperties = m_pStateSave->dop;
	m_TextDestination = m_pStateSave->rds;
	m_ParserInternalState = m_pStateSave->ris;

	pSaveOld = m_pStateSave;
	m_pStateSave = m_pStateSave->pNext;
	--m_cGroup;
	
	delete pSaveOld;

	return ecOK;
}

void CRtfToTxtConverter::ecParseChar(int ch)
{
	if (m_ParserInternalState == risBin && --m_cbBin <= 0)
		m_ParserInternalState = risNorm;
	
	if (m_TextDestination == rdsNorm)
		putchar(ch);
}

int CRtfToTxtConverter::ecParseRtfKeyword(ifstream &fIn)
{
	char ch;
	char fParam = fFalse;
	char fNeg = fFalse;
	int param = 0;
	char *pch;
	char szKeyword[30];
	char szParameter[20];

	szKeyword[0] = '\0';
	szParameter[0] = '\0';
	
	if (!fIn.good())
		return ecEndOfFile;
	else
		fIn.get(ch);

	if (!isalpha(ch))           // a control symbol; no delimiter.
	{
		szKeyword[0] = (char)ch;
		szKeyword[1] = '\0';
		
		return ecTranslateKeyword(szKeyword, 0, fParam);
	}
	
	for (pch = szKeyword; isalpha(ch); fIn.get(ch))
		*pch++ = (char)ch;
	
	*pch = '\0';
	
	if (ch == '-')
	{
		fNeg = fTrue;
		if (fIn.good())
			return ecEndOfFile;
	}
	
	if (isdigit(ch))
	{
		fParam = fTrue;         // a digit after the control means we have a parameter
		
		for (pch = szParameter; isdigit(ch); fIn.get(ch))
			*pch++ = (char)ch;
		
		*pch = '\0';
		param = atoi(szParameter);
		
		if (fNeg)
			param = -param;
		
		m_lParam = atol(szParameter);
		
		if (fNeg)
			param = -param;
	}
	
	if (ch != ' ')
		fIn.putback(ch);
	
	return ecTranslateKeyword(szKeyword, param, fParam);
}

int CRtfToTxtConverter::ecTranslateKeyword(char *szKeyword, int param, char fParam)
{
	int isym;
	int isymMax = sizeof(m_rgKeywordDescription) / sizeof(SYM);

	// search for szKeyword in rgsymRtf
	for (isym = 0; isym < isymMax; isym++)
	if (strcmp(szKeyword, m_rgKeywordDescription[isym].szKeyword) == 0)
		break;
	
	if (isym == isymMax)            // control word not found
	{
		if (m_fSkipDestIfUnk)         // if this is a new destination
			m_TextDestination = rdsSkip;          // skip the destination
		// else just discard it
		m_fSkipDestIfUnk = fFalse;
		return ecOK;
	}

	// found it!  use kwd and idx to determine what to do with it.
	m_fSkipDestIfUnk = fFalse;
	
	switch (m_rgKeywordDescription[isym].kwd)
	{
	case kwdProp:
		if (m_rgKeywordDescription[isym].fPassDflt || !fParam)
			param = m_rgKeywordDescription[isym].dflt;
		return ecApplyPropChange((IPROP)m_rgKeywordDescription[isym].idx, param);
	
	case kwdChar:
	{
		ecParseChar(m_rgKeywordDescription[isym].idx);
		return ecOK;
	}		
	
	case kwdDest:
	{
		ecChangeDest((IDEST)m_rgKeywordDescription[isym].idx);
		return ecOK;
	}		
	
	case kwdSpec:
		return ecParseSpecialKeyword((IPFN)m_rgKeywordDescription[isym].idx);
	
	default:
		return ecBadTable;
	}
	return ecBadTable;
}

int CRtfToTxtConverter::ecApplyPropChange(IPROP iprop, int val)
{
	char *pb = 0;
	if (m_TextDestination == rdsSkip)                 // If we're skipping text,
		return ecOK;                    // Do not do anything.

	switch (m_rgPropertyDescription[iprop].prop)
	{
	case propDop:
		pb = (char *)&m_DocumantProperties;
		break;
	case propSep:
		pb = (char *)&m_SectionProperties;
		break;
	case propPap:
		pb = (char *)&m_ParagraphProperties;
		break;
	case propChp:
		pb = (char *)&m_PropertiesCharacter;
		break;
	default:
		if (m_rgPropertyDescription[iprop].actn != actnSpec)
			return ecBadTable;
		break;
	}
	switch (m_rgPropertyDescription[iprop].actn)
	{
	case actnByte:
		pb[m_rgPropertyDescription[iprop].offset] = (unsigned char)val;
		break;
	case actnWord:
		(*(int *)(pb + m_rgPropertyDescription[iprop].offset)) = val;
		break;
	case actnSpec:
		return ecParseSpecialProperty(iprop, val);
		break;
	default:
		return ecBadTable;
	}
	return ecOK;
}

void CRtfToTxtConverter::ecChangeDest(IDEST idest)
{
	if (m_TextDestination != rdsSkip)           
		m_TextDestination = rdsSkip;					
}

int CRtfToTxtConverter::ecParseSpecialKeyword(IPFN ipfn)
{
	if (m_TextDestination == rdsSkip && ipfn != ipfnBin)  // if we're skipping, and it is not
		return ecOK;                        // the \bin keyword, ignore it.
	
	switch (ipfn)
	{
	case ipfnBin:
		m_ParserInternalState = risBin;
		m_cbBin = m_lParam;
		break;
	case ipfnSkipDest:
		m_fSkipDestIfUnk = fTrue;
		break;
	case ipfnHex:
		m_ParserInternalState = risHex;
		break;
	default:
		return ecBadTable;
	}
	return ecOK;
}

int CRtfToTxtConverter::ecParseSpecialProperty(IPROP iprop, int val)
{
	switch (iprop)
	{
	case ipropPard:
		memset(&m_ParagraphProperties, 0, sizeof(m_ParagraphProperties));
		return ecOK;
	case ipropPlain:
		memset(&m_PropertiesCharacter, 0, sizeof(m_PropertiesCharacter));
		return ecOK;
	case ipropSectd:
		memset(&m_SectionProperties, 0, sizeof(m_SectionProperties));
		return ecOK;
	default:
		return ecBadTable;
	}
	return ecBadTable;
}

void CRtfToTxtConverter::Convert()
{
	if (HasErrors())
	{
		return;
	}

	setlocale(LC_ALL, "rus");
	ifstream inputFileData(m_sInputFilePath.c_str(), ios_base::binary);
	
	if (!inputFileData.is_open())
	{
		m_sLastError = "Can't open input file:";
		m_sLastError +=	m_sInputFilePath;
		m_sLastError += "\n";
		return;
	}
	else
	{
		FILE * pFile = 0;
		freopen_s( &pFile, m_sOutputFilePath.c_str(), "w", stdout );
		const int errorCode = RTFParser(inputFileData);

		fclose(stdout); //need to redirect stdout to console after getting info from the RTF file
		freopen_s(&pFile, "CON", "w", stdout);

		if (errorCode != ecOK)
		{
			m_sLastError = "Error code: ";
			m_sLastError +=	CBaseConverter::IntToString(errorCode);
			m_sLastError += "\n";
		}

		inputFileData.close();
	}
}
