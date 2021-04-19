#pragma once
class CNameID
{
protected:
	CString m_strName;
	unsigned int m_nID;

public:
	CNameID(CString strName, unsigned int nID);
	virtual ~CNameID();

	CString GetName();
	unsigned int GetID();

	void SetName(CString name);
	void SetID(unsigned int id);
};

