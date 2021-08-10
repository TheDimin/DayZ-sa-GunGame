class WeaponHelpers
{
    //Can happen async so we cannot return the weapon
    static void SetWeapon(DayZPlayer _Player,string _Weapon,string _magName,array<string> _attachments)
    {
        auto humanInventory = _Player.GetHumanInventory();
		if(humanInventory.GetEntityInHands() != null)
		{
			_Player.ServerReplaceItemWithNew(new ReplaceWeaponInHands(humanInventory.GetEntityInHands(),_Weapon,_magName,_attachments));
			
		}
		else
		{
			Print("Creating weapon named::" + _Weapon);
        	auto weapon = Weapon_Base.Cast(humanInventory.CreateInHands( _Weapon ));

			if(weapon == null)
			{
				Print("Failed creation of weapon in hands");
				return;
			}

			AddMag(weapon,_magName);
			AddAttachments(weapon,_attachments);
		}
    }

    static void AddMag(Weapon_Base _Weapon,string _Mag)
    {
        //the magic that made autoloading possible https://feedback.bistudio.com/T149240
        int stateId = -1;

	    if ( _Weapon.IsInherited( SKS_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( BoltActionRifle_InnerMagazine_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( DoubleBarrel_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( Pistol_Base ) )
	    {
	    	stateId = PistolStableStateID.CLO_DIS_BU0_MA1;
	    } else if ( _Weapon.IsInherited( CZ527_Base ) )
	    {
	    	stateId = CZ527StableStateID.CZ527_CLO_BU0_MA1;
	    } else if ( _Weapon.IsInherited( Repeater_Base ) )
	    {
	    	return;
	    } else if ( _Weapon.IsInherited( RifleBoltFree_Base ) )
	    {
	    	stateId = RBFStableStateID.RBF_CLO_BU0_MA1;
	    } else if ( _Weapon.IsInherited( RifleBoltLock_Base ) )
	    {
	    	stateId = RBLStableStateID.RBL_OPN_BU0_MA1;
	    } else if ( _Weapon.IsInherited( Mp133Shotgun_Base ) )
	    {
	    	return;
	    }

        EntityAI mag = EntityAI.Cast(_Weapon.GetInventory().CreateAttachment(_Mag));

	    GetGame().RemoteObjectDelete( mag );
	    GetGame().RemoteObjectDelete( _Weapon );
		_Weapon.AttachMagazine(_Weapon.GetCurrentMuzzle(),Magazine.Cast(mag));

	    pushToChamberFromAttachedMagazine( _Weapon, _Weapon.GetCurrentMuzzle() );

	     ScriptReadWriteContext ctx = new ScriptReadWriteContext;
	     ctx.GetWriteContext().Write( stateId );
	    _Weapon.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );

	    GetGame().RemoteObjectCreate( _Weapon );
	    GetGame().RemoteObjectCreate( mag );
		_Weapon.SyncSelectionState(true,true);
		
    }
	
    //NOTE This doesn't work for mags call other function for those
    static void AddAttachments(Weapon_Base _Weapon,array<string> _Attachments)
    {
        foreach(string _AttachmentName : _Attachments)
		{
			_Weapon.GetInventory().CreateAttachment(_AttachmentName);
            //TODO If attachment needs battery ect we need to add it to the attachment
		}

		ItemOptics optic = _Weapon.GetAttachedOptics();
		if( !optic )
			return;
		//bypass energysystem
		optic.ShowReddot(true);
		
    }
}

class ReplaceWeaponInHands : ReplaceItemWithNewLambdaBase
{
    array<string> m_Attachments;
    string m_magName;

    void ReplaceWeaponInHands (EntityAI old_item,string new_item_type,string _magName,array<string> _attachments)
	{
		m_OldItem = old_item;
		m_NewItemType = new_item_type;
        m_magName = _magName;
        m_Attachments = _attachments;
	}

    override void OnSuccess (EntityAI new_item)
	{
		Print("SetweaponInHandsLambda OnSucces");
		Weapon_Base weapon = Weapon_Base.Cast(new_item);
        if(weapon == null)
        {
            Print("Item is not a weapon");
            return;
        }

        WeaponHelpers.AddMag(weapon,m_magName);
        WeaponHelpers.AddAttachments(weapon,m_Attachments);
	}
}