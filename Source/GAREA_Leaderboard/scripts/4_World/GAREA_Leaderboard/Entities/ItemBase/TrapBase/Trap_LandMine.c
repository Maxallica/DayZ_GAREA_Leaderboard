modded class LandMineTrap extends LandMineTrap
{
	private vector startPosition;
	private PlayerBase trapper;

	override void StartActivate(PlayerBase player)
	{
		PlayerIdentity identity = player.GetIdentity();
		if (identity)
		{
			trapper = player;
		}
		startPosition = player.GetPosition();
		super.StartActivate(player);
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