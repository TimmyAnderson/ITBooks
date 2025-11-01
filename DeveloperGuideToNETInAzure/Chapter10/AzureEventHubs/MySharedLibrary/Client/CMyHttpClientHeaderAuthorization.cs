using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MySharedLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHttpClientHeaderAuthorization : CMyHttpClientHeader
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const char										SEPARATOR_SCHEME_PARAMETERS=' ';
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientHeaderAuthorization(string Scheme, string Parameters)
			: base(CMyHttpClientHeaders.HEADER_NAME_AUTHORIZATION,CreateValue(Scheme,Parameters))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientHeaderAuthorization(string[] Values)
			: base(CMyHttpClientHeaders.HEADER_NAME_AUTHORIZATION,Values)
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public string											Scheme
		{
			get
			{
				string											Value=Values[0];
				string											Scheme=ParseValueScheme(Value);

				return(Scheme);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public string											Parameters
		{
			get
			{
				string											Value=Values[0];
				string											Parameters=ParseValueParameters(Value);

				return(Parameters);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static string CreateValue(string Scheme, string Parameters)
		{
			string												Value=$"{Scheme}{SEPARATOR_SCHEME_PARAMETERS}{Parameters}";

			return(Value);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static string ParseValueScheme(string Value)
		{
			int													SeparatorPosition=Value.IndexOf(SEPARATOR_SCHEME_PARAMETERS);

			if (SeparatorPosition>=0)
			{
				string											ValueParameters=Value.Substring(0,SeparatorPosition);

				return(ValueParameters);
			}
			else
			{
				return(Value);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static string ParseValueParameters(string Value)
		{
			int													SeparatorPosition=Value.IndexOf(SEPARATOR_SCHEME_PARAMETERS);

			if (SeparatorPosition>=0)
			{
				string											ValueParameters=Value.Substring(SeparatorPosition+1);

				return(ValueParameters);
			}
			else
			{
				return("");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------