﻿// <auto-generated />
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using UsingEFCore1;

#nullable disable

namespace UsingEFCore1.Migrations
{
    [DbContext(typeof(CDBContext))]
    partial class CDBContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder.HasAnnotation("ProductVersion", "6.0.9");

            modelBuilder.Entity("UsingEFCore1.CNumber", b =>
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

            modelBuilder.Entity("UsingEFCore1.CTestEntity", b =>
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
