using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Models
{
//----------------------------------------------------------------------------------------------------------------------
	internal static class CInitialDataSeed
	{
//----------------------------------------------------------------------------------------------------------------------
		internal static void CreateSchemeAndAddInitialData(IApplicationBuilder ApplicationBuilder)
		{
			using(CApplicationDbContext Context=ApplicationBuilder.ApplicationServices.GetRequiredService<CApplicationDbContext>())
			{
				bool											HasMigrations=Context.Database.GetPendingMigrations().Any();

				if (HasMigrations==true)
				{
					Context.Database.Migrate();
				}

				int												NumberOfProducts=Context.Products.Count();

				if (NumberOfProducts==0)
				{
					Context.Products.Add(new CProduct("Kayak","A boat for one person.","Watersports",275));
					Context.Products.Add(new CProduct("Lifejacket","Protective and fashionable.","Watersports",48.95m));
					Context.Products.Add(new CProduct("Soccer Ball","FIFA-approved size and weight.","Soccer",19.50m));
					Context.Products.Add(new CProduct("Corner Flags","Give your playing field a professional touch.","Soccer",34.95m));
					Context.Products.Add(new CProduct("Stadium","Flat-packed 35,000-seat stadium.","Soccer",79500));
					Context.Products.Add(new CProduct("Thinking Cap","Improve brain efficiency by 75%.","Chess",16));
					Context.Products.Add(new CProduct("Unsteady Chair","Secretly give your opponent a disadvantage.","Chess",29.95m));
					Context.Products.Add(new CProduct("Human Chess Board","A fun game for the family.","Chess",75));
					Context.Products.Add(new CProduct("Bling-Bling King","Gold-plated, diamond-studded King.","Chess",1200));

					Context.SaveChanges();
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------