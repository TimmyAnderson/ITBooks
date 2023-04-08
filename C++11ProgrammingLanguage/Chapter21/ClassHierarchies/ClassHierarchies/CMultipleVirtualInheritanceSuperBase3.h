//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! Je to VIRTUAL CLASS.
class CMultipleVirtualInheritanceSuperBase3
{
//-------------------------------------------------------------------------------------------------------
	public:
		char													MValueSuperBase3[120];

	public:
		CMultipleVirtualInheritanceSuperBase3(void)
		{
			for(size_t Index=0;Index<sizeof(MValueSuperBase3);Index++)
			{
				MValueSuperBase3[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CMultipleVirtualInheritanceSuperBase3(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------