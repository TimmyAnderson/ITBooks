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
namespace NonrelationalProperties
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
		private DbSet<CEntityDifferentConfigurations>			MEntitiesDifferentConfigurations;
		private DbSet<CEntityNotMappedDataAnnotations>			MEntitiesNotMappedDataAnnotations;
		private DbSet<CEntityNotMappedFluentAPI>				MEntitiesNotMappedFluentAPI;
		private DbSet<CEntityColumnPropertiesDataAnnotations>	MEntitiesColumnPropertiesDataAnnotations;
		private DbSet<CEntityColumnPropertiesFluentAPI>			MEntitiesColumnPropertiesFluentAPI;
		private DbSet<CEntityUsingValueConversions>				MEntitiesUsingValueConversions;
		private DbSet<CEntityPrimaryKeyConventions>				MEntitiesPrimaryKeyConventions;
		private DbSet<CEntityPrimaryKeyDataAnnotations>			MEntitiesPrimaryKeyDataAnnotations;
		private DbSet<CEntityPrimaryKeyFluentAPI>				MEntitiesPrimaryKeyFluentAPI;
		private DbSet<CEntityDataForKeylessView>				MEntitiesDataForKeylessView;
		private DbSet<CEntityKeylessDataAnnotations>			MEntitiesKeylessDataAnnotations;
		private DbSet<CEntityKeylessFluentAPI>					MEntitiesKeylessFluentAPI;
		private DbSet<CEntityIndexesDataAnnotations>			MEntitiesIndexesDataAnnotations;
		private DbSet<CEntityIndexesFluentAPI>					MEntitiesIndexesFluentAPI;
		private DbSet<CEntityCustomNamesDataAnnotations>		MEntitiesCustomNamesDataAnnotations;
		private DbSet<CEntityCustomNamesFluentAPI>				MEntitiesCustomNamesFluentAPI;
		private DbSet<CEntityQueryFilter>						MEntitiesQueryFilter;
		private DbSet<CEntityShadowProperties>					MEntitiesShadowProperties;
		private DbSet<CEntityBackingFieldsConventions>			MEntitiesBackingFieldsConventions;
		private DbSet<CEntityBackingFieldsDataAnnotations>		MEntitiesBackingFieldsDataAnnotations;
		private DbSet<CEntityBackingFieldsFluentAPI>			MEntitiesBackingFieldsFluentAPI;
		private DbSet<CEntityBackingFieldsAccessModes>			MEntitiesBackingFieldsAccessModes;
		private DbSet<CEntityAutoConfiguration1>				MEntitiesAutoConfiguration1;
		private DbSet<CEntityAutoConfiguration2>				MEntitiesAutoConfiguration2;
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
		public DbSet<CEntityDifferentConfigurations>			EntitiesDifferentConfigurations
		{
			get
			{
				return(MEntitiesDifferentConfigurations);
			}
			set
			{
				MEntitiesDifferentConfigurations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNotMappedDataAnnotations>			EntitiesNotMappedDataAnnotations
		{
			get
			{
				return(MEntitiesNotMappedDataAnnotations);
			}
			set
			{
				MEntitiesNotMappedDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityNotMappedFluentAPI>					EntitiesNotMappedFluentAPI
		{
			get
			{
				return(MEntitiesNotMappedFluentAPI);
			}
			set
			{
				MEntitiesNotMappedFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityColumnPropertiesDataAnnotations>	EntitiesColumnPropertiesDataAnnotations
		{
			get
			{
				return(MEntitiesColumnPropertiesDataAnnotations);
			}
			set
			{
				MEntitiesColumnPropertiesDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityColumnPropertiesFluentAPI>			EntitiesColumnPropertiesFluentAPI
		{
			get
			{
				return(MEntitiesColumnPropertiesFluentAPI);
			}
			set
			{
				MEntitiesColumnPropertiesFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityUsingValueConversions>				EntitiesUsingValueConversions
		{
			get
			{
				return(MEntitiesUsingValueConversions);
			}
			set
			{
				MEntitiesUsingValueConversions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPrimaryKeyConventions>				EntitiesPrimaryKeyConventions
		{
			get
			{
				return(MEntitiesPrimaryKeyConventions);
			}
			set
			{
				MEntitiesPrimaryKeyConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPrimaryKeyDataAnnotations>			EntitiesPrimaryKeyDataAnnotations
		{
			get
			{
				return(MEntitiesPrimaryKeyDataAnnotations);
			}
			set
			{
				MEntitiesPrimaryKeyDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPrimaryKeyFluentAPI>				EntitiesPrimaryKeyFluentAPI
		{
			get
			{
				return(MEntitiesPrimaryKeyFluentAPI);
			}
			set
			{
				MEntitiesPrimaryKeyFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataForKeylessView>					EntitiesDataForKeylessView
		{
			get
			{
				return(MEntitiesDataForKeylessView);
			}
			set
			{
				MEntitiesDataForKeylessView=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityKeylessDataAnnotations>				EntitiesKeylessDataAnnotations
		{
			get
			{
				return(MEntitiesKeylessDataAnnotations);
			}
			set
			{
				MEntitiesKeylessDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityKeylessFluentAPI>					EntitiesKeylessFluentAPI
		{
			get
			{
				return(MEntitiesKeylessFluentAPI);
			}
			set
			{
				MEntitiesKeylessFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityIndexesDataAnnotations>				EntitiesIndexesDataAnnotations
		{
			get
			{
				return(MEntitiesIndexesDataAnnotations);
			}
			set
			{
				MEntitiesIndexesDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityIndexesFluentAPI>					EntitiesIndexesFluentAPI
		{
			get
			{
				return(MEntitiesIndexesFluentAPI);
			}
			set
			{
				MEntitiesIndexesFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityCustomNamesDataAnnotations>			EntitiesCustomNamesDataAnnotations
		{
			get
			{
				return(MEntitiesCustomNamesDataAnnotations);
			}
			set
			{
				MEntitiesCustomNamesDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityCustomNamesFluentAPI>				EntitiesCustomNamesFluentAPI
		{
			get
			{
				return(MEntitiesCustomNamesFluentAPI);
			}
			set
			{
				MEntitiesCustomNamesFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityQueryFilter>						EntitiesQueryFilter
		{
			get
			{
				return(MEntitiesQueryFilter);
			}
			set
			{
				MEntitiesQueryFilter=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityShadowProperties>					EntitiesShadowProperties
		{
			get
			{
				return(MEntitiesShadowProperties);
			}
			set
			{
				MEntitiesShadowProperties=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityBackingFieldsConventions>			EntitiesBackingFieldsConventions
		{
			get
			{
				return(MEntitiesBackingFieldsConventions);
			}
			set
			{
				MEntitiesBackingFieldsConventions=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityBackingFieldsDataAnnotations>		EntitiesBackingFieldsDataAnnotations
		{
			get
			{
				return(MEntitiesBackingFieldsDataAnnotations);
			}
			set
			{
				MEntitiesBackingFieldsDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityBackingFieldsFluentAPI>				EntitiesBackingFieldsFluentAPI
		{
			get
			{
				return(MEntitiesBackingFieldsFluentAPI);
			}
			set
			{
				MEntitiesBackingFieldsFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityBackingFieldsAccessModes>			EntitiesBackingFieldsAccessModes
		{
			get
			{
				return(MEntitiesBackingFieldsAccessModes);
			}
			set
			{
				MEntitiesBackingFieldsAccessModes=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoConfiguration1>					EntitiesAutoConfiguration1
		{
			get
			{
				return(MEntitiesAutoConfiguration1);
			}
			set
			{
				MEntitiesAutoConfiguration1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityAutoConfiguration2>					EntitiesAutoConfiguration2
		{
			get
			{
				return(MEntitiesAutoConfiguration2);
			}
			set
			{
				MEntitiesAutoConfiguration2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static string ConvertEnumToString(EEnumType Value)
		{
			string												ConvertedValue=Value.ToString();

			return(ConvertedValue);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static EEnumType ConvertStringToEnum(string Value)
		{
			EEnumType											ConvertedValue=Enum.Parse<EEnumType>(Value);

			return(ConvertedValue);
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
		private void ConfigureEntityDifferentConfigurations(ModelBuilder ModelBuilder)
		{
			// !!!!! CONFIGURATION je presunuta do separatnej CLASS.
			ModelBuilder.ApplyConfiguration(new CEntityDifferentConfigurationsConfig());
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNotMappedDataAnnotations(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityNotMappedDataAnnotations>().ToTable("EntitiesNotMappedDataAnnotations");

			ModelBuilder.Entity<CEntityNotMappedDataAnnotations>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNotMappedFluentAPI(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityNotMappedFluentAPI>().ToTable("EntitiesNotMappedFluentAPI");

			ModelBuilder.Entity<CEntityNotMappedFluentAPI>().HasKey(P => P.ID);

			// !!! PROPERTY NEBUDE MAPPED do DB.
			ModelBuilder.Entity<CEntityNotMappedFluentAPI>().Ignore(P => P.ExcludedPropertyValue);

			// !!! CLASS NEBUDE MAPPED do DB.
			ModelBuilder.Ignore<CEntityExcludedFluentAPI>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNotExcluded(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityNotExcluded>().ToTable("EntitiesNotExcluded");

			ModelBuilder.Entity<CEntityNotExcluded>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityColumnPropertiesDataAnnotations(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityColumnPropertiesDataAnnotations>().ToTable("EntitiesColumnPropertiesDataAnnotations");

			ModelBuilder.Entity<CEntityColumnPropertiesDataAnnotations>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityColumnPropertiesFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityColumnPropertiesFluentAPI>	Entity=ModelBuilder.Entity<CEntityColumnPropertiesFluentAPI>();

			Entity.ToTable("EntitiesColumnPropertiesFluentAPI");

			Entity.HasKey(P => P.ID);

			// !!! PROPERTY je REQUIRED.
			Entity.Property(P => P.StringNonNull).IsRequired();

			// !!! PROPERTY ma MAX LENGTH.
			Entity.Property(P => P.StringWithMaxLength).HasMaxLength(50);

			// !!! PROPERTY ma SQL TYPE nastaveny na 'DATE'.
			Entity.Property(P => P.DateTimeWithSQLTypeDATE).HasColumnType("date");

			// !!! PROPERTY ma SQL NAME nastaveny na 'My_IntRenamed'.
			Entity.Property(P => P.IntRenamed).HasColumnName("My_IntRenamed");

			// !!! PROPERTY nie je TYPE 'UNICODE'.
			Entity.Property(P => P.StringNonUnicode).IsUnicode(false);

			// !!! PROPERTY ma nastavenu PRECISION.
			Entity.Property(P => P.DoubleWithLimitedPrecision).HasPrecision(9,2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityUsingValueConversions(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityUsingValueConversions>().ToTable("EntitiesUsingValueConversions");

			ModelBuilder.Entity<CEntityUsingValueConversions>().HasKey(P => P.ID);

			Expression<Func<EEnumType,string>>					ConversionClrTypeToDbType=(P => ConvertEnumToString(P));
			Expression<Func<string,EEnumType>>					ConversionDbTypeToClrType=(P => ConvertStringToEnum(P));

			// !!! Nastavia sa CONVERSION METHODS pre PROPERTY 'EnumTypeWithConversion1', ktory sa bude ukladat nie ako NUMBER, ale ako STRING.
			ModelBuilder.Entity<CEntityUsingValueConversions>().Property(P => P.EnumTypeWithConversion1).HasConversion(ConversionClrTypeToDbType,ConversionDbTypeToClrType);

			// !!! Nastavia sa CONVERSION METHODS pre PROPERTY 'EnumTypeWithConversion2', ktory sa bude ukladat nie ako NUMBER, ale ako STRING.
			// !!! CONVERSION sa vykona pomocou implementacie CONVERSION CLASS.
			ModelBuilder.Entity<CEntityUsingValueConversions>().Property(P => P.EnumTypeWithConversion2).HasConversion(new CEnumToStringValueConverter());
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityPrimaryKeyConventions(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityPrimaryKeyConventions>().ToTable("EntitiesPrimaryKeyConventions");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityPrimaryKeyDataAnnotations(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityPrimaryKeyDataAnnotations>().ToTable("EntitiesPrimaryKeyDataAnnotations");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityPrimaryKeyFluentAPI(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityPrimaryKeyFluentAPI>().ToTable("EntitiesPrimaryKeyFluentAPI");

			// !!! ENTITY CLASS ma definovany COMPOSITE PRIMARY KEY BY FLUENT API.
			ModelBuilder.Entity<CEntityPrimaryKeyFluentAPI>().HasKey(nameof(CEntityPrimaryKeyFluentAPI.ID1),nameof(CEntityPrimaryKeyFluentAPI.ID2));
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDataForKeylessView(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityDataForKeylessView>().ToTable("EntitiesDataForKeylessView");

			ModelBuilder.Entity<CEntityDataForKeylessView>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityKeylessDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityKeylessDataAnnotations>	Entity=ModelBuilder.Entity<CEntityKeylessDataAnnotations>();

			// !!!!! KEYLESS ENTITY je MAPPED na vytvoreny VIEW.
			Entity.ToView("View_Keyless1");

			Entity.Property(P => P.IntValue).HasColumnName("MyInt");
			Entity.Property(P => P.StringValue).HasColumnName("MyString");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityKeylessFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityKeylessFluentAPI>			Entity=ModelBuilder.Entity<CEntityKeylessFluentAPI>();

			// !!!!! KEYLESS ENTITY je MAPPED na vytvoreny VIEW.
			Entity.ToView("View_Keyless2");

			Entity.Property(P => P.IntValue).HasColumnName("MyInt");
			Entity.Property(P => P.StringValue).HasColumnName("MyString");

			// !!!!! ENTITY CLASS sa nastavi ako KEYLESS.
			Entity.HasNoKey();
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityIndexesDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityIndexesDataAnnotations>	Entity=ModelBuilder.Entity<CEntityIndexesDataAnnotations>();

			Entity.HasKey(P => P.ID);

			Entity.ToTable("EntitiesIndexesDataAnnotations");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityIndexesFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityIndexesFluentAPI>			Entity=ModelBuilder.Entity<CEntityIndexesFluentAPI>();

			Entity.ToTable("EntitiesIndexesFluentAPI");

			Entity.HasKey(P => P.ID);

			// !!! Nastavi sa SINGLE COLUMN INDEX.
			Entity.HasIndex(P => P.SingleColumnIndex).HasDatabaseName("My_SingleColumnIndex_FluentAPI");

			// !!! Nastavi sa MULTI COLUMN UNIQUE INDEX.
			Entity.HasIndex(nameof(CEntityIndexesFluentAPI.MultiColumnIndex1),nameof(CEntityIndexesFluentAPI.MultiColumnIndex2)).HasDatabaseName("My_MultiColumnIndex_FluentAPI").IsUnique(true);

			// !!! Nastavi sa SINGLE COLUMN UNIQUE INDEX.
			Entity.HasIndex(P => P.SingleColumnUniqueIndex).HasDatabaseName("My_SingleColumnUniqueIndex_FluentAPI").IsUnique(true);

			// !!! Nastavi sa SINGLE COLUMN FILTERED INDEX.
			Entity.HasIndex(P => P.SingleColumnFilteredIndex).HasDatabaseName("My_SingleColumnFilteredIndex_FluentAPI").HasFilter("SingleColumnFilteredIndex>1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityCustomNamesDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityCustomNamesDataAnnotations>	Entity=ModelBuilder.Entity<CEntityCustomNamesDataAnnotations>();

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityCustomNamesFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityCustomNamesFluentAPI>		Entity=ModelBuilder.Entity<CEntityCustomNamesFluentAPI>();

			// !!! TABLE ma nastaveny CUSTOM NAME a CUSTOM SCHEMA.
			Entity.ToTable("My_EntityCustomNamesFluentAPI","My_Schema");

			Entity.HasKey(P => P.ID);

			// !!! COLUMN ma nastaveny CUSTOM NAME.
			Entity.Property(P => P.Value).HasColumnName("My_Value");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityQueryFilter(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityQueryFilter>				Entity=ModelBuilder.Entity<CEntityQueryFilter>();

			Entity.ToTable("EntitiesQueryFilter");

			Entity.HasKey(P => P.ID);

			// !!!!! Nastavi sa FILTER, ktory sa aplikuje na KAZDU QUERY, ktora nepouzije METHOD [IQueryable<TEntity> IQueryable<TEntity>.IgnoreQueryFilters<TEntity>()].
			Entity.HasQueryFilter(P => P.Value>3);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityShadowProperties(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityShadowProperties>			Entity=ModelBuilder.Entity<CEntityShadowProperties>();

			Entity.ToTable("EntitiesShadowProperties");

			Entity.HasKey(P => P.ID);

			// !!! DEFINUJE sa SHADOW PROPERTY.
			Entity.Property<string>("ShadowPropertyString").HasColumnName("My_ShadowPropertyString");

			// !!! DEFINUJE sa SHADOW PROPERTY.
			Entity.Property<int>("ShadowPropertyInt").HasColumnName("My_ShadowPropertyInt");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityBackingFieldsConventions(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityBackingFieldsConventions>	Entity=ModelBuilder.Entity<CEntityBackingFieldsConventions>();

			Entity.ToTable("EntitiesBackingFieldsConventions");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityBackingFieldsDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityBackingFieldsDataAnnotations>	Entity=ModelBuilder.Entity<CEntityBackingFieldsDataAnnotations>();

			Entity.ToTable("EntitiesBackingFieldsDataAnnotations");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityBackingFieldsFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityBackingFieldsFluentAPI>	Entity=ModelBuilder.Entity<CEntityBackingFieldsFluentAPI>();

			Entity.ToTable("EntitiesBackingFieldsFluentAPI");

			Entity.HasKey(P => P.ID);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD.
			Entity.Property(P => P.BackingField1).HasField("MBackingField1").HasColumnName("My_BackingField1");

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD.
			Entity.Property(P => P.BackingField2).HasField("MBackingField2").HasColumnName("My_BackingField2");

			// !!!!! Kedze pre FIELD NEEXISTUJE C# PROPERTY, vytvori sa ENTITY PROPERTY, ktora ma ROVNAKY NAME, ako BACKING FIELD.
			Entity.Property<string>("MBackingField3").HasColumnName("My_BackingField3");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityBackingFieldsAccessModes(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityBackingFieldsAccessModes>	Entity=ModelBuilder.Entity<CEntityBackingFieldsAccessModes>();

			Entity.ToTable("EntitiesBackingFieldsAccessModes");

			Entity.HasKey(P => P.ID);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD a ACCESS MODE.
			Entity.Property(P => P.BackingFieldField).HasField("MBackingFieldField").HasColumnName("My_BackingFieldField").UsePropertyAccessMode(PropertyAccessMode.Field);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD a ACCESS MODE.
			Entity.Property(P => P.BackingFieldFieldDuringConstruction).HasField("MBackingFieldFieldDuringConstruction").HasColumnName("My_BackingFieldFieldDuringConstruction").UsePropertyAccessMode(PropertyAccessMode.FieldDuringConstruction);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD a ACCESS MODE.
			Entity.Property(P => P.BackingFieldProperty).HasField("MBackingFieldProperty").HasColumnName("My_BackingFieldProperty").UsePropertyAccessMode(PropertyAccessMode.Property);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD a ACCESS MODE.
			Entity.Property(P => P.BackingFieldPreferField).HasField("MBackingFieldPreferField").HasColumnName("My_BackingFieldPreferField").UsePropertyAccessMode(PropertyAccessMode.PreferField);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD a ACCESS MODE.
			Entity.Property(P => P.BackingFieldPreferFieldDuringConstruction).HasField("MBackingFieldPreferFieldDuringConstruction").HasColumnName("My_BackingFieldPreferFieldDuringConstruction").UsePropertyAccessMode(PropertyAccessMode.PreferFieldDuringConstruction);

			// !!! Pre C# PROPERTY sa nastavi BACKING FIELD a ACCESS MODE.
			Entity.Property(P => P.BackingFieldPreferProperty).HasField("MBackingFieldPreferProperty").HasColumnName("My_BackingFieldPreferProperty").UsePropertyAccessMode(PropertyAccessMode.PreferProperty);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Vykonava sa AUTO CONFIGURATION pomocou INTERFACE [IMutableModel].
		private void AutoConfigureEntities(ModelBuilder ModelBuilder)
		{
			IMutableModel										Model=ModelBuilder.Model;
			IMutableEntityType[]								EntityTypes=Model.GetEntityTypes().ToArray();

			foreach(IMutableEntityType EntityType in EntityTypes)
			{
				Type											ClrType=EntityType.ClrType;
				CAutoConfigureEntityAttribute					AutoConfigureEntityAttribute=ClrType.GetCustomAttribute<CAutoConfigureEntityAttribute>();

				if (AutoConfigureEntityAttribute!=null)
				{
					string										TableName=AutoConfigureEntityAttribute.TableName;

					EntityType.SetTableName(TableName);

					IMutableProperty[]							EntityProperties=EntityType.GetProperties().ToArray();

					foreach(IMutableProperty EntityProperty in EntityProperties)
					{
						// !!! Pre SHADOW PROPERTIES, alebo BACKING FIELDS vracia NULL.
						PropertyInfo							Property=EntityProperty.PropertyInfo;

						if (Property!=null)
						{
							CPrimaryKeyAttribute				PrimaryKeyAttribute=Property.GetCustomAttribute<CPrimaryKeyAttribute>();

							if (PrimaryKeyAttribute!=null)
							{
								EntityType.SetPrimaryKey(EntityProperty);
							}

							CRequiredAttribute					RequiredAttribute=Property.GetCustomAttribute<CRequiredAttribute>();

							if (RequiredAttribute!=null)
							{
								EntityProperty.IsNullable=false;
							}

							CMaxSizeAttribute					MaxSizeAttribute=Property.GetCustomAttribute<CMaxSizeAttribute>();

							if (MaxSizeAttribute!=null)
							{
								EntityProperty.SetMaxLength(MaxSizeAttribute.Size);
							}

							CPrecisionAttribute					PrecisionAttribute=Property.GetCustomAttribute<CPrecisionAttribute>();

							if (PrecisionAttribute!=null)
							{
								EntityProperty.SetPrecision(PrecisionAttribute.Precision);
							}

							CScaleAttribute						ScaleAttribute=Property.GetCustomAttribute<CScaleAttribute>();

							if (ScaleAttribute!=null)
							{
								EntityProperty.SetScale(ScaleAttribute.Scale);
							}
						}
					}
				}
			}
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
			ConfigureEntityDifferentConfigurations(ModelBuilder);
			ConfigureEntityNotMappedDataAnnotations(ModelBuilder);
			ConfigureEntityNotMappedFluentAPI(ModelBuilder);
			ConfigureEntityNotExcluded(ModelBuilder);
			ConfigureEntityColumnPropertiesDataAnnotations(ModelBuilder);
			ConfigureEntityColumnPropertiesFluentAPI(ModelBuilder);
			ConfigureEntityUsingValueConversions(ModelBuilder);
			ConfigureEntityPrimaryKeyConventions(ModelBuilder);
			ConfigureEntityPrimaryKeyDataAnnotations(ModelBuilder);
			ConfigureEntityPrimaryKeyFluentAPI(ModelBuilder);
			ConfigureEntityDataForKeylessView(ModelBuilder);
			ConfigureEntityKeylessDataAnnotations(ModelBuilder);
			ConfigureEntityKeylessFluentAPI(ModelBuilder);
			ConfigureEntityIndexesDataAnnotations(ModelBuilder);
			ConfigureEntityIndexesFluentAPI(ModelBuilder);
			ConfigureEntityCustomNamesDataAnnotations(ModelBuilder);
			ConfigureEntityCustomNamesFluentAPI(ModelBuilder);
			ConfigureEntityQueryFilter(ModelBuilder);
			ConfigureEntityShadowProperties(ModelBuilder);
			ConfigureEntityBackingFieldsConventions(ModelBuilder);
			ConfigureEntityBackingFieldsDataAnnotations(ModelBuilder);
			ConfigureEntityBackingFieldsFluentAPI(ModelBuilder);
			ConfigureEntityBackingFieldsAccessModes(ModelBuilder);

			AutoConfigureEntities(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------