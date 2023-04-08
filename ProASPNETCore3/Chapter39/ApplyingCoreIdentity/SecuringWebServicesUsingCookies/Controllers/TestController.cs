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
using SecuringWebServicesUsingCookies.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesUsingCookies.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class TestController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									COOKIE_HEADER_NAME="Set-Cookie";
		private const string									AUTHENTICATION_COOKIE_NAME=".AspNetCore.Identity.Application";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje vykonanie LOGIN zo strany WEB SERVICE CLIENT.
		// !!!!! METHOD vracia VALUE AUTHENTICATION COOKIE.
		private async Task<string> DoLoginAsync(CLogin Login)
		{
			HttpClient											Client=new HttpClient();
			string												SerializedObject=JsonSerializer.Serialize(Login);
			StringContent										RequestContent=new StringContent(SerializedObject,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/APILogin/Login",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				bool											HasSetCookie=Response.Headers.Contains(COOKIE_HEADER_NAME);

				if (HasSetCookie==true)
				{
					string[]									SetCookieValues=Response.Headers.Where(P => P.Key==COOKIE_HEADER_NAME).First().Value.ToArray();
					
					foreach(string SetCookieValue in SetCookieValues)
					{
						int										KeyValueSeparatorIndex=SetCookieValue.IndexOf('=');

						if (KeyValueSeparatorIndex!=-1)
						{
							string								CookieKey=SetCookieValue.Substring(0,KeyValueSeparatorIndex);

							if (CookieKey==AUTHENTICATION_COOKIE_NAME)
							{
								string							CookieValue=SetCookieValue.Substring(KeyValueSeparatorIndex+1);
								int								SeparatorIndex=CookieValue.IndexOf(';');

								if (SeparatorIndex!=-1)
								{
									CookieValue=CookieValue.Substring(0,SeparatorIndex);
								}

								return(CookieValue);
							}
						}
					}
				}

				return(null);
			}
			else
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje vykonanie LOGOUT zo strany WEB SERVICE CLIENT.
		private async Task<bool> DoLogoutAsync(string AuthenticationCookie)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Post,"http://localhost:50000/api/APILogin/Logout");
			string												CookieValue=$"{AUTHENTICATION_COOKIE_NAME}={AuthenticationCookie}";

			Request.Headers.Add("Cookie",CookieValue);

			HttpResponseMessage									Response=await Client.SendAsync(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD simuluje zavolanie WEB SERVICE METHOD.
		private async Task<CNameResult> CallMethodSecured(string AuthenticationCookie)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIName/Secured");
			string												CookieValue=$"{AUTHENTICATION_COOKIE_NAME}={AuthenticationCookie}";

			Request.Headers.Add("Cookie",CookieValue);

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
		private async Task<CNameResult> CallMethodSecuredForAdministrators(string AuthenticationCookie)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIName/SecuredForAdministrators");
			string												CookieValue=$"{AUTHENTICATION_COOKIE_NAME}={AuthenticationCookie}";

			Request.Headers.Add("Cookie",CookieValue);

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
		private async Task<CNameResult> CallMethodSecuredForUsers(string AuthenticationCookie)
		{
			HttpClient											Client=new HttpClient();
			HttpRequestMessage									Request=new HttpRequestMessage(HttpMethod.Get,"http://localhost:50000/api/APIName/SecuredForUsers");
			string												CookieValue=$"{AUTHENTICATION_COOKIE_NAME}={AuthenticationCookie}";

			Request.Headers.Add("Cookie",CookieValue);

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
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION COOKIE.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION COOKIE.
		// 3. Vykona LOGOUT cez API INTERFACE.
		public async Task<IActionResult> AccessSecuredActionMethodAsTimmyAsync()
		{
			CLogin												Login=new CLogin("Timmy","SomePassword.1+");
			string												AuthenticationCookie=await DoLoginAsync(Login);

			if (AuthenticationCookie!=null)
			{
				CNameResult										NameResult=await CallMethodSecured(AuthenticationCookie);

				if (NameResult.StatusCode!=HttpStatusCode.OK)
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}

				bool											LogoutResult=await DoLogoutAsync(AuthenticationCookie);

				if (LogoutResult==false)
				{
					IActionResult								Result=View("OperationFailed","LOGOUT FAILED !");

					return(Result);
				}

				IActionResult									SuccessResult=View("Names",NameResult.Names);

				return(SuccessResult);
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION COOKIE.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION COOKIE.
		// 3. Vykona LOGOUT cez API INTERFACE.
		public async Task<IActionResult> AccessSecuredActionMethodAsJennyAsync()
		{
			CLogin												Login=new CLogin("Jenny","SomePassword.2+");
			string												AuthenticationCookie=await DoLoginAsync(Login);

			if (AuthenticationCookie!=null)
			{
				CNameResult										NameResult=await CallMethodSecured(AuthenticationCookie);

				if (NameResult.StatusCode!=HttpStatusCode.OK)
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}

				bool											LogoutResult=await DoLogoutAsync(AuthenticationCookie);

				if (LogoutResult==false)
				{
					IActionResult								Result=View("OperationFailed","LOGOUT FAILED !");

					return(Result);
				}

				IActionResult									SuccessResult=View("Names",NameResult.Names);

				return(SuccessResult);
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION COOKIE.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION COOKIE.
		// 3. Vykona LOGOUT cez API INTERFACE.
		public async Task<IActionResult> AccessSecuredForAdministratorsActionMethodAsTimmyAsync()
		{
			CLogin												Login=new CLogin("Timmy","SomePassword.1+");
			string												AuthenticationCookie=await DoLoginAsync(Login);

			if (AuthenticationCookie!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForAdministrators(AuthenticationCookie);

				if (NameResult.StatusCode!=HttpStatusCode.OK)
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}

				bool											LogoutResult=await DoLogoutAsync(AuthenticationCookie);

				if (LogoutResult==false)
				{
					IActionResult								Result=View("OperationFailed","LOGOUT FAILED !");

					return(Result);
				}

				IActionResult									SuccessResult=View("Names",NameResult.Names);

				return(SuccessResult);
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION COOKIE.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION COOKIE.
		// 3. Vykona LOGOUT cez API INTERFACE.
		public async Task<IActionResult> AccessSecuredForAdministratorsActionMethodAsJennyAsync()
		{
			CLogin												Login=new CLogin("Jenny","SomePassword.2+");
			string												AuthenticationCookie=await DoLoginAsync(Login);

			if (AuthenticationCookie!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForAdministrators(AuthenticationCookie);

				if (NameResult.StatusCode!=HttpStatusCode.OK)
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}

				bool											LogoutResult=await DoLogoutAsync(AuthenticationCookie);

				if (LogoutResult==false)
				{
					IActionResult								Result=View("OperationFailed","LOGOUT FAILED !");

					return(Result);
				}

				IActionResult									SuccessResult=View("Names",NameResult.Names);

				return(SuccessResult);
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION COOKIE.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION COOKIE.
		// 3. Vykona LOGOUT cez API INTERFACE.
		public async Task<IActionResult> AccessSecuredForUsersActionMethodAsTimmyAsync()
		{
			CLogin												Login=new CLogin("Timmy","SomePassword.1+");
			string												AuthenticationCookie=await DoLoginAsync(Login);

			if (AuthenticationCookie!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForUsers(AuthenticationCookie);

				if (NameResult.StatusCode!=HttpStatusCode.OK)
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}

				bool											LogoutResult=await DoLogoutAsync(AuthenticationCookie);

				if (LogoutResult==false)
				{
					IActionResult								Result=View("OperationFailed","LOGOUT FAILED !");

					return(Result);
				}

				IActionResult									SuccessResult=View("Names",NameResult.Names);

				return(SuccessResult);
			}
			else
			{
				IActionResult									Result=View("OperationFailed","LOGIN FAILED !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ACTION METHOD simuluje cinnost WEB SERVICE CLIENT.
		// 1. Vykona LOGIN cez API INTERFACE na ziskanie AUTHENTICATION COOKIE.
		// 2. Zavola SECURED METHOD s nastavenym AUTHENTICATION COOKIE.
		// 3. Vykona LOGOUT cez API INTERFACE.
		public async Task<IActionResult> AccessSecuredForUsersActionMethodAsJennyAsync()
		{
			CLogin												Login=new CLogin("Jenny","SomePassword.2+");
			string												AuthenticationCookie=await DoLoginAsync(Login);

			if (AuthenticationCookie!=null)
			{
				CNameResult										NameResult=await CallMethodSecuredForUsers(AuthenticationCookie);

				if (NameResult.StatusCode!=HttpStatusCode.OK)
				{
					IActionResult								Result=View("OperationFailed",$"CALLING WEB SERVICE METHOD FAILED with STATUS CODE [{NameResult.StatusCode}] !");

					return(Result);
				}

				bool											LogoutResult=await DoLogoutAsync(AuthenticationCookie);

				if (LogoutResult==false)
				{
					IActionResult								Result=View("OperationFailed","LOGOUT FAILED !");

					return(Result);
				}

				IActionResult									SuccessResult=View("Names",NameResult.Names);

				return(SuccessResult);
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