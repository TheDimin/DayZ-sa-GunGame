modded class ModifiersManager
{
    override void Init()
    {
        AddModifier(new BloodRegenMdfr);
		//AddModifier(new BoneRegen);
		//AddModifier(new Health);
		//AddModifier(new SalineMdfr);
		AddModifier(new HealthRegenMdfr);
		//AddModifier(new HungerMdfr);
		//AddModifier(new Shock);
		AddModifier(new ImmuneSystemMdfr); //We could disable all diseases with this, BUT what are the brain &wound agents.
		//AddModifier(new StomachMdfr); //procces food eaten by the player
		//AddModifier(new HeatComfortMdfr);
		//AddModifier(new ThirstMdfr);
		AddModifier(new BleedingCheckMdfr); //This will kill the player if its below the threshold
		//AddModifier(new Blinded);
		//AddModifier(new BrokenArms);
		//AddModifier(new BrokenLegs);
		//AddModifier(new VomitStuffedMdfr);
		//AddModifier(new BurningMdfr);
		//AddModifier(new FeverMdfr);
		AddModifier(new HeartAttackMdfr);
		//AddModifier(new HemolyticReactionMdfr); //blood transfusion from bad blood type reaction
		//AddModifier(new PoisoningMdfr);
		AddModifier(new StuffedStomachMdfr);
		//AddModifier(new Tremor);
		//AddModifier(new UnconsciousnessMdfr);
		//AddModifier(new ShockDamageMdfr);
		//AddModifier(new CommonColdMdfr);
		//AddModifier(new CholeraMdfr);
		//AddModifier(new InfluenzaMdfr);
		//AddModifier(new SalmonellaMdfr);
		//AddModifier(new BrainDiseaseMdfr);
	    //AddModifier(new WetMdfr); //only responsible for the uipart.
		//AddModifier(new ImmunityBoost);
		//AddModifier(new AntibioticsMdfr);
		//AddModifier(new ToxicityMdfr);
		//AddModifier(new BreathVapourMdfr);
		//AddModifier(new ShockMdfr);
		//AddModifier(new WoundInfectionMdfr);
		//AddModifier(new CharcoalMdfr);
		//AddModifier(new MorphineMdfr);
		//AddModifier(new PainKillersMdfr);
		//AddModifier(new EpinephrineMdfr);
    }

    //if we cause a lot of nullptr errors to disables systems we can fix it by modding those get functions
    //but lets do that if that happens
    // (not Sure how enforce script deals with nullptr objects)
}