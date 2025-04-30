using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityConcurrencyTokensDataAnnotations
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
		private int												MEntityValue;
		private Guid											MVersion;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConcurrencyTokensDataAnnotations()
		{
			MEntityID=default;
			MEntityValue=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityConcurrencyTokensDataAnnotations(int EntityID, int EntityValue, Guid Version)
		{
			MEntityID=EntityID;
			MEntityValue=EntityValue;
			MVersion=Version;
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
		public int												EntityValue
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
		// !!! PROPERTY je oznacena ako CONCURRENCY TOKEN PROPERTY.
		[ConcurrencyCheck]
		public Guid												Version
		{
			get
			{
				return(MVersion);
			}
			set
			{
				MVersion=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityConcurrencyTokensDataAnnotations[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityConcurrencyTokensDataAnnotations			Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					Console.WriteLine(new string('-',80));
				}

				Console.Write(EntityText);
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
				SB.AppendLine($"ENTITY CONCURRENCY TOKENS DATA ANNOTATIONS [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY CONCURRENCY TOKENS DATA ANNOTATIONS:");
			}

			SB.AppendLine($"\tENTITY ID [{MEntityID}] !");
			SB.AppendLine($"\tENTITY VALUE [{MEntityValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------