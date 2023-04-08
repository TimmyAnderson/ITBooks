using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ParameterfulProperties
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CNamesDerived : CNamesBase
	{
//-------------------------------------------------------------------------------------------------------
		private readonly Dictionary<int,CName>					MDictionary;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNamesDerived()
		{
			MDictionary=new Dictionary<int,CName>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override CName									this[int Index]
		{
			get
			{
				if (MDictionary.ContainsKey(Index)==true)
				{
					return(MDictionary[Index]);
				}
				else
				{
					return(null);
				}
			}
			set
			{
				if (MDictionary.ContainsKey(Index)==true)
				{
					MDictionary[Index]=value;
				}
				else
				{
					MDictionary.Add(Index,value);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// INDEXERS podporuju aj VIACERO PARAMETERS.
		public override CName									this[string FirstName, string LastName, int Age]
		{
			get
			{
				foreach(CName Name in MDictionary.Values)
				{
					if (Name.FirstName==FirstName && Name.LastName==LastName && Name.Age==Age)
					{
						return(Name);
					}
				}

				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------