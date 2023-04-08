using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace InferredDataContractsService
{
//-------------------------------------------------------------------------------------------------------
	public class CFullNameService : IFullNameService
	{
//-------------------------------------------------------------------------------------------------------
		public CInferredFullName GetFullName(string FirstName, string LastName, int Age)
		{
			CInferredFullName			Ret=new CInferredFullName(FirstName,LastName,Age);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public CInferredFullNameDerived GetFullNameDerived(string FirstName, string LastName, int Age, string SomeInfo)
		{
			CInferredFullNameDerived	Ret=new CInferredFullNameDerived(FirstName,LastName,Age,SomeInfo);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------