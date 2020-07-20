modded class MissionBase
{
    override void OnInit()
    {
        super.OnInit();
        GetRPCManager().AddRPC("GunGame","RpcLoadData",GetGame(),SingeplayerExecutionType.Client);

        GetRPCManager().AddRPC("GunGame","RpcOnStateChange",GetGame(),SingeplayerExecutionType.Client);
    }
}