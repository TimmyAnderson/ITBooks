using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDependencyInjection
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CName[]								MDataFromInterfaceService;
		private readonly string									MDataFromBaseClassService;
		private readonly string									MDataFromConcreteClassService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDependencyInjection(CName[] DataFromInterfaceService, string DataFromBaseClassService, string DataFromConcreteClassService)
		{
			MDataFromInterfaceService=DataFromInterfaceService;
			MDataFromBaseClassService=DataFromBaseClassService;
			MDataFromConcreteClassService=DataFromConcreteClassService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CName[]											DataFromInterfaceService
		{
			get
			{
				return(MDataFromInterfaceService);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											DataFromBaseClassService
		{
			get
			{
				return(MDataFromBaseClassService);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											DataFromConcreteClassService
		{
			get
			{
				return(MDataFromConcreteClassService);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------