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
	public class APIAsynchronousEnumerableClientController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<ViewResult> TestGetNames()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/APIAsynchronousEnumerable");

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
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------