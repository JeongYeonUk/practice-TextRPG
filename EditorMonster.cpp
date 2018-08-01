#include "EditorMonster.h"
#include "Monster.h"
#include "FileStream.h"

DEFINITION_SINGLE(CEditorMonster)

enum EDIT_MONSTER_MENU
{
	EMM_NONE,
	EMM_INSERT,
	EMM_DELETE,
	EMM_OUTPUT,
	EMM_SAVE,
	EMM_LOAD,
	EMM_BACK
};

CEditorMonster::CEditorMonster()
{
}


CEditorMonster::~CEditorMonster()
{
	Safe_Delete_VecOrList(m_vecMonster);
}

bool CEditorMonster::Init()
{
	return true;
}

void CEditorMonster::Run()
{
	while (true)
	{
		switch (OutputMenu())
		{
		case EMM_INSERT:
			Insert();
			break;
		case EMM_DELETE:
			Delete();
			break;
		case EMM_OUTPUT:
			OutputMonsterList();
			break;
		case EMM_SAVE:
			Save();
			break;
		case EMM_LOAD:
			Load();
			break;
		case EMM_BACK:
			return;
		}
	}
}

int CEditorMonster::OutputMenu()
{
	system("cls");
	cout << "1. 몬스터 추가" << endl;
	cout << "2. 몬스터 삭제" << endl;
	cout << "3. 몬스터 목록" << endl;
	cout << "4. 저장" << endl;
	cout << "5. 불러오기" << endl;
	cout << "6. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = Input<int>();

	if (iMenu <= EMM_NONE || iMenu > EMM_BACK)
		return EMM_NONE;

	return iMenu;
}

void CEditorMonster::Insert()
{
	CMonster* pMonster = new CMonster;

	if (!pMonster->Init())
	{
		SAFE_DELETE(pMonster);
		return;
	}

	system("cls");
	cout << "=================== 몬스터 추가 =================== " << endl;
	cout << "이름 : ";
	string strName;
	cin >> strName;

	pMonster->SetName(strName);

	int iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp;
	cout << "최소공격력 : ";
	cin >> iAttackMin;

	cout << "최대공격력 : ";
	cin >> iAttackMax;

	cout << "최소방어력 : ";
	cin >> iArmorMin;

	cout << "최대방어력 : ";
	cin >> iArmorMax;

	cout << "체력 : ";
	cin >> iHP;

	cout << "마나 : ";
	cin >> iMP;

	cout << "레벨 : ";
	cin >> iLevel;

	cout << "획득경험치 : ";
	cin >> iExp;

	pMonster->SetCharacterInfo(iAttackMin, iAttackMax, iArmorMin, iArmorMax,
		iHP, iMP, iLevel, iExp);

	int iGoldMin, iGoldMax;
	cout << "최소 골드 : ";
	cin >> iGoldMin;
	cout << "최대 골드 : ";
	cin >> iGoldMax;

	pMonster->SetGold(iGoldMin, iGoldMax);

	int iStage = ST_NONE;
	
	while (iStage <= ST_NONE || iStage >= ST_BACK)
	{
		cout << "1. Easy" << endl;
		cout << "2. Normal" << endl;
		cout << "3. Hard" << endl;
		cout << "난이도를 선택하세요 : ";
		iStage = Input<int>();
	}

	pMonster->SetStageType((STAGE_TYPE)iStage);

	m_vecMonster.push_back(pMonster);
}

void CEditorMonster::Delete()
{
	while (true)
	{
		system("cls");
		cout << "=================== 몬스터 삭제 =================== " << endl;
		for (size_t i = 0; i < m_vecMonster.size(); ++i)
		{
			cout << i + 1 << ". ";
			m_vecMonster[i]->Render();
			cout << endl;
		}
		cout << m_vecMonster.size() + 1 << ". 뒤로가기" << endl;
		cout << "삭제할 몬스터를 선택하세요 : ";
		int iDelete = Input<int>();

		if (iDelete <= 0 || iDelete > m_vecMonster.size() + 1)
			continue;
		else if (iDelete == m_vecMonster.size() + 1)
			return;

		m_vecMonster.erase(m_vecMonster.begin() + (iDelete - 1));
	}
}

void CEditorMonster::OutputMonsterList()
{
	system("cls");
	cout << "=================== 몬스터 출력 =================== " << endl;

	for (size_t i = 0; i < m_vecMonster.size(); ++i)
	{
		cout << i + 1 << ". ";
		m_vecMonster[i]->Render();
		cout << endl;
	}

	system("pause");
}

void CEditorMonster::Save()
{
	if (m_vecMonster.size() != 0)
	{
		system("cls");
		cout << "=================== 파일 저장 =================== " << endl;

		CFileStream file("MonsterList.mtl", "wb");

		size_t iMonsterCount = m_vecMonster.size();

		file.Write(&iMonsterCount, 4);

		for (size_t i = 0; i < iMonsterCount; ++i)
		{
			m_vecMonster[i]->Save(&file);
		}

		cout << "몬스터 파일 저장 완료" << endl;
		system("pause");
	}
	else
	{
		cout << "몬스터 파일이 없습니다." << endl;
		system("pause");
	}
}

void CEditorMonster::Load()
{
	system("cls");
	cout << "=================== 파일 불러오기 =================== " << endl;

	CFileStream file("MonsterList.mtl", "rb");

	if (file.GetOpen())
	{
		Safe_Delete_VecOrList(m_vecMonster);

		size_t iMonsterCount = 0;

		file.Read(&iMonsterCount, 4);

		file.Write(&iMonsterCount, 4);

		for (size_t i = 0; i < iMonsterCount; ++i)
		{
			CMonster* pMonster = new CMonster;

			if (!pMonster->Init())
			{
				SAFE_DELETE(pMonster);
				return;
			}

			pMonster->Load(&file);

			m_vecMonster.push_back(pMonster);
		}

		cout << "몬스터 파일 읽기 완료" << endl;
		system("pause");
	}
	else
	{
		cout << "몬스터 파일이 없습니다." << endl;
		system("pause");
	}
}
