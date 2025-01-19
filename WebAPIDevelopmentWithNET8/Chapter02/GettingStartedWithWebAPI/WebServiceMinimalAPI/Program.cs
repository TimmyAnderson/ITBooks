using System;
using System.Linq;
using System.Text.Json.Serialization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Routing;
using Microsoft.Extensions.DependencyInjection;
//--------------------------------------------------------------------------------------------------------------------------------
namespace WebServiceMinimalAPI
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static CName[] GetNames(INameService NameService)
		{
			return(NameService.GetNames());
		}
//----------------------------------------------------------------------------------------------------------------------
		private static IResult GetName(INameService NameService, int ID)
		{
			CName												Name=NameService.GetName(ID);

			if (Name!=null)
			{
				IResult											Result=Results.Ok(Name);

				return(Result);
			}
			else
			{
				IResult											Result=Results.NotFound();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static IResult AddName(INameService NameService, CNameInput NameInput)
		{
			CName												Name=NameService.AddName(NameInput.FirstName,NameInput.LastName,NameInput.Age);
			IResult												Result=Results.Created("",Name);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static IResult UpdateName(INameService NameService, CName ExistingName)
		{
			CName												Name=NameService.UpdateName(ExistingName);

			if (Name!=null)
			{
				IResult											Result=Results.Ok(Name);

				return(Result);
			}
			else
			{
				IResult											Result=Results.NotFound();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static IResult DeleteName(INameService NameService, int ID)
		{
			bool												Deleted=NameService.DeleteName(ID);

			if (Deleted==true)
			{
				IResult											Result=Results.NoContent();

				return(Result);
			}
			else
			{
				IResult											Result=Results.NotFound();

				return(Result);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateSlimBuilder(args);

			Builder.Services.ConfigureHttpJsonOptions(Options =>
			{
				Options.SerializerOptions.TypeInfoResolverChain.Insert(0,AppJsonSerializerContext.Default);
			});

			Builder.Services.AddTransient<INameService,CNameService>();

			WebApplication										Application=Builder.Build();

			// !!! Vytvori sa GROUP.
			RouteGroupBuilder									GroupName=Application.MapGroup("/Name");
		
			GroupName.MapGet("/",GetNames);
			GroupName.MapGet("/{ID}",GetName);
			GroupName.MapPost("/",AddName);
			GroupName.MapPut("/",UpdateName);
			GroupName.MapDelete("/{ID}",DeleteName);

			Application.Run();
		}
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
[JsonSerializable(typeof(WebServiceMinimalAPI.CName[]))]
[JsonSerializable(typeof(WebServiceMinimalAPI.CNameInput))]
internal partial class AppJsonSerializerContext:JsonSerializerContext
{
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------