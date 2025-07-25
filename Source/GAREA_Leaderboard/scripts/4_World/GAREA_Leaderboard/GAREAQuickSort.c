class GAREAQuickSort
{
	protected ref array<GAREALeaderboardPlayer> sortedArray;
    
    void GAREAQuickSort(ref array<GAREALeaderboardPlayer> arr)
    {
        sortedArray = new ref array<GAREALeaderboardPlayer>();
		sortedArray.InsertAll(arr);
    }
	
	array<GAREALeaderboardPlayer> GetSortedList(string order = "asc")
	{
		int count = 0;
		GAREALeaderboardPlayer p;
		if (order == "desc")
		{
			
			count = sortedArray.Count();
			ref array<GAREALeaderboardPlayer> reversedSortedArray = new array<GAREALeaderboardPlayer>();
			for (int i = count; i > 0; i--)
			{
				p = sortedArray[i - 1];
				reversedSortedArray.Insert(p);
			}
			return reversedSortedArray;
		}
		else
		{
			return sortedArray;
		}
	}
	
	protected int intCopare(int x, int y)
	{
		int value = 0;
		if (x == y)
		{
			value = 0;
		}
		
		if (x < y)
		{
			value = -1;
		}
		
		if (x > y)
		{
			value = 1;
		}
		return value;
	}
	
	void QuickSortByPVPPoints(int left, int right)
    {
        int i = left;
		int j = right;
		
        GAREALeaderboardPlayer pivot = sortedArray[(left + right)/2];
		
        while (i <= j)
        {			
			while (intCopare(sortedArray[i].GetPVPPoints(), pivot.GetPVPPoints()) < 0)
            {
                i++;
            }

			while (intCopare(sortedArray[j].GetPVPPoints(), pivot.GetPVPPoints()) > 0)
            {
                j--;
            }
			
			if (i <= j)
            {
                // Swap
                GAREALeaderboardPlayer tmp = sortedArray[i];
                sortedArray[i] = sortedArray[j];
                sortedArray[j] = tmp;

                i++;
                j--;
            }
        }
		
		// Recursive calls
		if (left < j)
        {
            QuickSortByPVPPoints(left, j);
        }

        if (i < right)
        {
            QuickSortByPVPPoints(i, right);
        }
    }
	
	void QuickSortByPVEPoints(int left, int right)
    {
        int i = left;
		int j = right;
		
        GAREALeaderboardPlayer pivot = sortedArray[(left + right)/2];
		
        while (i <= j)
        {			
			while (intCopare(sortedArray[i].GetPVEPoints(), pivot.GetPVEPoints()) < 0)
            {
                i++;
            }

			while (intCopare(sortedArray[j].GetPVEPoints(), pivot.GetPVEPoints()) > 0)
            {
                j--;
            }
			
			if (i <= j)
            {
                // Swap
                GAREALeaderboardPlayer tmp = sortedArray[i];
                sortedArray[i] = sortedArray[j];
                sortedArray[j] = tmp;

                i++;
                j--;
            }
        }
		
		// Recursive calls
		if (left < j)
        {
            QuickSortByPVEPoints(left, j);
        }

        if (i < right)
        {
            QuickSortByPVEPoints(i, right);
        }
    }
	
	void QuickSortByName(int left, int right)
    {
        int i = left;
		int j = right;
		
        GAREALeaderboardPlayer pivot = sortedArray[(left + right)/2];
		
        while (i <= j)
        {			
			while (sortedArray[i].playerName < pivot.playerName)
            {
                i++;
            }

			while (sortedArray[j].playerName > pivot.playerName)
            {
                j--;
            }
			
			if (i <= j)
            {
                // Swap
                GAREALeaderboardPlayer tmp = sortedArray[i];
                sortedArray[i] = sortedArray[j];
                sortedArray[j] = tmp;

                i++;
                j--;
            }
        }
		
		// Recursive calls
		if (left < j)
        {
            QuickSortByName(left, j);
        }

        if (i < right)
        {
            QuickSortByName(i, right);
        }
    }
}