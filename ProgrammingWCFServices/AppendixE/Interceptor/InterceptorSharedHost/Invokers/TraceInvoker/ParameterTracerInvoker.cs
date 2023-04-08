using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Security.Permissions;
using System.Security;
using System.Net;
using System.Diagnostics;
using System.ServiceModel.Description;
using System.Reflection;
using System.ServiceModel.Dispatcher;
using InterceptorShared;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorSharedHost
{
//--------------------------------------------------------------------------------------------------------
	public class ParameterTracerInvoker : GenericInvoker
	{
//--------------------------------------------------------------------------------------------------------
		public ParameterTracerInvoker(IOperationInvoker OldInvoker)
			: base(OldInvoker)
		{
		}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
		protected override void PreInvoke(object Instance, object[] Inputs)
		{
			Console.WriteLine("Input Parameters: ");

			int					Count=1;

			foreach(object Argument in Inputs)
				Console.WriteLine(string.Format("\t{0}. - [{1}] !",Count++, Argument.ToString()));

			Console.WriteLine("");
		}
//--------------------------------------------------------------------------------------------------------
		protected override void PostInvoke(object Instance, object ReturnedValue, object[] Outputs, Exception Exception)
		{
			int					Count=1;

			Console.WriteLine("Output Parameters: ");

			foreach(object Output in Outputs)
				Console.WriteLine(string.Format("\t{0}. - [{1}] !",Count++, Outputs.ToString()));

			Console.WriteLine(string.Format("Returned: {0} !", ReturnedValue ?? String.Empty));
			Console.WriteLine(string.Format("Exception: {0} !", Exception));

			Console.WriteLine("");
		}
//--------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------