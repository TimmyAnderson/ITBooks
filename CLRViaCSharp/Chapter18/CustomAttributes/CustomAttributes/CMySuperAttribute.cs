using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
	// CUSTOM ATTRIBUTE MUSI BYT ZDEDENY z CLASS Attribute.
	// ATTRIBUTE je INHERITED.
	// ATTRIBUTE umoznuje OPAKOVANE aplikovanie na TEN ISTY MEMBER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Parameter | AttributeTargets.ReturnValue,AllowMultiple=true,Inherited=true)]
	public class CMySuperAttribute : Attribute
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMySuperAttribute(string LastName)
		{
			Console.WriteLine("!!!!! CMySuperAttribute CONSTRUCTOR CALLED !");

			MLastName=LastName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Je to OPTIONAL PARAMETER - MUSI MAT SETTER.
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Je to POVINNY PARAMETER - NEMUSI MAT SETTER.
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			if (MFirstName==null && MLastName==null)
			{
				return(string.Format("[{0}]",this.GetType()));
			}
			else if (MFirstName!=null && MLastName==null)
			{
				return(string.Format("[{0}] - [{1}]",this.GetType(),MFirstName));
			}
			else if (MFirstName==null && MLastName!=null)
			{
				return(string.Format("[{0}] - [{1}]",this.GetType(),MLastName));
			}
			else
			{
				return(string.Format("[{0}] - [{1} {2}]",this.GetType(),MFirstName,MLastName));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------