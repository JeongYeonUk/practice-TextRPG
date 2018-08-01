#include "StageHard.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"


CStageHard::CStageHard()
{
}


CStageHard::~CStageHard()
{
}

bool CStageHard::Init()
{
	return true;
}

void CStageHard::Run()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_HARD);

	while (true)
	{
		system("cls");
		OutputStageName("Hard");
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
				cout << pPlayer->GetName() << " ��" << pMonster->GetCharacterInfo().iExp
					<< " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
				int iDropGold;
				iDropGold = pMonster->GetDropGold();
				cout << pPlayer->GetName() << " ��" << iDropGold << " Gold�� ȹ���Ͽ����ϴ�." << endl;
				pPlayer->AddExp(pMonster->GetCharacterInfo().iExp);
				pPlayer->AddGold(iDropGold);

				if (pPlayer->CheckLevelUp())
				{
					pPlayer->LevelUp();

					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "Level Up" << endl;
				}

				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_HARD);
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
