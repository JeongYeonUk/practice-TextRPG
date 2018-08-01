#pragma once

#include "Character.h"

class CMonster :
	public CCharacter
{
private:
	CMonster();
	CMonster(const CMonster& monster);

public:
	~CMonster();

private:
	friend class CObjectManager;
	friend class CEditorMonster;

private:
	int				m_iGoldMin;
	int				m_iGoldMax;
	STAGE_TYPE		m_eStageType;

public:
	void SetGold(int iMin, int iMax)
	{
		m_iGoldMin = iMin;
		m_iGoldMax = iMax;
	}

	void SetStageType(STAGE_TYPE eType)
	{
		m_eStageType = eType;
	}

	int GetDropGold() const
	{
		return rand() % (m_iGoldMax - m_iGoldMin + 1) + m_iGoldMin;
	}

	STAGE_TYPE GetStageType() const
	{
		return m_eStageType;
	}

public:
	virtual bool Init();
	virtual void Render();
	virtual CMonster* Clone();
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

