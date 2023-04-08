﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CInstruction_JNE : CInstruction
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MLabel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstruction_JNE(string Label, string Comment)
			: base(Comment)
		{
			MLabel=Label;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Label
		{
			get
			{
				return(MLabel);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string GetInstructionString(bool PrintComments)
		{
			string												Instruction=string.Format("JNE {0}",MLabel);
			
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