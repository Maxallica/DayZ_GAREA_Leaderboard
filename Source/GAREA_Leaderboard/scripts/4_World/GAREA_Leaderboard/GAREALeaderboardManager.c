class GAREALeaderboardManager
{
	// GAREALeaderboardManager will be only used by server side
	
    protected static ref GAREALeaderboardManager Instance;
    private ref array<GAREALeaderboardPlayer> gareaLeaderboardPlayers;

    void GAREALeaderboardManager()
    {
		gareaLeaderboardPlayers = new ref array<GAREALeaderboardPlayer>;		
    }

    void ~GAREALeaderboardManager()
    {
    }

    static GAREALeaderboardManager GetInstance()
	{
		if (!Instance)
        {
            Instance = new GAREALeaderboardManager();
        }
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}
	
    void OnPlayerConnect(PlayerBase player)
	{
		PlayerIdentity identity = player.GetIdentity();
		if (identity)
		{
			float playtime = player.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
			
			string playerName = identity.GetName();			
			string playerId = identity.GetPlainId();
			
			bool newPlayer = false;
			GAREALeaderboardPlayer gareaLeaderboardPlayer = GetOrCreatePlayer(playerId, playerName, newPlayer);			
			if (!newPlayer)
			{
				gareaLeaderboardPlayer.playerIsOnline = true;
				
				bool saveImmediately = false;
				GAREALeaderboardConfig gareaLeaderboardConfig = GAREALeaderboardConfig.GetInstance();
				if (gareaLeaderboardConfig.resetPlayerBeforeLoginFor == "pvp" || gareaLeaderboardConfig.resetPlayerBeforeLoginFor == "both")
				{
					ResetPlayer(gareaLeaderboardPlayer, "", "", true, false, true, saveImmediately);
				}
				
				if (gareaLeaderboardConfig.resetPlayerBeforeLoginFor == "pve" || gareaLeaderboardConfig.resetPlayerBeforeLoginFor == "both")
				{
					ResetPlayer(gareaLeaderboardPlayer, "", "", false, true, true, saveImmediately);
				}
			}
		}
	}
	
	void OnPlayerDisconnect(string playerId)
	{
		if (playerId)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = GetOrCreatePlayer(playerId);
			if (gareaLeaderboardPlayer)
			{
				gareaLeaderboardPlayer.playerIsOnline = false;
			
				bool saveImmediately = false;
				GAREALeaderboardConfig gareaLeaderboardConfig = GAREALeaderboardConfig.GetInstance();
				if (gareaLeaderboardConfig.resetPlayerAfterLogoutFor == "pvp" || gareaLeaderboardConfig.resetPlayerAfterLogoutFor == "both")
				{
					ResetPlayer(gareaLeaderboardPlayer, "", "", true, false, true, saveImmediately);
				}
				
				if (gareaLeaderboardConfig.resetPlayerAfterLogoutFor == "pve" || gareaLeaderboardConfig.resetPlayerAfterLogoutFor == "both")
				{
					ResetPlayer(gareaLeaderboardPlayer, "", "", false, true, true, saveImmediately);
				}
				gareaLeaderboardPlayer.Save();
			}
		}
	}
	
	void UpdatePlayerStats(Object target, Object source)
	{
		if (target && source)
		{
			GAREALeaderboardConfig gareaLeaderboardConfig = GAREALeaderboardConfig.GetInstance();
			bool updateTimestampPVP;
			bool updateTimestampPVE;
			
			string targetType;
			string sourceType;
			string targetId;
			string sourceId;
			string targetName;
			string sourceName;
			float distance;
			
			GAREALeaderboardObjectUtils.GetRelevantData(target, source, targetType, sourceType, targetId, sourceId, targetName, sourceName, distance);
			
			// Update GAREALeaderboardPlayer
			if (targetId)
			{
				bool disableDeath;
				disableDeath = disableDeath || (sourceType == "Suicide" && gareaLeaderboardConfig.disableDeathBySuicide);
				disableDeath = disableDeath || (sourceType == "Grenade" && gareaLeaderboardConfig.disableDeathByGrenade);
				disableDeath = disableDeath || (sourceType == "Trap" && gareaLeaderboardConfig.disableDeathByTrap);
				disableDeath = disableDeath || (sourceType == "Zombie" && gareaLeaderboardConfig.disableDeathByZombie);
				disableDeath = disableDeath || (sourceType == "Animal" && gareaLeaderboardConfig.disableDeathByAnimal);
				disableDeath = disableDeath || (sourceType == "Car" && gareaLeaderboardConfig.disableDeathByCar);
				disableDeath = disableDeath || (sourceType == "Weapon" && gareaLeaderboardConfig.disableDeathByWeapon);
				disableDeath = disableDeath || (sourceType == "Unarmed" && gareaLeaderboardConfig.disableDeathByUnarmed);
				disableDeath = disableDeath || (sourceType == "Unknown" && gareaLeaderboardConfig.disableDeathByUnknown);
				
				if (!disableDeath)
				{
					GAREALeaderboardPlayer playerWhoDied = GetOrCreatePlayer(targetId, targetName);
					if (playerWhoDied)
					{
						// Death				
						playerWhoDied.playerDeaths += 1;
						playerWhoDied.Save();
						updateTimestampPVP = true;
						updateTimestampPVE = true;
					}
				}
			}			
			
			if (targetId != sourceId)
			{
				bool disableKill;
				disableKill = disableKill || (sourceType == "Grenade" && gareaLeaderboardConfig.disableKillOfGrenade);
				disableKill = disableKill || (sourceType == "Trap" && gareaLeaderboardConfig.disableKillOfTrap);
				disableKill = disableKill || (sourceType == "Car" && gareaLeaderboardConfig.disableKillOfCar);
				disableKill = disableKill || (targetType == "Zombie" && gareaLeaderboardConfig.disableKillOfZombie);
				disableKill = disableKill || (targetType == "Animal" && gareaLeaderboardConfig.disableKillOfAnimal);
				disableKill = disableKill || (sourceType == "Weapon" && gareaLeaderboardConfig.disableKillOfWeapon);
				disableKill = disableKill || (sourceType == "Unarmed" && gareaLeaderboardConfig.disableKillOfUnarmed);
				disableKill = disableKill || (sourceType == "UnconsciousSuicide" && gareaLeaderboardConfig.disableKillOfUnconsciousSuicide);
				disableKill = disableKill || (sourceType == "Unknown" && gareaLeaderboardConfig.disableKillOfUnknown);
				
				if (!disableKill)
				{	
					GAREALeaderboardPlayer playerWhoKilled = GetOrCreatePlayer(sourceId, sourceName);
					if (playerWhoKilled)
					{									
						// Kill
						
						// Real player
						if (targetType == "Player")
						{
							playerWhoKilled.playerKills += 1;							
							
							// HighestKillDistance					
							if (distance && playerWhoKilled.playerLongestDistance < distance)
							{
								playerWhoKilled.playerLongestDistance = Math.Round(distance);
							}
							updateTimestampPVP = true;
						}						
						// AI Survivor
						else if (targetType == "AI_Survivor")
						{	
							string includeAISurvivorFor = gareaLeaderboardConfig.includeAISurvivorFor;
							string includeAISurvivorForPVP = "pvp";
							string includeAISurvivorForPVE = "pve";
							string includeAISurvivorForBOTH = "both";		
																					
							// PVP
							if (includeAISurvivorFor == includeAISurvivorForPVP || includeAISurvivorFor == includeAISurvivorForBOTH)
							{
								playerWhoKilled.playerKills += 1;							
								
								// HighestKillDistance					
								if (distance && playerWhoKilled.playerLongestDistance < distance)
								{
									playerWhoKilled.playerLongestDistance = Math.Round(distance);
								}
								updateTimestampPVP = true;
							}
							
							// PVE
							if (includeAISurvivorFor == includeAISurvivorForPVE || includeAISurvivorFor == includeAISurvivorForBOTH)
							{
								playerWhoKilled.playerKillsAISurvivor += 1;
								updateTimestampPVE = true;
							}
						}			
						else if (targetType == "Zombie")
						{
							playerWhoKilled.playerKillsZombie += 1;
							updateTimestampPVE = true;
						}
						else if (targetType == "Animal")
						{
							// Cow
							if (target.IsInherited(Animal_BosTaurus) || target.IsInherited(Animal_BosTaurusF))
						 	{
								playerWhoKilled.playerKillsCow += 1;
								updateTimestampPVE = true;
							}
							// Wolf
							else if (target.IsInherited(Animal_CanisLupus))
							{
								playerWhoKilled.playerKillsWolf += 1;
								updateTimestampPVE = true;
							}
							// Goat
							else if (target.IsInherited(Animal_CapraHircus) || target.IsInherited(Animal_CapraHircusF))
							{
								playerWhoKilled.playerKillsGoat += 1;
								updateTimestampPVE = true;
							}
							// Roe deer
							else if (target.IsInherited(Animal_CapreolusCapreolus) || target.IsInherited(Animal_CapreolusCapreolusF))
							{
								playerWhoKilled.playerKillsRoeDeer += 1;
								updateTimestampPVE = true;
							}
							// Red deer
							else if (target.IsInherited(Animal_CervusElaphus) || target.IsInherited(Animal_CervusElaphusF))
							{
								playerWhoKilled.playerKillsRedDeer += 1;
								updateTimestampPVE = true;
							}
							// Chicken
							else if (target.IsInherited(Animal_GallusGallusDomesticus) || target.IsInherited(Animal_GallusGallusDomesticusF) || target.IsInherited(Animal_GallusGallusDomesticusF_Brown) || target.IsInherited(Animal_GallusGallusDomesticusF_White) || target.IsInherited(Animal_GallusGallusDomesticusF_Spotted))
							{
								playerWhoKilled.playerKillsChicken += 1;
								updateTimestampPVE = true;
							}
							// Sheep
							else if (target.IsInherited(Animal_OvisAries) || target.IsInherited(Animal_OvisAriesF))
							{
								playerWhoKilled.playerKillsSheep += 1;
								updateTimestampPVE = true;
							}
							// Pig
							else if (target.IsInherited(Animal_SusDomesticus))
							{
								playerWhoKilled.playerKillsPig += 1;
								updateTimestampPVE = true;
							}
							// Wild boar
							else if (target.IsInherited(Animal_SusScrofa))
							{
								playerWhoKilled.playerKillsWildBoar += 1;
								updateTimestampPVE = true;
							}
							// Bear
							else if (target.IsInherited(Animal_UrsusArctos))
							{
								playerWhoKilled.playerKillsBear += 1;
								updateTimestampPVE = true;
							}
						}
						
						if (updateTimestampPVE)
						{
							playerWhoKilled.UpdatePVEStats(gareaLeaderboardConfig);
						}
						playerWhoKilled.Save();
					}
				}
			}
			
			// Update timestamp
			if (updateTimestampPVP)
			{
				gareaLeaderboardConfig.UpdateUpdateTimestampPVP();
			}
			
			if (updateTimestampPVE)
			{
				gareaLeaderboardConfig.UpdateUpdateTimestampPVE();
			}
		}
	}
	
	GAREALeaderboardPlayer LoadPlayerFromFile(string playerId)
	{
		GAREALeaderboardPlayer gareaLeaderboardPlayer = GAREALeaderboardPlayer.LoadNewInstanceFromFile(GAREALeaderboard_PlayerDB + "\\" + playerId + ".json");
		if (gareaLeaderboardPlayer)
		{
			return gareaLeaderboardPlayer;
		}
		return null;
	}
	
	void LoadAllPlayersFromFile(bool setPlayersOffline = false)
	{
		string	fileName;
		int 	fileAttr;
		
		FindFileHandle playerFiles = FindFile(GAREALeaderboard_PlayerDB + "/*.json", fileName, fileAttr, FindFileFlags.DIRECTORIES);
		if (playerFiles)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = GAREALeaderboardPlayer.LoadNewInstanceFromFile(GAREALeaderboard_PlayerDB + "\\" + fileName);
			if (gareaLeaderboardPlayer)
			{
				fileName = "";
				fileAttr = 0;
				gareaLeaderboardPlayer.playerIsOnline = false;
				gareaLeaderboardPlayers.Insert(gareaLeaderboardPlayer);				
				
				while(FindNextFile(playerFiles, fileName, fileAttr))
				{
					gareaLeaderboardPlayer = GAREALeaderboardPlayer.LoadNewInstanceFromFile(GAREALeaderboard_PlayerDB + "\\" + fileName);
					if (gareaLeaderboardPlayer)
					{
						fileName = "";
						fileAttr = 0;
						if (setPlayersOffline)
						{
							gareaLeaderboardPlayer.playerIsOnline = false;
						}
						gareaLeaderboardPlayers.Insert(gareaLeaderboardPlayer);
					}
				}
				CloseFindFile(playerFiles);
			}
		}
	}
	
	void UpdatePlayer(GAREALeaderboardPlayer updatedPlayer, string playerId = "", string playerName = "", bool saveImmediately = true)
	{
		GAREALeaderboardPlayer gareaLeaderboardPlayer = GetOrCreatePlayer(playerId, playerName);		
		if (gareaLeaderboardPlayer)
		{
			gareaLeaderboardPlayer.Update(updatedPlayer);		
			if (saveImmediately)
			{
				gareaLeaderboardPlayer.Save();
			}
		}
	}
	
	void SaveAllPlayers(bool setPlayersOffline = false)
	{
		for (int i = 0; i < gareaLeaderboardPlayers.Count(); i++)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = gareaLeaderboardPlayers.Get(i);
			if (setPlayersOffline)
			{
				gareaLeaderboardPlayer.playerIsOnline = false;
			}
			gareaLeaderboardPlayer.Save();
		}
	}
	
	void DeletePlayer(string playerId = "")
	{
		GAREALeaderboardPlayer gareaLeaderboardPlayer = GetOrCreatePlayer(playerId);
		if (gareaLeaderboardPlayer)
		{
			if (gareaLeaderboardPlayer.Delete())
			{
				gareaLeaderboardPlayers.RemoveItem(gareaLeaderboardPlayer);
			}
		}
	}
	
	void DeletePlayers()
	{
		for (int i = 0; i < gareaLeaderboardPlayers.Count(); i++)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = gareaLeaderboardPlayers.Get(i);
			gareaLeaderboardPlayer.Delete();
		}
		gareaLeaderboardPlayers.Clear();
	}
	
	void DeleteObsoletePlayers(bool checkOnlineStatus = false)
	{
		array<string> playersToDelete = new array<string>();
		for (int i = 0; i < gareaLeaderboardPlayers.Count(); i++)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = gareaLeaderboardPlayers.Get(i);
			if (gareaLeaderboardPlayer.playerDeaths == 0 && (gareaLeaderboardPlayer.playerKills == 0 || gareaLeaderboardPlayer.playerKillsNPCs == 0))
			{
				if (checkOnlineStatus)
				{
					if (!gareaLeaderboardPlayer.playerIsOnline)
					{
						playersToDelete.Insert(gareaLeaderboardPlayer.playerId);
					}
				}
				else
				{
					playersToDelete.Insert(gareaLeaderboardPlayer.playerId);
				}
			}
		}

		for (int x = 0; x < playersToDelete.Count(); x++)
		{
			string playerId = playersToDelete.Get(x);
			DeletePlayer(playerId);
		}
	}
	
	void ResetPlayer(GAREALeaderboardPlayer gareaLeaderboardPlayer, string playerId = "", string playerName = "", bool resetPVP = true, bool resetPVE = true, bool resetGeneral = true, bool saveImmediately = true)
	{
		if (!gareaLeaderboardPlayer && playerId != "")
		{
			gareaLeaderboardPlayer = GetOrCreatePlayer(playerId, playerName);
		}
		
		if (gareaLeaderboardPlayer)
		{
			gareaLeaderboardPlayer.Reset(resetPVP, resetPVE, resetGeneral);			
			if (saveImmediately)
			{
				gareaLeaderboardPlayer.Save();
			}
		}
	}
	
	void ResetAllPlayers(bool resetPVP = true, bool resetPVE = true, bool resetGeneral = true, bool saveImmediately = true)
	{
		for (int i = 0; i < gareaLeaderboardPlayers.Count(); i++)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = gareaLeaderboardPlayers.Get(i);
			gareaLeaderboardPlayer.Reset(resetPVP, resetPVE, resetGeneral);
			
			if (saveImmediately)
			{
				gareaLeaderboardPlayer.Save();
			}
		}
	}
	
	GAREALeaderboardPlayer GetOrCreatePlayer(string playerId, string playerName = "", out bool newPlayer = false)
	{
		GAREALeaderboardPlayer retVal = null;
		if (playerId)
		{
			for (int i = 0; i < gareaLeaderboardPlayers.Count(); i++)
			{
				GAREALeaderboardPlayer gareaLeaderboardPlayer = gareaLeaderboardPlayers.Get(i);
				if (gareaLeaderboardPlayer.playerId  ==  playerId)
				{
					retVal = gareaLeaderboardPlayer;
					break;
				}
			}
		}
		
		if (retVal == null && playerName != "")
		{
			newPlayer = true;
			gareaLeaderboardPlayer = new GAREALeaderboardPlayer(playerId, playerName);
			gareaLeaderboardPlayer.playerIsOnline = true;
			retVal = gareaLeaderboardPlayer;
			gareaLeaderboardPlayers.Insert(retVal);
		}
		return retVal;
	}
	
	array<GAREALeaderboardPlayer> GetOnlinePlayers()
	{
		array<GAREALeaderboardPlayer> onlinePlayers = new array<GAREALeaderboardPlayer>();
		for (int i = 0; i < gareaLeaderboardPlayers.Count(); i++)
		{
			GAREALeaderboardPlayer gareaLeaderboardPlayer = gareaLeaderboardPlayers.Get(i);
			if (gareaLeaderboardPlayer.playerIsOnline)
			{
				onlinePlayers.Insert(gareaLeaderboardPlayer);
			}
		}
		return onlinePlayers;
	}
	
	void GetPlayerAndPositionPVP(string playerId, GAREALeaderboardConfig gareaLeaderboardConfig, out int position, out GAREALeaderboardPlayerPVP pvp)
	{
		if (playerId)
		{
			array<GAREALeaderboardPlayer> list = gareaLeaderboardPlayers;
			if (gareaLeaderboardConfig.showOnlyOnlinePlayersInTopXList)
			{
				list = GetOnlinePlayers();
			}
			
			GAREAQuickSort sort = new GAREAQuickSort(list);
			sort.QuickSortByPVPPoints(0, list.Count() - 1);
			array<GAREALeaderboardPlayer> sorted = sort.GetSortedList("desc");
			for (int i = 0; i < sorted.Count(); i++)
			{
				GAREALeaderboardPlayer lp = sorted.Get(i);
				if (lp.playerId == playerId)
				{
					position = i+1;			
					pvp = lp.GetPVP();
					break;
				}
			}
		}
	}
	
	void GetPlayerAndPositionPVE(string playerId, GAREALeaderboardConfig gareaLeaderboardConfig, out int position, out GAREALeaderboardPlayerPVE pve)
	{
		if (playerId)
		{
			array<GAREALeaderboardPlayer> list = gareaLeaderboardPlayers;
			if (gareaLeaderboardConfig.showOnlyOnlinePlayersInTopXList)
			{
				list = GetOnlinePlayers();
			}
			
			GAREAQuickSort sort = new GAREAQuickSort(list);
			sort.QuickSortByPVEPoints(0, list.Count() - 1);
			array<GAREALeaderboardPlayer> sorted = sort.GetSortedList("desc");		
			for (int i = 0; i < sorted.Count(); i++)
			{
				GAREALeaderboardPlayer lp = sorted.Get(i);
				if (lp.playerId == playerId)
				{
					position = i+1;
					pve = lp.GetPVE();
					break;
				}
			}
		}
	}	
	
	array<GAREALeaderboardPlayerPVP> GetTopXPVP(GAREALeaderboardConfig gareaLeaderboardConfig, int topX = 10)
	{
		array<GAREALeaderboardPlayer> list = gareaLeaderboardPlayers;
		if (gareaLeaderboardConfig.showOnlyOnlinePlayersInTopXList)
		{
			list = GetOnlinePlayers();
		}
		
		array<GAREALeaderboardPlayerPVP> listTopX = new array<GAREALeaderboardPlayerPVP>();
		GAREAQuickSort sort = new GAREAQuickSort(list);
		sort.QuickSortByPVPPoints(0, list.Count() - 1);
		array<GAREALeaderboardPlayer> sorted = sort.GetSortedList("desc");
		for (int i = 0; i < sorted.Count(); i++)
		{
			GAREALeaderboardPlayer p = sorted.Get(i);
			GAREALeaderboardPlayerPVP pvp = p.GetPVP();
			if (pvp)
			{
				listTopX.Insert(pvp);
			}	
			
			if (i == (topX - 1))
			{
				break;	
			}
		}
		return listTopX;
	}	
	
	array<GAREALeaderboardPlayerPVE> GetTopXPVE(GAREALeaderboardConfig gareaLeaderboardConfig, int topX = 10)
	{
		array<GAREALeaderboardPlayer> list = gareaLeaderboardPlayers;
		if (gareaLeaderboardConfig.showOnlyOnlinePlayersInTopXList)
		{
			list = GetOnlinePlayers();
		}
		
		array<GAREALeaderboardPlayerPVE> listTopX = new array<GAREALeaderboardPlayerPVE>();
		GAREAQuickSort sort = new GAREAQuickSort(list);
		sort.QuickSortByPVEPoints(0, list.Count() - 1);
		array<GAREALeaderboardPlayer> sorted = sort.GetSortedList("desc");
		for (int i = 0; i < sorted.Count(); i++)
		{
			GAREALeaderboardPlayer p = sorted.Get(i);			
			GAREALeaderboardPlayerPVE pve = p.GetPVE();
			if (pve)
			{
				listTopX.Insert(pve);
			}
			
			if (i == (topX - 1))
			{
				break;	
			}	
		}
		return listTopX;
	}
	
	array<GAREALeaderboardPlayerKey> GetPlayerKeys()
	{
		array<GAREALeaderboardPlayerKey> playerKeys = new array<GAREALeaderboardPlayerKey>();

		GAREAQuickSort sort = new GAREAQuickSort(gareaLeaderboardPlayers);
		sort.QuickSortByName(0, gareaLeaderboardPlayers.Count() - 1);
		array<GAREALeaderboardPlayer> sorted = sort.GetSortedList("asc");
		
		for (int i = 0; i < sorted.Count(); i++)
		{
			GAREALeaderboardPlayer p = sorted.Get(i);
			playerKeys.Insert(p.GetPlayerKey());
		}
		return playerKeys;
	}
	
	void OnRequestResetAllPlayersPVP()
	{
		bool saveImmediately = true;
		ResetAllPlayers(true, false, true, saveImmediately);
		SaveAllPlayers();
		GAREALeaderboardConfig.GetInstance().UpdateUpdateTimestampPVP("", saveImmediately);
	}
	
	void OnRequestResetAllPlayersPVE()
	{
		bool saveImmediately = true;
		ResetAllPlayers(false, true, true, saveImmediately);
		SaveAllPlayers();
		GAREALeaderboardConfig.GetInstance().UpdateUpdateTimestampPVE("", saveImmediately);
	}
}