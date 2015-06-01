#ifndef C_RTF_TO_TXT_CONVERTER__H
#define C_RTF_TO_TXT_CONVERTER__H

#include "CBaseConverter.h"
#include "Rtftype.h"

using namespace std;

class CRtfToTxtConverter : public CBaseConverter
{
protected:
	int m_cGroup;
	bool m_fSkipDestIfUnk;
	long m_cbBin;
	long m_lParam;

	RDS m_TextDestination;
	RIS m_ParserInternalState;

	CHP m_PropertiesCharacter;
	PAP m_ParagraphProperties;
	SEP m_SectionProperties;
	DOP m_DocumantProperties;

	SAVE *m_pStateSave;

	const static PROP m_rgPropertyDescription[ipropMax];
	const static SYM m_rgKeywordDescription[];

private:
	void ecChangeDest(IDEST idest);
	int ecPushRtfState();
	int ecParseRtfKeyword(ifstream &fIn);
	int ecTranslateKeyword(char *szKeyword, int param, char fParam);
	int ecParseSpecialKeyword(IPFN ipfn);
	int ecParseSpecialProperty(IPROP iprop, int val);

protected:
	virtual void ecParseChar(int ch);
	virtual int ecPopRtfState();
	virtual int ecApplyPropChange(IPROP iprop, int val);
	int RTFParser(ifstream &fIn);

public:
	virtual void Convert() override;

public:
	CRtfToTxtConverter();
	virtual ~CRtfToTxtConverter();
};

#endif	// C_RTF_TO_TXT_CONVERTER__H

