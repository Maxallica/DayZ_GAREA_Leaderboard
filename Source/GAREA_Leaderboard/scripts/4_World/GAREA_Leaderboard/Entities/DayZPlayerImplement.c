modded class DayZPlayerImplement
{
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.CommandHandler(pDt, pCurrentCommandID, pCurrentCommandFinished);
		UAInput localInputPVP = GetUApi().GetInputByName("UAOpenGAREALeaderboardPVP");
		UAInput localInputPVE = GetUApi().GetInputByName("UAOpenGAREALeaderboardPVE");
		
		if (localInputPVP.LocalPress() || localInputPVE.LocalPress())
		{
			MissionBaseWorld mission = MissionBaseWorld.Cast(GetGame().GetMission());
			if (mission)
			{
				if (localInputPVP.LocalPress())
				{
					mission.OpenGAREALeaderboardGUIPVP();
				}
				
				if (localInputPVE.LocalPress())
				{
					mission.OpenGAREALeaderboardGUIPVE();
				}
			}				
		}
	}
}