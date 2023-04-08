using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CChainedService : IChainedService
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ITextService1							MTextService1;
		private readonly ITextService2							MTextService2;
		private readonly ITextService3							MTextService3;
		private readonly ITextService4							MTextService4;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// SERVICE je zavisly na INYCH SERVICES.
		public CChainedService(ITextService1 TextService1, ITextService2 TextService2, ITextService3 TextService3, ITextService4 TextService4)
		{
			MTextService1=TextService1;
			MTextService2=TextService2;
			MTextService3=TextService3;
			MTextService4=TextService4;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string GetTextFromService1()
		{
			string												Value=MTextService1.GetText();

			return(Value);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetTextFromService2()
		{
			string												Value=MTextService2.GetText();

			return(Value);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetTextFromService3()
		{
			string												Value=MTextService3.GetText();

			return(Value);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetTextFromService4()
		{
			string												Value=MTextService4.GetText();

			return(Value);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------