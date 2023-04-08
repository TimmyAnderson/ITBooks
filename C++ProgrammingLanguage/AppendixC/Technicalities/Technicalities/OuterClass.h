//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class COuterClass
{
	private:
		void OuterPrivate(void);

	protected:
		void OuterProtected(void);

	public:
		void OuterPublic(void);

	// !!! ACCESS CONTROL urcuje ci INNER CLASS je, alebo nie je pristupny z OUTER CLASS.
	public:
	//private:
		class CInnerClass
		{
			private:
				void InnerPrivate(void);

			protected:
				void InnerProtected(void);

			public:
				void InnerPublic(void);

			public:
				CInnerClass(void);
				virtual ~CInnerClass(void);
		};

	public:
		COuterClass(void);
		virtual ~COuterClass(void);
};
//-------------------------------------------------------------------------------------------------------