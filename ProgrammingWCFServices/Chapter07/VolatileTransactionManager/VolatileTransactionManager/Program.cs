using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
//-------------------------------------------------------------------------------------------------------
namespace VolatileTransactionManager
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CName		Name1=new CName();
			CName		Name2=new CName();

			Name1.FirstName="Timmy";
			Name1.LastName="Anderson";
			Name2.FirstName="Jenny";
			Name2.LastName="Thompson";

			Console.WriteLine("BEFORE SCOPE");
			Console.WriteLine(string.Format("Name1: {0} !",Name1));
			Console.WriteLine(string.Format("Name2: {0} !",Name2));

			using(TransactionScope Scope=new TransactionScope())
			{
				Name1.FirstName=Name1.FirstName.ToUpper();
				Name1.LastName=Name1.LastName.ToUpper();
				Name2.FirstName=Name2.FirstName.ToUpper();
				Name2.LastName=Name2.LastName.ToUpper();

				Console.WriteLine("AFTER CHANGE");
				Console.WriteLine(string.Format("Name1: {0} !",Name1));
				Console.WriteLine(string.Format("Name2: {0} !",Name2));

				Scope.Complete();
				Console.WriteLine("Scope.Complete() CALLED !");
			}

			Console.WriteLine("AFTER SCOPE");
			Console.WriteLine(string.Format("Name1: {0} !",Name1));
			Console.WriteLine(string.Format("Name2: {0} !",Name2));
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			CName		Name1=new CName();
			CName		Name2=new CName();

			Name1.FirstName="Timmy";
			Name1.LastName="Anderson";
			Name2.FirstName="Jenny";
			Name2.LastName="Thompson";

			Console.WriteLine("BEFORE SCOPE");
			Console.WriteLine(string.Format("Name1: {0} !",Name1));
			Console.WriteLine(string.Format("Name2: {0} !",Name2));

			using(TransactionScope Scope=new TransactionScope())
			{
				Name1.FirstName=Name1.FirstName.ToUpper();
				Name1.LastName=Name1.LastName.ToUpper();
				Name2.FirstName=Name2.FirstName.ToUpper();
				Name2.LastName=Name2.LastName.ToUpper();

				Console.WriteLine("AFTER CHANGE");
				Console.WriteLine(string.Format("Name1: {0} !",Name1));
				Console.WriteLine(string.Format("Name2: {0} !",Name2));

				Console.WriteLine("!!!!!!! Scope.Complete() NOT CALLED - TRANSACTION will be ROLLBACKED !");
			}

			Console.WriteLine("AFTER SCOPE");
			Console.WriteLine(string.Format("Name1: {0} !",Name1));
			Console.WriteLine(string.Format("Name2: {0} !",Name2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------