using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Net.Http.Headers;
using Microsoft.Extensions.Primitives;
using AdvancedWebServices.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class APINameClientController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestGetNames()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIControllerName");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				IEnumerable<CName>								DeserializedData=JsonSerializer.Deserialize<IEnumerable<CName>>(Content,Options);
				CName[]											Model=DeserializedData.ToArray();
				ViewResult										Result=View("ViewNames",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestGetName1()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIControllerName/1");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				CName											Model=JsonSerializer.Deserialize<CName>(Content,Options);
				ViewResult										Result=View("ViewName",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestGetName2()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIControllerName/2");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				CName											Model=JsonSerializer.Deserialize<CName>(Content,Options);
				ViewResult										Result=View("ViewName",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestPostName()
		{
			// !!! Pri INSERT by sa NEMAL zadavat ID, pretoze ten generuje ENTITY FRAMEWORK. V pripade, ze by sa zadaval aj ID, mohlo by dost k OVER-BINDING.
			CNameNoID											InputName=new CNameNoID("Josh","Hurt",12);
			HttpClient											Client=new HttpClient();
			JsonContent											RequestContent=JsonContent.Create<CNameNoID>(InputName);
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APIControllerName",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				CName											Model=JsonSerializer.Deserialize<CName>(Content,Options);
				ViewResult										Result=View("ViewName",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestPutName1()
		{
			CName												InputName=new CName(1,"TIMMY","ANDERSON",12);
			HttpClient											Client=new HttpClient();
			JsonContent											RequestContent=JsonContent.Create<CName>(InputName);
			HttpResponseMessage									Response=await Client.PutAsync("http://localhost:50000/api/APIControllerName",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				CName											Model=JsonSerializer.Deserialize<CName>(Content,Options);
				ViewResult										Result=View("ViewName",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestPutName2()
		{
			CName												InputName=new CName(2,"JENNY","THOMPSON",13);
			HttpClient											Client=new HttpClient();
			JsonContent											RequestContent=JsonContent.Create<CName>(InputName);
			HttpResponseMessage									Response=await Client.PutAsync("http://localhost:50000/api/APIControllerName",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				CName											Model=JsonSerializer.Deserialize<CName>(Content,Options);
				ViewResult										Result=View("ViewName",Model);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Na to, aby PATCH fungoval je NUTNE v STARTUP povolit NEWTONSOFT JSON SERIALIZER.
		public async Task<ViewResult> TestPatchName1()
		{
			string												PatchBody="[{\"op\": \"replace\", \"path\": \"/firstName\", \"value\": \"TIMMY\"},{\"op\": \"replace\", \"path\": \"/lastName\", \"value\": \"ANDERSON\"}]";
			HttpClient											Client=new HttpClient();
			StringContent										RequestContent=new StringContent(PatchBody,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PatchAsync("http://localhost:50000/api/APIControllerName/1",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION SUCCEEDED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Na to, aby PATCH fungoval je NUTNE v STARTUP povolit NEWTONSOFT JSON SERIALIZER.
		public async Task<ViewResult> TestPatchName2()
		{
			string												PatchBody="[{\"op\": \"replace\", \"path\": \"/firstName\", \"value\": \"JENNY\"},{\"op\": \"replace\", \"path\": \"/lastName\", \"value\": \"THOMPSON\"}]";
			HttpClient											Client=new HttpClient();
			StringContent										RequestContent=new StringContent(PatchBody,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PatchAsync("http://localhost:50000/api/APIControllerName/2",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION SUCCEEDED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestDeleteName1()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.DeleteAsync("http://localhost:50000/api/APIControllerName/1");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION SUCCEEDED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestDeleteName2()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.DeleteAsync("http://localhost:50000/api/APIControllerName/2");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION SUCCEEDED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage("OPERATION FAILED !");
				ViewResult										Result=View("ResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------