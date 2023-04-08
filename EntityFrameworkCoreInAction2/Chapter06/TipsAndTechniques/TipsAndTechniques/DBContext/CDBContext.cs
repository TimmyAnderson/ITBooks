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
namespace TipsAndTechniques
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
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityManyToManyM>						MEntitiesManyToManyM;
		private DbSet<CEntityManyToManyN>						MEntitiesManyToManyN;
		private DbSet<CEntityManyToManyMN>						MEntitiesManyToManyMN;
		private DbSet<CEntityHierarchical>						MEntitiesHierarchical;
		private DbSet<CEntityIncludePrincipal>					MEntitiesIncludePrincipal;
		private DbSet<CEntityIncludeDependent1>					MEntitiesIncludeDependent1;
		private DbSet<CEntityIncludeDependent2>					MEntitiesIncludeDependent2;
		private DbSet<CEntityIncludeDependent3>					MEntitiesIncludeDependent3;
		private DbSet<CEntityMaxPrincipal>						MEntitiesMaxPrincipal;
		private DbSet<CEntityMaxDependent>						MEntitiesMaxDependent;
		private DbSet<CEntityGroupByFunction>					MEntitiesGroupByFunction;
		private DbSet<CEntityConstructorsPrincipal>				MEntitiesConstructorsPrincipal;
		private DbSet<CEntityConstructorsDependent>				MEntitiesConstructorsDependent;
		private DbSet<CEntityLazyLoadingPrincipal>				MEntitiesLazyLoadingPrincipal;
		private DbSet<CEntityLazyLoadingDependent>				MEntitiesLazyLoadingDependent;
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
		public DbSet<CEntityHierarchical>						EntitiesHierarchical
		{
			get
			{
				return(MEntitiesHierarchical);
			}
			set
			{
				MEntitiesHierarchical=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityIncludePrincipal>					EntitiesIncludePrincipal
		{
			get
			{
				return(MEntitiesIncludePrincipal);
			}
			set
			{
				MEntitiesIncludePrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityIncludeDependent1>					EntitiesIncludeDependent1
		{
			get
			{
				return(MEntitiesIncludeDependent1);
			}
			set
			{
				MEntitiesIncludeDependent1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityIncludeDependent2>					EntitiesIncludeDependent2
		{
			get
			{
				return(MEntitiesIncludeDependent2);
			}
			set
			{
				MEntitiesIncludeDependent2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityIncludeDependent3>					EntitiesIncludeDependent3
		{
			get
			{
				return(MEntitiesIncludeDependent3);
			}
			set
			{
				MEntitiesIncludeDependent3=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityMaxPrincipal>						EntitiesMaxPrincipal
		{
			get
			{
				return(MEntitiesMaxPrincipal);
			}
			set
			{
				MEntitiesMaxPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityMaxDependent>						EntitiesMaxDependent
		{
			get
			{
				return(MEntitiesMaxDependent);
			}
			set
			{
				MEntitiesMaxDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityGroupByFunction>					EntitiesGroupByFunction
		{
			get
			{
				return(MEntitiesGroupByFunction);
			}
			set
			{
				MEntitiesGroupByFunction=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityConstructorsPrincipal>				EntitiesConstructorsPrincipal
		{
			get
			{
				return(MEntitiesConstructorsPrincipal);
			}
			set
			{
				MEntitiesConstructorsPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityConstructorsDependent>				EntitiesConstructorsDependent
		{
			get
			{
				return(MEntitiesConstructorsDependent);
			}
			set
			{
				MEntitiesConstructorsDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityLazyLoadingPrincipal>				EntitiesLazyLoadingPrincipal
		{
			get
			{
				return(MEntitiesLazyLoadingPrincipal);
			}
			set
			{
				MEntitiesLazyLoadingPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityLazyLoadingDependent>				EntitiesLazyLoadingDependent
		{
			get
			{
				return(MEntitiesLazyLoadingDependent);
			}
			set
			{
				MEntitiesLazyLoadingDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTest(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CTestEntity>().ToTable("TestEntities");

			ModelBuilder.Entity<CTestEntity>().HasKey(P => P.ID);
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
		private void ConfigureEntityTableManyToManyM(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyM>().ToTable("EntitiesManyToManyM");

			ModelBuilder.Entity<CEntityManyToManyM>().HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTableManyToManyN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyN>().ToTable("EntitiesManyToManyN");

			ModelBuilder.Entity<CEntityManyToManyN>().HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTableManyToManyMN(ModelBuilder ModelBuilder)
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
		private void ConfigureEntityHierarchical(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityHierarchical>().ToTable("EntitiesHierarchical");

			ModelBuilder.Entity<CEntityHierarchical>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityHierarchical>				Entity=ModelBuilder.Entity<CEntityHierarchical>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityHierarchical,CEntityHierarchical>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityHierarchical,CEntityHierarchical>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.ForeignKeyID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityIncludePrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityIncludePrincipal>().ToTable("EntitiesIncludePrincipal");

			ModelBuilder.Entity<CEntityIncludePrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityIncludePrincipal>			Entity=ModelBuilder.Entity<CEntityIncludePrincipal>();

			CollectionNavigationBuilder<CEntityIncludePrincipal,CEntityIncludeDependent1>	LeftSideRelationship1=Entity.HasMany(P => P.EntitiesDependent1);

			ReferenceCollectionBuilder<CEntityIncludePrincipal,CEntityIncludeDependent1>	RightSideRelationship1=LeftSideRelationship1.WithOne(P => P.EntityPrincipal);

			RightSideRelationship1.HasForeignKey(P => P.EntityPrincipalID);

			CollectionNavigationBuilder<CEntityIncludePrincipal,CEntityIncludeDependent2>	LeftSideRelationship2=Entity.HasMany(P => P.EntitiesDependent2);

			ReferenceCollectionBuilder<CEntityIncludePrincipal,CEntityIncludeDependent2>	RightSideRelationship2=LeftSideRelationship2.WithOne(P => P.EntityPrincipal);

			RightSideRelationship2.HasForeignKey(P => P.EntityPrincipalID);

			CollectionNavigationBuilder<CEntityIncludePrincipal,CEntityIncludeDependent3>	LeftSideRelationship3=Entity.HasMany(P => P.EntitiesDependent3);

			ReferenceCollectionBuilder<CEntityIncludePrincipal,CEntityIncludeDependent3>	RightSideRelationship3=LeftSideRelationship3.WithOne(P => P.EntityPrincipal);

			RightSideRelationship3.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityIncludeDependent1(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityIncludeDependent1>().ToTable("EntitiesIncludeDependent1");

			ModelBuilder.Entity<CEntityIncludeDependent1>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityIncludeDependent2(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityIncludeDependent2>().ToTable("EntitiesIncludeDependent2");

			ModelBuilder.Entity<CEntityIncludeDependent2>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityIncludeDependent3(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityIncludeDependent3>().ToTable("EntitiesIncludeDependent3");

			ModelBuilder.Entity<CEntityIncludeDependent3>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityMaxPrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityMaxPrincipal>().ToTable("EntitiesMaxPrincipal");

			ModelBuilder.Entity<CEntityMaxPrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityMaxPrincipal>				Entity=ModelBuilder.Entity<CEntityMaxPrincipal>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityMaxPrincipal,CEntityMaxDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityMaxPrincipal,CEntityMaxDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityMaxDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityMaxDependent>().ToTable("EntitiesMaxDependent");

			ModelBuilder.Entity<CEntityMaxDependent>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityGroupByFunction(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityGroupByFunction>().ToTable("EntitiesGroupByFunction");

			ModelBuilder.Entity<CEntityGroupByFunction>().HasKey(P => P.NumberID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityConstructorsPrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityConstructorsPrincipal>().ToTable("EntitiesConstructorsPrincipal");

			ModelBuilder.Entity<CEntityConstructorsPrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityConstructorsPrincipal>		Entity=ModelBuilder.Entity<CEntityConstructorsPrincipal>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityConstructorsPrincipal,CEntityConstructorsDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityConstructorsPrincipal,CEntityConstructorsDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityConstructorsDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityConstructorsDependent>().ToTable("EntitiesConstructorsDependent");

			ModelBuilder.Entity<CEntityConstructorsDependent>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityLazyLoadingPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityLazyLoadingPrincipal>		Entity=ModelBuilder.Entity<CEntityLazyLoadingPrincipal>();

			Entity.ToTable("EntitiesLazyLoadingPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityLazyLoadingPrincipal,CEntityLazyLoadingDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityLazyLoadingPrincipal,CEntityLazyLoadingDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! LAZY LOADING pouzivajuca instanciu INTERFACE [ILazyLoader] vyzaduje nastavenie nazvu FIELD, ktory sa pouziva ako BACKING FIELD NAVIGATION PROPERTY.
			RightSideRelationship.Metadata.DependentToPrincipal.SetField("MEntityPrincipal");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityLazyLoadingDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityLazyLoadingDependent>		Entity=ModelBuilder.Entity<CEntityLazyLoadingDependent>();

			Entity.ToTable("EntitiesLazyLoadingDependent");

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
			ConfigureEntityTest(ModelBuilder);
			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);
			ConfigureEntityTableManyToManyM(ModelBuilder);
			ConfigureEntityTableManyToManyN(ModelBuilder);
			ConfigureEntityTableManyToManyMN(ModelBuilder);
			ConfigureEntityHierarchical(ModelBuilder);
			ConfigureEntityIncludePrincipal(ModelBuilder);
			ConfigureEntityIncludeDependent1(ModelBuilder);
			ConfigureEntityIncludeDependent2(ModelBuilder);
			ConfigureEntityIncludeDependent3(ModelBuilder);
			ConfigureEntityMaxPrincipal(ModelBuilder);
			ConfigureEntityMaxDependent(ModelBuilder);
			ConfigureEntityGroupByFunction(ModelBuilder);
			ConfigureEntityConstructorsPrincipal(ModelBuilder);
			ConfigureEntityConstructorsDependent(ModelBuilder);
			ConfigureEntityLazyLoadingPrincipal(ModelBuilder);
			ConfigureEntityLazyLoadingDependent(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------