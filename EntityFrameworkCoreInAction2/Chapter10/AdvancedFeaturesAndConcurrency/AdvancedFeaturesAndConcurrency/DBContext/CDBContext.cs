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
namespace AdvancedFeaturesAndConcurrency
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		public const string										TABLE_NAME_USING_UDF="EntitiesUsingUDF";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityUsingUDF>							MEntitiesUsingUDF;
		private DbSet<CEntityComputedColumns>					MEntitiesComputedColumns;
		private DbSet<CEntityDefaultValueColumns>				MEntitiesDefaultValueColumns;
		private DbSet<CEntityDBGeneratedPropertiesDataAnnotations>	MEntitiesDBGeneratedPropertiesDataAnnotations;
		private DbSet<CEntityDBGeneratedPropertiesFluentAPI>	MEntitiesDBGeneratedPropertiesFluentAPI;
		private DbSet<CEntityOptimisticConcurrency>				MEntitiesOptimisticConcurrency;
		private DbSet<CEntityConcurrencyTokensDataAnnotations>	MEntitiesConcurrencyTokensDataAnnotations;
		private DbSet<CEntityConcurrencyTokensFluentAPI>		MEntitiesConcurrencyTokensFluentAPI;
		private DbSet<CEntityMultipleConcurrencyTokensFluentAPI>	MEntitiesMultipleConcurrencyTokensFluentAPI;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
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
		public DbSet<CEntityUsingUDF>							EntitiesUsingUDF
		{
			get
			{
				return(MEntitiesUsingUDF);
			}
			set
			{
				MEntitiesUsingUDF=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityComputedColumns>					EntitiesComputedColumns
		{
			get
			{
				return(MEntitiesComputedColumns);
			}
			set
			{
				MEntitiesComputedColumns=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDefaultValueColumns>				EntitiesDefaultValueColumns
		{
			get
			{
				return(MEntitiesDefaultValueColumns);
			}
			set
			{
				MEntitiesDefaultValueColumns=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDBGeneratedPropertiesDataAnnotations>	EntitiesDBGeneratedPropertiesDataAnnotations
		{
			get
			{
				return(MEntitiesDBGeneratedPropertiesDataAnnotations);
			}
			set
			{
				MEntitiesDBGeneratedPropertiesDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDBGeneratedPropertiesFluentAPI>		EntitiesDBGeneratedPropertiesFluentAPI
		{
			get
			{
				return(MEntitiesDBGeneratedPropertiesFluentAPI);
			}
			set
			{
				MEntitiesDBGeneratedPropertiesFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOptimisticConcurrency>				EntitiesOptimisticConcurrency
		{
			get
			{
				return(MEntitiesOptimisticConcurrency);
			}
			set
			{
				MEntitiesOptimisticConcurrency=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityConcurrencyTokensDataAnnotations>	EntitiesConcurrencyTokensDataAnnotations
		{
			get
			{
				return(MEntitiesConcurrencyTokensDataAnnotations);
			}
			set
			{
				MEntitiesConcurrencyTokensDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityConcurrencyTokensFluentAPI>			EntitiesConcurrencyTokensFluentAPI
		{
			get
			{
				return(MEntitiesConcurrencyTokensFluentAPI);
			}
			set
			{
				MEntitiesConcurrencyTokensFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityMultipleConcurrencyTokensFluentAPI>	EntitiesMultipleConcurrencyTokensFluentAPI
		{
			get
			{
				return(MEntitiesMultipleConcurrencyTokensFluentAPI);
			}
			set
			{
				MEntitiesMultipleConcurrencyTokensFluentAPI=value;
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
		private void ConfigureEntityUsingUDF(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityUsingUDF>					Entity=ModelBuilder.Entity<CEntityUsingUDF>();

			Entity.ToTable(TABLE_NAME_USING_UDF);

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityComputedColumns(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityComputedColumns>			Entity=ModelBuilder.Entity<CEntityComputedColumns>();

			Entity.ToTable("EntitiesComputedColumns");

			Entity.HasKey(P => P.ID);

			// !!! Ziska sa REFERENCE na PROPERTY reprezentujucu COMPUTED PROPERTY.
			PropertyBuilder<int>								PropertyComputedValueDynamic=Entity.Property(P => P.ComputedValueDynamic);

			// !!!!! Nastavi sa SQL CODE, ktory sa vykona pri vypocte COMPUTED PROPERTY.
			// !!!!! PROPERTY sa nastavi ako DYNAMIC.
			PropertyComputedValueDynamic.HasComputedColumnSql("[IntValue1] + [IntValue2]",false);

			// !!! Ziska sa REFERENCE na PROPERTY reprezentujucu COMPUTED PROPERTY.
			PropertyBuilder<string>								PropertyComputedValuePersistent=Entity.Property(P => P.ComputedValuePersistent);

			// !!!!! Nastavi sa SQL CODE, ktory sa vykona pri vypocte COMPUTED PROPERTY.
			// !!!!! PROPERTY sa nastavi ako PERSISTENT.
			PropertyComputedValuePersistent.HasComputedColumnSql("[StringValue1] || ' ' || [StringValue2]",true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDefaultValueColumns(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDefaultValueColumns>		Entity=ModelBuilder.Entity<CEntityDefaultValueColumns>();

			Entity.ToTable("EntitiesDefaultValueColumns");

			Entity.HasKey(P => P.ID);

			// !!! Ziska sa REFERENCE na PROPERTY pre ktoru sa nastavi DEFAULT VALUE.
			PropertyBuilder<DateTime>							PropertyDefaultValue1=Entity.Property(P => P.DefaultValue1);

			// !!! DEFAULT VALUE bude generovana pomocou .NET EXPRESSION, ktora sa transformuje na SQL COMMAND.
			PropertyDefaultValue1.HasDefaultValue(new DateTime(2000,1,1,1,1,1));

			// !!! Ziska sa REFERENCE na PROPERTY pre ktoru sa nastavi DEFAULT VALUE.
			PropertyBuilder<double>								PropertyDefaultValue2=Entity.Property(P => P.DefaultValue2);

			// !!! DEFAULT VALUE bude generovana pomocou SQL COMMAND.
			PropertyDefaultValue2.HasDefaultValueSql("111.222");

			// !!! Ziska sa REFERENCE na PROPERTY pre ktoru sa nastavi DEFAULT VALUE.
			PropertyBuilder<int>								PropertyDefaultValue3=Entity.Property(P => P.DefaultValue3);

			// !!! DEFAULT VALUE bude generovana pomocou VALUE GENERATOR.
			PropertyDefaultValue3.HasValueGenerator(typeof(CIntValueGenerator));
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDBGeneratedPropertiesDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDBGeneratedPropertiesDataAnnotations>	Entity=ModelBuilder.Entity<CEntityDBGeneratedPropertiesDataAnnotations>();

			Entity.ToTable("EntitiesDBGeneratedPropertiesDataAnnotations");

			Entity.HasKey(P => P.DatabaseGeneratedIdentity);

			// !!! Ziska sa REFERENCIA na PROPERTY.
			PropertyBuilder<int>								ComputedProperty=Entity.Property(P => P.DatabaseGeneratedComputed);

			// !!! Nastavi sa SQL SCRIPT pre COMPUTED COLUMN.
			ComputedProperty.HasComputedColumnSql<int>("NonDatabaseGenerated+20");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDBGeneratedPropertiesFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDBGeneratedPropertiesFluentAPI>	Entity=ModelBuilder.Entity<CEntityDBGeneratedPropertiesFluentAPI>();

			Entity.ToTable("EntitiesDBGeneratedPropertiesFluentAPI");

			Entity.HasKey(P => P.DatabaseGeneratedOnAdd);

			// !!! Ziska sa REFERENCIA na PROPERTY.
			PropertyBuilder<int>								PropertyDatabaseGeneratedOnAdd=Entity.Property(P => P.DatabaseGeneratedOnAdd);

			// !!!!! PROPERTY sa nastavi ako PROPERTY, ktora je generovana v DATABASE pri INSERT.
			PropertyDatabaseGeneratedOnAdd.ValueGeneratedOnAdd();

			// !!! Ziska sa REFERENCIA na PROPERTY.
			PropertyBuilder<int>								PropertyDatabaseGeneratedOnAddOrUpdate=Entity.Property(P => P.DatabaseGeneratedOnAddOrUpdate);

			// !!! Nastavi sa SQL SCRIPT pre COMPUTED COLUMN.
			PropertyDatabaseGeneratedOnAddOrUpdate.HasComputedColumnSql<int>("NonDatabaseGenerated+10");

			// !!!!! PROPERTY sa nastavi ako PROPERTY, ktora je generovana v DATABASE pri INSERT, alebo UPDATE.
			PropertyDatabaseGeneratedOnAddOrUpdate.ValueGeneratedOnAddOrUpdate();

			// !!! Ziska sa REFERENCIA na PROPERTY.
			PropertyBuilder<int>								PropertyDatabaseGeneratedOnUpdate=Entity.Property(P => P.DatabaseGeneratedOnUpdate);

			// !!!!! PROPERTY sa nastavi ako PROPERTY, ktora je generovana v DATABASE pri UPDATE.
			PropertyDatabaseGeneratedOnUpdate.ValueGeneratedOnUpdate();

			// !!! Ziska sa REFERENCIA na PROPERTY.
			PropertyBuilder<int>								PropertyNonDatabaseGenerated=Entity.Property(P => P.NonDatabaseGenerated);

			// !!!!! PROPERTY sa nastavi ako PROPERTY, ktora NIE JE generovana v DATABASE.
			PropertyNonDatabaseGenerated.ValueGeneratedNever();
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOptimisticConcurrency(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOptimisticConcurrency>		Entity=ModelBuilder.Entity<CEntityOptimisticConcurrency>();

			Entity.ToTable("EntitiesOptimisticConcurrency");

			Entity.HasKey(P => P.EntityID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityConcurrencyTokensDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityConcurrencyTokensDataAnnotations>	Entity=ModelBuilder.Entity<CEntityConcurrencyTokensDataAnnotations>();

			Entity.ToTable("EntitiesConcurrencyTokensDataAnnotations");

			Entity.HasKey(P => P.EntityID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityConcurrencyTokensFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityConcurrencyTokensFluentAPI>	Entity=ModelBuilder.Entity<CEntityConcurrencyTokensFluentAPI>();

			Entity.ToTable("EntitiesConcurrencyTokensFluentAPI");

			Entity.HasKey(P => P.EntityID);

			// !!! Ziska sa PROPERTY, ktora bude oznacena ako CONCURRENCY TOKEN.
			PropertyBuilder<int>								ConcurrencyTokenProperty=Entity.Property(P => P.EntityValue);

			// !!! PROPERTY sa nastavi ako CONCURRENCY TOKEN.
			ConcurrencyTokenProperty.IsConcurrencyToken(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityMultipleConcurrencyTokensFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityMultipleConcurrencyTokensFluentAPI>	Entity=ModelBuilder.Entity<CEntityMultipleConcurrencyTokensFluentAPI>();

			Entity.ToTable("EntitiesMultipleConcurrencyTokensFluentAPI");

			Entity.HasKey(P => P.EntityID);

			// !!! Ziska sa PROPERTY, ktora bude oznacena ako CONCURRENCY TOKEN.
			PropertyBuilder<int>								ConcurrencyTokenProperty1=Entity.Property(P => P.EntityValue1);

			// !!! PROPERTY sa nastavi ako CONCURRENCY TOKEN.
			ConcurrencyTokenProperty1.IsConcurrencyToken(true);

			// !!! Ziska sa PROPERTY, ktora bude oznacena ako CONCURRENCY TOKEN.
			PropertyBuilder<int>								ConcurrencyTokenProperty2=Entity.Property(P => P.EntityValue2);

			// !!! PROPERTY sa nastavi ako CONCURRENCY TOKEN.
			ConcurrencyTokenProperty2.IsConcurrencyToken(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureUserDefinedFunctions(ModelBuilder ModelBuilder)
		{
			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => DbContextNonStaticUserDefinedFunctionAddValueFluentAPI(default,default));

			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI(default,default));

			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI(default,default));
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
			ConfigureEntityUsingUDF(ModelBuilder);
			ConfigureEntityComputedColumns(ModelBuilder);
			ConfigureEntityDefaultValueColumns(ModelBuilder);
			ConfigureEntityDBGeneratedPropertiesDataAnnotations(ModelBuilder);
			ConfigureEntityDBGeneratedPropertiesFluentAPI(ModelBuilder);
			ConfigureEntityOptimisticConcurrency(ModelBuilder);
			ConfigureEntityConcurrencyTokensDataAnnotations(ModelBuilder);
			ConfigureEntityConcurrencyTokensFluentAPI(ModelBuilder);
			ConfigureEntityMultipleConcurrencyTokensFluentAPI(ModelBuilder);

			ConfigureUserDefinedFunctions(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[DbFunction]
		public static int DbContextStaticUserDefinedFunctionAddValueDataAnnotations(int Value1, int Value2)
		{
			// !!!!! FUNCTION BODY sa NIKDY NEVOLA.

			return(0);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static int DbContextStaticUserDefinedFunctionAddValueFluentAPI(int Value1, int Value2)
		{
			// !!!!! FUNCTION BODY sa NIKDY NEVOLA.

			return(0);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[DbFunction]
		public int DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations(int Value1, int Value2)
		{
			// !!!!! FUNCTION BODY sa NIKDY NEVOLA.

			return(0);
		}
//----------------------------------------------------------------------------------------------------------------------
		public int DbContextNonStaticUserDefinedFunctionAddValueFluentAPI(int Value1, int Value2)
		{
			// !!!!! FUNCTION BODY sa NIKDY NEVOLA.

			return(0);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------