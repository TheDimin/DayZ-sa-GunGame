modded class IngameHud
{
    protected ref Widget	GGRootOverlay;
    protected ref Widget GGWaitingMenu;
    protected ref Widget GGVotingMenu;

    protected ref TextWidget	GGPlayerCountText;
    protected ref TextWidget	GGVotesCountText;
    protected ref MapWidget     GGVotesSelectedMap;
    protected ref WrapSpacerWidget GGWrapSpacer;
    ref MapHandler GGMapHandler;
    protected int GGActiveState = 0;

    protected ref array<ref MapVoteEntry> GGVoteEntrys = new array<ref MapVoteEntry>();

    void IngameHud()
    {
        GGRootOverlay = GetGame().GetWorkspace().CreateWidgets("GunGame/gui/layouts/GunGameOverlay.layout");

        GGWaitingMenu = GGRootOverlay.FindAnyWidget("PreGame");
        GGPlayerCountText = TextWidget.Cast(GGWaitingMenu.FindAnyWidget("playerCountText"));

        GGVotingMenu = GGRootOverlay.FindAnyWidget("VotingForMap");
        GGVotesCountText = TextWidget.Cast(GGVotingMenu.FindAnyWidget("votesCountText"));
        GGVotesSelectedMap = MapWidget.Cast(GGVotingMenu.FindAnyWidget("VoteMap"));
        GGWrapSpacer = WrapSpacerWidget.Cast(GGVotingMenu.FindAnyWidget("VoteSpacer"));
        
        GGMapHandler = new MapHandler(GGVotesSelectedMap);
    }

    void ~IngameHud()
    {
        delete GGRootOverlay;
    }

    override void Init( Widget hud_panel_widget )
	{
        super.Init(hud_panel_widget);

        #ifndef GG_Debug
            //Disabled Elements that we have disabled
            m_Notifiers.FindWidget("Temperature").Show(false);
            m_Notifiers.FindWidget("Hungry").Show(false);
            m_Notifiers.FindWidget("Thirsty").Show(false);
            m_Notifiers.FindWidget("NotifierDivider").Show(false);
            m_Notifiers.GetParent().FindWidget("BadgesSpacer").Show(false);
        #endif 

        Update(0);
        GetDayZGame().GunGameStateChange.Insert(OnGameStateChange);
    }

    override void Show( bool show )
	{
        super.Show(show);
		GGRootOverlay.Show( show );
	}

    void OnGameStateChange(int value)
    {
        HidePanels();
        GGActiveState = value;
        Print("GunGameHud::OnGameStateChange called ::" + value.ToString());
        GetGame().GetUIManager().ShowCursor( false );

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
        }
        
    }

    void HidePanels()
    {
        GGWaitingMenu.Show(false);
        GGVotingMenu.Show(false);
    }

    void  EnterWaitingOnPlayers()
    {
        GGWaitingMenu.Show(true);
    }

    void EnterVotingForMap()
    {
        GGVotingMenu.Show(true);
        
        float scale;
		vector map_pos;
		PlayerBase player = PlayerBase.Cast(GetDayZGame().GetPlayer());
		if( player && !player.GetLastMapInfo(scale,map_pos) )
		{
			string path = "CfgWorlds " + GetGame().GetWorldName();
			vector temp = GetGame().ConfigGetVector(path + " centerPosition");
			scale = 0.33;
			map_pos = Vector(temp[0],temp[2],temp[1]);
		}
        //GetGame().GetUIManager().EnterScriptedMenu(MENU_INVENTORY,GGRootOverlay);
        GetGame().GetUIManager().ShowCursor( true );
       //EnterScriptedMenu .

		GGVotesSelectedMap.SetScale(scale);
		GGVotesSelectedMap.SetMapPos(map_pos);

//TEMP
        GGVoteEntrys.Insert(new MapVoteEntry(GGWrapSpacer,this,new MapVoteInfo("Test","150 0 150",0)));
        

        GGVoteEntrys[0].Focus();
		//GGVotesSelectedMap.SetScale(1);
		//GGVotesSelectedMap.SetMapPos(GetDayZGame().GetPlayer().GetPosition());
    }  

    void SetVotingMapPos(MapVoteInfo voteInfo)
    {
        GGVotesSelectedMap.SetMapPos(voteInfo.location);
    }

    void UpdatePlayerVotesText()
    {
        //Print("[UpdateplayerCountText]: " + DayZGame.gunGameconfig.MinPlayers.ToString());
        GGVotesCountText.SetText(ClientData.m_PlayerBaseList.Count().ToString() + " / " + DayZGame.gunGameconfig.MinPlayers.ToString());
    }

    void UpdateplayerCountText()
    {
        //Print("[UpdateplayerCountText]: " + DayZGame.gunGameconfig.MinPlayers.ToString());
        GGPlayerCountText.SetText(ClientData.m_PlayerBaseList.Count().ToString() + " / " + DayZGame.gunGameconfig.MinPlayers.ToString());
    }


#ifndef GG_Debug
    //supposed to do the job
    override void RefreshQuickbarVisibility()
	{
		m_QuickbarWidget.Show(false);
	} 
#endif
}