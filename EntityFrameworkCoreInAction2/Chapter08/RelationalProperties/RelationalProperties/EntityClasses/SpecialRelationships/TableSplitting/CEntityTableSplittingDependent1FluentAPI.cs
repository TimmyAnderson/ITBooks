using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je DEPENDENT ENTITY, pretoze OBSAHUJE FOREIGN KEY PROPERTY.
	public sealed class CEntityTableSplittingDependent1FluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PRIMARY KEY je zaroven aj FOREIGN KEY.
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue1;
		// !!! PROPERTY bude MAPPED to rovnakeho COLUMN ako v ENTITY 'CEntityTableSplittingDependent2FluentAPI'.
		private string											MEntitySharedValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAVIGATION PROPERTY na PRINCIPAL ENTITY.
		private CEntityTableSplittingPrincipalFluentAPI			MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableSplittingDependent1FluentAPI()
		{
			MEntityDependentID=default;
			MEntityDependentValue1=default;
			MEntitySharedValue=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableSplittingDependent1FluentAPI(string EntityDependentValue1, string EntitySharedValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue1=EntityDependentValue1;
			MEntitySharedValue=EntitySharedValue;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityDependentID
		{
			get
			{
				return(MEntityDependentID);
			}
			set
			{
				MEntityDependentID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Ak DEPENDENT ENTITY nema ziadnu NON-NULLABLE PROPERTY, ENTITY FRAMEWORK CORE NEDOKAZE rozlisit kedy je cela DEPENDENT ENTITY NULL a nema pre nu vytvarat instanciu DEPENDENT ENTITY CLASS. ENTITY FRAMEWORK CORE totizto BY-DEFAULT povazuje celu DEPENDENT ENTITY za NULL, ak su vsetky jej PROPERTIES NULL a vtedy nevytvara instanciu DEPENDENT ENTITY CLASS. Ak vsak ani jedna PROPERTY DEPENDENT ENTITY nie je NON-NULLABLE, ENTITY FRAMEWORK CORE nedokaze toto rozlisenie spravit. Riesenim je pridanie NON-NULLABLE PROPERTY, alebo oznacenie niektorej z BY-DEFAULT NULLABLE PROPERTY za REQUIRED PROPERTY. Alternativou je oznacit NAVIGATION PROPERTY za REQUIRED.
		//[Required]
		public string											EntityDependentValue1
		{
			get
			{
				return(MEntityDependentValue1);
			}
			set
			{
				MEntityDependentValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntitySharedValue
		{
			get
			{
				return(MEntitySharedValue);
			}
			set
			{
				MEntitySharedValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTableSplittingPrincipalFluentAPI			EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				MEntityPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityTableSplittingDependent1FluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTableSplittingDependent1FluentAPI		Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TABLE SPLITTING DEPENDENT 1 FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TABLE SPLITTING DEPENDENT 1 FLUENT API:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE 1 [{MEntityDependentValue1}] !");
			SB.AppendLine($"\tENTITY SHARED VALUE [{MEntitySharedValue}] !");

			if (MEntityPrincipal!=null)
			{
				SB.AppendLine($"\tENTITY PRINCIPAL:");

				SB.AppendLine($"\t\tENTITY PRINCIPAL ID [{MEntityPrincipal.EntityPrincipalID}] !");
				SB.AppendLine($"\t\tENTITY PRINCIPAL VALUE [{MEntityPrincipal.EntityPrincipalValue}] !");
			}
			else
			{
				SB.AppendLine($"\t--- ENTITY PRINCIPAL is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------