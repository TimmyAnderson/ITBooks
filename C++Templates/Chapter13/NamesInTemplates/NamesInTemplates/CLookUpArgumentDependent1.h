//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
namespace LookUpArgumentDependent1Namespace
{
//----------------------------------------------------------------------------------------------------------------------
	class CLookUpArgumentDependent1 final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			int													MField;

		public:
			int GetField(void) const noexcept;

		public:
			CLookUpArgumentDependent1(int Field);
			virtual ~CLookUpArgumentDependent1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! OPERATOR je definovany ako FUNCTION, ale je v NAMESPACE.
	bool operator<(const CLookUpArgumentDependent1& Value1, const CLookUpArgumentDependent1& Value2);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------