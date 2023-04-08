//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! Je to VIRTUAL CLASS.
class CMultipleVirtualInheritanceSuperBase1
{
//-------------------------------------------------------------------------------------------------------
	public:
		char													MValueSuperBase1[40];

	public:
		CMultipleVirtualInheritanceSuperBase1(void)
		{
			for(size_t Index=0;Index<sizeof(MValueSuperBase1);Index++)
			{
				MValueSuperBase1[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CMultipleVirtualInheritanceSuperBase1(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------