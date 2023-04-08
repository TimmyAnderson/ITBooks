//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <metahost.h>
#include <mscoree.h>
#include <string>
#include <corpub.h>
#include "Helpers\Helpers.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//-------------------------------------------------------------------------------------------------------
void Test(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		HRESULT													HR;
		CSmartCOMPointer<ICorPublish>							CorPublish=NULL;

		if (SUCCEEDED(HR=CoCreateInstance(CLSID_CorpubPublish,NULL,CLSCTX_INPROC_SERVER,__uuidof(ICorPublish),(void**) &CorPublish)))
		{
			CSmartCOMPointer<ICorPublishProcessEnum>			CorPublishProcessEnum=NULL;

			if (SUCCEEDED(HR=CorPublish->EnumProcesses(COR_PUB_MANAGEDONLY,&CorPublishProcessEnum)))
			{
				ULONG											NumberOfProcesses;

				if (SUCCEEDED(HR=CorPublishProcessEnum->GetCount(&NumberOfProcesses)))
				{
					wprintf_s(L"NUMBER of MANAGED PROCESSES [%d] !\n",NumberOfProcesses);
				}

				ULONG											Fetched;

				while(true)
				{
					CSmartCOMPointer<ICorPublishProcess>		CorPublishProcess=NULL;

					HR=CorPublishProcessEnum->Next(1,&CorPublishProcess,&Fetched);

					if (FAILED(HR) || HR==S_FALSE || Fetched!=1)
					{
						break;
					}


					wchar_t										ProcessBuffer[1024];
					ULONG32										ProcessBufferSize=_countof(ProcessBuffer);
					ULONG32										ProcessCopiedChars=0;

					if (SUCCEEDED(HR=CorPublishProcess->GetDisplayName(ProcessBufferSize,&ProcessCopiedChars,ProcessBuffer)))
					{
						wprintf_s(L"\tPROCESS [%s] !\n",ProcessBuffer);
					}

					CSmartCOMPointer<ICorPublishAppDomainEnum>	CorPublishAppDomainEnum=NULL;

					if (SUCCEEDED(HR=CorPublishProcess->EnumAppDomains(&CorPublishAppDomainEnum)))
					{
						while(true)
						{
							CSmartCOMPointer<ICorPublishAppDomain>	CorPublishAppDomain=NULL;

							HR=CorPublishAppDomainEnum->Next(1,&CorPublishAppDomain,&Fetched);

							if (FAILED(HR) || HR==S_FALSE || Fetched!=1)
							{
								break;
							}

							wchar_t								AppDomainBuffer[1024];
							ULONG32								AppDomainBufferSize=_countof(AppDomainBuffer);
							ULONG32								AppDomainCopiedChars=0;

							if (SUCCEEDED(CorPublishAppDomain->GetName(AppDomainBufferSize,&AppDomainCopiedChars,AppDomainBuffer)))
							{
								wprintf_s(L"\tAPP DOMAIN [%s] !\n",AppDomainBuffer);
							}

							CorPublishAppDomain=NULL;
						}

						CorPublishAppDomainEnum=NULL;
					}

					CorPublishProcess=NULL;
				}

				CorPublishProcessEnum=NULL;
			}

			CorPublish=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	Test();

	CHelpers::ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------