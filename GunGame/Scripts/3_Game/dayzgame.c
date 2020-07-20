class GunGameConfig
{
	int MinPlayers = 2;
}


modded class DayZGame
{
	static ref GunGameConfig gunGameconfig = new GunGameConfig();

	ref ScriptInvoker GunGameStateChange = new ScriptInvoker();;

	void DayZGame()
	{
	}

	void GunGameLoadConfig()
	{
		protected static const string JSON_FILE_PATH = "$profile:GunGame/Config.json";
		
		if( !FileExist( JSON_FILE_PATH ) )
		{
			MakeDirectory("$profile:GunGame");
			//TODO test if this works
			Print("Failed to find Config.json in profile namespace");
			return;
		}
		
		JsonFileLoader<GunGameConfig>.JsonLoadFile( JSON_FILE_PATH, gunGameconfig);
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
		}
	}

	void RpcOnStateChange(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if(IsServer())
		{
			Print("This garbage is called on server not client");
		}

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