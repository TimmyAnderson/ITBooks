using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Console;
using Microsoft.Extensions.Options;
//----------------------------------------------------------------------------------------------------------------------
namespace LazyLoadingUsingILazyLoader
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityPrincipal>							MEntitiesPrincipal;
		private DbSet<CEntityDependent>							MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(bool UseLogging)
		{
			if (UseLogging==true)
			{
				OptionsFactory<ConsoleLoggerOptions>			OptionsFactory=new OptionsFactory<ConsoleLoggerOptions>(new ConfigureOptions<ConsoleLoggerOptions>[0],new IPostConfigureOptions<ConsoleLoggerOptions>[0]);
				OptionsMonitor<ConsoleLoggerOptions>			OptionsMonitor=new OptionsMonitor<ConsoleLoggerOptions>(OptionsFactory,new IOptionsChangeTokenSource<ConsoleLoggerOptions>[0],new OptionsCache<ConsoleLoggerOptions>());
				ConsoleLoggerProvider							LoggerProvider=new ConsoleLoggerProvider(OptionsMonitor);
				ILoggerProvider[]								LoggerProviders=new ILoggerProvider[]{LoggerProvider};
				LoggerFilterOptions								FilterOptions=new LoggerFilterOptions();

				FilterOptions.MinLevel=LogLevel.Trace;

				MLoggerFactory=new LoggerFactory(LoggerProviders,FilterOptions);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPrincipal>							EntitiesPrincipal
		{
			get
			{
				return(MEntitiesPrincipal);
			}
			set
			{
				MEntitiesPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDependent>							EntitiesDependent
		{
			get
			{
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityPrincipal>					Entity=ModelBuilder.Entity<CEntityPrincipal>();

			Entity.ToTable("EntitiesPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityPrincipal,CEntityDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityPrincipal,CEntityDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! LAZY LOADING pouzivajuca instanciu INTERFACE [ILazyLoader] vyzaduje nastavenie nazvu FIELD, ktory sa pouziva ako BACKING FIELD NAVIGATION PROPERTY.
			RightSideRelationship.Metadata.DependentToPrincipal.SetField("MEntityPrincipal");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDependent>					Entity=ModelBuilder.Entity<CEntityDependent>();

			Entity.ToTable("EntitiesDependent");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! LAZY LOADING pouzivajuca instanciu INTERFACE [ILazyLoader] vyzaduje nastavenie nazvu FIELD, ktory sa pouziva ako BACKING FIELD NAVIGATION PROPERTY.
			Entity.HasOne(P => P.EntityPrincipal).WithMany(P => P.EntitiesDependent).Metadata.PrincipalToDependent.SetField("MEntitiesDependent");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			OptionsBuilder.UseLoggerFactory(MLoggerFactory).EnableSensitiveDataLogging();
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityPrincipal(ModelBuilder);
			ConfigureEntityDependent(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------