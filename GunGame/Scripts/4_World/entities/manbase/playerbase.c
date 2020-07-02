modded class PlayerBase
{
    override void EEKilled( Object killer )
	{
        super.EEKilled(killer);
    }

    override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
        super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);

        UAInput killInput = GetUApi().GetInputByName("UAScriptedInput1");

        if(killInput.LocalValue() != 0 )
        {
            Print("ButtonPressed?");
        }
    }

#ifndef GG_Debug
    override bool IsInventoryVisible()
	{
		return false;
	}

    bool CanManipulateInventory()
	{
         return false;
	}
#endif
}