using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityOneToManyPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		private IList<CEntityOneToManyDependent>				MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=default;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyPrincipal(string EntityPrincipalValue)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyPrincipal(int EntityPrincipalID, string EntityPrincipalValue)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyPrincipal(string EntityPrincipalValue, IList<CEntityOneToManyDependent> EntitiesDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyPrincipal(int EntityPrincipalID, string EntityPrincipalValue, IList<CEntityOneToManyDependent> EntitiesDependent)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue=EntityPrincipalValue;
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
		public string											EntityPrincipalValue
		{
			get
			{
				return(MEntityPrincipalValue);
			}
			set
			{
				MEntityPrincipalValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IList<CEntityOneToManyDependent>					EntitiesDependent
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