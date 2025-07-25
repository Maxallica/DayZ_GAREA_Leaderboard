class GAREALeaderboardObjectUtils
{
    static void GetTargetType(Object target, out string targetType)
	{
		if (target)
		{
			if (target.IsInherited(PlayerBase))
			{
				targetType = "Player";
			}
			else if (target.IsInherited(DayZAnimal))
			{
				targetType = "Animal";
			}
			else if (target.IsInherited(DayZInfected))
			{
				targetType = "Zombie";
			}
		}
	}
	
	static void GetSourceType(Object source, out string sourceType)
	{
		if (source)
		{
			if (source.IsInherited(Grenade_Base))
			{
				sourceType = "Grenade";
		    }
			else if (source.IsInherited(TrapBase))
			{
		    	sourceType = "Trap";
		    }
			else if (source.IsInherited(DayZInfected))
			{
				sourceType = "Zombie";
			}
			else if (source.IsInherited(DayZAnimal))
			{
				sourceType = "Animal";
		    }
			else if (source.IsInherited(CarScript))
			{
				sourceType = "Car";
		    }
			else if (source.IsWeapon() || source.IsMeleeWeapon())
			{
				sourceType = "Weapon";
		    }
			else if (source.IsMan())
			{
		        sourceType = "Unarmed";
		    }
			else
			{
		        sourceType = "Unknown";
		    }
		}		
	}
	
	static void GetRelevantData(Object target, Object source, out string targetType, out string sourceType, out string targetId, out string sourceId, out string targetName, out string sourceName, out float distance)
	{
		PlayerBase targetIsPlayer;
		AnimalBase targetIsAnimal;
		ZombieBase targetIsZombie;
		
		PlayerBase sourceIsPlayer;
		PlayerIdentity sourceIdentity;		
		
		GetTargetType(target, targetType);
		GetSourceType(source, sourceType);
		
		switch (targetType)
		{
			case "Player":				
				targetIsPlayer = PlayerBase.Cast(target);
				if (targetIsPlayer)
				{
					if (targetIsPlayer.gareaPlayerUnconsicousKillerSteamId)
					{
						sourceType = "UnconsciousSuicide";
						sourceId = targetIsPlayer.gareaPlayerUnconsicousKillerSteamId;
						sourceName = targetIsPlayer.gareaPlayerUnconsicousKillerPlayerName;
						source = null;
					}
					
					PlayerIdentity targetIdentity = targetIsPlayer.GetIdentity();
					if (targetIdentity)
					{
						targetId = targetIdentity.GetPlainId();
						targetName = targetIdentity.GetName();
					}
					else
					{
						targetType = "AI_Survivor";
					}
				}			
				
				if (target && source && target == source)
				{
					sourceType = "Suicide";
				}
				break;
			case "Animal":				
				targetIsAnimal = AnimalBase.Cast(target);			
				break;
			case "Zombie":				
				targetIsZombie = ZombieBase.Cast(target);
				break;	
		}
		
		switch (sourceType)
		{
		    case "Suicide":
				sourceIsPlayer = PlayerBase.Cast(source);
				if (sourceIsPlayer)
				{
					sourceIdentity = sourceIsPlayer.GetIdentity();
					if (sourceIdentity)
					{
						sourceId = sourceIdentity.GetPlainId();
						sourceName = sourceIdentity.GetName();
					}
				}
		      break;
		    case "Grenade":	
				Grenade_Base grenadeBase = Grenade_Base.Cast(source);
				if (grenadeBase)
				{
					sourceId = grenadeBase.GetPlainId();
					sourceName = grenadeBase.GetPlayerName();
				
					if (targetIsPlayer)
					{
						distance = vector.Distance(targetIsPlayer.GetPosition(), grenadeBase.GetStartPosition());	
					}					
				}			
		      break;
		    case "Trap":			
				BearTrap bearTrap = BearTrap.Cast(source);
				if (bearTrap)
				{
					sourceId = bearTrap.GetPlainId();
					sourceName = bearTrap.GetPlayerName();
				
					if (targetIsPlayer)
					{
						distance = vector.Distance(targetIsPlayer.GetPosition(), bearTrap.GetStartPosition());	
					}
				}
			
				LandMineTrap landMineTrap = LandMineTrap.Cast(source);
				if (landMineTrap)
				{
					sourceId = landMineTrap.GetPlainId();
					sourceName = landMineTrap.GetPlayerName();
				
					if (targetIsPlayer)
					{
						distance = vector.Distance(targetIsPlayer.GetPosition(), landMineTrap.GetStartPosition());	
					}
				}
		      break;
		    case "Zombie":
		      break;
		    case "Animal":
		      break;
		    case "Car":
				CarScript carScript = CarScript.Cast(source);
				if (carScript)
				{
					Human driver = Human.Cast(carScript.CrewMember(0));
					if (driver)
					{
						sourceIsPlayer = PlayerBase.Cast(driver);
						if (sourceIsPlayer)
						{
							sourceIdentity = sourceIsPlayer.GetIdentity();
							if (sourceIdentity)
							{
								sourceId = sourceIdentity.GetPlainId();
								sourceName = sourceIdentity.GetName();
							}
						}
					}
				}
		      break;
		    case "Weapon":
				sourceIsPlayer = PlayerBase.Cast(EntityAI.Cast(source).GetHierarchyParent());
				if (sourceIsPlayer)
				{
					sourceIdentity = sourceIsPlayer.GetIdentity();
					if (sourceIdentity)
					{
						sourceId = sourceIdentity.GetPlainId();
						sourceName = sourceIdentity.GetName();
					}
					
					if (sourceIsPlayer && targetIsPlayer)
					{
						distance = vector.Distance(targetIsPlayer.GetPosition(), sourceIsPlayer.GetPosition());	
					}
				}
		      break;
		    case "Unarmed":
				sourceIsPlayer = PlayerBase.Cast(EntityAI.Cast(source));
				if (sourceIsPlayer)
				{
					sourceIdentity = sourceIsPlayer.GetIdentity();
					if (sourceIdentity)
					{
						sourceId = sourceIdentity.GetPlainId();
						sourceName = sourceIdentity.GetName();
					}
				}
		      break;
		    case "Unknown":
				sourceIsPlayer = PlayerBase.Cast(EntityAI.Cast(source));
				if (sourceIsPlayer)
				{
					sourceIdentity = sourceIsPlayer.GetIdentity();
					if (sourceIdentity)
					{
						sourceId = sourceIdentity.GetPlainId();
						sourceName = sourceIdentity.GetName();
					}
				}
		      break;
		}
	}
}