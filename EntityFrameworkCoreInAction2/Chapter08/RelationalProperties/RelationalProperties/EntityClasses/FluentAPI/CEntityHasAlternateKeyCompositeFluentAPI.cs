using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityHasAlternateKeyCompositeFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityValue;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELDS reprezentuju COMPOSITE ALTERNATE KEY. ALTERNATE KEY MUSI byt UNIQUE.
		private string											MMyAlternateKey1;
		private string											MMyAlternateKey2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasAlternateKeyCompositeFluentAPI()
		{
			MEntityID=default;
			MEntityValue=default;
			MMyAlternateKey1=default;
			MMyAlternateKey2=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityHasAlternateKeyCompositeFluentAPI(string EntityValue, string MyAlternateKey1, string MyAlternateKey2)
		{
			MEntityID=default;
			MEntityValue=EntityValue;
			MMyAlternateKey1=MyAlternateKey1;
			MMyAlternateKey2=MyAlternateKey2;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityID
		{
			get
			{
				return(MEntityID);
			}
			set
			{
				MEntityID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityValue
		{
			get
			{
				return(MEntityValue);
			}
			set
			{
				MEntityValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											MyAlternateKey1
		{
			get
			{
				return(MMyAlternateKey1);
			}
			set
			{
				MMyAlternateKey1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											MyAlternateKey2
		{
			get
			{
				return(MMyAlternateKey2);
			}
			set
			{
				MMyAlternateKey2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityHasAlternateKeyCompositeFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityHasAlternateKeyCompositeFluentAPI		EntityN=Entities[Index];
				string											EntityNText=EntityN.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityNText,ConsoleColor.Green);
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
				SB.AppendLine($"ENTITY HAS ALTERNATE KEY COMPOSITE FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY HAS ALTERNATE KEY COMPOSITE FLUENT API:");
			}

			SB.AppendLine($"\tENTITY ID [{MEntityID}] !");
			SB.AppendLine($"\tENTITY VALUE [{MEntityValue}] !");
			SB.AppendLine($"\tENTITY MY ALTERNATE KEY 1 [{MMyAlternateKey1}] !");
			SB.AppendLine($"\tENTITY MY ALTERNATE KEY 2 [{MMyAlternateKey2}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------