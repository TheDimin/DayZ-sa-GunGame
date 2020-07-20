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
    int targetMap = 0;

    void MapVoteEndedEvent (array<int> votes) 
    {
        int mostVotes = -1;

        for (int i = 0; i < votes.Count(); i++)
        {
            if(votes[i] > mostVotes)
            {
                mostVotes = votes[i];
                targetMap = i;
            }
        }
    }
}