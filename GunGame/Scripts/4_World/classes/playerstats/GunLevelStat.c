class GunLevelStat extends PlayerStatBase
{
	protected int		level = 0;
	protected string 	label;
	protected WeaponCreationManager gunGameManager;
	
	void GunLevelStat( string label)
	{
		label 	= label;
	}
		
	override void Init(int id)
	{
		m_Type = id;
	}

    void SetWeaponCreationManager(WeaponCreationManager manager)
    {
        if(gunGameManager)
        {
            Error2("GunGame","GunLevelStat has already a reference to GunGameManager");
            return;
        }

        gunGameManager = manager;   
    }
	
	override void SerializeValue(array<ref StatDebugObject> objects, int flags)
	{
		objects.Insert( new StatDebugObject(GetLabel(), Get(), eRemoteStatType.PLAYER_STATS) );
	}

	void Increase()
	{
        level++;

		if( level > GetMaxLevel() )
		{
			//TODO
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

	override float Get()
	{
		return level;
	}
	
	override string GetLabel()
	{
		return label;
	}
	
	override array<PlayerStatRecord> GetRecords()
	{
		return null;
	}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		ctx.Write(level);
	}

	override bool OnStoreLoad( ParamsReadContext ctx)
	{
		int value;
		if(ctx.Read(value))
		{
			level = value;
		}
		else
		{
			return false;
		}
		return true;
	}
}