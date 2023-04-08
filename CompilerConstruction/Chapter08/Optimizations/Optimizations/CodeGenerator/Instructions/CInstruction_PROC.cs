﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CInstruction_PROC : CInstruction
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFunctionName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstruction_PROC(string FunctionName, string Comment)
			: base(Comment)
		{
			MFunctionName=FunctionName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FunctionName
		{
			get
			{
				return(MFunctionName);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string GetInstructionString(bool PrintComments)
		{
			string												Instruction=string.Format("{0} PROC",MFunctionName);
			
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