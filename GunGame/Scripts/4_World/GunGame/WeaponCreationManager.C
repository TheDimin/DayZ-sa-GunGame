class WeaponCreationManager : Managed
{
    ref array<ref GunLevel> gunLevels;
	
    void WeaponCreationManager()
    {
       LoadWeapons();
    }
	

//############## WEAPONS ##############
	void SetGunLevels(array<ref GunLevel> newLevels)
	{
		gunLevels = newLevels;
	}

	void LoadWeapons()
	{
		gunLevels = new array<ref GunLevel>; 
 		gunLevels.Insert(new GunLevel("M4A1","Mag_CMAG_30Rnd",{"ACOGOptic","M4_PlasticHndgrd","M4_OEBttstck"}));
	}

    void SetWeapon(PlayerBase player)
    {
        //todo 
        auto gunLevel = gunLevels[player.GetPlayerStats().GetStatObject(EGunGameStats.GUNLEVEL).Get()];
        auto weapon = SetWeapon(player,gunLevel);

		Print("CurrentGun lvl :" + player.GetPlayerStats().GetStatObject(EGunGameStats.GUNLEVEL).Get().ToString());

        AddAttachments(weapon,gunLevel);
    }

	int WeaponCount()
	{
		return gunLevels.Count();
	}


    private Weapon_Base SetWeapon(PlayerBase _Player,GunLevel _GunLevel)
    {
        auto humanInventory = _Player.GetHumanInventory();
		auto entityInHands = GetHumanInventory().GetEntityInHands();

		if(entityInHands)
		{
			delete entityInHands;
		}

        auto weapon = Weapon_Base.Cast(humanInventory.CreateInHands( _GunLevel.weapon ));
		AddMag(_Player,weapon,_GunLevel);
		
		return weapon;
    }

    private void AddMag(PlayerBase _Player,Weapon_Base _Weapon,GunLevel _GunLevel)
    {
        //the magic that made autoloading possible https://feedback.bistudio.com/T149240
        int stateId = -1;

	    if ( _Weapon.IsInherited( SKS_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( BoltActionRifle_InnerMagazine_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( DoubleBarrel_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( Pistol_Base ) )
	    {
	    	stateId = PistolStableStateID.CLO_DIS_BU0_MA1;
	    } else if ( _Weapon.IsInherited( CZ527_Base ) )
	    {
	    	stateId = CZ527StableStateID.CZ527_CLO_BU0_MA1;
	    } else if ( _Weapon.IsInherited( Repeater_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( RifleBoltFree_Base ) )
	    {
	    	stateId = RBFStableStateID.RBF_CLO_BU0_MA1;
	    } else if ( _Weapon.IsInherited( RifleBoltLock_Base ) )
	    {
	    	stateId = RBLStableStateID.RBL_OPN_BU0_MA1;
	    } else if ( _Weapon.IsInherited( Mp133Shotgun_Base ) )
	    {
	    	return;
	    }

        //InventoryLocation il = new InventoryLocation;
	    //il.SetAttachment( _Weapon, NULL, InventorySlots.MAGAZINE );
	    // using any of the inventory sync for existing spawning magazines also works
	    // e.g. GameInventory.LocationSyncMoveEntity

	    //EntityAI mag = SpawnEntity( _GunLevel.mag, il, ECE_IN_INVENTORY, RF_DEFAULT );

        EntityAI mag = EntityAI.Cast(_Weapon.GetInventory().CreateAttachment(_GunLevel.mag));

	    GetGame().RemoteObjectDelete( mag );
	    GetGame().RemoteObjectDelete( _Weapon );
		_Weapon.AttachMagazine(_Weapon.GetCurrentMuzzle(),Magazine.Cast(mag));

	    pushToChamberFromAttachedMagazine( _Weapon, _Weapon.GetCurrentMuzzle() );

	     ScriptReadWriteContext ctx = new ScriptReadWriteContext;
	     ctx.GetWriteContext().Write( stateId );
	    _Weapon.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );

	    GetGame().RemoteObjectCreate( _Weapon );
	    GetGame().RemoteObjectCreate( mag );

		_Weapon.SyncSelectionState(true,true);
		
    }

    private void AddAttachments(Weapon_Base _Weapon,GunLevel _GunLevel)
    {
        foreach(string _AttachmentName : _GunLevel.attachments)
		{
			_Weapon.GetInventory().CreateAttachment(_AttachmentName);
		}
    }
}