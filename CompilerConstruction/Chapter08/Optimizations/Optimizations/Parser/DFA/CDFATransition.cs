using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CDFATransition : IEquatable<CDFATransition>
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CDFAState								MSourceState;
		private readonly CSymbol								MTransitionSymbol;
		private readonly CDFAState								MDestinationState;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFATransition(CDFAState SourceState, CSymbol TransitionSymbol, CDFAState DestinationState)
		{
			MSourceState=SourceState;
			MTransitionSymbol=TransitionSymbol;
			MDestinationState=DestinationState;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDFAState										SourceState
		{
			get
			{
				return(MSourceState);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol											TransitionSymbol
		{
			get
			{
				return(MTransitionSymbol);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CDFAState										DestinationState
		{
			get
			{
				return(MDestinationState);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool Equals(CDFATransition Other)
		{
 			if (Other==null)
			{
				return(false);
			}

			if (MSourceState.Equals(Other.MSourceState)==false)
			{
				return(false);
			}

			if (MTransitionSymbol.Equals(Other.MTransitionSymbol)==false)
			{
				return(false);
			}

			if (MDestinationState.Equals(Other.MDestinationState)==false)
			{
				return(false);
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			string												Ret=string.Format("{0} --- {1} ---> {2}",MSourceState,MTransitionSymbol,MDestinationState);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------