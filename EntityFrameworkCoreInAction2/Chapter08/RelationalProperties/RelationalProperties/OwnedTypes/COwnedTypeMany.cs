using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS je OWNED TYPE pomocou FLUENT API.
	public sealed class COwnedTypeMany
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MOwnedTypeID;
//----------------------------------------------------------------------------------------------------------------------
		private int												MOwnedTypeInt;
		private string											MOwnedTypeString;
		private string											MOwnedTypeStringRequired;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeMany()
		{
			MOwnedTypeID=default;
			MOwnedTypeInt=default;
			MOwnedTypeString=default;
			MOwnedTypeStringRequired=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeMany(int OwnedTypeInt, string OwnedTypeString, string OwnedTypeStringRequired)
		{
			MOwnedTypeID=default;
			MOwnedTypeInt=OwnedTypeInt;
			MOwnedTypeString=OwnedTypeString;
			MOwnedTypeStringRequired=OwnedTypeStringRequired;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												OwnedTypeID
		{
			get
			{
				return(MOwnedTypeID);
			}
			set
			{
				MOwnedTypeID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												OwnedTypeInt
		{
			get
			{
				return(MOwnedTypeInt);
			}
			set
			{
				MOwnedTypeInt=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											OwnedTypeString
		{
			get
			{
				return(MOwnedTypeString);
			}
			set
			{
				MOwnedTypeString=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTY je REQUIRED.
		[Required]
		public string											OwnedTypeStringRequired
		{
			get
			{
				return(MOwnedTypeStringRequired);
			}
			set
			{
				MOwnedTypeStringRequired=value;
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
				SB.AppendLine($"OWNED TYPE MANY [{Index}]:");
			}
			else
			{
				SB.AppendLine($"OWNED TYPE MANY:");
			}

			SB.AppendLine($"\tOWNED TYPE ID [{MOwnedTypeID}] !");

			SB.AppendLine($"\tOWNED TYPE INT [{MOwnedTypeInt}] !");
			SB.AppendLine($"\tOWNED TYPE STRING [{MOwnedTypeString}] !");
			SB.AppendLine($"\tOWNED TYPE STRING REQUIRED [{MOwnedTypeStringRequired}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------