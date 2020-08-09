modded class MissionServer
{
    //Killer weapon can be null
    void OnPlayerKilledByPlayer( PlayerBase victim, PlayerBase killer, EntityAI killerWeapon, bool is_headshot );

    override void OnInit()
	{
		super.OnInit();

        //auto eventOnPlayerKilledByPlayer = ;
        SyncEvents.GetEventOnPlayerKilledByPlayer().Insert(OnPlayerKilledByPlayer);
    }
    
}