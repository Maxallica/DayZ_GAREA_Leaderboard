class GAREALeaderboardGUIPVE extends UIScriptedMenu
{
    protected static ref GAREALeaderboardGUIPVE Instance;
	
	// Controls
	protected Widget pAdminButtons;
	protected ButtonWidget bAdmin;
	protected Widget pPVP;
	protected ButtonWidget bPVP;	
	protected ButtonWidget bClose
	
	// Titlebar
	protected TextWidget tTitle;
	protected TextWidget tPlayerOnlineCounter;
    protected TextWidget tUpdateTimestamp;
	protected TextWidget tTime;
	
	// Headers
	protected TextWidget thPlayerPos;
	protected TextWidget thPlayerName;
	protected TextWidget thPlayerDeaths;
	protected TextWidget thPlayerSurvivedTime;	
		
	protected TextWidget thPlayerKillsAISurvivor;
	protected TextWidget thPlayerKillsZombie;
	protected TextWidget thPlayerKillsAnimal;	
	protected TextWidget thPlayerKillsBear;
	protected TextWidget thPlayerKillsWolf;
	protected TextWidget thPlayerKillsWildBoar;
	protected TextWidget thPlayerKillsRedDeer;
	protected TextWidget thPlayerKillsRoeDeer;
	protected TextWidget thPlayerKillsSheep;
	protected TextWidget thPlayerKillsGoat;
	protected TextWidget thPlayerKillsCow;
	protected TextWidget thPlayerKillsPig;
	protected TextWidget thPlayerKillsChicken;
	
	protected TextWidget thPlayerKillsNPCTotal;
	protected TextWidget thPlayerPVEPoints;
	
	// Player data	
	protected TextWidget tPlayerPos;
	protected TextWidget tPlayerName;
	protected TextWidget tPlayerDeaths;
	protected TextWidget tPlayerSurvivedTime;
	
	protected Widget pPlayerKillsAISurvivor;
	protected Widget pPlayerKillsZombie;
	protected Widget pPlayerKillsAnimals;
	
	protected TextWidget tPlayerKillsAISurvivor;
	protected TextWidget tPlayerKillsZombie;
	protected TextWidget tPlayerKillsAnimal;	
	protected TextWidget tPlayerKillsBear;
	protected TextWidget tPlayerKillsWolf;
	protected TextWidget tPlayerKillsWildBoar;
	protected TextWidget tPlayerKillsRedDeer;
	protected TextWidget tPlayerKillsRoeDeer;
	protected TextWidget tPlayerKillsSheep;
	protected TextWidget tPlayerKillsGoat;
	protected TextWidget tPlayerKillsCow;
	protected TextWidget tPlayerKillsPig;
	protected TextWidget tPlayerKillsChicken;
	
	protected TextWidget tPlayerKillsNPCTotal;	
	protected TextWidget tPlayerPVEPoints;
	
	protected TextWidget tTopX;
	protected ScrollWidget swBoard;
	protected GridSpacerWidget gsBoard;
	
	bool open;
    void GAREALeaderboardGUIPVE()
    {
    }

    void ~GAREALeaderboardGUIPVE()
    {
		open = false;
		GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
	}

    static GAREALeaderboardGUIPVE GetInstance()
	{
		if (!Instance)
        {
            Instance = new GAREALeaderboardGUIPVE();
        }
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("GAREA_Leaderboard\\gui\\layouts\\gareaLeaderboard_pve.layout");
		
		// Controls
		pAdminButtons = Widget.Cast(layoutRoot.FindAnyWidget("pAdminButtons"));
		bAdmin = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bAdmin"));
		pPVP = Widget.Cast(layoutRoot.FindAnyWidget("pPVP"));
		bPVP = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bPVP"));
		bClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("bClose"));
		
		// Titlebar		
        tTitle = TextWidget.Cast(layoutRoot.FindAnyWidget("tTitle"));
		tPlayerOnlineCounter = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerOnlineCounter"));
		tUpdateTimestamp = TextWidget.Cast(layoutRoot.FindAnyWidget("tUpdateTimestamp"));
		tTime = TextWidget.Cast(layoutRoot.FindAnyWidget("tTime"));
		
		// Headers
		thPlayerPos = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerPos"));
		thPlayerName = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerName"));
		thPlayerDeaths = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerDeaths"));
		thPlayerSurvivedTime = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerSurvivedTime"));
		
		// AI Survivor
		thPlayerKillsAISurvivor = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsAISurvivor"));
		// Zombie
		thPlayerKillsZombie = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsZombie"));
		// Animal
		thPlayerKillsAnimal = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsAnimal"));
		// Bear
		thPlayerKillsBear = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsBear"));
		// Wolf
		thPlayerKillsWolf = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsWolf"));
		// Wild boar
		thPlayerKillsWildBoar = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsWildBoar"));
		// Red deer
		thPlayerKillsRedDeer = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsRedDeer"));
		// Roe deer
		thPlayerKillsRoeDeer = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsRoeDeer"));
		// Sheep
		thPlayerKillsSheep = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsSheep"));
		// Goat
		thPlayerKillsGoat = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsGoat"));
		// Cow
		thPlayerKillsCow = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsCow"));
		// Pig
		thPlayerKillsPig = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsPig"));
		// Chicken
		thPlayerKillsChicken = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsChicken"));
		
		// Total		
		thPlayerKillsNPCTotal = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerKillsNPCTotal"));
		
		// PVE Points
		thPlayerPVEPoints = TextWidget.Cast(layoutRoot.FindAnyWidget("thPlayerPVEPoints"));
		
		// Player data
		tPlayerPos = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerPos"));
		tPlayerName = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerName"));		
		tPlayerDeaths = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerDeaths"));
		tPlayerSurvivedTime = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerSurvivedTime"));
		
		pPlayerKillsAISurvivor = Widget.Cast(layoutRoot.FindAnyWidget("pPlayerKillsAISurvivor"));
		pPlayerKillsZombie = Widget.Cast(layoutRoot.FindAnyWidget("pPlayerKillsZombie"));
		pPlayerKillsAnimals = Widget.Cast(layoutRoot.FindAnyWidget("pPlayerKillsAnimals"));
		
		// AI Survivor
		tPlayerKillsAISurvivor = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsAISurvivor"));	
		// Zombie
		tPlayerKillsZombie = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsZombie"));		
		// Animal
		tPlayerKillsAnimal = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsAnimal"));					
		// Bear
		tPlayerKillsBear = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsBear"));
		// Wolf
		tPlayerKillsWolf = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsWolf"));
		// Wild boar
		tPlayerKillsWildBoar = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsWildBoar"));
		// Red deer
		tPlayerKillsRedDeer = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsRedDeer"));
		// Roe deer
		tPlayerKillsRoeDeer = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsRoeDeer"));
		// Sheep
		tPlayerKillsSheep = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsSheep"));
		// Goat
		tPlayerKillsGoat = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsGoat"));
		// Cow
		tPlayerKillsCow = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsCow"));
		// Pig
		tPlayerKillsPig = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsPig"));
		// Chicken
		tPlayerKillsChicken = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsChicken"));
		
		// Total
		tPlayerKillsNPCTotal = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerKillsNPCTotal"));
		
		// PVE Points
		tPlayerPVEPoints = TextWidget.Cast(layoutRoot.FindAnyWidget("tPlayerPVEPoints"));
		
		tTopX = TextWidget.Cast(layoutRoot.FindAnyWidget("tTopX"));
		swBoard = ScrollWidget.Cast(layoutRoot.FindAnyWidget("swBoard"));
		swBoard.HScrollToPos01(0);
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
			pPVP.Show(true);
			if (gareaLeaderboardConfig.disablePVPLeaderboard)
			{
				pPVP.Show(false);
			}
			
			string includeAISurvivorFor = gareaLeaderboardConfig.includeAISurvivorFor;
			string includeAISurvivorForPVE = "pve";
			string includeAISurvivorForBOTH = "both";
			
			GAREALeaderboardPlayerPVE requestedPlayer = gareaLeaderboard.requestedPlayerPVE;		
			
			tPlayerOnlineCounter.SetText("Online " + gareaLeaderboard.playerOnlineCounter);
			tUpdateTimestamp.SetText(gareaLeaderboardConfig.updateTimestampPVE);			
			tTime.SetText("" + GAREALeaderboardUtils.GetTime());
			tTopX.SetText("Top " + gareaLeaderboardConfig.playerDisplaySize);
			
			// Translation header
			tTitle.SetText(gareaLeaderboardConfig.tTitle);
			thPlayerPos.SetText(gareaLeaderboardConfig.thPlayerPos);
			thPlayerName.SetText(gareaLeaderboardConfig.thPlayerName);
			thPlayerDeaths.SetText(gareaLeaderboardConfig.thPlayerDeaths);
			
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
			tPlayerDeaths.SetText("" + requestedPlayer.playerDeaths);
			
			if (gareaLeaderboardConfig.showSurvivedTimeFor == "yourself" || gareaLeaderboardConfig.showSurvivedTimeFor == "all")
			{
				tPlayerSurvivedTime.SetText("" + requestedPlayer.GetSurvivedTimeAsString(gareaLeaderboardConfig));
			}
			
			pPlayerKillsAISurvivor.Show(false);
			if (includeAISurvivorFor == includeAISurvivorForPVE || includeAISurvivorFor == includeAISurvivorForBOTH)
			{
				// AI Survivors
				tPlayerKillsAISurvivor.SetText("" + requestedPlayer.playerKillsAISurvivor);
									
				// Translation header
				thPlayerKillsAISurvivor.SetText(gareaLeaderboardConfig.thPlayerKillsAISurvivor);
				pPlayerKillsAISurvivor.Show(true);
			}
			
			pPlayerKillsZombie.Show(false);
			if (!gareaLeaderboardConfig.disableKillOfZombie)
			{
				// Zombies
				tPlayerKillsZombie.SetText("" + requestedPlayer.playerKillsZombie);
									
				// Translation header
				thPlayerKillsZombie.SetText("" + gareaLeaderboardConfig.thPlayerKillsZombie);
				pPlayerKillsZombie.Show(true);
			}
			
			pPlayerKillsAnimals.Show(false);
			if (!gareaLeaderboardConfig.disableKillOfAnimal)
			{
				// Animals
				tPlayerKillsAnimal.SetText("" + requestedPlayer.playerKillsAnimals);
				// Bear
				tPlayerKillsBear.SetText("" + requestedPlayer.playerKillsBear);
				// Wolf
				tPlayerKillsWolf.SetText("" + requestedPlayer.playerKillsWolf);
				// Wild boar
				tPlayerKillsWildBoar.SetText("" + requestedPlayer.playerKillsWildBoar);
				// Red deer
				tPlayerKillsRedDeer.SetText("" + requestedPlayer.playerKillsRedDeer);
				// Roe deer
				tPlayerKillsRoeDeer.SetText("" + requestedPlayer.playerKillsRoeDeer);
				// Sheep
				tPlayerKillsSheep.SetText("" + requestedPlayer.playerKillsSheep);
				// Goat
				tPlayerKillsGoat.SetText("" + requestedPlayer.playerKillsGoat);
				// Cow
				tPlayerKillsCow.SetText("" + requestedPlayer.playerKillsCow);
				// Pig
				tPlayerKillsPig.SetText("" + requestedPlayer.playerKillsPig);
				// Chicken
				tPlayerKillsChicken.SetText("" + requestedPlayer.playerKillsChicken);
				
				// Translation header
				thPlayerKillsAnimal.SetText("" + gareaLeaderboardConfig.thPlayerKillsAnimal);
				// Bear
				thPlayerKillsBear.SetText("" + gareaLeaderboardConfig.thBears);
				// Wolf
				thPlayerKillsWolf.SetText("" + gareaLeaderboardConfig.thWolves);
				// Wild boar
				thPlayerKillsWildBoar.SetText("" + gareaLeaderboardConfig.thWildBoars);
				// Red deer
				thPlayerKillsRedDeer.SetText("" + gareaLeaderboardConfig.thRedDeers);
				// Roe deer
				thPlayerKillsRoeDeer.SetText("" + gareaLeaderboardConfig.thRoeDeers);
				// Sheep
				thPlayerKillsSheep.SetText("" + gareaLeaderboardConfig.thSheeps);
				// Goat
				thPlayerKillsGoat.SetText("" + gareaLeaderboardConfig.thGoats);
				// Cow
				thPlayerKillsCow.SetText("" + gareaLeaderboardConfig.thCows);
				// Pig
				thPlayerKillsPig.SetText("" + gareaLeaderboardConfig.thPigs);
				// Chicken
				thPlayerKillsChicken.SetText("" + gareaLeaderboardConfig.thChicken);
				pPlayerKillsAnimals.Show(true);
			}
			
			// TOtal
			tPlayerKillsNPCTotal.SetText("" + requestedPlayer.playerKillsNPCs);
			thPlayerKillsNPCTotal.SetText("" + gareaLeaderboardConfig.thKillsNPCTotal);
			
			// PVE Points
			tPlayerPVEPoints.SetText("" + requestedPlayer.GetPVEPoints());
			thPlayerPVEPoints.SetText("" + gareaLeaderboardConfig.thPlayerPoints);
			
			// Admin
			pAdminButtons.Show(false);
			if (gareaLeaderboard.IsRequestedPlayerAnAdminPVE())
			{
				pAdminButtons.Show(true);
			}
			
			// Top x players
			array<GAREALeaderboardPlayerPVE> topXPlayersPVE = gareaLeaderboard.topXPlayersPVE;
			for (int i = 0; i < topXPlayersPVE.Count(); i++)
			{
				Widget fGAREALeaderboardEntry = GetGame().GetWorkspace().CreateWidgets( "GAREA_Leaderboard\\gui\\layouts\\gareaLeaderboard_entry_pve.layout" );
								
				GAREALeaderboardPlayerPVE gareaLeaderboardPlayer = topXPlayersPVE.Get(i);
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
					
					// Player deaths
					TextWidget tPlayerDeaths = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerDeaths"));
					tPlayerDeaths.SetText("" + gareaLeaderboardPlayer.playerDeaths);
					if (yourself)
					{
						tPlayerDeaths.SetColor(ARGB(255, 0, 0, 0));
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
					
					// AI Survivor
					TextWidget tPlayerKillsAISurvivor = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsAISurvivor"));
					tPlayerKillsAISurvivor.Show(false);
					if (includeAISurvivorFor == includeAISurvivorForPVE || includeAISurvivorFor == includeAISurvivorForBOTH)
					{
						tPlayerKillsAISurvivor.SetText("" + gareaLeaderboardPlayer.playerKillsAISurvivor);
						if (yourself)
						{
							tPlayerKillsAISurvivor.SetColor(ARGB(255, 0, 0, 0));
						}
						tPlayerKillsAISurvivor.Show(true);
					}
					
					// Zombie
					TextWidget tPlayerKillsZombie = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsZombie"));
					tPlayerKillsZombie.Show(false);
					if (!gareaLeaderboardConfig.disableKillOfZombie)
					{							
						tPlayerKillsZombie.SetText("" + gareaLeaderboardPlayer.playerKillsZombie);
						if (yourself)
						{
							tPlayerKillsZombie.SetColor(ARGB(255, 0, 0, 0));
						}
						tPlayerKillsZombie.Show(true);
					}
					
					TextWidget tPlayerKillsAnimal = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsAnimal"));
					TextWidget tPlayerKillsBear = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsBear"));
					TextWidget tPlayerKillsWolf = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsWolf"));
					TextWidget tPlayerKillsWildBoar = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsWildBoar"));
					TextWidget tPlayerKillsRedDeer = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsRedDeer"));
					TextWidget tPlayerKillsRoeDeer = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsRoeDeer"));
					TextWidget tPlayerKillsSheep = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsSheep"));
					TextWidget tPlayerKillsGoat = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsGoat"));
					TextWidget tPlayerKillsCow = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsCow"));
					TextWidget tPlayerKillsPig = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsPig"));
					TextWidget tPlayerKillsChicken = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsChicken"));
					
					tPlayerKillsAnimal.Show(false);
					tPlayerKillsBear.Show(false);
					tPlayerKillsWolf.Show(false);
					tPlayerKillsWildBoar.Show(false);
					tPlayerKillsRedDeer.Show(false);
					tPlayerKillsRoeDeer.Show(false);
					tPlayerKillsSheep.Show(false);
					tPlayerKillsGoat.Show(false);
					tPlayerKillsCow.Show(false);
					tPlayerKillsPig.Show(false);
					tPlayerKillsChicken.Show(false);
					if (!gareaLeaderboardConfig.disableKillOfAnimal)
					{
						// Animal						
						tPlayerKillsAnimal.SetText("" + gareaLeaderboardPlayer.playerKillsAnimals);
						if (yourself)
						{
							tPlayerKillsAnimal.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Bear
						tPlayerKillsBear.SetText("" + gareaLeaderboardPlayer.playerKillsBear);
						if (yourself)
						{
							tPlayerKillsBear.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Wolf
						tPlayerKillsWolf.SetText("" + gareaLeaderboardPlayer.playerKillsWolf);
						if (yourself)
						{
							tPlayerKillsWolf.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Wild boar
						tPlayerKillsWildBoar.SetText("" + gareaLeaderboardPlayer.playerKillsWildBoar);
						if (yourself)
						{
							tPlayerKillsWildBoar.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Red deer
						tPlayerKillsRedDeer.SetText("" + gareaLeaderboardPlayer.playerKillsRedDeer);
						if (yourself)
						{
							tPlayerKillsRedDeer.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Roe deer
						tPlayerKillsRoeDeer.SetText("" + gareaLeaderboardPlayer.playerKillsRoeDeer);
						if (yourself)
						{
							tPlayerKillsRoeDeer.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Sheep
						tPlayerKillsSheep.SetText("" + gareaLeaderboardPlayer.playerKillsSheep);
						if (yourself)
						{
							tPlayerKillsSheep.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Goat
						tPlayerKillsGoat.SetText("" + gareaLeaderboardPlayer.playerKillsGoat);;
						if (yourself)
						{
							tPlayerKillsGoat.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Cow						
						tPlayerKillsCow.SetText("" + gareaLeaderboardPlayer.playerKillsCow);
						if (yourself)
						{
							tPlayerKillsCow.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Pig						
						tPlayerKillsPig.SetText("" + gareaLeaderboardPlayer.playerKillsPig);
						if (yourself)
						{
							tPlayerKillsPig.SetColor(ARGB(255, 0, 0, 0));
						}
						
						// Chicken
						tPlayerKillsChicken.SetText("" + gareaLeaderboardPlayer.playerKillsChicken);
						if (yourself)
						{
							tPlayerKillsChicken.SetColor(ARGB(255, 0, 0, 0));
						}
						
						tPlayerKillsAnimal.Show(true);
						tPlayerKillsBear.Show(true);
						tPlayerKillsWolf.Show(true);
						tPlayerKillsWildBoar.Show(true);
						tPlayerKillsRedDeer.Show(true);
						tPlayerKillsRoeDeer.Show(true);
						tPlayerKillsSheep.Show(true);
						tPlayerKillsGoat.Show(true);
						tPlayerKillsCow.Show(true);
						tPlayerKillsPig.Show(true);
						tPlayerKillsChicken.Show(true);
					}
					
					// Total
					TextWidget tPlayerKillsNPCTotal = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerKillsNPCTotal"));
					tPlayerKillsNPCTotal.SetText("" + gareaLeaderboardPlayer.playerKillsNPCs);
					if (yourself)
					{
						tPlayerKillsNPCTotal.SetColor(ARGB(255, 0, 0, 0));
					}
					
					TextWidget tPlayerPVEPoints = TextWidget.Cast(fGAREALeaderboardEntry.FindAnyWidget("tPlayerPVEPoints"));
					tPlayerPVEPoints.SetText("" + gareaLeaderboardPlayer.GetPVEPoints());
					if (yourself)
					{
						tPlayerPVEPoints.SetColor(ARGB(255, 0, 0, 0));
					}
					
					gsBoard.AddChild(fGAREALeaderboardEntry);
				}
			};
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
		bool retVal = super.OnClick(w, x, y, button);		
		switch(w)
		{
			case bAdmin:
				Close();
			
				// Send request for admin
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardAdmin", null, true);			
				return true;
			break;
			case bPVP:
				Close();
			
				// Send request for pvp
				GetRPCManager().SendRPC("GAREA_Leaderboard", "RPCRequestGAREALeaderboardPVP", null, true);
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
}
