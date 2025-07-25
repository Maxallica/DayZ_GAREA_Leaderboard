class GAREALeaderboardGUIAdmin extends UIScriptedMenu
{
	protected static ref GAREALeaderboardGUIAdmin Instance;
	
	// TextListbox
	protected TextListboxWidget tlbPlayerList;
	protected int tlbPlayerListSelectedRow;
	protected int tlbPlayerListSelectedColumn;
	
	protected EditBoxWidget ebSearch;
	protected Widget pPlayerEntry;
	
	// Controls
	protected Widget pPVP;
	protected ButtonWidget bPVP;
	protected Widget pPVE;
	protected ButtonWidget bPVE;
	protected ButtonWidget bClose
	protected ButtonWidget bDeletePlayer;
	protected ButtonWidget bSavePlayer;
	protected ButtonWidget bResetPlayerDeaths;
	protected ButtonWidget bResetPlayerSurvivalTime;
	protected ButtonWidget bResetPlayerPVP;
	protected ButtonWidget bResetPlayerPVE;
	
	protected ButtonWidget bReloadConfig;
	protected ButtonWidget bReloadAllPlayerFiles;
	protected ButtonWidget bResetAllPlayersPVP;
	protected ButtonWidget bResetAllPlayersPVE;
	protected ButtonWidget bDeleteObsoletePlayers;
	
	// Titlebar
	protected TextWidget tTitle;
	
	// Player data
	// General
	protected Widget pPlayerOnline;
	protected TextWidget tPlayerName;
	protected EditBoxWidget tPlayerDeaths;
	protected EditBoxWidget tPlayerSurvivedTime;
	// PVP
	protected EditBoxWidget tPlayerKills;
	protected EditBoxWidget tPlayerLongestDistance;
	// PVE	
	protected EditBoxWidget tPlayerKillsAISurvivor;
	protected EditBoxWidget tPlayerKillsZombie;
	protected EditBoxWidget tPlayerKillsBear;
	protected EditBoxWidget tPlayerKillsWolf;
	protected EditBoxWidget tPlayerKillsWildBoar;
	protected EditBoxWidget tPlayerKillsRedDeer;
	protected EditBoxWidget tPlayerKillsRoeDeer;
	protected EditBoxWidget tPlayerKillsSheep;
	protected EditBoxWidget tPlayerKillsGoat;
	protected EditBoxWidget tPlayerKillsCow;
	protected EditBoxWidget tPlayerKillsPig;
	protected EditBoxWidget tPlayerKillsChicken;	
	protected TextWidget tPlayerKillsAnimal;	
	protected TextWidget tPlayerKillsNPCTotal;	
	
	protected ref array<GAREALeaderboardPlayerKey> playerKeys;
	
	bool open;
	bool typing;
	void GAREALeaderboardGUIAdmin()
	{
		this.playerKeys = new array<GAREALeaderboardPlayerKey>();
	}

	void ~GAREALeaderboardGUIAdmin()
	{
		open = false;
		GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable(true);
	}

	static GAREALeaderboardGUIAdmin GetInstance()
	{
		if (!Instance)
		{
			Instance = new GAREALeaderboardGUIAdmin();
		}
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("GAREA_Leaderboard\\gui\\layouts\\gareaLeaderboard_admin.layout");
		tlbPlayerList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("tlbPlayerList"));
		
		ebSearch = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ebSearch"));
		pPlayerEntry = Widget.Cast(layoutRoot.FindAnyWidget("pPlayerEntry"));
		pPlayerEntry.Show(false);
		
		// Controls
		pPVP = Widget.Cast(layoutRoot.FindAnyWidget("pPVP"));
		pPVE = Widget.Cast(layoutRoot.FindAnyWidget("pPVE"));		
		bPVP = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bPVP"));
		bPVE = Widget.Cast(layoutRoot.FindAnyWidget("bPVE"));
		bDeletePlayer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bDeletePlayer"));
		bSavePlayer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bSavePlayer"));
		bResetPlayerDeaths = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bResetPlayerDeaths"));
		bResetPlayerSurvivalTime = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bResetPlayerSurvivalTime"));
		bResetPlayerPVP = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bResetPlayerPVP"));
		bResetPlayerPVE = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bResetPlayerPVE"));		
		bClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bClose"));
		
		bReloadConfig = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bReloadConfig"));
		bReloadAllPlayerFiles = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bReloadAllPlayerFiles"));
		bResetAllPlayersPVP = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bResetAllPlayersPVP"));
		bResetAllPlayersPVE = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bResetAllPlayersPVE"));
		bDeleteObsoletePlayers = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bDeleteObsoletePlayers"));
		
		// Titlebar
		tTitle = TextWidget.Cast(layoutRoot.FindAnyWidget("tTitle"));
		
		// Player data
		// General
		pPlayerOnline = Widget.Cast(layoutRoot.FindAnyWidget("pPlayerOnline"));
		tPlayerName = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerName"));
		tPlayerDeaths = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerDeaths"));
		tPlayerSurvivedTime = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerSurvivedTime"));
		// PVP
		tPlayerKills = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKills"));
		tPlayerLongestDistance = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerLongestDistance"));
		// PVE		
		// AI Survivor
		tPlayerKillsAISurvivor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsAISurvivor"));
		// Zombie
		tPlayerKillsZombie = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsZombie"));						
		// Bear
		tPlayerKillsBear = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsBear"));
		// Wolf
		tPlayerKillsWolf = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsWolf"));
		// Wild boar
		tPlayerKillsWildBoar = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsWildBoar"));
		// Red deer
		tPlayerKillsRedDeer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsRedDeer"));
		// Roe deer
		tPlayerKillsRoeDeer = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsRoeDeer"));
		// Sheep
		tPlayerKillsSheep = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsSheep"));
		// Goat
		tPlayerKillsGoat = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsGoat"));
		// Cow
		tPlayerKillsCow = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsCow"));
		// Pig
		tPlayerKillsPig = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsPig"));
		// Chicken
		tPlayerKillsChicken = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsChicken"));
		// Animal
		tPlayerKillsAnimal = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsAnimal"));
		// Total
		tPlayerKillsNPCTotal = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsNPCTotal"));
		
		return layoutRoot;
	}

	void UpdatePlayerList(array<GAREALeaderboardPlayerKey> playerKeys)
	{
		this.playerKeys = playerKeys;
		FilterPlayerList();	
	}
	
	void FilterPlayerList(string searchWord = "")
	{
		tlbPlayerList.ClearItems();		
		for (int i = 0; i < playerKeys.Count(); i++)
		{
			GAREALeaderboardPlayerKey playerKey = playerKeys.Get(i);			
			if (playerKey)
			{
				string entry = playerKey.playerName + " " + "(" + playerKey.playerId + ")";
				entry = entry.Trim();
				entry.ToLower();
				
				searchWord = searchWord.Trim();
				searchWord.ToLower();
				
				if (searchWord == "" || entry.Contains(searchWord) || entry == searchWord)
				{
					tlbPlayerList.AddItem(playerKey.playerName + " " + "(" + playerKey.playerId + ")", playerKey, 0);
				}
			}
		}
		tlbPlayerList.Update();
	}
	
	void UpdatePlayerData(GAREALeaderboardPlayer gareaLeaderboardPlayer)
	{
		if (gareaLeaderboardPlayer)
		{
			// Player data
			// General
			if (gareaLeaderboardPlayer.playerIsOnline)
			{
				pPlayerOnline.SetColor(ARGB(255, 0, 255, 0));
			}
			else
			{
				pPlayerOnline.SetColor(ARGB(255, 255, 0, 0));
			}
			tPlayerName.SetText("" + gareaLeaderboardPlayer.playerName + " " + "(" + gareaLeaderboardPlayer.playerId + ")", true);
			tPlayerDeaths.SetText("" + gareaLeaderboardPlayer.playerDeaths);
			tPlayerSurvivedTime.SetText("" + gareaLeaderboardPlayer.surviedTime);
			// PVP
			tPlayerKills.SetText("" + gareaLeaderboardPlayer.playerKills);
			tPlayerLongestDistance.SetText("" + gareaLeaderboardPlayer.playerLongestDistance);
			// PVE 	
			// AI Survivor
			tPlayerKillsAISurvivor.SetText("" + gareaLeaderboardPlayer.playerKillsAISurvivor);
			// Zombie
			tPlayerKillsZombie.SetText("" + gareaLeaderboardPlayer.playerKillsZombie);
			// Bear
			tPlayerKillsBear.SetText("" + gareaLeaderboardPlayer.playerKillsBear);
			// Wolf
			tPlayerKillsWolf.SetText("" + gareaLeaderboardPlayer.playerKillsWolf);
			// Wild boar
			tPlayerKillsWildBoar.SetText("" + gareaLeaderboardPlayer.playerKillsWildBoar);
			// Red deer
			tPlayerKillsRedDeer.SetText("" + gareaLeaderboardPlayer.playerKillsRedDeer);
			// Roe deer
			tPlayerKillsRoeDeer.SetText("" + gareaLeaderboardPlayer.playerKillsRoeDeer);
			// Sheep
			tPlayerKillsSheep.SetText("" + gareaLeaderboardPlayer.playerKillsSheep);
			// Goat
			tPlayerKillsGoat.SetText("" + gareaLeaderboardPlayer.playerKillsGoat);
			// Cow
			tPlayerKillsCow.SetText("" + gareaLeaderboardPlayer.playerKillsCow);
			// Pig
			tPlayerKillsPig.SetText("" + gareaLeaderboardPlayer.playerKillsPig);
			// Chicken
			tPlayerKillsChicken.SetText("" + gareaLeaderboardPlayer.playerKillsChicken);
			// Animal
			tPlayerKillsAnimal.SetText("" + gareaLeaderboardPlayer.playerKillsAnimals, true);
			// Total
			tPlayerKillsNPCTotal.SetText("" + gareaLeaderboardPlayer.playerKillsNPCs, true);
			
			pPlayerEntry.Show(true);
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
		GAREALeaderboardPlayerKey gareaLeaderboardPlayerKey;
		bool retVal = super.OnClick(w, x, y, button);		
		switch(w)
		{
			case bReloadConfig:			
				// Reload config
				Close();
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminReloadConfig", null, true);
				return true;
			break;
			case bReloadAllPlayerFiles:
				// Reload all player files
				Close();
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminReloadAllPlayerFiles", null, true);
				return true;
			break;
			case bResetAllPlayersPVP:
				// Reset all players PVP
				pPlayerEntry.Show(false);
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetAllPlayersPVP", null, true);
				return true;
			break;
			case bResetAllPlayersPVE:
				// Reset all players PVE
				pPlayerEntry.Show(false);
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminResetAllPlayersPVE", null, true);
				return true;
			break;
			case bDeleteObsoletePlayers:
				// Delete obsolete players
				Close();
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminDeleteObsoletePlayers", null, true);
				return true;
			break;
			case bResetPlayerDeaths:
				// Reset Deaths
				tPlayerDeaths.SetText("0");
				return true;
			break;
			case bResetPlayerSurvivalTime:
				// Reset SurivalTime
				tPlayerSurvivedTime.SetText("0");
				return true;
			break;
			case bResetPlayerPVP:
				// Reset PVP
				tPlayerKills.SetText("0");
				tPlayerLongestDistance.SetText("0");
				return true;
			break;	
			case bResetPlayerPVE:
				// Reset PVE
				// AI Survivor
				tPlayerKillsAISurvivor.SetText("0");
				// Zombie
				tPlayerKillsZombie.SetText("0");
				// Bear
				tPlayerKillsBear.SetText("0");
				// Wolf
				tPlayerKillsWolf.SetText("0");
				// Wild boar
				tPlayerKillsWildBoar.SetText("0");
				// Red deer
				tPlayerKillsRedDeer.SetText("0");
				// Roe deer
				tPlayerKillsRoeDeer.SetText("0");
				// Sheep
				tPlayerKillsSheep.SetText("0");
				// Goat
				tPlayerKillsGoat.SetText("0");
				// Cow
				tPlayerKillsCow.SetText("0");
				// Pig
				tPlayerKillsPig.SetText("0");
				// Chicken
				tPlayerKillsChicken.SetText("0");		
				// Animal
				tPlayerKillsAnimal.SetText("0");
				// Total
				tPlayerKillsNPCTotal.SetText("0");
				return true;
			break;			
			case bSavePlayer:				
				// Update player
				tlbPlayerList.GetItemData(tlbPlayerListSelectedRow, tlbPlayerListSelectedColumn, gareaLeaderboardPlayerKey);
			
				GAREALeaderboardPlayer gareaLeaderboardPlayer = new GAREALeaderboardPlayer();
				gareaLeaderboardPlayer.playerId = gareaLeaderboardPlayerKey.playerId;
				gareaLeaderboardPlayer.playerName = gareaLeaderboardPlayerKey.playerName;
				gareaLeaderboardPlayer.playerDeaths = tPlayerDeaths.GetText().ToInt();
				gareaLeaderboardPlayer.surviedTime = tPlayerSurvivedTime.GetText().ToFloat();
				// PVP
				gareaLeaderboardPlayer.playerKills = tPlayerKills.GetText().ToInt();		
				gareaLeaderboardPlayer.playerLongestDistance = tPlayerLongestDistance.GetText().ToInt();
				// PVE
				gareaLeaderboardPlayer.playerKillsAISurvivor = tPlayerKillsAISurvivor.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsZombie = tPlayerKillsZombie.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsBear = tPlayerKillsBear.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsWolf = tPlayerKillsWolf.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsWildBoar = tPlayerKillsWildBoar.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsRedDeer = tPlayerKillsRedDeer.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsRoeDeer = tPlayerKillsRoeDeer.GetText().ToInt();	
				gareaLeaderboardPlayer.playerKillsSheep = tPlayerKillsSheep.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsGoat = tPlayerKillsGoat.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsCow = tPlayerKillsCow.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsPig = tPlayerKillsPig.GetText().ToInt();
				gareaLeaderboardPlayer.playerKillsChicken = tPlayerKillsChicken.GetText().ToInt();
			
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminUpdatePlayer", new Param1<GAREALeaderboardPlayer>(gareaLeaderboardPlayer), true);
				return true;
			break;
			case bDeletePlayer:
				// Delete player
				tlbPlayerList.GetItemData(tlbPlayerListSelectedRow, tlbPlayerListSelectedColumn, gareaLeaderboardPlayerKey);
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminDeletePlayer", new Param1<GAREALeaderboardPlayerKey>(gareaLeaderboardPlayerKey), true);
				playerKeys.RemoveItem(gareaLeaderboardPlayerKey);
				tlbPlayerList.RemoveRow(tlbPlayerListSelectedRow);
				pPlayerEntry.Show(false);
				return true;
			break;
			case bPVP:
				Close();
			
				// Show pvp leaderboard
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVP", null, true);
				return true;
			break;
			case bPVE:
				Close();
			
				// Show pve leaderboard
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVE", null, true);
				return true;
			break;
			case bClose:
				// Close gui when X button was clicked
				Close();
				return true;
			break;
		}
		return retVal;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		bool retVal = super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
		pPlayerEntry.Show(false, true);
		tlbPlayerListSelectedRow = row;
		tlbPlayerListSelectedColumn = column;
		return retVal;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		bool retVal = super.OnDoubleClick(w, x, y, button);
		switch(w.ClassName())
		{
			case "TextListboxWidget":			
				// Send request for admin				
				GAREALeaderboardPlayerKey gareaLeaderboardPlayerKey;
				tlbPlayerList.GetItemData(tlbPlayerListSelectedRow, tlbPlayerListSelectedColumn, gareaLeaderboardPlayerKey);
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdminGetPlayer", new Param1<GAREALeaderboardPlayerKey>(gareaLeaderboardPlayerKey), true);
			break;
		}
		return retVal;
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		bool retVal = super.OnChange(w, x, y, finished);
		switch(w.ClassName())
		{
			case "EditBoxWidget":
				if (w != ebSearch)
			 	{
					int playerKillsAISurvivor = tPlayerKillsAISurvivor.GetText().ToInt();
					int playerKillsZombie = tPlayerKillsZombie.GetText().ToInt();
					int playerKillsBear = tPlayerKillsBear.GetText().ToInt();
					int playerKillsWolf = tPlayerKillsWolf.GetText().ToInt();
					int playerKillsWildBoar = tPlayerKillsWildBoar.GetText().ToInt();
					int playerKillsRedDeer = tPlayerKillsRedDeer.GetText().ToInt();
					int playerKillsRoeDeer = tPlayerKillsRoeDeer.GetText().ToInt();	
					int playerKillsSheep = tPlayerKillsSheep.GetText().ToInt();
					int playerKillsGoat = tPlayerKillsGoat.GetText().ToInt();
					int playerKillsCow = tPlayerKillsCow.GetText().ToInt();
					int playerKillsPig = tPlayerKillsPig.GetText().ToInt();
					int playerKillsChicken = tPlayerKillsChicken.GetText().ToInt();
					
					int animalKills = 0;
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
					
					int npcKills = 0;
					npcKills += playerKillsZombie;
					npcKills += playerKillsAISurvivor;
					npcKills += animalKills;
				
					// Animal
					tPlayerKillsAnimal.SetText("" + animalKills, true);	
					// Total
					tPlayerKillsNPCTotal.SetText("" + npcKills, true);
				} else if (w == ebSearch) {
					FilterPlayerList(ebSearch.GetText());
				}
			break;
		}
		return retVal;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		bool retVal = super.OnMouseEnter(w, x, y);
		switch(w.ClassName())
		{
			case "EditBoxWidget":
				typing = true;
			break;
		}
		return retVal;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		bool retVal = super.OnMouseLeave(w, enterW, x, y);
		switch(w.ClassName())
		{
			case "EditBoxWidget":
				typing = false;
			break;
		}
		return retVal;
	}
}