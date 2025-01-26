using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http.Headers;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHttpClientHeaders
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										HEADER_NAME_AUTHORIZATION="Authorization";
//--------------------------------------------------------------------------------------------------------------------------------
		private static readonly string							HEADER_NAME_LOWER_INVARIANT_AUTHORIZATION=HEADER_NAME_AUTHORIZATION.ToLowerInvariant();
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly CMyHttpClientHeader[]					MHeaders;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientHeaders(CMyHttpClientHeader[] Headers)
		{
			MHeaders=Headers;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientHeaders(HttpHeaders Headers)
		{
			List<CMyHttpClientHeader>							HeadersCollection=new List<CMyHttpClientHeader>();

			foreach(KeyValuePair<string,IEnumerable<string>> KeyValue in Headers)
			{
				string											HeaderKey=KeyValue.Key;
				string											HeaderKeyLowerInvariant=HeaderKey.ToLowerInvariant();
				string[]										HeaderValues=KeyValue.Value.ToArray();

				if (HeaderKeyLowerInvariant==HEADER_NAME_LOWER_INVARIANT_AUTHORIZATION)
				{
					CMyHttpClientHeaderAuthorization			Header=new CMyHttpClientHeaderAuthorization(HeaderValues);

					HeadersCollection.Add(Header);
				}
				else
				{
					CMyHttpClientHeader							Header=new CMyHttpClientHeader(HeaderKey,HeaderValues);

					HeadersCollection.Add(Header);
				}
			}

			MHeaders=HeadersCollection.ToArray();
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientHeader[]							Headers
		{
			get
			{
				return(MHeaders);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------