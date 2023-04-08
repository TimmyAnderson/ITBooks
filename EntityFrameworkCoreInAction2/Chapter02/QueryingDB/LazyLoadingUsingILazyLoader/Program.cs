using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace LazyLoadingUsingILazyLoader
{
//----------------------------------------------------------------------------------------------------------------------
	class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		public static void CreateTestDB()
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
							Context.Database.EnsureCreated();

							CEntityDependent					EntityDependent11=new CEntityDependent("AAA 111");
							CEntityDependent					EntityDependent12=new CEntityDependent("AAA 222");
							CEntityDependent					EntityDependent21=new CEntityDependent("BBB 111");
							CEntityDependent					EntityDependent22=new CEntityDependent("BBB 222");

							CEntityPrincipal					EntityPrincipal1=new CEntityPrincipal("AAA",new CEntityDependent[]{EntityDependent11,EntityDependent12});
							CEntityPrincipal					EntityPrincipal2=new CEntityPrincipal("BBB",new CEntityDependent[]{EntityDependent21,EntityDependent22});

							Context.EntitiesPrincipal.Add(EntityPrincipal1);
							Context.EntitiesPrincipal.Add(EntityPrincipal2);

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
		public static void TestSelect()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext(true))
				{
					try
					{
						CEntityPrincipal[]						EntitiesPrincipal=Context.EntitiesPrincipal.ToArray();

						for(int Index=0;Index<EntitiesPrincipal.Length;Index++)
						{
							CEntityPrincipal					EntityPrincipal=EntitiesPrincipal[Index];
							// !!! Zobrazia sa PROPERTIES BEZ prechodu cez LAZY LOADED NAVIGATION PROPERTY.
							string								EntityPrincipalText=EntityPrincipal.Print(Index+1);

							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityPrincipalText,ConsoleColor.Green);
						}

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();

						for(int Index=0;Index<EntitiesPrincipal.Length;Index++)
						{
							CEntityPrincipal					EntityPrincipal=EntitiesPrincipal[Index];

							// !!!!! Explicitnym pristupom k NAVIGATION PROPERTY sa vykona LAZY LOADING.
							EntityPrincipal.EntitiesDependent.ToArray();
						}

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();

						for(int Index=0;Index<EntitiesPrincipal.Length;Index++)
						{
							CEntityPrincipal					EntityPrincipal=EntitiesPrincipal[Index];
							// !!! Zobrazia sa PROPERTIES aj s prechodom cez LAZY LOADED NAVIGATION PROPERTY.
							// !!!!! ENTITY FRAMEWORK vykona LAZY LOADING.
							string								EntityPrincipalText=EntityPrincipal.Print(Index+1);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityPrincipalText,ConsoleColor.Green);
						}

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLineSeparator();

						for(int Index=0;Index<EntitiesPrincipal.Length;Index++)
						{
							CEntityPrincipal					EntityPrincipal=EntitiesPrincipal[Index];
							// !!! Zobrazia sa PROPERTIES aj s prechodom cez LAZY LOADED NAVIGATION PROPERTY.
							// !!!!! ENTITY FRAMEWORK uz NEVYKONA LAZY LOADING, pretoze DEPENDENT OBJECTS uz BOLI NACITANE a teda su v MEMORY.
							string								EntityPrincipalText=EntityPrincipal.Print(Index+1);

							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.WriteLine(EntityPrincipalText,ConsoleColor.Green);
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
			TestSelect();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------