using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityLazyLoadingPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Instancia CLASS implementujucej INTERFACE [ILazyLoader], ktora sa pouziva na vykonanie LAZY LOADING.
		private readonly ILazyLoader							MLazyLoader;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		private ICollection<CEntityLazyLoadingDependent>		MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! CONSTRUCTOR vola ENTITY FRAMEWORK, ktory zasle instanciu LAZY LOADER.
		public CEntityLazyLoadingPrincipal(ILazyLoader LazyLoader)
		{
			MLazyLoader=LazyLoader;
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=default(string);
			MEntitiesDependent=default(ICollection<CEntityLazyLoadingDependent>);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityLazyLoadingPrincipal(string EntityPrincipalValue, ICollection<CEntityLazyLoadingDependent> EntitiesDependent)
		{
			MLazyLoader=default(ILazyLoader);
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalID
		{
			get
			{
				return(MEntityPrincipalID);
			}
			set
			{
				MEntityPrincipalID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalValue
		{
			get
			{
				return(MEntityPrincipalValue);
			}
			set
			{
				MEntityPrincipalValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY, ktora v GETTER vykonava LAZY LOADING.
		public ICollection<CEntityLazyLoadingDependent>			EntitiesDependent
		{
			get
			{
				if (MLazyLoader!=null)
				{
					// !!! Volanim METHOD [ILazyLoader.Load()] sa vykona LAZY LOADING, ak OBJECT este NEBOL NACITANY.
					MLazyLoader.Load(this,ref MEntitiesDependent);
				}
				
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityLazyLoadingPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityLazyLoadingPrincipal						Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string Print(int? Index)
		{
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"ENTITY PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES N:");

				int												EntityDependentIndex=1;

				foreach(CEntityLazyLoadingDependent EntityDependent in MEntitiesDependent)
				{
					SB.AppendLine($"\t\tENTITY DEPENDENT [{EntityDependentIndex}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");

					EntityDependentIndex++;
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------