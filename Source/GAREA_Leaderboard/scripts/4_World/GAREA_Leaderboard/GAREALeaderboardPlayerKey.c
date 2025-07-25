class GAREALeaderboardPlayerKey : RestCallback
{
    string playerId = "";
    string playerName = "";
	
	void GAREALeaderboardPlayerKey(GAREALeaderboardPlayer p, string playerId = "", string playerName = "")
    {
		this.playerId = playerId;
		this.playerName = playerName;
		
		if (p)
		{
			this.playerId = p.playerId;
			this.playerName = p.playerName;
		}
    }
}