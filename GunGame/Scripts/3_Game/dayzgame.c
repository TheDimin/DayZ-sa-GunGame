class GunGameConfig : Managed
{
	int MinPlayers = 2;
	ref array<ref MapVoteInfo> mapVoteInfo;
}

///Information about a specific map that will be replicated to clients
class MapVoteInfo : Managed
{
    string name = "null";
    vector location = "0 0 0"; //Center point of all spawnpoints of the map
    int count = 0;

    void MapVoteInfo(string Name, vector Location)
    {
        if(Name != "")
            name = Name;

        location = Location;
    }
}

modded class DayZGame
{
	static ref GunGameConfig gunGameconfig;

	ref ScriptInvoker GunGameStateChange = new ScriptInvoker();
	ref ScriptInvoker OnConfigReplicated = new ScriptInvoker();
	int gunGameState = -1;
	
	void DayZGame()
	{
		GunGameStateChange.Insert(OnGunGameStateChange);
	}

	void OnGunGameStateChange(int newState)
	{
		gunGameState = newState;
	}

	//Called on client
	void RpcLoadData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		if( type == CallType.Client )
        {
			
			Param1<GunGameConfig > data;
        	if ( !ctx.Read( data ) ) 
				return;

			gunGameconfig = data.param1;
			Print("[CHECK] COnfig value: "+ gunGameconfig.mapVoteInfo[0].name );
			OnConfigReplicated.Invoke(gunGameconfig);
		}
	}

	void RpcOnStateChange(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Print("RpcOnStateChange called");
		if( type == CallType.Client )
        {
			Param1<int> data;
			if(!ctx.Read(data))
			{
				Error("Failed to read data");
				return;
			}

			GunGameStateChange.Invoke(data.param1);
		}
	}
}