﻿// <auto-generated />
using System;
using ChangingDBContent;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

#nullable disable

namespace ChangingDBContent.Migrations
{
    [DbContext(typeof(CDBContext))]
    partial class CDBContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "6.0.9");

            modelBuilder.Entity("CEntityManyToManyAutoMCEntityManyToManyAutoN", b =>
                {
                    b.Property<int>("EntitiesMEntityMID")
                        .HasColumnType("INTEGER");

                    b.Property<int>("EntitiesNEntityNID")
                        .HasColumnType("INTEGER");

                    b.HasKey("EntitiesMEntityMID", "EntitiesNEntityNID");

                    b.HasIndex("EntitiesNEntityNID");

                    b.ToTable("CEntityManyToManyAutoMCEntityManyToManyAutoN");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyAutoM", b =>
                {
                    b.Property<int>("EntityMID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityMValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityMID");

                    b.ToTable("EntitiesManyToManyAutoM", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyAutoN", b =>
                {
                    b.Property<int>("EntityNID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityNValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityNID");

                    b.ToTable("EntitiesManyToManyAutoN", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyM", b =>
                {
                    b.Property<int>("EntityMID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityMValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityMID");

                    b.ToTable("EntitiesManyToManyM", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyMN", b =>
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
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyN", b =>
                {
                    b.Property<int>("EntityNID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityNValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityNID");

                    b.ToTable("EntitiesManyToManyN", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToManyDependent", b =>
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
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToManyPrincipal", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesOneToManyPrincipal", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToOneDependent", b =>
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
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToOnePrincipal", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesOneToOnePrincipal", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityZeroToManyDependent", b =>
                {
                    b.Property<int>("EntityDependentID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityDependentValue")
                        .HasColumnType("TEXT");

                    b.Property<int?>("EntityPrincipalID")
                        .HasColumnType("INTEGER");

                    b.HasKey("EntityDependentID");

                    b.HasIndex("EntityPrincipalID");

                    b.ToTable("EntitiesZeroToManyDependent", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CEntityZeroToManyPrincipal", b =>
                {
                    b.Property<int>("EntityPrincipalID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("EntityPrincipalValue")
                        .HasColumnType("TEXT");

                    b.HasKey("EntityPrincipalID");

                    b.ToTable("EntitiesZeroToManyPrincipal", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CNumber", b =>
                {
                    b.Property<int>("NumberID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("Number")
                        .HasColumnType("INTEGER");

                    b.Property<string>("NumberAsText")
                        .HasColumnType("TEXT");

                    b.HasKey("NumberID");

                    b.ToTable("EntitiesNumber", (string)null);
                });

            modelBuilder.Entity("ChangingDBContent.CTestEntity", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("TestEntities", (string)null);
                });

            modelBuilder.Entity("CEntityManyToManyAutoMCEntityManyToManyAutoN", b =>
                {
                    b.HasOne("ChangingDBContent.CEntityManyToManyAutoM", null)
                        .WithMany()
                        .HasForeignKey("EntitiesMEntityMID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("ChangingDBContent.CEntityManyToManyAutoN", null)
                        .WithMany()
                        .HasForeignKey("EntitiesNEntityNID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyMN", b =>
                {
                    b.HasOne("ChangingDBContent.CEntityManyToManyM", "EntityM")
                        .WithMany("EntitiesMN")
                        .HasForeignKey("EntityMID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("ChangingDBContent.CEntityManyToManyN", "EntityN")
                        .WithMany("EntitiesMN")
                        .HasForeignKey("EntityNID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityM");

                    b.Navigation("EntityN");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToManyDependent", b =>
                {
                    b.HasOne("ChangingDBContent.CEntityOneToManyPrincipal", "EntityPrincipal")
                        .WithMany("EntitiesDependent")
                        .HasForeignKey("EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToOneDependent", b =>
                {
                    b.HasOne("ChangingDBContent.CEntityOneToOnePrincipal", "EntityPrincipal")
                        .WithOne("EntityDependent")
                        .HasForeignKey("ChangingDBContent.CEntityOneToOneDependent", "EntityPrincipalID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityZeroToManyDependent", b =>
                {
                    b.HasOne("ChangingDBContent.CEntityZeroToManyPrincipal", "EntityPrincipal")
                        .WithMany("EntitiesDependent")
                        .HasForeignKey("EntityPrincipalID");

                    b.Navigation("EntityPrincipal");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyM", b =>
                {
                    b.Navigation("EntitiesMN");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityManyToManyN", b =>
                {
                    b.Navigation("EntitiesMN");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToManyPrincipal", b =>
                {
                    b.Navigation("EntitiesDependent");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityOneToOnePrincipal", b =>
                {
                    b.Navigation("EntityDependent");
                });

            modelBuilder.Entity("ChangingDBContent.CEntityZeroToManyPrincipal", b =>
                {
                    b.Navigation("EntitiesDependent");
                });
#pragma warning restore 612, 618
        }
    }
}
