//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template <typename TType>
class CTemplate
{
	private:
		static TType											MStaticField;

	private:
		TType													MField;

	private:
		friend TType FriendGetValue(CTemplate<TType> Template);

	public:
		static const TType& GetStaticField(void);
		static void SetStaticField(const TType& Value);

	public:
		TType GetField(void);

	public:
		CTemplate(void);
		CTemplate(TType Value);
		virtual ~CTemplate(void);
};
//-------------------------------------------------------------------------------------------------------