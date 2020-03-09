modded class MissionGameplay
{
	// we don't want users to open there inventory
	override void ShowInventory()
	{//only works if client has mod aswell
		super.ShowInventory();
	}


};