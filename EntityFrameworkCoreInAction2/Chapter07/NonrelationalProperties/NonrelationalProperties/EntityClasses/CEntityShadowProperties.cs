using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Helpers;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! SHADOW PROPERTIES su definovane pomocou FLUENT API.
	public sealed class CEntityShadowProperties
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MNonShadowProperty;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityShadowProperties()
		{
			MID=default;
			MNonShadowProperty=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityShadowProperties(string NonShadowProperty)
		{
			MID=default;
			MNonShadowProperty=NonShadowProperty;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											NonShadowProperty
		{
			get
			{
				return(MNonShadowProperty);
			}
			set
			{
				MNonShadowProperty=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityShadowProperties[] Entities, CDBContext Context)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityShadowProperties							Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1,Context);
							
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
		public string Print(int? Index, CDBContext Context)
		{
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"ENTITY SHADOW PROPERTIES [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY SHADOW PROPERTIES:");
			}

			SB.AppendLine($"\tID [{MID}] !");

			SB.AppendLine($"\tNON SHADOW PROPERTY [{MNonShadowProperty}] !");

			EntityEntry<CEntityShadowProperties>				Entry=Context.Entry<CEntityShadowProperties>(this);

			if (Entry!=null)
			{
				// !!!!! VALUES SHADOW PROPERTY sa citaju z TRACKED ENTITY DATA.
				string											ShadowPropertyString=(string) Entry.Property("ShadowPropertyString").CurrentValue;
				int												ShadowPropertyInt=(int) Entry.Property("ShadowPropertyInt").CurrentValue;

				SB.AppendLine($"\tSHADOW PROPERTY STRING [{ShadowPropertyString}] !");
				SB.AppendLine($"\tSHADOW PROPERTY INT [{ShadowPropertyInt}] !");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------