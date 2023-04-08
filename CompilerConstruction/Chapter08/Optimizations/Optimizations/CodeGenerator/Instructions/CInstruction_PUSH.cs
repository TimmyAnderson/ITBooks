﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CInstruction_PUSH : CInstruction
	{
//-------------------------------------------------------------------------------------------------------
		private readonly COperand								MOperand;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstruction_PUSH(COperand Operand, string Comment)
			: base(Comment)
		{
			if ((Operand is COperand_Constant)==true)
			{
				throw(new CCompilerException("Operand MUST NOT be CONSTANT !"));
			}

			MOperand=Operand;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public COperand											Operand
		{
			get
			{
				return(MOperand);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string GetInstructionString(bool PrintComments)
		{
			string												Instruction=string.Format("PUSH {0}",MOperand.GetOperandText());
			
			if (PrintComments==true && MComment!=null)
			{
				string											CommentedInstruction=AddComment(Instruction,MComment);

				return(CommentedInstruction);
			}
			else
			{
				return(Instruction);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------