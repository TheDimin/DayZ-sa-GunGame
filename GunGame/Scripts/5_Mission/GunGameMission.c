class GunGameMP extends MissionServer
{
	ref WeaponCreationManager weaponCreationManager = new WeaponCreationManager();
	ref LocationManager<GunGameLocation> locationManager = new LocationManager<GunGameLocation>();
	//override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	//{
	//	super.CreateCharacter(identity,pos,ctx,characterName);
		//TODO set location
	//}
	void GunGameMP()
	{	
		MissionServer();

		weaponCreationManager.SetGunLevels(locationManager.GetActiveMap().Weapons);
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		weaponCreationManager.SetWeapon(player);
		//TODO: Is this called on respawn ? if so we can't do it here 
		
	}

	override void OnClientPrepareEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout)
	{
		//We don't care what others tried to do, For gungame we do this
		useDB = false;
		locationManager.GetSpawnPoint(identity,pos,yaw);
	}
	
	
	override void InitEquipArrays()
	{
		super.InitEquipArrays();
		//Todo Setup All gungameLevels when lvl selected
	}
}