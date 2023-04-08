using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace ContextBindingsSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CToUpperService : IToUpperContract
	{
//-------------------------------------------------------------------------------------------------------
		public string ToUpper(string Param)
		{
			Console.WriteLine(string.Format("ToUpper(): [{0}] !",Param));

			ContextMessageProperty	CMP=(ContextMessageProperty) OperationContext.Current.IncomingMessageProperties[ContextMessageProperty.Name];

			string					FullName=CMP.Context["FullName"];

			Console.WriteLine(string.Format("CONTEXT PARAMETER - FullName: [{0}] !",FullName));

			return(Param.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------