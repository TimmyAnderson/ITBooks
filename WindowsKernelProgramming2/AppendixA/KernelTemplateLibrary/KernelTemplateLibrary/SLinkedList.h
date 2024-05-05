//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "SLocker.h"
#include "SSharedLocker.h"
#include "SFastMutex.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace KTL
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock=SFastMutex>
	struct SLinkedList final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			mutable TLock										MLock;
			LIST_ENTRY											MHead;
			ULONG												MCount;

		public:
			void Init(void);
			bool IsEmpty(void) const;
			ULONG GetCount(void) const;
			void Clear(void);
			void AddHead(TType* Item);
			void AddTail(TType* Item);
			TType* RemoveHead(void);
			TType* RemoveTail(void);
			const TType* GetHead(void) const;
			TType const* GetTail(void) const;
			bool RemoveItem(TType* Item);

		public:
			template<typename TFunction>
			TType* Find(TFunction Predicate);
			template<typename TFunction>
			TType* ForEach(TFunction Action);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	void SLinkedList<TType,TLock>::Init(void)
	{
		InitializeListHead(&MHead);

		MLock.Init();

		MCount=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	bool SLinkedList<TType,TLock>::IsEmpty(void) const
	{
		bool													Result=(MCount==0);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	ULONG SLinkedList<TType,TLock>::GetCount(void) const
	{
		return(MCount);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	void SLinkedList<TType,TLock>::Clear(void)
	{
		SLocker													Locker(MLock);

		InitializeListHead(&MHead);

		MCount=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	void SLinkedList<TType,TLock>::AddHead(TType* Item)
	{
		SLocker													Locker(MLock);

		InsertHeadList(&MHead,&Item->Link);

		MCount++;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	void SLinkedList<TType,TLock>::AddTail(TType* Item)
	{
		SLocker													Locker(MLock);

		InsertTailList(&MHead,&Item->Link);

		MCount++;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	TType* SLinkedList<TType,TLock>::RemoveHead(void)
	{
		SLocker													Locker(MLock);

		if (MCount==0)
		{
			return(nullptr);
		}

		MCount--;

		auto													Link=RemoveHeadList(&MHead);
		TType*													Result=((Link==&MHead) ? nullptr : CONTAINING_RECORD(Link,TType,Link));

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	TType* SLinkedList<TType,TLock>::RemoveTail(void)
	{
		SLocker													Locker(MLock);

		if (MCount==0)
		{
			return(nullptr);
		}

		MCount--;

		auto													Link=RemoveTailList(&MHead);
		TType*													Result=((Link==&MHead) ? nullptr : CONTAINING_RECORD(Link,TType,Link));

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	const TType* SLinkedList<TType,TLock>::GetHead(void) const
	{
		SLocker													Locker(MLock);

		if (MCount==0)
		{
			return(nullptr);
		}

		const TType*											Result=CONTAINING_RECORD(MHead.Flink,TType,Link);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	const TType* SLinkedList<TType,TLock>::GetTail(void) const
	{
		SLocker													Locker(MLock);

		if (MCount==0)
		{
			return(nullptr);
		}

		const TType*											Result=CONTAINING_RECORD(MHead.Blink,TType,Link);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	bool SLinkedList<TType,TLock>::RemoveItem(TType* Item)
	{
		SLocker													Locker(MLock);

		MCount--;

		bool													Result=RemoveEntryList(&Item->Link);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	template<typename TFunction>
	TType* SLinkedList<TType,TLock>::Find(TFunction Predicate)
	{
		SLocker													Locker(MLock);

		for(auto Node=MHead.Flink;Node!=&MHead;Node=Node->Flink)
		{
			auto												Item=CONTAINING_RECORD(Node,TType,Link);

			if (Predicate(Item)==true)
			{
				return(Item);
			}
		}
		return nullptr;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, typename TLock>
	template<typename TFunction>
	TType* SLinkedList<TType,TLock>::ForEach(TFunction Action)
	{
		SLocker													Locker(MLock);

		for (auto Node=MHead.Flink;Node!=&MHead;Node=Node->Flink)
		{
			auto												Item=CONTAINING_RECORD(Node,TType,Link);

			Action(Item);
		}

		return(nullptr);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------