using System;
using System.Threading;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMyLoggerService : IMyLoggerService
	{
//----------------------------------------------------------------------------------------------------------------------
		public void LogDataLoader(string ClassName, string MethodName)
		{
			Console.WriteLine($"!!!!!!!!!! DATA LOADER [{ClassName}.{MethodName}()] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void LogResolver(string ClassName, string MethodName)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{ClassName}.{MethodName}()] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------