using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace PerformanceTuning2
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			CTestEntity											TestEntity1=new CTestEntity("AAA");
			CTestEntity											TestEntity2=new CTestEntity("BBB");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);

			CEntityDependent									EntityDependent11=new CEntityDependent(111,"DEPENDENT 111");
			CEntityDependent									EntityDependent12=new CEntityDependent(222,"DEPENDENT 222");
			CEntityDependent									EntityDependent21=new CEntityDependent(333,"DEPENDENT 333");
			CEntityDependent									EntityDependent22=new CEntityDependent(444,"DEPENDENT 444");

			CEntityPrincipal									EntityPrincipal1=new CEntityPrincipal(111,"PRINCIPAL 111",new List<CEntityDependent>(new CEntityDependent[]{EntityDependent11,EntityDependent12}));
			CEntityPrincipal									EntityPrincipal2=new CEntityPrincipal(222,"PRINCIPAL 222",new List<CEntityDependent>(new CEntityDependent[]{EntityDependent21,EntityDependent22}));

			Context.EntitiesPrincipal.Add(EntityPrincipal1);
			Context.EntitiesPrincipal.Add(EntityPrincipal2);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void CreateTestDB()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				bool											DatabaseCreated=false;

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						if (Context.Database.CanConnect()==false)
						{
							// !!! Na vytvorenie DB sa pouziva METHOD DatabaseFacade.Migrate().
							Context.Database.Migrate();

							FillData(Context);

							Context.SaveChanges();

							DatabaseCreated=true;
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						DatabaseCreated=false;
					}
				}

				if (DatabaseCreated==true)
				{
					CConsoleHelpers.WriteLine($"DATABASE CREATED !",ConsoleColor.Green);
				}
				else
				{
					CConsoleHelpers.WriteLine($"DATABASE ALREADY EXISTS !",ConsoleColor.Blue);
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestSelectTestEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CTestEntity[]							Entities=Context.TestEntities.ToArray();

						CTestEntity.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestSelectNoInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NORMAL QUERY:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NO INCLUDE QUERY:",ConsoleColor.Cyan);

						// !!!!! V QUERY je mozne referovat na DEPENDENT ENTITIES aj BEZ pouzitia LINQ OPERATOR [Include].
						CDataPrincipal[]						Entities=Context.EntitiesPrincipal.Select(P => new CDataPrincipal(P.EntityPrincipalID,P.EntityPrincipalIntValue,P.EntityPrincipalStringValue,P.EntitiesDependent.Select(Q => new CDataDependent(Q.EntityDependentID,Q.EntityDependentIntValue,Q.EntityDependentStringValue)).ToArray())).ToArray();

						CDataPrincipal.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			//CreateTestDB();
			//TestSelectTestEntity();
			TestSelectNoInclude();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------