modded class AnimalBase extends DayZAnimal
{
	// Workaround to get accurate last object
	private EntityAI gareaLastHitSource;
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			gareaLastHitSource = source;
			super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		}
	}
	
	// Server function
    override void EEKilled(Object killer)
    {
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			// Workaround to get accurate last object
			Object killSource = killer;
			if (this == killer && gareaLastHitSource != null && killer != gareaLastHitSource)
			{
				killSource = gareaLastHitSource;
			}

			GAREALeaderboardManager.GetInstance().UpdatePlayerStats(this, killSource);
		}
		super.EEKilled(killer);
	}
}