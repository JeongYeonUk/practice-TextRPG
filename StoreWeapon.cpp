#include "StoreWeapon.h"
#include "ItemWeapon.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "FileStream.h"

CStoreWeapon::CStoreWeapon()
{
}


CStoreWeapon::~CStoreWeapon()
{
}

bool CStoreWeapon::Init()
{
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
				return false;
			}

			pItem->Load(&file);

			m_vecItem.push_back(pItem);
		}

		file.Close();
	}
	else
	{
		CItemWeapon* pItem = (CItemWeapon*)CreateItem("목검", IT_WEAPON, 1000, 500,
			"나무로 만든 검");
		pItem->SetWeaponInfo(5, 10, 10.f);

		pItem = (CItemWeapon*)CreateItem("철검", IT_WEAPON, 3000, 1500,
			"철로 만든 검");
		pItem->SetWeaponInfo(20, 30, 20.f);

		pItem = (CItemWeapon*)CreateItem("무한의 대검", IT_WEAPON, 25000, 12500,
			"제일 강한 검");
		pItem->SetWeaponInfo(70, 100, 35.f);
	}

	return true;
}

void CStoreWeapon::Run()
{
	CPlayer*	pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");
	while (true)
	{
		system("cls");
		OutputTag("Weapon Store");
		OutputItemList();
		cout << m_vecItem.size() + 1 << ". 뒤로가기" << endl;
		cout << "보유금액 : " << pPlayer->GetGold() << " Gold" << endl;
		cout << "구매할 아이템을 선택하세요 : ";
		int iInput = Input<int>();

		if (iInput < 1 || iInput > m_vecItem.size() + 1)
			continue;
		else if (iInput == m_vecItem.size() + 1)
			return;

		if (GET_SINGLE(CInventory)->Full())
		{
			cout << "인벤토리에 빈 공간이 없습니다." << endl;
			continue;
		}
		else if (pPlayer->GetGold() < m_vecItem[iInput - 1]->GetItemInfo().iPrice)
		{
			cout << "소지금이 부족합니다." << endl;
			continue;
		}

		CItem* pItem = m_vecItem[iInput - 1]->Clone();

		GET_SINGLE(CInventory)->AddItem(pItem);

		pPlayer->AddGold(-(pItem->GetItemInfo().iPrice));
	}
}