﻿// <auto-generated />
using System;
using DataAccess3;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

#nullable disable

namespace DataAccess3.Migrations
{
    [DbContext(typeof(CDBContext))]
    [Migration("20250430120557_InitialMigration")]
    partial class InitialMigration
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "9.0.4");

            modelBuilder.Entity("DataAccess3.CEntityBulkOperations", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("Category")
                        .HasColumnType("INTEGER");

                    b.Property<int>("Value1")
                        .HasColumnType("INTEGER");

                    b.Property<int>("Value2")
                        .HasColumnType("INTEGER");

                    b.HasKey("ID");

                    b.ToTable("EntitiesBulkOperations", (string)null);

                    b.HasData(
                        new
                        {
                            ID = 1,
                            Category = 10,
                            Value1 = 11,
                            Value2 = 16
                        },
                        new
                        {
                            ID = 2,
                            Category = 10,
                            Value1 = 12,
                            Value2 = 17
                        },
                        new
                        {
                            ID = 3,
                            Category = 100,
                            Value1 = 101,
                            Value2 = 106
                        },
                        new
                        {
                            ID = 4,
                            Category = 100,
                            Value1 = 102,
                            Value2 = 107
                        },
                        new
                        {
                            ID = 5,
                            Category = 1000,
                            Value1 = 1001,
                            Value2 = 1006
                        },
                        new
                        {
                            ID = 6,
                            Category = 1000,
                            Value1 = 1002,
                            Value2 = 1007
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityConcurrencyTokensDataAnnotations", b =>
                {
                    b.Property<int>("EntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue")
                        .HasColumnType("INTEGER");

                    b.Property<Guid>("Version")
                        .IsConcurrencyToken()
                        .HasColumnType("TEXT");

                    b.HasKey("EntityID");

                    b.ToTable("EntitiesConcurrencyTokensDataAnnotations", (string)null);

                    b.HasData(
                        new
                        {
                            EntityID = 1,
                            EntityValue = 100,
                            Version = new Guid("f5cdc704-2d54-44a7-817b-a4776f12eb26")
                        },
                        new
                        {
                            EntityID = 2,
                            EntityValue = 200,
                            Version = new Guid("39cc4026-30e6-4b4e-abb9-0ead985b7a1a")
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityConcurrencyTokensFluentAPI", b =>
                {
                    b.Property<int>("EntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityValue")
                        .IsConcurrencyToken()
                        .HasColumnType("INTEGER");

                    b.Property<Guid>("Version")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityID");

                    b.ToTable("EntitiesConcurrencyTokensFluentAPI", (string)null);

                    b.HasData(
                        new
                        {
                            EntityID = 1,
                            EntityValue = 100,
                            Version = new Guid("f5cdc704-2d54-44a7-817b-a4776f12eb26")
                        },
                        new
                        {
                            EntityID = 2,
                            EntityValue = 200,
                            Version = new Guid("39cc4026-30e6-4b4e-abb9-0ead985b7a1a")
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityManyToManyM", b =>
                {
                    b.Property<int>("EntityMID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityMValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityMID");

                    b.ToTable("EntitiesManyToManyM", (string)null);

                    b.HasData(
                        new
                        {
                            EntityMID = 1,
                            EntityMValue = "AAA"
                        },
                        new
                        {
                            EntityMID = 2,
                            EntityMValue = "BBB"
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityManyToManyMN", b =>
                {
                    b.Property<int>("EntityMID")
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityNID")
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityMNValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityMID", "EntityNID");

                    b.HasIndex("EntityNID");

                    b.ToTable("EntitiesManyToManyMN", (string)null);

                    b.HasData(
                        new
                        {
                            EntityMID = 1,
                            EntityNID = 1,
                            EntityMNValue = "LINK 11"
                        },
                        new
                        {
                            EntityMID = 1,
                            EntityNID = 2,
                            EntityMNValue = "LINK 12"
                        },
                        new
                        {
                            EntityMID = 2,
                            EntityNID = 1,
                            EntityMNValue = "LINK 21"
                        },
                        new
                        {
                            EntityMID = 2,
                            EntityNID = 2,
                            EntityMNValue = "LINK 22"
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityManyToManyN", b =>
                {
                    b.Property<int>("EntityNID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityNValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityNID");

                    b.ToTable("EntitiesManyToManyN", (string)null);

                    b.HasData(
                        new
                        {
                            EntityNID = 1,
                            EntityNValue = "111"
                        },
                        new
                        {
                            EntityNID = 2,
                            EntityNValue = "222"
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToManyDependent", b =>
                {
                    b.Property<int>("EntityDependentID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityDependentValue")
                        .HasColumnType("TEXT");

                    b.Property<int>("EntityPrincipalID")
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityDependentID");

                    b.HasIndex("EntityPrincipalID");

                    b.ToTable("EntitiesOneToManyDependent", (string)null);

                    b.HasData(
                        new
                        {
                            EntityDependentID = 1,
                            EntityDependentValue = "AAA 111",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 2,
                            EntityDependentValue = "AAA 222",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 3,
                            EntityDependentValue = "BBB 111",
                            EntityPrincipalID = 2
                        },
                        new
                        {
                            EntityDependentID = 4,
                            EntityDependentValue = "BBB 222",
                            EntityPrincipalID = 2
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToManyPrincipal", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesOneToManyPrincipal", (string)null);

                    b.HasData(
                        new
                        {
                            EntityPrincipalID = 1,
                            EntityPrincipalValue = "AAA"
                        },
                        new
                        {
                            EntityPrincipalID = 2,
                            EntityPrincipalValue = "BBB"
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToOneDependent", b =>
                {
                    b.Property<int>("EntityDependentID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityDependentValue")
                        .HasColumnType("TEXT");

                    b.Property<int>("EntityPrincipalID")
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityDependentID");

                    b.HasIndex("EntityPrincipalID")
                        .IsUnique();

                    b.ToTable("EntitiesOneToOneDependent", (string)null);

                    b.HasData(
                        new
                        {
                            EntityDependentID = 1,
                            EntityDependentValue = "CHILD AAA",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 2,
                            EntityDependentValue = "CHILD BBB",
                            EntityPrincipalID = 2
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToOnePrincipal", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesOneToOnePrincipal", (string)null);

                    b.HasData(
                        new
                        {
                            EntityPrincipalID = 1,
                            EntityPrincipalValue = "PARENT AAA"
                        },
                        new
                        {
                            EntityPrincipalID = 2,
                            EntityPrincipalValue = "PARENT BBB"
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityRawSql", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("Category")
                        .HasColumnType("INTEGER");

                    b.Property<int>("Value")
                        .HasColumnType("INTEGER");

                    b.HasKey("ID");

                    b.ToTable("EntitiesRawSql", (string)null);

                    b.HasData(
                        new
                        {
                            ID = 1,
                            Category = 10,
                            Value = 11
                        },
                        new
                        {
                            ID = 2,
                            Category = 10,
                            Value = 12
                        },
                        new
                        {
                            ID = 3,
                            Category = 100,
                            Value = 101
                        },
                        new
                        {
                            ID = 4,
                            Category = 100,
                            Value = 102
                        },
                        new
                        {
                            ID = 5,
                            Category = 1000,
                            Value = 1001
                        },
                        new
                        {
                            ID = 6,
                            Category = 1000,
                            Value = 1002
                        });
                });

            modelBuilder.Entity("DataAccess3.CEntityManyToManyMN", b =>
                {
                    b.HasOne("DataAccess3.CEntityManyToManyM", "EntityM")
                        .WithMany("EntitiesMN")
                        .HasForeignKey("EntityMID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("DataAccess3.CEntityManyToManyN", "EntityN")
                        .WithMany("EntitiesMN")
                        .HasForeignKey("EntityNID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityM");

                    b.Navigation("EntityN");
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToManyDependent", b =>
                {
                    b.HasOne("DataAccess3.CEntityOneToManyPrincipal", "EntityPrincipal")
                        .WithMany("EntitiesDependent")
                        .HasForeignKey("EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToOneDependent", b =>
                {
                    b.HasOne("DataAccess3.CEntityOneToOnePrincipal", "EntityPrincipal")
                        .WithOne("EntityDependent")
                        .HasForeignKey("DataAccess3.CEntityOneToOneDependent", "EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("DataAccess3.CEntityManyToManyM", b =>
                {
                    b.Navigation("EntitiesMN");
                });

            modelBuilder.Entity("DataAccess3.CEntityManyToManyN", b =>
                {
                    b.Navigation("EntitiesMN");
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToManyPrincipal", b =>
                {
                    b.Navigation("EntitiesDependent");
                });

            modelBuilder.Entity("DataAccess3.CEntityOneToOnePrincipal", b =>
                {
                    b.Navigation("EntityDependent");
                });
#pragma warning restore 612, 618
        }
    }
}
