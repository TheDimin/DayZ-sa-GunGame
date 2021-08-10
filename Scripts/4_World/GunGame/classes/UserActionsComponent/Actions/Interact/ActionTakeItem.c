modded class ActionTakeItem
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        return false; //No Item collection
    }
}