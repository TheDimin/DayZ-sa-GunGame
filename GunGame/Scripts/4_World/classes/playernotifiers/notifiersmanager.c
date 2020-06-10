modded class NotifiersManager
{

    void NotifiersManager(PlayerBase player)
	{
        m_Player = player;

		m_Notifiers = new array<ref NotifierBase>;
		
		m_Notifiers.Insert(new HungerNotfr(this));
		m_Notifiers.Insert(new ThirstNotfr(this));
		m_Notifiers.Insert(new WarmthNotfr(this));
		m_Notifiers.Insert(new WetnessNotfr(this));
		m_Notifiers.Insert(new HealthNotfr(this));
		m_Notifiers.Insert(new FeverNotfr(this));
		m_Notifiers.Insert(new SickNotfr(this));
		//m_Notifiers.Insert(new BleedingNotfr(this));
		m_Notifiers.Insert(new StuffedNotfr(this));
		m_Notifiers.Insert(new BloodNotfr(this));
		//m_Notifiers.Insert(new AgentsNotfr(this));
		m_Notifiers.Insert(new PillsNotfr(this));
		m_Notifiers.Insert(new HeartbeatNotfr(this));
		
		m_MinTickTime = MIN_TICK_NOTIFIERS;

        //bit whack but only way i can think of disabling UI elements 
        //Would perfer not to touch the constructor so game updates changing it will work (Same for other mods)

        VirtualHud hud = GetVirtualHud();
        if(hud)
        {
        
            for(int i = 0;i < eDisplayElements.COUNT;i++)
            {
                if(i == eDisplayElements.DELM_TDCY_HEALTH || i == eDisplayElements.DELM_TDCY_BLOOD)
                continue;

                DisplayElementBadge dis_elm = DisplayElementBadge.Cast(hud.GetElement(i));
    
	    	    if( dis_elm )
	    	    {
	    		    dis_elm.SetLevel(eBadgeLevel.NONE);
	    	    }
            }
        }
    }
}