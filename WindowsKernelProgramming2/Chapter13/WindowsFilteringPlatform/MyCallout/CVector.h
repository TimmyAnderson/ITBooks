//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include "NamespaceSTD.h"
#include "EPoolType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace KTL
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	class CVector final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			TType*												MData;
			ULONG												MSize;
			ULONG												MCapacity;

		public:
//----------------------------------------------------------------------------------------------------------------------
			struct SIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					const CVector&								MVector;
					ULONG										MIndex;

				public:
					SIterator& operator++(void);
					SIterator operator++(int) const;
					bool operator==(const SIterator& Other) const;
					bool operator!=(const SIterator& Other) const;
					const TType& operator*(void) const;

				public:
					SIterator(const CVector& Vector, const ULONG Index);
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

		public:
			CVector& operator=(const CVector& Other);
			CVector& operator=(CVector&& Other);
			const TType& operator[](ULONG Index) const;
			TType& operator[](ULONG Index);

		public:
			SIterator begin(void);
			SIterator end(void);
			SIterator begin(void) const;
			SIterator end(void) const;
			const SIterator cbegin(void) const;
			const SIterator cend(void) const;

		public:
			ULONG Size(void) const;
			ULONG Capacity(void) const;
			bool IsEmpty(void) const;

		public:
			void Add(const TType& Item);
			void Add(TType&& Item);
			void Insert(ULONG Index, const TType& Item);
			void Insert(ULONG Index, TType&& Item);
			bool Remove(const TType& Value);
			template<typename FFunction>
			bool RemoveIf(FFunction&& Predicate);
			bool Contains(const TType& Value) const;
			bool RemoveAt(ULONG Index);
			void Resize(ULONG NewSize);
			void Clear(void);
			void Free(void) noexcept;

		public:
			explicit CVector(ULONG Capacity=0);
			CVector(const CVector& Other);
			CVector(CVector&& Other);
			~CVector(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>::SIterator::SIterator(const CVector& Vector, const ULONG Index)
		: MVector(Vector), MIndex(Index)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CVector<TType,POOL,TAG>::SIterator& CVector<TType,POOL,TAG>::SIterator::operator++(void)
	{
		++MIndex;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::SIterator::operator++(int) const
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(MVector,MIndex+1);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CVector<TType,POOL,TAG>::SIterator::operator==(const SIterator& Other) const
	{
		bool													Result=(&MVector==&Other.MVector && MIndex==Other.MIndex);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CVector<TType,POOL,TAG>::SIterator::operator!=(const SIterator& Other) const
	{
		bool													Result=(!(*this==Other));

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	const TType& CVector<TType,POOL,TAG>::SIterator::operator*(void) const
	{
		const TType&											Result=MVector[MIndex];

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>::CVector(ULONG Capacity)
	{
		MCapacity=Capacity;
		MSize=0;

		if (Capacity!=0)
		{
			MData=static_cast<TType*>(ExAllocatePool2(static_cast<POOL_FLAGS>(POOL),sizeof(TType)*Capacity,TAG));

			new (MData) TType[Capacity];

			if (MData==nullptr)
			{
				::ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
		else
		{
			MData=nullptr;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>::CVector(const CVector& Other)
		: MCapacity(Other.Size())
	{
		MSize=MCapacity;
		MData=static_cast<TType*>(ExAllocatePool2(static_cast<POOL_FLAGS>(POOL),sizeof(TType)*MSize,TAG));

		if (MData==nullptr)
		{
			::ExRaiseStatus(STATUS_NO_MEMORY);
		}

		for (ULONG Index=0;Index<MSize;Index++)
		{
			new (MData+Index) TType(Other.MData[Index]);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>::CVector(CVector&& Other)
		: MCapacity(Other.MCapacity), MSize(Other.MSize)
	{
		MData=Other.MData;

		Other.MData=nullptr;
		Other.MSize=0;
		Other.MCapacity=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>::~CVector(void) noexcept
	{
		Free();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>& CVector<TType,POOL,TAG>::operator=(const CVector& Other)
	{
		if (this!=Other)
		{
			Free();

			MSize=MCapacity;
			MData=static_cast<TType*>(ExAllocatePool2(static_cast<POOL_FLAGS>(POOL),sizeof(TType)*MSize,TAG));

			if (MData==nullptr)
			{
				::ExRaiseStatus(STATUS_NO_MEMORY);
			}

			for (ULONG Index=0;Index<MSize;Index++)
			{
				new (MData+Index) TType(Other.MData[Index]);
			}
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CVector<TType,POOL,TAG>& CVector<TType,POOL,TAG>::operator=(CVector&& Other)
	{
		if (this!=&Other)
		{
			Free();

			MSize=Other.MSize;
			MCapacity=Other.MCapacity;
			MData=Other.MData;

			Other.MData=nullptr;
			Other.MSize=0;
			Other.MCapacity=0;
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	const TType& CVector<TType,POOL,TAG>::operator[](ULONG Index) const
	{
		NT_ASSERT(Index<MSize);

		const TType&											Result=MData[Index];

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	TType& CVector<TType,POOL,TAG>::operator[](ULONG Index)
	{
		NT_ASSERT(Index<MSize);

		TType&													Result=MData[Index];

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::begin(void)
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(*this,0U);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::end(void)
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(*this,MSize);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::begin(void) const
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(*this,0U);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::end(void) const
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(*this,MSize);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	const typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::cbegin(void) const
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(*this,0U);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	const typename CVector<TType,POOL,TAG>::SIterator CVector<TType,POOL,TAG>::cend(void) const
	{
		typename CVector<TType,POOL,TAG>::SIterator				Result(*this,MSize);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	ULONG CVector<TType,POOL,TAG>::Size(void) const
	{
		return(MSize);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	ULONG CVector<TType,POOL,TAG>::Capacity(void) const
	{
		return(MCapacity);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CVector<TType,POOL,TAG>::IsEmpty(void) const
	{
		bool													Result=(MSize==0);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Add(const TType& Item)
	{
		if (MSize>=MCapacity)
		{
			Resize(max(MCapacity*2,MSize+1));
		}

		MData[MSize++]=Item;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Add(TType&& Item)
	{
		if (MSize>=MCapacity)
		{
			Resize(max(MCapacity*2,MSize+1));
		}

		MData[MSize++]=STD::Move(Item);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Insert(ULONG Index, const TType& Item)
	{
		// TODO.
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Insert(ULONG Index, TType&& Item)
	{
		// TODO.
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CVector<TType,POOL,TAG>::Remove(const TType& Value)
	{
		for (ULONG Index=0;Index<MSize;Index++)
		{
			if (MData[Index]==Value)
			{
				RemoveAt(Index);

				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	template<typename FFunction>
	bool CVector<TType,POOL,TAG>::RemoveIf(FFunction&& Predicate)
	{
		for (ULONG Index=0;Index<MSize;Index++)
		{
			if (Predicate(MData[Index]))
			{
				RemoveAt(Index);

				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CVector<TType,POOL,TAG>::Contains(const TType& Value) const
	{
		for (ULONG Index=0;Index<MSize;Index++)
		{
			if (MData[Index]==Value)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CVector<TType,POOL,TAG>::RemoveAt(ULONG Index)
	{
		if (Index>=MSize)
		{
			return(false);
		}

		MData[Index].~TType();

		memmove(MData+Index,MData+Index+1,(MSize-Index-1)*sizeof(TType));

		MSize--;

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Resize(ULONG NewSize)
	{
		if (NewSize<=MCapacity)
		{
			for (ULONG Index=NewSize;Index<MSize;Index++)
			{
				MData[Index].~TType();
			}

			MSize=NewSize;

			return;
		}

		MCapacity=NewSize;

		auto													Data=static_cast<TType*>(ExAllocatePool2(static_cast<POOL_FLAGS>(POOL),sizeof(TType)*NewSize,TAG));

		if (Data==nullptr)
		{
			::ExRaiseStatus(STATUS_NO_MEMORY);
		}

		if (MData!=nullptr)
		{
			memcpy(Data,MData,sizeof(TType)*MSize);

			ExFreePool(MData);
		}

		MData=Data;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Clear(void)
	{
		Free();

		MSize=0;
		MCapacity=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CVector<TType,POOL,TAG>::Free(void) noexcept
	{
		if (MData!=nullptr)
		{
			for (ULONG Index=0;Index<MSize;Index++)
			{
				(MData+Index)->~TType();
			}

			ExFreePool(MData);

			MData=nullptr;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------