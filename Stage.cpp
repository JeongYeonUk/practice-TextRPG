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
	cout << "1. 공격" << endl;
	cout << "2. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = Input<int>();

	if (iMenu <= MENU_NONE || iMenu > MENU_BACK)
		return MENU_NONE;

	return iMenu;
}

CStage::BATTLE_FLAG CStage::BattleAttack(CPlayer * pPlayer, CMonster * pMonster)
{
	int iDamage = pPlayer->GetDamage() - pMonster->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << pPlayer->GetName() << "가 " << pMonster->GetName() << "에게 " <<
		iDamage << "피해를 주었습니다." << endl;

	if (pMonster->Damage(iDamage))
	{
		return BF_MONSTER_DIE;
	}

	iDamage = pMonster->GetDamage() - pPlayer->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << pMonster->GetName() << "가 " << pPlayer->GetName() << "에게 " <<
		iDamage << "피해를 주었습니다." << endl;

	if (pPlayer->Damage(iDamage))
		return BF_PLAYER_DIE;

	return BF_NONE;
}

void CStage::OutputStageName(const string& strName)
{
	cout << "===================" << strName << "===================" << endl;
}
