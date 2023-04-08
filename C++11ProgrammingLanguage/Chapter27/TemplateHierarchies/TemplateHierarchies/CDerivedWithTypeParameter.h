//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS MOZE dedit zo svojho TYPE PARAMETER.
template<typename TType>
class CDerivedWithTypeParameter : public TType
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void DoSomething(void)
		{
		}

	public:
		// !!! Ak ma BASE CLASS definovanu METHOD VirtualMethod(), tak ju CLASS [CDerivedWithTypeParameter] pretazi.
		// !!! Ak BASE CLASS NEMA definovanu METHOD VirtualMethod(), tak CLASS [CDerivedWithTypeParameter] definuje NOVU METHOD.
		virtual void VirtualMethod(void)
		{
			wprintf_s(L"METHOD CDerivedWithTypeParameter::VirtualMethod() CALLED !\n");

			// !!! BASE CLASS MUSI mat definovanu METHOD DoSomething().
			DoSomething();
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------