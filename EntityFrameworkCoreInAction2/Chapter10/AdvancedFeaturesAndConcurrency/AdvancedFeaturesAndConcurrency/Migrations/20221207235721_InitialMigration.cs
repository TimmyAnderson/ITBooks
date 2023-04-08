using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AdvancedFeaturesAndConcurrency.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesComputedColumns",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    StringValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    IntValue1 = table.Column<int>(type: "INTEGER", nullable: false),
                    IntValue2 = table.Column<int>(type: "INTEGER", nullable: false),
                    ComputedValueDynamic = table.Column<int>(type: "INTEGER", nullable: false, computedColumnSql: "[IntValue1] + [IntValue2]", stored: false),
                    ComputedValuePersistent = table.Column<string>(type: "TEXT", nullable: true, computedColumnSql: "[StringValue1] || ' ' || [StringValue2]", stored: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesComputedColumns", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesConcurrencyTokensDataAnnotations",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConcurrencyTokensDataAnnotations", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesConcurrencyTokensFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConcurrencyTokensFluentAPI", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDBGeneratedPropertiesDataAnnotations",
                columns: table => new
                {
                    DatabaseGeneratedIdentity = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    DatabaseGeneratedComputed = table.Column<int>(type: "INTEGER", nullable: false, computedColumnSql: "NonDatabaseGenerated+20"),
                    NonDatabaseGenerated = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDBGeneratedPropertiesDataAnnotations", x => x.DatabaseGeneratedIdentity);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDBGeneratedPropertiesFluentAPI",
                columns: table => new
                {
                    DatabaseGeneratedOnAdd = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    DatabaseGeneratedOnAddOrUpdate = table.Column<int>(type: "INTEGER", nullable: false, computedColumnSql: "NonDatabaseGenerated+10"),
                    DatabaseGeneratedOnUpdate = table.Column<int>(type: "INTEGER", nullable: false),
                    NonDatabaseGenerated = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDBGeneratedPropertiesFluentAPI", x => x.DatabaseGeneratedOnAdd);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDefaultValueColumns",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true),
                    DefaultValue1 = table.Column<DateTime>(type: "TEXT", nullable: false, defaultValue: new DateTime(2000, 1, 1, 1, 1, 1, 0, DateTimeKind.Unspecified)),
                    DefaultValue2 = table.Column<double>(type: "REAL", nullable: false, defaultValueSql: "111.222"),
                    DefaultValue3 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDefaultValueColumns", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesMultipleConcurrencyTokensFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue1 = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityValue2 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesMultipleConcurrencyTokensFluentAPI", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOptimisticConcurrency",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOptimisticConcurrency", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesUsingUDF",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", nullable: true),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    DoubleValue = table.Column<double>(type: "REAL", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesUsingUDF", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "TestEntities",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestEntities", x => x.ID);
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesComputedColumns");

            migrationBuilder.DropTable(
                name: "EntitiesConcurrencyTokensDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesConcurrencyTokensFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesDBGeneratedPropertiesDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesDBGeneratedPropertiesFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesDefaultValueColumns");

            migrationBuilder.DropTable(
                name: "EntitiesMultipleConcurrencyTokensFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOptimisticConcurrency");

            migrationBuilder.DropTable(
                name: "EntitiesUsingUDF");

            migrationBuilder.DropTable(
                name: "TestEntities");
        }
    }
}
