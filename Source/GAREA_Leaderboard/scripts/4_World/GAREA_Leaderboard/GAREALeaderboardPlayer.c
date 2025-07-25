class GAREALeaderboardPlayer : RestCallback
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
	
    void GAREALeaderboardPlayer(string playerId = "", string playerName = "")
    {
		this.playerId = playerId;
		this.playerName = playerName;
		Save(false);
    }
	
	static GAREALeaderboardPlayer LoadNewInstanceFromFile(string filePath)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = new GAREALeaderboardPlayer();
			JsonFileLoader<GAREALeaderboardPlayer>.JsonLoadFile(filePath, gareaLeaderboardPlayer);
			if (gareaLeaderboardPlayer.playerId != "")
			{	
				return gareaLeaderboardPlayer;
			}        	
		}
		return null;
	}

	void Reset(bool resetPVP = true, bool resetPVE = true, bool resetGeneral = true)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{	
			// PVP
			if (resetPVP)
			{
				this.playerKills = 0;
				this.playerLongestDistance = 0;
			}
			
			// PVE
			if (resetPVE)
			{
				this.playerKillsAISurvivor = 0;
				this.playerKillsZombie = 0;
				this.playerKillsBear = 0;
				this.playerKillsWolf = 0;
				this.playerKillsWildBoar = 0;
				this.playerKillsRedDeer = 0;
				this.playerKillsRoeDeer = 0;
				this.playerKillsSheep = 0;
				this.playerKillsGoat = 0;
				this.playerKillsCow = 0;
				this.playerKillsPig = 0;
				this.playerKillsChicken = 0;
				
				this.playerKillsAnimals = 0;
				this.playerKillsNPCs = 0;
			}			
			
			if (resetGeneral)
			{
				this.playerDeaths = 0;
				UpdateSurvivedTime(-1);
			}
		}	
	}
	
	void Save(bool forceSave = true)
	{
		if (playerId != "")
		{
			string filePath = GAREALeaderboard_PlayerDB + "\\" + playerId + ".json";
			if (GetGame().IsServer() || !GetGame().IsMultiplayer())
			{
				if (forceSave)
				{
					JsonFileLoader<GAREALeaderboardPlayer>.JsonSaveFile(filePath, this);
				}
				else
				{
					if (!FileExist(filePath))
	        		{
						JsonFileLoader<GAREALeaderboardPlayer>.JsonSaveFile(filePath, this);
			        }
				}
			}
		}		
	}
	
	bool Delete()
	{
		bool retVal = false;
		if (playerId != "")
		{
			string filePath = GAREALeaderboard_PlayerDB + "\\" + playerId + ".json";
			if (GetGame().IsServer() || !GetGame().IsMultiplayer())
			{
				if (FileExist(filePath))
				{
					retVal = DeleteFile(filePath);
				}
			}
		}		
		return retVal;
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
	
	int GetPVEPoints()
	{
		int points = 0;
		points += playerKillsNPCs * 10;
		points -= playerDeaths;
		return points;
	}
	
	void UpdatePVEStats(GAREALeaderboardConfig gareaLeaderboardConfig)
	{
		int npcKills = 0;
		if (!gareaLeaderboardConfig || !gareaLeaderboardConfig.disableKillOfZombie)
		{
			npcKills += playerKillsZombie;
		}
		string includeAISurvivorFor = "";
		if (gareaLeaderboardConfig)
		{
			includeAISurvivorFor = gareaLeaderboardConfig.includeAISurvivorFor;
		}
		string includeAISurvivorForPVE = "pve";
		string includeAISurvivorForBOTH = "both";
		if (!gareaLeaderboardConfig || includeAISurvivorFor == includeAISurvivorForPVE || includeAISurvivorFor == includeAISurvivorForBOTH)
		{
			npcKills += playerKillsAISurvivor;
		}
		
		int animalKills = 0;
		if (!gareaLeaderboardConfig || !gareaLeaderboardConfig.disableKillOfAnimal)
        {    
            animalKills += playerKillsBear;
            animalKills += playerKillsWolf;
            animalKills += playerKillsWildBoar;
            animalKills += playerKillsRoeDeer;
            animalKills += playerKillsRedDeer;
            animalKills += playerKillsSheep;
            animalKills += playerKillsGoat;
            animalKills += playerKillsCow;
            animalKills += playerKillsPig;
            animalKills += playerKillsChicken;
		}
		playerKillsAnimals = animalKills;
				
		npcKills += playerKillsAnimals;
		playerKillsNPCs = npcKills;
	}
	
	void Update(GAREALeaderboardPlayer p)
	{
		this.playerDeaths = p.playerDeaths;
		UpdateSurvivedTime(p.surviedTime);
		
		// PVP
		this.playerKills = p.playerKills;
		this.playerLongestDistance = p.playerLongestDistance;
		
		// PVE
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
	
	void ReloadSurvivedTime()
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			array<Man> mans = new array<Man>;
			GetGame().GetPlayers(mans);
			
			for (int i = 0; i < mans.Count(); i++)
			{
				Man man = mans[i];
				if (man)
				{
					PlayerBase playerBase = PlayerBase.Cast(man);
					if (playerBase)
					{
						PlayerIdentity identity = playerBase.GetIdentity();
						if (identity)
						{
							if (identity.GetPlainId() == playerId)
							{
								surviedTime = playerBase.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
								break;							
							}
						}
					}
				}
			}
		}
	}
	
	void UpdateSurvivedTime(float time)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			array<Man> mans = new array<Man>;
			GetGame().GetPlayers(mans);
			
			for (int i = 0; i < mans.Count(); i++)
			{
				Man man = mans[i];
				if (man)
				{
					PlayerBase playerBase = PlayerBase.Cast(man);
					if (playerBase)
					{
						PlayerIdentity identity = playerBase.GetIdentity();
						if (identity)
						{
							if (identity.GetPlainId() == playerId)
							{
								surviedTime = playerBase.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
								// opposite_playtime will reset the playtime
								float opposite_playtime = surviedTime * (-1);
								
								if (time <= -1)
								{
									playerBase.StatUpdate(AnalyticsManagerServer.STAT_PLAYTIME, opposite_playtime);
								}
								else
								{
									playerBase.StatUpdate(AnalyticsManagerServer.STAT_PLAYTIME, opposite_playtime);
									surviedTime = playerBase.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
									
									playerBase.StatUpdate(AnalyticsManagerServer.STAT_PLAYTIME, (surviedTime + time));									
								}
								
								playerBase.StatSyncToClient();
								surviedTime = playerBase.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
								break;							
							}
						}
					}
				}
			}
		}
	}
	
	GAREALeaderboardPlayerPVP GetPVP()
	{
		ReloadSurvivedTime();
		return new GAREALeaderboardPlayerPVP(this);
	}
	
	GAREALeaderboardPlayerPVE GetPVE()
	{
		ReloadSurvivedTime();
		return new GAREALeaderboardPlayerPVE(this);
	}
	
	GAREALeaderboardPlayerKey GetPlayerKey()
	{
		return new GAREALeaderboardPlayerKey(this);
	}
}