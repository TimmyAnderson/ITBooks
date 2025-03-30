﻿// <auto-generated />
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using UsingGraphQL;

#nullable disable

namespace UsingGraphQL.Migrations
{
    [DbContext(typeof(CDBContext))]
    [Migration("20250325003605_InitialMigration")]
    partial class InitialMigration
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
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
#pragma warning restore 612, 618
        }
    }
}
