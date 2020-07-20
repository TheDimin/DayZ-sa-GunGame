/**@class	GunGameGuardBase
 * @brief	represents guard on a transition from state to state
 **/
class GGGuardBase
{
	/**@fn		GuardCondition
	 * @brief enable or disable transition based on condition
	 * the guard is a boolean operation executed first and which can prevent the transition from firing by returning false
	 * @return	true if transition is allowed
	 **/
	bool GuardCondition (GunGameEventBase e) { return true; }
};