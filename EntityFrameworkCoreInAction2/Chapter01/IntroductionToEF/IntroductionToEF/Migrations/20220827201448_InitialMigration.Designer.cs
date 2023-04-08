﻿// <auto-generated />
using IntroductionToEF;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

#nullable disable

namespace IntroductionToEF.Migrations
{
    [DbContext(typeof(CDBContext))]
    [Migration("20220827201448_InitialMigration")]
    partial class InitialMigration
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "6.0.8");

            modelBuilder.Entity("IntroductionToEF.CDependentEntity", b =>
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

            modelBuilder.Entity("IntroductionToEF.CPrincipalEntity", b =>
                {
                    b.Property<int>("PrincipalEntityID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("PrincipalEntityID");

                    b.ToTable("PrincipalEntities", (string)null);
                });

            modelBuilder.Entity("IntroductionToEF.CTestEntity", b =>
                {
                    b.Property<int>("ID")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("INTEGER");

                    b.Property<string>("Value")
                        .HasColumnType("TEXT");

                    b.HasKey("ID");

                    b.ToTable("TestEntities", (string)null);
                });

            modelBuilder.Entity("IntroductionToEF.CDependentEntity", b =>
                {
                    b.HasOne("IntroductionToEF.CPrincipalEntity", "PrincipalEntity")
                        .WithMany("DependentEntities")
                        .HasForeignKey("PrincipalEntityID")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("PrincipalEntity");
                });

            modelBuilder.Entity("IntroductionToEF.CPrincipalEntity", b =>
                {
                    b.Navigation("DependentEntities");
                });
#pragma warning restore 612, 618
        }
    }
}
