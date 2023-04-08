using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using SecuringWebServicesBearerTokens.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class TestController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje vykonanie LOGIN zo strany WEB SERVICE CLIENT.
		// !!!!! METHOD vracia VALUE JWT TOKEN.
		private async Task<string> DoLoginAsync(CLogin Login)
		{
			HttpClient											Client=new HttpClient();
			string												SerializedObject=JsonSerializer.Serialize(Login);
			StringContent										RequestContent=new StringContent(SerializedObject,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APILogin/Login",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();

				Options.PropertyNameCaseInsensitive=true;

				CLoginResult									ResponseLoginResult=JsonSerializer.Deserialize<CLoginResult>(Content,Options);

				if (ResponseLoginResult.Success==true)
				{
					return(ResponseLoginResult.Token);
				}
				else
				{
					return(null);
				}
			}
			else
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje zavolanie WEB SERVICE METHOD.
		private async Task<CNameResult> CallMethodSecured(string Token)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIName/Secured");
			string												TokenHeaderValue=$"Bearer {Token}";

			Request.Headers.Add("Authorization",TokenHeaderValue);

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CName[]											ResponseNames=JsonSerializer.Deserialize<CName[]>(Content,Options);
				CNameResult										Result=new CNameResult(Response.StatusCode,ResponseNames);

				return(Result);
			}
			else
			{
				CNameResult										Result=new CNameResult(Response.StatusCode);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje zavolanie WEB SERVICE METHOD.
		private async Task<CNameResult> CallMethodSecuredForAdministrators(string Token)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIName/SecuredForAdministrators");
			string												TokenHeaderValue=$"Bearer {Token}";

			Request.Headers.Add("Authorization",TokenHeaderValue);

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CName[]											ResponseNames=JsonSerializer.Deserialize<CName[]>(Content,Options);
				CNameResult										Result=new CNameResult(Response.StatusCode,ResponseNames);

				return(Result);
			}
			else
			{
				CNameResult										Result=new CNameResult(Response.StatusCode);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje zavolanie WEB SERVICE METHOD.
		private async Task<CNameResult> CallMethodSecuredForUsers(string Token)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIName/SecuredForUsers");
			string												TokenHeaderValue=$"Bearer {Token}";

			Request.Headers.Add("Authorization",TokenHeaderValue);

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CName[]											ResponseNames=JsonSerializer.Deserialize<CName[]>(Content,Options);
				CNameResult										Result=new CNameResult(Response.StatusCode,ResponseNames);

				return(Result);
			}
			else
			{
				CNameResult										Result=new CNameResult(Response.StatusCode);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION TOKEN.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION TOKEN.
		public async Task<IActionResult> AccessSecuredActionMethodAsTimmyAsync()
		{
			CLogin												Login=new CLogin("Timmy","SomePassword.1+");
			string												AuthenticationToken=await DoLoginAsync(Login);

			if (AuthenticationToken!=null)
			{
				CNameResult										NameResult=await CallMethodSecured(AuthenticationToken);

				if (NameResult.StatusCode==HttpStatusCode.OK)
				{
					IActionResult								Result=View("Names",NameResult.Names);

					return(Result);
				}
				else
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION TOKEN.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION TOKEN.
		public async Task<IActionResult> AccessSecuredActionMethodAsJennyAsync()
		{
			CLogin												Login=new CLogin("Jenny","SomePassword.2+");
			string												AuthenticationToken=await DoLoginAsync(Login);

			if (AuthenticationToken!=null)
			{
				CNameResult										NameResult=await CallMethodSecured(AuthenticationToken);

				if (NameResult.StatusCode==HttpStatusCode.OK)
				{
					IActionResult								Result=View("Names",NameResult.Names);

					return(Result);
				}
				else
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION TOKEN.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION TOKEN.
		public async Task<IActionResult> AccessSecuredForAdministratorsActionMethodAsTimmyAsync()
		{
			CLogin												Login=new CLogin("Timmy","SomePassword.1+");
			string												AuthenticationToken=await DoLoginAsync(Login);

			if (AuthenticationToken!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForAdministrators(AuthenticationToken);

				if (NameResult.StatusCode==HttpStatusCode.OK)
				{
					IActionResult								Result=View("Names",NameResult.Names);

					return(Result);
				}
				else
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION TOKEN.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION TOKEN.
		public async Task<IActionResult> AccessSecuredForAdministratorsActionMethodAsJennyAsync()
		{
			CLogin												Login=new CLogin("Jenny","SomePassword.2+");
			string												AuthenticationToken=await DoLoginAsync(Login);

			if (AuthenticationToken!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForAdministrators(AuthenticationToken);

				if (NameResult.StatusCode==HttpStatusCode.OK)
				{
					IActionResult								Result=View("Names",NameResult.Names);

					return(Result);
				}
				else
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION TOKEN.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION TOKEN.
		public async Task<IActionResult> AccessSecuredForUsersActionMethodAsTimmyAsync()
		{
			CLogin												Login=new CLogin("Timmy","SomePassword.1+");
			string												AuthenticationToken=await DoLoginAsync(Login);

			if (AuthenticationToken!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForUsers(AuthenticationToken);

				if (NameResult.StatusCode==HttpStatusCode.OK)
				{
					IActionResult								Result=View("Names",NameResult.Names);

					return(Result);
				}
				else
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION TOKEN.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION TOKEN.
		public async Task<IActionResult> AccessSecuredForUsersActionMethodAsJennyAsync()
		{
			CLogin												Login=new CLogin("Jenny","SomePassword.2+");
			string												AuthenticationToken=await DoLoginAsync(Login);

			if (AuthenticationToken!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForUsers(AuthenticationToken);

				if (NameResult.StatusCode==HttpStatusCode.OK)
				{
					IActionResult								Result=View("Names",NameResult.Names);

					return(Result);
				}
				else
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------