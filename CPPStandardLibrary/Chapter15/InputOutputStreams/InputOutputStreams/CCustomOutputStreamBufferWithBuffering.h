//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <streambuf>
#include <ostream>
#include <string>
//-----------------------------------------------------------------------------
// !!! CUSTOM STREAM BUFFER MUSI implementovat CLASS [basic_streambuf<TCharacter,TTraits>].
// !!! CLASS [CCustomStreamBufferNoBuffering] IMPLEMENTUJE CUSTOM BUFFERING.
class CCustomOutputStreamBufferWithBuffering final : public std::wstreambuf
{
//-----------------------------------------------------------------------------
	private:
		static const std::size_t								BUFFER_SIZE=5;

	private:
		std::wstring											MDataStore;
		// !!! BUFFER reprezentuje CUSTOM BUFFER pre BUFFERING IO OPERATIONS.
		// !!!!! Nastavenim BUFFER POINTERS pomocou METHOD basic_streambuf<TCharacter,TTraits>::setp() METHODS STREAM BUFFER AUTOMATICKY ukladaju data do CUSTOM BUFFER a AZ PO JEHO PREPLNENI volaju METHOD basic_streambuf<TCharacter,TTraits>::overflow().
		wchar_t													MBuffer[BUFFER_SIZE];

	private:
		void FlushCustomBufferToDataStore(void);

	protected:
		// !!!!! CUSTOM OUTPUT STREAM BUFFER MUSI implementovat METHOD basic_streambuf<TCharacter,TTraits>::overflow().
		// !!!!! METHOD je volana AZ KED je CUSTOM BUFFER PLNY.
		virtual int_type overflow(int_type Character) override;
		// !!! METHOD basic_streambuf<TCharacter,TTraits>::xsputn() umoznuje zapisat naraz VIACERO CHARACTERS do DATA STORE.
		// !!!!! METHOD je volana AZ KED je CUSTOM BUFFER PLNY.
		virtual std::streamsize xsputn(const char_type* String, std::streamsize Size) override;
		virtual int sync(void) override;

	public:
		const std::wstring& GetDataStore(void) const noexcept;

	public:
		CCustomOutputStreamBufferWithBuffering(void);
		virtual ~CCustomOutputStreamBufferWithBuffering(void) override;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// CLASS [CCustomOutputStreamWithBuffering] definuje CUSTOM OUTPUT STREAM pouzivajuca STREAM BUFFER [CCustomOutputStreamBufferWithBuffering].
class CCustomOutputStreamWithBuffering final : public std::wostream
{
//-----------------------------------------------------------------------------
	private:
		CCustomOutputStreamBufferWithBuffering					MStreamBuffer;

	public:
		const std::wstring& GetStreamContent(void) const noexcept
		{
			return(MStreamBuffer.GetDataStore());
		}

	public:
		CCustomOutputStreamWithBuffering(void)
			: std::wostream(0), MStreamBuffer()
		{
			// !!! STREAM BUFFER sa nastavi na instanciu CUSTOM STREAM BUFFER.
			rdbuf(&MStreamBuffer);
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------