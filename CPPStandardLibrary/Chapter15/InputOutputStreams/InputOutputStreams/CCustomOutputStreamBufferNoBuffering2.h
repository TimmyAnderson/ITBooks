//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <streambuf>
#include <ostream>
#include <string>
//-----------------------------------------------------------------------------
// !!! CUSTOM STREAM BUFFER MUSI implementovat CLASS [basic_streambuf<TCharacter,TTraits>].
// !!! CLASS [CCustomStreamBufferNoBuffering] NEIMPLEMENTUJE CUSTOM BUFFERING.
class CCustomOutputStreamBufferNoBuffering2 final : public std::wstreambuf
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MDataStore;

	protected:
		// !!!!! CUSTOM OUTPUT STREAM BUFFER MUSI implementovat METHOD basic_streambuf<TCharacter,TTraits>::overflow().
		virtual int_type overflow(int_type Character) override;
		// !!! METHOD basic_streambuf<TCharacter,TTraits>::xsputn() umoznuje zapisat naraz VIACERO CHARACTERS do DATA STORE.
		virtual std::streamsize xsputn(const char_type* String, std::streamsize Size) override;

	public:
		const std::wstring& GetDataStore(void) const noexcept;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// CLASS [CCustomOutputStreamNoBuffering2] definuje CUSTOM OUTPUT STREAM pouzivajuca STREAM BUFFER [CCustomOutputStreamBufferNoBuffering2].
class CCustomOutputStreamNoBuffering2 final : public std::wostream
{
//-----------------------------------------------------------------------------
	private:
		CCustomOutputStreamBufferNoBuffering2					MStreamBuffer;

	public:
		const std::wstring& GetStreamContent(void) const noexcept
		{
			return(MStreamBuffer.GetDataStore());
		}

	public:
		CCustomOutputStreamNoBuffering2(void)
			: std::wostream(0), MStreamBuffer()
		{
			// !!! STREAM BUFFER sa nastavi na instanciu CUSTOM STREAM BUFFER.
			rdbuf(&MStreamBuffer);
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------