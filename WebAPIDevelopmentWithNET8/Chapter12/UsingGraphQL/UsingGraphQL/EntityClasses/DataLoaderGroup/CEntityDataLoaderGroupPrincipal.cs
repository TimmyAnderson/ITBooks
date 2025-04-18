using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDataLoaderGroupPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue1;
		private string											MEntityPrincipalValue2;
//----------------------------------------------------------------------------------------------------------------------
		private IList<CEntityDataLoaderGroupDependent>			MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue1=default;
			MEntityPrincipalValue2=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupPrincipal(string EntityPrincipalValue1, string EntityPrincipalValue2)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupPrincipal(int EntityPrincipalID, string EntityPrincipalValue1, string EntityPrincipalValue2)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupPrincipal(string EntityPrincipalValue1, string EntityPrincipalValue2, IList<CEntityDataLoaderGroupDependent> EntitiesDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderGroupPrincipal(int EntityPrincipalID, string EntityPrincipalValue1, string EntityPrincipalValue2, IList<CEntityDataLoaderGroupDependent> EntitiesDependent)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntitiesDependent=EntitiesDependent;
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
		public string											EntityPrincipalValue1
		{
			get
			{
				return(MEntityPrincipalValue1);
			}
			set
			{
				MEntityPrincipalValue1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalValue2
		{
			get
			{
				return(MEntityPrincipalValue2);
			}
			set
			{
				MEntityPrincipalValue2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityDataLoaderGroupDependent>			EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------