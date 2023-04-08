using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Console;
using Microsoft.Extensions.Options;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		private const string									TABLE_SPLITTING_TABLE_NAME="EntitiesTableSplittingFluentAPI";
		private const string									TABLE_SPLITTING_COLUMN_NAME="My_SHARED_COLUMN";
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILoggerFactory							MLoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityOneToOnePrincipalConventions>		MEntitiesOneToOnePrincipalConventions;
		private DbSet<CEntityOneToOneDependentConventions>		MEntitiesOneToOneDependentConventions;
		private DbSet<CEntityZeroToOnePrincipalConventions>		MEntitiesZeroToOnePrincipalConventions;
		private DbSet<CEntityZeroToOneDependentConventions>		MEntitiesZeroToOneDependentConventions;
		private DbSet<CEntityOneToManyPrincipalConventions>		MEntitiesOneToManyPrincipalConventions;
		private DbSet<CEntityOneToManyDependentConventions>		MEntitiesOneToManyDependentConventions;
		private DbSet<CEntityZeroToManyPrincipalConventions>	MEntitiesZeroToManyPrincipalConventions;
		private DbSet<CEntityZeroToManyDependentConventions>	MEntitiesZeroToManyDependentConventions;
		private DbSet<CEntityForeignKeyName1PrincipalConventions>	MEntitiesForeignKeyName1PrincipalConventions;
		private DbSet<CEntityForeignKeyName1DependentConventions>	MEntitiesForeignKeyName1DependentConventions;
		private DbSet<CEntityForeignKeyName2PrincipalConventions>	MEntitiesForeignKeyName2PrincipalConventions;
		private DbSet<CEntityForeignKeyName2DependentConventions>	MEntitiesForeignKeyName2DependentConventions;
		private DbSet<CEntityForeignKeyName3PrincipalConventions>	MEntitiesForeignKeyName3PrincipalConventions;
		private DbSet<CEntityForeignKeyName3DependentConventions>	MEntitiesForeignKeyName3DependentConventions;
		private DbSet<CEntityNoForeignKey1PrincipalConventions>	MEntitiesNoForeignKey1PrincipalConventions;
		private DbSet<CEntityNoForeignKey1DependentConventions>	MEntitiesNoForeignKey1DependentConventions;
		private DbSet<CEntityNoForeignKey2PrincipalConventions>	MEntitiesNoForeignKey2PrincipalConventions;
		private DbSet<CEntityNoForeignKey2DependentConventions>	MEntitiesNoForeignKey2DependentConventions;
		private DbSet<CEntityNoForeignKey3PrincipalConventions>	MEntitiesNoForeignKey3PrincipalConventions;
		private DbSet<CEntityNoForeignKey3DependentConventions>	MEntitiesNoForeignKey3DependentConventions;
		private DbSet<CEntityOneToOnePrincipalDataAnnotations>	MEntitiesOneToOnePrincipalDataAnnotations;
		private DbSet<CEntityOneToOneDependentDataAnnotations>	MEntitiesOneToOneDependentDataAnnotations;
		private DbSet<CEntityZeroToOnePrincipalDataAnnotations>	MEntitiesZeroToOnePrincipalDataAnnotations;
		private DbSet<CEntityZeroToOneDependentDataAnnotations>	MEntitiesZeroToOneDependentDataAnnotations;
		private DbSet<CEntityOneToManyPrincipalDataAnnotations>	MEntitiesOneToManyPrincipalDataAnnotations;
		private DbSet<CEntityOneToManyDependentDataAnnotations>	MEntitiesOneToManyDependentDataAnnotations;
		private DbSet<CEntityZeroToManyPrincipalDataAnnotations>	MEntitiesZeroToManyPrincipalDataAnnotations;
		private DbSet<CEntityZeroToManyDependentDataAnnotations>	MEntitiesZeroToManyDependentDataAnnotations;
		private DbSet<CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations>	MEntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations;
		private DbSet<CEntityAttributeOnNavigationPropertyDependentDataAnnotations>	MEntitiesAttributeOnNavigationPropertyDependentDataAnnotations;
		private DbSet<CEntityAttributeOnForeignKeyPrincipalDataAnnotations>	MEntitiesAttributeOnForeignKeyPrincipalDataAnnotations;
		private DbSet<CEntityAttributeOnForeignKeyDependentDataAnnotations>	MEntitiesAttributeOnForeignKeyDependentDataAnnotations;
		private DbSet<CEntityCompositeForeignKeyPrincipalDataAnnotations>	MEntitiesCompositeForeignKeyPrincipalDataAnnotations;
		private DbSet<CEntityCompositeForeignKeyDependentDataAnnotations>	MEntitiesCompositeForeignKeyDependentDataAnnotations;
		private DbSet<CEntityInversePropertyPrincipalDataAnnotations>	MEntitiesInversePropertyPrincipalDataAnnotations;
		private DbSet<CEntityInversePropertyDependentDataAnnotations>	MEntitiesInversePropertyDependentDataAnnotations;
		private DbSet<CEntityOneToOne1PrincipalFluentAPI>		MEntitiesOneToOne1PrincipalFluentAPI;
		private DbSet<CEntityOneToOne1DependentFluentAPI>		MEntitiesOneToOne1DependentFluentAPI;
		private DbSet<CEntityOneToOne2PrincipalFluentAPI>		MEntitiesOneToOne2PrincipalFluentAPI;
		private DbSet<CEntityOneToOne2DependentFluentAPI>		MEntitiesOneToOne2DependentFluentAPI;
		private DbSet<CEntityZeroToOne1PrincipalFluentAPI>		MEntitiesZeroToOne1PrincipalFluentAPI;
		private DbSet<CEntityZeroToOne1DependentFluentAPI>		MEntitiesZeroToOne1DependentFluentAPI;
		private DbSet<CEntityZeroToOne2PrincipalFluentAPI>		MEntitiesZeroToOne2PrincipalFluentAPI;
		private DbSet<CEntityZeroToOne2DependentFluentAPI>		MEntitiesZeroToOne2DependentFluentAPI;
		private DbSet<CEntityOneToOneMixedKeys1PrincipalFluentAPI>	MEntitiesOneToOneMixedKeys1PrincipalFluentAPI;
		private DbSet<CEntityOneToOneMixedKeys1DependentFluentAPI>	MEntitiesOneToOneMixedKeys1DependentFluentAPI;
		private DbSet<CEntityOneToOneMixedKeys2PrincipalFluentAPI>	MEntitiesOneToOneMixedKeys2PrincipalFluentAPI;
		private DbSet<CEntityOneToOneMixedKeys2DependentFluentAPI>	MEntitiesOneToOneMixedKeys2DependentFluentAPI;
		private DbSet<CEntityOneToMany1PrincipalFluentAPI>		MEntitiesOneToMany1PrincipalFluentAPI;
		private DbSet<CEntityOneToMany1DependentFluentAPI>		MEntitiesOneToMany1DependentFluentAPI;
		private DbSet<CEntityOneToMany2PrincipalFluentAPI>		MEntitiesOneToMany2PrincipalFluentAPI;
		private DbSet<CEntityOneToMany2DependentFluentAPI>		MEntitiesOneToMany2DependentFluentAPI;
		private DbSet<CEntityZeroToMany1PrincipalFluentAPI>		MEntitiesZeroToMany1PrincipalFluentAPI;
		private DbSet<CEntityZeroToMany1DependentFluentAPI>		MEntitiesZeroToMany1DependentFluentAPI;
		private DbSet<CEntityZeroToMany2PrincipalFluentAPI>		MEntitiesZeroToMany2PrincipalFluentAPI;
		private DbSet<CEntityZeroToMany2DependentFluentAPI>		MEntitiesZeroToMany2DependentFluentAPI;
		private DbSet<CEntityManyToMany1MFluentAPI>				MEntitiesManyToMany1MFluentAPI;
		private DbSet<CEntityManyToMany1NFluentAPI>				MEntitiesManyToMany1NFluentAPI;
		private DbSet<CEntityManyToMany1MNFluentAPI>			MEntitiesManyToMany1MNFluentAPI;
		private DbSet<CEntityManyToMany2MFluentAPI>				MEntitiesManyToMany2MFluentAPI;
		private DbSet<CEntityManyToMany2NFluentAPI>				MEntitiesManyToMany2NFluentAPI;
		private DbSet<CEntityManyToMany2MNFluentAPI>			MEntitiesManyToMany2MNFluentAPI;
		private DbSet<CEntityZeroManyToMany1MFluentAPI>			MEntitiesZeroManyToMany1MFluentAPI;
		private DbSet<CEntityZeroManyToMany1NFluentAPI>			MEntitiesZeroManyToMany1NFluentAPI;
		private DbSet<CEntityZeroManyToMany1MNFluentAPI>		MEntitiesZeroManyToMany1MNFluentAPI;
		private DbSet<CEntityZeroManyToMany2MFluentAPI>			MEntitiesZeroManyToMany2MFluentAPI;
		private DbSet<CEntityZeroManyToMany2NFluentAPI>			MEntitiesZeroManyToMany2NFluentAPI;
		private DbSet<CEntityZeroManyToMany2MNFluentAPI>		MEntitiesZeroManyToMany2MNFluentAPI;
		private DbSet<CEntityManyToManyMixedKeys1MFluentAPI>	MEntitiesManyToManyMixedKeys1MFluentAPI;
		private DbSet<CEntityManyToManyMixedKeys1NFluentAPI>	MEntitiesManyToManyMixedKeys1NFluentAPI;
		private DbSet<CEntityManyToManyMixedKeys1MNFluentAPI>	MEntitiesManyToManyMixedKeys1MNFluentAPI;
		private DbSet<CEntityManyToManyMixedKeys2MFluentAPI>	MEntitiesManyToManyMixedKeys2MFluentAPI;
		private DbSet<CEntityManyToManyMixedKeys2NFluentAPI>	MEntitiesManyToManyMixedKeys2NFluentAPI;
		private DbSet<CEntityManyToManyMixedKeys2MNFluentAPI>	MEntitiesManyToManyMixedKeys2MNFluentAPI;
		private DbSet<CEntityAutoManyToMany1MFluentAPI>			MEntitiesAutoManyToMany1MFluentAPI;
		private DbSet<CEntityAutoManyToMany1NFluentAPI>			MEntitiesAutoManyToMany1NFluentAPI;
		private DbSet<CEntityAutoManyToMany1MNFluentAPI>		MEntitiesAutoManyToMany1MNFluentAPI;
		private DbSet<CEntityAutoManyToMany2MFluentAPI>			MEntitiesAutoManyToMany2MFluentAPI;
		private DbSet<CEntityAutoManyToMany2NFluentAPI>			MEntitiesAutoManyToMany2NFluentAPI;
		private DbSet<CEntityAutoManyToMany2MNFluentAPI>		MEntitiesAutoManyToMany2MNFluentAPI;
		private DbSet<CEntityAutoZeroManyToMany1MFluentAPI>		MEntitiesAutoZeroManyToMany1MFluentAPI;
		private DbSet<CEntityAutoZeroManyToMany1NFluentAPI>		MEntitiesAutoZeroManyToMany1NFluentAPI;
		private DbSet<CEntityAutoZeroManyToMany1MNFluentAPI>	MEntitiesAutoZeroManyToMany1MNFluentAPI;
		private DbSet<CEntityAutoZeroManyToMany2MFluentAPI>		MEntitiesAutoZeroManyToMany2MFluentAPI;
		private DbSet<CEntityAutoZeroManyToMany2NFluentAPI>		MEntitiesAutoZeroManyToMany2NFluentAPI;
		private DbSet<CEntityAutoZeroManyToMany2MNFluentAPI>	MEntitiesAutoZeroManyToMany2MNFluentAPI;
		private DbSet<CEntityAutoManyToManyMixedKeys1MFluentAPI>	MEntitiesAutoManyToManyMixedKeys1MFluentAPI;
		private DbSet<CEntityAutoManyToManyMixedKeys1NFluentAPI>	MEntitiesAutoManyToManyMixedKeys1NFluentAPI;
		private DbSet<CEntityAutoManyToManyMixedKeys1MNFluentAPI>	MEntitiesAutoManyToManyMixedKeys1MNFluentAPI;
		private DbSet<CEntityAutoManyToManyMixedKeys2MFluentAPI>	MEntitiesAutoManyToManyMixedKeys2MFluentAPI;
		private DbSet<CEntityAutoManyToManyMixedKeys2NFluentAPI>	MEntitiesAutoManyToManyMixedKeys2NFluentAPI;
		private DbSet<CEntityAutoManyToManyMixedKeys2MNFluentAPI>	MEntitiesAutoManyToManyMixedKeys2MNFluentAPI;
		private DbSet<CEntityOnDeleteNoActionNotNullPrincipalFluentAPI>	MEntitiesOnDeleteNoActionNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteNoActionNotNullDependentFluentAPI>	MEntitiesOnDeleteNoActionNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteNoActionNullPrincipalFluentAPI>	MEntitiesOnDeleteNoActionNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteNoActionNullDependentFluentAPI>	MEntitiesOnDeleteNoActionNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI>	MEntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteClientNoActionNotNullDependentFluentAPI>	MEntitiesOnDeleteClientNoActionNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteClientNoActionNullPrincipalFluentAPI>	MEntitiesOnDeleteClientNoActionNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteClientNoActionNullDependentFluentAPI>	MEntitiesOnDeleteClientNoActionNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteRestrictNotNullPrincipalFluentAPI>	MEntitiesOnDeleteRestrictNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteRestrictNotNullDependentFluentAPI>	MEntitiesOnDeleteRestrictNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteRestrictNullPrincipalFluentAPI>	MEntitiesOnDeleteRestrictNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteRestrictNullDependentFluentAPI>	MEntitiesOnDeleteRestrictNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteSetNullNotNullPrincipalFluentAPI>	MEntitiesOnDeleteSetNullNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteSetNullNotNullDependentFluentAPI>	MEntitiesOnDeleteSetNullNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteSetNullNullPrincipalFluentAPI>	MEntitiesOnDeleteSetNullNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteSetNullNullDependentFluentAPI>	MEntitiesOnDeleteSetNullNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI>	MEntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteClientSetNullNotNullDependentFluentAPI>	MEntitiesOnDeleteClientSetNullNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteClientSetNullNullPrincipalFluentAPI>	MEntitiesOnDeleteClientSetNullNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteClientSetNullNullDependentFluentAPI>	MEntitiesOnDeleteClientSetNullNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteCascadeNotNullPrincipalFluentAPI>	MEntitiesOnDeleteCascadeNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteCascadeNotNullDependentFluentAPI>	MEntitiesOnDeleteCascadeNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteCascadeNullPrincipalFluentAPI>	MEntitiesOnDeleteCascadeNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteCascadeNullDependentFluentAPI>	MEntitiesOnDeleteCascadeNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI>	MEntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteClientCascadeNotNullDependentFluentAPI>	MEntitiesOnDeleteClientCascadeNotNullDependentFluentAPI;
		private DbSet<CEntityOnDeleteClientCascadeNullPrincipalFluentAPI>	MEntitiesOnDeleteClientCascadeNullPrincipalFluentAPI;
		private DbSet<CEntityOnDeleteClientCascadeNullDependentFluentAPI>	MEntitiesOnDeleteClientCascadeNullDependentFluentAPI;
		private DbSet<CEntityRequiredTruePrincipalFluentAPI>	MEntitiesRequiredTruePrincipalFluentAPI;
		private DbSet<CEntityRequiredTrueDependentFluentAPI>	MEntitiesRequiredTrueDependentFluentAPI;
		private DbSet<CEntityRequiredFalsePrincipalFluentAPI>	MEntitiesRequiredFalsePrincipalFluentAPI;
		private DbSet<CEntityRequiredFalseDependentFluentAPI>	MEntitiesRequiredFalseDependentFluentAPI;
		private DbSet<CEntityHasAlternateKeyFluentAPI>			MEntitiesHasAlternateKeyFluentAPI;
		private DbSet<CEntityHasAlternateKeyCompositeFluentAPI>	MEntitiesHasAlternateKeyCompositeFluentAPI;
		private DbSet<CEntityHasPrincipalKeyPrincipalFluentAPI>	MEntitiesHasPrincipalKeyPrincipalFluentAPI;
		private DbSet<CEntityHasPrincipalKeyDependentFluentAPI>	MEntitiesHasPrincipalKeyDependentFluentAPI;
		private DbSet<CEntityHasPrincipalKeyCompositePrincipalFluentAPI>	MEntitiesHasPrincipalKeyCompositePrincipalFluentAPI;
		private DbSet<CEntityHasPrincipalKeyCompositeDependentFluentAPI>	MEntitiesHasPrincipalKeyCompositeDependentFluentAPI;
		private DbSet<CEntityHasConstraintNamePrincipalFluentAPI>	MEntitiesHasConstraintNamePrincipalFluentAPI;
		private DbSet<CEntityHasConstraintNameDependentFluentAPI>	MEntitiesHasConstraintNameDependentFluentAPI;
		private DbSet<CEntityOwnedTypeInOneTable>				MEntitiesOwnedTypeInOneTable;
		private DbSet<CEntityOwnedTypeInMultiTables>			MEntitiesOwnedTypeInMultiTables;
		private DbSet<CEntityOwnedTypeOneAndMany>				MEntitiesOwnedTypeOneAndMany;
		private DbSet<CEntityTablePerHierarchyBaseConventions>	MEntitiesTablePerHierarchyBaseConventions;
		private DbSet<CEntityTablePerHierarchyDerived1Conventions>	MEntitiesTablePerHierarchyDerived1Conventions;
		private DbSet<CEntityTablePerHierarchyDerived2Conventions>	MEntitiesTablePerHierarchyDerived2Conventions;
		private DbSet<CEntityTablePerHierarchyBaseFluentAPI>	MEntitiesTablePerHierarchyBaseFluentAPI;
		private DbSet<CEntityTablePerHierarchyDerived1FluentAPI>	MEntitiesTablePerHierarchyDerived1FluentAPI;
		private DbSet<CEntityTablePerHierarchyDerived2FluentAPI>	MEntitiesTablePerHierarchyDerived2FluentAPI;
		private DbSet<CEntityTablePerTypeBaseFluentAPI>			MEntitiesTablePerTypeBaseFluentAPI;
		private DbSet<CEntityTableSplittingPrincipalFluentAPI>	MEntitiesTableSplittingPrincipalFluentAPI;
		private DbSet<CEntityTableSplittingDependent1FluentAPI>	MEntitiesTableSplittingDependent1FluentAPI;
		private DbSet<CEntityTableSplittingDependent2FluentAPI>	MEntitiesTableSplittingDependent2FluentAPI;
		private DbSet<Dictionary<string,object>>				MMyPropertyBagPrincipal;
		private DbSet<CEntityPropertyBagDependentFluentAPI>		MEntitiesPropertyBagDependentFluentAPI;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
			MMyPropertyBagPrincipal=Set<Dictionary<string,object>>(CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_TABLE_NAME);
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
		public DbSet<CEntityOneToOnePrincipalConventions>		EntitiesOneToOnePrincipalConventions
		{
			get
			{
				return(MEntitiesOneToOnePrincipalConventions);
			}
			set
			{
				MEntitiesOneToOnePrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependentConventions>		EntitiesOneToOneDependentConventions
		{
			get
			{
				return(MEntitiesOneToOneDependentConventions);
			}
			set
			{
				MEntitiesOneToOneDependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOnePrincipalConventions>		EntitiesZeroToOnePrincipalConventions
		{
			get
			{
				return(MEntitiesZeroToOnePrincipalConventions);
			}
			set
			{
				MEntitiesZeroToOnePrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOneDependentConventions>		EntitiesZeroToOneDependentConventions
		{
			get
			{
				return(MEntitiesZeroToOneDependentConventions);
			}
			set
			{
				MEntitiesZeroToOneDependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyPrincipalConventions>		EntitiesOneToManyPrincipalConventions
		{
			get
			{
				return(MEntitiesOneToManyPrincipalConventions);
			}
			set
			{
				MEntitiesOneToManyPrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyDependentConventions>		EntitiesOneToManyDependentConventions
		{
			get
			{
				return(MEntitiesOneToManyDependentConventions);
			}
			set
			{
				MEntitiesOneToManyDependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToManyPrincipalConventions>		EntitiesZeroToManyPrincipalConventions
		{
			get
			{
				return(MEntitiesZeroToManyPrincipalConventions);
			}
			set
			{
				MEntitiesZeroToManyPrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToManyDependentConventions>		EntitiesZeroToManyDependentConventions
		{
			get
			{
				return(MEntitiesZeroToManyDependentConventions);
			}
			set
			{
				MEntitiesZeroToManyDependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityForeignKeyName1PrincipalConventions>	EntitiesForeignKeyName1PrincipalConventions
		{
			get
			{
				return(MEntitiesForeignKeyName1PrincipalConventions);
			}
			set
			{
				MEntitiesForeignKeyName1PrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityForeignKeyName1DependentConventions>	EntitiesForeignKeyName1DependentConventions
		{
			get
			{
				return(MEntitiesForeignKeyName1DependentConventions);
			}
			set
			{
				MEntitiesForeignKeyName1DependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityForeignKeyName2PrincipalConventions>	EntitiesForeignKeyName2PrincipalConventions
		{
			get
			{
				return(MEntitiesForeignKeyName2PrincipalConventions);
			}
			set
			{
				MEntitiesForeignKeyName2PrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityForeignKeyName2DependentConventions>	EntitiesForeignKeyName2DependentConventions
		{
			get
			{
				return(MEntitiesForeignKeyName2DependentConventions);
			}
			set
			{
				MEntitiesForeignKeyName2DependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityForeignKeyName3PrincipalConventions>	EntitiesForeignKeyName3PrincipalConventions
		{
			get
			{
				return(MEntitiesForeignKeyName3PrincipalConventions);
			}
			set
			{
				MEntitiesForeignKeyName3PrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityForeignKeyName3DependentConventions>	EntitiesForeignKeyName3DependentConventions
		{
			get
			{
				return(MEntitiesForeignKeyName3DependentConventions);
			}
			set
			{
				MEntitiesForeignKeyName3DependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNoForeignKey1PrincipalConventions>	EntitiesNoForeignKey1PrincipalConventions
		{
			get
			{
				return(MEntitiesNoForeignKey1PrincipalConventions);
			}
			set
			{
				MEntitiesNoForeignKey1PrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNoForeignKey1DependentConventions>	EntitiesNoForeignKey1DependentConventions
		{
			get
			{
				return(MEntitiesNoForeignKey1DependentConventions);
			}
			set
			{
				MEntitiesNoForeignKey1DependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNoForeignKey2PrincipalConventions>	EntitiesNoForeignKey2PrincipalConventions
		{
			get
			{
				return(MEntitiesNoForeignKey2PrincipalConventions);
			}
			set
			{
				MEntitiesNoForeignKey2PrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNoForeignKey2DependentConventions>	EntitiesNoForeignKey2DependentConventions
		{
			get
			{
				return(MEntitiesNoForeignKey2DependentConventions);
			}
			set
			{
				MEntitiesNoForeignKey2DependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNoForeignKey3PrincipalConventions>	EntitiesNoForeignKey3PrincipalConventions
		{
			get
			{
				return(MEntitiesNoForeignKey3PrincipalConventions);
			}
			set
			{
				MEntitiesNoForeignKey3PrincipalConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNoForeignKey3DependentConventions>	EntitiesNoForeignKey3DependentConventions
		{
			get
			{
				return(MEntitiesNoForeignKey3DependentConventions);
			}
			set
			{
				MEntitiesNoForeignKey3DependentConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOnePrincipalDataAnnotations>	EntitiesOneToOnePrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesOneToOnePrincipalDataAnnotations);
			}
			set
			{
				MEntitiesOneToOnePrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependentDataAnnotations>	EntitiesOneToOneDependentDataAnnotations
		{
			get
			{
				return(MEntitiesOneToOneDependentDataAnnotations);
			}
			set
			{
				MEntitiesOneToOneDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOnePrincipalDataAnnotations>	EntitiesZeroToOnePrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesZeroToOnePrincipalDataAnnotations);
			}
			set
			{
				MEntitiesZeroToOnePrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOneDependentDataAnnotations>	EntitiesZeroToOneDependentDataAnnotations
		{
			get
			{
				return(MEntitiesZeroToOneDependentDataAnnotations);
			}
			set
			{
				MEntitiesZeroToOneDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyPrincipalDataAnnotations>	EntitiesOneToManyPrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesOneToManyPrincipalDataAnnotations);
			}
			set
			{
				MEntitiesOneToManyPrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyDependentDataAnnotations>	EntitiesOneToManyDependentDataAnnotations
		{
			get
			{
				return(MEntitiesOneToManyDependentDataAnnotations);
			}
			set
			{
				MEntitiesOneToManyDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToManyPrincipalDataAnnotations>	EntitiesZeroToManyPrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesZeroToManyPrincipalDataAnnotations);
			}
			set
			{
				MEntitiesZeroToManyPrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToManyDependentDataAnnotations>	EntitiesZeroToManyDependentDataAnnotations
		{
			get
			{
				return(MEntitiesZeroToManyDependentDataAnnotations);
			}
			set
			{
				MEntitiesZeroToManyDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations>	EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations);
			}
			set
			{
				MEntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAttributeOnNavigationPropertyDependentDataAnnotations>	EntitiesAttributeOnNavigationPropertyDependentDataAnnotations
		{
			get
			{
				return(MEntitiesAttributeOnNavigationPropertyDependentDataAnnotations);
			}
			set
			{
				MEntitiesAttributeOnNavigationPropertyDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAttributeOnForeignKeyPrincipalDataAnnotations>	EntitiesAttributeOnForeignKeyPrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesAttributeOnForeignKeyPrincipalDataAnnotations);
			}
			set
			{
				MEntitiesAttributeOnForeignKeyPrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAttributeOnForeignKeyDependentDataAnnotations>	EntitiesAttributeOnForeignKeyDependentDataAnnotations
		{
			get
			{
				return(MEntitiesAttributeOnForeignKeyDependentDataAnnotations);
			}
			set
			{
				MEntitiesAttributeOnForeignKeyDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityCompositeForeignKeyPrincipalDataAnnotations>	EntitiesCompositeForeignKeyPrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesCompositeForeignKeyPrincipalDataAnnotations);
			}
			set
			{
				MEntitiesCompositeForeignKeyPrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityCompositeForeignKeyDependentDataAnnotations>	EntitiesCompositeForeignKeyDependentDataAnnotations
		{
			get
			{
				return(MEntitiesCompositeForeignKeyDependentDataAnnotations);
			}
			set
			{
				MEntitiesCompositeForeignKeyDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityInversePropertyPrincipalDataAnnotations>	EntitiesInversePropertyPrincipalDataAnnotations
		{
			get
			{
				return(MEntitiesInversePropertyPrincipalDataAnnotations);
			}
			set
			{
				MEntitiesInversePropertyPrincipalDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityInversePropertyDependentDataAnnotations>	EntitiesInversePropertyDependentDataAnnotations
		{
			get
			{
				return(MEntitiesInversePropertyDependentDataAnnotations);
			}
			set
			{
				MEntitiesInversePropertyDependentDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOne1PrincipalFluentAPI>		EntitiesOneToOne1PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOneToOne1PrincipalFluentAPI);
			}
			set
			{
				MEntitiesOneToOne1PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOne1DependentFluentAPI>		EntitiesOneToOne1DependentFluentAPI
		{
			get
			{
				return(MEntitiesOneToOne1DependentFluentAPI);
			}
			set
			{
				MEntitiesOneToOne1DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOne2PrincipalFluentAPI>		EntitiesOneToOne2PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOneToOne2PrincipalFluentAPI);
			}
			set
			{
				MEntitiesOneToOne2PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOne2DependentFluentAPI>		EntitiesOneToOne2DependentFluentAPI
		{
			get
			{
				return(MEntitiesOneToOne2DependentFluentAPI);
			}
			set
			{
				MEntitiesOneToOne2DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOne1PrincipalFluentAPI>		EntitiesZeroToOne1PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesZeroToOne1PrincipalFluentAPI);
			}
			set
			{
				MEntitiesZeroToOne1PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOne1DependentFluentAPI>		EntitiesZeroToOne1DependentFluentAPI
		{
			get
			{
				return(MEntitiesZeroToOne1DependentFluentAPI);
			}
			set
			{
				MEntitiesZeroToOne1DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOne2PrincipalFluentAPI>		EntitiesZeroToOne2PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesZeroToOne2PrincipalFluentAPI);
			}
			set
			{
				MEntitiesZeroToOne2PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToOne2DependentFluentAPI>		EntitiesZeroToOne2DependentFluentAPI
		{
			get
			{
				return(MEntitiesZeroToOne2DependentFluentAPI);
			}
			set
			{
				MEntitiesZeroToOne2DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneMixedKeys1PrincipalFluentAPI>	EntitiesOneToOneMixedKeys1PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOneToOneMixedKeys1PrincipalFluentAPI);
			}
			set
			{
				MEntitiesOneToOneMixedKeys1PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneMixedKeys1DependentFluentAPI>	EntitiesOneToOneMixedKeys1DependentFluentAPI
		{
			get
			{
				return(MEntitiesOneToOneMixedKeys1DependentFluentAPI);
			}
			set
			{
				MEntitiesOneToOneMixedKeys1DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneMixedKeys2PrincipalFluentAPI>	EntitiesOneToOneMixedKeys2PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOneToOneMixedKeys2PrincipalFluentAPI);
			}
			set
			{
				MEntitiesOneToOneMixedKeys2PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneMixedKeys2DependentFluentAPI>	EntitiesOneToOneMixedKeys2DependentFluentAPI
		{
			get
			{
				return(MEntitiesOneToOneMixedKeys2DependentFluentAPI);
			}
			set
			{
				MEntitiesOneToOneMixedKeys2DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToMany1PrincipalFluentAPI>		EntitiesOneToMany1PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOneToMany1PrincipalFluentAPI);
			}
			set
			{
				MEntitiesOneToMany1PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToMany1DependentFluentAPI>		EntitiesOneToMany1DependentFluentAPI
		{
			get
			{
				return(MEntitiesOneToMany1DependentFluentAPI);
			}
			set
			{
				MEntitiesOneToMany1DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToMany2PrincipalFluentAPI>		EntitiesOneToMany2PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOneToMany2PrincipalFluentAPI);
			}
			set
			{
				MEntitiesOneToMany2PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToMany2DependentFluentAPI>		EntitiesOneToMany2DependentFluentAPI
		{
			get
			{
				return(MEntitiesOneToMany2DependentFluentAPI);
			}
			set
			{
				MEntitiesOneToMany2DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToMany1PrincipalFluentAPI>		EntitiesZeroToMany1PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesZeroToMany1PrincipalFluentAPI);
			}
			set
			{
				MEntitiesZeroToMany1PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToMany1DependentFluentAPI>		EntitiesZeroToMany1DependentFluentAPI
		{
			get
			{
				return(MEntitiesZeroToMany1DependentFluentAPI);
			}
			set
			{
				MEntitiesZeroToMany1DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToMany2PrincipalFluentAPI>		EntitiesZeroToMany2PrincipalFluentAPI
		{
			get
			{
				return(MEntitiesZeroToMany2PrincipalFluentAPI);
			}
			set
			{
				MEntitiesZeroToMany2PrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroToMany2DependentFluentAPI>		EntitiesZeroToMany2DependentFluentAPI
		{
			get
			{
				return(MEntitiesZeroToMany2DependentFluentAPI);
			}
			set
			{
				MEntitiesZeroToMany2DependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToMany1MFluentAPI>				EntitiesManyToMany1MFluentAPI
		{
			get
			{
				return(MEntitiesManyToMany1MFluentAPI);
			}
			set
			{
				MEntitiesManyToMany1MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToMany1NFluentAPI>				EntitiesManyToMany1NFluentAPI
		{
			get
			{
				return(MEntitiesManyToMany1NFluentAPI);
			}
			set
			{
				MEntitiesManyToMany1NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToMany1MNFluentAPI>				EntitiesManyToMany1MNFluentAPI
		{
			get
			{
				return(MEntitiesManyToMany1MNFluentAPI);
			}
			set
			{
				MEntitiesManyToMany1MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToMany2MFluentAPI>				EntitiesManyToMany2MFluentAPI
		{
			get
			{
				return(MEntitiesManyToMany2MFluentAPI);
			}
			set
			{
				MEntitiesManyToMany2MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToMany2NFluentAPI>				EntitiesManyToMany2NFluentAPI
		{
			get
			{
				return(MEntitiesManyToMany2NFluentAPI);
			}
			set
			{
				MEntitiesManyToMany2NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToMany2MNFluentAPI>				EntitiesManyToMany2MNFluentAPI
		{
			get
			{
				return(MEntitiesManyToMany2MNFluentAPI);
			}
			set
			{
				MEntitiesManyToMany2MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroManyToMany1MFluentAPI>			EntitiesZeroManyToMany1MFluentAPI
		{
			get
			{
				return(MEntitiesZeroManyToMany1MFluentAPI);
			}
			set
			{
				MEntitiesZeroManyToMany1MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroManyToMany1NFluentAPI>			EntitiesZeroManyToMany1NFluentAPI
		{
			get
			{
				return(MEntitiesZeroManyToMany1NFluentAPI);
			}
			set
			{
				MEntitiesZeroManyToMany1NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroManyToMany1MNFluentAPI>			EntitiesZeroManyToMany1MNFluentAPI
		{
			get
			{
				return(MEntitiesZeroManyToMany1MNFluentAPI);
			}
			set
			{
				MEntitiesZeroManyToMany1MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroManyToMany2MFluentAPI>			EntitiesZeroManyToMany2MFluentAPI
		{
			get
			{
				return(MEntitiesZeroManyToMany2MFluentAPI);
			}
			set
			{
				MEntitiesZeroManyToMany2MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroManyToMany2NFluentAPI>			EntitiesZeroManyToMany2NFluentAPI
		{
			get
			{
				return(MEntitiesZeroManyToMany2NFluentAPI);
			}
			set
			{
				MEntitiesZeroManyToMany2NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityZeroManyToMany2MNFluentAPI>			EntitiesZeroManyToMany2MNFluentAPI
		{
			get
			{
				return(MEntitiesZeroManyToMany2MNFluentAPI);
			}
			set
			{
				MEntitiesZeroManyToMany2MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMixedKeys1MFluentAPI>		EntitiesManyToManyMixedKeys1MFluentAPI
		{
			get
			{
				return(MEntitiesManyToManyMixedKeys1MFluentAPI);
			}
			set
			{
				MEntitiesManyToManyMixedKeys1MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMixedKeys1NFluentAPI>		EntitiesManyToManyMixedKeys1NFluentAPI
		{
			get
			{
				return(MEntitiesManyToManyMixedKeys1NFluentAPI);
			}
			set
			{
				MEntitiesManyToManyMixedKeys1NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMixedKeys1MNFluentAPI>	EntitiesManyToManyMixedKeys1MNFluentAPI
		{
			get
			{
				return(MEntitiesManyToManyMixedKeys1MNFluentAPI);
			}
			set
			{
				MEntitiesManyToManyMixedKeys1MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMixedKeys2MFluentAPI>		EntitiesManyToManyMixedKeys2MFluentAPI
		{
			get
			{
				return(MEntitiesManyToManyMixedKeys2MFluentAPI);
			}
			set
			{
				MEntitiesManyToManyMixedKeys2MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMixedKeys2NFluentAPI>		EntitiesManyToManyMixedKeys2NFluentAPI
		{
			get
			{
				return(MEntitiesManyToManyMixedKeys2NFluentAPI);
			}
			set
			{
				MEntitiesManyToManyMixedKeys2NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMixedKeys2MNFluentAPI>	EntitiesManyToManyMixedKeys2MNFluentAPI
		{
			get
			{
				return(MEntitiesManyToManyMixedKeys2MNFluentAPI);
			}
			set
			{
				MEntitiesManyToManyMixedKeys2MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToMany1MFluentAPI>			EntitiesAutoManyToMany1MFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToMany1MFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToMany1MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToMany1NFluentAPI>			EntitiesAutoManyToMany1NFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToMany1NFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToMany1NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToMany1MNFluentAPI>			EntitiesAutoManyToMany1MNFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToMany1MNFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToMany1MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToMany2MFluentAPI>			EntitiesAutoManyToMany2MFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToMany2MFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToMany2MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToMany2NFluentAPI>			EntitiesAutoManyToMany2NFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToMany2NFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToMany2NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToMany2MNFluentAPI>			EntitiesAutoManyToMany2MNFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToMany2MNFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToMany2MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoZeroManyToMany1MFluentAPI>		EntitiesAutoZeroManyToMany1MFluentAPI
		{
			get
			{
				return(MEntitiesAutoZeroManyToMany1MFluentAPI);
			}
			set
			{
				MEntitiesAutoZeroManyToMany1MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoZeroManyToMany1NFluentAPI>		EntitiesAutoZeroManyToMany1NFluentAPI
		{
			get
			{
				return(MEntitiesAutoZeroManyToMany1NFluentAPI);
			}
			set
			{
				MEntitiesAutoZeroManyToMany1NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoZeroManyToMany1MNFluentAPI>		EntitiesAutoZeroManyToMany1MNFluentAPI
		{
			get
			{
				return(MEntitiesAutoZeroManyToMany1MNFluentAPI);
			}
			set
			{
				MEntitiesAutoZeroManyToMany1MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoZeroManyToMany2MFluentAPI>		EntitiesAutoZeroManyToMany2MFluentAPI
		{
			get
			{
				return(MEntitiesAutoZeroManyToMany2MFluentAPI);
			}
			set
			{
				MEntitiesAutoZeroManyToMany2MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoZeroManyToMany2NFluentAPI>		EntitiesAutoZeroManyToMany2NFluentAPI
		{
			get
			{
				return(MEntitiesAutoZeroManyToMany2NFluentAPI);
			}
			set
			{
				MEntitiesAutoZeroManyToMany2NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoZeroManyToMany2MNFluentAPI>		EntitiesAutoZeroManyToMany2MNFluentAPI
		{
			get
			{
				return(MEntitiesAutoZeroManyToMany2MNFluentAPI);
			}
			set
			{
				MEntitiesAutoZeroManyToMany2MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToManyMixedKeys1MFluentAPI>	EntitiesAutoManyToManyMixedKeys1MFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToManyMixedKeys1MFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToManyMixedKeys1MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToManyMixedKeys1NFluentAPI>	EntitiesAutoManyToManyMixedKeys1NFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToManyMixedKeys1NFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToManyMixedKeys1NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToManyMixedKeys1MNFluentAPI>	EntitiesAutoManyToManyMixedKeys1MNFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToManyMixedKeys1MNFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToManyMixedKeys1MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToManyMixedKeys2MFluentAPI>	EntitiesAutoManyToManyMixedKeys2MFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToManyMixedKeys2MFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToManyMixedKeys2MFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToManyMixedKeys2NFluentAPI>	EntitiesAutoManyToManyMixedKeys2NFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToManyMixedKeys2NFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToManyMixedKeys2NFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoManyToManyMixedKeys2MNFluentAPI>	EntitiesAutoManyToManyMixedKeys2MNFluentAPI
		{
			get
			{
				return(MEntitiesAutoManyToManyMixedKeys2MNFluentAPI);
			}
			set
			{
				MEntitiesAutoManyToManyMixedKeys2MNFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteNoActionNotNullPrincipalFluentAPI>	EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteNoActionNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteNoActionNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteNoActionNotNullDependentFluentAPI>	EntitiesOnDeleteNoActionNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteNoActionNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteNoActionNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteNoActionNullPrincipalFluentAPI>	EntitiesOnDeleteNoActionNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteNoActionNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteNoActionNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteNoActionNullDependentFluentAPI>	EntitiesOnDeleteNoActionNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteNoActionNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteNoActionNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI>	EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientNoActionNotNullDependentFluentAPI>	EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientNoActionNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientNoActionNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientNoActionNullPrincipalFluentAPI>	EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientNoActionNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientNoActionNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientNoActionNullDependentFluentAPI>	EntitiesOnDeleteClientNoActionNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientNoActionNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientNoActionNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteRestrictNotNullPrincipalFluentAPI>	EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteRestrictNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteRestrictNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteRestrictNotNullDependentFluentAPI>	EntitiesOnDeleteRestrictNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteRestrictNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteRestrictNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteRestrictNullPrincipalFluentAPI>	EntitiesOnDeleteRestrictNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteRestrictNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteRestrictNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteRestrictNullDependentFluentAPI>	EntitiesOnDeleteRestrictNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteRestrictNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteRestrictNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteSetNullNotNullPrincipalFluentAPI>	EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteSetNullNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteSetNullNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteSetNullNotNullDependentFluentAPI>	EntitiesOnDeleteSetNullNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteSetNullNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteSetNullNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteSetNullNullPrincipalFluentAPI>	EntitiesOnDeleteSetNullNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteSetNullNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteSetNullNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteSetNullNullDependentFluentAPI>	EntitiesOnDeleteSetNullNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteSetNullNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteSetNullNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI>	EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientSetNullNotNullDependentFluentAPI>	EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientSetNullNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientSetNullNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientSetNullNullPrincipalFluentAPI>	EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientSetNullNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientSetNullNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientSetNullNullDependentFluentAPI>	EntitiesOnDeleteClientSetNullNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientSetNullNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientSetNullNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteCascadeNotNullPrincipalFluentAPI>	EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteCascadeNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteCascadeNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteCascadeNotNullDependentFluentAPI>	EntitiesOnDeleteCascadeNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteCascadeNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteCascadeNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteCascadeNullPrincipalFluentAPI>	EntitiesOnDeleteCascadeNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteCascadeNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteCascadeNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteCascadeNullDependentFluentAPI>	EntitiesOnDeleteCascadeNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteCascadeNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteCascadeNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI>	EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientCascadeNotNullDependentFluentAPI>	EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientCascadeNotNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientCascadeNotNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientCascadeNullPrincipalFluentAPI>	EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientCascadeNullPrincipalFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientCascadeNullPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOnDeleteClientCascadeNullDependentFluentAPI>	EntitiesOnDeleteClientCascadeNullDependentFluentAPI
		{
			get
			{
				return(MEntitiesOnDeleteClientCascadeNullDependentFluentAPI);
			}
			set
			{
				MEntitiesOnDeleteClientCascadeNullDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityRequiredTruePrincipalFluentAPI>		EntitiesRequiredTruePrincipalFluentAPI
		{
			get
			{
				return(MEntitiesRequiredTruePrincipalFluentAPI);
			}
			set
			{
				MEntitiesRequiredTruePrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityRequiredTrueDependentFluentAPI>		EntitiesRequiredTrueDependentFluentAPI
		{
			get
			{
				return(MEntitiesRequiredTrueDependentFluentAPI);
			}
			set
			{
				MEntitiesRequiredTrueDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityRequiredFalsePrincipalFluentAPI>	EntitiesRequiredFalsePrincipalFluentAPI
		{
			get
			{
				return(MEntitiesRequiredFalsePrincipalFluentAPI);
			}
			set
			{
				MEntitiesRequiredFalsePrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityRequiredFalseDependentFluentAPI>	EntitiesRequiredFalseDependentFluentAPI
		{
			get
			{
				return(MEntitiesRequiredFalseDependentFluentAPI);
			}
			set
			{
				MEntitiesRequiredFalseDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasAlternateKeyFluentAPI>			EntitiesHasAlternateKeyFluentAPI
		{
			get
			{
				return(MEntitiesHasAlternateKeyFluentAPI);
			}
			set
			{
				MEntitiesHasAlternateKeyFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasAlternateKeyCompositeFluentAPI>	EntitiesHasAlternateKeyCompositeFluentAPI
		{
			get
			{
				return(MEntitiesHasAlternateKeyCompositeFluentAPI);
			}
			set
			{
				MEntitiesHasAlternateKeyCompositeFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasPrincipalKeyPrincipalFluentAPI>	EntitiesHasPrincipalKeyPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesHasPrincipalKeyPrincipalFluentAPI);
			}
			set
			{
				MEntitiesHasPrincipalKeyPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasPrincipalKeyDependentFluentAPI>	EntitiesHasPrincipalKeyDependentFluentAPI
		{
			get
			{
				return(MEntitiesHasPrincipalKeyDependentFluentAPI);
			}
			set
			{
				MEntitiesHasPrincipalKeyDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasPrincipalKeyCompositePrincipalFluentAPI>	EntitiesHasPrincipalKeyCompositePrincipalFluentAPI
		{
			get
			{
				return(MEntitiesHasPrincipalKeyCompositePrincipalFluentAPI);
			}
			set
			{
				MEntitiesHasPrincipalKeyCompositePrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasPrincipalKeyCompositeDependentFluentAPI>	EntitiesHasPrincipalKeyCompositeDependentFluentAPI
		{
			get
			{
				return(MEntitiesHasPrincipalKeyCompositeDependentFluentAPI);
			}
			set
			{
				MEntitiesHasPrincipalKeyCompositeDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasConstraintNamePrincipalFluentAPI>	EntitiesHasConstraintNamePrincipalFluentAPI
		{
			get
			{
				return(MEntitiesHasConstraintNamePrincipalFluentAPI);
			}
			set
			{
				MEntitiesHasConstraintNamePrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityHasConstraintNameDependentFluentAPI>	EntitiesHasConstraintNameDependentFluentAPI
		{
			get
			{
				return(MEntitiesHasConstraintNameDependentFluentAPI);
			}
			set
			{
				MEntitiesHasConstraintNameDependentFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOwnedTypeInOneTable>				EntitiesOwnedTypeInOneTable
		{
			get
			{
				return(MEntitiesOwnedTypeInOneTable);
			}
			set
			{
				MEntitiesOwnedTypeInOneTable=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOwnedTypeInMultiTables>				EntitiesOwnedTypeInMultiTables
		{
			get
			{
				return(MEntitiesOwnedTypeInMultiTables);
			}
			set
			{
				MEntitiesOwnedTypeInMultiTables=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOwnedTypeOneAndMany>				EntitiesOwnedTypeOneAndMany
		{
			get
			{
				return(MEntitiesOwnedTypeOneAndMany);
			}
			set
			{
				MEntitiesOwnedTypeOneAndMany=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerHierarchyBaseConventions>	EntitiesTablePerHierarchyBaseConventions
		{
			get
			{
				return(MEntitiesTablePerHierarchyBaseConventions);
			}
			set
			{
				MEntitiesTablePerHierarchyBaseConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerHierarchyDerived1Conventions>	EntitiesTablePerHierarchyDerived1Conventions
		{
			get
			{
				return(MEntitiesTablePerHierarchyDerived1Conventions);
			}
			set
			{
				MEntitiesTablePerHierarchyDerived1Conventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerHierarchyDerived2Conventions>	EntitiesTablePerHierarchyDerived2Conventions
		{
			get
			{
				return(MEntitiesTablePerHierarchyDerived2Conventions);
			}
			set
			{
				MEntitiesTablePerHierarchyDerived2Conventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerHierarchyBaseFluentAPI>		EntitiesTablePerHierarchyBaseFluentAPI
		{
			get
			{
				return(MEntitiesTablePerHierarchyBaseFluentAPI);
			}
			set
			{
				MEntitiesTablePerHierarchyBaseFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerHierarchyDerived1FluentAPI>	EntitiesTablePerHierarchyDerived1FluentAPI
		{
			get
			{
				return(MEntitiesTablePerHierarchyDerived1FluentAPI);
			}
			set
			{
				MEntitiesTablePerHierarchyDerived1FluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerHierarchyDerived2FluentAPI>	EntitiesTablePerHierarchyDerived2FluentAPI
		{
			get
			{
				return(MEntitiesTablePerHierarchyDerived2FluentAPI);
			}
			set
			{
				MEntitiesTablePerHierarchyDerived2FluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTablePerTypeBaseFluentAPI>			EntitiesTablePerTypeBaseFluentAPI
		{
			get
			{
				return(MEntitiesTablePerTypeBaseFluentAPI);
			}
			set
			{
				MEntitiesTablePerTypeBaseFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTableSplittingPrincipalFluentAPI>	EntitiesTableSplittingPrincipalFluentAPI
		{
			get
			{
				return(MEntitiesTableSplittingPrincipalFluentAPI);
			}
			set
			{
				MEntitiesTableSplittingPrincipalFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTableSplittingDependent1FluentAPI>	EntitiesTableSplittingDependent1FluentAPI
		{
			get
			{
				return(MEntitiesTableSplittingDependent1FluentAPI);
			}
			set
			{
				MEntitiesTableSplittingDependent1FluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityTableSplittingDependent2FluentAPI>	EntitiesTableSplittingDependent2FluentAPI
		{
			get
			{
				return(MEntitiesTableSplittingDependent2FluentAPI);
			}
			set
			{
				MEntitiesTableSplittingDependent2FluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<Dictionary<string,object>>					MyPropertyBagPrincipal
		{
			get
			{
				return(MMyPropertyBagPrincipal);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPropertyBagDependentFluentAPI>		EntitiesPropertyBagDependentFluentAPI
		{
			get
			{
				return(MEntitiesPropertyBagDependentFluentAPI);
			}
			set
			{
				MEntitiesPropertyBagDependentFluentAPI=value;
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
		private void ConfigureEntityOneToOnePrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOnePrincipalConventions>	Entity=ModelBuilder.Entity<CEntityOneToOnePrincipalConventions>();

			Entity.ToTable("EntitiesOneToOnePrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneDependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneDependentConventions>	Entity=ModelBuilder.Entity<CEntityOneToOneDependentConventions>();

			Entity.ToTable("EntitiesOneToOneDependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOnePrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOnePrincipalConventions>	Entity=ModelBuilder.Entity<CEntityZeroToOnePrincipalConventions>();

			Entity.ToTable("EntitiesZeroToOnePrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOneDependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOneDependentConventions>	Entity=ModelBuilder.Entity<CEntityZeroToOneDependentConventions>();

			Entity.ToTable("EntitiesZeroToOneDependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyPrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyPrincipalConventions>	Entity=ModelBuilder.Entity<CEntityOneToManyPrincipalConventions>();

			Entity.ToTable("EntitiesOneToManyPrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyDependentConventions>	Entity=ModelBuilder.Entity<CEntityOneToManyDependentConventions>();

			Entity.ToTable("EntitiesOneToManyDependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyPrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToManyPrincipalConventions>	Entity=ModelBuilder.Entity<CEntityZeroToManyPrincipalConventions>();

			Entity.ToTable("EntitiesZeroToManyPrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyDependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToManyDependentConventions>	Entity=ModelBuilder.Entity<CEntityZeroToManyDependentConventions>();

			Entity.ToTable("EntitiesZeroToManyDependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityForeignKeyName1PrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityForeignKeyName1PrincipalConventions>	Entity=ModelBuilder.Entity<CEntityForeignKeyName1PrincipalConventions>();

			Entity.ToTable("EntitiesForeignKeyName1PrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityForeignKeyName1DependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityForeignKeyName1DependentConventions>	Entity=ModelBuilder.Entity<CEntityForeignKeyName1DependentConventions>();

			Entity.ToTable("EntitiesForeignKeyName1DependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityForeignKeyName2PrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityForeignKeyName2PrincipalConventions>	Entity=ModelBuilder.Entity<CEntityForeignKeyName2PrincipalConventions>();

			Entity.ToTable("EntitiesForeignKeyName2PrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityForeignKeyName2DependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityForeignKeyName2DependentConventions>	Entity=ModelBuilder.Entity<CEntityForeignKeyName2DependentConventions>();

			Entity.ToTable("EntitiesForeignKeyName2DependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityForeignKeyName3PrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityForeignKeyName3PrincipalConventions>	Entity=ModelBuilder.Entity<CEntityForeignKeyName3PrincipalConventions>();

			Entity.ToTable("EntitiesForeignKeyName3PrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityForeignKeyName3DependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityForeignKeyName3DependentConventions>	Entity=ModelBuilder.Entity<CEntityForeignKeyName3DependentConventions>();

			Entity.ToTable("EntitiesForeignKeyName3DependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNoForeignKey1PrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNoForeignKey1PrincipalConventions>	Entity=ModelBuilder.Entity<CEntityNoForeignKey1PrincipalConventions>();

			Entity.ToTable("EntitiesNoForeignKey1PrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNoForeignKey1DependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNoForeignKey1DependentConventions>	Entity=ModelBuilder.Entity<CEntityNoForeignKey1DependentConventions>();

			Entity.ToTable("EntitiesNoForeignKey1DependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNoForeignKey2PrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNoForeignKey2PrincipalConventions>	Entity=ModelBuilder.Entity<CEntityNoForeignKey2PrincipalConventions>();

			Entity.ToTable("EntitiesNoForeignKey2PrincipalConventions");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNoForeignKey2DependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNoForeignKey2DependentConventions>	Entity=ModelBuilder.Entity<CEntityNoForeignKey2DependentConventions>();

			Entity.ToTable("EntitiesNoForeignKey2DependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNoForeignKey3PrincipalConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNoForeignKey3PrincipalConventions>	Entity=ModelBuilder.Entity<CEntityNoForeignKey3PrincipalConventions>();

			Entity.ToTable("EntitiesNoForeignKey3PrincipalConventions");

			Entity.HasKey(P => P.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNoForeignKey3DependentConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityNoForeignKey3DependentConventions>	Entity=ModelBuilder.Entity<CEntityNoForeignKey3DependentConventions>();

			Entity.ToTable("EntitiesNoForeignKey3DependentConventions");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOnePrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOnePrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityOneToOnePrincipalDataAnnotations>();

			Entity.ToTable("EntitiesOneToOnePrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityOneToOneDependentDataAnnotations>();

			Entity.ToTable("EntitiesOneToOneDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOnePrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOnePrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityZeroToOnePrincipalDataAnnotations>();

			Entity.ToTable("EntitiesZeroToOnePrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOneDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOneDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityZeroToOneDependentDataAnnotations>();

			Entity.ToTable("EntitiesZeroToOneDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyPrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyPrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityOneToManyPrincipalDataAnnotations>();

			Entity.ToTable("EntitiesOneToManyPrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityOneToManyDependentDataAnnotations>();

			Entity.ToTable("EntitiesOneToManyDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyPrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToManyPrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityZeroToManyPrincipalDataAnnotations>();

			Entity.ToTable("EntitiesZeroToManyPrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToManyDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToManyDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityZeroToManyDependentDataAnnotations>();

			Entity.ToTable("EntitiesZeroToManyDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAttributeOnNavigationPropertyPrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations>();

			Entity.ToTable("EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAttributeOnNavigationPropertyDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAttributeOnNavigationPropertyDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityAttributeOnNavigationPropertyDependentDataAnnotations>();

			Entity.ToTable("EntitiesAttributeOnNavigationPropertyDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAttributeOnForeignKeyPrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAttributeOnForeignKeyPrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityAttributeOnForeignKeyPrincipalDataAnnotations>();

			Entity.ToTable("EntitiesAttributeOnForeignKeyPrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAttributeOnForeignKeyDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAttributeOnForeignKeyDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityAttributeOnForeignKeyDependentDataAnnotations>();

			Entity.ToTable("EntitiesAttributeOnForeignKeyDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityCompositeForeignKeyPrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityCompositeForeignKeyPrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityCompositeForeignKeyPrincipalDataAnnotations>();

			Entity.ToTable("EntitiesCompositeForeignKeyPrincipalDataAnnotations");

			Entity.HasKey(nameof(CEntityCompositeForeignKeyPrincipalDataAnnotations.EntityPrincipalID1),nameof(CEntityCompositeForeignKeyPrincipalDataAnnotations.EntityPrincipalID2));
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityCompositeForeignKeyDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityCompositeForeignKeyDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityCompositeForeignKeyDependentDataAnnotations>();

			Entity.ToTable("EntitiesCompositeForeignKeyDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityInversePropertyPrincipalDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityInversePropertyPrincipalDataAnnotations>	Entity=ModelBuilder.Entity<CEntityInversePropertyPrincipalDataAnnotations>();

			Entity.ToTable("EntitiesInversePropertyPrincipalDataAnnotations");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityInversePropertyDependentDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityInversePropertyDependentDataAnnotations>	Entity=ModelBuilder.Entity<CEntityInversePropertyDependentDataAnnotations>();

			Entity.ToTable("EntitiesInversePropertyDependentDataAnnotations");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOne1PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOne1PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOne1PrincipalFluentAPI>();

			Entity.ToTable("EntitiesOneToOne1PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOne1PrincipalFluentAPI,CEntityOneToOne1DependentFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOne1PrincipalFluentAPI,CEntityOneToOne1DependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityOneToOne1DependentFluentAPI>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOne1DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOne1DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOne1DependentFluentAPI>();

			Entity.ToTable("EntitiesOneToOne1DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOne2PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOne2PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOne2PrincipalFluentAPI>();

			Entity.ToTable("EntitiesOneToOne2PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOne2DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOne2DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOne2DependentFluentAPI>();

			Entity.ToTable("EntitiesOneToOne2DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOne2DependentFluentAPI,CEntityOneToOne2PrincipalFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOne2DependentFluentAPI,CEntityOneToOne2PrincipalFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityDependent);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityOneToOne2DependentFluentAPI>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOne1PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOne1PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToOne1PrincipalFluentAPI>();

			Entity.ToTable("EntitiesZeroToOne1PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityZeroToOne1PrincipalFluentAPI,CEntityZeroToOne1DependentFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityZeroToOne1PrincipalFluentAPI,CEntityZeroToOne1DependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityZeroToOne1DependentFluentAPI>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOne1DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOne1DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToOne1DependentFluentAPI>();

			Entity.ToTable("EntitiesZeroToOne1DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOne2PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOne2PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToOne2PrincipalFluentAPI>();

			Entity.ToTable("EntitiesZeroToOne2PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToOne2DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToOne2DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToOne2DependentFluentAPI>();

			Entity.ToTable("EntitiesZeroToOne2DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityZeroToOne2DependentFluentAPI,CEntityZeroToOne2PrincipalFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityZeroToOne2DependentFluentAPI,CEntityZeroToOne2PrincipalFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityDependent);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityZeroToOne2DependentFluentAPI>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneMixedKeys1PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneMixedKeys1PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOneMixedKeys1PrincipalFluentAPI>();

			Entity.ToTable("EntitiesOneToOneMixedKeys1PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOneMixedKeys1PrincipalFluentAPI,CEntityOneToOneMixedKeys1DependentFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOneMixedKeys1PrincipalFluentAPI,CEntityOneToOneMixedKeys1DependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			// !!!!! FOREIGN KEY je zaroven aj PRIMARY KEY.
			RightSide.HasForeignKey<CEntityOneToOneMixedKeys1DependentFluentAPI>(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneMixedKeys1DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneMixedKeys1DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOneMixedKeys1DependentFluentAPI>();

			Entity.ToTable("EntitiesOneToOneMixedKeys1DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneMixedKeys2PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneMixedKeys2PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOneMixedKeys2PrincipalFluentAPI>();

			Entity.ToTable("EntitiesOneToOneMixedKeys2PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneMixedKeys2DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneMixedKeys2DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToOneMixedKeys2DependentFluentAPI>();

			Entity.ToTable("EntitiesOneToOneMixedKeys2DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOneMixedKeys2DependentFluentAPI,CEntityOneToOneMixedKeys2PrincipalFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOneMixedKeys2DependentFluentAPI,CEntityOneToOneMixedKeys2PrincipalFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityDependent);

			// !!!!! Vytvori sa FOREIGN KEY.
			// !!!!! FOREIGN KEY je zaroven aj PRIMARY KEY.
			RightSide.HasForeignKey<CEntityOneToOneMixedKeys2DependentFluentAPI>(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToMany1PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToMany1PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToMany1PrincipalFluentAPI>();

			Entity.ToTable("EntitiesOneToMany1PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToMany1PrincipalFluentAPI,CEntityOneToMany1DependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToMany1PrincipalFluentAPI,CEntityOneToMany1DependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToMany1DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToMany1DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToMany1DependentFluentAPI>();

			Entity.ToTable("EntitiesOneToMany1DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToMany2PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToMany2PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToMany2PrincipalFluentAPI>();

			Entity.ToTable("EntitiesOneToMany2PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToMany2DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToMany2DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOneToMany2DependentFluentAPI>();

			Entity.ToTable("EntitiesOneToMany2DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToMany2DependentFluentAPI,CEntityOneToMany2PrincipalFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToMany2PrincipalFluentAPI,CEntityOneToMany2DependentFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToMany1PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToMany1PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToMany1PrincipalFluentAPI>();

			Entity.ToTable("EntitiesZeroToMany1PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityZeroToMany1PrincipalFluentAPI,CEntityZeroToMany1DependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroToMany1PrincipalFluentAPI,CEntityZeroToMany1DependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToMany1DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToMany1DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToMany1DependentFluentAPI>();

			Entity.ToTable("EntitiesZeroToMany1DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToMany2PrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToMany2PrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToMany2PrincipalFluentAPI>();

			Entity.ToTable("EntitiesZeroToMany2PrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroToMany2DependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroToMany2DependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroToMany2DependentFluentAPI>();

			Entity.ToTable("EntitiesZeroToMany2DependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityZeroToMany2DependentFluentAPI,CEntityZeroToMany2PrincipalFluentAPI>	LeftSide=Entity.HasOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroToMany2PrincipalFluentAPI,CEntityZeroToMany2DependentFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToMany1MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToMany1MFluentAPI>		Entity=ModelBuilder.Entity<CEntityManyToMany1MFluentAPI>();

			Entity.ToTable("EntitiesManyToMany1MFluentAPI");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityManyToMany1MFluentAPI,CEntityManyToMany1MNFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToMany1MFluentAPI,CEntityManyToMany1MNFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityM);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToMany1NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToMany1NFluentAPI>		Entity=ModelBuilder.Entity<CEntityManyToMany1NFluentAPI>();

			Entity.ToTable("EntitiesManyToMany1NFluentAPI");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityManyToMany1NFluentAPI,CEntityManyToMany1MNFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToMany1NFluentAPI,CEntityManyToMany1MNFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToMany1MNFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToMany1MNFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToMany1MNFluentAPI>();

			Entity.ToTable("EntitiesManyToMany1MNFluentAPI");

			// !!!!! ENTITY MN v RELATIONSHIP M:N ma ARTIFICIAL PRIMARY KEY.
			Entity.HasKey(P => P.EntityMNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToMany2MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToMany2MFluentAPI>		Entity=ModelBuilder.Entity<CEntityManyToMany2MFluentAPI>();

			Entity.ToTable("EntitiesManyToMany2MFluentAPI");

			Entity.HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToMany2NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToMany2NFluentAPI>		Entity=ModelBuilder.Entity<CEntityManyToMany2NFluentAPI>();

			Entity.ToTable("EntitiesManyToMany2NFluentAPI");

			Entity.HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToMany2MNFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToMany2MNFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToMany2MNFluentAPI>();

			Entity.ToTable("EntitiesManyToMany2MNFluentAPI");

			// !!!!! ENTITY MN v RELATIONSHIP M:N ma ARTIFICIAL PRIMARY KEY.
			Entity.HasKey(P => P.EntityMNID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY M.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityManyToMany2MNFluentAPI,CEntityManyToMany2MFluentAPI>	LeftSideM=Entity.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToMany2MFluentAPI,CEntityManyToMany2MNFluentAPI>	RightSideM=LeftSideM.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSideM.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSideM.IsRequired(true);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY N.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityManyToMany2MNFluentAPI,CEntityManyToMany2NFluentAPI>	LeftSideN=Entity.HasOne(P => P.EntityN);
			
			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToMany2NFluentAPI,CEntityManyToMany2MNFluentAPI>	RightSideN=LeftSideN.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSideN.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSideN.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroManyToMany1MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroManyToMany1MFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroManyToMany1MFluentAPI>();

			Entity.ToTable("EntitiesZeroManyToMany1MFluentAPI");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityZeroManyToMany1MFluentAPI,CEntityZeroManyToMany1MNFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroManyToMany1MFluentAPI,CEntityZeroManyToMany1MNFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityM);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroManyToMany1NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroManyToMany1NFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroManyToMany1NFluentAPI>();

			Entity.ToTable("EntitiesZeroManyToMany1NFluentAPI");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityZeroManyToMany1NFluentAPI,CEntityZeroManyToMany1MNFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroManyToMany1NFluentAPI,CEntityZeroManyToMany1MNFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroManyToMany1MNFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroManyToMany1MNFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroManyToMany1MNFluentAPI>();

			Entity.ToTable("EntitiesZeroManyToMany1MNFluentAPI");

			// !!!!! ENTITY MN v RELATIONSHIP M:N ma ARTIFICIAL PRIMARY KEY.
			Entity.HasKey(P => P.EntityMNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroManyToMany2MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroManyToMany2MFluentAPI>		Entity=ModelBuilder.Entity<CEntityZeroManyToMany2MFluentAPI>();

			Entity.ToTable("EntitiesZeroManyToMany2MFluentAPI");

			Entity.HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroManyToMany2NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroManyToMany2NFluentAPI>		Entity=ModelBuilder.Entity<CEntityZeroManyToMany2NFluentAPI>();

			Entity.ToTable("EntitiesZeroManyToMany2NFluentAPI");

			Entity.HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityZeroManyToMany2MNFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityZeroManyToMany2MNFluentAPI>	Entity=ModelBuilder.Entity<CEntityZeroManyToMany2MNFluentAPI>();

			Entity.ToTable("EntitiesZeroManyToMany2MNFluentAPI");

			// !!!!! ENTITY MN v RELATIONSHIP M:N ma ARTIFICIAL PRIMARY KEY.
			Entity.HasKey(P => P.EntityMNID);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY M.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityZeroManyToMany2MNFluentAPI,CEntityZeroManyToMany2MFluentAPI>	LeftSideM=Entity.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroManyToMany2MFluentAPI,CEntityZeroManyToMany2MNFluentAPI>	RightSideM=LeftSideM.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSideM.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSideM.IsRequired(false);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY N.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityZeroManyToMany2MNFluentAPI,CEntityZeroManyToMany2NFluentAPI>	LeftSideN=Entity.HasOne(P => P.EntityN);
			
			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityZeroManyToMany2NFluentAPI,CEntityZeroManyToMany2MNFluentAPI>	RightSideN=LeftSideN.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSideN.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSideN.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMixedKeys1MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMixedKeys1MFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToManyMixedKeys1MFluentAPI>();

			Entity.ToTable("EntitiesManyToManyMixedKeys1MFluentAPI");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityManyToManyMixedKeys1MFluentAPI,CEntityManyToManyMixedKeys1MNFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToManyMixedKeys1MFluentAPI,CEntityManyToManyMixedKeys1MNFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityM);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMixedKeys1NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMixedKeys1NFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToManyMixedKeys1NFluentAPI>();

			Entity.ToTable("EntitiesManyToManyMixedKeys1NFluentAPI");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityManyToManyMixedKeys1NFluentAPI,CEntityManyToManyMixedKeys1MNFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToManyMixedKeys1NFluentAPI,CEntityManyToManyMixedKeys1MNFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMixedKeys1MNFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMixedKeys1MNFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToManyMixedKeys1MNFluentAPI>();

			Entity.ToTable("EntitiesManyToManyMixedKeys1MNFluentAPI");

			// !!!!! ENTITY MN v RELATIONSHIP M:N MUSI mat COMPOSITE KEY.
			Entity.HasKey(nameof(CEntityManyToManyMixedKeys1MNFluentAPI.EntityMID),nameof(CEntityManyToManyMixedKeys1MNFluentAPI.EntityNID));
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMixedKeys2MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMixedKeys2MFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToManyMixedKeys2MFluentAPI>();

			Entity.ToTable("EntitiesManyToManyMixedKeys2MFluentAPI");

			Entity.HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMixedKeys2NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMixedKeys2NFluentAPI>		Entity=ModelBuilder.Entity<CEntityManyToManyMixedKeys2NFluentAPI>();

			Entity.ToTable("EntitiesManyToManyMixedKeys2NFluentAPI");

			Entity.HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMixedKeys2MNFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMixedKeys2MNFluentAPI>	Entity=ModelBuilder.Entity<CEntityManyToManyMixedKeys2MNFluentAPI>();

			Entity.ToTable("EntitiesManyToManyMixedKeys2MNFluentAPI");

			// !!!!! ENTITY MN v RELATIONSHIP M:N MUSI mat COMPOSITE KEY.
			Entity.HasKey(nameof(CEntityManyToManyMixedKeys2MNFluentAPI.EntityMID),nameof(CEntityManyToManyMixedKeys2MNFluentAPI.EntityNID));

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY M.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityManyToManyMixedKeys2MNFluentAPI,CEntityManyToManyMixedKeys2MFluentAPI>	LeftSideM=Entity.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToManyMixedKeys2MFluentAPI,CEntityManyToManyMixedKeys2MNFluentAPI>	RightSideM=LeftSideM.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSideM.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSideM.IsRequired(true);

			// !!!!! RELATIONSHIP je CONFIGURED na DEPENDENT ENTITY N.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityManyToManyMixedKeys2MNFluentAPI,CEntityManyToManyMixedKeys2NFluentAPI>	LeftSideN=Entity.HasOne(P => P.EntityN);
			
			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToManyMixedKeys2NFluentAPI,CEntityManyToManyMixedKeys2MNFluentAPI>	RightSideN=LeftSideN.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSideN.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSideN.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToMany1MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToMany1MFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToMany1MFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToMany1MFluentAPI");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na ENTITY M.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityAutoManyToMany1MFluentAPI,CEntityAutoManyToMany1NFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			CollectionCollectionBuilder<CEntityAutoManyToMany1NFluentAPI,CEntityAutoManyToMany1MFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesM);

			// !!!!! Definuje sa LINK ENTITY MN.
			EntityTypeBuilder<CEntityAutoManyToMany1MNFluentAPI>	EntityMN=RightSide.UsingEntity<CEntityAutoManyToMany1MNFluentAPI>();

			EntityMN.ToTable("EntitiesAutoManyToMany1MNFluentAPI");

			EntityMN.HasKey(P => P.EntityMNID);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToMany1MNFluentAPI,CEntityAutoManyToMany1MFluentAPI>	EntityMNLeftSide1=EntityMN.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToMany1MFluentAPI,CEntityAutoManyToMany1MNFluentAPI>	EntityMNRightSide1=EntityMNLeftSide1.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide1.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide1.IsRequired(true);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToMany1MNFluentAPI,CEntityAutoManyToMany1NFluentAPI>	EntityMNLeftSide2=EntityMN.HasOne(P => P.EntityN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToMany1NFluentAPI,CEntityAutoManyToMany1MNFluentAPI>	EntityMNRightSide2=EntityMNLeftSide2.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide2.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide2.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToMany1NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToMany1NFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToMany1NFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToMany1NFluentAPI");

			Entity.HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToMany2MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToMany2MFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToMany2MFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToMany2MFluentAPI");

			Entity.HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToMany2NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToMany2NFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToMany2NFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToMany2NFluentAPI");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na ENTITY N.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityAutoManyToMany2NFluentAPI,CEntityAutoManyToMany2MFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			CollectionCollectionBuilder<CEntityAutoManyToMany2MFluentAPI,CEntityAutoManyToMany2NFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesN);

			// !!!!! Definuje sa LINK ENTITY MN.
			EntityTypeBuilder<CEntityAutoManyToMany2MNFluentAPI>	EntityMN=RightSide.UsingEntity<CEntityAutoManyToMany2MNFluentAPI>();

			EntityMN.ToTable("EntitiesAutoManyToMany2MNFluentAPI");

			EntityMN.HasKey(P => P.EntityMNID);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToMany2MNFluentAPI,CEntityAutoManyToMany2MFluentAPI>	EntityMNLeftSide1=EntityMN.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToMany2MFluentAPI,CEntityAutoManyToMany2MNFluentAPI>	EntityMNRightSide1=EntityMNLeftSide1.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide1.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide1.IsRequired(true);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToMany2MNFluentAPI,CEntityAutoManyToMany2NFluentAPI>	EntityMNLeftSide2=EntityMN.HasOne(P => P.EntityN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToMany2NFluentAPI,CEntityAutoManyToMany2MNFluentAPI>	EntityMNRightSide2=EntityMNLeftSide2.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide2.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide2.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoZeroManyToMany1MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoZeroManyToMany1MFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoZeroManyToMany1MFluentAPI>();

			Entity.ToTable("EntitiesAutoZeroManyToMany1MFluentAPI");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na ENTITY M.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityAutoZeroManyToMany1MFluentAPI,CEntityAutoZeroManyToMany1NFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			CollectionCollectionBuilder<CEntityAutoZeroManyToMany1NFluentAPI,CEntityAutoZeroManyToMany1MFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesM);

			// !!!!! Definuje sa LINK ENTITY MN.
			EntityTypeBuilder<CEntityAutoZeroManyToMany1MNFluentAPI>	EntityMN=RightSide.UsingEntity<CEntityAutoZeroManyToMany1MNFluentAPI>();

			EntityMN.ToTable("EntitiesAutoZeroManyToMany1MNFluentAPI");

			EntityMN.HasKey(P => P.EntityMNID);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoZeroManyToMany1MNFluentAPI,CEntityAutoZeroManyToMany1MFluentAPI>	EntityMNLeftSide1=EntityMN.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoZeroManyToMany1MFluentAPI,CEntityAutoZeroManyToMany1MNFluentAPI>	EntityMNRightSide1=EntityMNLeftSide1.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide1.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			EntityMNRightSide1.IsRequired(false);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoZeroManyToMany1MNFluentAPI,CEntityAutoZeroManyToMany1NFluentAPI>	EntityMNLeftSide2=EntityMN.HasOne(P => P.EntityN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoZeroManyToMany1NFluentAPI,CEntityAutoZeroManyToMany1MNFluentAPI>	EntityMNRightSide2=EntityMNLeftSide2.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide2.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je -NONREQUIRED.
			EntityMNRightSide2.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoZeroManyToMany1NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoZeroManyToMany1NFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoZeroManyToMany1NFluentAPI>();

			Entity.ToTable("EntitiesAutoZeroManyToMany1NFluentAPI");

			Entity.HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoZeroManyToMany2MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoZeroManyToMany2MFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoZeroManyToMany2MFluentAPI>();

			Entity.ToTable("EntitiesAutoZeroManyToMany2MFluentAPI");

			Entity.HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoZeroManyToMany2NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoZeroManyToMany2NFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoZeroManyToMany2NFluentAPI>();

			Entity.ToTable("EntitiesAutoZeroManyToMany2NFluentAPI");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na ENTITY N.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityAutoZeroManyToMany2NFluentAPI,CEntityAutoZeroManyToMany2MFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			CollectionCollectionBuilder<CEntityAutoZeroManyToMany2MFluentAPI,CEntityAutoZeroManyToMany2NFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesN);

			// !!!!! Definuje sa LINK ENTITY MN.
			EntityTypeBuilder<CEntityAutoZeroManyToMany2MNFluentAPI>	EntityMN=RightSide.UsingEntity<CEntityAutoZeroManyToMany2MNFluentAPI>();

			EntityMN.ToTable("EntitiesAutoZeroManyToMany2MNFluentAPI");

			EntityMN.HasKey(P => P.EntityMNID);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoZeroManyToMany2MNFluentAPI,CEntityAutoZeroManyToMany2MFluentAPI>	EntityMNLeftSide1=EntityMN.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoZeroManyToMany2MFluentAPI,CEntityAutoZeroManyToMany2MNFluentAPI>	EntityMNRightSide1=EntityMNLeftSide1.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide1.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			EntityMNRightSide1.IsRequired(false);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoZeroManyToMany2MNFluentAPI,CEntityAutoZeroManyToMany2NFluentAPI>	EntityMNLeftSide2=EntityMN.HasOne(P => P.EntityN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoZeroManyToMany2NFluentAPI,CEntityAutoZeroManyToMany2MNFluentAPI>	EntityMNRightSide2=EntityMNLeftSide2.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide2.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			EntityMNRightSide2.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToManyMixedKeys1MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToManyMixedKeys1MFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToManyMixedKeys1MFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToManyMixedKeys1MFluentAPI");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na ENTITY M.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityAutoManyToManyMixedKeys1MFluentAPI,CEntityAutoManyToManyMixedKeys1NFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			CollectionCollectionBuilder<CEntityAutoManyToManyMixedKeys1NFluentAPI,CEntityAutoManyToManyMixedKeys1MFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesM);

			// !!!!! Definuje sa LINK ENTITY MN.
			EntityTypeBuilder<CEntityAutoManyToManyMixedKeys1MNFluentAPI>	EntityMN=RightSide.UsingEntity<CEntityAutoManyToManyMixedKeys1MNFluentAPI>();

			EntityMN.ToTable("EntitiesAutoManyToManyMixedKeys1MNFluentAPI");

			// !!!!! COMPOSITE PRIMARY KEY.
			EntityMN.HasKey(nameof(CEntityAutoManyToManyMixedKeys1MNFluentAPI.EntityMID),nameof(CEntityAutoManyToManyMixedKeys1MNFluentAPI.EntityNID));

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToManyMixedKeys1MNFluentAPI,CEntityAutoManyToManyMixedKeys1MFluentAPI>	EntityMNLeftSide1=EntityMN.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToManyMixedKeys1MFluentAPI,CEntityAutoManyToManyMixedKeys1MNFluentAPI>	EntityMNRightSide1=EntityMNLeftSide1.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide1.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide1.IsRequired(true);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToManyMixedKeys1MNFluentAPI,CEntityAutoManyToManyMixedKeys1NFluentAPI>	EntityMNLeftSide2=EntityMN.HasOne(P => P.EntityN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToManyMixedKeys1NFluentAPI,CEntityAutoManyToManyMixedKeys1MNFluentAPI>	EntityMNRightSide2=EntityMNLeftSide2.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide2.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide2.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToManyMixedKeys1NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToManyMixedKeys1NFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToManyMixedKeys1NFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToManyMixedKeys1NFluentAPI");

			Entity.HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToManyMixedKeys2MFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToManyMixedKeys2MFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToManyMixedKeys2MFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToManyMixedKeys2MFluentAPI");

			Entity.HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityAutoManyToManyMixedKeys2NFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityAutoManyToManyMixedKeys2NFluentAPI>	Entity=ModelBuilder.Entity<CEntityAutoManyToManyMixedKeys2NFluentAPI>();

			Entity.ToTable("EntitiesAutoManyToManyMixedKeys2NFluentAPI");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na ENTITY N.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP M:N.
			CollectionNavigationBuilder<CEntityAutoManyToManyMixedKeys2NFluentAPI,CEntityAutoManyToManyMixedKeys2MFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP M:N.
			CollectionCollectionBuilder<CEntityAutoManyToManyMixedKeys2MFluentAPI,CEntityAutoManyToManyMixedKeys2NFluentAPI>	RightSide=LeftSide.WithMany(P => P.EntitiesN);

			// !!!!! Definuje sa LINK ENTITY MN.
			EntityTypeBuilder<CEntityAutoManyToManyMixedKeys2MNFluentAPI>	EntityMN=RightSide.UsingEntity<CEntityAutoManyToManyMixedKeys2MNFluentAPI>();

			EntityMN.ToTable("EntitiesAutoManyToManyMixedKeys2MNFluentAPI");

			// !!!!! COMPOSITE PRIMARY KEY.
			EntityMN.HasKey(nameof(CEntityAutoManyToManyMixedKeys2MNFluentAPI.EntityMID),nameof(CEntityAutoManyToManyMixedKeys2MNFluentAPI.EntityNID));

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToManyMixedKeys2MNFluentAPI,CEntityAutoManyToManyMixedKeys2MFluentAPI>	EntityMNLeftSide1=EntityMN.HasOne(P => P.EntityM);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToManyMixedKeys2MFluentAPI,CEntityAutoManyToManyMixedKeys2MNFluentAPI>	EntityMNRightSide1=EntityMNLeftSide1.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide1.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide1.IsRequired(true);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceNavigationBuilder<CEntityAutoManyToManyMixedKeys2MNFluentAPI,CEntityAutoManyToManyMixedKeys2NFluentAPI>	EntityMNLeftSide2=EntityMN.HasOne(P => P.EntityN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP medzi ENTITY MN a ENTIY M.
			ReferenceCollectionBuilder<CEntityAutoManyToManyMixedKeys2NFluentAPI,CEntityAutoManyToManyMixedKeys2MNFluentAPI>	EntityMNRightSide2=EntityMNLeftSide2.WithMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa FOREIGN KEY.
			EntityMNRightSide2.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			EntityMNRightSide2.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteNoActionNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteNoActionNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteNoActionNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteNoActionNotNullPrincipalFluentAPI,CEntityOnDeleteNoActionNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteNoActionNotNullPrincipalFluentAPI,CEntityOnDeleteNoActionNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [NoAction].
			RightSide.OnDelete(DeleteBehavior.NoAction);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteNoActionNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteNoActionNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteNoActionNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteNoActionNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteNoActionNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteNoActionNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteNoActionNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteNoActionNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteNoActionNullPrincipalFluentAPI,CEntityOnDeleteNoActionNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteNoActionNullPrincipalFluentAPI,CEntityOnDeleteNoActionNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [NoAction].
			RightSide.OnDelete(DeleteBehavior.NoAction);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteNoActionNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteNoActionNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteNoActionNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteNoActionNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI,CEntityOnDeleteClientNoActionNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI,CEntityOnDeleteClientNoActionNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [ClientNoAction].
			RightSide.OnDelete(DeleteBehavior.ClientNoAction);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientNoActionNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientNoActionNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientNoActionNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientNoActionNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientNoActionNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientNoActionNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteClientNoActionNullPrincipalFluentAPI,CEntityOnDeleteClientNoActionNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteClientNoActionNullPrincipalFluentAPI,CEntityOnDeleteClientNoActionNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [ClientNoAction].
			RightSide.OnDelete(DeleteBehavior.ClientNoAction);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientNoActionNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientNoActionNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientNoActionNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientNoActionNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteRestrictNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteRestrictNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteRestrictNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteRestrictNotNullPrincipalFluentAPI,CEntityOnDeleteRestrictNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteRestrictNotNullPrincipalFluentAPI,CEntityOnDeleteRestrictNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [Restrict].
			RightSide.OnDelete(DeleteBehavior.Restrict);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteRestrictNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteRestrictNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteRestrictNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteRestrictNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteRestrictNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteRestrictNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteRestrictNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteRestrictNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteRestrictNullPrincipalFluentAPI,CEntityOnDeleteRestrictNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteRestrictNullPrincipalFluentAPI,CEntityOnDeleteRestrictNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [Restrict].
			RightSide.OnDelete(DeleteBehavior.Restrict);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteRestrictNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteRestrictNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteRestrictNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteRestrictNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteSetNullNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteSetNullNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteSetNullNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteSetNullNotNullPrincipalFluentAPI,CEntityOnDeleteSetNullNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteSetNullNotNullPrincipalFluentAPI,CEntityOnDeleteSetNullNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [SetNull].
			RightSide.OnDelete(DeleteBehavior.SetNull);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteSetNullNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteSetNullNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteSetNullNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteSetNullNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteSetNullNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteSetNullNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteSetNullNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteSetNullNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteSetNullNullPrincipalFluentAPI,CEntityOnDeleteSetNullNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteSetNullNullPrincipalFluentAPI,CEntityOnDeleteSetNullNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [SetNull].
			RightSide.OnDelete(DeleteBehavior.SetNull);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteSetNullNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteSetNullNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteSetNullNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteSetNullNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI,CEntityOnDeleteClientSetNullNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI,CEntityOnDeleteClientSetNullNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [ClientSetNull].
			RightSide.OnDelete(DeleteBehavior.ClientSetNull);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientSetNullNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientSetNullNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientSetNullNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientSetNullNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientSetNullNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientSetNullNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteClientSetNullNullPrincipalFluentAPI,CEntityOnDeleteClientSetNullNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteClientSetNullNullPrincipalFluentAPI,CEntityOnDeleteClientSetNullNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [ClientSetNull].
			RightSide.OnDelete(DeleteBehavior.ClientSetNull);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientSetNullNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientSetNullNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientSetNullNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientSetNullNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteCascadeNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteCascadeNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteCascadeNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteCascadeNotNullPrincipalFluentAPI,CEntityOnDeleteCascadeNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteCascadeNotNullPrincipalFluentAPI,CEntityOnDeleteCascadeNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [Cascade].
			RightSide.OnDelete(DeleteBehavior.Cascade);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteCascadeNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteCascadeNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteCascadeNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteCascadeNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteCascadeNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteCascadeNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteCascadeNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteCascadeNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteCascadeNullPrincipalFluentAPI,CEntityOnDeleteCascadeNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteCascadeNullPrincipalFluentAPI,CEntityOnDeleteCascadeNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [Cascade].
			RightSide.OnDelete(DeleteBehavior.Cascade);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteCascadeNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteCascadeNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteCascadeNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteCascadeNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI,CEntityOnDeleteClientCascadeNotNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI,CEntityOnDeleteClientCascadeNotNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [ClientCascade].
			RightSide.OnDelete(DeleteBehavior.ClientCascade);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientCascadeNotNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientCascadeNotNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientCascadeNotNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientCascadeNullPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientCascadeNullPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientCascadeNullPrincipalFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOnDeleteClientCascadeNullPrincipalFluentAPI,CEntityOnDeleteClientCascadeNullDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOnDeleteClientCascadeNullPrincipalFluentAPI,CEntityOnDeleteClientCascadeNullDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);

			// !!!!! DELETE BEHAVIOR sa nastavi na VALUE [ClientCascade].
			RightSide.OnDelete(DeleteBehavior.ClientCascade);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOnDeleteClientCascadeNullDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOnDeleteClientCascadeNullDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityOnDeleteClientCascadeNullDependentFluentAPI>();

			Entity.ToTable("EntitiesOnDeleteClientCascadeNullDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityRequiredTruePrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityRequiredTruePrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityRequiredTruePrincipalFluentAPI>();

			Entity.ToTable("EntitiesRequiredTruePrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityRequiredTruePrincipalFluentAPI,CEntityRequiredTrueDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityRequiredTruePrincipalFluentAPI,CEntityRequiredTrueDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityRequiredTrueDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityRequiredTrueDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityRequiredTrueDependentFluentAPI>();

			Entity.ToTable("EntitiesRequiredTrueDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityRequiredFalsePrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityRequiredFalsePrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityRequiredFalsePrincipalFluentAPI>();

			Entity.ToTable("EntitiesRequiredFalsePrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityRequiredFalsePrincipalFluentAPI,CEntityRequiredFalseDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityRequiredFalsePrincipalFluentAPI,CEntityRequiredFalseDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je NON-REQUIRED.
			RightSide.IsRequired(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityRequiredFalseDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityRequiredFalseDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityRequiredFalseDependentFluentAPI>();

			Entity.ToTable("EntitiesRequiredFalseDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasAlternateKeyFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasAlternateKeyFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasAlternateKeyFluentAPI>();

			Entity.ToTable("EntitiesHasAlternateKeyFluentAPI");

			Entity.HasKey(P => P.EntityID);
			
			// !!!!! Definuje sa ALTERNATE KEY, ktory MUSI byt UNIQUE.
			Entity.HasAlternateKey(P => P.MyAlternateKey);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasAlternateKeyCompositeFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasAlternateKeyCompositeFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasAlternateKeyCompositeFluentAPI>();

			Entity.ToTable("EntitiesHasAlternateKeyCompositeFluentAPI");

			Entity.HasKey(P => P.EntityID);
			
			// !!!!! Definuje sa COMPOSITE ALTERNATE KEY, ktory MUSI byt UNIQUE.
			Entity.HasAlternateKey(nameof(CEntityHasAlternateKeyCompositeFluentAPI.MyAlternateKey1),nameof(CEntityHasAlternateKeyCompositeFluentAPI.MyAlternateKey2));
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasPrincipalKeyPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasPrincipalKeyPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasPrincipalKeyPrincipalFluentAPI>();

			Entity.ToTable("EntitiesHasPrincipalKeyPrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityHasPrincipalKeyPrincipalFluentAPI,CEntityHasPrincipalKeyDependentFluentAPI>	LeftSideEntity=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityHasPrincipalKeyPrincipalFluentAPI,CEntityHasPrincipalKeyDependentFluentAPI>	RightSideEntity=LeftSideEntity.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY, ktory NIE JE ZHODNY s PRIMARY KEY PRINCIPAL ENTITY.
			// !!!!! FOREIGN KEY je zhodny s PRINCIPAL KEY v PRINCIPAL ENTITY.
			RightSideEntity.HasForeignKey(P => P.MyPrincipalKeyInEntityDependent);

			// !!!!! Nastavi sa PRINCIPAL KEY v PRINCIPAL ENTITY. METHOD vykonava nasledujuce cinnosti.
			// !!!!! 1. METHOD oznaci definovanu PROPERTY ako UNIQUE PROPERTY na ktoru je aplikovany UNIQUE CONSTRAINT.
			// !!!!! 2. METHOD interne VOLA aj METHOD [KeyBuilder<TEntity> EntityTypeBuilder<TEntity>.HasAlternateKey(Expression<Func<TEntity,object>> KeyExpression)], ktora oznaci definovanu PROPERTY ako ALTERNATE KEY. ALTERNATE KEY je NON-PRIMARY KEY na ktory sa pomocou FOREIGN KEY mozu referovat DEPENDENT ENTITIES.
			RightSideEntity.HasPrincipalKey(P => P.MyPrincipalKeyInEntityPrincipal);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasPrincipalKeyDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasPrincipalKeyDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasPrincipalKeyDependentFluentAPI>();

			Entity.ToTable("EntitiesHasPrincipalKeyDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasPrincipalKeyCompositePrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasPrincipalKeyCompositePrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasPrincipalKeyCompositePrincipalFluentAPI>();

			Entity.ToTable("EntitiesHasPrincipalKeyCompositePrincipalFluentAPI");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityHasPrincipalKeyCompositePrincipalFluentAPI,CEntityHasPrincipalKeyCompositeDependentFluentAPI>	LeftSideEntity=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityHasPrincipalKeyCompositePrincipalFluentAPI,CEntityHasPrincipalKeyCompositeDependentFluentAPI>	RightSideEntity=LeftSideEntity.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY, ktory NIE JE ZHODNY s PRIMARY KEY PRINCIPAL ENTITY.
			// !!!!! FOREIGN KEY je zhodny s PRINCIPAL KEY v PRINCIPAL ENTITY.
			RightSideEntity.HasForeignKey(nameof(CEntityHasPrincipalKeyCompositeDependentFluentAPI.MyPrincipalKeyInEntityDependent1),nameof(CEntityHasPrincipalKeyCompositeDependentFluentAPI.MyPrincipalKeyInEntityDependent2));

			// !!!!! Nastavi sa PRINCIPAL KEY v PRINCIPAL ENTITY. METHOD vykonava nasledujuce cinnosti.
			// !!!!! 1. METHOD oznaci definovanu PROPERTY ako UNIQUE PROPERTY na ktoru je aplikovany UNIQUE CONSTRAINT.
			// !!!!! 2. METHOD interne VOLA aj METHOD [KeyBuilder<TEntity> EntityTypeBuilder<TEntity>.HasAlternateKey(Expression<Func<TEntity,object>> KeyExpression)], ktora oznaci definovanu PROPERTY ako ALTERNATE KEY. ALTERNATE KEY je NON-PRIMARY KEY na ktory sa pomocou FOREIGN KEY mozu referovat DEPENDENT ENTITIES.
			RightSideEntity.HasPrincipalKey(nameof(CEntityHasPrincipalKeyCompositePrincipalFluentAPI.MyPrincipalKeyInEntityPrincipal1),nameof(CEntityHasPrincipalKeyCompositePrincipalFluentAPI.MyPrincipalKeyInEntityPrincipal2));
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasPrincipalKeyCompositeDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasPrincipalKeyCompositeDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasPrincipalKeyCompositeDependentFluentAPI>();

			Entity.ToTable("EntitiesHasPrincipalKeyCompositeDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasConstraintNamePrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasConstraintNamePrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasConstraintNamePrincipalFluentAPI>();

			Entity.ToTable("EntitiesHasConstraintNamePrincipalFluentAPI");

			KeyBuilder											KeyBuilder=Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! Nastavi sa NAME PRIMARY KEY.
			KeyBuilder.HasName("My_PRIMARY_KEY_PRINCIPAL");

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityHasConstraintNamePrincipalFluentAPI,CEntityHasConstraintNameDependentFluentAPI>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityHasConstraintNamePrincipalFluentAPI,CEntityHasConstraintNameDependentFluentAPI>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);

			// !!!!! Nastavi sa CONSTRAINT NAME FORIEGN KEY.
			RightSide.HasConstraintName("My_FOREIGN_KEY_CONSTRAINT");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityHasConstraintNameDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityHasConstraintNameDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityHasConstraintNameDependentFluentAPI>();

			Entity.ToTable("EntitiesHasConstraintNameDependentFluentAPI");

			KeyBuilder											KeyBuilder=Entity.HasKey(P => P.EntityDependentID);

			// !!!!! Nastavi sa NAME PRIMARY KEY.
			KeyBuilder.HasName("My_PRIMARY_KEY_DEPENDENT");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeInOneTable(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedTypeInOneTable>		Entity=ModelBuilder.Entity<CEntityOwnedTypeInOneTable>();

			Entity.ToTable("EntitiesOwnedTypeInOneTable");

			Entity.HasKey(P => P.EntityID);

			// !!! Ziska sa REFERENCE na NAVIGATION PROPERTY.
			NavigationBuilder<CEntityOwnedTypeInOneTable,COwnedTypeDataAnnotations>	NavigationBuilder=Entity.Navigation(P => P.OwnedTypeDataAnnotationsRequired);

			// !!! OWNED TYPE PROPERTY sa nastavi ako REQUIRED.
			NavigationBuilder.IsRequired(true);

			// !!!!! OWNED TYPE sa nastavi pomocou FLUENT API.
			Entity.OwnsOne(P => P.OwnedTypeFluentAPI);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeInMultiTables(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedTypeInMultiTables>	Entity=ModelBuilder.Entity<CEntityOwnedTypeInMultiTables>();

			Entity.ToTable("EntitiesOwnedTypeInMultiTables");

			Entity.HasKey(P => P.EntityID);

			// !!!!! OWNED TYPE sa nastavi pomocou FLUENT API.
			OwnedNavigationBuilder<CEntityOwnedTypeInMultiTables,COwnedTypeDataAnnotations>	OwnedNavigationBuilder1=Entity.OwnsOne(P => P.OwnedTypeDataAnnotations);

			// !!!!! OWNED TYPE bude v osobitnej TABLE.
			OwnedNavigationBuilder1.ToTable("OwnedType1");

			// !!!!! OWNED TYPE sa nastavi pomocou FLUENT API.
			OwnedNavigationBuilder<CEntityOwnedTypeInMultiTables,COwnedTypeDataAnnotations>	OwnedNavigationBuilder2=Entity.OwnsOne(P => P.OwnedTypeDataAnnotationsRequired);

			// !!!!! OWNED TYPE bude v osobitnej TABLE.
			OwnedNavigationBuilder2.ToTable("OwnedType2");

			// !!! Ziska sa REFERENCE na NAVIGATION PROPERTY.
			NavigationBuilder<CEntityOwnedTypeInMultiTables,COwnedTypeDataAnnotations>	NavigationBuilder=Entity.Navigation(P => P.OwnedTypeDataAnnotationsRequired);

			// !!! OWNED TYPE PROPERTY sa nastavi ako REQUIRED.
			NavigationBuilder.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeOneAndMany(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedTypeOneAndMany>		Entity=ModelBuilder.Entity<CEntityOwnedTypeOneAndMany>();

			Entity.ToTable("EntitiesOwnedTypeOneAndMany");

			Entity.HasKey(P => P.EntityID);

			// !!!!! OWNED TYPE ENTITY to ONE sa nastavi pomocou FLUENT API.
			Entity.OwnsOne(P => P.OwnedTypeOne);

			// !!!!! OWNED TYPE ENTITY to MANY sa nastavi pomocou FLUENT API.
			// !!!!! OWNED TYPE ENTITY to MANY sa VZDY uklada do SEPARATNEJ TABLE.
			OwnedNavigationBuilder<CEntityOwnedTypeOneAndMany,COwnedTypeMany>	OwnedNavigationBuilder=Entity.OwnsMany(P => P.OwnedTypesMany);

			// !!!!! Pre OWNED TYPE ENTITY to MANY je potrebne na OWNED ENTITY definovat PRIMARY KEY.
			OwnedNavigationBuilder.HasKey(P => P.OwnedTypeID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTablePerHierarchyBaseConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTablePerHierarchyBaseConventions>	Entity=ModelBuilder.Entity<CEntityTablePerHierarchyBaseConventions>();

			Entity.ToTable("EntitiesTablePerHierarchyBaseConventions");

			Entity.HasKey(P => P.EntityID);

			EntityTypeBuilder<CEntityTablePerHierarchyDerived1Conventions>	EntityDerived1=ModelBuilder.Entity<CEntityTablePerHierarchyDerived1Conventions>();
			
			PropertyBuilder<string>								SharedPropertyDervied1=EntityDerived1.Property(P => P.DerivedValueInSharedColumn);

			// !!! PROPERTY bude odkazovat do toho isteho DB COLUMN.
			SharedPropertyDervied1.HasColumnName("My_SHARED_COLUMN");

			EntityTypeBuilder<CEntityTablePerHierarchyDerived2Conventions>	EntityDerived2=ModelBuilder.Entity<CEntityTablePerHierarchyDerived2Conventions>();

			PropertyBuilder<string>								SharedPropertyDervied2=EntityDerived2.Property(P => P.DerivedValueInSharedColumn);

			// !!! PROPERTY bude odkazovat do toho isteho DB COLUMN.
			SharedPropertyDervied2.HasColumnName("My_SHARED_COLUMN");

			PropertyBuilder<string>								SameNamePropertyDervied1=EntityDerived1.Property(P => P.DerivedValueWithSameName);

			// !!!!! Ak VIACERO DERIVED CLASSES obsahuje ROVNAKO pomenovanu PROPERTY, je NUTNE EXPLICITNE urcit DB COLUMN do ktoreho bude dana PROPERTY MAPPED.
			SameNamePropertyDervied1.HasColumnName("My_SAME_NAME_1");

			PropertyBuilder<string>								SameNamePropertyDervied2=EntityDerived2.Property(P => P.DerivedValueWithSameName);

			// !!!!! Ak VIACERO DERIVED CLASSES obsahuje ROVNAKO pomenovanu PROPERTY, je NUTNE EXPLICITNE urcit DB COLUMN do ktoreho bude dana PROPERTY MAPPED.
			SameNamePropertyDervied2.HasColumnName("My_SAME_NAME_2");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTablePerHierarchyBaseFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTablePerHierarchyBaseFluentAPI>	Entity=ModelBuilder.Entity<CEntityTablePerHierarchyBaseFluentAPI>();

			Entity.ToTable("EntitiesTablePerHierarchyBaseFluentAPI");

			Entity.HasKey(P => P.EntityID);

			// !!!!! Definuje sa DISCRIMINATOR PROPERTY.
			DiscriminatorBuilder<EDiscriminatorFluentAPI>		Discriminator=Entity.HasDiscriminator(P => P.Discriminator);

			// !!!!! Definuje sa DISCRIMINATOR VALUE pre ENTITY DERIVED CLASS.
			Discriminator.HasValue<CEntityTablePerHierarchyDerived1FluentAPI>(EDiscriminatorFluentAPI.E_DERIVED_1);

			// !!!!! Definuje sa DISCRIMINATOR VALUE pre ENTITY DERIVED CLASS.
			Discriminator.HasValue<CEntityTablePerHierarchyDerived2FluentAPI>(EDiscriminatorFluentAPI.E_DERIVED_2);

			EntityTypeBuilder<CEntityTablePerHierarchyDerived1FluentAPI>	EntityDerived1=ModelBuilder.Entity<CEntityTablePerHierarchyDerived1FluentAPI>();
			
			PropertyBuilder<string>								SharedPropertyDervied1=EntityDerived1.Property(P => P.DerivedValueInSharedColumn);

			// !!! PROPERTY bude odkazovat do toho isteho DB COLUMN.
			SharedPropertyDervied1.HasColumnName("My_SHARED_COLUMN");

			EntityTypeBuilder<CEntityTablePerHierarchyDerived2FluentAPI>	EntityDerived2=ModelBuilder.Entity<CEntityTablePerHierarchyDerived2FluentAPI>();

			PropertyBuilder<string>								SharedPropertyDervied2=EntityDerived2.Property(P => P.DerivedValueInSharedColumn);

			// !!! PROPERTY bude odkazovat do toho isteho DB COLUMN.
			SharedPropertyDervied2.HasColumnName("My_SHARED_COLUMN");

			PropertyBuilder<string>								SameNamePropertyDervied1=EntityDerived1.Property(P => P.DerivedValueWithSameName);

			// !!!!! Ak VIACERO DERIVED CLASSES obsahuje ROVNAKO pomenovanu PROPERTY, je NUTNE EXPLICITNE urcit DB COLUMN do ktoreho bude dana PROPERTY MAPPED.
			SameNamePropertyDervied1.HasColumnName("My_SAME_NAME_1");

			PropertyBuilder<string>								SameNamePropertyDervied2=EntityDerived2.Property(P => P.DerivedValueWithSameName);

			// !!!!! Ak VIACERO DERIVED CLASSES obsahuje ROVNAKO pomenovanu PROPERTY, je NUTNE EXPLICITNE urcit DB COLUMN do ktoreho bude dana PROPERTY MAPPED.
			SameNamePropertyDervied2.HasColumnName("My_SAME_NAME_2");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTablePerTypeBaseFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTablePerTypeBaseFluentAPI>	Entity=ModelBuilder.Entity<CEntityTablePerTypeBaseFluentAPI>();

			Entity.ToTable("EntitiesTablePerTypeBaseFluentAPI");

			Entity.HasKey(P => P.EntityID);

			// !!! Ziska sa ENTITY DERIVED TYPE.
			EntityTypeBuilder<CEntityTablePerTypeDerived1FluentAPI>	EntityDerived1=ModelBuilder.Entity<CEntityTablePerTypeDerived1FluentAPI>();

			// !!!!! Nastavi sa nazov TABLE pre DERIVED TYPE.
			EntityDerived1.ToTable("EntitiesTablePerTypeDerived1FluentAPI");

			// !!! Ziska sa ENTITY DERIVED TYPE.
			EntityTypeBuilder<CEntityTablePerTypeDerived2FluentAPI>	EntityDerived2=ModelBuilder.Entity<CEntityTablePerTypeDerived2FluentAPI>();

			// !!!!! Nastavi sa nazov TABLE pre DERIVED TYPE.
			EntityDerived2.ToTable("EntitiesTablePerTypeDerived2FluentAPI");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTableSplittingPrincipalFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTableSplittingPrincipalFluentAPI>	Entity=ModelBuilder.Entity<CEntityTableSplittingPrincipalFluentAPI>();

			// !!!!! PRINCIPAL ENTITY MUSI byt MAPPED do tej iste TABLE ako DEPENDENT ENTITIES.
			Entity.ToTable(TABLE_SPLITTING_TABLE_NAME);

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! Vytvori sa 1:1 RELATIONSHIP medzi ENTITY 'CEntityTableSplittingPrincipalFluentAPI' a ENTITY 'CEntityTableSplittingDependent1FluentAPI'.

			// !!!!! PRIMARY KEY DEPENDENT ENTITY je zaroven aj FOREIGN KEY do PRINCIPAL ENTITY.
			Entity.HasOne(P => P.EntityDependent1).WithOne(P => P.EntityPrincipal).HasForeignKey<CEntityTableSplittingDependent1FluentAPI>(P => P.EntityDependentID);

			// !!!!! Vytvori sa 1:1 RELATIONSHIP medzi ENTITY 'CEntityTableSplittingPrincipalFluentAPI' a ENTITY 'CEntityTableSplittingDependent2FluentAPI'.

			// !!!!! PRIMARY KEY DEPENDENT ENTITY je zaroven aj FOREIGN KEY do PRINCIPAL ENTITY.
			Entity.HasOne(P => P.EntityDependent2).WithOne(P => P.EntityPrincipal).HasForeignKey<CEntityTableSplittingDependent2FluentAPI>(P => P.EntityDependentID);

			// !!!!! Ak DEPENDENT ENTITY nema ziadnu NON-NULLABLE PROPERTY, ENTITY FRAMEWORK CORE NEDOKAZE rozlisit kedy je cela DEPENDENT ENTITY NULL a nema pre nu vytvarat instanciu DEPENDENT ENTITY CLASS. ENTITY FRAMEWORK CORE totizto BY-DEFAULT povazuje celu DEPENDENT ENTITY za NULL, ak su vsetky jej PROPERTIES NULL a vtedy nevytvara instanciu DEPENDENT ENTITY CLASS. Ak vsak ani jedna PROPERTY DEPENDENT ENTITY nie je NON-NULLABLE, ENTITY FRAMEWORK CORE nedokaze toto rozlisenie spravit. Riesenim je pridanie NON-NULLABLE PROPERTY, alebo oznacenie niektorej z BY-DEFAULT NULLABLE PROPERTY za REQUIRED PROPERTY. Alternativou je oznacit NAVIGATION PROPERTY za REQUIRED.
			Entity.Navigation(P => P.EntityDependent1).IsRequired(true);

			// !!!!! Ak DEPENDENT ENTITY nema ziadnu NON-NULLABLE PROPERTY, ENTITY FRAMEWORK CORE NEDOKAZE rozlisit kedy je cela DEPENDENT ENTITY NULL a nema pre nu vytvarat instanciu DEPENDENT ENTITY CLASS. ENTITY FRAMEWORK CORE totizto BY-DEFAULT povazuje celu DEPENDENT ENTITY za NULL, ak su vsetky jej PROPERTIES NULL a vtedy nevytvara instanciu DEPENDENT ENTITY CLASS. Ak vsak ani jedna PROPERTY DEPENDENT ENTITY nie je NON-NULLABLE, ENTITY FRAMEWORK CORE nedokaze toto rozlisenie spravit. Riesenim je pridanie NON-NULLABLE PROPERTY, alebo oznacenie niektorej z BY-DEFAULT NULLABLE PROPERTY za REQUIRED PROPERTY. Alternativou je oznacit NAVIGATION PROPERTY za REQUIRED.
			Entity.Navigation(P => P.EntityDependent2).IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTableSplittingDependent1FluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTableSplittingDependent1FluentAPI>	Entity=ModelBuilder.Entity<CEntityTableSplittingDependent1FluentAPI>();

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! DEPENDENT ENTITY bude MAPPED do tej iste ENTITY ako PRINCIPAL ENTITY.
			Entity.ToTable(TABLE_SPLITTING_TABLE_NAME);

			// !!!!! PROPERTY sa nastavi aby ukazovala do toho isteho DB COLUMN.
			Entity.Property(P => P.EntitySharedValue).HasColumnName(TABLE_SPLITTING_COLUMN_NAME);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityTableSplittingDependent2FluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityTableSplittingDependent2FluentAPI>	Entity=ModelBuilder.Entity<CEntityTableSplittingDependent2FluentAPI>();

			Entity.HasKey(P => P.EntityDependentID);

			// !!!!! DEPENDENT ENTITY bude MAPPED do tej iste ENTITY ako PRINCIPAL ENTITY.
			Entity.ToTable(TABLE_SPLITTING_TABLE_NAME);

			// !!!!! PROPERTY sa nastavi aby ukazovala do toho isteho DB COLUMN.
			Entity.Property(P => P.EntitySharedValue).HasColumnName(TABLE_SPLITTING_COLUMN_NAME);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureMyPropertyBagPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<Dictionary<string,object>>		Entity=ModelBuilder.SharedTypeEntity<Dictionary<string,object>>(CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_TABLE_NAME);

			// !!!!! DYNAMICKY sa vytvori PROPERTY v PROPERTY BAG.
			Entity.IndexerProperty<int>(CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID);

			// !!!!! PROPERTY sa nastavi ako PRIMARY KEY.
			Entity.HasKey(CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID);

			// !!!!! DYNAMICKY sa vytvori PROPERTY v PROPERTY BAG.
			Entity.IndexerProperty<int>(CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_INT);

			// !!!!! DYNAMICKY sa vytvori PROPERTY v PROPERTY BAG.
			Entity.IndexerProperty<string>(CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_VALUE_STRING);

			// !!!!! Nakonfiguruje sa RELATIONSHIP 1:N.

			// !!!!! Nastavi sa LEFT SIDE RELATIONSHIP 1:N.
			CollectionNavigationBuilder<Dictionary<string,object>,CEntityPropertyBagDependentFluentAPI>	LeftSide=Entity.HasMany<CEntityPropertyBagDependentFluentAPI>((string) null);

			// !!!!! Nastavi sa RIGHT SIDE RELATIONSHIP 1:N.
			ReferenceCollectionBuilder<Dictionary<string,object>,CEntityPropertyBagDependentFluentAPI>	RightSide=LeftSide.WithOne();

			// !!!!! Nastavi sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityPropertyBagDependentFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityPropertyBagDependentFluentAPI>	Entity=ModelBuilder.Entity<CEntityPropertyBagDependentFluentAPI>();

			Entity.ToTable("EntitiesPropertyBagDependentFluentAPI");

			Entity.HasKey(P => P.EntityDependentID);
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
			ConfigureEntityOneToOnePrincipalConventions(ModelBuilder);
			ConfigureEntityOneToOneDependentConventions(ModelBuilder);
			ConfigureEntityZeroToOnePrincipalConventions(ModelBuilder);
			ConfigureEntityZeroToOneDependentConventions(ModelBuilder);
			ConfigureEntityOneToManyPrincipalConventions(ModelBuilder);
			ConfigureEntityOneToManyDependentConventions(ModelBuilder);
			ConfigureEntityZeroToManyPrincipalConventions(ModelBuilder);
			ConfigureEntityZeroToManyDependentConventions(ModelBuilder);
			ConfigureEntityForeignKeyName1PrincipalConventions(ModelBuilder);
			ConfigureEntityForeignKeyName1DependentConventions(ModelBuilder);
			ConfigureEntityForeignKeyName2PrincipalConventions(ModelBuilder);
			ConfigureEntityForeignKeyName2DependentConventions(ModelBuilder);
			ConfigureEntityForeignKeyName3PrincipalConventions(ModelBuilder);
			ConfigureEntityForeignKeyName3DependentConventions(ModelBuilder);
			ConfigureEntityNoForeignKey1PrincipalConventions(ModelBuilder);
			ConfigureEntityNoForeignKey1DependentConventions(ModelBuilder);
			ConfigureEntityNoForeignKey2PrincipalConventions(ModelBuilder);
			ConfigureEntityNoForeignKey2DependentConventions(ModelBuilder);
			ConfigureEntityNoForeignKey3PrincipalConventions(ModelBuilder);
			ConfigureEntityNoForeignKey3DependentConventions(ModelBuilder);
			ConfigureEntityOneToOnePrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityOneToOneDependentDataAnnotations(ModelBuilder);
			ConfigureEntityZeroToOnePrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityZeroToOneDependentDataAnnotations(ModelBuilder);
			ConfigureEntityOneToManyPrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityOneToManyDependentDataAnnotations(ModelBuilder);
			ConfigureEntityZeroToManyPrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityZeroToManyDependentDataAnnotations(ModelBuilder);
			ConfigureEntityAttributeOnNavigationPropertyPrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityAttributeOnNavigationPropertyDependentDataAnnotations(ModelBuilder);
			ConfigureEntityAttributeOnForeignKeyPrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityAttributeOnForeignKeyDependentDataAnnotations(ModelBuilder);
			ConfigureEntityCompositeForeignKeyPrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityCompositeForeignKeyDependentDataAnnotations(ModelBuilder);
			ConfigureEntityInversePropertyPrincipalDataAnnotations(ModelBuilder);
			ConfigureEntityInversePropertyDependentDataAnnotations(ModelBuilder);
			ConfigureEntityOneToOne1PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOneToOne1DependentFluentAPI(ModelBuilder);
			ConfigureEntityOneToOne2PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOneToOne2DependentFluentAPI(ModelBuilder);
			ConfigureEntityZeroToOne1PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityZeroToOne1DependentFluentAPI(ModelBuilder);
			ConfigureEntityZeroToOne2PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityZeroToOne2DependentFluentAPI(ModelBuilder);
			ConfigureEntityOneToOneMixedKeys1PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOneToOneMixedKeys1DependentFluentAPI(ModelBuilder);
			ConfigureEntityOneToOneMixedKeys2PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOneToOneMixedKeys2DependentFluentAPI(ModelBuilder);
			ConfigureEntityOneToMany1PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOneToMany1DependentFluentAPI(ModelBuilder);
			ConfigureEntityOneToMany2PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOneToMany2DependentFluentAPI(ModelBuilder);
			ConfigureEntityZeroToMany1PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityZeroToMany1DependentFluentAPI(ModelBuilder);
			ConfigureEntityZeroToMany2PrincipalFluentAPI(ModelBuilder);
			ConfigureEntityZeroToMany2DependentFluentAPI(ModelBuilder);
			ConfigureEntityManyToMany1MFluentAPI(ModelBuilder);
			ConfigureEntityManyToMany1NFluentAPI(ModelBuilder);
			ConfigureEntityManyToMany1MNFluentAPI(ModelBuilder);
			ConfigureEntityManyToMany2MFluentAPI(ModelBuilder);
			ConfigureEntityManyToMany2NFluentAPI(ModelBuilder);
			ConfigureEntityManyToMany2MNFluentAPI(ModelBuilder);
			ConfigureEntityZeroManyToMany1MFluentAPI(ModelBuilder);
			ConfigureEntityZeroManyToMany1NFluentAPI(ModelBuilder);
			ConfigureEntityZeroManyToMany1MNFluentAPI(ModelBuilder);
			ConfigureEntityZeroManyToMany2MFluentAPI(ModelBuilder);
			ConfigureEntityZeroManyToMany2NFluentAPI(ModelBuilder);
			ConfigureEntityZeroManyToMany2MNFluentAPI(ModelBuilder);
			ConfigureEntityManyToManyMixedKeys1MFluentAPI(ModelBuilder);
			ConfigureEntityManyToManyMixedKeys1NFluentAPI(ModelBuilder);
			ConfigureEntityManyToManyMixedKeys1MNFluentAPI(ModelBuilder);
			ConfigureEntityManyToManyMixedKeys2MFluentAPI(ModelBuilder);
			ConfigureEntityManyToManyMixedKeys2NFluentAPI(ModelBuilder);
			ConfigureEntityManyToManyMixedKeys2MNFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToMany1MFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToMany1NFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToMany2MFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToMany2NFluentAPI(ModelBuilder);
			ConfigureEntityAutoZeroManyToMany1MFluentAPI(ModelBuilder);
			ConfigureEntityAutoZeroManyToMany1NFluentAPI(ModelBuilder);
			ConfigureEntityAutoZeroManyToMany2MFluentAPI(ModelBuilder);
			ConfigureEntityAutoZeroManyToMany2NFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToManyMixedKeys1MFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToManyMixedKeys1NFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToManyMixedKeys2MFluentAPI(ModelBuilder);
			ConfigureEntityAutoManyToManyMixedKeys2NFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteNoActionNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteNoActionNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteNoActionNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteNoActionNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientNoActionNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientNoActionNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientNoActionNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteRestrictNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteRestrictNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteRestrictNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteRestrictNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteSetNullNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteSetNullNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteSetNullNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteSetNullNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientSetNullNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientSetNullNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientSetNullNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteCascadeNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteCascadeNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteCascadeNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteCascadeNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientCascadeNotNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientCascadeNullPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityOnDeleteClientCascadeNullDependentFluentAPI(ModelBuilder);
			ConfigureEntityRequiredTruePrincipalFluentAPI(ModelBuilder);
			ConfigureEntityRequiredTrueDependentFluentAPI(ModelBuilder);
			ConfigureEntityRequiredFalsePrincipalFluentAPI(ModelBuilder);
			ConfigureEntityRequiredFalseDependentFluentAPI(ModelBuilder);
			ConfigureEntityHasAlternateKeyFluentAPI(ModelBuilder);
			ConfigureEntityHasAlternateKeyCompositeFluentAPI(ModelBuilder);
			ConfigureEntityHasPrincipalKeyPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityHasPrincipalKeyDependentFluentAPI(ModelBuilder);
			ConfigureEntityHasPrincipalKeyCompositePrincipalFluentAPI(ModelBuilder);
			ConfigureEntityHasPrincipalKeyCompositeDependentFluentAPI(ModelBuilder);
			ConfigureEntityHasConstraintNamePrincipalFluentAPI(ModelBuilder);
			ConfigureEntityHasConstraintNameDependentFluentAPI(ModelBuilder);
			ConfigureEntityOwnedTypeInOneTable(ModelBuilder);
			ConfigureEntityOwnedTypeInMultiTables(ModelBuilder);
			ConfigureEntityOwnedTypeOneAndMany(ModelBuilder);
			ConfigureEntityTablePerHierarchyBaseConventions(ModelBuilder);
			ConfigureEntityTablePerHierarchyBaseFluentAPI(ModelBuilder);
			ConfigureEntityTablePerTypeBaseFluentAPI(ModelBuilder);
			ConfigureEntityTableSplittingPrincipalFluentAPI(ModelBuilder);
			ConfigureEntityTableSplittingDependent1FluentAPI(ModelBuilder);
			ConfigureEntityTableSplittingDependent2FluentAPI(ModelBuilder);
			ConfigureMyPropertyBagPrincipal(ModelBuilder);
			ConfigureEntityPropertyBagDependentFluentAPI(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------