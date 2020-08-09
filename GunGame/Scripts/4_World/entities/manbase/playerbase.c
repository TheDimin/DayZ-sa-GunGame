const int GunGameRespawn = 9984;
modded class PlayerBase
{   
    int MapVote = -1;

    void PlayerBase()
    {
        GetDayZGame().GunGameStateChange.Insert(OnGameStateChange);
    }

    void OnGameStateChange(int value)
    {
        switch (value)
        {
            case 2:
            {
                MapVote = -1;
            }
            break;
        }
    }

    //Hack for respawninging
    void GunGameRespawn()
    {
        if(!GetGame().IsServer())
            return;
        	//GetMission().OnEvent(GunGameRespawn, Param1<PlayerBase> );

        //TODO Kill EEKILLED
        //TODO Heal player

        vector location;
        float yaw;
        LocationManager<GunGameLocation>.instance.GetSpawnPoint(null,location,yaw);

        PlaceOnSurface();
        SetPosition(location);
        SetOrientation(Vector(0,yaw,0));

        
    }

    override bool CanJump()
	{
        if(GetGame().IsServer())
        {
            //mark kill
            //Kill player
            LevelKillStat.Cast(GetPlayerStats().GetPCO().GetStatObject(EGunGameStats.KILLCOUNT)).Increase();
            SetHealth("","",0);
        }

        return super.CanJump();
    }

    override void EEKilled( Object killer )
	{
        Print("Got killed");
        super.EEKilled(killer);

        //TEMP
        SyncEvents.EventOnPlayerKilledByPlayer.Invoke(this,killer, null, true);
    }

    override void OnCommandHandlerTick(float delta_time, int pCurrentCommandID)
	{
        //Copied death condition from base class ! instead of calling that other funtion we call our sync event
	    if( !IsAlive() )
		{
			if ( !m_DeathSyncSent && m_KillerData )
			{
                if(m_KillerData.m_Killer != this)
				    SyncEvents.EventOnPlayerKilledByPlayer.Invoke(this,m_KillerData.m_Killer, m_KillerData.m_MurderWeapon, m_KillerData.m_KillerHiTheBrain);
			}
		}

        super.OnCommandHandlerTick(delta_time, pCurrentCommandID);
    }

    //SetHealth(0);

    override void OnItemInHandsChanged ()
	{
		super.OnItemInHandsChanged();
        if(GetItemAccessor().IsItemInHandsWeapon())
        {
            Print("Player holds weapon in hands");
            auto weapon = Weapon_Base.Cast(GetItemInHands());
            //TODO show mag
            //	proto native void SelectionMagazineShow ();?
            //weapon.HideWeaponBarrel(false);
            weapon.ShowMagazine();
        }
	}

#ifndef GG_Debug
    override bool IsInventoryVisible()
	{
		return false;
	}

    bool CanManipulateInventory()
	{
         return false;
	}
#endif
}