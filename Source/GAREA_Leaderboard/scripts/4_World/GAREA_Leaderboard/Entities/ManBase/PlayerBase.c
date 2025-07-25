modded class PlayerBase extends ManBase
{
	private EntityAI gareaLastHitSource;
	private string gareaPlayerSteamId;
	string gareaPlayerUnconsicousKillerSteamId;
	string gareaPlayerUnconsicousKillerPlayerName;
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			gareaLastHitSource = source;
        	super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		}
    }
	
	override void OnUnconsciousStart()
    {
        if (gareaLastHitSource)
        {		
            Man man = gareaLastHitSource.GetHierarchyRootPlayer();
			if (!man)
			{
				BearTrap bearTrap = BearTrap.Cast(gareaLastHitSource);
				if (bearTrap)
				{
					man = bearTrap.GetTrapper();
				}
			
				LandMineTrap landMineTrap = LandMineTrap.Cast(gareaLastHitSource);
				if (landMineTrap)
				{
					man = landMineTrap.GetTrapper();
				}
				
				Grenade_Base grenadeBase = Grenade_Base.Cast(gareaLastHitSource);
				if (grenadeBase)
				{
					man = grenadeBase.GetThrower();
				}
			}
			
			if (man)
			{
				PlayerBase gareaUnconsciousKiller;
				PlayerBase.CastTo(gareaUnconsciousKiller, man);
				if (gareaUnconsciousKiller)
				{
					PlayerIdentity sourceIdentity = gareaUnconsciousKiller.GetIdentity();
					if (sourceIdentity)
					{
						gareaPlayerUnconsicousKillerSteamId = sourceIdentity.GetPlainId();
						gareaPlayerUnconsicousKillerPlayerName = sourceIdentity.GetName();
					}
				}
			}
        }
        super.OnUnconsciousStart();
    }

    override void OnUnconsciousStop(int pCurrentCommandID)
    {
        if (pCurrentCommandID != DayZPlayerConstants.COMMANDID_DEATH)
        {
            gareaPlayerUnconsicousKillerSteamId = "";
			gareaPlayerUnconsicousKillerPlayerName = "";
        }
        super.OnUnconsciousStop(pCurrentCommandID);
    }
	
    override void EEKilled(Object killer)
    {
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			GAREALeaderboardManager.GetInstance().UpdatePlayerStats(this, killer);
		}
		super.EEKilled(killer);
	}
	
	override void OnConnect()
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			PlayerIdentity identity = GetIdentity();
			if (identity)
			{
				gareaPlayerSteamId = identity.GetPlainId();
				GAREALeaderboardManager.GetInstance().OnPlayerConnect(this);
			}
		}
		super.OnConnect();
	}
	
	override void OnDisconnect()
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			GAREALeaderboardManager.GetInstance().OnPlayerDisconnect(gareaPlayerSteamId);
		}
		super.OnDisconnect();
	}
}
