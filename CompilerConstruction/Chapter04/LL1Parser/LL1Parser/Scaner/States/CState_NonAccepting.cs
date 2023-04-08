using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public class CState_NonAccepting : CState
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CTransition>						MTransitions;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected CState_NonAccepting(string Name, bool IsStartState)
			: base(Name,IsStartState,false,false)
		{
			MTransitions=new List<CTransition>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState_NonAccepting(string Name)
			: base(Name,false,false,false)
		{
			MTransitions=new List<CTransition>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTransition[]									Transitions
		{
			get
			{
				return(MTransitions.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTransition GetMatchingTransition(char NewChar)
		{
			foreach(CTransition Transition in MTransitions)
			{
				if (Transition.InputChar.IsValidChar(NewChar)==true)
					return(Transition);
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public void AddTransition(CTransition Transition)
		{
			if (Transition.InputChar.GetType()==typeof(CInputChar_Other))
			{
				if (MTransitions.Where(P => P.GetType()==typeof(CInputChar_Other)).FirstOrDefault()!=null)
					throw(new InvalidOperationException(string.Format("CAN'T ADD TRANSITION TYPE [{0}] MORE than ONCE !",typeof(CInputChar_Other).Name)));

				MTransitions.Add(Transition);
			}
			else
			{
				if (MTransitions.Count>0 && MTransitions[MTransitions.Count-1].InputChar.GetType()==typeof(CInputChar_Other))
				{
					MTransitions.Insert(MTransitions.Count-1,Transition);
				}
				else
				{
					MTransitions.Add(Transition);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------