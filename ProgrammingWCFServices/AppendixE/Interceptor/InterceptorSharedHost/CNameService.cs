using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorSharedHost
{
//--------------------------------------------------------------------------------------------------------
	// Aplikujem Service Behavior.
	[ServiceParameterTracer]
	public class CNameService : INameService
	{
//--------------------------------------------------------------------------------------------------------
		public CFullName GetFullName(string FirstName, string LastName, int Age)
		{
			CFullName			FullName=new CFullName(FirstName,LastName,Age);

			Console.WriteLine(string.Format("GetFullName() - INPUT [FN: {0}, LN: {1}, A: {2}] - OUTPUT: [{3}]",FirstName,LastName,Age,FullName));

			return(FullName);
		}
//--------------------------------------------------------------------------------------------------------
		public string GetFirstName(CFullName FullName)
		{
			string				FirstName=FullName.FirstName;

			Console.WriteLine(string.Format("GetFullName() - INPUT [{0}] - OUTPUT: [{1}]",FullName,FirstName));
			
			return(FirstName);
		}
//--------------------------------------------------------------------------------------------------------
		public string JustThrowException(string Name)
		{
			string				Ret=Name.ToUpper();

			Console.WriteLine(string.Format("JustThrowException() - INPUT [{0}] - OUTPUT: [{1}]",Name,Ret));

			if(Name!="Timmy")
				throw(new FaultException("ERROR - You are NOT Timmy !!!"));

			return(Ret);
		}
//--------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------