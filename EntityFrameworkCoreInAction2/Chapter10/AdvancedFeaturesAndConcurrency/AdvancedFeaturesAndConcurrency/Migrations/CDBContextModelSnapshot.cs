﻿// <auto-generated />
using System;
using AdvancedFeaturesAndConcurrency;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

#nullable disable

namespace AdvancedFeaturesAndConcurrency.Migrations
{
    [DbContext(typeof(CDBContext))]
    partial class CDBContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "7.0.0");

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityComputedColumns", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("ComputedValueDynamic")
                        .ValueGeneratedOnAddOrUpdate()
                        .HasColumnType("INTEGER")
                        .HasComputedColumnSql("[IntValue1] + [IntValue2]", false);

                    b.Property<string>("ComputedValuePersistent")
                        .ValueGeneratedOnAddOrUpdate()
                        .HasColumnType("TEXT")
                        .HasComputedColumnSql("[StringValue1] || ' ' || [StringValue2]", true);

                    b.Property<int>("IntValue1")
                        .HasColumnType("INTEGER");

                    b.Property<int>("IntValue2")
                        .HasColumnType("INTEGER");

                    b.Property<string>("StringValue1")
                        .HasColumnType("TEXT");

                    b.Property<string>("StringValue2")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("EntitiesComputedColumns", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityConcurrencyTokensDataAnnotations", b =>
                {
                    b.Property<int>("EntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue")
                        .IsConcurrencyToken()
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityID");

                    b.ToTable("EntitiesConcurrencyTokensDataAnnotations", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityConcurrencyTokensFluentAPI", b =>
                {
                    b.Property<int>("EntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue")
                        .IsConcurrencyToken()
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityID");

                    b.ToTable("EntitiesConcurrencyTokensFluentAPI", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityDBGeneratedPropertiesDataAnnotations", b =>
                {
                    b.Property<int>("DatabaseGeneratedIdentity")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("DatabaseGeneratedComputed")
                        .ValueGeneratedOnAddOrUpdate()
                        .HasColumnType("INTEGER")
                        .HasComputedColumnSql("NonDatabaseGenerated+20");

                    b.Property<int>("NonDatabaseGenerated")
                        .HasColumnType("INTEGER");

                    b.HasKey("DatabaseGeneratedIdentity");

                    b.ToTable("EntitiesDBGeneratedPropertiesDataAnnotations", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityDBGeneratedPropertiesFluentAPI", b =>
                {
                    b.Property<int>("DatabaseGeneratedOnAdd")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("DatabaseGeneratedOnAddOrUpdate")
                        .ValueGeneratedOnAddOrUpdate()
                        .HasColumnType("INTEGER")
                        .HasComputedColumnSql("NonDatabaseGenerated+10");

                    b.Property<int>("DatabaseGeneratedOnUpdate")
                        .ValueGeneratedOnUpdate()
                        .HasColumnType("INTEGER");

                    b.Property<int>("NonDatabaseGenerated")
                        .HasColumnType("INTEGER");

                    b.HasKey("DatabaseGeneratedOnAdd");

                    b.ToTable("EntitiesDBGeneratedPropertiesFluentAPI", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityDefaultValueColumns", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<DateTime>("DefaultValue1")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("TEXT")
                        .HasDefaultValue(new DateTime(2000, 1, 1, 1, 1, 1, 0, DateTimeKind.Unspecified));

                    b.Property<double>("DefaultValue2")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("REAL")
                        .HasDefaultValueSql("111.222");

                    b.Property<int>("DefaultValue3")
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("EntitiesDefaultValueColumns", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityMultipleConcurrencyTokensFluentAPI", b =>
                {
                    b.Property<int>("EntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue1")
                        .IsConcurrencyToken()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue2")
                        .IsConcurrencyToken()
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityID");

                    b.ToTable("EntitiesMultipleConcurrencyTokensFluentAPI", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityOptimisticConcurrency", b =>
                {
                    b.Property<int>("EntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue")
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityID");

                    b.ToTable("EntitiesOptimisticConcurrency", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CEntityUsingUDF", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<double>("DoubleValue")
                        .HasColumnType("REAL");

                    b.Property<int>("IntValue")
                        .HasColumnType("INTEGER");

                    b.Property<string>("StringValue")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("EntitiesUsingUDF", (string)null);
                });

            modelBuilder.Entity("AdvancedFeaturesAndConcurrency.CTestEntity", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("TestEntities", (string)null);
                });
#pragma warning restore 612, 618
        }
    }
}
