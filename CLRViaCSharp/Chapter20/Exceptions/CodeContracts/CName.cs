using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics.Contracts;
//-------------------------------------------------------------------------------------------------------
namespace CodeContracts
{
//-------------------------------------------------------------------------------------------------------
	public class CName
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName, int Age)
		{
			// PRE-CONTIDIONS.
			Contract.Requires(Age>=0);
			Contract.Requires(FirstName!=null);
			Contract.Requires(LastName!=null);

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
			set
			{
				Contract.Requires(value>=0);

				MAge=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// INVARIANT METODA.
		// !!!!! Je volna v RUNTIME iba ak je RUNTIME CHECK zapnuty.
		[ContractInvariantMethod]
		private void MyInvariantChecker1()
		{
			Contract.Invariant(MAge>=0);
		}
//-------------------------------------------------------------------------------------------------------
		// INVARIANT METODA.
		// !!!!! Je volna v RUNTIME iba ak je RUNTIME CHECK zapnuty.
		[ContractInvariantMethod]
		private void MyInvariantChecker2()
		{
			Contract.Invariant(MFirstName!=null);
			Contract.Invariant(MLastName!=null);
		}
//-------------------------------------------------------------------------------------------------------
		private int PrivateAddAndReturnAge(int Addition)
		{
			Contract.Requires(Addition>=0);
			MAge+=Addition;

			return(MAge);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int AddAndReturnAge(int Addition)
		{
			Contract.Requires(Addition>=0);
			// I tato POST-CONTITION je VERIFIKOVATELNA, lebo SCITAVAM dve VERIFIKOVATELNE KLADNE CISLA.
			// !!! Contract.Result<int>() je SPECIALNA METODA, ktorej NAVRATOVA HODNOTA reprezentuje NAVRATOVU HODNOTU METODY AddAndReturnAge().
			Contract.Ensures(Contract.Result<int>()>=0);
			// POST-CONDITION na kontrolu hodnoty FIELD.
			Contract.Ensures(MAge>=0);

			MAge+=Addition;

			return(MAge);
		}
//-------------------------------------------------------------------------------------------------------
		public string GetFullName()
		{
			// !!! POST-CONDITION. Kontroluje RETURN VALUE METHOD.
			Contract.Ensures(Contract.Result<string>()!=null);

			string												ReturnValue=string.Format("{0} {1}",MFirstName,MLastName);

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		public override bool Equals(object Obj)
		{
			CName												Name=Obj as CName;

			if (Obj==null)
			{
				return(false);
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