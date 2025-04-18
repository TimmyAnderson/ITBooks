using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDataLoaderGroupPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly int									MPrincipalID;
		private readonly string									MPrincipalValue1;
		private readonly string									MPrincipalValue2;
		private readonly IList<CDataLoaderGroupDependent>		MDependents;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDataLoaderGroupPrincipal(int PrincipalID, string PrincipalValue1, string PrincipalValue2)
		{
			MPrincipalID=PrincipalID;
			MPrincipalValue1=PrincipalValue1;
			MPrincipalValue2=PrincipalValue2;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDataLoaderGroupPrincipal(int PrincipalID, string PrincipalValue1, string PrincipalValue2, IList<CDataLoaderGroupDependent> Dependents)
		{
			MPrincipalID=PrincipalID;
			MPrincipalValue1=PrincipalValue1;
			MPrincipalValue2=PrincipalValue2;
			MDependents=Dependents;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												PrincipalID
		{
			get
			{
				return(MPrincipalID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PrincipalValue1
		{
			get
			{
				return(MPrincipalValue1);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PrincipalValue2
		{
			get
			{
				return(MPrincipalValue2);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IList<CDataLoaderGroupDependent>					Dependents
		{
			get
			{
				return(MDependents);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------