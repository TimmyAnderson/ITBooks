//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "KernelHeaders.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace KTL
{
//----------------------------------------------------------------------------------------------------------------------
	class CExecutiveResource final
	{
		private:
			ERESOURCE											MResource;

		public:
			void Init(void);
			void Delete(void);

			void Lock(void);
			void Unlock(void);

			void LockShared(void);
			void UnlockShared(void);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------