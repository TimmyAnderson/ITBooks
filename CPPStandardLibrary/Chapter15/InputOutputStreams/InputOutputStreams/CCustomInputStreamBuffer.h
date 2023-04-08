//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <streambuf>
#include <ostream>
#include <string>
//-----------------------------------------------------------------------------
// !!! CUSTOM STREAM BUFFER MUSI implementovat CLASS [basic_streambuf<TCharacter,TTraits>].
class CCustomInputStreamBuffer final : public std::wstreambuf
{
//-----------------------------------------------------------------------------
	private:
		static const std::ptrdiff_t								PUTBACK_BUFFER_SIZE=4;
		static const std::ptrdiff_t								BUFFER_SIZE=6;

	private:
		std::wstring											MDataStore;
		std::size_t												MDataStoreOffset;
		// !!! BUFFER reprezentuje PUTBACK BUFFER a normalny (interny) BUFFER daneho STREAM BUFFER.
		char_type												MBuffer[PUTBACK_BUFFER_SIZE+BUFFER_SIZE];

	private:
		bool FillBuffer(void);

	protected:
		// !!! METHOD underflow() je volana ked je interny BUFFER daneho STREAM BUFFER prazdny. Ulohou METHOD je naplnit ho.
		virtual int_type underflow(void) override;
		virtual std::streamsize xsgetn(char_type* String, std::streamsize Count) override;
		virtual int_type pbackfail(int_type Character) override;

	public:
		const std::wstring& GetDataStore(void) const noexcept;
		std::wstring GetPointers(void) const;
		std::wstring GetBufferContent(void) const;

	public:
		CCustomInputStreamBuffer(const std::wstring& DataStore);
		virtual ~CCustomInputStreamBuffer(void) override;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------