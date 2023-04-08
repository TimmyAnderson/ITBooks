using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CInstruction_MOV : CInstruction
	{
//-------------------------------------------------------------------------------------------------------
		private readonly COperand								MOperand1;
		private readonly COperand								MOperand2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstruction_MOV(COperand Operand1, COperand Operand2, string Comment)
			: base(Comment)
		{
			if ((Operand1 is COperand_Constant)==true)
			{
				throw(new InvalidOperationException("Operand1 MUST NOT be CONSTANT !"));
			}

			if (((Operand1 is COperand_Memory)==true && (Operand2 is COperand_Memory)==true) || ((Operand1 is COperand_MemoryOffset)==true && (Operand2 is COperand_MemoryOffset)==true))
			{
				throw(new InvalidOperationException("Both OPERANDS CAN'T be MEMORY OPERANDS !"));
			}

			MOperand1=Operand1;
			MOperand2=Operand2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public COperand											Operand1
		{
			get
			{
				return(MOperand1);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public COperand											Operand2
		{
			get
			{
				return(MOperand2);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string GetInstructionString(bool PrintComments)
		{
			string												Instruction=string.Format("MOV {0},{1}",MOperand1.GetOperandText(),MOperand2.GetOperandText());
			
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