//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#include "NamespaceSTD.h"
#include <ntifs.h>
#include "EPoolType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace KTL
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	class CBasicString
	{
//----------------------------------------------------------------------------------------------------------------------
		static_assert(sizeof(TType)==sizeof(wchar_t) || sizeof(TType)==sizeof(char));

		public:
			using												IteratorType=TType*;
			using												ConstIteratorType=const TType*;

		private:
			TType*												MData;
			ULONG												MLength;
			ULONG												MCapacity;

		public:
			static const ULONG									MDefaultCapacity=16;

		public:
			CBasicString& operator=(const CBasicString& Other);
			CBasicString& operator=(PCUNICODE_STRING Other);
			CBasicString& operator=(CBasicString&& Other);
			CBasicString& operator+=(const CBasicString& Other);
			CBasicString& operator+=(const TType* String);
			CBasicString& operator+=(const UNICODE_STRING& Other);
			CBasicString operator+(const CBasicString& Other);
			bool operator==(const CBasicString& Other) const;
			bool operator!=(const CBasicString& Other) const;
			operator const TType*(void) const;

		protected:
			static TType* AllocateAndCopy(ULONG Length, const TType* Source, ULONG LengthToCopy=0);

		protected:
			constexpr const TType* FindInternal(TType Character)
			{
				for (ULONG Index=0;Index<MLength;Index++)
				{
					if (MData[Index]==Character)
					{
						const TType*							Result=(MData+Index);

						return(Result);
					}
				}

				return(nullptr);
			}

			constexpr const TType* FindInternalNoCase(TType Character)
			{
				TType											LocalCharacter;

				if constexpr (sizeof(TType)==sizeof(char))
				{
					LocalCharacter=tolower(Character);
				}
				else
				{
					LocalCharacter=towlower(Character);
				}

				for (ULONG Index=0;Index<MLength;Index++)
				{
					auto										TempCharacter=tolower(MData[Index]);

					if (TempCharacter==LocalCharacter)
					{
						const TType*							Result=(MData+Index);

						return(Result);
					}
				}

				return(nullptr);
			}

		public:
			constexpr const TType* Find(const TType Character, bool CaseInsensitive=false) const
			{
				if (MLength==0)
				{
					return(nullptr);
				}

				const TType*									Result=((CaseInsensitive==true) ? FindInternalNoCase(Character) : FindInternal(Character));

				return(Result);
			}

		public:
			ULONG Length(void) const;
			ULONG Capacity(void) const;
			const TType* Data(void) const;
			TType* Data(void);

		public:
			CBasicString& Append(const CBasicString& String);
			CBasicString& Append(const TType* String, ULONG Count);
			UNICODE_STRING& GetUnicodeString(UNICODE_STRING& UnicodeString) const;
			UNICODE_STRING& GetUnicodeString(PUNICODE_STRING UnicodeString) const;
			bool EqualNoCase(const TType* String) const;
			void ShrinkToFit(void);
			bool EqualsNoCase(const CBasicString& Other) const;
			void Release(void) noexcept;

		public:
			IteratorType begin(void);
			IteratorType begin(void) const;
			ConstIteratorType cbegin(void) const;
			IteratorType end(void);
			IteratorType end(void) const;
			ConstIteratorType cend(void) const;

		public:
			CBasicString(const TType* Data=nullptr);
			CBasicString(const TType* Data, ULONG Length, ULONG Capacity=0);
			explicit CBasicString(PCUNICODE_STRING UnicodeString);
			explicit CBasicString(ULONG Capacity);
			CBasicString(const CBasicString& Other);
			CBasicString(CBasicString&& Other);
			~CBasicString(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::CBasicString(const TType* Data)
	{
		if (Data!=nullptr)
		{
			if constexpr (sizeof(TType)==sizeof(char))
			{
				MLength=(ULONG)strlen(Data);
			}
			else
			{
				MLength=(ULONG)wcslen(Data);
			}

			MCapacity=max(MLength,MDefaultCapacity);
			MData=AllocateAndCopy(MCapacity,Data,MLength);

			if (MData==nullptr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
		else
		{
			MLength=0;
			MCapacity=0;
			MData=nullptr;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::CBasicString(const TType* Data, ULONG Length, ULONG Capacity)
	{
		MLength=Length;
		MCapacity=Capacity;

		MData=AllocateAndCopy(MLength,Data,MCapacity);

		if (MData==nullptr)
		{
			ExRaiseStatus(STATUS_NO_MEMORY);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::CBasicString(PCUNICODE_STRING UnicodeString)
	{
		static_assert(sizeof(TType)==sizeof(wchar_t));

		if (UnicodeString->Length>0)
		{
			NT_ASSERT(UnicodeString->Buffer);

			MLength=MCapacity=(UnicodeString->Length/sizeof(TType));
			MData=AllocateAndCopy(MLength,UnicodeString->Buffer);

			if (MData==nullptr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
		else
		{
			MData=nullptr;
			MLength=0;
			MCapacity=0;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::CBasicString(ULONG Capacity)
	{
		MCapacity=Capacity;
		MData=AllocateAndCopy(Capacity,nullptr);

		if (MData==nullptr)
		{
			ExRaiseStatus(STATUS_NO_MEMORY);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::CBasicString(const CBasicString& Other)
	{
		if (this!=&Other)
		{
			MLength=Other.MLength;
			MData=AllocateAndCopy(MLength,Other.MData);

			if (MData==nullptr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::CBasicString(CBasicString&& Other)
	{
		if (this!=&Other)
		{
			MLength=Other.Length();
			MCapacity=Other.Capacity();
			MData=Other.MData;

			Other.MData=nullptr;
			Other.MLength=0;
			Other.MCapacity=0;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::~CBasicString(void) noexcept
	{
		Release();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::operator=(const CBasicString& Other)
	{
		if (this!=&Other)
		{
			MLength=Other.MLength;

			if (MCapacity>=MLength)
			{
				memcpy(MData,Other.MData,MLength*sizeof(TType));
			}
			else
			{
				Release();

				MLength=Other.MLength;
				MData=AllocateAndCopy(MLength,Other.MData);

				if (MData==nullptr)
				{
					ExRaiseStatus(STATUS_NO_MEMORY);
				}

				MCapacity=MLength;
			}
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::operator=(PCUNICODE_STRING Other)
	{
		static_assert(sizeof(TType)==sizeof(wchar_t));

		MLength=(Other->Length/sizeof(TType));

		if (MCapacity>=MLength)
		{
			if (MLength>0)
			{
				memcpy(MData,Other->Buffer,MLength*sizeof(TType));
			}
		}
		else
		{
			Release();

			MCapacity=min(MLength,MDefaultCapacity);
			MData=AllocateAndCopy(MCapacity,Other->Buffer,MLength);

			if (MData==nullptr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::operator=(CBasicString&& Other)
	{
		if (this!=&Other)
		{
			Release();

			MLength=Other.Length();
			MCapacity=Other.Capacity();
			MData=Other.MData;

			Other.MData=nullptr;
			Other.MLength=0;
			Other.MCapacity=0;
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::operator+=(const CBasicString& Other)
	{
		CBasicString&											Result=Append(Other);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::operator+=(const TType* String)
	{
		if constexpr(sizeof(TType)==sizeof(char))
		{
			CBasicString&										Result=Append(String,(ULONG)strlen(String));

			return(Result);
		}
		else
		{
			CBasicString&										Result=Append(String,(ULONG)wcslen(String));

			return(Result);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::operator+=(const UNICODE_STRING& Other)
	{
		static_assert(sizeof(TType)==sizeof(wchar_t));

		CBasicString&											Result=Append(Other.Buffer,Other.Length/sizeof(WCHAR));

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG> CBasicString<TType,POOL,TAG>::operator+(const CBasicString& Other)
	{
		CBasicString<TType,POOL,TAG>							String(*this);

		String+=Other;

		return(String);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CBasicString<TType,POOL,TAG>::operator==(const CBasicString& Other) const
	{
		if constexpr (sizeof(TType)==sizeof(char))
		{
			bool												Result=(strcmp(MData,Other.MData)==0);

			return(Result);
		}
		else
		{
			bool												Result=(wcscmp(MData,Other.MData)==0);

			return(Result);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CBasicString<TType,POOL,TAG>::operator!=(const CBasicString& Other) const
	{
		bool													Result=(!(*this==Other));

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>::operator const TType*(void) const
	{
		const TType*											Result=Data();

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	TType* CBasicString<TType,POOL,TAG>::AllocateAndCopy(ULONG Length, const TType* Source, ULONG LengthToCopy)
	{
		if (LengthToCopy==0)
		{
			LengthToCopy=Length;
		}

		auto													Data=static_cast<TType*>(ExAllocatePool2((POOL_FLAGS)POOL,(Length+1)*sizeof(TType),TAG));

		if (Data==nullptr)
		{
			return(nullptr);
		}

#ifdef KTL_TRACK_BASIC_STRING
		DbgPrint(KTL_PREFIX "CBasicString allocate [%u] characters (copy: [%u]).\n",Length,LengthToCopy);
#endif

		if (LengthToCopy!=0 && Source!=nullptr)
		{
			memcpy(Data,Source,LengthToCopy*sizeof(TType));
		}

		return(Data);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	ULONG CBasicString<TType,POOL,TAG>::Length(void) const
	{
		return(MLength);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	ULONG CBasicString<TType,POOL,TAG>::Capacity(void) const
	{
		return(MCapacity);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	const TType* CBasicString<TType,POOL,TAG>::Data(void) const
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	TType* CBasicString<TType,POOL,TAG>::Data(void)
	{
		return(MData);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::Append(const CBasicString& String)
	{
		auto													NewLength=(MLength+String.Length());

		if (NewLength>MCapacity)
		{
			auto												Data=AllocateAndCopy(NewLength,MData,MLength);

			if (Data==nullptr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}

			memcpy(Data+MLength,String.Data(),String.Length()*sizeof(TType));

			Release();

			MCapacity=MLength=NewLength;
			MData=Data;
		}
		else
		{
			memcpy(MData+MLength,String.Data(),String.Length()*sizeof(TType));

			MLength=NewLength;
		}

		MData[MLength]=static_cast<TType>(0);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	CBasicString<TType,POOL,TAG>& CBasicString<TType,POOL,TAG>::Append(const TType* String, ULONG Count)
	{
		auto													NewLength=(MLength+Count);

		if (NewLength>MCapacity)
		{
			auto												Data=AllocateAndCopy(NewLength,MData,MLength);

			if (Data==nullptr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}

			memcpy(Data+MLength,String,Count*sizeof(TType));

			Release();

			MCapacity=MLength=NewLength;
			MData=Data;
		}
		else
		{
			memcpy(MData+MLength,String,Count*sizeof(TType));

			MLength=NewLength;
		}

		MData[MLength]=static_cast<TType>(0);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	UNICODE_STRING& CBasicString<TType,POOL,TAG>::GetUnicodeString(UNICODE_STRING& UnicodeString) const
	{
		static_assert(sizeof(TType)==sizeof(wchar_t));

		UnicodeString.Length=UnicodeString.MaximumLength=USHORT(Length()*sizeof(wchar_t));
		UnicodeString.Buffer=MData;

		return(UnicodeString);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	UNICODE_STRING& CBasicString<TType,POOL,TAG>::GetUnicodeString(PUNICODE_STRING UnicodeString) const
	{
		UNICODE_STRING&											Result=GetUnicodeString(*UnicodeString);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CBasicString<TType,POOL,TAG>::EqualNoCase(const TType* String) const
	{
		if constexpr (sizeof(TType)==sizeof(char))
		{
			bool												Result=(_stricmp(MData,String)==0);

			return(Result);
		}
		else
		{
			bool												Result=(_wcsicmp(MData,String)==0);

			return(Result);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CBasicString<TType,POOL,TAG>::ShrinkToFit(void)
	{
		if (MCapacity>MLength)
		{
			CBasicString										String(*this);

			Release();

			*this=STD::Move(String);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	bool CBasicString<TType,POOL,TAG>::EqualsNoCase(const CBasicString& Other) const
	{
		if constexpr (sizeof(TType)==sizeof(char))
		{
			bool												Result=(_stricmp(MData,Other.MData)==0);

			return(Result);
		}
		else
		{
			bool												Result=(_wcsicmp(MData,Other.MData)==0);

			return(Result);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	void CBasicString<TType,POOL,TAG>::Release(void) noexcept
	{
		if (MData!=nullptr)
		{
			ExFreePool(MData);

			MLength=0;
			MData=nullptr;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CBasicString<TType,POOL,TAG>::IteratorType CBasicString<TType,POOL,TAG>::begin(void)
	{
		return MData;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CBasicString<TType,POOL,TAG>::IteratorType CBasicString<TType,POOL,TAG>::begin(void) const
	{
		return MData;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CBasicString<TType,POOL,TAG>::ConstIteratorType CBasicString<TType,POOL,TAG>::cbegin(void) const
	{
		return MData;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CBasicString<TType,POOL,TAG>::IteratorType CBasicString<TType,POOL,TAG>::end(void)
	{
		IteratorType											Result=(MData+MLength);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CBasicString<TType,POOL,TAG>::IteratorType CBasicString<TType,POOL,TAG>::end(void) const
	{
		IteratorType											Result=(MData+MLength);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType, EPoolType POOL, ULONG TAG>
	typename CBasicString<TType,POOL,TAG>::ConstIteratorType CBasicString<TType,POOL,TAG>::cend(void) const
	{
		ConstIteratorType										Result=(MData+MLength);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<EPoolType POOL, ULONG TAG>
	using														WString=CBasicString<wchar_t,POOL,TAG>;
//----------------------------------------------------------------------------------------------------------------------
	template<ULONG TAG>
	using														NPWString=CBasicString<wchar_t,EPoolType::NonPaged,TAG>;
//----------------------------------------------------------------------------------------------------------------------
	template<ULONG TAG>
	using														PWString=CBasicString<wchar_t,EPoolType::Paged,TAG>;
//----------------------------------------------------------------------------------------------------------------------
	template<EPoolType POOL, ULONG TAG>
	using														AString=CBasicString<char,POOL,TAG>;
//----------------------------------------------------------------------------------------------------------------------
	template<ULONG TAG>
	using														NPAString=CBasicString<char,EPoolType::NonPaged,TAG>;
//----------------------------------------------------------------------------------------------------------------------
	template<ULONG TAG>
	using														PAString=CBasicString<char,EPoolType::Paged,TAG>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------