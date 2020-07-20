typedef FSMTransition<GunGameStateBase, GunGameEventBase, GunGameActionBase, GGGuardBase> GunGameTransition;

class GunGameFSM : FSMBase<GunGameStateBase, GunGameEventBase, GunGameActionBase, GGGuardBase>
{
    //protected ref GunGameStateBase m_state; /// current fsm state
	//protected ref GunGameStateBase m_initialState; /// configurable initial state of the machine
	//protected ref GunGameEventBase m_initialEvent; /// configurable initial event to start the machine (null by default)
	//protected ref array<ref FSMTransition<GunGameStateBase, GunGameEventBase, GunGameActionBase, GGGuardBase>> m_transitions; /// fsm transition table

	override void SetInitialState (GunGameStateBase initial_state)
	{
		super.SetInitialState(initial_state);
        initial_state.SetFsmRef(this);
	}

    override void AddTransition (GunGameTransition t)
	{
		super.AddTransition(t);
        t.m_dstState.SetFsmRef(this);
	}

	override ProcessEventResult ProcessLocalTransition (GunGameTransition t, GunGameEventBase e)
	{
		if(super.ProcessLocalTransition(t,e) == ProcessEventResult.FSM_OK)
		{
			GetRPCManager().SendRPC( "GunGame", "RpcOnStateChange", new Param1< int >( m_state.GetStateId() ), true );
			return ProcessEventResult.FSM_OK;
		}

		return ProcessEventResult.FSM_TERMINATED;
	}
}