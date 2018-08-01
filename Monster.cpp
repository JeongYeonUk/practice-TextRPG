#include "Monster.h"
#include "FileStream.h"


CMonster::CMonster()
{
	m_eType = OT_MONSTER;
}

CMonster::CMonster(const CMonster & monster) : CCharacter(monster)
{
	m_iGoldMin = monster.m_iGoldMin;
	m_iGoldMax = monster.m_iGoldMax;
	m_eStageType = monster.m_eStageType;
}


CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	return true;
}

void CMonster::Render()
{
	cout << "이름 : " << m_strName;
	switch (m_eStageType)
	{
	case ST_EASY:
		cout << "\t난이도 : Easy" << endl;
		break;
	case ST_NORMAL:
		cout << "\t난이도 : Normal" << endl;
		break;
	case ST_HARD:
		cout << "\t난이도 : Hard" << endl;
		break;
	default:
		break;
	}
	cout << "레벨 : " << m_tInfo.iLevel << "\t획득경험치 : " << m_tInfo.iExp << endl;
	cout << "공격력 : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax <<
		"\t방어력 : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "체력 : " << m_tInfo.iHP << " / " << m_tInfo.iHPMax << "\t마나 : " <<
		m_tInfo.iMP << " / " << m_tInfo.iMPMax << endl;
	cout << "획득금액 : " << m_iGoldMin << " ~ " << m_iGoldMax << " Gold" << endl;
}

CMonster * CMonster::Clone()
{
	return new CMonster(*this);
}

void CMonster::Save(CFileStream * pFile)
{
	CCharacter::Save(pFile);

	pFile->Write(&m_iGoldMin, 4);
	pFile->Write(&m_iGoldMax, 4);
	pFile->Write(&m_eStageType, 4);
}

void CMonster::Load(CFileStream * pFile)
{
	CCharacter::Load(pFile);

	pFile->Read(&m_iGoldMin, 4);
	pFile->Read(&m_iGoldMax, 4);
	pFile->Read(&m_eStageType, 4);
}
