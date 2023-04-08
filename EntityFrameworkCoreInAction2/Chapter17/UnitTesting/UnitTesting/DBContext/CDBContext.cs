using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Microsoft.EntityFrameworkCore.Diagnostics;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Console;
using Microsoft.Extensions.Options;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UnitTesting
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! DB CONTEXT nie je SEALED, aby mohol byt OVERRIDEN.
	public class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ELoggingType							MLoggingType;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityPrincipal>							MEntitiesPrincipal;
		private DbSet<CEntityDependent>							MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
			MLoggingType=ELoggingType.E_NO_LOGGING;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(ELoggingType LoggingType)
		{
			MLoggingType=LoggingType;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(DbContextOptions Options)
			: base(Options)
		{
			MLoggingType=ELoggingType.E_NO_LOGGING;
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private bool MyLogFilter(EventId ID, LogLevel Level)
		{
			return(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void MyLogWriter(EventData Data)
		{
			string												Message=Data.ToString();

			CConsoleHelpers.WriteLine($"ID [{Data.EventId}] MESSAGE [{Message}].",ConsoleColor.DarkYellow);
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
			EntityTypeBuilder<CEntityPrincipal>					Entity=ModelBuilder.Entity<CEntityPrincipal>();

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
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDependent>					Entity=ModelBuilder.Entity<CEntityDependent>();

			Entity.ToTable("EntitiesDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			// !!! Ak sa volal CONSTRUCTOR s PARAMETER [DbContextOptions], tak DB CONTEXT OPTIONS uz su CONFIGURED.
			if (OptionsBuilder.IsConfigured==false)
			{
				OptionsBuilder.UseSqlite(MConnectionString_SQLITE).ConfigureWarnings(P => P.Default(WarningBehavior.Log));
			}
			else
			{
				CConsoleHelpers.WriteLine("DB CONTEXT OPTIONS are already CONFIGURED !",ConsoleColor.Green);
			}

			if (MLoggingType==ELoggingType.E_USE_LOGGER_FACTORY)
			{
				// !!! Do LOGS sa budu ukladat potencialne SENSITIVE LOG INFORMATION.
				OptionsBuilder.EnableSensitiveDataLogging();

				// !!! LOG budu DETAILNEJSIE.
				OptionsBuilder.EnableDetailedErrors();

				// !!!!! Vytvori sa instancia CLASS [LoggerFactory].

				OptionsFactory<ConsoleLoggerOptions>			OptionsFactory=new OptionsFactory<ConsoleLoggerOptions>(new ConfigureOptions<ConsoleLoggerOptions>[0],new IPostConfigureOptions<ConsoleLoggerOptions>[0]);
				OptionsMonitor<ConsoleLoggerOptions>			OptionsMonitor=new OptionsMonitor<ConsoleLoggerOptions>(OptionsFactory,new IOptionsChangeTokenSource<ConsoleLoggerOptions>[0],new OptionsCache<ConsoleLoggerOptions>());
				ConsoleLoggerProvider							LoggerProvider=new ConsoleLoggerProvider(OptionsMonitor);
				ILoggerProvider[]								LoggerProviders=new ILoggerProvider[]{LoggerProvider};
				LoggerFilterOptions								FilterOptions=new LoggerFilterOptions();

				FilterOptions.MinLevel=LogLevel.Trace;

				// !!!!! Vytvori sa nova LOGGER FACTORY.
				ILoggerFactory									LoggerFactory=new LoggerFactory(LoggerProviders,FilterOptions);

				// !!! Existujuca LOGGER FACTORY sa nahradi za novu.
				OptionsBuilder.UseLoggerFactory(LoggerFactory);
			}
			else if (MLoggingType==ELoggingType.E_USE_TO_LOG_METHOD)
			{
				// !!! Do LOGS sa budu ukladat potencialne SENSITIVE LOG INFORMATION.
				OptionsBuilder.EnableSensitiveDataLogging();

				// !!! LOG budu DETAILNEJSIE.
				OptionsBuilder.EnableDetailedErrors();

				// !!!!! Povoli sa LOGGING cez CUSTOM METHOD.
				OptionsBuilder.LogTo(MyLogFilter,MyLogWriter);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityTest(ModelBuilder);
			ConfigureEntityPrincipal(ModelBuilder);
			ConfigureEntityDependent(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------