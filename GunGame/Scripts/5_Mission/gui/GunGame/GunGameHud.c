class GunGameHud : Managed
{
    protected ref Widget	rootOverlay;
    protected ref Widget waitingMenu;
    protected ref Widget votingMenu;

    protected ref TextWidget	playerCountText;
    protected ref TextWidget	votesCountText;
    protected ref MapWidget     votesSelectedMap;

    ref MapHandler mapHandler;
    protected int activeState = 0;

    void GunGameHud()
    {
        rootOverlay = GetGame().GetWorkspace().CreateWidgets("GunGame/gui/layouts/GunGameOverlay.layout");

        waitingMenu = rootOverlay.FindWidget("PreGame");
        playerCountText = TextWidget.Cast(waitingMenu.FindAnyWidget("playerCountText"));

        votingMenu = rootOverlay.FindWidget("VotingForMap");
        votesCountText = TextWidget.Cast(votingMenu.FindAnyWidget("votesCountText"));
        votesSelectedMap = MapWidget.Cast(votingMenu.FindAnyWidget("VoteMap"));

        mapHandler = new MapHandler(votesSelectedMap);
        
        Update(0);
        GetDayZGame().GunGameStateChange.Insert(OnGameStateChange);

       
    }

    void ~GunGameHud()
    {
        delete rootOverlay;
    }

    void Update( float timeslice )
	{
        //SHOULDN"T DO THIS EVERY FRAME
       // UpdateplayerCountText();
       // Print("PlayerPos:::" + GetDayZGame().GetPlayer().GetPosition().ToString());
		//votesSelectedMap.SetMapPos(GetDayZGame().GetPlayer().GetPosition());
    }

    void OnGameStateChange(int value)
    {
        HidePanels();
        activeState = value;
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
        }
        
    }

    void HidePanels()
    {
        waitingMenu.Show(false);
        votingMenu.Show(false);
    }

    void  EnterWaitingOnPlayers()
    {
        waitingMenu.Show(true);
    }

    void EnterVotingForMap()
    {
        votingMenu.Show(true);


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
			votesSelectedMap.SetScale(scale);
			votesSelectedMap.SetMapPos(map_pos);

//TEMP
		//votesSelectedMap.SetScale(1);
		//votesSelectedMap.SetMapPos(GetDayZGame().GetPlayer().GetPosition());
    }

    void UpdatePlayerVotesText()
    {
        //Print("[UpdateplayerCountText]: " + DayZGame.gunGameconfig.MinPlayers.ToString());
        playerCountText.SetText(ClientData.m_PlayerBaseList.Count().ToString() + " / " + DayZGame.gunGameconfig.MinPlayers.ToString());
    }

    void UpdateplayerCountText()
    {
        //Print("[UpdateplayerCountText]: " + DayZGame.gunGameconfig.MinPlayers.ToString());
        playerCountText.SetText(ClientData.m_PlayerBaseList.Count().ToString() + " / " + DayZGame.gunGameconfig.MinPlayers.ToString());
    }
}