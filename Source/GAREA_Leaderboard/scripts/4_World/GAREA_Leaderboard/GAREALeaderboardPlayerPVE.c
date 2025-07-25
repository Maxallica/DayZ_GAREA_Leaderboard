class GAREALeaderboardPlayerPVE : RestCallback
{
	string playerId = "";
    string playerName = "";
	int playerDeaths;
	bool playerIsOnline;
	
	// Time in seconds
	float surviedTime;
	
	// PVE
	int playerKillsAISurvivor;
	int playerKillsZombie;
	int playerKillsBear;
	int playerKillsWolf;
	int playerKillsWildBoar;
	int playerKillsRedDeer;
	int playerKillsRoeDeer;	
	int playerKillsSheep;
	int playerKillsGoat;
	int playerKillsCow;
	int playerKillsPig;		
	int playerKillsChicken;
	
	int playerKillsAnimals;
	int playerKillsNPCs;
	
	void GAREALeaderboardPlayerPVE(GAREALeaderboardPlayer p)
	{
		this.playerId = p.playerId;
		this.playerName = p.playerName;
		this.playerDeaths = p.playerDeaths;
		this.playerIsOnline = p.playerIsOnline;
		this.surviedTime = p.surviedTime;
		
		this.playerKillsAISurvivor = p.playerKillsAISurvivor;
		this.playerKillsZombie = p.playerKillsZombie;
		this.playerKillsBear = p.playerKillsBear;
		this.playerKillsWolf = p.playerKillsWolf;
		this.playerKillsWildBoar = p.playerKillsWildBoar;
		this.playerKillsRedDeer = p.playerKillsRedDeer;
		this.playerKillsRoeDeer = p.playerKillsRoeDeer;
		this.playerKillsSheep = p.playerKillsSheep;
		this.playerKillsGoat = p.playerKillsGoat;
		this.playerKillsCow = p.playerKillsCow;
		this.playerKillsPig = p.playerKillsPig;
		this.playerKillsChicken = p.playerKillsChicken;
		
		this.playerKillsAnimals = p.playerKillsAnimals;
		this.playerKillsNPCs = p.playerKillsNPCs;
	}	
	
	int GetPVEPoints()
	{
		int points = 0;
		points += playerKillsNPCs * 10;
		points -= playerDeaths;
		return points;
	}
	
	string GetSurvivedTimeAsString(GAREALeaderboardConfig gareaLeaderboardConfig = null)
	{		
		int hours = surviedTime / 3600;
		int minitues = (((int) surviedTime) % 3600) / 60;
		
		if (gareaLeaderboardConfig.tShortHour && gareaLeaderboardConfig.tShortMinute)
		{
			return "" + hours + gareaLeaderboardConfig.tShortHour + " " + minitues + gareaLeaderboardConfig.tShortMinute; 
		}
		else
		{
			return "" + hours + "h" + " " + minitues + "min"; 
		}
	}
}