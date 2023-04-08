using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using ResponseMSMQShared;
//-------------------------------------------------------------------------------------------------------
// 1. Toto je response service, ktory zachytava volania z CalculatorService a spracovava ich.
// 2. Pracuje tie ako MSMQ service a jeho ulohou je zachytavat navratove hodnoty z CalculatorService a spracovavat ich podla toho aky vysledok, alebo expcetion obsahuju.
// 3. Pouziva sa pritom prenos ID aby som vedel ktore volanie Add vratilo vysledok.
// 4. Na prenos ID sa pouzivaju headers.
//-------------------------------------------------------------------------------------------------------
namespace ResponseCalculatorLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CResponseCalculatorService : IResponseCalculatorContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CResponseCalculatorService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void OnAdd1Completed(int ReturnValue, ExceptionDetail Error)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			CMyResponseContext		MyResponseContext=CResponseMSMQHelper.GetMyResponseContext();

			if (Error==null)
				Console.WriteLine(string.Format("Add1()={0}, ID: {1} !",ReturnValue,MyResponseContext.MethodID));
			else
				Console.WriteLine(string.Format("Add1() - EXCEPTION {0}, ID: {1} !",Error.Message,MyResponseContext.MethodID));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void OnAdd2Completed(int ReturnValue, ExceptionDetail Error)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			CMyResponseContext		MyResponseContext=CResponseMSMQHelper.GetMyResponseContext();

			if (Error==null)
				Console.WriteLine(string.Format("Add2()={0}, ID: {1} !",ReturnValue,MyResponseContext.MethodID));
			else
				Console.WriteLine(string.Format("Add2() - EXCEPTION {0}, ID: {1} !",Error.Message,MyResponseContext.MethodID));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
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