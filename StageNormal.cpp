#include "StageNormal.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"


CStageNormal::CStageNormal()
{
}


CStageNormal::~CStageNormal()
{
}

bool CStageNormal::Init()
{
	return true;
}

void CStageNormal::Run()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_NORMAL);

	while (true)
	{
		system("cls");
		OutputStageName("Normal");
		pPlayer->Render();
		cout << endl;
		pMonster->Render();
		cout << endl;

		switch (OutputMenu())
		{
		case MENU_ATTACK:
			switch (BattleAttack(pPlayer, pMonster))
			{
			case BF_PLAYER_DIE:
				pPlayer->DropExp();
				pPlayer->DropGold();

				pPlayer->FullHPMP();
				break;
			case BF_MONSTER_DIE:
				cout << pPlayer->GetName() << " ÀÌ" << pMonster->GetCharacterInfo().iExp
					<< " °æÇèÄ¡¸¦ È¹µæÇÏ¿´½À´Ï´Ù." << endl;
				int iDropGold;
				iDropGold = pMonster->GetDropGold();
				cout << pPlayer->GetName() << " ÀÌ" << iDropGold << " Gold¸¦ È¹µæÇÏ¿´½À´Ï´Ù." << endl;
				pPlayer->AddExp(pMonster->GetCharacterInfo().iExp);
				pPlayer->AddGold(iDropGold);

				if (pPlayer->CheckLevelUp())
				{
					pPlayer->LevelUp();

					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "Level Up" << endl;
				}

				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_NORMAL);
				break;
			default:
				break;
			}
			break;
		case MENU_BACK:
			SAFE_DELETE(pMonster);
			return;
		default:
			break;
		}

		system("pause");
	}
}
