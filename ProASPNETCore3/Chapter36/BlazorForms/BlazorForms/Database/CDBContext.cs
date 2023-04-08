using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Database
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityPerson>							MPersons;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPerson>								Persons
		{
			get
			{
				return(MPersons);
			}
			set
			{
				MPersons=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			base.OnModelCreating(ModelBuilder);

			ModelBuilder.Entity<CEntityPerson>().ToTable("Person");

			ModelBuilder.Entity<CEntityPerson>().HasKey(P => P.ID);

			EntityTypeBuilder<CEntityPerson>					Builder=ModelBuilder.Entity<CEntityPerson>();

			Builder.HasData(new CEntityPerson(1,"Timmy","Anderson",12,1));
			Builder.HasData(new CEntityPerson(2,"Jenny","Thompson",13,2));
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			base.OnConfiguring(OptionsBuilder);

			OptionsBuilder.UseSqlite("Data Source=MyDatabase.db");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------