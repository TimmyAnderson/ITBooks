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
using CreatingRESTfulWebServices.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class APIValidationClientController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestPostValidName()
		{
			// !!! Pri INSERT by sa NEMAL zadavat ID, pretoze ten generuje ENTITY FRAMEWORK. V pripade, ze by sa zadaval aj ID, mohlo by dost k OVER-BINDING.
			CNameNoID											InputName=new CNameNoID("Josh","Hurt",12);
			HttpClient											Client=new HttpClient();
			JsonContent											RequestContent=JsonContent.Create<CNameNoID>(InputName);
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APIValidation",RequestContent);

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
				string											Content=await Response.Content.ReadAsStringAsync();

				if (Content.Length>0)
				{
					JsonSerializerOptions						Options=new JsonSerializerOptions();

					Options.PropertyNameCaseInsensitive=true;

					CValidationErrors							Model=JsonSerializer.Deserialize<CValidationErrors>(Content,Options);
					ViewResult									Result=View("ViewValidationErrors",Model);

					return(Result);
				}
				else
				{
					CResultMessage								ResultMessage=new CResultMessage("OPERATION FAILED !");
					ViewResult									Result=View("ResultMessage",ResultMessage);

					return(Result);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestPostInvalidName()
		{
			// !!! Pri INSERT by sa NEMAL zadavat ID, pretoze ten generuje ENTITY FRAMEWORK. V pripade, ze by sa zadaval aj ID, mohlo by dost k OVER-BINDING.
			CNameNoID											InputName=new CNameNoID("Josh","",0);
			HttpClient											Client=new HttpClient();
			JsonContent											RequestContent=JsonContent.Create<CNameNoID>(InputName);
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APIValidation",RequestContent);

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
				string											Content=await Response.Content.ReadAsStringAsync();

				if (Content.Length>0)
				{
					JsonSerializerOptions						Options=new JsonSerializerOptions();

					Options.PropertyNameCaseInsensitive=true;

					CValidationErrors							Model=JsonSerializer.Deserialize<CValidationErrors>(Content,Options);
					ViewResult									Result=View("ViewValidationErrors",Model);

					return(Result);
				}
				else
				{
					CResultMessage								ResultMessage=new CResultMessage("OPERATION FAILED !");
					ViewResult									Result=View("ResultMessage",ResultMessage);

					return(Result);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------