class GAREALeaderboard : RestCallback
{	
	// Requested PlayerState
	int requestedPlayerPosition;
	GAREALeaderboardPlayerPVP requestedPlayerPVP;
	GAREALeaderboardPlayerPVE requestedPlayerPVE;
	
	// Global data
	int playerOnlineCounter;
	GAREALeaderboardConfig gareaLeaderboardConfig;
	ref array<GAREALeaderboardPlayerPVP> topXPlayersPVP;
	ref array<GAREALeaderboardPlayerPVE> topXPlayersPVE;
	
    void GAREALeaderboard()
    {
		topXPlayersPVP = new array<GAREALeaderboardPlayerPVP>;
		topXPlayersPVE = new array<GAREALeaderboardPlayerPVE>;
    }
	
	bool IsRequestedPlayerAnAdminPVP()
	{
		if (gareaLeaderboardConfig && requestedPlayerPVP)
		{
			array<string> adminIds = gareaLeaderboardConfig.adminIds;
			for (int i = 0; i < adminIds.Count(); i++)
			{
				string adminId = adminIds.Get(i);
				if (requestedPlayerPVP.playerId == adminId)
				{
					return true;
				}
			}
		}
		return false;
	}
	
	bool IsRequestedPlayerAnAdminPVE()
	{
		if (gareaLeaderboardConfig && requestedPlayerPVE)
		{
			array<string> adminIds = gareaLeaderboardConfig.adminIds;
			for (int i = 0; i < adminIds.Count(); i++)
			{
				string adminId = adminIds.Get(i);
				if (requestedPlayerPVE.playerId == adminId)
				{
					return true;
				}
			}
		}
		return false;
	}
}