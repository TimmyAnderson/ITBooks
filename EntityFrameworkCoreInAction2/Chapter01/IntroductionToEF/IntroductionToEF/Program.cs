using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace IntroductionToEF
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			CTestEntity											TestEntity1=new CTestEntity("XXX");
			CTestEntity											TestEntity2=new CTestEntity("YYY");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);

			CDependentEntity									DependentEntity1=new CDependentEntity("AAA 11");
			CDependentEntity									DependentEntity2=new CDependentEntity("AAA 12");
			CDependentEntity									DependentEntity3=new CDependentEntity("BBB 13");
			CDependentEntity									DependentEntity4=new CDependentEntity("BBB 14");

			CPrincipalEntity									PrincipalEntity1=new CPrincipalEntity("AAA",new CDependentEntity[]{DependentEntity1,DependentEntity2});
			CPrincipalEntity									PrincipalEntity2=new CPrincipalEntity("BBB",new CDependentEntity[]{DependentEntity3,DependentEntity4});

			Context.PrincipalEntities.Add(PrincipalEntity1);
			Context.PrincipalEntities.Add(PrincipalEntity2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintPrincipalEntities()
		{
			using(CDBContext Context=new CDBContext())
			{
				try
				{
					CPrincipalEntity[]							PrincipalEntities=Context.PrincipalEntities.Include(P => P.DependentEntities).ToArray();

					for(int Index=0;Index<PrincipalEntities.Length;Index++)
					{
						CPrincipalEntity						PrincipalEntity=PrincipalEntities[Index];
						string									PrincipalEntityText=PrincipalEntity.Print(Index+1,0);

						if (Index>0)
						{
							CConsoleHelpers.WriteLineSeparator();
						}

						CConsoleHelpers.Write(PrincipalEntityText,ConsoleColor.Green);
					}
				}
				catch(Exception E)
				{
					CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
				}
			}
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
					CConsoleHelpers.WriteLine($"DATABASE NOT CREATED !",ConsoleColor.Red);
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
		public static void TestSelectTestEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CTestEntity[]							Entities=Context.TestEntities.ToArray();

						for(int Index=0;Index<Entities.Length;Index++)
						{
							CTestEntity							Entity=Entities[Index];
							string								EntityText=Entity.Print(Index+1);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
						}
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
		public static void TestReadEntities()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CPrincipalEntity[]						Entities=Context.PrincipalEntities.Include(P => P.DependentEntities).AsNoTracking().ToArray();

						for(int Index=0;Index<Entities.Length;Index++)
						{
							CPrincipalEntity					Entity=Entities[Index];
							string								EntityText=Entity.Print(Index+1,0);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
						}
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
		public static void TestInsertUpdateDeleteEntities()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				int												PrincipalEntityID=0;

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CDependentEntity						DependentEntity1=new CDependentEntity("CCC 15");
						CDependentEntity						DependentEntity2=new CDependentEntity("CCC 16");
						CPrincipalEntity						PrincipalEntity=new CPrincipalEntity("CCC",new CDependentEntity[]{DependentEntity1,DependentEntity2});

						CConsoleHelpers.WriteLine($"NEW RECORD BEFORE ADD - RECORD [{PrincipalEntity.Print(null,0)}] !",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLineSeparator();

						// !!! Prida sa novy RECORD do DB.
						Context.PrincipalEntities.Add(PrincipalEntity);

						CConsoleHelpers.WriteLine($"NEW RECORD AFTER ADD - RECORD [{PrincipalEntity.Print(null,0)}] !",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLineSeparator();

						// !!! Vykona sa zapis RECORD do DB.
						Context.SaveChanges();

						// !!!!! Po zapise RECORD do DB su uz zapisane IDENTIFIERS.
						CConsoleHelpers.WriteLine($"NEW RECORD AFTER SAVE - RECORD [{PrincipalEntity.Print(null,0)}] !",ConsoleColor.Yellow);

						PrincipalEntityID=PrincipalEntity.PrincipalEntityID;

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				PrintPrincipalEntities();

				CConsoleHelpers.WriteLineSeparator();
				CConsoleHelpers.WriteLineSeparator();
				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CPrincipalEntity						PrincipalEntity=Context.PrincipalEntities.Where(P => P.PrincipalEntityID==PrincipalEntityID).Include(P => P.DependentEntities).FirstOrDefault();

						PrincipalEntity.Value=PrincipalEntity.Value+" CHANGED !!!!!";

						// !!! Vykona sa UPDATE RECORD v DB.
						Context.PrincipalEntities.Update(PrincipalEntity);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"EXISTING RECORD UPDATED - RECORD [{PrincipalEntity.Print(null,0)}] !",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				PrintPrincipalEntities();

				CConsoleHelpers.WriteLineSeparator();
				CConsoleHelpers.WriteLineSeparator();
				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CPrincipalEntity						PrincipalEntity=Context.PrincipalEntities.Where(P => P.PrincipalEntityID==PrincipalEntityID).Include(P => P.DependentEntities).FirstOrDefault();

						// !!! Vykona sa DELETE RECORD v DB.
						Context.PrincipalEntities.Remove(PrincipalEntity);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"EXISTING RECORD DELETED - RECORD [{PrincipalEntity.Print(null,0)}] !",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				PrintPrincipalEntities();
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
		public static void CheckDuplicityForEntityObjects()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CPrincipalEntity[]						Entities=Context.PrincipalEntities.Include(P => P.DependentEntities).AsNoTracking().ToArray();

						for(int Index=0;Index<Entities.Length;Index++)
						{
							CPrincipalEntity					Entity=Entities[Index];
							string								EntityText=Entity.Print(Index+1,0);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityText,ConsoleColor.Green);

							CConsoleHelpers.WriteLineSeparator();

							if (Entity.DependentEntities.Count>0)
							{
								CDependentEntity				DependentEntity1=Entity.DependentEntities.First();

								foreach(CDependentEntity DependentEntity2 in Entity.DependentEntities.Skip(1))
								{
									CPrincipalEntity			PrincipalEntity1=DependentEntity1.PrincipalEntity;
									CPrincipalEntity			PrincipalEntity2=DependentEntity2.PrincipalEntity;

									if (object.ReferenceEquals(PrincipalEntity1,PrincipalEntity2)==true)
									{
										CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.Value}] and PRINCIPAL ENTITY [{PrincipalEntity2.Value}] refer to the EQUAL OBJECT.",ConsoleColor.Yellow);
									}
									else
									{
										CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.Value}] and PRINCIPAL ENTITY [{PrincipalEntity2.Value}] refer to the NOT-EQUAL OBJECTS.",ConsoleColor.Yellow);
									}
								}
							}
						}
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
			//TestReadEntities();
			//TestInsertUpdateDeleteEntities();
			CheckDuplicityForEntityObjects();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------