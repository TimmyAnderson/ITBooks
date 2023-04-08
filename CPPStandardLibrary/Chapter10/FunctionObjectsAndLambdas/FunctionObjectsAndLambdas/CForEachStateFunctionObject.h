//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class CForEachStateFunctionObject final
{
//-----------------------------------------------------------------------------
	private:
		int														MNumberOfItems;
		int														MSumOfValues;

	public:
		void operator()(int Value)
		{
			MNumberOfItems++;
			MSumOfValues+=Value;
		}

	public:
		int GetNumberOfItems(void) const noexcept
		{
			return(MNumberOfItems);
		}

		int GetSumOfValues(void) const noexcept
		{
			return(MSumOfValues);
		}

	public:
		CForEachStateFunctionObject(void)
			: MNumberOfItems(0), MSumOfValues(0)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------