//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CAccessControlBase
{
	private:
		void BasePrivate(void);
		void DummyPrivate(void);

	protected:
		void BaseProtected(void);
		void DummyProtected(void);

	public:
		void BasePublic(void);
		void DummyPublic(void);

	public:
		void MemberConversionSucceeded(std::wstring Text);
		void ExternalConversionSucceeded(std::wstring Text);

	public:
		CAccessControlBase(void);
		virtual ~CAccessControlBase(void);
};
//-------------------------------------------------------------------------------------------------------