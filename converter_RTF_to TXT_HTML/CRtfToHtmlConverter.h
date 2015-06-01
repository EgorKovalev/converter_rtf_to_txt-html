#ifndef C_RTF_TO_HTML_CONVERTER__H
#define C_RTF_TO_HTML_CONVERTER__H

#include "CRtfToTxtConverter.h"

class CRtfToHtmlConverter : public CRtfToTxtConverter
{
protected:
	virtual int ecApplyPropChange(IPROP iprop, int val) override;
	virtual int ecPopRtfState() override;
	virtual void ecParseChar(int idest) override;

public:
	CRtfToHtmlConverter();
	virtual ~CRtfToHtmlConverter();
};
#endif	//C_RTF_TO_HTML_CONVERTER__H
