using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MySharedLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHttpClientContent
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										MEDIA_TYPE_TEXT="text/plain";
		public const string										MEDIA_TYPE_JSON="application/json";
		public const string										MEDIA_TYPE_JSON_PROBLEM="application/problem+json";
		public const string										MEDIA_TYPE_JSON_GRAPH_QL="application/graphql-response+json";
		public const string										MEDIA_TYPE_HTTP="text/html";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										CHAR_SET_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly CMyHttpClientContentType				MContentType;
		private readonly byte[]									MContent;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientContent(CMyHttpClientContentType ContentType, byte[] Content)
		{
			MContentType=ContentType;
			MContent=Content;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientContent(HttpContent Content)
		{
			long?												ContentLength=Content.Headers.ContentLength;

			if (ContentLength>0)
			{
				string											ContentType=Content?.Headers?.ContentType?.MediaType;
				string											CharSet=Content?.Headers?.ContentType?.CharSet;

				MContentType=new CMyHttpClientContentType(ContentType,CharSet);
				MContent=Content.ReadAsByteArrayAsync().Result;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientContentType							ContentType
		{
			get
			{
				return(MContentType);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public byte[]											Content
		{
			get
			{
				return(MContent);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static Encoding GetEncoding(string CharSet, Encoding DefaultEncoding)
		{
			if (CharSet!=null)
			{
				if (CharSet.ToLowerInvariant()==CHAR_SET_UTF_8)
				{
					return(Encoding.UTF8);
				}
			}

			return(DefaultEncoding);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static MediaTypeHeaderValue CreateMediaTypeHeaderValue(string MediaType, string CharSet)
		{
			MediaTypeHeaderValue								MediaTypeObject=new MediaTypeHeaderValue(MediaType);

			if (CharSet!=null)
			{
				MediaTypeObject.CharSet=CharSet;
			}

			return(MediaTypeObject);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public HttpContent ConvertToHttpContent()
		{
			if (MContentType!=null)
			{
				if (MContent!=null)
				{
					if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_TEXT)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.ASCII);
						string									ContentText=Encoding.GetString(MContent);
						StringContent							Content=new StringContent(ContentText);

						Content.Headers.ContentType=CreateMediaTypeHeaderValue(MContentType.MediaType,MContentType.CharSet);

						return(Content);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									ContentText=Encoding.GetString(MContent);
						StringContent							Content=new StringContent(ContentText);

						Content.Headers.ContentType=CreateMediaTypeHeaderValue(MContentType.MediaType,MContentType.CharSet);

						return(Content);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON_PROBLEM)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									ContentText=Encoding.GetString(MContent);
						StringContent							Content=new StringContent(ContentText);

						Content.Headers.ContentType=CreateMediaTypeHeaderValue(MContentType.MediaType,MContentType.CharSet);

						return(Content);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON_GRAPH_QL)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									ContentText=Encoding.GetString(MContent);
						StringContent							Content=new StringContent(ContentText);

						Content.Headers.ContentType=CreateMediaTypeHeaderValue(MContentType.MediaType,MContentType.CharSet);

						return(Content);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_HTTP)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.ASCII);
						string									ContentText=Encoding.GetString(MContent);
						StringContent							Content=new StringContent(ContentText);

						Content.Headers.ContentType=CreateMediaTypeHeaderValue(MContentType.MediaType,MContentType.CharSet);

						return(Content);
					}
				}
			}

			return(null);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public string ConvertToString()
		{
			if (MContentType!=null)
			{
				if (MContent!=null)
				{
					if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_TEXT)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.ASCII);
						string									Text=Encoding.GetString(MContent);

						return(Text);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									RawText=Encoding.GetString(MContent);
						object									DeserializedObject=JsonConvert.DeserializeObject(RawText);
						string									Text=JsonConvert.SerializeObject(DeserializedObject,Formatting.Indented);

						return(Text);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON_PROBLEM)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									RawText=Encoding.GetString(MContent);
						object									DeserializedObject=JsonConvert.DeserializeObject(RawText);
						string									Text=JsonConvert.SerializeObject(DeserializedObject,Formatting.Indented);

						return(Text);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON_GRAPH_QL)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									RawText=Encoding.GetString(MContent);
						object									DeserializedObject=JsonConvert.DeserializeObject(RawText);
						string									Text=JsonConvert.SerializeObject(DeserializedObject,Formatting.Indented);

						return(Text);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_HTTP)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.ASCII);
						string									Text=Encoding.GetString(MContent);

						return(Text);
					}
					else
					{
						StringBuilder							SB=new StringBuilder();

						for(int Index=0;Index<MContent.Length;Index++)
						{
							if (Index>0)
							{
								SB.Append(',');
							}

							byte								Byte=MContent[Index];

							SB.Append(Byte.ToString("X2"));
						}

						string									Text=SB.ToString();

						return(Text);
					}
				}
			}

			return("");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public TObject ConvertToObject<TObject>() where TObject : class
		{
			if (MContentType!=null)
			{
				if (MContent!=null)
				{
					if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									RawText=Encoding.GetString(MContent);
						object									DeserializedObject=JsonConvert.DeserializeObject(RawText);
						string									Text=JsonConvert.SerializeObject(DeserializedObject,Formatting.Indented);
						TObject									Object=JsonConvert.DeserializeObject<TObject>(Text);

						return(Object);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON_PROBLEM)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									RawText=Encoding.GetString(MContent);
						object									DeserializedObject=JsonConvert.DeserializeObject(RawText);
						string									Text=JsonConvert.SerializeObject(DeserializedObject,Formatting.Indented);
						TObject									Object=JsonConvert.DeserializeObject<TObject>(Text);

						return(Object);
					}
					else if (MContentType?.MediaType?.ToLowerInvariant()==MEDIA_TYPE_JSON_GRAPH_QL)
					{
						Encoding								Encoding=GetEncoding(MContentType?.CharSet,Encoding.UTF8);
						string									RawText=Encoding.GetString(MContent);
						object									DeserializedObject=JsonConvert.DeserializeObject(RawText);
						string									Text=JsonConvert.SerializeObject(DeserializedObject,Formatting.Indented);
						TObject									Object=JsonConvert.DeserializeObject<TObject>(Text);

						return(Object);
					}
				}
			}

			return(null);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static CMyHttpClientContent CreateContentJsonString(string JsonContent)
		{
			CMyHttpClientContentType							ContentType=new CMyHttpClientContentType(MEDIA_TYPE_JSON,CHAR_SET_UTF_8);
			byte[]												RawContent=Encoding.UTF8.GetBytes(JsonContent);
			CMyHttpClientContent								Content=new CMyHttpClientContent(ContentType,RawContent);

			return(Content);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public static CMyHttpClientContent CreateContentJsonObject(object JsonContent)
		{
			CMyHttpClientContentType							ContentType=new CMyHttpClientContentType(MEDIA_TYPE_JSON,CHAR_SET_UTF_8);
			string												SerializedJsonContent=JsonConvert.SerializeObject(JsonContent);
			byte[]												RawContent=Encoding.UTF8.GetBytes(SerializedJsonContent);
			CMyHttpClientContent								Content=new CMyHttpClientContent(ContentType,RawContent);

			return(Content);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------