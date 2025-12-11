using System;
using System.Threading;
using System.Threading.Tasks;
using MediatR;
//----------------------------------------------------------------------------------------------------------------------
namespace CqrsCore
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CHandlerWriteToLog2 : INotificationHandler<CNotificationWriteToLog>
	{
//----------------------------------------------------------------------------------------------------------------------
		public Task Handle(CNotificationWriteToLog Request, CancellationToken CancellationToken)
		{
			Console.WriteLine($"LOG 2 - OPERATION [{Request.Operation}] - NAME - ID [{Request.FullName.ID}] FIRST NAME [{Request.FullName.FirstName}] LAST NAME [{Request.FullName.LastName}] AGE [{Request.FullName.Age}] SEX [{Request.FullName.Sex}].");

			Task												CompletedTask=Task.CompletedTask;
			
			return(CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------