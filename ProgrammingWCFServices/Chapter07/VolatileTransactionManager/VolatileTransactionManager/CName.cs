using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
//-------------------------------------------------------------------------------------------------------
namespace VolatileTransactionManager
{
//-------------------------------------------------------------------------------------------------------
	public class CName : IEnlistmentNotification, ISinglePhaseNotification
	{
//-------------------------------------------------------------------------------------------------------
		private Transaction										MTransaction;
		private string											MFirstName;
		private string											MLastName;
		private string											MCommitedFirstName;
		private string											MCommitedLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName()
		{
			MFirstName="NONE";
			MLastName="NONE";
			MCommitedFirstName="NONE";
			MCommitedLastName="NONE";
		}
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MCommitedFirstName=FirstName;
			MCommitedLastName=LastName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;

				if (Enlisted()==false)
					MCommitedFirstName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			internal set
			{
				MLastName=value;

				if (Enlisted()==false)
					MCommitedLastName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void InternalCommit()
		{
			//Console.WriteLine(CDebugHelper.GetMethodCallString());
			MCommitedFirstName=MFirstName;
			MCommitedLastName=MLastName;
		}
//-------------------------------------------------------------------------------------------------------
		private void InternalRollback()
		{
			//Console.WriteLine(CDebugHelper.GetMethodCallString());
			MFirstName=MCommitedFirstName;
			LastName=MCommitedLastName;
		}
//-------------------------------------------------------------------------------------------------------
		private bool Enlisted()
		{
			//Console.WriteLine(CDebugHelper.GetMethodCallString());

			if (MTransaction!=null)
				return(true);

			if ((MTransaction=Transaction.Current)==null)
				return(false);

			MTransaction.EnlistVolatile(this,EnlistmentOptions.None);
			//Console.WriteLine("ENLISTED");
			return(true);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Prepare(PreparingEnlistment PreparingEnlistment)
		{
			Console.WriteLine(string.Format("Prepare(): [{0}] !",ToString()));

			PreparingEnlistment.Prepared();
		}
//-------------------------------------------------------------------------------------------------------
		public void Commit(Enlistment Enlistment)
		{
			Console.WriteLine(string.Format("Commit(): [{0}] !",ToString()));

			InternalCommit();
			MTransaction=null;
			Enlistment.Done();
		}
//-------------------------------------------------------------------------------------------------------
		public void Rollback(Enlistment Enlistment)
		{
			Console.WriteLine(string.Format("Rollback(): [{0}] !",ToString()));

			MTransaction=null;
			InternalRollback();
		}
//-------------------------------------------------------------------------------------------------------
		public void InDoubt(Enlistment Enlistment)
		{
			Console.WriteLine(string.Format("InDoubt(): [{0}] !",ToString()));

			MTransaction=null;

			throw(new TransactionAbortedException("Commit results cannot be determined !"));
		}
//-------------------------------------------------------------------------------------------------------
		public void SinglePhaseCommit(SinglePhaseEnlistment SinglePhaseEnlistment)
		{
			Console.WriteLine(string.Format("SinglePhaseCommit(): [{0}] !",ToString()));

			InternalCommit();
			MTransaction=null;
			SinglePhaseEnlistment.Done();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("FirstName: {0}, LastName: {1}, CommitedFirstName: {2}, CommitedLastName: {3}",MFirstName, MLastName,MCommitedFirstName,MCommitedLastName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------