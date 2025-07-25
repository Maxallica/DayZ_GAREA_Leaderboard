modded class ActionUnpin extends ActionUnpin
{	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		vector position = player.GetPosition();		
		Grenade_Base grenade = Grenade_Base.Cast(item);
		if (grenade)
		{
			grenade.SetAdditionalInfos(position, player);
		}
		return super.ActionCondition(player, target, item);
	}
}

modded class Grenade_Base extends Grenade_Base
{
	private vector startPosition;
	private Man thrower;
	
	void SetAdditionalInfos(vector startPosition, PlayerBase thrower)
	{
		this.startPosition = startPosition;
		this.thrower = thrower;
	}
	
	vector GetStartPosition()
	{
		return startPosition;
	}
	
	string GetPlainId()
	{
		string plainId = "";
		if (thrower)
		{
			PlayerIdentity identity = thrower.GetIdentity();		
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
		if (thrower)
		{
			PlayerIdentity identity = thrower.GetIdentity();
			if (identity)
			{
				playerName = identity.GetName();
			}
		}
		return playerName;
	}
	
	Man GetThrower()
	{
		Man man;
		if (thrower)
		{
			ManBase.CastTo(man, thrower);
		}
		return man;
	}
	
	override protected void OnUnpin()
    {
        super.OnUnpin();
		this.thrower = GetHierarchyRootPlayer();
    }

    override protected void OnPin()
    {
        super.OnPin();
        this.thrower = null;
    }
}