using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MySharedLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuCommand
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly string									MCommandID;
		private readonly string									MCommandText;
		private readonly EMenuCommandParameterType[]			MCommandParameterTypes;
		private readonly Action<string,object[]>				MCommandOperation;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuCommand(string CommandID, string CommandText, EMenuCommandParameterType[] CommandParameterTypes, Action<string,object[]> CommandOperation)
		{
			MCommandID=CommandID;
			MCommandText=CommandText;
			MCommandParameterTypes=CommandParameterTypes;
			MCommandOperation=CommandOperation;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public string											CommandID
		{
			get
			{
				return(MCommandID);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public string											CommandText
		{
			get
			{
				return(MCommandText);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public EMenuCommandParameterType[]						CommandParameterTypes
		{
			get
			{
				return(MCommandParameterTypes);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public Action<string,object[]>							CommandOperation
		{
			get
			{
				return(MCommandOperation);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public void CallCommandOperation(string[] RawCommandParameters)
		{
			if (MCommandOperation==null)
			{
				return;
			}

			if (MCommandParameterTypes.Length!=RawCommandParameters.Length)
			{
				throw(new InvalidOperationException($"COMMAND [{MCommandID}] has INVALID NUMBER of PARAMETERS. EXPECTED NUMBER of PARAMETERS [{MCommandParameterTypes.Length}]."));
			}

			object[]											CommandParameters=new object[RawCommandParameters.Length];

			for(int Index=0;Index<RawCommandParameters.Length;Index++)
			{
				string											RawCommandParameter=RawCommandParameters[Index];
				EMenuCommandParameterType						CommandParameterType=MCommandParameterTypes[Index];

				if (CommandParameterType==EMenuCommandParameterType.E_STRING)
				{
					CommandParameters[Index]=RawCommandParameter;
				}
				else if (CommandParameterType==EMenuCommandParameterType.E_INT)
				{
					int											CommandParameter;

					if (int.TryParse(RawCommandParameter,out CommandParameter)==true)
					{
						CommandParameters[Index]=CommandParameter;
					}
					else
					{
						throw(new InvalidOperationException($"COMMAND [{MCommandID}] has INVALID VALUE [{RawCommandParameter}] at INDEX [{Index}]. EXPECTED PARAMETER TYPE [{CommandParameterType}]."));
					}
				}
				else
				{
					throw(new InvalidOperationException($"COMMAND [{MCommandID}] has UNSUPPORTED PARAMETER TYPE [{CommandParameterType}] at INDEX [{Index}]."));
				}
			}

			MCommandOperation(MCommandID,CommandParameters);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------