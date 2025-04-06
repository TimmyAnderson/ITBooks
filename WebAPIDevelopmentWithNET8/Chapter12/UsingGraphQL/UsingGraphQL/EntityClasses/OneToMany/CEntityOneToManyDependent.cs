using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityOneToManyDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityOneToManyPrincipal						MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent()
		{
			MEntityDependentID=default;
			MEntityDependentValue=default;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue, int EntityPrincipalID)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(int EntityDependentID, string EntityDependentValue, int EntityPrincipalID)
		{
			MEntityDependentID=EntityDependentID;
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipal=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityOneToManyDependent(string EntityDependentValue, CEntityOneToManyPrincipal EntityPrincipal)
		{
			MEntityDependentID=default;
			MEntityDependentValue=EntityDependentValue;
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
		public string											EntityDependentValue
		{
			get
			{
				return(MEntityDependentValue);
			}
			set
			{
				MEntityDependentValue=value;
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
		public CEntityOneToManyPrincipal						EntityPrincipal
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