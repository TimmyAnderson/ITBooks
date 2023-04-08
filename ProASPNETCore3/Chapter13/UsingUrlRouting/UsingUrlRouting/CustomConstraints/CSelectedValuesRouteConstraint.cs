using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Routing;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.CustomConstraints
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM CONSTRAINT.
	public sealed class CSelectedValuesRouteConstraint : IRouteConstraint
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly string[]								MAllowedValues;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSelectedValuesRouteConstraint()
		{
			MAllowedValues=new string[]{"Timmy","Anderson"};
		}
//----------------------------------------------------------------------------------------------------------------------
		public CSelectedValuesRouteConstraint(string AllowedValue1, string AllowedValue2, string AllowedValue3, string AllowedValue4)
		{
			MAllowedValues=new string[]{AllowedValue1,AllowedValue2,AllowedValue3,AllowedValue4};
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public bool Match(HttpContext Context, IRouter Route, string RouteKey, RouteValueDictionary Values, RouteDirection Direction)
		{
			object												RawSegmentValue;

			if (Values.TryGetValue(RouteKey,out RawSegmentValue)==true)
			{
				if (RawSegmentValue!=null)
				{
					string										SegmentValue=RawSegmentValue.ToString();

					if (MAllowedValues.Contains(SegmentValue)==true)
					{
						return(true);
					}
				}
			}

			return(false);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------