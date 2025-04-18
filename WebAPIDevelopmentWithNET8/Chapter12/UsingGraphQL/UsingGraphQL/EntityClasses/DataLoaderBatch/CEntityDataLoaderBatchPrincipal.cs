using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDataLoaderBatchPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue1;
		private string											MEntityPrincipalValue2;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityDataLoaderBatchDependent					MEntityDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchPrincipal()
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue1=default;
			MEntityPrincipalValue2=default;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchPrincipal(string EntityPrincipalValue1, string EntityPrincipalValue2)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchPrincipal(int EntityPrincipalID, string EntityPrincipalValue1, string EntityPrincipalValue2)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntityDependent=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchPrincipal(string EntityPrincipalValue1, string EntityPrincipalValue2, CEntityDataLoaderBatchDependent EntityDependent)
		{
			MEntityPrincipalID=default;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntityDependent=EntityDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDataLoaderBatchPrincipal(int EntityPrincipalID, string EntityPrincipalValue1, string EntityPrincipalValue2, CEntityDataLoaderBatchDependent EntityDependent)
		{
			MEntityPrincipalID=EntityPrincipalID;
			MEntityPrincipalValue1=EntityPrincipalValue1;
			MEntityPrincipalValue2=EntityPrincipalValue2;
			MEntityDependent=EntityDependent;
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
		public CEntityDataLoaderBatchDependent					EntityDependent
		{
			get
			{
				return(MEntityDependent);
			}
			set
			{
				MEntityDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------