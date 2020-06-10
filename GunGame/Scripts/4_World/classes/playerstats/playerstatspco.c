enum EGunGameStats : EPlayerStats_current
{
	GUNLEVEL
};

modded class PlayerStatsPCO_current
{
    override void Init()
	{
        super.Init();
		RegisterStat(EGunGameStats.GUNLEVEL,new GunLevelStat("GunLevel"));
	}
};