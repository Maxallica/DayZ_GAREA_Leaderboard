class GAREALeaderboardGUIPVP extends UIScriptedMenu
{
    protected static ref GAREALeaderboardGUIPVP Instance;
	
	// Controls
	protected Widget pAdminButtons;
	protected ButtonWidget bAdmin;
	protected Widget pPVE;
	protected ButtonWidget bPVE;
	protected ButtonWidget bClose;
	
	// Titlebar
	protected TextWidget tTitle;
	protected TextWidget tPlayerOnlineCounter;
    protected TextWidget tUpdateTimestamp;
	protected TextWidget tTime;
	
	// Player data
	protected TextWidget tPlayerPos;
	protected TextWidget tPlayerName;
	protected TextWidget tPlayerKills;
	protected TextWidget tPlayerDeaths;
	protected TextWidget tPlayerKD;
	protected TextWidget tPlayerLongestDistance;
	protected TextWidget tPlayerSurvivedTime;
	protected TextWidget tPlayerPVPPoints;
	
	// Headers
	protected TextWidget thPlayerPos;
	protected TextWidget thPlayerName;
	protected TextWidget thPlayerKills;
	protected TextWidget thPlayerDeaths;
	protected TextWidget thPlayerKD;
	protected TextWidget thPlayerLongestDistance;
	protected TextWidget thPlayerSurvivedTime;
	protected TextWidget thPlayerPVPPoints;
	
	protected TextWidget tTopX;
	protected ScrollWidget swBoard;
	protected GridSpacerWidget gsBoard;
	
	bool open;

    void GAREALeaderboardGUIPVP()
    {
    }

    void ~GAREALeaderboardGUIPVP()
    {
		open = false;
		GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
	}

    static GAREALeaderboardGUIPVP GetInstance()
	{
		if (!Instance)
        {
            Instance = new GAREALeaderboardGUIPVP();
        }
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("GAREA_Leaderboard\\gui\\layouts\\gareaLeaderboard_pvp.layout");
		
		// Controls
		pAdminButtons = Widget.Cast(layoutRoot.FindAnyWidget("pAdminButtons"));
		bAdmin = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bAdmin"));
		pPVE = Widget.Cast(layoutRoot.FindAnyWidget("pPVE"));
		bPVE = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bPVE"));
        bClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bClose"));
		
		// Titlebar
        tTitle = TextWidget.Cast(layoutRoot.FindAnyWidget("tTitle"));		
		tPlayerOnlineCounter = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerOnlineCounter"));
        tUpdateTimestamp = TextWidget.Cast(layoutRoot.FindAnyWidget("tUpdateTimestamp"));
		tTime = TextWidget.Cast(layoutRoot.FindAnyWidget("tTime"));
				
		// Headers
		thPlayerPos = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerPos"));
		thPlayerName = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerName"));
		thPlayerKills = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKills"));
		thPlayerDeaths = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerDeaths"));
		thPlayerKD = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKD"));
		thPlayerLongestDistance = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerLongestDistance"));
		thPlayerSurvivedTime = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerSurvivedTime"));
		thPlayerPVPPoints = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerPVPPoints"));
		
		// Player data
		tPlayerPos = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerPos"));
		tPlayerName = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerName"));
		tPlayerKills = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKills"));
		tPlayerDeaths = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerDeaths"));
		tPlayerKD = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKD"));
		tPlayerLongestDistance = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerLongestDistance"));
		tPlayerSurvivedTime = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerSurvivedTime"));
		tPlayerPVPPoints = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerPVPPoints"));
		
		tTopX = TextWidget.Cast(layoutRoot.FindAnyWidget("tTopX"));		
		swBoard = ScrollWidget.Cast(layoutRoot.FindAnyWidget("swBoard"));
		swBoard.VScrollToPos01(0);
		gsBoard = GridSpacerWidget.Cast(layoutRoot.FindAnyWidget("gsBoard"));
		
        return layoutRoot;
    }

    void UpdateLeaderBoard(GAREALeaderboard gareaLeaderboard)
	{	
		if (gareaLeaderboard)
		{
			// Reset TopX board
			if (gsBoard)
			{
				while (gsBoard.GetChildren())
				{
					gsBoard.RemoveChild(gsBoard.GetChildren());	
				}
			}
			
			GAREALeaderboardConfig gareaLeaderboardConfig = gareaLeaderboard.gareaLeaderboardConfig;			
			pPVE.Show(true);
			if (gareaLeaderboardConfig.disablePVELeaderboard)
			{
				pPVE.Show(false);
			}
						
			GAREALeaderboardPlayerPVP requestedPlayer = gareaLeaderboard.requestedPlayerPVP;		
			
			// Titlebar
			tPlayerOnlineCounter.SetText("Online " + gareaLeaderboard.playerOnlineCounter);
			tUpdateTimestamp.SetText(gareaLeaderboardConfig.updateTimestampPVP);
			tTime.SetText("" + GAREALeaderboardUtils.GetTime());
			tTopX.SetText("Top " + gareaLeaderboardConfig.playerDisplaySize);
			
			// Headers
			tTitle.SetText(gareaLeaderboardConfig.tTitle);
			thPlayerPos.SetText(gareaLeaderboardConfig.thPlayerPos);
			thPlayerName.SetText(gareaLeaderboardConfig.thPlayerName);
			thPlayerKills.SetText(gareaLeaderboardConfig.thPlayerKills);
			thPlayerDeaths.SetText(gareaLeaderboardConfig.thPlayerDeaths);
			thPlayerKD.SetText(gareaLeaderboardConfig.thPlayerKD);
			thPlayerLongestDistance.SetText(gareaLeaderboardConfig.thPlayerLongestDistance);
			thPlayerPVPPoints.SetText(gareaLeaderboardConfig.thPlayerPoints);
			
			tPlayerName.ClearFlags(WidgetFlags.CLIPCHILDREN);
			thPlayerSurvivedTime.Show(false);
			if (gareaLeaderboardConfig.showSurvivedTimeFor == "yourself" || gareaLeaderboardConfig.showSurvivedTimeFor == "all")
			{
				tPlayerName.SetFlags(WidgetFlags.CLIPCHILDREN);
				thPlayerSurvivedTime.SetText(gareaLeaderboardConfig.thPlayerSurvivedTime);
				thPlayerSurvivedTime.Show(true);
			}
			
			// Player data
			tPlayerPos.SetText("" + gareaLeaderboard.requestedPlayerPosition);
			tPlayerName.SetText("" + requestedPlayer.playerName);
			tPlayerKills.SetText("" + requestedPlayer.playerKills);
			tPlayerDeaths.SetText("" + requestedPlayer.playerDeaths);
			tPlayerKD.SetText("" + requestedPlayer.GetKD());
			tPlayerLongestDistance.SetText("" + requestedPlayer.playerLongestDistance + "m");
			tPlayerPVPPoints.SetText("" + requestedPlayer.GetPVPPoints());
			
			if (gareaLeaderboardConfig.showSurvivedTimeFor == "yourself" || gareaLeaderboardConfig.showSurvivedTimeFor == "all")
			{
				tPlayerSurvivedTime.SetText("" + requestedPlayer.GetSurvivedTimeAsString(gareaLeaderboardConfig));
			}
			
			// Admin
			pAdminButtons.Show(false);
			if (gareaLeaderboard.IsRequestedPlayerAnAdminPVP())
			{
				pAdminButtons.Show(true);
			}
			
			// Top x players
			array<GAREALeaderboardPlayerPVP> topXPlayersPVP = gareaLeaderboard.topXPlayersPVP;
			for (int i = 0; i < topXPlayersPVP.Count(); i++)
			{
				Widget fGAREALeaderboardEntry = GetGame().GetWorkspace().CreateWidgets( "GAREA_Leaderboard\\gui\\layouts\\gareaLeaderboard_entry_pvp.layout" );
								
				GAREALeaderboardPlayerPVP gareaLeaderboardPlayer = topXPlayersPVP.Get(i);
				if (gareaLeaderboardPlayer)
				{
					Widget pBackground = Widget.Cast(fGAREALeaderboardEntry.FindAnyWidget("pBackground"));					
					bool yourself = false;
					if (requestedPlayer.playerId == gareaLeaderboardPlayer.playerId)
					{
						yourself = true;
					}
					
					if (yourself)
					{
						pBackground.SetColor(ARGB(255, 255, 255, 255));					
					}
					
					Widget pPlayerOnline = Widget.Cast(fGAREALeaderboardEntry.FindAnyWidget("pPlayerOnline"));
					if (gareaLeaderboardPlayer.playerIsOnline)
					{
						pPlayerOnline.SetColor(ARGB(255, 0, 255, 0));
					}
					else
					{
						pPlayerOnline.SetColor(ARGB(255, 255, 0, 0));
					}
					
					int pos = i+1;
					
					// Pos
					TextWidget tPlayerPos = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerPos"));
					tPlayerPos.SetText("" + pos);
					if (yourself)
					{
						tPlayerPos.SetColor(ARGB(255, 0, 0, 0));
					}
					
					// Player name
					TextWidget tPlayerName = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerName"));
					tPlayerName.SetText("" + gareaLeaderboardPlayer.playerName);
					if (yourself)
					{
						tPlayerName.SetColor(ARGB(255, 0, 0, 0));
					}
					
					// Survied time
					tPlayerName.ClearFlags(WidgetFlags.CLIPCHILDREN);
					if (gareaLeaderboardConfig.showSurvivedTimeFor == "all")
					{
						tPlayerName.SetFlags(WidgetFlags.CLIPCHILDREN);
						TextWidget tPlayerSurvivedTime = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerSurvivedTime"));
						tPlayerSurvivedTime.SetText("" + gareaLeaderboardPlayer.GetSurvivedTimeAsString(gareaLeaderboardConfig));
						if (yourself)
						{
							tPlayerSurvivedTime.SetColor(ARGB(255, 0, 0, 0));
						}
					}
					
					// Longest distance
					TextWidget tPlayerLongestDistance = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerLongestDistance"));
					tPlayerLongestDistance.SetText("" + gareaLeaderboardPlayer.playerLongestDistance + "m");
					if (yourself)
					{
						tPlayerLongestDistance.SetColor(ARGB(255, 0, 0, 0));
					}
					
					// Kills
					TextWidget tPlayerKills = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKills"));
					tPlayerKills.SetText("" + gareaLeaderboardPlayer.playerKills);
					if (yourself)
					{
						tPlayerKills.SetColor(ARGB(255, 0, 0, 0));
					}
					
					// Deaths
					TextWidget tPlayerDeaths = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerDeaths"));
					tPlayerDeaths.SetText("" + gareaLeaderboardPlayer.playerDeaths);
					if (yourself)
					{
						tPlayerDeaths.SetColor(ARGB(255, 0, 0, 0));
					}
					
					// K/D 
					TextWidget tPlayerKD = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKD"));
					tPlayerKD.SetText("" + gareaLeaderboardPlayer.GetKD());
					if (yourself)
					{
						tPlayerKD.SetColor(ARGB(255, 0, 0, 0));
					}
					
					// PVP points
					TextWidget tPlayerPVPPoints = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerPVPPoints"));
					tPlayerPVPPoints.SetText("" + gareaLeaderboardPlayer.GetPVPPoints());
					if (yourself)
					{
						tPlayerPVPPoints.SetColor(ARGB(255, 0, 0, 0));
					}
					
					gsBoard.AddChild(fGAREALeaderboardEntry);
				}				
			}
		}
	}
	
    override void OnShow()
	{
		super.OnShow();
		open = true;
		// To avoid action events from player (e.g. activate flashlight)
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			player.SetRestrained(true);	
		}
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
	}
	
	override void OnHide()
	{
		super.OnHide();
		// Reactivate action events from player
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			player.SetRestrained(false);
		}
		open = false;
		GetGame().GetPlayer().SetInventorySoftLock(false);
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
		Close();
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		bool retVal = super.OnKeyDown(w, x, y, key);		
		if (key == 1 && open)
		{	
			// Close gui when ESC was clicked, gui must be open
			Close();
			return true;
		}
		return retVal;
	}

    override bool OnClick( Widget w, int x, int y, int button )
	{
		bool retVal = super.OnClick(w, x, y, button);		
		switch(w)
		{
			case bAdmin:
				Close();
			
				// Send request for admin
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdmin", null, true);
				return true;
			break;
			case bPVE:
				Close();
			
				// Send request for pve
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVE", null, true);
				return true;
			break;
			case bClose:
                // Close gui when X button was clicked
                Close();
				return true;
		}
		return retVal;
	}
}
