using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ParameterfulProperties
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CNamesBase
	{
//-------------------------------------------------------------------------------------------------------
		[IndexerName("MySuperIndexer")]
		public abstract CName									this[int Index]
		{
			get;
			set;
		}
//-------------------------------------------------------------------------------------------------------
		// INDEXERS podporuju aj VIACERO PARAMETERS.
		[IndexerName("MySuperIndexer")]
		public abstract CName									this[string FirstName, string LastName, int Age]
		{
			get;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------