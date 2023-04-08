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
namespace AdvancedFeaturesAndConcurrencySqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQL_SERVER=@"Data Source=(LocalDb)\MSSQLLocalDB;Initial Catalog=AdvancedFeaturesAndConcurrency";
//----------------------------------------------------------------------------------------------------------------------
		public const string										TABLE_NAME_USING_UDF="EntitiesUsingUDF";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityUsingUDF>							MEntitiesUsingUDF;
		private DbSet<CEntityTableValuedFunctionResult>			MEntitiesTableValuedFunctionResult;
		private DbSet<CEntityUsingSequence>						MEntitiesUsingSequence;
		private DbSet<CEntityTimestampsDataAnnotations>			MEntitiesTimestampsDataAnnotations;
		private DbSet<CEntityTimestampsFluentAPI>				MEntitiesTimestampsFluentAPI;
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
		public DbSet<CEntityTableValuedFunctionResult>			EntitiesTableValuedFunctionResult
		{
			get
			{
				return(MEntitiesTableValuedFunctionResult);
			}
			set
			{
				MEntitiesTableValuedFunctionResult=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityUsingSequence>						EntitiesUsingSequence
		{
			get
			{
				return(MEntitiesUsingSequence);
			}
			set
			{
				MEntitiesUsingSequence=value;
			}
		}
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
		private void ConfigureEntityTableValuedFunctionResult(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTableValuedFunctionResult>	Entity=ModelBuilder.Entity<CEntityTableValuedFunctionResult>();

			// !!!!! ENTITY, ktora reprezentuje RESULT SET TABLE VALUED FUNCTION NEMUSI mat KEY.
			Entity.HasNoKey();
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! CODE funguje IBA pre SQL SERVER.
		private void ConfigureSequenceValueEntity(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityUsingSequence>				Entity=ModelBuilder.Entity<CEntityUsingSequence>();

			Entity.ToTable("EntitiesUsingSequence");
				
			Entity.HasKey(P => P.ID);

			// !!!!! V SCHEMA sa vytvori SEQUENCE.
			SequenceBuilder										Sequence=ModelBuilder.HasSequence("MySequence","TestSchema");

			// !!! Urci sa pociatocna VALUE SEQUENCE.
			Sequence.StartsAt(1000);

			// !!! Urci sa INCREMENT VALUE SEQUENCE.
			Sequence.IncrementsBy(4);

			// !!! Ziska sa REFERENCE na SEQUENCE.
			PropertyBuilder<int>								SequenceProperty=Entity.Property(P => P.SequenceValue);

			// !!! Nastavi sa DEFAULT VALUE, ktora pouziva SYNTAX SQL SERVER, ktora ziska novu VALUE danej SEQUENCE.
			SequenceProperty.HasDefaultValueSql("NEXT VALUE FOR TestSchema.MySequence");
		}
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
		private void ConfigureUserDefinedFunctions(ModelBuilder ModelBuilder)
		{
			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => DbContextNonStaticUserDefinedFunctionAddValueFluentAPI(default,default));

			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI(default,default));

			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI(default,default));

			// !!! DEFINUJE sa USER DEFINED FUNCTION.
			ModelBuilder.HasDbFunction(() => DbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI(default));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

			OptionsBuilder.UseLoggerFactory(MLoggerFactory).EnableSensitiveDataLogging();
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityTest(ModelBuilder);
			ConfigureEntityUsingUDF(ModelBuilder);
			ConfigureEntityTableValuedFunctionResult(ModelBuilder);
			ConfigureSequenceValueEntity(ModelBuilder);
			ConfigureEntityTimestampsDataAnnotations(ModelBuilder);
			ConfigureEntityTimestampsFluentAPI(ModelBuilder);

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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! TABLE VALUED FUNCTION MUSI vracat INTERFACE [IQueryable<TType>].
		[DbFunction]
		public IQueryable<CEntityTableValuedFunctionResult> DbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations(int Value)
		{
			IQueryable<CEntityTableValuedFunctionResult>		ResultSet=FromExpression(() => DbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations(Value));

			return(ResultSet);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! TABLE VALUED FUNCTION MUSI vracat INTERFACE [IQueryable<TType>].
		public IQueryable<CEntityTableValuedFunctionResult> DbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI(int Value)
		{
			IQueryable<CEntityTableValuedFunctionResult>		ResultSet=FromExpression(() => DbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI(Value));

			return(ResultSet);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------