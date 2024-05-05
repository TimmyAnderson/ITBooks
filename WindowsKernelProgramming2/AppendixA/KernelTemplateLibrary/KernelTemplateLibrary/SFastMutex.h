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
	struct SFastMutex final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			FAST_MUTEX											MMutex;

		public:
			void Init(void);
			void Lock(void);
			void Unlock(void);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------