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
namespace ChangingDBContent
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityOneToOnePrincipal>					MEntitiesOneToOnePrincipal;
		private DbSet<CEntityOneToOneDependent>					MEntitiesOneToOneDependent;
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityZeroToManyPrincipal>				MEntitiesZeroToManyPrincipal;
		private DbSet<CEntityZeroToManyDependent>				MEntitiesZeroToManyDependent;
		private DbSet<CEntityManyToManyM>						MEntitiesManyToManyM;
		private DbSet<CEntityManyToManyN>						MEntitiesManyToManyN;
		private DbSet<CEntityManyToManyMN>						MEntitiesManyToManyMN;
		private DbSet<CEntityManyToManyAutoM>					MEntitiesManyToManyAutoM;
		private DbSet<CEntityManyToManyAutoN>					MEntitiesManyToManyAutoN;
		private DbSet<CNumber>									MEntitiesNumbers;
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
		public DbSet<CTestEntity>								TestEntities
		{
			get
			{
				return(MTestEntities);
			}
			set
			{
				MTestEntities=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOnePrincipal>					EntitiesOneToOnePrincipal
		{
			get
			{
				return(MEntitiesOneToOnePrincipal);
			}
			set
			{
				MEntitiesOneToOnePrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependent>					EntitiesOneToOneDependent
		{
			get
			{
				return(MEntitiesOneToOneDependent);
			}
			set
			{
				MEntitiesOneToOneDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyPrincipal>					EntitiesOneToManyPrincipal
		{
			get
			{
				return(MEntitiesOneToManyPrincipal);
			}
			set
			{
				MEntitiesOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyDependent>					EntitiesOneToManyDependent
		{
			get
			{
				return(MEntitiesOneToManyDependent);
			}
			set
			{
				MEntitiesOneToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToManyPrincipal>				EntitiesZeroToManyPrincipal
		{
			get
			{
				return(MEntitiesZeroToManyPrincipal);
			}
			set
			{
				MEntitiesZeroToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToManyDependent>					EntitiesZeroToManyDependent
		{
			get
			{
				return(MEntitiesZeroToManyDependent);
			}
			set
			{
				MEntitiesZeroToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyM>						EntitiesManyToManyM
		{
			get
			{
				return(MEntitiesManyToManyM);
			}
			set
			{
				MEntitiesManyToManyM=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyN>						EntitiesManyToManyN
		{
			get
			{
				return(MEntitiesManyToManyN);
			}
			set
			{
				MEntitiesManyToManyN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMN>						EntitiesManyToManyMN
		{
			get
			{
				return(MEntitiesManyToManyMN);
			}
			set
			{
				MEntitiesManyToManyMN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyAutoM>					EntitiesManyToManyAutoM
		{
			get
			{
				return(MEntitiesManyToManyAutoM);
			}
			set
			{
				MEntitiesManyToManyAutoM=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyAutoN>					EntitiesManyToManyAutoN
		{
			get
			{
				return(MEntitiesManyToManyAutoN);
			}
			set
			{
				MEntitiesManyToManyAutoN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CNumber>									EntitiesNumbers
		{
			get
			{
				return(MEntitiesNumbers);
			}
			set
			{
				MEntitiesNumbers=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTestEntity(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CTestEntity>().ToTable("TestEntities");

			ModelBuilder.Entity<CTestEntity>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableOneToOnePrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToOnePrincipal>().ToTable("EntitiesOneToOnePrincipal");

			ModelBuilder.Entity<CEntityOneToOnePrincipal>().HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableOneToOneDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToOneDependent>().ToTable("EntitiesOneToOneDependent");

			ModelBuilder.Entity<CEntityOneToOneDependent>().HasKey(P => P.EntityDependentID);

			EntityTypeBuilder<CEntityOneToOneDependent>			Entity=ModelBuilder.Entity<CEntityOneToOneDependent>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityOneToOneDependent,CEntityOneToOnePrincipal>	LeftSideRelationship=Entity.HasOne(P => P.EntityPrincipal);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceReferenceBuilder<CEntityOneToOneDependent,CEntityOneToOnePrincipal>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityDependent);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey<CEntityOneToOneDependent>(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyPrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToManyPrincipal>().ToTable("EntitiesOneToManyPrincipal");

			ModelBuilder.Entity<CEntityOneToManyPrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityOneToManyPrincipal>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToManyDependent>().ToTable("EntitiesOneToManyDependent");

			ModelBuilder.Entity<CEntityOneToManyDependent>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyPrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityZeroToManyPrincipal>().ToTable("EntitiesZeroToManyPrincipal");

			ModelBuilder.Entity<CEntityZeroToManyPrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityZeroToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityZeroToManyPrincipal>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityZeroToManyPrincipal,CEntityZeroToManyDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityZeroToManyPrincipal,CEntityZeroToManyDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			// !!!!! Nastavi sa, ze FOREIGN KEY je NULLABLE.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID).IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityZeroToManyDependent>().ToTable("EntitiesZeroToManyDependent");

			ModelBuilder.Entity<CEntityZeroToManyDependent>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyM(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyM>().ToTable("EntitiesManyToManyM");

			ModelBuilder.Entity<CEntityManyToManyM>().HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyN>().ToTable("EntitiesManyToManyN");

			ModelBuilder.Entity<CEntityManyToManyN>().HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyMN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyMN>().ToTable("EntitiesManyToManyMN");

			// !!!!! LINK ENTITY v RELATIONSHIP M:N MUSI mat COMPOSITE KEY.
			ModelBuilder.Entity<CEntityManyToManyMN>().HasKey(nameof(CEntityManyToManyMN.EntityMID),nameof(CEntityManyToManyMN.EntityNID));

			EntityTypeBuilder<CEntityManyToManyMN>				Entity=ModelBuilder.Entity<CEntityManyToManyMN>();

			// !!!!! Vytvori sa RELATIONSHIP 1:N medzi LINK ENTITY a ENTITY M.

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityManyToManyMN,CEntityManyToManyM>	RightSideEntityM=Entity.HasOne(P => P.EntityM);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityManyToManyM,CEntityManyToManyMN>	LeftSideEntityM=RightSideEntityM.WithMany(P => P.EntitiesMN);

			// !!!!! Definuje sa FOREIGN KEY.
			LeftSideEntityM.HasForeignKey(P => P.EntityMID);

			// !!!!! Vytvori sa RELATIONSHIP 1:N medzi LINK ENTITY a ENTITY M.

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityManyToManyMN,CEntityManyToManyN>	RightSideEntityN=Entity.HasOne(P => P.EntityN);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityManyToManyN,CEntityManyToManyMN>	LeftSideEntityN=RightSideEntityN.WithMany(P => P.EntitiesMN);

			// !!!!! Definuje sa FOREIGN KEY.
			LeftSideEntityN.HasForeignKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyAutoM(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyAutoM>().ToTable("EntitiesManyToManyAutoM");

			ModelBuilder.Entity<CEntityManyToManyAutoM>().HasKey(P => P.EntityMID);

			EntityTypeBuilder<CEntityManyToManyAutoM>			Entity=ModelBuilder.Entity<CEntityManyToManyAutoM>();

			// !!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityManyToManyAutoM,CEntityManyToManyAutoN>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesN);

			// !!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			LeftSideRelationship.WithMany(P => P.EntitiesM);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyAutoN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyAutoN>().ToTable("EntitiesManyToManyAutoN");

			ModelBuilder.Entity<CEntityManyToManyAutoN>().HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableNumber(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CNumber>().ToTable("EntitiesNumber");

			ModelBuilder.Entity<CNumber>().HasKey(P => P.NumberID);

			// !!!!! Nastavi sa FILTER, ktory sa aplikuje na KAZDU QUERY, ktora nepouzije METHOD [IQueryable<TEntity> IQueryable<TEntity>.IgnoreQueryFilters<TEntity>()].
			ModelBuilder.Entity<CNumber>().HasQueryFilter(P => P.Number>5);
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
			ConfigureTestEntity(ModelBuilder);
			ConfigureTableOneToOnePrincipal(ModelBuilder);
			ConfigureTableOneToOneDependent(ModelBuilder);
			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);
			ConfigureEntityZeroToManyPrincipal(ModelBuilder);
			ConfigureEntityZeroToManyDependent(ModelBuilder);
			ConfigureTableManyToManyM(ModelBuilder);
			ConfigureTableManyToManyN(ModelBuilder);
			ConfigureTableManyToManyMN(ModelBuilder);
			ConfigureTableManyToManyAutoM(ModelBuilder);
			ConfigureTableManyToManyAutoN(ModelBuilder);
			ConfigureTableNumber(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------