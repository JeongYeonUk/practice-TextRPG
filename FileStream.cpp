#include "FileStream.h"

CFileStream::CFileStream() : 
	m_pFile(nullptr), 
	m_bOpen(false), 
	m_iFileSize(0), 
	m_iCurrent(0)
{
}

CFileStream::CFileStream(const char * pFileName, const char * pMode) :
	m_pFile(nullptr),
	m_bOpen(false),
	m_iFileSize(0),
	m_iCurrent(0)
{
	Open(pFileName, pMode);
}

CFileStream::~CFileStream()
{
	Close();
}

bool CFileStream::Open(const char* pFileName, const char* pMode)
{
	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile)
		return false;

	m_bOpen = true;

	if (pMode[0] == 'r' || pMode[0] == 'R')
		m_eMode = FM_READ;
	else if (pMode[0] == 'w' || pMode[0] == 'W')
		m_eMode = FM_WRITE;

	fseek(m_pFile, 0, SEEK_END);
	m_iFileSize = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen)
		return false;

	fclose(m_pFile);
	m_pFile = nullptr;
	m_bOpen = false;
	m_iFileSize = 0;

	return true;
}

bool CFileStream::Read(void * pData, int iSize)
{
	if (!m_bOpen || m_eMode != FM_READ)
		return false;

	fread(pData, iSize, 1, m_pFile);

	m_iCurrent += iSize;

	return true;
}

bool CFileStream::ReadLine(void * pData, int * pSize)
{
	if (!m_bOpen || m_eMode != FM_READ)
		return false;

	char	cBuffer = 0;

	vector<char> vec;
	vec.reserve(128);

	while (feof(m_pFile) == 0)
	{
		fread(&cBuffer, 1, 1, m_pFile);

		if (cBuffer == '\n')
			break;

		vec.push_back(cBuffer);
	}

	*pSize = vec.size();

	memcpy(pData, &vec[0], vec.size());

	m_iCurrent += vec.size();

	return true;
}

bool CFileStream::Write(void * pData, int iSize)
{
	if (!m_bOpen || m_eMode != FM_WRITE)
		return false;
	
	fwrite(pData, iSize, 1, m_pFile);

	return true;
}
