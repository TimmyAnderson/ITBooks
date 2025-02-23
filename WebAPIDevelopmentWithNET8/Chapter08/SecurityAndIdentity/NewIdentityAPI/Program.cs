using System;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Routing;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//--------------------------------------------------------------------------------------------------------------------------------
namespace NewIdentityAPI
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static bool CreateDatabase(WebApplication Application)
		{
			using(IServiceScope ServiceScope=Application.Services.CreateScope())
			{
				using(CIdentityContextDB Context=ServiceScope.ServiceProvider.GetRequiredService<CIdentityContextDB>())
				{
					try
					{
						if (Context.Database.CanConnect()==false)
						{
							Context.Database.EnsureCreated();
						}

						RoleManager<CIdentityRole>				RoleManager=ServiceScope.ServiceProvider.GetRequiredService<RoleManager<CIdentityRole>>();
						string[]								RoleNames=new string[]{CSecurityRoles.ADMINISTRATORS,CSecurityRoles.VIPS,CSecurityRoles.USERS};

						foreach(string RoleName in RoleNames)
						{
							bool								RoleExists=RoleManager.RoleExistsAsync(RoleName).Result;

							if (RoleExists==false)
							{
								RoleManager.CreateAsync(new CIdentityRole(RoleName)).Wait();
							}
						}

						return(true);
					}
					catch(Exception E)
					{
						Console.WriteLine($"EXCEPTION [{E.Message}] !");
						return(false);
					}
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder = WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			// !!! Prida sa DB CONTEXT pre IDENTITY DB.
			Builder.Services.AddDbContext<CIdentityContextDB>();

			// !!! Pridaju sa SERVICES pre IDENTITY FRAMEWORK.
			IdentityBuilder										IdentityBuilder=Builder.Services.AddIdentityApiEndpoints<CIdentityUser>();
				
			// !!! Pridaju sa ROLES.
			IdentityBuilder.AddRoles<CIdentityRole>();

			// !!! Do DB CONTEXT sa pridaju TABLES pre ukladanie IDENTITY.
			IdentityBuilder.AddEntityFrameworkStores<CIdentityContextDB>();

			Builder.Services.AddAuthorization();

			WebApplication										Application=Builder.Build();

			if (CreateDatabase(Application)==false)
			{
				return;
			}

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			// !!! Pridaju sa IDENTITY ENTPOINTS.
			Application.MapGroup("/MyAccount").MapIdentityApi<CIdentityUser>();

			Application.MapControllers();

			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------