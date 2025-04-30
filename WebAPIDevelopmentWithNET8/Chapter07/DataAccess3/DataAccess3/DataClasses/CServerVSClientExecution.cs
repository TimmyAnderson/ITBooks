using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CServerVSClientExecution
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly int									MPrincipalEntityID;
		private readonly string									MPrincipalEntityValue;
		private readonly string									MDependentEntityValues;
		private readonly int									MDependentEntityCount;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CServerVSClientExecution(int PrincipalEntityID, string PrincipalEntityValue, string DependentEntityValues, int DependentEntityCount)
		{
			MPrincipalEntityID=PrincipalEntityID;
			MPrincipalEntityValue=PrincipalEntityValue;
			MDependentEntityValues=DependentEntityValues;
			MDependentEntityCount=DependentEntityCount;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												PrincipalEntityID
		{
			get
			{
				return(MPrincipalEntityID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PrincipalEntityValue
		{
			get
			{
				return(MPrincipalEntityValue);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											DependentEntityValues
		{
			get
			{
				return(MDependentEntityValues);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												DependentEntityCount
		{
			get
			{
				return(MDependentEntityCount);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string Print(int? Index)
		{
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"SERVER VS CLIENT EXECUTION [{Index}]:");
			}
			else
			{
				SB.AppendLine($"SERVER VS CLIENT EXECUTION:");
			}

			SB.AppendLine($"\tPRINCIPAL ENTITY ID [{MPrincipalEntityID}] !");
			SB.AppendLine($"\tPRINCIPAL ENTITY VALUE [{MPrincipalEntityValue}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY VALUES [{MDependentEntityValues}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY COUNT [{MDependentEntityCount}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------