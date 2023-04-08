//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TOuterType>
class COuterClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		TOuterType												MOuterValue;

	public:
		template<typename TInnerType>
		class CInnerClass
		{
			private:
				TInnerType										MInnerValue;

			public:
				TInnerType GetValue(void)
				{
					return(MInnerValue);
				}

			public:
				CInnerClass(TInnerType InnerValue)
					: MInnerValue(InnerValue)
				{
				}
		};

	public:
		TOuterType GetValue(void)
		{
			return(MOuterValue);
		}

	public:
		COuterClass(TOuterType OuterValue)
			: MOuterValue(OuterValue)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------