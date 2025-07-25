class GAREALeaderboardUtils
{
    static string GetTimestamp(string dateTimeFormat = "%1.%2.%3 %4:%5:%6")
	{
		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		int second = 0;

		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		return string.Format(dateTimeFormat, day.ToStringLen(2), month.ToStringLen(2), year.ToStringLen(4), hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
	}
	
	static string GetTime(bool withSeconds = false)
	{
		string dateTimeFormat = "";		
		int hour = 0;
		int minute = 0;
		int second = 0;
		GetHourMinuteSecond(hour, minute, second);
		
		if (withSeconds)
		{
			dateTimeFormat = "%1:%2:%3";
			return string.Format(dateTimeFormat, hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
		}
		else
		{
			dateTimeFormat = "%1:%2";
			return string.Format(dateTimeFormat, hour.ToStringLen(2), minute.ToStringLen(2));
		}
	}
}