class LocationManager<Class MapType> : Managed
{
   	protected ref array<ref MapType> GamemodeMaps = new array<ref MapType>();
	ref MapType ActiveMap;

    private int nextLocationIndex = 0;

    void LocationManager()
    {
        LoadConfig();
    }
    
	void LoadConfig()
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
		ActiveMap = GamemodeMaps[index];
	}
	
	MapType GetActiveMap()
	{
		return ActiveMap;
	}

    //Internal version that actualy gets a location (mod this when trying to do a different spawn implementation)
    protected Vector2 FindRandomSpawnLocation()
    {
        Vector2 targetLocation = Utils.StrToVector2(ActiveMap.Locations.Get(nextLocationIndex));
        nextLocationIndex++;
        if(nextLocationIndex >= ActiveMap.Locations.Count())
        {
            nextLocationIndex = 0;
        }

        return targetLocation;
    }

	void GetSpawnPoint(PlayerIdentity identity,out vector pos, out float yaw)
	{
		yaw = 0; //TODO ?

		Vector2 targetLocation = FindRandomSpawnLocation();
		pos= Vector(targetLocation.x, 0, targetLocation.y);
	}
}