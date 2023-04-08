using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionReleaseInstanceOnCompleteLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession, ReleaseServiceInstanceOnTransactionComplete=false)]
	public class CPerSessionReleaseInstanceOnCompleteService : IPerSessionReleaseInstanceOnCompleteContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private string											MValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPerSessionReleaseInstanceOnCompleteService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintSessionID()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Console.WriteLine(string.Format("SessionID: {0} !",OperationContext.Current.SessionId));
			Console.WriteLine(string.Format("Value: {0} !",MValue));
		}
//-------------------------------------------------------------------------------------------------------
		public void NoTransaction(string Value)
		{
			MValue=Value;

			Console.WriteLine(string.Format("NoTransaction() - Value: {0} !",MValue));

			Console.WriteLine(string.Format("NoTransaction() - SessionID: {0} !",OperationContext.Current.SessionId));

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void DoTransaction(string Value)
		{
			Console.WriteLine(string.Format("NoTransaction() - Value BEFORE SET: {0} !",MValue));

			MValue=Value;

			Console.WriteLine(string.Format("NoTransaction() - Value AFTER SET: {0} !",MValue));

			Console.WriteLine(string.Format("SessionID: {0} !",OperationContext.Current.SessionId));

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
			Console.WriteLine(string.Format("Value: {0} !",MValue));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------