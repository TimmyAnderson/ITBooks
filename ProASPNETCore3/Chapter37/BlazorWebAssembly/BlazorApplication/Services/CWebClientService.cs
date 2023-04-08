using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using SharedClasses.Classes;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorApplication.Services
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CWebClientService
	{
//----------------------------------------------------------------------------------------------------------------------
		public async static Task<CPerson> AddPerson(CPerson Person)
		{
			HttpClient											Client=new HttpClient();
			string												SerializedObject=JsonSerializer.Serialize(Person);
			StringContent										RequestContent=new StringContent(SerializedObject,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PostAsync("http://localhost:50000/api/persons/AddPerson",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CPerson											ResponsePerson=JsonSerializer.Deserialize<CPerson>(Content,Options);

				return(ResponsePerson);
			}
			else
			{
				throw(new InvalidOperationException("CONNECTION to SERVER FAILED !"));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async static Task<CPerson> UpdatePerson(CPerson Person)
		{
			HttpClient											Client=new HttpClient();
			string												SerializedObject=JsonSerializer.Serialize(Person);
			StringContent										RequestContent=new StringContent(SerializedObject,Encoding.UTF8,"application/json");
			HttpResponseMessage									Response=await Client.PutAsync("http://localhost:50000/api/persons/UpdatePerson",RequestContent);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CPerson											ResponsePerson=JsonSerializer.Deserialize<CPerson>(Content,Options);

				return(ResponsePerson);
			}
			else
			{
				throw(new InvalidOperationException("CONNECTION to SERVER FAILED !"));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async static Task RemovePerson(int ID)
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.DeleteAsync($"http://localhost:50000/api/persons/RemovePerson/{ID}");

			if (Response.StatusCode!=HttpStatusCode.OK)
			{
				throw(new InvalidOperationException("CONNECTION to SERVER FAILED !"));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async static Task<CPerson> GetPerson(int ID)
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync($"http://localhost:50000/api/persons/GetPerson/{ID}");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CPerson											ResponsePerson=JsonSerializer.Deserialize<CPerson>(Content,Options);

				return(ResponsePerson);
			}
			else
			{
				throw(new InvalidOperationException("CONNECTION to SERVER FAILED !"));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async static Task<CPerson[]> GetPersons()
		{
			HttpClient											Client=new HttpClient();
			HttpResponseMessage									Response=await Client.GetAsync("http://localhost:50000/api/persons/GetPersons");

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				string											Content=await Response.Content.ReadAsStringAsync();
				JsonSerializerOptions							Options=new JsonSerializerOptions();
				
				Options.PropertyNameCaseInsensitive=true;

				CPerson[]										ResponsePersons=JsonSerializer.Deserialize<CPerson[]>(Content,Options);

				return(ResponsePersons);
			}
			else
			{
				throw(new InvalidOperationException("CONNECTION to SERVER FAILED !"));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------