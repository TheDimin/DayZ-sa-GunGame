class GunGameManager
{
    ref array<ref GunLevel> GunLevels = new array<ref GunLevel>;

    void GunGameManager()
    {
        GunLevels.Insert(new GunLevel("M4A1","Mag_CMAG_30Rnd",{"ACOGOptic","M4_PlasticHndgrd","M4_OEBttstck"}));
    }

    void SetGear(PlayerBase player)
    {
        //todo
        auto gunLevel = GunLevels[0];
        auto weapon = SetWeapon(player,gunLevel);
		AddMag(player,weapon,gunLevel);
        AddAttachments(weapon,gunLevel);
    }

    private Weapon_Base SetWeapon(PlayerBase _Player,GunLevel _GunLevel)
    {
        auto humanInventory = _Player.GetHumanInventory();

        auto weapon = Weapon_Base.Cast(humanInventory.CreateInHands( _GunLevel.weaponName ));
		humanInventory.CreateInInventory(_GunLevel.magName);
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

	    //EntityAI mag = SpawnEntity( _GunLevel.magName, il, ECE_IN_INVENTORY, RF_DEFAULT );

        EntityAI mag = EntityAI.Cast(_Weapon.GetInventory().CreateAttachment(_GunLevel.magName));

	    GetGame().RemoteObjectDelete( mag );
	    GetGame().RemoteObjectDelete( _Weapon );

	    pushToChamberFromAttachedMagazine( _Weapon, _Weapon.GetCurrentMuzzle() );

	    ScriptReadWriteContext ctx = new ScriptReadWriteContext;
	    ctx.GetWriteContext().Write( stateId );
	    _Weapon.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );

	    GetGame().RemoteObjectCreate( _Weapon );
	    GetGame().RemoteObjectCreate( mag );
    }

    private void AddAttachments(Weapon_Base _Weapon,GunLevel _GunLevel)
    {
        foreach(string _AttachmentName : _GunLevel.attachmentNames)
		{
			_Weapon.GetInventory().CreateAttachment(_AttachmentName);
		}
    }
	
	int GetLevels()
	{
		return GunLevels.Count();
	}

}