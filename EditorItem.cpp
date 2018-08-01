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
	cout << "1. 아이템 추가" << endl;
	cout << "2. 아이템 삭제" << endl;
	cout << "3. 아이템 목록" << endl;
	cout << "4. 저장" << endl;
	cout << "5. 불러오기" << endl;
	cout << "6. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = Input<int>();

	if (iMenu <= EIM_NONE || iMenu > EIM_BACK)
		return EIM_NONE;

	return iMenu;
}

void CEditorItem::Insert()
{
	CItem* pItem = nullptr;

	system("cls");
	cout << "=================== 아이템 추가 =================== " << endl;
	int iItemType = -1;

	while (iItemType <= 0 || iItemType > IT_MAX)
	{
		cout << "1. 무기" << endl;
		cout << "2. 방어구" << endl;
		cout << "아이템 종류를 선택하세요 : ";
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
	cout << "이름 : ";
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
		cout << "최소공격력 : ";
		iAttackMin = Input<int>();

		cout << "최대공격력 : ";
		iAttackMax = Input<int>();

		cout << "치명타 확률 : ";
		fCritical = Input<float>();

		((CItemWeapon*)pItem)->SetWeaponInfo(iAttackMin, iAttackMax, fCritical);
		break;
	}
	case IT_ARMOR:
	{
		int iArmorMin, iArmorMax;
		cout << "최소방어력 : ";
		iArmorMin = Input<int>();

		cout << "최대방어력 : ";
		iArmorMax = Input<int>();

		((CItemArmor*)pItem)->SetArmorInfo(iArmorMin, iArmorMax);
		break;
	}
	default:
		break;
	}

	char  strDesc[256] = {};

	cin.ignore(1024, '\n');
	cout << "아이템 설명 : ";
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
		cout << "1. 무기" << endl;
		cout << "2. 방어구" << endl;
		cout << "아이템 종류를 선택하세요 : ";
		iItemType = Input<int>();
	}

	switch (iItemType - 1)
	{
	case IT_WEAPON:
		while (true)
		{
			system("cls");
			cout << "=================== 아이템 삭제 =================== " << endl;
			for (size_t i = 0; i < m_vecWeapon.size(); ++i)
			{
				cout << i + 1 << ". ";
				m_vecWeapon[i]->Render();
				cout << endl;
			}
			cout << m_vecWeapon.size() + 1 << ". 뒤로가기" << endl;
			cout << "삭제할 아이템을 선택하세요 : ";
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
			cout << "=================== 아이템 삭제 =================== " << endl;
			for (size_t i = 0; i < m_vecArmor.size(); ++i)
			{
				cout << i + 1 << ". ";
				m_vecArmor[i]->Render();
				cout << endl;
			}
			cout << m_vecArmor.size() + 1 << ". 뒤로가기" << endl;
			cout << "삭제할 아이템을 선택하세요 : ";
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
	cout << "=================== 무기상점 =================== " << endl;
	for (size_t i = 0; i < m_vecWeapon.size(); ++i)
	{
		cout << i + 1 << ". ";
		m_vecWeapon[i]->Render();
		cout << endl;
	}

	cout << "=================== 방어구상점 =================== " << endl;
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

		cout << "상점 목록 저장 완료" << endl;
		system("pause");
	}
	else
	{
		cout << "상점 목록이 없습니다." << endl;
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

	cout << "상점 목록 읽기 완료" << endl;
	system("pause");
}
