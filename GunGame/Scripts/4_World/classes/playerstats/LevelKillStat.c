class LevelKillStat extends PlayerStatBase
{
	protected int		m_value = 0;
	protected WeaponCreationManager m_GunGameManager;
	protected GunLevelStat m_GunLevelStat;
	
	void LevelKillStat(WeaponCreationManager manager,GunLevelStat gunLevelStat)
	{
		m_GunGameManager = manager;
		m_GunLevelStat = gunLevelStat;
	}
		
	override void Init(int id)
	{
		m_Type = EGunGameStats.KILLCOUNT;
	}

	void Increase()
	{
        m_value++;

		if( m_value >= GetRequiredKills() )
		{
			m_GunLevelStat.Increase();
			m_value = 0;
		}
	}

    int GetRequiredKills()
    {
        if(!m_GunGameManager)
        {
            Error2("GunGame","GunGameManager is invalid");
            return -1;
        }

		if(LocationManager<GunGameLocation>.instance.ActiveMap.Weapons.Count() < m_GunLevelStat.Get())
		{
			Error2("GunGame","Gun lvl is out of range");
			return -1;
		}

        return LocationManager<GunGameLocation>.instance.ActiveMap.Weapons[m_GunLevelStat.Get()].GetRequiredKills();
    }

	override float Get()
	{
		return m_value;
	}
	
	override string GetLabel()
	{
		return "CurrentKills";
	}
}