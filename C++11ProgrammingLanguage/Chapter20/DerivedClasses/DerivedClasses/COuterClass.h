//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class COuterClass
{
//-----------------------------------------------------------------------------
	// !!! ACCESS CONTROL urcuje ci INNER CLASS je, alebo nie je pristupna z OUTER CLASS.
	public:
		class CInnerClass
		{
//-----------------------------------------------------------------------------
			private:
				bool											MCallOuterClass;

			private:
				void InnerPrivate(void);

			protected:
				void InnerProtected(void);

			public:
				void InnerPublic(void);

			public:
				CInnerClass(bool CallOuterClass);
				virtual ~CInnerClass(void);
//-----------------------------------------------------------------------------
		};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	private:
		bool													MCallInnerClass;

	private:
		void OuterPrivate(void);

	protected:
		void OuterProtected(void);

	public:
		void OuterPublic(void);

	public:
		COuterClass(bool CallInnerClass);
		virtual ~COuterClass(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------