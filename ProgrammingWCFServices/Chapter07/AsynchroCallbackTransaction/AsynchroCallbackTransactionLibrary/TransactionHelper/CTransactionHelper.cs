using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
//-------------------------------------------------------------------------------------------------------
namespace TransactionHelper
{
//-------------------------------------------------------------------------------------------------------
	public static class CTransactionHelper
	{
//-------------------------------------------------------------------------------------------------------
		private static string									MConnectStringDB1="Data Source=(local);Initial Catalog=DB1;Integrated Security=True";
		private static string									MConnectStringDB2="Data Source=(local);Initial Catalog=DB2;Integrated Security=True";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static string GetExceptionString(Exception E)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("EXCEPTION ({0}): {1}.{2}() - {3} !",E.GetType().Name,SF.GetMethod().DeclaringType.Name,SF.GetMethod().Name,E.Message));
		}
//-------------------------------------------------------------------------------------------------------
		private static string GetConnectionString(EDBID DBID)
		{
			if (DBID==EDBID.E_DI_DB_1)
				return(MConnectStringDB1);
			else if (DBID==EDBID.E_DI_DB_2)
				return(MConnectStringDB2);
			else
				return("");
		}
//-------------------------------------------------------------------------------------------------------
		private static string GetTableName(ETableID TableID)
		{
			if (TableID==ETableID.E_TI_TABLE_1)
				return("Table1");
			else if (TableID==ETableID.E_TI_TABLE_2)
				return("Table2");
			else
				return("");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static void DeleteAll(EDBID DBID)
		{
			DeleteTable(DBID,ETableID.E_TI_TABLE_1);
			DeleteTable(DBID,ETableID.E_TI_TABLE_2);
		}
//-------------------------------------------------------------------------------------------------------
		public static void DeleteTable(EDBID DBID, ETableID TableID)
		{
			IDbConnection			Connection=null;
			IDbCommand				Command=null;

			try
			{
				Connection=new SqlConnection(GetConnectionString(DBID));

				Connection.Open();

				Command=new SqlCommand();
				Command.Connection=Connection;
				Command.CommandText="DELETE FROM " + GetTableName(TableID);

				Command.ExecuteNonQuery();
			}
			catch(Exception E)
			{
				Console.WriteLine(GetExceptionString(E));
			}
			finally
			{
				if (Connection!=null)
				{
					Connection.Dispose();
					Connection=null;
				}

				if (Command!=null)
				{
					Command.Dispose();
					Command=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void InsertValue(EDBID DBID, ETableID TableID, string Value, Transaction T)
		{
			IDbConnection			Connection=null;
			IDbCommand				Command=null;

			try
			{
				Connection=new SqlConnection(GetConnectionString(DBID));

				Connection.Open();

				Command=new SqlCommand();
				Command.Connection=Connection;

				if (T!=null)
					Command.CommandText="INSERT INTO " + GetTableName(TableID) + " ([Value], [LID], [GID]) VALUES ('" + Value + "', '" + (T.TransactionInformation.LocalIdentifier ?? "NONE") + "', '" + ((T.TransactionInformation.DistributedIdentifier!=Guid.Empty) ? T.TransactionInformation.DistributedIdentifier.ToString() : "NONE") + "')";
				else
					Command.CommandText="INSERT INTO " + GetTableName(TableID) + " ([Value], [LID], [GID]) VALUES ('" + Value + "', 'T NONE', 'T NONE')";

				Command.ExecuteNonQuery();
			}
			catch(Exception E)
			{
				Console.WriteLine(GetExceptionString(E));
			}
			finally
			{
				if (Connection!=null)
				{
					Connection.Dispose();
					Connection=null;
				}

				if (Command!=null)
				{
					Command.Dispose();
					Command=null;
				}
			}
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------