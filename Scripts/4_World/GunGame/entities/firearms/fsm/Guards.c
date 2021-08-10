modded class WeaponGuardCanSwapMag
{
    //MODDED: Removed the check of new_mag == current_mag
	override bool GuardCondition (WeaponEventBase e)
	{
		int mi = m_weapon.GetCurrentMuzzle();
		Magazine attached_mag = m_weapon.GetMagazine(mi);
		if (m_weapon && e.m_magazine /*&& m_weapon.CanSwapMagazine(mi, e.m_magazine)*/)
		{
			wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " guard - can swap magazine");
			return true;
		}
		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " guard - cannot swap magazine");
		return false;
	}
};
