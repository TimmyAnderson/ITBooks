﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CInstructionCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CInstruction>						MInstructions;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstructionCollection()
		{
			MInstructions=new List<CInstruction>();
		}
//-------------------------------------------------------------------------------------------------------
		public CInstructionCollection(CInstruction[] Instructions)
		{
			MInstructions=new List<CInstruction>(Instructions);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstruction[]									Instructions
		{
			get
			{
				return(MInstructions.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddInstruction(CInstruction Instruction)
		{
			MInstructions.Add(Instruction);
		}
//-------------------------------------------------------------------------------------------------------
		public void FillInstructions(CInstructionCollection Instructions)
		{
			MInstructions.AddRange(Instructions.MInstructions);
		}
//-------------------------------------------------------------------------------------------------------
		public void Clear()
		{
			MInstructions.Clear();
		}
//-------------------------------------------------------------------------------------------------------
		public string GetInstructionsString(bool PrintComments)
		{
			StringBuilder										SB=new StringBuilder();

			foreach(CInstruction Instruction in MInstructions)
			{
				string											InstructionString=Instruction.GetInstructionString(PrintComments);

				SB.AppendLine(InstructionString);

				if ((Instruction is CInstruction_ENDP)==true)
				{
					SB.AppendLine();
				}
			}
			
			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------