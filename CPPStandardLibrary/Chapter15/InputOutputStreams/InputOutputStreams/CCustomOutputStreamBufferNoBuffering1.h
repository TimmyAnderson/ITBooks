//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <streambuf>
#include <ostream>
#include <string>
//-----------------------------------------------------------------------------
// !!! CUSTOM STREAM BUFFER MUSI implementovat CLASS [basic_streambuf<TCharacter,TTraits>].
// !!! CLASS [CCustomStreamBufferNoBuffering] NEIMPLEMENTUJE CUSTOM BUFFERING.
class CCustomOutputStreamBufferNoBuffering1 final : public std::wstreambuf
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MDataStore;

	protected:
		// !!!!! CUSTOM OUTPUT STREAM BUFFER MUSI implementovat METHOD basic_streambuf<TCharacter,TTraits>::overflow().
		virtual int_type overflow(int_type Character) override;

	public:
		const std::wstring& GetDataStore(void) const noexcept;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// CLASS [CCustomOutputStreamNoBuffering1] definuje CUSTOM OUTPUT STREAM pouzivajuca STREAM BUFFER [CCustomOutputStreamBufferNoBuffering1].
class CCustomOutputStreamNoBuffering1 final : public std::wostream
{
//-----------------------------------------------------------------------------
	private:
		CCustomOutputStreamBufferNoBuffering1					MStreamBuffer;

	public:
		const std::wstring& GetStreamContent(void) const noexcept
		{
			return(MStreamBuffer.GetDataStore());
		}

	public:
		CCustomOutputStreamNoBuffering1(void)
			: std::wostream(0), MStreamBuffer()
		{
			// !!! STREAM BUFFER sa nastavi na instanciu CUSTOM STREAM BUFFER.
			rdbuf(&MStreamBuffer);
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------