using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.AspNetCore.JsonPatch;
using CreatingRESTfulWebServices.Database;
using CreatingRESTfulWebServices.Model;
using System.IO;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CAPIEndpointName
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task GetNames(HttpContext Context)
		{
			INameProvider										NameProvider=Context.RequestServices.GetRequiredService<INameProvider>();
			IEnumerable<CName>									Names=NameProvider.GetNames();
			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNameCaseInsensitive=true;

			string												ResponseContent=JsonSerializer.Serialize(Names,Options);

			Context.Response.ContentType="application/json";
			await Context.Response.WriteAsync(ResponseContent);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static async Task GetName(HttpContext Context)
		{
			INameProvider										NameProvider=Context.RequestServices.GetRequiredService<INameProvider>();
			string												RawID=(string) Context.Request.RouteValues["ID"];
			int													ID=int.Parse(RawID);
			CName												Name=NameProvider.GetName(ID);
			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNameCaseInsensitive=true;

			string												ResponseContent=JsonSerializer.Serialize(Name,Options);

			Context.Response.ContentType="application/json";
			await Context.Response.WriteAsync(ResponseContent);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static async Task InsertName(HttpContext Context)
		{
			INameProvider										NameProvider=Context.RequestServices.GetRequiredService<INameProvider>();
			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNameCaseInsensitive=true;

			// !!! Pri INSERT by sa NEMAL zadavat ID, pretoze ten generuje ENTITY FRAMEWORK. V pripade, ze by sa zadaval aj ID, mohlo by dost k OVER-BINDING.
			CNameNoID											NameNoID=await JsonSerializer.DeserializeAsync<CNameNoID>(Context.Request.Body,Options);
			CName												Name=new CName(0,NameNoID.FirstName,NameNoID.LastName,NameNoID.Age);
			CName												InsertedName=NameProvider.AddName(Name);
			string												ResponseContent=JsonSerializer.Serialize(InsertedName,Options);

			Context.Response.ContentType="application/json";
			await Context.Response.WriteAsync(ResponseContent);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static async Task UpdateName(HttpContext Context)
		{
			INameProvider										NameProvider=Context.RequestServices.GetRequiredService<INameProvider>();
			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNameCaseInsensitive=true;

			CName												Name=await JsonSerializer.DeserializeAsync<CName>(Context.Request.Body,Options);
			CName												UpdatedName=NameProvider.UpdateName(Name);
			string												ResponseContent=JsonSerializer.Serialize(UpdatedName,Options);

			Context.Response.ContentType="application/json";
			await Context.Response.WriteAsync(ResponseContent);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static async Task PartialUpdateName(HttpContext Context)
		{
			INameProvider										NameProvider=Context.RequestServices.GetRequiredService<INameProvider>();
			string												RawID=(string) Context.Request.RouteValues["ID"];
			int													ID=int.Parse(RawID);
			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNameCaseInsensitive=true;

			string												RawBody;
			
			using(StreamReader SR=new StreamReader(Context.Request.Body))
			{
				RawBody=await SR.ReadToEndAsync();
			}

			// !!!!! Na DESERIALIZATION PATCH OBJECT je NUTNE pouzit NEWTONSOFT JSON SERIALIZER.
			JsonPatchDocument<CName>							NamePatch=Newtonsoft.Json.JsonConvert.DeserializeObject<JsonPatchDocument<CName>>(RawBody);
			bool												UpdatedName=NameProvider.PatchName(ID,NamePatch);

			if (UpdatedName==true)
			{
				// !!! V pripade, ze UPDATE BOL uspesny, vrati sa HTTP STATUS CODE 200.
				Context.Response.StatusCode=200;
			}
			else
			{
				// !!! V pripade, ze UPDATE NEBOL uspesny, vrati sa HTTP STATUS CODE 404.
				Context.Response.StatusCode=404;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static Task DeleteName(HttpContext Context)
		{
			INameProvider										NameProvider=Context.RequestServices.GetRequiredService<INameProvider>();
			string												RawID=(string) Context.Request.RouteValues["ID"];
			int													ID=int.Parse(RawID);

			NameProvider.RemoveName(ID);

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------