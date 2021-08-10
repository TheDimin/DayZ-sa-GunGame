class GunGameHud
{
    protected ref Widget	RootOverlay;
    protected ref Widget WaitingMenu;
    protected ref Widget VotingMenu;
    protected ref Widget m_InGameMenu;

    protected ref WrapSpacerWidget DebugMenu;

    protected ref TextWidget	PlayerCountText;
    protected ref TextWidget	VotesCountText;
    protected ref MapWidget     VotesSelectedMap;
    protected ref WrapSpacerWidget VotingSpacer;

    protected ref array<ref MapVoteEntry> VoteEntrys = new array<ref MapVoteEntry>();

    ref MapHandler m_MapHandler;

    protected int m_ActiveState = 0;



    void GunGameHud()
    {
        RootOverlay = GetGame().GetWorkspace().CreateWidgets("GunGame/gui/layouts/GunGameOverlay.layout");

        WaitingMenu = RootOverlay.FindAnyWidget("PreGame");
        PlayerCountText = TextWidget.Cast(WaitingMenu.FindAnyWidget("playerCountText"));

        VotingMenu = RootOverlay.FindAnyWidget("VotingForMap");
        VotesCountText = TextWidget.Cast(VotingMenu.FindAnyWidget("votesCountText"));
        VotesSelectedMap = MapWidget.Cast(VotingMenu.FindAnyWidget("VoteMap"));
        VotingSpacer = WrapSpacerWidget.Cast(VotingMenu.FindAnyWidget("VoteSpacer"));

        m_InGameMenu = RootOverlay.FindAnyWidget("InGame");
        DebugMenu = WrapSpacerWidget.Cast(m_InGameMenu.FindAnyWidget("DebugSpacer"));

        
        m_MapHandler = new MapHandler(VotesSelectedMap);
        GetRPCManager().AddRPC("GunGame","RpcReceivedMaps",this,SingeplayerExecutionType.Client);


        RegisterDebugMenu();

    }

    void ~GunGameHud()
    {
        RootOverlay.Unlink();
        delete RootOverlay;
    }

    void Init()
    {
        HidePanels();
        GetDayZGame().GunGameStateChange.Insert(OnGameStateChange);
        GetDayZGame().OnConfigReplicated.Insert(OnConfigReplicated);
    }

    void OnConfigReplicated(GunGameConfig config)
    {
        LoadMapData();
       // UpdatePlayerVotesText();
      //  UpdateplayerCountText();
        //Print(config.mapVoteInfo[0].name);
    }

    
    void Show( bool show )
	{
		RootOverlay.Show( show );
	}

    void OnGameStateChange(int value)
    {
        HidePanels();
        m_ActiveState = value;
        Print("GunGameHud::OnGameStateChange called ::" + value.ToString());


        switch (value)
        {
            case 1:
            {
                EnterWaitingOnPlayers();
            }
            break;
            case 2:
            {
                EnterVotingForMap();
            }
            break;
            case 3:
            {
                EnterIngameMenu();
            }
            break;
            default:
            {
                Error("Invalid state");
            }
        }
    }

    void EnterIngameMenu()
    {
        Print("Enterd voting menu");
        //#ifdef GG_Debug
        GetGame().GetUIManager().ShowCursor( true );
//#endif
    }

    void HidePanels()
    {
        GetGame().GetUIManager().ShowCursor( false );
        WaitingMenu.Show(false);
        VotingMenu.Show(false);
#ifndef GG_Debug
//        DebugMenu.show(false);
#endif
    }

    void  EnterWaitingOnPlayers()
    {
        WaitingMenu.Show(true);
    }

    void EnterVotingForMap()
    {
        VotingMenu.Show(true);
        //GetGame().GetUIManager().EnterScriptedMenu(MENU_INVENTORY,RootOverlay);
        GetGame().GetUIManager().ShowCursor( true );
       //EnterScriptedMenu .

		VotesSelectedMap.SetScale(0.09);
		VotesSelectedMap.SetMapPos("0 0 0");

//TEMP

       // RegisterMap(new MapVoteInfo("Test","150 0 150"));
        if(VoteEntrys == null || VoteEntrys.Count() <= 0)
        return;

        VoteEntrys[0].Focus();
		//VotesSelectedMap.SetScale(1);
		//VotesSelectedMap.SetMapPos(GetDayZGame().GetPlayer().GetPosition());
    }  

    void LoadMapData()
    {
        VoteEntrys = new array<ref MapVoteEntry>();

        int index = 0;
        foreach (MapVoteInfo newEntry : DayZGame.gunGameconfig.mapVoteInfo) // ForEach new item
		{
            RegisterMap(newEntry,index);
            index++;
        }
    }

    void RegisterMap(MapVoteInfo info,int index)
    {
        auto createdWidget = GetGame().GetWorkspace().CreateWidgets( "GunGame/gui/layouts/Elements/MapVoteInfo.layout", VotingSpacer );
        MapVoteEntry mapVoteEntry;
        createdWidget.GetScript(mapVoteEntry);
        mapVoteEntry.SetData(this,info,index);
        VoteEntrys.Insert(mapVoteEntry);
    }

    void SetVotingMapPos(MapVoteInfo voteInfo)
    {
        VotesSelectedMap.SetMapPos(voteInfo.location);
        //TODO generate some valid map scale
        //VotesSelectedMap.SetScale(0.05);
        Print("Changing map pos to ::" + voteInfo.location.ToString());
    }

    void UpdatePlayerVotesText()
    {
        //Print("[UpdateplayerCountText]: " + DayZGame.gunGameconfig.MinPlayers.ToString());
        VotesCountText.SetText("0" + " / " + ClientData.m_PlayerBaseList.Count().ToString()); //TODO get current votes
    }

    void UpdateplayerCountText()
    {
        //Print("[UpdateplayerCountText]: " + DayZGame.gunGameconfig.MinPlayers.ToString());
        PlayerCountText.SetText(ClientData.m_PlayerBaseList.Count().ToString() + " / " + DayZGame.gunGameconfig.MinPlayers.ToString());
    }


    void RegisterDebugMenu()
    {
        RegisterDebugFunction("Test Title",Test);
        RegisterDebugFunction("Reload Game",ReloadGame);
    } 

    void RegisterDebugFunction(string Title, func temp)
    {
        auto createdWidget = GetGame().GetWorkspace().CreateWidgets( "GunGame/gui/layouts/Elements/ScriptableButton.layout", DebugMenu );
        ScriptableElement scriptableElement;
        createdWidget.GetScript(scriptableElement);
        scriptableElement.SetTitle(Title);
        scriptableElement.OnClickEvent.Insert(temp);
    }

    void ReloadGame()
    {
        Print("something");
    }

    void Test()
    {
        Print("Amazing button test");
    }
}