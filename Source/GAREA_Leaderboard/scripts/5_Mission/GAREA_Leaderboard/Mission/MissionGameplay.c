modded class MissionGameplay extends Mission
{
	void MissionGameplay()
	{		
        GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardPVP", this, SingeplayerExecutionType.Server);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardPVE", this, SingeplayerExecutionType.Server);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCShowGAREALeaderboardAdmin", this, SingeplayerExecutionType.Server);
		GetRPCManager().AddRPC("GAREA_Leaderboard", "RPCUpdateGAREALeaderboardAdminPlayer", this, SingeplayerExecutionType.Server);
	}

	void ~MissionGameplay()
	{
		GAREALeaderboardGUIPVP.GetInstance().ClearInstance();
	}

	override void OpenGAREALeaderboardGUIPVP()
	{
		if (GetGame())
		{
			UIManager uiManager = GetGame().GetUIManager();
			
			GAREALeaderboardGUIPVP gareaLeaderboardGUIPVP = GAREALeaderboardGUIPVP.GetInstance();
			GAREALeaderboardGUIPVE gareaLeaderboardGUIPVE = GAREALeaderboardGUIPVE.GetInstance();
			GAREALeaderboardGUIAdmin gareaLeaderboardGUIAdmin = GAREALeaderboardGUIAdmin.GetInstance();
			if (uiManager)
			{
				if (gareaLeaderboardGUIAdmin.open && !gareaLeaderboardGUIAdmin.typing)
				{
					gareaLeaderboardGUIAdmin.Close();
				}
							
				if (!gareaLeaderboardGUIPVP.open && !gareaLeaderboardGUIPVE.open)
				{
					if (uiManager && uiManager.GetMenu() == NULL)
					{
						GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVP", null, true);
					}
				}
				else
				{
					gareaLeaderboardGUIPVP.Close();
					gareaLeaderboardGUIPVE.Close();
				}
			}
		}
	}
	
	override void OpenGAREALeaderboardGUIPVE()
	{
		if (GetGame())
		{
			UIManager uiManager = GetGame().GetUIManager();
			
			GAREALeaderboardGUIPVP gareaLeaderboardGUIPVP = GAREALeaderboardGUIPVP.GetInstance();
			GAREALeaderboardGUIPVE gareaLeaderboardGUIPVE = GAREALeaderboardGUIPVE.GetInstance();
			GAREALeaderboardGUIAdmin gareaLeaderboardGUIAdmin = GAREALeaderboardGUIAdmin.GetInstance();
			if (uiManager)
			{
				if (gareaLeaderboardGUIAdmin.open && !gareaLeaderboardGUIAdmin.typing)
				{
					gareaLeaderboardGUIAdmin.Close();
				}
				
				if (!gareaLeaderboardGUIPVP.open && !gareaLeaderboardGUIPVE.open)
				{
					if (uiManager && uiManager.GetMenu() == NULL)
					{
						GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVE", null, true);
					}
				}
				else
				{
					gareaLeaderboardGUIPVP.Close();
					gareaLeaderboardGUIPVE.Close();
				}
			}
		}
	}
	
	void RPCShowGAREALeaderboardPVP(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param1<GAREALeaderboard> data;
		if (ctx.Read(data))
		{			
			UIManager uiManager = GetGame().GetUIManager();
			if (uiManager && uiManager.GetMenu() == NULL)
			{
				GAREALeaderboard gareaLeaderboard = data.param1;
				if (gareaLeaderboard && !gareaLeaderboard.gareaLeaderboardConfig.disablePVPLeaderboard)
				{
					GAREALeaderboardGUIPVP gareaLeaderboardGUIPVP = GAREALeaderboardGUIPVP.GetInstance();
					if (gareaLeaderboardGUIPVP && !gareaLeaderboardGUIPVP.open)
					{
						uiManager.ShowScriptedMenu(gareaLeaderboardGUIPVP, NULL);
						gareaLeaderboardGUIPVP.UpdateLeaderBoard(gareaLeaderboard);
					}	
				}
				
			}
		}
	}
	
	void RPCShowGAREALeaderboardPVE(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param1<GAREALeaderboard> data;
		if (ctx.Read(data))
		{			
			UIManager uiManager = GetGame().GetUIManager();
			if (uiManager && uiManager.GetMenu() == NULL)
			{
				GAREALeaderboard gareaLeaderboard = data.param1;
				if (gareaLeaderboard && !gareaLeaderboard.gareaLeaderboardConfig.disablePVELeaderboard)
				{
					GAREALeaderboardGUIPVE gareaLeaderboardGUIPVE = GAREALeaderboardGUIPVE.GetInstance();
					if (gareaLeaderboardGUIPVE && !gareaLeaderboardGUIPVE.open)
					{
						uiManager.ShowScriptedMenu(gareaLeaderboardGUIPVE, NULL);
						gareaLeaderboardGUIPVE.UpdateLeaderBoard(gareaLeaderboard);
					}
				}				
			}
		}
	}
	
	void RPCShowGAREALeaderboardAdmin(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param1<array<GAREALeaderboardPlayerKey>> data;
		if (ctx.Read(data))
		{			
			UIManager uiManager = GetGame().GetUIManager();
			if (uiManager && uiManager.GetMenu() == NULL)
			{
				array<GAREALeaderboardPlayerKey> playerNamesById = data.param1;
				if (playerNamesById)
				{
					GAREALeaderboardGUIAdmin gareaLeaderboardGUIAdmin = GAREALeaderboardGUIAdmin.GetInstance();
					if (gareaLeaderboardGUIAdmin && !gareaLeaderboardGUIAdmin.open)
					{
						uiManager.ShowScriptedMenu(gareaLeaderboardGUIAdmin, NULL);
						gareaLeaderboardGUIAdmin.UpdatePlayerList(playerNamesById);
					}
				}				
			}
		}
	}
	
	void RPCUpdateGAREALeaderboardAdminPlayer(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param1<GAREALeaderboardPlayer> data;
		if (ctx.Read(data))
		{
			GAREALeaderboardPlayer playerData = data.param1;
			if (playerData)
			{	
				GAREALeaderboardGUIAdmin gareaLeaderboardGUIAdmin = GAREALeaderboardGUIAdmin.GetInstance();
				if (gareaLeaderboardGUIAdmin && gareaLeaderboardGUIAdmin.open)
				{
					gareaLeaderboardGUIAdmin.UpdatePlayerData(playerData);
				}			
			}
		}
	}
}