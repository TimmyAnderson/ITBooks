﻿// <auto-generated />
using LINQQueries;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

#nullable disable

namespace LINQQueries.Migrations
{
    [DbContext(typeof(CDBContext))]
    [Migration("20220916204136_InitialMigration")]
    partial class InitialMigration
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "6.0.4");

            modelBuilder.Entity("LINQQueries.CDependentEntity", b =>
                {
                    b.Property<int>("DependentEntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<int>("PrincipalEntityID")
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("DependentEntityID");

                    b.HasIndex("PrincipalEntityID");

                    b.ToTable("DependentEntities", (string)null);
                });

            modelBuilder.Entity("LINQQueries.CPrincipalEntity", b =>
                {
                    b.Property<int>("PrincipalEntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("PrincipalEntityID");

                    b.ToTable("PrincipalEntities", (string)null);
                });

            modelBuilder.Entity("LINQQueries.CTestEntity", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("TestEntities", (string)null);
                });

            modelBuilder.Entity("LINQQueries.CDependentEntity", b =>
                {
                    b.HasOne("LINQQueries.CPrincipalEntity", "PrincipalEntity")
                        .WithMany("DependentEntities")
                        .HasForeignKey("PrincipalEntityID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("PrincipalEntity");
                });

            modelBuilder.Entity("LINQQueries.CPrincipalEntity", b =>
                {
                    b.Navigation("DependentEntities");
                });
#pragma warning restore 612, 618
        }
    }
}
