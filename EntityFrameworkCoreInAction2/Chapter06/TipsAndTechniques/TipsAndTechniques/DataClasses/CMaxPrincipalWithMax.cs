using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMaxPrincipalWithMax
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
		private string											MEntityPrincipalValue;
		// !!!!! VALUE MUSI byt NULLABLE, pretoze LINQ OPERATOR [Max] MOZE vratit VALUE [NULL].
		private int?											MEntitiesDependentMaxValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CMaxPrincipalWithMax()
		{
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=default(string);
			MEntitiesDependentMaxValue=default(int);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CMaxPrincipalWithMax(int EntityPrincipalID, string EntityPrincipalValue, int? EntitiesDependentMaxValue)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependentMaxValue=EntitiesDependentMaxValue;
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
		public int?												EntitiesDependentMaxValue
		{
			get
			{
				return(MEntitiesDependentMaxValue);
			}
			set
			{
				MEntitiesDependentMaxValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CMaxPrincipalWithMax[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CMaxPrincipalWithMax							Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY PRINCIPAL MAX [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY PRINCIPAL MAX:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");
			SB.AppendLine($"\tENTITIES DEPENDENT MAX VALUE [{MEntitiesDependentMaxValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------