//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! Je to VIRTUAL CLASS.
class CMultipleVirtualInheritanceSuperBase2
{
//-------------------------------------------------------------------------------------------------------
	public:
		char													MValueSuperBase2[80];

	public:
		CMultipleVirtualInheritanceSuperBase2(void)
		{
			for(size_t Index=0;Index<sizeof(MValueSuperBase2);Index++)
			{
				MValueSuperBase2[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CMultipleVirtualInheritanceSuperBase2(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------