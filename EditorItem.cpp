#include "EditorItem.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "FileStream.h"

DEFINITION_SINGLE(CEditorItem)

enum EDIT_ITEM_MENU
{
	EIM_NONE,
	EIM_INSERT,
	EIM_DELETE,
	EIM_OUTPUT,
	EIM_SAVE,
	EIM_LOAD,
	EIM_BACK
};

CEditorItem::CEditorItem()
{
}


CEditorItem::~CEditorItem()
{
	Safe_Delete_VecOrList(m_vecWeapon);
	Safe_Delete_VecOrList(m_vecArmor);	
}

bool CEditorItem::Init()
{
	return true;
}

void CEditorItem::Run()
{
	while (true)
	{
		switch (OutputMenu())
		{
		case EIM_INSERT:
			Insert();
			break;
		case EIM_DELETE:
			Delete();
			break;
		case EIM_OUTPUT:
			OutputStoreList();
			break;
		case EIM_SAVE:
			Save();
			break;
		case EIM_LOAD:
			Load();
			break;
		case EIM_BACK:
			return;
		}
	}
}

int CEditorItem::OutputMenu()
{
	system("cls");
	cout << "1. ������ �߰�" << endl;
	cout << "2. ������ ����" << endl;
	cout << "3. ������ ���" << endl;
	cout << "4. ����" << endl;
	cout << "5. �ҷ�����" << endl;
	cout << "6. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iMenu = Input<int>();

	if (iMenu <= EIM_NONE || iMenu > EIM_BACK)
		return EIM_NONE;

	return iMenu;
}

void CEditorItem::Insert()
{
	CItem* pItem = nullptr;

	system("cls");
	cout << "=================== ������ �߰� =================== " << endl;
	int iItemType = -1;

	while (iItemType <= 0 || iItemType > IT_MAX)
	{
		cout << "1. ����" << endl;
		cout << "2. ��" << endl;
		cout << "������ ������ �����ϼ��� : ";
		iItemType = Input<int>();
	}

	switch (iItemType-1)
	{
	case IT_WEAPON:
		pItem = new CItemWeapon;
		break;
	case IT_ARMOR:
		pItem = new CItemArmor;
	default:
		break;
	}

	if (!pItem->Init())
	{
		SAFE_DELETE(pItem);
		return;
	}

	cin.ignore(1024, '\n');
	cout << "�̸� : ";
	char strName[256] = {};
	cin.getline(strName, 255);

	pItem->SetName(strName);

	int iPrice, iSell;
	cout << "Price : ";
	cin >> iPrice;

	cout << "Sell : ";
	cin >> iSell;

	switch (iItemType-1)
	{
	case IT_WEAPON:
	{
		int iAttackMin, iAttackMax, fCritical;
		cout << "�ּҰ��ݷ� : ";
		iAttackMin = Input<int>();

		cout << "�ִ���ݷ� : ";
		iAttackMax = Input<int>();

		cout << "ġ��Ÿ Ȯ�� : ";
		fCritical = Input<float>();

		((CItemWeapon*)pItem)->SetWeaponInfo(iAttackMin, iAttackMax, fCritical);
		break;
	}
	case IT_ARMOR:
	{
		int iArmorMin, iArmorMax;
		cout << "�ּҹ��� : ";
		iArmorMin = Input<int>();

		cout << "�ִ���� : ";
		iArmorMax = Input<int>();

		((CItemArmor*)pItem)->SetArmorInfo(iArmorMin, iArmorMax);
		break;
	}
	default:
		break;
	}

	char  strDesc[256] = {};

	cin.ignore(1024, '\n');
	cout << "������ ���� : ";
	cin.getline(strDesc, 255);

	pItem->SetItemInfo((ITEM_TYPE)(iItemType - 1), iPrice, iSell, strDesc);

	switch (iItemType-1)
	{
	case IT_WEAPON:
		m_vecWeapon.push_back(pItem);
		break;
	case IT_ARMOR:
		m_vecArmor.push_back(pItem);
		break;
	}
}

void CEditorItem::Delete()
{	int iItemType = -1;

	while (iItemType <= 0 || iItemType > IT_MAX)
	{
		system("cls");
		cout << "1. ����" << endl;
		cout << "2. ��" << endl;
		cout << "������ ������ �����ϼ��� : ";
		iItemType = Input<int>();
	}

	switch (iItemType - 1)
	{
	case IT_WEAPON:
		while (true)
		{
			system("cls");
			cout << "=================== ������ ���� =================== " << endl;
			for (size_t i = 0; i < m_vecWeapon.size(); ++i)
			{
				cout << i + 1 << ". ";
				m_vecWeapon[i]->Render();
				cout << endl;
			}
			cout << m_vecWeapon.size() + 1 << ". �ڷΰ���" << endl;
			cout << "������ �������� �����ϼ��� : ";
			int iDelete = Input<int>();

			if (iDelete <= 0 || iDelete > m_vecWeapon.size() + 1)
				continue;
			else if (iDelete == m_vecWeapon.size() + 1)
				return;

			m_vecWeapon.erase(m_vecWeapon.begin() + (iDelete - 1));
		}
		break;
	case IT_ARMOR:
		while (true)
		{
			system("cls");
			cout << "=================== ������ ���� =================== " << endl;
			for (size_t i = 0; i < m_vecArmor.size(); ++i)
			{
				cout << i + 1 << ". ";
				m_vecArmor[i]->Render();
				cout << endl;
			}
			cout << m_vecArmor.size() + 1 << ". �ڷΰ���" << endl;
			cout << "������ �������� �����ϼ��� : ";
			int iDelete = Input<int>();

			if (iDelete <= 0 || iDelete > m_vecArmor.size() + 1)
				continue;
			else if (iDelete == m_vecArmor.size() + 1)
				return;

			m_vecArmor.erase(m_vecArmor.begin() + (iDelete - 1));
		}
		break;
	default:
		break;
	}
	
	
}

void CEditorItem::OutputStoreList()
{
	system("cls");
	cout << "=================== ������� =================== " << endl;
	for (size_t i = 0; i < m_vecWeapon.size(); ++i)
	{
		cout << i + 1 << ". ";
		m_vecWeapon[i]->Render();
		cout << endl;
	}

	cout << "=================== ������ =================== " << endl;
	for (size_t i = 0; i < m_vecArmor.size(); ++i)
	{
		cout << i + 1 << ". ";
		m_vecArmor[i]->Render();
		cout << endl;
	}

	system("pause");
}

void CEditorItem::Save()
{	
	if (m_vecWeapon.size() != 0 && m_vecArmor.size() != 0)
	{
		CFileStream file("StoreWeapon.swp", "wb");

		if (file.GetOpen())
		{
			size_t iCount = m_vecWeapon.size();

			file.Write(&iCount, 4);

			for (size_t i = 0; i < iCount; ++i)
			{
				m_vecWeapon[i]->Save(&file);
			}

			file.Close();
		}

		if (file.Open("StoreArmor.sar", "wb"))
		{
			size_t iCount = m_vecArmor.size();

			file.Write(&iCount, 4);

			for (size_t i = 0; i < iCount; ++i)
			{
				m_vecArmor[i]->Save(&file);
			}

			file.Close();
		}

		cout << "���� ��� ���� �Ϸ�" << endl;
		system("pause");
	}
	else
	{
		cout << "���� ����� �����ϴ�." << endl;
		system("pause");
	}
}

void CEditorItem::Load()
{
	Safe_Delete_VecOrList(m_vecWeapon);
	Safe_Delete_VecOrList(m_vecArmor);

	CFileStream file("StoreWeapon.swp", "rb");

	if (file.GetOpen())
	{
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; ++i)
		{
			CItemWeapon* pItem = new CItemWeapon;

			if (!pItem->Init())
			{
				SAFE_DELETE(pItem);
				return;
			}

			pItem->Load(&file);

			m_vecWeapon.push_back(pItem);
		}

		file.Close();
	}

	if (file.Open("StoreArmor.sar", "rb"))
	{

		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; ++i)
		{
			CItemArmor* pItem = new CItemArmor;

			if (!pItem->Init())
			{
				SAFE_DELETE(pItem);
				return;
			}

			pItem->Load(&file);

			m_vecArmor.push_back(pItem);
		}

		file.Close();
	}

	cout << "���� ��� �б� �Ϸ�" << endl;
	system("pause");
}
