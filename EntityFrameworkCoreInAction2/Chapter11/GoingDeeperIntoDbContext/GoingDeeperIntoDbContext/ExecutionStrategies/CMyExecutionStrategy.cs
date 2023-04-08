using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Implementacia CUSTOM EXECUTION STRATEGY.
	// !!!!! CUSTOM EXECUTION STRATEGY by napriklad mohla spravit RETRY ak dojde k vypadku komunikacie medzi ENTITY FRAMEWORK CORE a DATABASE SERVER.
	public sealed class CMyExecutionStrategy : IExecutionStrategy
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ExecutionStrategyDependencies			MDependencies;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CMyExecutionStrategy(ExecutionStrategyDependencies Dependencies)
		{
			MDependencies=Dependencies;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public bool												RetriesOnFailure
		{
			get
			{
				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public TResult Execute<TState,TResult>(TState State, Func<DbContext,TState,TResult> Operation, Func<DbContext,TState,ExecutionResult<TResult>> VerifySucceeded)
		{
			try
			{
				CConsoleHelpers.WriteLine("EXECUTION STRATEGY EXECUTING !!!",ConsoleColor.DarkGray);

				TResult											Result=Operation(MDependencies.CurrentContext.Context,State);

				CConsoleHelpers.WriteLine("EXECUTION STRATEGY EXECUTED !!!",ConsoleColor.DarkGray);

				return(Result);
			}
			catch(Exception E)
			{
				throw(new InvalidOperationException("DB OPERATION FAILED !!!",E));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<TResult> ExecuteAsync<TState,TResult>(TState State, Func<DbContext,TState,CancellationToken,Task<TResult>> Operation, Func<DbContext,TState,CancellationToken,Task<ExecutionResult<TResult>>> VerifySucceeded, CancellationToken CancellationToken)
		{
			try
			{
				CConsoleHelpers.WriteLine("EXECUTION STRATEGY EXECUTING (ASYNCHRONOUSLY) !!!",ConsoleColor.DarkGray);

				TResult											Result=await Operation(MDependencies.CurrentContext.Context,State,CancellationToken).ConfigureAwait(false);

				CConsoleHelpers.WriteLine("EXECUTION STRATEGY EXECUTED (ASYNCHRONOUSLY) !!!",ConsoleColor.DarkGray);

				return(Result);
			}
			catch(Exception E)
			{
				throw(new InvalidOperationException("DB OPERATION FAILED !!!",E));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------