typedef Param1<array<MapVoteInfo>> MapsVoteInfoParam;
///Information about a specific map that will be replicated to clients
class MapVoteInfo : Managed
{
    string name = "null";
    vector location = "0 0 0";
    int count = 0;

    void MapVoteInfo(string Name, vector Location,int Count)
    {
        name = Name;
        location = Location;
        count = Count;
    }
}

/// Widget element representing a map that can be voted for
class MapVoteEntry extends ScriptedWidgetEventHandler
{
    protected ref Widget root;

    protected ref TextWidget displayName;
    protected ref TextWidget displayCount;

    protected ref MapVoteInfo M_Data;

    protected ref IngameHud M_Owner;

    void MapVoteEntry( Widget parent,IngameHud owner, MapVoteInfo data )
	{
        M_Data = data;
        M_Owner = owner;
        
        root = GetGame().GetWorkspace().CreateWidgets( "GunGame/gui/layouts/Elements/MapVoteInfo.layout", parent );

        displayName = TextWidget.Cast(root.FindAnyWidget("VoteName"));
        displayCount = TextWidget.Cast(root.FindAnyWidget("VoteCount"));
        
        displayName.SetText(M_Data.name);
        displayCount.SetText(M_Data.count.ToString());

        root.SetHandler( this );
    }



    override bool OnClick( Widget w, int x, int y, int button )
	{
        Print("OnClick called");
        if(w == root)
        {
            Print("Widget was clicked");
            return false;
        }
        return false;
    }

    bool OnUpdate(Widget w)
    {
        Print("BullshitUpdate Called");
        return false;
    }

    bool OnFocus(Widget w, int x, int y)
    {
        if(w == root)
        {
            Focus();
        }

        return false;
    }

    void Focus()
    {
        M_Owner.SetVotingMapPos(M_Data);
    }

    override bool OnDoubleClick( Widget w, int x, int y, int button )
	{
        return false;
    }

    override bool OnSelect(Widget w, int x, int y)
    {
        return false;
    }
}