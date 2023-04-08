//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CStore
{
	private:
		TType													MValue;

	public:
		TType GetValue(void)
		{
			wprintf_s(L"TType GetValue(void) CALLED !\n");

			return(MValue);
		}

	public:
		CStore(TType Value)
			: MValue(Value)
		{
		}

		virtual ~CStore(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------