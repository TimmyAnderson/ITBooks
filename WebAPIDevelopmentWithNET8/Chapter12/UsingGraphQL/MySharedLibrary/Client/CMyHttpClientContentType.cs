﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using Newtonsoft.Json;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MySharedLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHttpClientContentType
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly string									MMediaType;
		private readonly string									MCharSet;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientContentType(string MediaType, string CharSet)
		{
			MMediaType=MediaType;
			MCharSet=CharSet;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public string											MediaType
		{
			get
			{
				return(MMediaType);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public string											CharSet
		{
			get
			{
				return(MCharSet);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public string ConvertToString()
		{
			if (MMediaType!=null)
			{
				if (MCharSet==null)
				{
					string										Text=MMediaType;

					return(Text);
				}
				else
				{
					string										Text=$"{MMediaType},{MCharSet}";

					return(Text);
				}
			}
			
			return("");
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------