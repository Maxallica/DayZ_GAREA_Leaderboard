class CfgPatches
{
	class GAREA_Leaderboard
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
	class GAREA_Leaderboard
	{
		type = "mod";
		dir="GAREA_Leaderboard";
		name="GAREA_Leaderboard";
		tooltip="GAREA Leaderboard Mod";
		overview="GAREA Leaderboard";		
		author="GAREA";
		action="https://www.yourgamearea.de/";		
		picture="GAREA_Leaderboard/data/logo.paa";
		logoSmall="GAREA_Leaderboard/data/logo.paa";
		logo="GAREA_Leaderboard/data/logo.paa";
		logoOver="GAREA_Leaderboard/data/logo.paa";		
		inputs="GAREA_Leaderboard/data/modded_inputs.xml";
		hideName=0;
		hidePicture=0;
		version="1.5";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"GAREA_Leaderboard/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"GAREA_Leaderboard/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"GAREA_Leaderboard/scripts/5_Mission"
				};
			};
		};
	};
};