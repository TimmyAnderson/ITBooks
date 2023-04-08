//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! TYPE [TMyTypeWithTraits] MUSI mat deklarovane ALIASES [TypeValue], [TypePointer] a [TypeReference].
template<typename TMyTypeWithTraits>
class CMyTypeTraits
{
//-------------------------------------------------------------------------------------------------------
	public:
		using Value=typename TMyTypeWithTraits::TypeValue;
		using Pointer=typename TMyTypeWithTraits::TypePointer;
		using Reference=typename TMyTypeWithTraits::TypeReference;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------