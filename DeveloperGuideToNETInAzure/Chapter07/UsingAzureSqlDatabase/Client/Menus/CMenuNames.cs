using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuNames : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		//private const string									CONNECTION_STRING="Server=tcp:ta76dbserver.database.windows.net,1433;Initial Catalog=MyDatabase;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;Authentication=\"Active Directory Default\";";
		// !!!!! CONNECTION STRING funguje, IBA ak je na SQL SERVERI VYPNUTA OPTION [Microsoft Entra authentication only].
		private const string									CONNECTION_STRING="Server=tcp:ta76dbserver.database.windows.net,1433;Initial Catalog=MyDatabase;Persist Security Info=False;User ID=mydbadmin;Password=Qaxwsx123+.;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuNames()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetNames(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(CONNECTION_STRING);

			using(CDBContext Context=new CDBContext(OptionsBuilder.Options))
			{
				CEntityName[]									Names=Context.EntitiesNames.ToArray();

				for(int Index=0;Index<Names.Length;Index++)
				{
					CEntityName									Name=Names[Index];

					Console.WriteLine($"{(Index+1)}. ID [{Name.ID}] FIRST NAME [{Name.FirstName}] LAST NAME [{Name.LastName}] AGE [{Name.Age}] SEX [{Name.Sex}].");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(CONNECTION_STRING);

			using(CDBContext Context=new CDBContext(OptionsBuilder.Options))
			{
				CEntityName										Name=Context.EntitiesNames.Where(P => P.ID==ID).FirstOrDefault();

				Console.WriteLine($"FIRST NAME [{Name.FirstName}] LAST NAME [{Name.LastName}] AGE [{Name.Age}] SEX [{Name.Sex}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertName(string CommandID, object[] Parameters)
		{
			string												FirstName=((string) Parameters[0]);
			string												LastName=((string) Parameters[1]);
			int													Age=((int) Parameters[2]);
			ESex												Sex=((ESex) Parameters[3]);
			CEntityName											Name=new CEntityName(FirstName,LastName,Age,Sex);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(CONNECTION_STRING);

			using(CDBContext Context=new CDBContext(OptionsBuilder.Options))
			{
				Context.EntitiesNames.Add(Name);

				Context.SaveChanges();

				Console.WriteLine("RECORD INSERTED.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);
			string												FirstName=((string) Parameters[1]);
			string												LastName=((string) Parameters[2]);
			int													Age=((int) Parameters[3]);
			ESex												Sex=((ESex) Parameters[4]);
			CEntityName											Name=new CEntityName(ID,FirstName,LastName,Age,Sex);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(CONNECTION_STRING);

			using(CDBContext Context=new CDBContext(OptionsBuilder.Options))
			{
				CEntityName										NameFromDB=Context.EntitiesNames.Where(P => P.ID==Name.ID).FirstOrDefault();

				if (NameFromDB!=null)
				{
					EntityEntry<CEntityName>					Entry=Context.Entry(NameFromDB);

					Entry.CurrentValues.SetValues(Name);

					Context.SaveChanges();

					Console.WriteLine("RECORD UPDATED.");
				}
				else
				{
					Console.WriteLine("RECORD NOT FOUND.");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(CONNECTION_STRING);

			using(CDBContext Context=new CDBContext(OptionsBuilder.Options))
			{
				int												NumberOfDeletedItems=Context.EntitiesNames.Where(P => P.ID==ID).ExecuteDelete();

				if (NumberOfDeletedItems==1)
				{
					Console.WriteLine("RECORD DELETED.");
				}
				else
				{
					Console.WriteLine("RECORD NOT FOUND.");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","GET NAMES",new EMenuCommandParameterType[0],ExecuteCommandGetNames));
			CommandsCollection.Add(new CMenuCommand("2","GET NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetName));
			CommandsCollection.Add(new CMenuCommand("3","INSERT NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandInsertName));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandUpdateName));
			CommandsCollection.Add(new CMenuCommand("5","DELETE NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteName));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------