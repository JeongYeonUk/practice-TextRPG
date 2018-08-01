#include "Obj.h"
#include "FileStream.h"

CObj::CObj()
{
}

CObj::CObj(const CObj & obj)
{
	m_strName = obj.m_strName;
	m_eType = obj.m_eType;
}

CObj::~CObj()
{
}

OBJECT_TYPE CObj::GetObjectType() const
{
	return m_eType;
}

bool CObj::Init()
{
	return true;
}

void CObj::Render()
{
}

void CObj::Save(CFileStream * pFile)
{
	pFile->Write(&m_eType, 4);

	int iLength = m_strName.length();

	pFile->Write(&iLength, 4);

	pFile->Write((void*)m_strName.c_str(), iLength);
}

void CObj::Load(CFileStream * pFile)
{
	pFile->Read(&m_eType, 4);

	int iLength = 0;
	pFile->Read(&iLength, 4);

	char* pName = new char[iLength + 1];
	memset(pName, 0, iLength);

	pFile->Read(pName, iLength);
	pName[iLength] = 0;

	m_strName = pName;

	SAFE_DELETE_ARRAY(pName);
}
