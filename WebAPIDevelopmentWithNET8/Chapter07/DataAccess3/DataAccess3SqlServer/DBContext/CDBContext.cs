using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3SqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityTimestampsDataAnnotations>			MEntitiesTimestampsDataAnnotations;
		private DbSet<CEntityTimestampsFluentAPI>				MEntitiesTimestampsFluentAPI;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(DbContextOptions<CDBContext> Options)
			: base(Options)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTimestampsDataAnnotations>			EntitiesTimestampsDataAnnotations
		{
			get
			{
				return(MEntitiesTimestampsDataAnnotations);
			}
			set
			{
				MEntitiesTimestampsDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTimestampsFluentAPI>				EntitiesTimestampsFluentAPI
		{
			get
			{
				return(MEntitiesTimestampsFluentAPI);
			}
			set
			{
				MEntitiesTimestampsFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTimestampsDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTimestampsDataAnnotations>	Entity=ModelBuilder.Entity<CEntityTimestampsDataAnnotations>();

			Entity.ToTable("EntitiesTimestampsDataAnnotations");

			Entity.HasKey(P => P.EntityID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTimestampsFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTimestampsFluentAPI>		Entity=ModelBuilder.Entity<CEntityTimestampsFluentAPI>();

			Entity.ToTable("EntitiesTimestampsFluentAPI");

			Entity.HasKey(P => P.EntityID);

			// !!! Ziska sa PROPERTY, ktora bude oznacena ako TIMESTAMP.
			PropertyBuilder<byte[]>								ConcurrencyTokenProperty=Entity.Property(P => P.Timestamp);

			// !!! PROPERTY sa nastavi ako TIMESTAMP.
			ConcurrencyTokenProperty.IsRowVersion();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataTimestampsDataAnnotations(ModelBuilder ModelBuilder)
		{
			CEntityTimestampsDataAnnotations					Entity1=new CEntityTimestampsDataAnnotations(1,100);
			CEntityTimestampsDataAnnotations					Entity2=new CEntityTimestampsDataAnnotations(2,200);

			EntityTypeBuilder<CEntityTimestampsDataAnnotations>	Entities=ModelBuilder.Entity<CEntityTimestampsDataAnnotations>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataTimestampsFluentAPI(ModelBuilder ModelBuilder)
		{
			CEntityTimestampsFluentAPI							Entity1=new CEntityTimestampsFluentAPI(1,100);
			CEntityTimestampsFluentAPI							Entity2=new CEntityTimestampsFluentAPI(2,200);

			EntityTypeBuilder<CEntityTimestampsFluentAPI>		Entities=ModelBuilder.Entity<CEntityTimestampsFluentAPI>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityTimestampsDataAnnotations(ModelBuilder);
			ConfigureEntityTimestampsFluentAPI(ModelBuilder);

			FillDataTimestampsDataAnnotations(ModelBuilder);
			FillDataTimestampsFluentAPI(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------