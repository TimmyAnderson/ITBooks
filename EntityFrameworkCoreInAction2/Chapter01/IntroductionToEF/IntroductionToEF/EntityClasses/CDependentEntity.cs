﻿using System;
using System.Collections.Generic;
using System.Net;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace IntroductionToEF
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDependentEntity
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MDependentEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MPrincipalEntityID;
		private CPrincipalEntity								MPrincipalEntity;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDependentEntity()
		{
			MDependentEntityID=default(int);
			MValue=default(string);
			MPrincipalEntityID=default(int);
			MPrincipalEntity=default(CPrincipalEntity);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDependentEntity(string Value)
		{
			MDependentEntityID=default(int);
			MValue=Value;
			MPrincipalEntityID=default(int);
			MPrincipalEntity=default(CPrincipalEntity);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												DependentEntityID
		{
			get
			{
				return(MDependentEntityID);
			}
			set
			{
				MDependentEntityID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											Value
		{
			get
			{
				return(MValue);
			}
			set
			{
				MValue=value;
			}
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
			set
			{
				MPrincipalEntityID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPrincipalEntity									PrincipalEntity
		{
			get
			{
				return(MPrincipalEntity);
			}
			set
			{
				MPrincipalEntity=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string Print(int? Index, int NumberOfPrefixTabs)
		{
			string												PrefixTabs=new string('\t',NumberOfPrefixTabs);
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"{PrefixTabs}DEPENDENT ENTITY [{Index}]:");
			}
			else
			{
				SB.AppendLine($"{PrefixTabs}DEPENDENT ENTITY:");
			}

			SB.AppendLine($"{PrefixTabs}\tDEPENDENT ENTITY ID [{MDependentEntityID}] !");
			SB.AppendLine($"{PrefixTabs}\tPRINCIPAL ENTITY ID [{MPrincipalEntityID}] !");
			SB.AppendLine($"{PrefixTabs}\tVALUE [{MValue}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------