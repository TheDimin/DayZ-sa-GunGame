/**@class	GunGameEventBase
 * @brief	represents event that triggers transition from state to state
 **/
class GunGameEventBase
{
};

class EnoughPlayersReadyEvent : GunGameEventBase
{
}

class MapVoteEndedEvent : GunGameEventBase
{
    int targetMap = -1;

    void MapVoteEndedEvent (ref array<int> votes) 
    {
        int mostVotes = -1;
        Print("Constructor called with vote index count:: " + votes.Count().ToString());
        for (int i = 0; i < votes.Count(); i++)
        {
            Print("Votes for map '" + i.ToString() + "' ::" + votes[i].ToString());
            if(votes[i] > mostVotes)
            {
                mostVotes = votes[i];
                targetMap = i;
            }
        }
    }
}