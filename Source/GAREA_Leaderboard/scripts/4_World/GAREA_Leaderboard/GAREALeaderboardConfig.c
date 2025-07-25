class GAREALeaderboardConfig : RestCallback
{	
    protected static ref GAREALeaderboardConfig Instance;
	
	// Styling
	int playerDisplaySize = 10;
	string dateTimeFormat = "%1.%2.%3 %4:%5:%6";
	
	// Admin
	ref array<string> adminIds = new array<string>();
	
	// Options
	bool disableDeathBySuicide = false;
	bool disableDeathByGrenade = false;
	bool disableDeathByTrap = false;
	bool disableDeathByZombie = false;
	bool disableDeathByAnimal = false;
	bool disableDeathByCar = false;
	bool disableDeathByWeapon = false;
	bool disableDeathByUnarmed = false;
	bool disableDeathByUnknown = false;
	
	bool disableKillOfGrenade = false;
	bool disableKillOfTrap = false;
	bool disableKillOfAnimal = false;
	bool disableKillOfZombie = false;
	bool disableKillOfCar = false;
	bool disableKillOfWeapon = false;
	bool disableKillOfUnarmed = false;
	bool disableKillOfUnknown = false;
	bool disableKillOfUnconsciousSuicide = false;
	
	string includeAISurvivorFor = "pve";
	string resetPlayerBeforeLoginFor = "none";
	string resetPlayerAfterLogoutFor = "none";
	string showSurvivedTimeFor = "all";
	bool showOnlyOnlinePlayersInTopXList = false;
	
	bool disablePVPLeaderboard = false;
	bool disablePVELeaderboard = false;	
	
	// Translations
	string tTitle = "GAREA Leaderboard";
	string thPlayerName = "Player";
	string thPlayerPos = "Pos";
	string thPlayerKills = "Kills";	
	string thPlayerDeaths = "Deaths";
	string thPlayerKD = "K/D";	
	string thPlayerLongestDistance = "Longest Distance";
	string thPlayerSurvivedTime = "Survived Time";
	
	string thPlayerKillsAISurvivor = "AI Survivors";
	string thPlayerKillsZombie = "Zombies";
	string thPlayerKillsAnimal = "Animals";
	string thBears = "Bears";
	string thWolves = "Wolves";
	string thWildBoars = "Wild boars";
	string thRedDeers = "Red deers";
	string thRoeDeers = "Roe deers";
	string thSheeps = "Sheeps";
	string thGoats = "Goats";
	string thCows = "Cows";
	string thPigs = "Pigs";
	string thChicken = "Chicken";
	string thKillsNPCTotal= "Total";
	
	string thPlayerPoints = "Points";
	
	string tShortMinute = "min";
	string tShortHour = "h";
	
	// Info
	string updateTimestampPVP;
	string updateTimestampPVE;
	
    void GAREALeaderboardConfig()
    {
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{	
			// Info			
			string currenTimestamp = GAREALeaderboardUtils.GetTimestamp();
			updateTimestampPVP = currenTimestamp;
			updateTimestampPVE = currenTimestamp;
			
       		if (!FileExist(GAREALeaderboard_Config))
       		{	
				Save();
	        }
		}
    }

	static GAREALeaderboardConfig GetInstance(bool reload = false)
	{
		if (!Instance)
        {
            Instance = new GAREALeaderboardConfig();
        }
		
		if (reload)
		{
			Reload();
		}		
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}
	
	void Save(bool forceSave = true)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if (forceSave)
			{
				JsonFileLoader<GAREALeaderboardConfig>.JsonSaveFile(GAREALeaderboard_Config, this);
			}
			else
			{
				if (!FileExist(GAREALeaderboard_Config))
        		{
					JsonFileLoader<GAREALeaderboardConfig>.JsonSaveFile(GAREALeaderboard_Config, this);
		        }
			}
		}
	}
	
	static void Reload()
	{
		if (Instance && FileExist(GAREALeaderboard_Config))
        {
			JsonFileLoader<GAREALeaderboardConfig>.JsonLoadFile(GAREALeaderboard_Config, Instance);
			if (Instance.playerDisplaySize > 100)
			{
				Instance.playerDisplaySize = 100;
			}
		}
	}
	
	void UpdateUpdateTimestampPVP(string updateTimestampPVP = "", bool saveImmediately = true, bool reloadConfig = false)
	{
		if (updateTimestampPVP == "")
		{
			if (reloadConfig)
			{
				Reload();
			}			
			updateTimestampPVP = GAREALeaderboardUtils.GetTimestamp(dateTimeFormat);
		}
		this.updateTimestampPVP = updateTimestampPVP;
		
		if (saveImmediately)
		{
			Save();
		}		
	}
	
	void UpdateUpdateTimestampPVE(string updateTimestampPVE = "", bool saveImmediately = true, bool reloadConfig = false)
	{
		if (updateTimestampPVE == "")
		{
			if (reloadConfig)
			{
				Reload();
			}
			updateTimestampPVE = GAREALeaderboardUtils.GetTimestamp(dateTimeFormat);
		}
		this.updateTimestampPVE = updateTimestampPVE;
		
		if (saveImmediately)
		{
			Save();
		}
	}
}