#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "FileStream.h"

DEFINITION_SINGLE(CObjectManager);

CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	// 플레이어 생성
	CObj* pPlayer = CreateObject("Player", OT_PLAYER);

	CFileStream file("MonsterList.mtl", "rb");

	if (file.GetOpen())
	{
		int iMonsterCount = 0;

		file.Read(&iMonsterCount, 4);

		for (int i = 0; i < iMonsterCount; ++i)
		{
			CMonster* pMonster = new CMonster;

			pMonster->Load(&file);

			m_mapObj.insert(make_pair(pMonster->GetName(), pMonster));
		}
	}
	else
	{
		CMonster* pMonster = (CMonster*)CreateObject("Goblin", OT_MONSTER);

		pMonster->SetName("고블린");
		pMonster->SetCharacterInfo(10, 20, 3, 5, 100, 10, 1, 1000);
		pMonster->SetGold(1000, 2000);
		pMonster->SetStageType(ST_EASY);

		pMonster = (CMonster*)CreateObject("Troll", OT_MONSTER);

		pMonster->SetName("트롤");
		pMonster->SetCharacterInfo(50, 80, 40, 60, 2000, 300, 5, 7000);
		pMonster->SetGold(5000, 10000);
		pMonster->SetStageType(ST_NORMAL);

		pMonster = (CMonster*)CreateObject("Dragon", OT_MONSTER);

		pMonster->SetName("드래곤");
		pMonster->SetCharacterInfo(150, 250, 150, 250, 10000, 10000, 10, 25000);
		pMonster->SetGold(30000, 50000);
		pMonster->SetStageType(ST_HARD);
	}
	return true;
}

CObj * CObjectManager::CreateObject(const string& strKey, OBJECT_TYPE eType)
{
	CObj*	pObj = nullptr;

	switch (eType)
	{
	case OT_PLAYER:
		pObj = new CPlayer;
		break;
	case OT_MONSTER:
		pObj = new CMonster;
	default:
		break;
	}

	if (!pObj->Init())
	{
		SAFE_DELETE(pObj);
		return nullptr;
	}

	m_mapObj.insert(make_pair(strKey, pObj));

	return pObj;
}

CObj * CObjectManager::FindObject(const string & strKey)
{
	unordered_map<string, CObj*>::iterator iter = m_mapObj.find(strKey);

	if (iter == m_mapObj.end())
		return NULL;

	return iter->second;
}

// 객체를 찾은 후 해당 객체를 복사해서 생성한 후 반환
CObj * CObjectManager::CloneObject(const string & strKey)
{
	CObj* pOrigin = FindObject(strKey);

	if (!pOrigin)
		return NULL;

	return pOrigin->Clone();
}

CObj * CObjectManager::CloneObject(STAGE_TYPE eType)
{
	vector<CMonster*> vecMonster;

	unordered_map<string, CObj*>::iterator iter;

	for (iter = m_mapObj.begin(); iter != m_mapObj.end(); ++iter)
	{
		if (iter->second->GetObjectType() == OT_MONSTER)
		{
			CMonster* pMonster = (CMonster*)iter->second;

			if (pMonster->GetStageType() == eType)
				vecMonster.push_back(pMonster);
		}
	}

	if (vecMonster.empty())
		return nullptr;

	int idx = rand() % vecMonster.size();

	return vecMonster[idx]->Clone();
}


