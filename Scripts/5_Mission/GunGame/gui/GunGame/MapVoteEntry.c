/// Widget element representing a map that can be voted for
class MapVoteEntry extends ScriptedWidgetEventHandler
{
    ref Widget root;

    protected ref TextWidget displayName;
    protected ref TextWidget displayCount;

    protected ref MapVoteInfo M_Data;

    protected ref GunGameHud M_Owner;
    protected int M_Index;


    void OnWidgetScriptInit(Widget layoutRoot)
	{
        root = layoutRoot;
        
        root.SetHandler( this );

        displayName = TextWidget.Cast(root.FindAnyWidget("VoteName"));
        displayCount = TextWidget.Cast(root.FindAnyWidget("VoteCount"));
    }

    void SetData(GunGameHud owner,MapVoteInfo data,int index )
    {
        M_Data = data;
        M_Owner = owner;
        M_Index = index;

        displayName.SetText(M_Data.name);
        displayCount.SetText(M_Data.count.ToString());
    }
     
    override bool OnDoubleClick(Widget w, int x, int y, int button)
    {
        if(w == root)
        {//void SendRPC( string modName, string funcName, ref Param params = NULL, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
            GetRPCManager().SendRPC("GunGame","SRpcVoteForMap",new Param1<int>(M_Index),true,null,GetGame().GetPlayer());
            root.SetColor(Colors.GREEN);
        }
        Print("OnDubbleClickCalled");
        return false;
    }

    override bool OnFocus(Widget w, int x, int y)
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
}