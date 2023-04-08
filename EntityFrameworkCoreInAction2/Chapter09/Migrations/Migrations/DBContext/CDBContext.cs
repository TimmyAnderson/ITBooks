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
using Microsoft.Extensions.Logging.Console;
using Microsoft.Extensions.Options;
//----------------------------------------------------------------------------------------------------------------------
namespace Migrations
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		public const string										TABLE_NAME_USING_UDF="EntitiesUsingUDF";
//----------------------------------------------------------------------------------------------------------------------
		private readonly EMigrationType							MMigrationType;
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityPrincipal>							MEntitiesPrincipal;
		private DbSet<CEntityDependent>							MEntitiesDependent;
		private DbSet<CEntityNotInMigration>					MEntitiesNotInMigration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
			MMigrationType=EMigrationType.E_MIGRATION_VERSION_2;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER urcuje ci sa ma pouzit MIGRATION VERSION 1, alebo MIGRATION VERSION 2.
		// !!! MIGRATION VERSION 1 NEOBSAHUJE ENTITY 'CEntityPrincipal' a ENTITY 'CEntityDependent', kym MIGRATION VERSION 1 ano.
		public CDBContext(EMigrationType MigrationType)
		{
			MMigrationType=MigrationType;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(bool UseLogging)
			: this()
		{
			MMigrationType=EMigrationType.E_MIGRATION_VERSION_2;

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
		public DbSet<CEntityNotInMigration>					EntitiesNotInMigration
		{
			get
			{
				return(MEntitiesNotInMigration);
			}
			set
			{
				MEntitiesNotInMigration=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void SetCustomHistoryTable(SqliteDbContextOptionsBuilder Builder)
		{
			// !!! Nastavi sa CUSTOM NAME pre MIGRATION TABLE.
			Builder.MigrationsHistoryTable("MyMigrationTable");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void RemoveFromMigrations(TableBuilder<CEntityNotInMigration> Builder)
		{
			// !!!!! ENTITY NEBUDE sucastou MIGRATIONS.
			Builder.ExcludeFromMigrations(true);
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
		private void ConfigureEntityPrincipal(ModelBuilder ModelBuilder)
		{
			if (MMigrationType==EMigrationType.E_MIGRATION_VERSION_1)
			{
				// !!!!! Ak sa pouzije MIGRATION VERSION 1, tak ENTITY bude IGNORED.
				ModelBuilder.Ignore<CEntityPrincipal>();
			}
			else if (MMigrationType==EMigrationType.E_MIGRATION_VERSION_2)
			{
				EntityTypeBuilder<CEntityPrincipal>				Entity=ModelBuilder.Entity<CEntityPrincipal>();

				Entity.ToTable("EntitiesPrincipal");

				Entity.HasKey(P => P.EntityPrincipalID);

				// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

				// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
				CollectionNavigationBuilder<CEntityPrincipal,CEntityDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

				// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
				ReferenceCollectionBuilder<CEntityPrincipal,CEntityDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

				// !!!!! Vytvori sa FOREIGN KEY.
				RightSide.HasForeignKey(P => P.EntityPrincipalID);

				// !!!!! RELATIONSHIP je REQUIRED.
				RightSide.IsRequired(true);
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED VALUE [{MMigrationType}]."));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDependent(ModelBuilder ModelBuilder)
		{
			if (MMigrationType==EMigrationType.E_MIGRATION_VERSION_1)
			{
				// !!!!! Ak sa pouzije MIGRATION VERSION 1, tak ENTITY bude IGNORED.
				ModelBuilder.Ignore<CEntityDependent>();
			}
			else if (MMigrationType==EMigrationType.E_MIGRATION_VERSION_2)
			{
				EntityTypeBuilder<CEntityDependent>				Entity=ModelBuilder.Entity<CEntityDependent>();

				Entity.ToTable("EntitiesDependent");

				Entity.HasKey(P => P.EntityDependentID);
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED VALUE [{MMigrationType}]."));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureNotInMigration(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNotInMigration>			Entity=ModelBuilder.Entity<CEntityNotInMigration>();

			// !!!!! ENTITY NEBUDE sucastou MIGRATIONS.
			Entity.ToTable("EntitiesNotInMigration",RemoveFromMigrations);

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void SeedData(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CTestEntity>						EntityTest=ModelBuilder.Entity<CTestEntity>();

			CTestEntity											TestEntity1=new CTestEntity(1,"AAA");
			CTestEntity											TestEntity2=new CTestEntity(2,"BBB");

			EntityTest.HasData(TestEntity1);
			EntityTest.HasData(TestEntity2);

			if (MMigrationType==EMigrationType.E_MIGRATION_VERSION_2)
			{
				// !!!!! Ak ENTITIES maju RELATIONSHIPS, PRIMARY a FOREIGN KEYS MUSIA byt nastavene.

				EntityTypeBuilder<CEntityPrincipal>				EntityPrincipal=ModelBuilder.Entity<CEntityPrincipal>();

				CEntityPrincipal								EntityPrincipal1=new CEntityPrincipal(1,111,"PRINCIPAL 111");
				CEntityPrincipal								EntityPrincipal2=new CEntityPrincipal(2,222,"PRINCIPAL 222");

				EntityPrincipal.HasData(EntityPrincipal1);
				EntityPrincipal.HasData(EntityPrincipal2);

				EntityTypeBuilder<CEntityDependent>				EntityDependent=ModelBuilder.Entity<CEntityDependent>();

				CEntityDependent								EntityDependent11=new CEntityDependent(1,111,"DEPENDENT 111",EntityPrincipal1.EntityPrincipalID);
				CEntityDependent								EntityDependent12=new CEntityDependent(2,222,"DEPENDENT 222",EntityPrincipal1.EntityPrincipalID);
				CEntityDependent								EntityDependent21=new CEntityDependent(3,333,"DEPENDENT 333",EntityPrincipal2.EntityPrincipalID);
				CEntityDependent								EntityDependent22=new CEntityDependent(4,444,"DEPENDENT 444",EntityPrincipal2.EntityPrincipalID);

				EntityDependent.HasData(EntityDependent11);
				EntityDependent.HasData(EntityDependent12);
				EntityDependent.HasData(EntityDependent21);
				EntityDependent.HasData(EntityDependent22);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			OptionsBuilder.UseSqlite(MConnectionString_SQLITE,SetCustomHistoryTable);

			OptionsBuilder.UseLoggerFactory(MLoggerFactory).EnableSensitiveDataLogging();
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityTest(ModelBuilder);
			ConfigureEntityPrincipal(ModelBuilder);
			ConfigureEntityDependent(ModelBuilder);
			ConfigureNotInMigration(ModelBuilder);

			SeedData(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------