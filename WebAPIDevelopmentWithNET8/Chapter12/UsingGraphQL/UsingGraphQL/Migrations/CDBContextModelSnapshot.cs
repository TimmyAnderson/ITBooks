﻿// <auto-generated />
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using UsingGraphQL;

#nullable disable

namespace UsingGraphQL.Migrations
{
    [DbContext(typeof(CDBContext))]
    partial class CDBContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "9.0.3");

            modelBuilder.Entity("UsingGraphQL.CEntityName", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("Age")
                        .HasColumnType("INTEGER");

                    b.Property<string>("FirstName")
                        .HasColumnType("TEXT");

                    b.Property<string>("LastName")
                        .HasColumnType("TEXT");

                    b.Property<int>("Sex")
                        .HasColumnType("INTEGER");

                    b.HasKey("ID");

                    b.ToTable("NamesEntities", (string)null);

                    b.HasData(
                        new
                        {
                            ID = 1,
                            Age = 12,
                            FirstName = "Timmy",
                            LastName = "Anderson",
                            Sex = 1
                        },
                        new
                        {
                            ID = 2,
                            Age = 13,
                            FirstName = "Jenny",
                            LastName = "Thompson",
                            Sex = 2
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToManyDependent", b =>
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
                            EntityDependentValue = "DEPENDENT 111",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 2,
                            EntityDependentValue = "DEPENDENT 222",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 3,
                            EntityDependentValue = "DEPENDENT 333",
                            EntityPrincipalID = 2
                        },
                        new
                        {
                            EntityDependentID = 4,
                            EntityDependentValue = "DEPENDENT 444",
                            EntityPrincipalID = 2
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToManyPrincipal", b =>
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
                            EntityPrincipalValue = "PRINCIPAL 111"
                        },
                        new
                        {
                            EntityPrincipalID = 2,
                            EntityPrincipalValue = "PRINCIPAL 222"
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOneDependent1", b =>
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

                    b.ToTable("EntitiesOneToOneDependent1", (string)null);

                    b.HasData(
                        new
                        {
                            EntityDependentID = 1,
                            EntityDependentValue = "DEPENDENT 111",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 2,
                            EntityDependentValue = "DEPENDENT 222",
                            EntityPrincipalID = 2
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOneDependent2", b =>
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

                    b.ToTable("EntitiesOneToOneDependent2", (string)null);

                    b.HasData(
                        new
                        {
                            EntityDependentID = 1,
                            EntityDependentValue = "DEPENDENT 111",
                            EntityPrincipalID = 1
                        },
                        new
                        {
                            EntityDependentID = 2,
                            EntityDependentValue = "DEPENDENT 222",
                            EntityPrincipalID = 2
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOnePrincipal1", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesOneToOnePrincipal1", (string)null);

                    b.HasData(
                        new
                        {
                            EntityPrincipalID = 1,
                            EntityPrincipalValue = "PRINCIPAL 111"
                        },
                        new
                        {
                            EntityPrincipalID = 2,
                            EntityPrincipalValue = "PRINCIPAL 222"
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOnePrincipal2", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesOneToOnePrincipal2", (string)null);

                    b.HasData(
                        new
                        {
                            EntityPrincipalID = 1,
                            EntityPrincipalValue = "PRINCIPAL 111"
                        },
                        new
                        {
                            EntityPrincipalID = 2,
                            EntityPrincipalValue = "PRINCIPAL 222"
                        });
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToManyDependent", b =>
                {
                    b.HasOne("UsingGraphQL.CEntityOneToManyPrincipal", "EntityPrincipal")
                        .WithMany("EntitiesDependent")
                        .HasForeignKey("EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOneDependent1", b =>
                {
                    b.HasOne("UsingGraphQL.CEntityOneToOnePrincipal1", "EntityPrincipal")
                        .WithOne("EntityDependent")
                        .HasForeignKey("UsingGraphQL.CEntityOneToOneDependent1", "EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOneDependent2", b =>
                {
                    b.HasOne("UsingGraphQL.CEntityOneToOnePrincipal2", "EntityPrincipal")
                        .WithOne("EntityDependent")
                        .HasForeignKey("UsingGraphQL.CEntityOneToOneDependent2", "EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToManyPrincipal", b =>
                {
                    b.Navigation("EntitiesDependent");
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOnePrincipal1", b =>
                {
                    b.Navigation("EntityDependent");
                });

            modelBuilder.Entity("UsingGraphQL.CEntityOneToOnePrincipal2", b =>
                {
                    b.Navigation("EntityDependent");
                });
#pragma warning restore 612, 618
        }
    }
}
