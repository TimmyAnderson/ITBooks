//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CLValueRValueThisMethods final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void OldStyleThisParameter(void);

		// !!! THIS PARAMETER ma TYPE [CLValueRValueThisMethods&].
		void LValueReferenceThisParameter(void) &;

		// !!! THIS PARAMETER ma TYPE [CLValueRValueThisMethods&&].
		void RValueReferenceThisParameter(void) &&;

	public:
		CLValueRValueThisMethods(void);
		virtual ~CLValueRValueThisMethods(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------