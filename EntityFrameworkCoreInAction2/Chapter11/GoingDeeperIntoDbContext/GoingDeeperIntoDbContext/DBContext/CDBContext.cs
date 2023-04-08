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
namespace GoingDeeperIntoDbContext
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		public const string										TO_SQL_QUERY_TABLE_NAME="EntitiesToSqlQueryBackendData";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ECustomExecutionStrategy				MCustomExecutionStrategy;
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityZeroToManyPrincipal>				MEntitiesZeroToManyPrincipal;
		private DbSet<CEntityZeroToManyDependent>				MEntitiesZeroToManyDependent;
		private DbSet<CEntityOneToManyTrackingChangesSnapshotPrincipal>	MEntitiesOneToManyTrackingChangesSnapshotPrincipal;
		private DbSet<CEntityOneToManyTrackingChangesSnapshotDependent>	MEntitiesOneToManyTrackingChangesSnapshotDependent;
		private DbSet<CEntityOneToManyTrackingChangesChangedNotificationsPrincipal>	MEntitiesOneToManyTrackingChangesChangedNotificationsPrincipal;
		private DbSet<CEntityOneToManyTrackingChangesChangedNotificationsDependent>	MEntitiesOneToManyTrackingChangesChangedNotificationsDependent;
		private DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal>	MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal;
		private DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent;
		private DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal>	MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal;
		private DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>	MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent;
		private DbSet<CEntityToSqlQueryBackendData>				MEntitiesToSqlQueryBackendData;
		private DbSet<CEntityToSqlQuery>						MEntitiesToSqlQuery;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
			MCustomExecutionStrategy=ECustomExecutionStrategy.E_DO_NOT_USE_CUSTOM_EXECUTION_STRATEGY;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(ECustomExecutionStrategy CustomExecutionStrategy)
		{
			MCustomExecutionStrategy=CustomExecutionStrategy;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(bool UseLogging)
			: this()
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
		public DbSet<CEntityZeroToManyDependent>				EntitiesZeroToManyDependent
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
		public DbSet<CEntityOneToManyTrackingChangesSnapshotPrincipal>	EntitiesOneToManyTrackingChangesSnapshotPrincipal
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesSnapshotPrincipal);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesSnapshotPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesSnapshotDependent>	EntitiesOneToManyTrackingChangesSnapshotDependent
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesSnapshotDependent);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesSnapshotDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesChangedNotificationsPrincipal>	EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesChangedNotificationsPrincipal);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesChangedNotificationsPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesChangedNotificationsDependent>	EntitiesOneToManyTrackingChangesChangedNotificationsDependent
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesChangedNotificationsDependent);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesChangedNotificationsDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal>	EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal>	EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>	EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent
		{
			get
			{
				return(MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent);
			}
			set
			{
				MEntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityToSqlQueryBackendData>				EntitiesToSqlQueryBackendData
		{
			get
			{
				return(MEntitiesToSqlQueryBackendData);
			}
			set
			{
				MEntitiesToSqlQueryBackendData=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityToSqlQuery>							EntitiesToSqlQuery
		{
			get
			{
				return(MEntitiesToSqlQuery);
			}
			set
			{
				MEntitiesToSqlQuery=value;
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
			EntityTypeBuilder<CEntityOneToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityOneToManyPrincipal>();

			Entity.ToTable("EntitiesOneToManyPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyDependent>		Entity=ModelBuilder.Entity<CEntityOneToManyDependent>();

			Entity.ToTable("EntitiesOneToManyDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityZeroToManyPrincipal>();

			Entity.ToTable("EntitiesZeroToManyPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityZeroToManyPrincipal,CEntityZeroToManyDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroToManyPrincipal,CEntityZeroToManyDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToManyDependent>		Entity=ModelBuilder.Entity<CEntityZeroToManyDependent>();

			Entity.ToTable("EntitiesZeroToManyDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesSnapshotPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesSnapshotPrincipal>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesSnapshotPrincipal>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesSnapshotPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToManyTrackingChangesSnapshotPrincipal,CEntityOneToManyTrackingChangesSnapshotDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToManyTrackingChangesSnapshotPrincipal,CEntityOneToManyTrackingChangesSnapshotDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [Snapshot].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.Snapshot);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesSnapshotDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesSnapshotDependent>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesSnapshotDependent>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesSnapshotDependent");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [Snapshot].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.Snapshot);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesChangedNotificationsPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesChangedNotificationsPrincipal>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesChangedNotificationsPrincipal>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToManyTrackingChangesChangedNotificationsPrincipal,CEntityOneToManyTrackingChangesChangedNotificationsDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToManyTrackingChangesChangedNotificationsPrincipal,CEntityOneToManyTrackingChangesChangedNotificationsDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [ChangedNotifications].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.ChangedNotifications);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesChangedNotificationsDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesChangedNotificationsDependent>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesChangedNotificationsDependent>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesChangedNotificationsDependent");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [ChangedNotifications].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.ChangedNotifications);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal,CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal,CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [ChangingAndChangedNotifications].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.ChangingAndChangedNotifications);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [ChangingAndChangedNotifications].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.ChangingAndChangedNotifications);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal,CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal,CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [ChangingAndChangedNotificationsWithOriginalValues].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.ChangingAndChangedNotificationsWithOriginalValues);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>	Entity=ModelBuilder.Entity<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>();

			Entity.ToTable("EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! TRACKING CHANGES MODE je nastaveny na VALUE [ChangingAndChangedNotificationsWithOriginalValues].
			Entity.HasChangeTrackingStrategy(ChangeTrackingStrategy.ChangingAndChangedNotificationsWithOriginalValues);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityToSqlQueryBackendData(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityToSqlQueryBackendData>		Entity=ModelBuilder.Entity<CEntityToSqlQueryBackendData>();

			Entity.ToTable(TO_SQL_QUERY_TABLE_NAME);

			Entity.HasKey(P => P.EntityID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityToSqlQuery(ModelBuilder ModelBuilder)
		{
			// !!!!! SQL z ktorej sa vytvori ENTITY.
			string												SQL=$"SELECT EntityID, EntityIntValue, EntityStringValue, EntityDoubleValue FROM {TO_SQL_QUERY_TABLE_NAME} ORDER BY EntityIntValue DESC";

			// !!!!! ENTITY sa vytvori z SQL COMMAND.
			// !!!!! ENTITY je READ ONLY.
			EntityTypeBuilder<CEntityToSqlQuery>				Entity=ModelBuilder.Entity<CEntityToSqlQuery>().ToSqlQuery(SQL);

			Entity.HasKey(P => P.EntityID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void SetOptions(SqliteDbContextOptionsBuilder OptionsBuilder)
		{
			if (MCustomExecutionStrategy==ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY)
			{
				// !!!!! Nastavi sa CUSTOM EXECUTION STRATEGY.
				OptionsBuilder.ExecutionStrategy(P => new CMyExecutionStrategy(P));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			OptionsBuilder.UseSqlite(MConnectionString_SQLITE,SetOptions);

			OptionsBuilder.UseLoggerFactory(MLoggerFactory).EnableSensitiveDataLogging();
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityTest(ModelBuilder);
			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);
			ConfigureEntityZeroToManyPrincipal(ModelBuilder);
			ConfigureEntityZeroToManyDependent(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesSnapshotPrincipal(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesSnapshotDependent(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesChangedNotificationsPrincipal(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesChangedNotificationsDependent(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal(ModelBuilder);
			ConfigureEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(ModelBuilder);
			ConfigureEntityToSqlQueryBackendData(ModelBuilder);
			ConfigureEntityToSqlQuery(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------