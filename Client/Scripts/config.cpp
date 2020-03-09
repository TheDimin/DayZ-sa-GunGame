class CfgPatches
{
	class GunGame_scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class GunGame
	{
		
		dir = "GunGame";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "GunGame";
		credits = "0";
		author = "TheDimin";
		authorID = "0"; 
		version = "0.01"; 
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{	
			class gameScriptModule
			{
				value = "";
				files[] = {"GunGame/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"GunGame/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"GunGame/Scripts/5_Mission"};
			};
		};
	};
};