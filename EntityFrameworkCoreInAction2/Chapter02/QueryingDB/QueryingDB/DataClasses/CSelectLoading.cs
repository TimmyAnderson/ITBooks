﻿using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace QueryingDB
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSelectLoading
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly int									MPrincipalEntityID;
		private readonly string									MPrincipalEntityValue;
		private readonly int									MDependentEntityCount;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSelectLoading(int PrincipalEntityID, string PrincipalEntityValue, int DependentEntityCount)
		{
			MPrincipalEntityID=PrincipalEntityID;
			MPrincipalEntityValue=PrincipalEntityValue;
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
				SB.AppendLine($"SELECT LOADING [{Index}]:");
			}
			else
			{
				SB.AppendLine($"SELECT LOADING:");
			}

			SB.AppendLine($"\tPRINCIPAL ENTITY ID [{MPrincipalEntityID}] !");
			SB.AppendLine($"\tPRINCIPAL ENTITY VALUE [{MPrincipalEntityValue}] !");
			SB.AppendLine($"\tDEPENDENT ENTITY COUNT [{MDependentEntityCount}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------