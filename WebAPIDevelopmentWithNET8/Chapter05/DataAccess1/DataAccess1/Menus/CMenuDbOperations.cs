using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess1
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuDbOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuDbOperations()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static void FillDatabase1(CDBContext Context)
		{
			CEntityConventionsOneToManyDependent				EntityOneToManyDependentConventions11=new CEntityConventionsOneToManyDependent("DEPENDENT 111");
			CEntityConventionsOneToManyDependent				EntityOneToManyDependentConventions12=new CEntityConventionsOneToManyDependent("DEPENDENT 222");
			CEntityConventionsOneToManyDependent				EntityOneToManyDependentConventions21=new CEntityConventionsOneToManyDependent("DEPENDENT 333");
			CEntityConventionsOneToManyDependent				EntityOneToManyDependentConventions22=new CEntityConventionsOneToManyDependent("DEPENDENT 444");

			CEntityConventionsOneToManyPrincipal				EntityOneToManyPrincipalConventions1=new CEntityConventionsOneToManyPrincipal("PRINCIPAL 111",new CEntityConventionsOneToManyDependent[]{EntityOneToManyDependentConventions11,EntityOneToManyDependentConventions12});
			CEntityConventionsOneToManyPrincipal				EntityOneToManyPrincipalConventions2=new CEntityConventionsOneToManyPrincipal("PRINCIPAL 222",new CEntityConventionsOneToManyDependent[]{EntityOneToManyDependentConventions21,EntityOneToManyDependentConventions22});

			Context.EntitiesConventionsOneToManyPrincipal.Add(EntityOneToManyPrincipalConventions1);
			Context.EntitiesConventionsOneToManyPrincipal.Add(EntityOneToManyPrincipalConventions2);

			Context.SaveChanges();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void FillDatabase2(CDBContext Context)
		{
			CEntityDataAnnotationsOneToManyDependent			EntityOneToManyDependentDataAnnotations11=new CEntityDataAnnotationsOneToManyDependent("DEPENDENT 111");
			CEntityDataAnnotationsOneToManyDependent			EntityOneToManyDependentDataAnnotations12=new CEntityDataAnnotationsOneToManyDependent("DEPENDENT 222");
			CEntityDataAnnotationsOneToManyDependent			EntityOneToManyDependentDataAnnotations21=new CEntityDataAnnotationsOneToManyDependent("DEPENDENT 333");
			CEntityDataAnnotationsOneToManyDependent			EntityOneToManyDependentDataAnnotations22=new CEntityDataAnnotationsOneToManyDependent("DEPENDENT 444");

			CEntityDataAnnotationsOneToManyPrincipal			EntityOneToManyPrincipalDataAnnotations1=new CEntityDataAnnotationsOneToManyPrincipal("PRINCIPAL 111",new CEntityDataAnnotationsOneToManyDependent[]{EntityOneToManyDependentDataAnnotations11,EntityOneToManyDependentDataAnnotations12});
			CEntityDataAnnotationsOneToManyPrincipal			EntityOneToManyPrincipalDataAnnotations2=new CEntityDataAnnotationsOneToManyPrincipal("PRINCIPAL 222",new CEntityDataAnnotationsOneToManyDependent[]{EntityOneToManyDependentDataAnnotations21,EntityOneToManyDependentDataAnnotations22});

			Context.EntitiesDataAnnotationsOneToManyPrincipal.Add(EntityOneToManyPrincipalDataAnnotations1);
			Context.EntitiesDataAnnotationsOneToManyPrincipal.Add(EntityOneToManyPrincipalDataAnnotations2);

			Context.SaveChanges();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void FillDatabase3(CDBContext Context)
		{
			CEntityFluentAPIOneToManyDependent					EntityOneToManyDependentFluentAPI11=new CEntityFluentAPIOneToManyDependent("DEPENDENT 111");
			CEntityFluentAPIOneToManyDependent					EntityOneToManyDependentFluentAPI12=new CEntityFluentAPIOneToManyDependent("DEPENDENT 222");
			CEntityFluentAPIOneToManyDependent					EntityOneToManyDependentFluentAPI21=new CEntityFluentAPIOneToManyDependent("DEPENDENT 333");
			CEntityFluentAPIOneToManyDependent					EntityOneToManyDependentFluentAPI22=new CEntityFluentAPIOneToManyDependent("DEPENDENT 444");

			CEntityFluentAPIOneToManyPrincipal					EntityOneToManyPrincipalFluentAPI1=new CEntityFluentAPIOneToManyPrincipal("PRINCIPAL 111",new CEntityFluentAPIOneToManyDependent[]{EntityOneToManyDependentFluentAPI11,EntityOneToManyDependentFluentAPI12});
			CEntityFluentAPIOneToManyPrincipal					EntityOneToManyPrincipalFluentAPI2=new CEntityFluentAPIOneToManyPrincipal("PRINCIPAL 222",new CEntityFluentAPIOneToManyDependent[]{EntityOneToManyDependentFluentAPI21,EntityOneToManyDependentFluentAPI22});

			Context.EntitiesFluentAPIOneToManyPrincipal.Add(EntityOneToManyPrincipalFluentAPI1);
			Context.EntitiesFluentAPIOneToManyPrincipal.Add(EntityOneToManyPrincipalFluentAPI2);

			Context.SaveChanges();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void FillDatabase4(CDBContext Context)
		{
			CEntitySeparateConfigurations						EntitySeparateConfigurations1=new CEntitySeparateConfigurations(100,null,null,"BBB","CCC",new DateTime(2001,1,1),123.123);
			CEntitySeparateConfigurations						EntitySeparateConfigurations2=new CEntitySeparateConfigurations(200,300,"DDD","EEE","FFF",new DateTime(2002,2,2),456.456);

			Context.EntitiesSeparateConfigurations.Add(EntitySeparateConfigurations1);
			Context.EntitiesSeparateConfigurations.Add(EntitySeparateConfigurations2);

			Context.SaveChanges();
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCreateDatabase(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					if (Context.Database.CanConnect()==false)
					{
						Context.Database.Migrate();

						FillDatabase1(Context);
						FillDatabase2(Context);
						FillDatabase3(Context);
						FillDatabase4(Context);

						Console.WriteLine("DATABASE CREATED !");
					}
					else
					{
						Console.WriteLine("Can't CONNECT to DATABASE.");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandConventions(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConventionsOneToManyPrincipal[]		Entities=Context.EntitiesConventionsOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

					CEntityConventionsOneToManyPrincipal.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDataAnnotations(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityDataAnnotationsOneToManyPrincipal[]	Entities=Context.EntitiesDataAnnotationsOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

					CEntityDataAnnotationsOneToManyPrincipal.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandFluentAPI(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityFluentAPIOneToManyPrincipal[]		Entities=Context.EntitiesFluentAPIOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

					CEntityFluentAPIOneToManyPrincipal.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSeparateConfiguration(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntitySeparateConfigurations[]				Entities=Context.EntitiesSeparateConfigurations.ToArray();

					CEntitySeparateConfigurations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetNames(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityName[]								Entities=Context.EntitiesNames.ToArray();

					foreach(CEntityName EntityName in Entities)
					{
						Console.WriteLine($"ID [{EntityName.ID}] FIRST NAME [{EntityName.FirstName}] LAST NAME [{EntityName.LastName}] AGE [{EntityName.Age}] SEX [{EntityName.Sex}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("db","CREATE DB",new EMenuCommandParameterType[0],ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("1","CONVENTIONS",new EMenuCommandParameterType[0],ExecuteCommandConventions));
			CommandsCollection.Add(new CMenuCommand("2","DATA ANNOTATIONS",new EMenuCommandParameterType[0],ExecuteCommandDataAnnotations));
			CommandsCollection.Add(new CMenuCommand("3","FLUENT API",new EMenuCommandParameterType[0],ExecuteCommandFluentAPI));
			CommandsCollection.Add(new CMenuCommand("4","SEPARATE CONFIGURATION",new EMenuCommandParameterType[0],ExecuteCommandSeparateConfiguration));
			CommandsCollection.Add(new CMenuCommand("5","GET NAMES",new EMenuCommandParameterType[0],ExecuteCommandGetNames));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------