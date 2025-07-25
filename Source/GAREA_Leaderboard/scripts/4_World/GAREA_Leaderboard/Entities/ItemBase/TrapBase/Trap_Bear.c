modded class BearTrap extends BearTrap
{
	private vector startPosition;
	private PlayerBase trapper;

	override void OnSteppedOn(EntityAI victim)
	{
		PlayerBase player = PlayerBase.Cast(victim);
		if (player)
		{
			trapper = player;
			startPosition = player.GetPosition();
		}
		super.OnSteppedOn(victim);
	}

	vector GetStartPosition()
	{
		return startPosition;
	}
	
	Man GetTrapper()
	{
		Man man;
		if (trapper)
		{
			ManBase.CastTo(man, trapper);
		}
		return man;
	}
	
	string GetPlainId()
	{
		string plainId = "";
		if (trapper)
		{
			PlayerIdentity identity = trapper.GetIdentity();
			if (identity)
			{
				plainId = identity.GetPlainId();
			}
		}
		return plainId;
	}
	
	string GetPlayerName()
	{
		string playerName = "";
		if (trapper)
		{
			PlayerIdentity identity = trapper.GetIdentity();
			if (identity)
			{
				playerName = identity.GetName();
			}
		}
		return playerName;
	}
}