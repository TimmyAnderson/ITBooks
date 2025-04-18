using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDataLoaderBatchDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue1;
		private string											MEntityDependentValue2;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityDataLoaderBatchPrincipal					MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchDependent()
		{
			MEntityDependentID=default;
			MEntityDependentValue1=default;
			MEntityDependentValue2=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchDependent(string EntityDependentValue1, string EntityDependentValue2)
		{
			MEntityDependentID=default;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchDependent(string EntityDependentValue1, string EntityDependentValue2, int EntityPrincipalID)
		{
			MEntityDependentID=default;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchDependent(int EntityDependentID, string EntityDependentValue1, string EntityDependentValue2, int EntityPrincipalID)
		{
			MEntityDependentID=EntityDependentID;
			MEntityDependentValue1=EntityDependentValue1;
			MEntityDependentValue2=EntityDependentValue2;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchDependent(string EntityDependentValue1, string EntityDependentValue2, CEntityDataLoaderBatchPrincipal EntityPrincipal)
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
		public CEntityDataLoaderBatchPrincipal					EntityPrincipal
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