class CfgPatches
{
	class GunGame
	{
		units[] = {};
		weapons[] = {};
		//requiredVersion=0.1;
		requiredAddons[] =
		{
			"JM_CF_Scripts",
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class GunGame
	{
		type = "mod";

		name = "Gun Game";
		tooltip = "Gun Game for dayz";
		overview = "Custom gun game mode for dayz";
		action = "https://github.com/TheDimin";
		author = "TheDimin";
		version = "0.01";

		dependencies[] = { "Game", "World", "Mission" };

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = 
				{ 
					"GunGame/Scripts/Definitions",
					"GunGame/Temp/3_Game",
					"GunGame/Scripts/3_Game" 
				};
			};

			class worldScriptModule
			{
				value = "";
				files[] = 
				{
					"GunGame/Scripts/Definitions",
					"GunGame/Temp/4_World",
					"GunGame/Scripts/4_World" 
				};
			};

			class missionScriptModule
			{
				value = "";
				files[] = 
				{ 
					"GunGame/Scripts/Definitions",
					"GunGame/Temp/5_Mission",
					"GunGame/Scripts/5_Mission"
				};
			};
			class blueprintScriptModule
			{
				value = "";
				files[] =
				{
					"C:/Users/DPHoo/Documents/DayZ Other Profiles/Temp",
				
				};
			}
		};
	};
};