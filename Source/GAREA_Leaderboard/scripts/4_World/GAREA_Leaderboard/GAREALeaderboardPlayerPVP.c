class GAREALeaderboardPlayerPVP : RestCallback
{
    string playerId = "";
    string playerName = "";
	bool playerIsOnline;
	
	// Time in seconds
	float surviedTime;
	
	// PVP
	int playerKills;
    int playerDeaths;
	int playerLongestDistance;	
	
	void GAREALeaderboardPlayerPVP(GAREALeaderboardPlayer p)
	{
		this.playerId = p.playerId;
		this.playerName = p.playerName;
		this.playerIsOnline = p.playerIsOnline;
		this.surviedTime = p.surviedTime;
		
		this.playerKills = p.playerKills;
		this.playerDeaths = p.playerDeaths;
		this.playerLongestDistance = p.playerLongestDistance;
	}
	
	float GetKD()
	{
		if (playerKills == 0)
		{
			return 0;
		}

		if (playerDeaths > 0)
		{
			float kd = (((float) playerKills) / ((float) playerDeaths));
			kd *= 10;
			kd = Math.Round(kd);
			kd /= 10;
		}
		else
		{
			kd = playerKills;
		}
		return kd;
	}
	
	int GetPVPPoints()
	{
		int points = 0;
		points += playerKills * 100;
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