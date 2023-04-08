using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Remoting.Lifetime;
//-------------------------------------------------------------------------------------------------------
namespace AppDomains
{
//-------------------------------------------------------------------------------------------------------
	// !!! Kedze objekt DEDI MarshalByRefObject, tak BUDE VYTVORENY PROXY OBJEKT pri prechode MEDZI 2 APP DOMAINS.
	public class CName_MarshalByReference : MarshalByRefObject
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName_MarshalByReference()
		{
			MFirstName="Timmy";
			MLastName="Anderson";
			MAge=12;
		}
//-------------------------------------------------------------------------------------------------------
		public CName_MarshalByReference(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		~CName_MarshalByReference()
		{
			string			DomainName=AppDomain.CurrentDomain.FriendlyName;
			string			Text=string.Format("!!! FINALIZE - Domain: [{0}] - Name: [{1}] !",DomainName,this.ToString());

			Console.WriteLine(Text);
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
		// Tu mozem zmenit DLZKU ZIVOTNOSTI OBJEKTU.
		public override object InitializeLifetimeService()
		{
			// Vracia POCIATOCNY TIMOUT na 5 minut a RENEWAL na 2 minuty.
			object												LifeTime=base.InitializeLifetimeService();
			ILease												Lease=(ILease) LifeTime;

			if (Lease.CurrentState==LeaseState.Initial)
			{
				Lease.InitialLeaseTime=TimeSpan.FromSeconds(5);
				Lease.SponsorshipTimeout=TimeSpan.FromSeconds(5);
				Lease.RenewOnCallTime=TimeSpan.FromSeconds(5);
			}

			return(Lease);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintFullName()
		{
			string												DomainName=AppDomain.CurrentDomain.FriendlyName;
			string												Text=string.Format("CName_MarshalByReference.PrintFullName() - Domain: [{0}] - Name: [{1}] !",DomainName,this.ToString());

			Console.WriteLine(Text);
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintFullNameAndThrowException()
		{
			string												DomainName=AppDomain.CurrentDomain.FriendlyName;
			string												Text=string.Format("CName_MarshalByReference.PrintFullName() - Domain: [{0}] - Name: [{1}] !",DomainName,this.ToString());

			Console.WriteLine(Text);

			throw(new Exception(string.Format("EXCEPTION OCCURED in APP DOMAIN [{0}] !",DomainName)));
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