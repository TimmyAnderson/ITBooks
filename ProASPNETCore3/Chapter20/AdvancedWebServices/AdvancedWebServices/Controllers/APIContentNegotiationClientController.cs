using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Net.Http.Json;
using System.Text.Json;
using System.Threading.Tasks;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using System.Runtime.Serialization;
using Microsoft.AspNetCore.Mvc;
using AdvancedWebServices.Model;
using Microsoft.AspNetCore.Mvc.Formatters;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class APIContentNegotiationClientController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnString()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIContentNegotiation/ReturnString");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnInt()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIContentNegotiation/ReturnInt");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnName()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIContentNegotiation/ReturnName");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameAcceptXML()
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnName");

			// !!!!! Ak je ASP.NET nakonfigurovane BY-DEFAULT, tak XML SERIALIZER nie je sucastou HTTP REQUEST PIPELINE. V takom pripade, ak aj ACCEPT HEADER obsahuje poziadavku na XML, ASP.NET vrati JSON OBJECT.
			// !!!!! Ak je ASP.NET nakonfigurovane na pouzitie XML SERIALIZER, tak ASP.NET vrati XML.
			Request.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/xml"));

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameProducesJSONAcceptJSON()
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnNameProducesJSON");

			Request.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Obsahuje JSON, pretoze ACCEPT obsahuje JSON, aj PRODUCES ATTRIBUTE obsahuje JSON.
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameProducesJSONAcceptXML()
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnNameProducesJSON");

			Request.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/xml"));

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Obsahuje JSON, pretoze aj ked ACCEPT obsahuje XML, PRODUCES ATTRIBUTE obsahuje JSON.
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameProducesXMLAcceptJSON()
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnNameProducesXML");

			Request.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Obsahuje XML, pretoze aj ked ACCEPT obsahuje JSON, PRODUCES ATTRIBUTE obsahuje XML.
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameProducesXMLAcceptXML()
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnNameProducesXML");

			Request.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/xml"));

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Obsahuje JSON, pretoze ACCEPT obsahuje XML, aj PRODUCES ATTRIBUTE obsahuje XML.
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameFormatThroughRoute()
		{
			HttpClient											Client=new HttpClient();

			// !!! FORMAT sa definuje v ROUTE.
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnNameFormatThroughRouteOrQueryString/MY_XML");
			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Obsahuje XML, lebo FORMAT definovany v ROUTE ma hodnotu 'MY_XML'.
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Url:",Response.RequestMessage.RequestUri.ToString());
				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReturnNameFormatThroughQueryString()
		{
			HttpClient											Client=new HttpClient();

			// !!! FORMAT sa definuje v QUERY STRING.
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIContentNegotiation/ReturnNameFormatThroughRouteOrQueryString?Format=MY_XML");
			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Obsahuje XML, lebo FORMAT definovany v QUERY STRING ma hodnotu 'MY_XML'.
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Url:",Response.RequestMessage.RequestUri.ToString());
				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReceiveJSON()
		{
			CName												InputName=new CName(0,"Timmy","Anderson",12);
			HttpClient											Client=new HttpClient();
			string												SerializedName=JsonSerializer.Serialize<CName>(InputName);
			StringContent										RequestContent=new StringContent(SerializedName,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APIContentNegotiation",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Url:",Response.RequestMessage.RequestUri.ToString());
				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestReceiveXML()
		{
			CName												InputName=new CName(0,"Timmy","Anderson",12);
			HttpClient											Client=new HttpClient();
			DataContractSerializer								Serializer=new DataContractSerializer(typeof(CName));
			string												SerializedName;

			using(MemoryStream MS=new MemoryStream())
			{
				Serializer.WriteObject(MS,InputName);

				MS.Seek(0,SeekOrigin.Begin);

				using(StreamReader SR=new StreamReader(MS))
				{
					SerializedName=SR.ReadToEnd();
				}
			}

			StringContent										RequestContent=new StringContent(SerializedName,Encoding.UTF8,"application/xml");
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APIContentNegotiation",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				Dictionary<string,string>						Data=new Dictionary<string,string>();

				Data.Add("Url:",Response.RequestMessage.RequestUri.ToString());
				Data.Add("Accept:",Response.RequestMessage.Headers.Accept.ToString());
				Data.Add("Content Type:",Response.Content.Headers.ContentType.ToString());
				Data.Add("Content:",Content);

				CResultData										Model=new CResultData(Data);
				ViewResult										Result=View("ResultData",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------