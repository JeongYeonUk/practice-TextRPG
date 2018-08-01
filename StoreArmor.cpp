#include "StoreArmor.h"
#include "ItemArmor.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "FileStream.h"

CStoreArmor::CStoreArmor()
{
}


CStoreArmor::~CStoreArmor()
{
}

bool CStoreArmor::Init()
{
	/*CItemArmor* pItem = (CItemArmor*)CreateItem("Ãµ°©¿Ê", IT_ARMOR, 1000, 500,
		"ÃµÀ¸·Î ¸¸µç °©¿Ê");
	pItem->SetArmorInfo(3, 5);

	pItem = (CItemArmor*)CreateItem("°¡Á×°©¿Ê", IT_ARMOR, 3000, 1500,
		"°¡Á×À¸·Î ¸¸µç °©¿Ê");
	pItem->SetArmorInfo(10, 20);

	pItem = (CItemArmor*)CreateItem("°¡½Ã°©¿Ê", IT_ARMOR, 25000, 12500,
		"°¡½Ã°¡ µ¸Èù °©¿Ê");
	pItem->SetArmorInfo(30, 50);*/

	CFileStream file("StoreArmor.sar", "rb");

	if (file.GetOpen())
	{

		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; ++i)
		{
			CItemArmor* pItem = new CItemArmor;

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
		CItemArmor* pItem = (CItemArmor*)CreateItem("Ãµ°©¿Ê", IT_ARMOR, 1000, 500,
			"ÃµÀ¸·Î ¸¸µç °©¿Ê");
		pItem->SetArmorInfo(3, 5);

		pItem = (CItemArmor*)CreateItem("°¡Á×°©¿Ê", IT_ARMOR, 3000, 1500,
			"°¡Á×À¸·Î ¸¸µç °©¿Ê");
		pItem->SetArmorInfo(10, 20);

		pItem = (CItemArmor*)CreateItem("°¡½Ã°©¿Ê", IT_ARMOR, 25000, 12500,
			"°¡½Ã°¡ µ¸Èù °©¿Ê");
		pItem->SetArmorInfo(30, 50);
	}

	return true;
}

void CStoreArmor::Run()
{
	CPlayer*	pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");
	while (true)
	{
		system("cls");
		OutputTag("Armor Store");
		OutputItemList();
		cout << m_vecItem.size() + 1 << ". µÚ·Î°¡±â" << endl;
		cout << "º¸À¯±Ý¾× : " << pPlayer->GetGold() << " Gold" << endl;
		cout << "±¸¸ÅÇÒ ¾ÆÀÌÅÛÀ» ¼±ÅÃÇÏ¼¼¿ä : ";
		int iInput = Input<int>();

		if (iInput < 1 || iInput > m_vecItem.size() + 1)
			continue;
		else if (iInput == m_vecItem.size() + 1)
			return;

		if (GET_SINGLE(CInventory)->Full())
		{
			cout << "ÀÎº¥Åä¸®¿¡ ºó °ø°£ÀÌ ¾ø½À´Ï´Ù." << endl;
			continue;
		}
		else if (pPlayer->GetGold() < m_vecItem[iInput - 1]->GetItemInfo().iPrice)
		{
			cout << "¼ÒÁö±ÝÀÌ ºÎÁ·ÇÕ´Ï´Ù." << endl;
			continue;
		}

		CItem* pItem = m_vecItem[iInput - 1]->Clone();

		GET_SINGLE(CInventory)->AddItem(pItem);

		pPlayer->AddGold(-(pItem->GetItemInfo().iPrice));
	}
}
