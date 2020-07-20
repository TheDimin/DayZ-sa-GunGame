modded class DayZPlayerImplement
{
    static const int DEAD_SCREEN_DELAY = 1000; //ms
	static const float DEFAULT_DYING_TIME = 0; //s
	static const float DYING_PROGRESSION_TIME = 999; //STupid number to make sure Default dying time is always lower
    static const float m_DeathSimulationTimeout = 0;


    //NOTE ShowDeadScreen is not the respawn menu !!! only the "You are dead" screen
     
    override void SimulateDeath(bool state)
	{
        //super.SimulateDeath(false);
        //TODO check if we should force respawn when state is false

        
		if(state)
		{
        	GetGame().GetMission().SetPlayerRespawning(true);
        	GetGame().RespawnPlayer();
	    	//turns off dead screen, hides HUD for countdown
	    	//------------------------------------------------- 
	    	auto missionGP = GetGame().GetMission();
	    	//missionGP.DestroyAllMenus();

	    	//---------------------------------------------------
	    	missionGP.Continue();
		}
	    // Close();
    }

    override void ResetDeathStartTime()
	{
	}
}
