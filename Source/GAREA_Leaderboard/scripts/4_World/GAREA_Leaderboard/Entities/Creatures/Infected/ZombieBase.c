modded class ZombieBase extends DayZInfected
{	
	// Server function
    override void EEKilled(Object killer)
    {
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			GAREALeaderboardManager.GetInstance().UpdatePlayerStats(this, killer);
		}
		super.EEKilled(killer);
	}
}
