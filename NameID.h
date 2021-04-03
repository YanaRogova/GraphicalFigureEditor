#pragma once
class CNameID
{
protected:
	CString m_strName;
	unsigned int m_nID;

public:
	CNameID(CString strName, unsigned int nID);
	CString GetName();
	void SetName(CString name);
	unsigned int GetID();
	void SetID(unsigned int id);
};

