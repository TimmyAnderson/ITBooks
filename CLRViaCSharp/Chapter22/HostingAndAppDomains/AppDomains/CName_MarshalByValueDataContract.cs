using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Runtime.Remoting.Lifetime;
//-------------------------------------------------------------------------------------------------------
namespace AppDomains
{
//-------------------------------------------------------------------------------------------------------
	// !!! Kedze NEDEDI z MarshalByRefObject AVSAK JE SERIALIZOVATELNA, tak trieda bude MARSHAL BY VALUE.
	[DataContract]
	public class CName_MarshalByValueDataContract
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName_MarshalByValueDataContract()
		{
			MFirstName="Timmy";
			MLastName="Anderson";
			MAge=12;
		}
//-------------------------------------------------------------------------------------------------------
		public CName_MarshalByValueDataContract(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		~CName_MarshalByValueDataContract()
		{
			string												DomainName=AppDomain.CurrentDomain.FriendlyName;
			string												Text=string.Format("!!! FINALIZE - Domain: [{0}] - Name: [{1}] !",DomainName,this.ToString());

			Console.WriteLine(Text);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			private set
			{
				MFirstName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			private set
			{
				MLastName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public int												Age
		{
			get
			{
				return(MAge);
			}
			private set
			{
				MAge=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintFullName()
		{
			string												DomainName=AppDomain.CurrentDomain.FriendlyName;
			string												Text=string.Format("CName_MarshalByValueDataContract.PrintFullName() - Domain: [{0}] - Name: [{1}] !",DomainName,this.ToString());

			Console.WriteLine(Text);
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