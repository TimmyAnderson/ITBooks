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
	public class CName_MarshalByReferenceWithFields : MarshalByRefObject
	{
//-------------------------------------------------------------------------------------------------------
		// Ma PUBLIC FIELDS
		public string											MFirstName;
		public string											MLastName;
		public int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName_MarshalByReferenceWithFields()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		~CName_MarshalByReferenceWithFields()
		{
			string			DomainName=AppDomain.CurrentDomain.FriendlyName;
			string			Text=string.Format("!!! FINALIZE - Domain: [{0}] - Name: [{1}] !",DomainName,this.ToString());

			Console.WriteLine(Text);
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------