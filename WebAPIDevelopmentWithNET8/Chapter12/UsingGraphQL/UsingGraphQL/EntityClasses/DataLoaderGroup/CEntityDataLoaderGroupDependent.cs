using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDataLoaderGroupDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue1;
		private string											MEntityDependentValue2;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityDataLoaderGroupPrincipal					MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupDependent()
		{
			MEntityDependentID=default;
			MEntityDependentValue1=default;
			MEntityDependentValue2=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupDependent(string EntityDependentValue1, string EntityDependentValue2)
		{
			MEntityDependentID=default;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupDependent(string EntityDependentValue1, string EntityDependentValue2, int EntityPrincipalID)
		{
			MEntityDependentID=default;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupDependent(int EntityDependentID, string EntityDependentValue1, string EntityDependentValue2, int EntityPrincipalID)
		{
			MEntityDependentID=EntityDependentID;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupDependent(string EntityDependentValue1, string EntityDependentValue2, CEntityDataLoaderGroupPrincipal EntityPrincipal)
		{
			MEntityDependentID=default;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=default;
			MEntityPrincipal=EntityPrincipal;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityDependentID
		{
			get
			{
				return(MEntityDependentID);
			}
			set
			{
				MEntityDependentID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityDependentValue1
		{
			get
			{
				return(MEntityDependentValue1);
			}
			set
			{
				MEntityDependentValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityDependentValue2
		{
			get
			{
				return(MEntityDependentValue2);
			}
			set
			{
				MEntityDependentValue2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalID
		{
			get
			{
				return(MEntityPrincipalID);
			}
			set
			{
				MEntityPrincipalID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupPrincipal					EntityPrincipal
		{
			get
			{
				return(MEntityPrincipal);
			}
			set
			{
				MEntityPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------