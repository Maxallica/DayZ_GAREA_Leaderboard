modded class MissionServer extends MissionBase
{
	void MissionServer()
	{
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVP", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVE", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdmin", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminGetPlayer", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminDeletePlayer", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminUpdatePlayer", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetPlayerPVP", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetPlayerPVE", this, SingeplayerExecutionType.Client);		
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetPlayerPVE", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminReloadConfig", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminReloadAllPlayerFiles", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetAllPlayersPVP", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetAllPlayersPVE", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminDeleteObsoletePlayers", this, SingeplayerExecutionType.Client);

        if (!FileExist(GAREALeaderboard_CONFIG_FOLDER))
		{
			MakeDirectory(GAREALeaderboard_CONFIG_FOLDER);
		}

        if (!FileExist(GAREALeaderboard_PlayerDB))
		{
		    MakeDirectory(GAREALeaderboard_PlayerDB);
        }

		GAREALeaderboardConfig.GetInstance(true);
		GAREALeaderboardManager.GetInstance().LoadAllPlayersFromFile(true);
	}
	
    void ~MissionServer()
	{
		GAREALeaderboardManager.GetInstance().SaveAllPlayers(true);
		GAREALeaderboardManager.ClearInstance();
		GAREALeaderboardConfig.ClearInstance();
	}
	
	void RPCRequestGAREALeaderboardPVP(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardConfig gareaLeaderboardConfig = GAREALeaderboardConfig.GetInstance();
			string playerId = sender.GetPlainId();
			
			// array<Man> mans = new array<Man>();
			// GetGame().GetPlayers(mans);	
			int playerOnlineCounter = 0;
			// playerOnlineCounter = mans.Count()
			playerOnlineCounter = GAREALeaderboardManager.GetInstance().GetOnlinePlayers().Count();
			GAREALeaderboard gareaLeaderboard = new GAREALeaderboard();
			
			// Requested player	
			int pos;
			GAREALeaderboardPlayerPVP requestedPlayer;
			GAREALeaderboardManager.GetInstance().GetPlayerAndPositionPVP(playerId, gareaLeaderboardConfig, pos, requestedPlayer);
			gareaLeaderboard.requestedPlayerPosition = pos;			
			gareaLeaderboard.requestedPlayerPVP = requestedPlayer;
						
			// Global data
			gareaLeaderboard.playerOnlineCounter = playerOnlineCounter;
			gareaLeaderboard.gareaLeaderboardConfig = gareaLeaderboardConfig;
			int playerDisplaySize = gareaLeaderboardConfig.playerDisplaySize;
			gareaLeaderboard.topXPlayersPVP = GAREALeaderboardManager.GetInstance().GetTopXPVP(gareaLeaderboardConfig, playerDisplaySize);
			GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardPVP", new Param1<GAREALeaderboard>(gareaLeaderboard), true, sender);
		}
	}
	
	void RPCRequestGAREALeaderboardPVE(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardConfig gareaLeaderboardConfig = GAREALeaderboardConfig.GetInstance();
			string playerId = sender.GetPlainId();
			
			// array<Man> mans = new array<Man>();
			// GetGame().GetPlayers(mans);	
			int playerOnlineCounter = 0;
			// playerOnlineCounter = mans.Count()
			playerOnlineCounter = GAREALeaderboardManager.GetInstance().GetOnlinePlayers().Count();
			GAREALeaderboard gareaLeaderboard = new GAREALeaderboard();
			
			// Requested player	
			int pos;
			GAREALeaderboardPlayerPVE requestedPlayer;
			GAREALeaderboardManager.GetInstance().GetPlayerAndPositionPVE(playerId, gareaLeaderboardConfig, pos, requestedPlayer);
			gareaLeaderboard.requestedPlayerPosition = pos;
			gareaLeaderboard.requestedPlayerPVE = requestedPlayer;
			
			// Global data
			gareaLeaderboard.playerOnlineCounter = playerOnlineCounter;
			gareaLeaderboard.gareaLeaderboardConfig = gareaLeaderboardConfig;
			int playerDisplaySize = gareaLeaderboardConfig.playerDisplaySize;
			
			if (!gareaLeaderboardConfig.disableKillOfZombie || !gareaLeaderboardConfig.disableKillOfAnimal)
			{
				gareaLeaderboard.topXPlayersPVE = GAREALeaderboardManager.GetInstance().GetTopXPVE(gareaLeaderboardConfig, playerDisplaySize);
			}
			GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardPVE", new Param1<GAREALeaderboard>(gareaLeaderboard), true, sender);			
		}
	}
	
	void RPCRequestGAREALeaderboardAdmin(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			array<GAREALeaderboardPlayerKey> playerKeys = GAREALeaderboardManager.GetInstance().GetPlayerKeys();
			GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardAdmin", new Param1<array<GAREALeaderboardPlayerKey>>(playerKeys), true, sender);
		}
	}
	
	void RPCRequestGAREALeaderboardAdminGetPlayer(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			Param1<GAREALeaderboardPlayerKey> data;
			if (ctx.Read(data))
			{
				GAREALeaderboardPlayerKey playerKey = data.param1;
				if (playerKey)
				{
					GAREALeaderboardPlayer player = GAREALeaderboardManager.GetInstance().GetOrCreatePlayer(playerKey.playerId);					
					player.ReloadSurvivedTime();
					GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCUpdateGAREALeaderboardAdminPlayer", new Param1<GAREALeaderboardPlayer>>(player), true, sender);
				}				
			}
		}
	}
	
	void RPCRequestGAREALeaderboardAdminResetPlayerPVP(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			Param1<GAREALeaderboardPlayerKey> data;
			if (ctx.Read(data))
			{
				GAREALeaderboardPlayerKey playerKey = data.param1;
				if (playerKey)
				{
					bool saveImmediately = true;
					GAREALeaderboardManager.GetInstance().ResetPlayer(null, playerKey.playerId, playerKey.playerName, true, false, false, saveImmediately);
				}
			}
		}
	}
	
	void RPCRequestGAREALeaderboardAdminResetPlayerPVE(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			Param1<GAREALeaderboardPlayerKey> data;
			if (ctx.Read(data))
			{
				GAREALeaderboardPlayerKey playerKey = data.param1;
				if (playerKey)
				{
					bool saveImmediately = true;
					GAREALeaderboardManager.GetInstance().ResetPlayer(null, playerKey.playerId, playerKey.playerName, false, true, false, saveImmediately);
				}
			}
		}
	}
	
	void RPCRequestGAREALeaderboardAdminDeletePlayer(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			Param1<GAREALeaderboardPlayerKey> data;
			if (ctx.Read(data))
			{
				GAREALeaderboardPlayerKey playerKey = data.param1;
				if (playerKey)
				{
					GAREALeaderboardManager.GetInstance().DeletePlayer(playerKey.playerId);
				}
			}
		}
	}
	
	void RPCRequestGAREALeaderboardAdminUpdatePlayer(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			Param1<GAREALeaderboardPlayer> data;
			if (ctx.Read(data))
			{
				GAREALeaderboardPlayer updatedPlayer = data.param1;
				if (updatedPlayer)
				{
					GAREALeaderboardConfig gareaLeaderboardConfig = GAREALeaderboardConfig.GetInstance();
					updatedPlayer.UpdatePVEStats(gareaLeaderboardConfig);
					
					bool saveImmediately = true;
					GAREALeaderboardManager.GetInstance().UpdatePlayer(updatedPlayer, updatedPlayer.playerId, updatedPlayer.playerName, saveImmediately);
				}
			}
		}
	}
	
	void RPCRequestGAREALeaderboardAdminReloadConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardConfig.GetInstance(true);
		}
	}
	
	void RPCRequestGAREALeaderboardAdminReloadAllPlayerFiles(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardManager.ClearInstance();
			GAREALeaderboardManager.GetInstance().LoadAllPlayersFromFile();
			array<GAREALeaderboardPlayerKey> playerKeys = GAREALeaderboardManager.GetInstance().GetPlayerKeys();
			GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardAdmin", new Param1<array<GAREALeaderboardPlayerKey>>(playerKeys), true, sender);
		}
	}
	
	void RPCRequestGAREALeaderboardAdminResetAllPlayersPVP(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardManager.GetInstance().OnRequestResetAllPlayersPVP();
		}
	}
	
	void RPCRequestGAREALeaderboardAdminResetAllPlayersPVE(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardManager.GetInstance().OnRequestResetAllPlayersPVE();
		}
	}
	
	void RPCRequestGAREALeaderboardAdminDeleteObsoletePlayers(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (sender)
		{
			GAREALeaderboardManager.GetInstance().DeleteObsoletePlayers(true);
		}
	}
};
