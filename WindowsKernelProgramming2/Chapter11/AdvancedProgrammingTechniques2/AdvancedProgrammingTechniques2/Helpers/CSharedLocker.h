//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TLock>
concept CConceptSharedLock=requires(TLock Value)
{
	Value.LockShared();
	Value.UnlockShared();
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TLock> requires CConceptSharedLock<TLock>
class CSharedLocker final : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TLock&													MLock;

	public:
		explicit CSharedLocker(TLock& lock);
		~CSharedLocker(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TLock> requires CConceptSharedLock<TLock>
CSharedLocker<TLock>::CSharedLocker(TLock& Lock)
	: MLock(Lock)
{
	MLock.LockShared();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TLock> requires CConceptSharedLock<TLock>
CSharedLocker<TLock>::~CSharedLocker(void)
{
	MLock.UnlockShared();
}
//----------------------------------------------------------------------------------------------------------------------