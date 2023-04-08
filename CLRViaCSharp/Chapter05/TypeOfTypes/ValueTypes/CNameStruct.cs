using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ValueTypes
{
//-------------------------------------------------------------------------------------------------------
	public struct CNameStruct : IPrint
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameStruct(string FirstName, string LastName, int Age)
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
		public static bool operator==(CNameStruct Operand1, CNameStruct Operand2)
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
		public static bool operator!=(CNameStruct Operand1, CNameStruct Operand2)
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
		public override bool Equals(object Object)
		{
			if (Object==null)
			{
				return(false);
			}

			if (Object.GetType()!=typeof(CNameStruct))
			{
				return(false);
			}

			CNameStruct											Name=(CNameStruct) Object;

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
			// !!!!! Kedze METHOD ValueType.GetHashCode() vola Object.GetHashCode() z BASE CLASS, vykona sa BOXING.
			/*
				ldarg											THIS
				ldobj											ValueTypes.CNameStruct
				box												ValueTypes.CNameStruct
				call											instance int32 [mscorlib]System.ValueType::GetHashCode()
			*/
			return(base.GetHashCode());
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