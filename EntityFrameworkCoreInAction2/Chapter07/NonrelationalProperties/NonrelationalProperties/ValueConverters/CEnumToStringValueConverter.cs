using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Text;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEnumToStringValueConverter : ValueConverter<EEnumType,string>
	{
//----------------------------------------------------------------------------------------------------------------------
		public CEnumToStringValueConverter()
			: base(P => ConvertEnumToString(P),P => ConvertStringToEnum(P))
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static string ConvertEnumToString(EEnumType Value)
		{
			string												ConvertedValue=Value.ToString();

			return(ConvertedValue);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static EEnumType ConvertStringToEnum(string Value)
		{
			EEnumType											ConvertedValue=Enum.Parse<EEnumType>(Value);

			return(ConvertedValue);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------