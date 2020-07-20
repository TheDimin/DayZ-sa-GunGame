class LocationManager<Class MapType> : Managed
{
	static LocationManager<MapType> instance;

   	protected ref array<ref MapType> GamemodeMaps = new array<ref MapType>();
	ref MapType ActiveMap;

    private int nextLocationIndex = 0;

    void LocationManager()
    {
		if(!instance)
			instance = this;

        LoadConfig();
    }
    
	protected void LoadConfig()
	{
		protected static const string JSON_FILE_PATH = "$profile:GunGame/MapLocations.json";
		if( !FileExist( JSON_FILE_PATH ) )
		{
			//TODO test if this works
			DPrint("Failed to find MapLocations.json in profile namespace");
			return;
		}
		JsonFileLoader<ref array<ref MapType>>.JsonLoadFile( JSON_FILE_PATH, GamemodeMaps);

		SetCurrentMapByIndex(0);
	}

	void SetCurrentMapByIndex(int index)
	{
		if(GamemodeMaps.Count() <= 0)
		{
			DPrint("Failed to load data");
			return;
		}

		ActiveMap = GamemodeMaps[index];
	}
	
	MapType GetActiveMap()
	{
		return ActiveMap;
	}

    //Internal version that actualy gets a location (mod this when trying to do a different spawn implementation)
    protected Vector2 FindRandomSpawnLocation()
    {
		if(!ActiveMap)
		{
			Print("NO active map found");
		}

        Vector2 targetLocation = Utils.StrToVector2(ActiveMap.GetLocations().Get(nextLocationIndex));
        nextLocationIndex++;
        if(nextLocationIndex >= ActiveMap.GetLocations().Count())
        {
            nextLocationIndex = 0;
        }
					Print("[LocationManager] GetSpawnPoint called");
        return targetLocation;
    }

	void GetSpawnPoint(PlayerIdentity identity,out vector pos, out float yaw)
	{
		yaw = 0; //TODO ?
		Vector2 targetLocation = FindRandomSpawnLocation();
		pos = Vector(targetLocation.x, 0, targetLocation.y);
		
	}
}