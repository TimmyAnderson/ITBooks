using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ModelBindingSourceController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ModelBindingSourceController(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Hodnota PARAMETER 'ID' sa nacita z ROUTE VARIABLES.
		[Route("{Controller}/{Action}/{id?}")]
		public ViewResult ShowName1([FromRoute] int ID)
		{
			CChild												Model=MChildProvider.GetChild(ID);

			if (Model!=null)
			{
				ViewResult										Result=View("ViewChild",Model);

				return(Result);
			}
			else
			{
				CResultMessage									Message=new CResultMessage($"NO OBJECT FOUND for ID [{ID}] !");
				ViewResult										Result=View("ShowResultMessage",Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Hodnota PARAMETER 'ID' sa nacita z QUERY STRING VARIABLES.
		[Route("{Controller}/{Action}/{id?}")]
		public ViewResult ShowName2([FromQuery] int ID)
		{
			CChild												Model=MChildProvider.GetChild(ID);

			if (Model!=null)
			{
				ViewResult										Result=View("ViewChild",Model);

				return(Result);
			}
			else
			{
				CResultMessage									Message=new CResultMessage($"NO OBJECT FOUND for ID [{ID}] !");
				ViewResult										Result=View("ShowResultMessage",Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Hodnota PARAMETER 'ID' sa nacita z QUERY STRING VARIABLES. PARAMTER [Name] urcuje nazov HEADER, z ktoreho ma byt BOUND jeho VALUE.
		public ViewResult ShowHeader([FromHeader(Name="Accept")] string AcceptHeaderValue)
		{
			CResultMessage										Message=new CResultMessage($"ACCEPT HEADER VALUE [{AcceptHeaderValue}] !");
			ViewResult											Result=View("ShowResultMessage",Message);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! BINDING SOURCE ATTRIBUTES su aplikovane na PROPERTIES CLASS 'CMultiSourceData'.
		[Route("{Controller}/{Action}/{id?}")]
		public ViewResult MultiSourceBinding(CMultiSourceData MultiSourceData)
		{
			ViewResult											Result=View("ViewMultiSourceData",MultiSourceData);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Simuluje odoslanie HTTP POST s BODY, ktore obsahuje instanciu CLASS 'CSimpleChild'.
		public async Task<ViewResult> BindFromBodySendPost()
		{
			CSimpleChild										InputName=new CSimpleChild(0,"Timmy","Anderson",12,ESex.Male);
			HttpClient											Client=new HttpClient();
			string												SerializedName=JsonSerializer.Serialize<CSimpleChild>(InputName);
			StringContent										RequestContent=new StringContent(SerializedName,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/ModelBindingSource/BindFromBody",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				// !!! Nacita sa HTTP RESPONSE BODY.
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				// !!! Vykona sa DESERIALIZATION HTTP RESPONSE BODY.
				CSimpleChild									OutputName=JsonSerializer.Deserialize<CSimpleChild>(Content,Options);
				ViewResult										Result=View("ViewSimpleChild",OutputName);

				return(Result);
			}
			else
			{
				CResultMessage									ResultMessage=new CResultMessage($"OPERATION FAILED - ERROR CODE [{Response.StatusCode}] !");
				ViewResult										Result=View("ShowResultMessage",ResultMessage);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER je nacitany z BODY.
		[HttpPost]
		public CSimpleChild BindFromBody([FromBody] CSimpleChild SimpleChild)
		{
			// !!! Ako HTTP RESPONSE BODY sa vrati TEN ISTY OBJECT.
			return(SimpleChild);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------