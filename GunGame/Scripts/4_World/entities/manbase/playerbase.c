modded class PlayerBase
{   
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