//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
// CLASS reprezentuje FUNCTION OBJECT, pretoze definuje OPERATOR().
template<typename TType>
class CFunctionObjectFindByValue final
{
//-----------------------------------------------------------------------------
	private:
		TType													MValueToFind;

	public:
		bool operator()(const TType& Value)
		{
			if (MValueToFind==Value)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		CFunctionObjectFindByValue(const TType& ValueToFind)
			: MValueToFind(ValueToFind)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------