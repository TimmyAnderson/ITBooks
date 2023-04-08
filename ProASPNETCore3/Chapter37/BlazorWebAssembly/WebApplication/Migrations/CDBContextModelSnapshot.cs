﻿// <auto-generated />
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using WebApplication.Database;

namespace WebApplication.Migrations
{
    [DbContext(typeof(CDBContext))]
    partial class CDBContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "3.1.8");

            modelBuilder.Entity("WebApplication.Database.CEntityPerson", b =>
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

                    b.ToTable("Person");

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
