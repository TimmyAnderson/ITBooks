using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace BETestLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CBETestService : IBETestContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CBETestService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string SomeMethod(string Text)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine(string.Format("Data from CLIENT: {0} !",Text));

			return(Text.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------