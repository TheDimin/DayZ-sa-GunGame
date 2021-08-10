modded class MissionBase
{
    override void OnInit()
    {
        super.OnInit();
        GetRPCManager().AddRPC("GunGame","RpcLoadData",GetGame(),SingeplayerExecutionType.Client);
        //Print("[CHECK] COnfig value: "+DayZGame.gunGameconfig.mapVoteInfo[0].name );
        GetRPCManager().AddRPC("GunGame","RpcOnStateChange",GetGame(),SingeplayerExecutionType.Client);
    }
}