//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class CWrongStatefulPredicate final
{
//-----------------------------------------------------------------------------
	private:
		int														MIndexToCheck;
		int														MCounter;

	public:
		// Vrati TRUE pre INDEX s poradovym cislom 'MIndexToCheck'.
		bool operator()(int)
		{
			MCounter++;

			if (MCounter==MIndexToCheck)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		CWrongStatefulPredicate(int IndexToCheck)
			: MIndexToCheck(IndexToCheck), MCounter(0)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------