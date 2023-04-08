﻿// <auto-generated />
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Migrations;

#nullable disable

namespace Migrations.Migrations
{
    [DbContext(typeof(CDBContext))]
    [Migration("20221213020612_MIGRATION_2")]
    partial class MIGRATION2
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "7.0.0");

            modelBuilder.Entity("Migrations.CEntityDependent", b =>
                {
                    b.Property<int>("EntityDependentID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityDependentIntValue")
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityDependentStringValue")
                        .HasColumnType("TEXT");

                    b.Property<int>("EntityPrincipalID")
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityDependentID");

                    b.HasIndex("EntityPrincipalID");

                    b.ToTable("EntitiesDependent", (string)null);

                    b.HasData(
                        new
                        {
                            EntityDependentID = 1,
                            EntityDependentIntValue = 111,
                            EntityDependentStringValue = "DEPENDENT 111",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 2,
                            EntityDependentIntValue = 222,
                            EntityDependentStringValue = "DEPENDENT 222",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 3,
                            EntityDependentIntValue = 333,
                            EntityDependentStringValue = "DEPENDENT 333",
                            EntityPrincipalID = 2
                        },
                        new
                        {
                            EntityDependentID = 4,
                            EntityDependentIntValue = 444,
                            EntityDependentStringValue = "DEPENDENT 444",
                            EntityPrincipalID = 2
                        });
                });

            modelBuilder.Entity("Migrations.CEntityNotInMigration", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("IntValue")
                        .HasColumnType("INTEGER");

                    b.Property<string>("StringValue")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("EntitiesNotInMigration", null, t =>
                        {
                            t.ExcludeFromMigrations();
                        });
                });

            modelBuilder.Entity("Migrations.CEntityPrincipal", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntityPrincipalIntValue")
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalStringValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesPrincipal", (string)null);

                    b.HasData(
                        new
                        {
                            EntityPrincipalID = 1,
                            EntityPrincipalIntValue = 111,
                            EntityPrincipalStringValue = "PRINCIPAL 111"
                        },
                        new
                        {
                            EntityPrincipalID = 2,
                            EntityPrincipalIntValue = 222,
                            EntityPrincipalStringValue = "PRINCIPAL 222"
                        });
                });

            modelBuilder.Entity("Migrations.CTestEntity", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("TestEntities", (string)null);

                    b.HasData(
                        new
                        {
                            ID = 1,
                            Value = "AAA"
                        },
                        new
                        {
                            ID = 2,
                            Value = "BBB"
                        });
                });

            modelBuilder.Entity("Migrations.CEntityDependent", b =>
                {
                    b.HasOne("Migrations.CEntityPrincipal", "EntityPrincipal")
                        .WithMany("EntitiesDependent")
                        .HasForeignKey("EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("Migrations.CEntityPrincipal", b =>
                {
                    b.Navigation("EntitiesDependent");
                });
#pragma warning restore 612, 618
        }
    }
}
