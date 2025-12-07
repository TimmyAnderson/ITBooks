using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuObservability : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									SEPARATOR="--------------------------------------------------------------------------------";
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuObservability()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private CMyHttpClientOperationResponse ExecuteTestMethod1Task(object Parameter)
		{
			Tuple<int,int>										TypedParameter=(Tuple<int,int>) Parameter;

			int													ID=TypedParameter.Item1;
			int													MaxWaitTimeoutInMS=TypedParameter.Item2;

			string												MessageID=TypedParameter.Item1.ToString();
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}Observability/TestMethod1?ID={ID}&MaxWaitTimeoutInMS={MaxWaitTimeoutInMS}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			CMyHttpClientOperationResponse						Response=CMyHttpClient.ExecuteMessage(Request,false);

			return(Response);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private CMyHttpClientOperationResponse ExecuteTestMethod2Task(object Parameter)
		{
			Tuple<int,int>										TypedParameter=(Tuple<int,int>) Parameter;

			int													ID=TypedParameter.Item1;
			int													MaxWaitTimeoutInMS=TypedParameter.Item2;

			string												MessageID=TypedParameter.Item1.ToString();
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}Observability/TestMethod2?ID={ID}&MaxWaitTimeoutInMS={MaxWaitTimeoutInMS}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			CMyHttpClientOperationResponse						Response=CMyHttpClient.ExecuteMessage(Request,false);

			return(Response);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestMethods1(string CommandID, object[] Parameters)
		{
			int													NumberOfRequests=((int) Parameters[0]);
			int													MaxWaitTimeoutInMS=((int) Parameters[1]);

			List<Task<CMyHttpClientOperationResponse>>			Tasks=new List<Task<CMyHttpClientOperationResponse>>();

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				Tuple<int,int>									TaskParameter=new Tuple<int,int>(Index+1,MaxWaitTimeoutInMS);
				Task<CMyHttpClientOperationResponse>			Task=new Task<CMyHttpClientOperationResponse>(ExecuteTestMethod1Task,TaskParameter);

				Tasks.Add(Task);
			}

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				Task<CMyHttpClientOperationResponse>			Task=Tasks[Index];

				Task.Start();
			}

			while(Tasks.Count>0)
			{
				Task<CMyHttpClientOperationResponse>[]			TasksToComplete=Tasks.ToArray();
				int												TaskIndex=Task.WaitAny(TasksToComplete);
				Task<CMyHttpClientOperationResponse>			CompletedTask=Tasks[TaskIndex];

				CMyHttpClientOperationResponse					Response=CompletedTask.Result;
				string											ResponseText=Response.GetMessageAsText();

				Console.WriteLine(ResponseText);
				Console.WriteLine(SEPARATOR);
				Console.WriteLine(SEPARATOR);
				Console.WriteLine(SEPARATOR);

				Tasks.RemoveAt(TaskIndex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestMethods2(string CommandID, object[] Parameters)
		{
			int													NumberOfRequests=((int) Parameters[0]);
			int													MaxWaitTimeoutInMS=((int) Parameters[1]);

			List<Task<CMyHttpClientOperationResponse>>			Tasks=new List<Task<CMyHttpClientOperationResponse>>();

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				Tuple<int,int>									TaskParameter=new Tuple<int,int>(Index+1,MaxWaitTimeoutInMS);
				Task<CMyHttpClientOperationResponse>			Task=new Task<CMyHttpClientOperationResponse>(ExecuteTestMethod2Task,TaskParameter);

				Tasks.Add(Task);
			}

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				Task<CMyHttpClientOperationResponse>			Task=Tasks[Index];

				Task.Start();
			}

			while(Tasks.Count>0)
			{
				Task<CMyHttpClientOperationResponse>[]			TasksToComplete=Tasks.ToArray();
				int												TaskIndex=Task.WaitAny(TasksToComplete);
				Task<CMyHttpClientOperationResponse>			CompletedTask=Tasks[TaskIndex];

				CMyHttpClientOperationResponse					Response=CompletedTask.Result;
				string											ResponseText=Response.GetMessageAsText();

				Console.WriteLine(ResponseText);
				Console.WriteLine(SEPARATOR);
				Console.WriteLine(SEPARATOR);
				Console.WriteLine(SEPARATOR);

				Tasks.RemoveAt(TaskIndex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","EXECUTE TEST METHODS 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandTestMethods1));
			CommandsCollection.Add(new CMenuCommand("2","EXECUTE TEST METHODS 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandTestMethods2));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------