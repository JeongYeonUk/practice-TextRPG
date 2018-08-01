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
	cout << "1. ���� �߰�" << endl;
	cout << "2. ���� ����" << endl;
	cout << "3. ���� ���" << endl;
	cout << "4. ����" << endl;
	cout << "5. �ҷ�����" << endl;
	cout << "6. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ��� : ";
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
	cout << "=================== ���� �߰� =================== " << endl;
	cout << "�̸� : ";
	string strName;
	cin >> strName;

	pMonster->SetName(strName);

	int iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp;
	cout << "�ּҰ��ݷ� : ";
	cin >> iAttackMin;

	cout << "�ִ���ݷ� : ";
	cin >> iAttackMax;

	cout << "�ּҹ��� : ";
	cin >> iArmorMin;

	cout << "�ִ���� : ";
	cin >> iArmorMax;

	cout << "ü�� : ";
	cin >> iHP;

	cout << "���� : ";
	cin >> iMP;

	cout << "���� : ";
	cin >> iLevel;

	cout << "ȹ�����ġ : ";
	cin >> iExp;

	pMonster->SetCharacterInfo(iAttackMin, iAttackMax, iArmorMin, iArmorMax,
		iHP, iMP, iLevel, iExp);

	int iGoldMin, iGoldMax;
	cout << "�ּ� ��� : ";
	cin >> iGoldMin;
	cout << "�ִ� ��� : ";
	cin >> iGoldMax;

	pMonster->SetGold(iGoldMin, iGoldMax);

	int iStage = ST_NONE;
	
	while (iStage <= ST_NONE || iStage >= ST_BACK)
	{
		cout << "1. Easy" << endl;
		cout << "2. Normal" << endl;
		cout << "3. Hard" << endl;
		cout << "���̵��� �����ϼ��� : ";
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
		cout << "=================== ���� ���� =================== " << endl;
		for (size_t i = 0; i < m_vecMonster.size(); ++i)
		{
			cout << i + 1 << ". ";
			m_vecMonster[i]->Render();
			cout << endl;
		}
		cout << m_vecMonster.size() + 1 << ". �ڷΰ���" << endl;
		cout << "������ ���͸� �����ϼ��� : ";
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
	cout << "=================== ���� ��� =================== " << endl;

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
		cout << "=================== ���� ���� =================== " << endl;

		CFileStream file("MonsterList.mtl", "wb");

		size_t iMonsterCount = m_vecMonster.size();

		file.Write(&iMonsterCount, 4);

		for (size_t i = 0; i < iMonsterCount; ++i)
		{
			m_vecMonster[i]->Save(&file);
		}

		cout << "���� ���� ���� �Ϸ�" << endl;
		system("pause");
	}
	else
	{
		cout << "���� ������ �����ϴ�." << endl;
		system("pause");
	}
}

void CEditorMonster::Load()
{
	system("cls");
	cout << "=================== ���� �ҷ����� =================== " << endl;

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

		cout << "���� ���� �б� �Ϸ�" << endl;
		system("pause");
	}
	else
	{
		cout << "���� ������ �����ϴ�." << endl;
		system("pause");
	}
}
