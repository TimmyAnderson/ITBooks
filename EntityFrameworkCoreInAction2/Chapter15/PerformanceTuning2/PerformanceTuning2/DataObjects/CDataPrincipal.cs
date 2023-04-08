using System;
using System.Collections.Generic;
using System.Text;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace PerformanceTuning2
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDataPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MPrincipalDataID;
		private int												MPrincipalDataIntValue;
		private string											MPrincipalDataStringValue;
		private IList<CDataDependent>							MDependentData;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDataPrincipal()
		{
			MPrincipalDataID=default;
			MPrincipalDataIntValue=default;
			MPrincipalDataStringValue=default;
			MDependentData=default;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDataPrincipal(int PrincipalDataID, int PrincipalDataIntValue, string PrincipalDataStringValue, IList<CDataDependent> DependentData)
		{
			MPrincipalDataID=PrincipalDataID;
			MPrincipalDataIntValue=PrincipalDataIntValue;
			MPrincipalDataStringValue=PrincipalDataStringValue;
			MDependentData=DependentData;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												PrincipalDataID
		{
			get
			{
				return(MPrincipalDataID);
			}
			set
			{
				MPrincipalDataID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												PrincipalDataIntValue
		{
			get
			{
				return(MPrincipalDataIntValue);
			}
			set
			{
				MPrincipalDataIntValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PrincipalDataStringValue
		{
			get
			{
				return(MPrincipalDataStringValue);
			}
			set
			{
				MPrincipalDataStringValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IList<CDataDependent>							DependentData
		{
			get
			{
				return(MDependentData);
			}
			set
			{
				MDependentData=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void PrintToConsole(CDataPrincipal[] Entities)
		{
			for(int Index=0;Index<Entities.Length;Index++)
			{
				CDataPrincipal									Entity=Entities[Index];
				string											EntityText=Entity.Print(Index+1);
							
				if (Index>0)
				{
					CConsoleHelpers.WriteLineSeparator();
				}

				CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
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
				SB.AppendLine($"PRINCIPAL DATA [{Index}]:");
			}
			else
			{
				SB.AppendLine($"PRINCIPAL DATA:");
			}

			SB.AppendLine($"\tPRINCIPAL DATA ID [{MPrincipalDataID}] !");
			SB.AppendLine($"\tPRINCIPAL DATA INT VALUE [{MPrincipalDataIntValue}] !");
			SB.AppendLine($"\tPRINCIPAL DATA STRING VALUE [{MPrincipalDataStringValue}] !");

			if (MDependentData!=null)
			{
				SB.AppendLine($"\tDEPENDENT DATA:");

				for(int DependentDataIndex=0;DependentDataIndex<MDependentData.Count;DependentDataIndex++)
				{
					CDataDependent							DependentData=MDependentData[DependentDataIndex];

					SB.AppendLine($"\t\tDEPENDENT DATA [{(DependentDataIndex+1)}]:");

					SB.AppendLine($"\t\t\tDEPENDENT DATA ID [{DependentData.DependentDataID}] !");
					SB.AppendLine($"\t\t\tDEPENDENT DATA INT VALUE [{DependentData.DependentDataIntValue}] !");
					SB.AppendLine($"\t\t\tDEPENDENT DATA STRING VALUE [{DependentData.DependentDataStringValue}] !");
				}
			}
			else
			{
				SB.AppendLine($"\t--- DEPENDENT DATA is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------