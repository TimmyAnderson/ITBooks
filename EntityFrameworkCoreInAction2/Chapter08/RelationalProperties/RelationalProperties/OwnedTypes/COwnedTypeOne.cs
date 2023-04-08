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
	public sealed class COwnedTypeOne
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MOwnedTypeInt;
		private string											MOwnedTypeString;
		private string											MOwnedTypeStringRequired;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeOne()
		{
			MOwnedTypeInt=default;
			MOwnedTypeString=default;
			MOwnedTypeStringRequired=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public COwnedTypeOne(int OwnedTypeInt, string OwnedTypeString, string OwnedTypeStringRequired)
		{
			MOwnedTypeInt=OwnedTypeInt;
			MOwnedTypeString=OwnedTypeString;
			MOwnedTypeStringRequired=OwnedTypeStringRequired;
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
				SB.AppendLine($"OWNED TYPE ONE [{Index}]:");
			}
			else
			{
				SB.AppendLine($"OWNED TYPE ONE:");
			}

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