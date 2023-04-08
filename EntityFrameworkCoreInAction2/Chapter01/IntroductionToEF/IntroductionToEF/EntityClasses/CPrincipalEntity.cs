using System;
using System.Collections.Generic;
using System.Net;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace IntroductionToEF
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CPrincipalEntity
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MPrincipalEntityID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MValue;
//----------------------------------------------------------------------------------------------------------------------
		private ICollection<CDependentEntity>					MDependentEntities;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPrincipalEntity()
		{
			MPrincipalEntityID=default(int);
			MValue=default(string);
			MDependentEntities=new List<CDependentEntity>();
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPrincipalEntity(string Value, ICollection<CDependentEntity> DependentEntities)
		{
			MPrincipalEntityID=default(int);
			MValue=Value;
			MDependentEntities=DependentEntities;
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
		public ICollection<CDependentEntity>					DependentEntities
		{
			get
			{
				return(MDependentEntities);
			}
			set
			{
				MDependentEntities=value;
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
				SB.AppendLine($"{PrefixTabs}PRINCIPAL ENTITY [{Index}]:");
			}
			else
			{
				SB.AppendLine($"{PrefixTabs}PRINCIPAL ENTITY:");
			}

			SB.AppendLine($"{PrefixTabs}\tPRINCIPAL ENTITY ID [{MPrincipalEntityID}] !");
			SB.AppendLine($"{PrefixTabs}\tVALUE [{MValue}] !");

			if (MDependentEntities!=null)
			{
				SB.AppendLine($"{PrefixTabs}\tDEPENDENT ENTITIES:");

				int												DependentEntityIndex=1;

				foreach(CDependentEntity DependentEntity in MDependentEntities)
				{
					SB.AppendLine($"{PrefixTabs}\t\tDEPENDENT ENTITY [{DependentEntityIndex}]:");

					SB.AppendLine($"{PrefixTabs}\t\t\tDEPENDENT ENTITY ID [{DependentEntity.DependentEntityID}] !");
					SB.AppendLine($"{PrefixTabs}\t\t\tVALUE [{DependentEntity.Value}] !");

					DependentEntityIndex++;
				}
			}
			else
			{
				SB.AppendLine($"{PrefixTabs}\t--- DEPENDENT ENTITY is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------