﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3SqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityTimestampsFluentAPI
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityID;
		private int												MEntityValue;
		private byte[]											MTimestamp;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTimestampsFluentAPI()
		{
			MEntityID=default;
			MEntityValue=default;
			MTimestamp=default(byte[]);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityTimestampsFluentAPI(int EntityID, int EntityValue)
		{
			MEntityID=EntityID;
			MEntityValue=EntityValue;
			MTimestamp=default(byte[]);
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
		// !!! PROPERTY je pomocou FLUENT API oznacena ako TIMESTAMP PROPERTY.
		public byte[]											Timestamp
		{
			get
			{
				return(MTimestamp);
			}
			set
			{
				MTimestamp=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CEntityTimestampsFluentAPI[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CEntityTimestampsFluentAPI						Entity=Entities[Index];
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
				SB.AppendLine($"ENTITY TIMESTAMPS FLUENT API [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY TIMESTAMPS FLUENT API:");
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