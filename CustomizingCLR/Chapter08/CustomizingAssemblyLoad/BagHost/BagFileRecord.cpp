//------------------------------------------------------------------------------------------------------
#include "BagFileRecord.h"
#include "BagFileRecord.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CBagFileRecord::CBagFileRecord(wstring FileName, DWORD FileSize, bool IsEXE, std::wstring AssemblyIdentity)
	: MFileName(FileName), MFileSize(FileSize), MIsEXE(IsEXE), MAssemblyIdentity(AssemblyIdentity), MFileData(NULL)
{
	MFileData=new BYTE[FileSize];
}
//------------------------------------------------------------------------------------------------------
CBagFileRecord::~CBagFileRecord(void)
{
	if (MFileData!=NULL)
	{
		delete[](MFileData);
		MFileData=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
wstring CBagFileRecord::GetFileName(void)
{
	return(MFileName);
}
//------------------------------------------------------------------------------------------------------
DWORD CBagFileRecord::GetFileSize(void)
{
	return(MFileSize);
}
//------------------------------------------------------------------------------------------------------
bool CBagFileRecord::GetIsEXE(void)
{
	return(MIsEXE);
}
//------------------------------------------------------------------------------------------------------
wstring CBagFileRecord::GetAssemblyIdentity(void)
{
	return(MAssemblyIdentity);
}
//------------------------------------------------------------------------------------------------------
BYTE* CBagFileRecord::GetFileData(void)
{
	return(MFileData);
}
//------------------------------------------------------------------------------------------------------