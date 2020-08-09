//GunLevel LvlKillCount
typedef Param2<int, int> GunGameStats;

class GunGameMission extends MissionServer
{
	ref WeaponCreationManager weaponCreationManager;
	ref LocationManager<GunGameLocation> locationManager = new LocationManager<GunGameLocation>();
	ref GunGameFSM FSM = new GunGameFSM();

	ScriptModule BlueprintModule;

	//PlayerId and its GunLvlStat
	ref map<string, ref GunGameStats> PlayerGunLvls = new map<string,ref GunGameStats>();

	void GunGameMission()
	{	
		weaponCreationManager = new WeaponCreationManager(locationManager);
		
		auto waitOnPlayersState = new GGWaitOnPlayers();
		auto selectMapState = new GGSelectMapState();
		auto playingState = new GGPlayingState();

		auto enoughPlayersReadyEvent = new EnoughPlayersReadyEvent();
		auto mapVoteEndedEvent = new MapVoteEndedEvent(new array<int>);

		//FSMTransition<FSMStateBase, FSMEventBase, FSMActionBase, FSMGuardBase> t
		FSM.AddTransition(new GunGameTransition(waitOnPlayersState,enoughPlayersReadyEvent,selectMapState));
		FSM.AddTransition(new GunGameTransition(selectMapState, mapVoteEndedEvent,playingState));

		FSM.SetInitialState(waitOnPlayersState);
		FSM.Start(null);
		
		GetRPCManager().AddRPC("GunGame","SRpcVoteForMap",this,SingeplayerExecutionType.Server);

		BlueprintManager lel = new BlueprintManager();
	}

	override void OnInit()
	{
		super.OnInit();
		GunGameLoadConfig();

		//TEMP
		BlueprintModule = ScriptModule.LoadScript(MissionScript,"GunGame/Scripts/6_Generated",true);

		BlueprintModule.CallFunction(null,"Lol",null,null);
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

		JsonFileLoader<GunGameConfig>.JsonLoadFile( JSON_FILE_PATH, GetDayZGame().gunGameconfig);
		GetDayZGame().gunGameconfig.mapVoteInfo = LocationManager<GunGameLocation>.Get().mapVoteInfo;
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		FSM.Update(timeslice);
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		PlayerIdentity p_identity = player.GetIdentity();


		//Would have been nice if we did this on a lower layer, but we can't
		//If we found a gunlvl for set it otherwise create it.
		GunGameStats PlayerGunGameStat;
		if(!PlayerGunLvls.Find(p_identity.GetId(),PlayerGunGameStat))
		{
		//	Print("No Data for player found");
			PlayerGunGameStat = new GunGameStats(0,0);
		}

		auto gunLvlStat = new GunLevelStat(weaponCreationManager);
		gunLvlStat.EventOnLastLvlFinished.Insert(OnPlayerReachedLastLevel);
		gunLvlStat.SetByFloat(PlayerGunGameStat.param1);

		auto lvlKillStat = new LevelKillStat(weaponCreationManager,gunLvlStat);
		lvlKillStat.SetByFloat(PlayerGunGameStat.param2);

		player.GetPlayerStats().GetPCO().RegisterStat(EGunGameStats.GUNLEVEL,gunLvlStat);
		player.GetPlayerStats().GetPCO().RegisterStat(EGunGameStats.KILLCOUNT,lvlKillStat);

		weaponCreationManager.SetWeapon(player);
		//TODO: Is this called on respawn ? if so we can't do it here 
		
	}

	override void OnClientPrepareEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout)
	{
			//We don't care what others tried to do, For gungame we do not support database usage
		useDB = false;
		locationManager.GetSpawnPoint(identity,pos,yaw);
	}
	
	override void InvokeOnConnect(PlayerBase player,PlayerIdentity identity)
	{
		super.InvokeOnConnect(player,identity);
		Print("[CHECK] COnfig value: "+DayZGame.gunGameconfig.mapVoteInfo.Get(0).name );
		GetRPCManager().SendRPC( "GunGame", "RpcLoadData", new Param1< GunGameConfig >( DayZGame.gunGameconfig ), true, identity );
		//GetRPCManager().SendRPC("GunGame","RpcReceivedMaps",new MapsVoteInfoParam(LocationManager<GunGameLocation>.Get().GetVoteInfo()),true,identity);
	}
	
	override void InitEquipArrays()
	{
		super.InitEquipArrays();
		//Todo Setup All gungameLevels when lvl selected
	}

	//Killer weapon can be null
    override void OnPlayerKilledByPlayer( PlayerBase victim, PlayerBase killer, EntityAI killerWeapon, bool is_headshot )
    {
		PrintMessageToAll("MissionSErver:: Player got killed");
		LevelKillStat.Cast(killer.m_PlayerStats.GetPCO().GetStatObject(EGunGameStats.KILLCOUNT)).Increase();
		
		SaveDataBetweenRespawn(victim);
    }

	void OnPlayerReachedLastLevel()
	{
		PrintMessageToAll("Somebody reached last lvl");
	}

	void SaveDataBetweenRespawn(PlayerBase player)
	{
		Print("Saving data");
		auto gunLvlStat = player.GetPlayerStats().GetPCO().GetStatObject(EGunGameStats.GUNLEVEL).Get();
		auto lvlKillStat = player.GetPlayerStats().GetPCO().GetStatObject(EGunGameStats.KILLCOUNT).Get();
		
		PlayerGunLvls.Insert(player.GetIdentity().GetId(),new GunGameStats(gunLvlStat,lvlKillStat));
	}

	void SRpcVoteForMap(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if( type == CallType.Server )
        {
            Param1<int> data;
			if(!ctx.Read(data))
			{
				Error("Failed to read data");
				return;
			}
            
            GGSelectMapState currentstate = GGSelectMapState.Cast(FSM.GetCurrentState());

            if(currentstate == null)
            {    
                Print("Attempt on voting while state was not voting");
                return;
            }

			PlayerBase targetPlayer = PlayerBase.Cast(target);
			if(targetPlayer == null)
            {    
                Print("Failed to cast player");
                return;
            }
            
			if(targetPlayer.MapVote != -1)
			{
				currentstate.RemoveVote(targetPlayer.MapVote);
			}

			targetPlayer.MapVote = data.param1;
			currentstate.RegisterVote(targetPlayer.MapVote);
        }
    }

	//############# TEMP ###############
	void PrintMessageToAll (string msg) 
	{
        msg = "Server: " + msg;
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", msg, ""));
        Print(msg);

        //--- Message to all palyers
        ref array<Man> t_players = new array<Man>;
        GetGame().GetPlayers(t_players);
        foreach(auto t_player : t_players) {
            Param1<string> t_param_msg = new Param1<string>(msg);
            GetGame().RPCSingleParam(t_player, ERPCs.RPC_USER_ACTION_MESSAGE, t_param_msg, true, t_player.GetIdentity());
        }
    }
	
}