enum EGunGameStats : EPlayerStats_current
{
	GUNLEVEL,
	KILLCOUNT
}

class GunLevelStat extends PlayerStatBase
{
	protected int		m_value = 0;
	protected WeaponCreationManager gunGameManager;
	ref ScriptInvoker EventOnLastLvlFinished = new ScriptInvoker();
	
	void GunLevelStat(WeaponCreationManager manager)
	{
		gunGameManager = manager;
	}

	void ~GunLevelStat()
	{
		delete EventOnLastLvlFinished;
	}
		
	override void Init(int id)
	{
		m_Type = EGunGameStats.GUNLEVEL;
	}

	void Increase()
	{
        m_value++;

		if( m_value > GetMaxLevel() )
		{
			EventOnLastLvlFinished.Invoke();
		}
	}

    int GetMaxLevel()
    {
        if(!gunGameManager)
        {
            Error2("GunGame","GunGameManager is invalid");
            return -1;
        }

        return gunGameManager.WeaponCount();
    }

	void SetByFloat(float value)
	{
		if(m_value == 0)
		{
			m_value = value;
		}
		else
		{
			Print("Value was already set");
		}
	}

	override float Get()
	{
		return m_value;
	}
	
	override string GetLabel()
	{
		return "GunLevel";
	}
}