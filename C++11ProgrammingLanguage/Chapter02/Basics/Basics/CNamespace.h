//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
namespace MY
{
//-----------------------------------------------------------------------------
	class CNamespace
	{
//-----------------------------------------------------------------------------
		private:
			int													MValue;

		public:
			int GetValue(void) const noexcept
			{
				return(MValue);
			}

		public:
			CNamespace(int Value)
				: MValue(Value)
			{
			}
//-----------------------------------------------------------------------------
	};
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------