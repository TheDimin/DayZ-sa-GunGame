modded class SyncEvents
{
    static ref ScriptInvoker EventOnPlayerKilledByPlayer = new ScriptInvoker();

    static ScriptInvoker GetEventOnPlayerKilledByPlayer()
    {
        return EventOnPlayerKilledByPlayer;
    }
}