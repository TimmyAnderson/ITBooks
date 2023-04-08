//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
template<typename TType>
class CTemplateClass final
{
//-----------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		TType GetField(void) const noexcept
		{
			return(MField);
		}

		void SetField(TType Value) noexcept
		{
			MField=Value;
		}

	public:
		CTemplateClass(TType Field)
			: MField(Field)
		{
		}

		~CTemplateClass(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------