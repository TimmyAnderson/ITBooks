using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ReferenceTypes
{
//-------------------------------------------------------------------------------------------------------
	public class CNameClass
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameClass(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void NoChange(string FirstName, string LastName, int Age)
		{
			ToString();
		}
//-------------------------------------------------------------------------------------------------------
		public void Change(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;

			ToString();
		}
//-------------------------------------------------------------------------------------------------------
		public void Print()
		{
			Console.WriteLine(string.Format("NAME - First name: [{0}], Last name: [{1}], Age: [{2}] !",MFirstName,MLastName,MAge));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static bool operator==(CNameClass Operand1, CNameClass Operand2)
		{
			object												RawOperand1=Operand1;
			object												RawOperand2=Operand2;

			if (RawOperand1==null && RawOperand2==null)
			{
				return(true);
			}
			else if (RawOperand1!=null && RawOperand2==null)
			{
				return(false);
			}
			else if (RawOperand1==null && RawOperand2!=null)
			{
				return(false);
			}
			else
			{
				return(Operand1.Equals(Operand2));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static bool operator!=(CNameClass Operand1, CNameClass Operand2)
		{
			object												RawOperand1=Operand1;
			object												RawOperand2=Operand2;

			if (RawOperand1==null && RawOperand2==null)
			{
				return(false);
			}
			else if (RawOperand1!=null && RawOperand2==null)
			{
				return(true);
			}
			else if (RawOperand1==null && RawOperand2!=null)
			{
				return(true);
			}
			else
			{
				return(!Operand1.Equals(Operand2));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool Equals(object Object)
		{
			CNameClass											Name=Object as CNameClass;

			if (Name==null)
			{
				return(false);
			}

			// !!! Pre REFERENCE TYPES ma zmysel vykonat optimalizaciu porovnanim REFERENCES.
			if (Object.ReferenceEquals(this,Name)==true)
			{
				return(true);
			}

			if (MFirstName!=Name.MFirstName)
			{
				return(false);
			}

			if (MLastName!=Name.MLastName)
			{
				return(false);
			}

			if (MAge!=Name.MAge)
			{
				return(false);
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override int GetHashCode()
		{
			int													FirstNameHashCode=MFirstName.GetHashCode();
			int													LastNameHashCode=MLastName.GetHashCode();
			int													AgeHashCode=MAge.GetHashCode();
			int													HashCode=FirstNameHashCode^LastNameHashCode^AgeHashCode;

			return(HashCode);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}]",MFirstName,MLastName,MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------