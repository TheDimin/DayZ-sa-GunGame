class WeaponCreationManager : Managed
{
	static WeaponCreationManager instance;

	LocationManager<GunGameLocation> locationManager;

	void WeaponCreationManager(LocationManager<GunGameLocation> _LocationManager)
	{
		if(instance != null)
		delete this;

		locationManager = _LocationManager;
		instance = this;
	}
	

//############## WEAPONS ##############
    void SetWeapon(PlayerBase player)
    {
        if(locationManager.ActiveMap == null || locationManager.ActiveMap.Weapons == null)
			return;//NO weapon to set, no data loaded 
        auto gunLevel = locationManager.ActiveMap.Weapons[player.GetPlayerStats().GetStatObject(EGunGameStats.GUNLEVEL).Get()];
       
	    if(gunLevel == null)
			Print("Chief we got a issue");

		
		WeaponHelpers.SetWeapon(player,gunLevel.weapon,gunLevel.mag,gunLevel.attachments);

        //AddAttachments(weapon,gunLevel);
		//AddMag(weapon,gunLevel);
    }

	int WeaponCount()
	{
		if(locationManager.ActiveMap == null)
			return 0;
			
		return locationManager.ActiveMap.Weapons.Count();
	}


 
}