//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
class CConcreteCollectionType
{
//-----------------------------------------------------------------------------
	private:
		std::vector<int>										MCollection;

	public:
		int& operator[](std::size_t Index)
		{
			return(MCollection[Index]);
		}

		const int& operator[](std::size_t Index) const
		{
			return(MCollection[Index]);
		}

	public:
		void Add(int Value)
		{
			MCollection.push_back(Value);
		}

		std::size_t GetSize(void) const
		{
			return(MCollection.size());
		}

	public:
		CConcreteCollectionType(void)
			: MCollection()
		{
		}

		~CConcreteCollectionType(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------