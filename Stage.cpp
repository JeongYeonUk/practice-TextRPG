#include "Stage.h"
#include "Player.h"
#include "Monster.h"


CStage::CStage()
{
}


CStage::~CStage()
{
}

int CStage::OutputMenu()
{
	cout << "1. ����" << endl;
	cout << "2. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iMenu = Input<int>();

	if (iMenu <= MENU_NONE || iMenu > MENU_BACK)
		return MENU_NONE;

	return iMenu;
}

CStage::BATTLE_FLAG CStage::BattleAttack(CPlayer * pPlayer, CMonster * pMonster)
{
	int iDamage = pPlayer->GetDamage() - pMonster->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << pPlayer->GetName() << "�� " << pMonster->GetName() << "���� " <<
		iDamage << "���ظ� �־����ϴ�." << endl;

	if (pMonster->Damage(iDamage))
	{
		return BF_MONSTER_DIE;
	}

	iDamage = pMonster->GetDamage() - pPlayer->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << pMonster->GetName() << "�� " << pPlayer->GetName() << "���� " <<
		iDamage << "���ظ� �־����ϴ�." << endl;

	if (pPlayer->Damage(iDamage))
		return BF_PLAYER_DIE;

	return BF_NONE;
}

void CStage::OutputStageName(const string& strName)
{
	cout << "===================" << strName << "===================" << endl;
}
