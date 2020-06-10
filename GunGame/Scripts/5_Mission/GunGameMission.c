class GunGameMP extends MissionServer
{
	ref GunGameManager gunGameManager = new GunGameManager();

	//override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	//{
	//	super.CreateCharacter(identity,pos,ctx,characterName);
		//TODO set location
	//}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		gunGameManager.SetGear(player);

		//Is this called on respawn ? if so we can't do it here 
		player.GetPlayerStats().GetStatObject(EGunGameStats.GUNLEVEL);
		/*
		EntityAI itemTop;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemTop = player.FindAttachmentBySlotName("Body");

		if ( itemTop )
		{
			itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
			if ( Class.CastTo(itemBs, itemEnt ) )
				itemBs.SetQuantity(4);

			SetRandomHealth(itemEnt);
			itemEnt = itemTop.GetInventory().CreateInInventory("Chemlight_White");
			SetRandomHealth(itemEnt);
			itemEnt = itemTop.GetInventory().CreateInInventory("Chemlight_White");

			rand = Math.RandomFloatInclusive(0.0, 1.0);
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory("Apple");
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory("Pear");
			else
				itemEnt = player.GetInventory().CreateInInventory("Plum");

			SetRandomHealth(itemEnt);
		}
		*/
	}

	

	override void OnClientPrepareEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout)
	{
		//WE can change spawn pos /rotation here !
		super.OnClientPrepareEvent(identity,useDB,pos,yaw,preloadTimeout);
		PrintString("Magic test =" + pos);
	}
}