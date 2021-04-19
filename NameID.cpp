#include "pch.h"
#include "NameID.h"

CNameID::CNameID(CString strName, unsigned int nID)
{
	m_strName = strName;
	m_nID = nID;
}

CNameID::~CNameID()
{
}

CString CNameID::GetName()
{
	return m_strName;
}

unsigned int CNameID::GetID()
{
	return m_nID;
}

void CNameID::SetName(CString name)
{
	m_strName = name;
}

void CNameID::SetID(unsigned int id)
{
	m_nID = id;
}