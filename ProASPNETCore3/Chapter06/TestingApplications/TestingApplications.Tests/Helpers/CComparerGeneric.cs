﻿using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace TestingApplications.Tests.Helpers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CComparer<TType> : CComparer, IEqualityComparer<TType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Func<TType,TType,bool>					MComparisonFunction;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CComparer(Func<TType,TType,bool> ComparisonFunction)
		{
			MComparisonFunction=ComparisonFunction;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public bool Equals(TType X, TType Y)
		{
			bool												AreEqual=MComparisonFunction(X,Y);

			return(AreEqual);
		}
//----------------------------------------------------------------------------------------------------------------------
		public int GetHashCode(TType Object)
		{
			int													HashCode=Object.GetHashCode();

			return(HashCode);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------