static void GAREALeaderboard_ResetAllPlayersPVP(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
{
	if (GetGame().IsServer() || !GetGame().IsMultiplayer())
	{
		bool saveImmediately = true;
		GAREALeaderboardManager.GetInstance().ResetAllPlayers(true, false, saveImmediately);
		GAREALeaderboardConfig.GetInstance().UpdateUpdateTimestampPVP("", saveImmediately);
		GAREALeaderboardManager.GetInstance().SaveAllPlayers();
	}
}

static void GAREALeaderboard_ResetAllPlayersPVE(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
{
	if (GetGame().IsServer() || !GetGame().IsMultiplayer())
	{
		bool saveImmediately = true;
		GAREALeaderboardManager.GetInstance().ResetAllPlayers(false, true, saveImmediately);
		GAREALeaderboardConfig.GetInstance().UpdateUpdateTimestampPVE("", saveImmediately);
		GAREALeaderboardManager.GetInstance().SaveAllPlayers();
	}
}