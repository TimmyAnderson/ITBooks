using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CIdentitySeedData
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									ADMIN_USER="Admin";
		private const string									ADMIN_PASSWORD="Secret123$";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static async void EnsurePopulated(IApplicationBuilder ApplicationBuilder)
		{
			CIdentityDbContext									Context=ApplicationBuilder.ApplicationServices.CreateScope().ServiceProvider.GetRequiredService<CIdentityDbContext>();
			bool												HasMigrations=Context.Database.GetPendingMigrations().Any();

			if (HasMigrations==true)
			{
				Context.Database.Migrate();
			}

			UserManager<IdentityUser>							UserManager=ApplicationBuilder.ApplicationServices.CreateScope().ServiceProvider.GetRequiredService<UserManager<IdentityUser>>();
			IdentityUser										User=await UserManager.FindByIdAsync(ADMIN_USER);

			if (User==null)
			{
				User=new IdentityUser("Admin");

				User.Email="admin@example.com";
				User.PhoneNumber="555-1234";

				await UserManager.CreateAsync(User,ADMIN_PASSWORD);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------