//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TType, int BUFFER_SIZE>
class CBufferTemplate
{
//-------------------------------------------------------------------------------------------------------
	private:
		// !!! VALUE PARAMETERS je mozne pouzit na definovanie velkosti BUFFERS.
		TType													MBuffer[BUFFER_SIZE];
		
	public:
		void GetBuffer(TType Value[BUFFER_SIZE])
		{
			for(int Index=0;Index<BUFFER_SIZE;Index++)
			{
				Value[Index]=MBuffer[Index];
			}
		}

		void SetBuffer(TType Value[BUFFER_SIZE])
		{
			for(int Index=0;Index<BUFFER_SIZE;Index++)
			{
				MBuffer[Index]=Value[Index];
			}
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------