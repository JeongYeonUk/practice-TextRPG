#include "Player.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"

CPlayer::CPlayer()
{
	m_eType = OT_PLAYER;
	memset(m_pEquip, 0, sizeof(CItem*) * EQ_END);
}

CPlayer::CPlayer(const CPlayer & player) : CCharacter(player)
{
	m_eJob = player.m_eJob;
	m_strJobName = player.m_strJobName;
	m_iGold = player.m_iGold;
	memset(m_pEquip, 0, sizeof(CItem*) * EQ_END);
}


CPlayer::~CPlayer()
{
	for (int i = 0; i < EQ_END; ++i)
	{
		SAFE_DELETE(m_pEquip[i]);
	}
}

void CPlayer::AddGold(int iGold)
{
	m_iGold += iGold;
}

void CPlayer::DropGold()
{
	m_iGold *= 0.9f;
}

int CPlayer::GetDamage()
{
	int iMin = m_tInfo.iAttackMin;
	int iMax = m_tInfo.iAttackMax;

	if (m_pEquip[EQ_WEAPON])
	{
		iMin = ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMin();
		iMax = ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMax();

		if (rand() % 9901 / 100.f < ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetCritical())
		{
			cout << "Critical" << endl;
			iMin *= 2;
			iMax *= 2;
		}
	}

	return rand() % (iMax - iMin + 1) + iMin;
}

int CPlayer::GetArmor()
{
	int iMin = m_tInfo.iArmorMin;
	int iMax = m_tInfo.iArmorMax;

	if (m_pEquip[EQ_ARMOR])
	{
		iMin = ((CItemArmor*)m_pEquip[EQ_ARMOR])->GetArmorMin();
		iMax = ((CItemArmor*)m_pEquip[EQ_ARMOR])->GetArmorMax();
	}

	return rand() % (iMax - iMin + 1) + iMin;
}

CItem* CPlayer::Equip(CItem * pItem)
{
	EQUIP	eq = EQ_WEAPON;

	switch (pItem->GetItemInfo().eType)
	{
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	default:
		break;
	}

	if (m_pEquip[eq])
	{
		CItem* pEquip = m_pEquip[eq];
		m_pEquip[eq] = pItem;

		return pEquip;
	}

	m_pEquip[eq] = pItem;

	return nullptr;
}

bool CPlayer::Init()
{
	system("cls");
	cin.ignore(1024, '\n');
	cout << "이름을 입력하세요 : ";
	char	strName[32] = {};
	cin.getline(strName, 31);

	SetName(strName);

	int iJob;

	while (true)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		iJob = Input<int>();

		if (iJob < JOB_KNIGHT || iJob >= JOB_END)
			continue;

		break;
	}

	m_eJob = (JOB)iJob;

	switch (m_eJob)
	{
	case JOB_KNIGHT:
		m_strJobName = "기사";
		SetCharacterInfo(10, 15, 15, 20, 500, 100, 1, 0);
		break;
	case JOB_ARCHER:
		m_strJobName = "궁수";
		SetCharacterInfo(15, 20, 10, 15, 400, 200, 1, 0);
		break;
	case JOB_MAGICIAN:
		m_strJobName = "마법사";
		SetCharacterInfo(20, 25, 5, 10, 300, 300, 1, 0);
		break;
	default:
		break;
	}

	m_iGold = 10000;

	return true;
}

void CPlayer::Render()
{
	cout << "이름 : " << m_strName << "\t직업 : " << m_strJobName << endl;
	cout << "레벨 : " << m_tInfo.iLevel << "\t경험치 : " << m_tInfo.iExp << endl;
	cout << "공격력 : ";
	
	if (m_pEquip[EQ_WEAPON])
	{
		cout << m_tInfo.iAttackMin << " + " <<
			((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMin() << " ~ " <<
			m_tInfo.iAttackMax << " + " <<
			((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMax();
	}
	else
	{
		cout << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax;
	}
	 
	cout << "\t방어력 : ";
	
	if (m_pEquip[EQ_ARMOR])
	{
		cout << m_tInfo.iArmorMin << " + " <<
			((CItemArmor*)m_pEquip[EQ_ARMOR])->GetArmorMin() << " ~ " <<
			m_tInfo.iArmorMax << " + " <<
			((CItemArmor*)m_pEquip[EQ_ARMOR])->GetArmorMax() << endl;
	}
	else
	{
		cout << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	}	
	
	cout << "체력 : " << m_tInfo.iHP << " / " << m_tInfo.iHPMax << "\t마나 : " <<
		m_tInfo.iMP << " / " << m_tInfo.iMPMax << endl;
	cout << "보유금액 : " << m_iGold << " Gold" << endl;

	cout << "장착무기 : ";
	if (m_pEquip[EQ_WEAPON])
		cout << m_pEquip[EQ_WEAPON]->GetName();
	else
		cout << "없음";

	cout << "\t장착방어구 : ";
	if (m_pEquip[EQ_ARMOR])
		cout << m_pEquip[EQ_ARMOR]->GetName() << endl;
	else
		cout << "없음" << endl;
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}
