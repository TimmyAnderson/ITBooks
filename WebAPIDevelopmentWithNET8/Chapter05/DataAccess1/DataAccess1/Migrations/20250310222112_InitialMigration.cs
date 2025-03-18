using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace DataAccess1.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "DataAnnotationsOneToManyPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_DataAnnotationsOneToManyPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesConventionsOneToManyPrincipal",
                columns: table => new
                {
                    CEntityConventionsOneToManyPrincipalId = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConventionsOneToManyPrincipal", x => x.CEntityConventionsOneToManyPrincipalId);
                });

            migrationBuilder.CreateTable(
                name: "EntitieSeparateConfigurations",
                columns: table => new
                {
                    Id = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    IntNonNull = table.Column<int>(type: "INTEGER", nullable: false),
                    IntNull = table.Column<int>(type: "INTEGER", nullable: true),
                    StringWithMaxLength = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    StringNonNullWithMaxLength = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    StringNonUnicodeWithMaxLength = table.Column<string>(type: "TEXT", unicode: false, maxLength: 50, nullable: true),
                    DateTimeWithSQLTypeDATEAndIndex = table.Column<DateTime>(type: "date", nullable: false),
                    DoubleWithLimitedPrecision = table.Column<double>(type: "REAL", precision: 9, scale: 2, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitieSeparateConfigurations", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesFluentAPIOneToManyPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesFluentAPIOneToManyPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "NamesEntities",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    FirstName = table.Column<string>(type: "TEXT", nullable: true),
                    LastName = table.Column<string>(type: "TEXT", nullable: true),
                    Age = table.Column<int>(type: "INTEGER", nullable: false),
                    Sex = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_NamesEntities", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "DataAnnotationsOneToManyDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_DataAnnotationsOneToManyDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_DataAnnotationsOneToManyDependent_DataAnnotationsOneToManyPrincipal_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "DataAnnotationsOneToManyPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesConventionsOneToManyDependent",
                columns: table => new
                {
                    CEntityConventionsOneToManyDependentId = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    CEntityConventionsOneToManyPrincipalId = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConventionsOneToManyDependent", x => x.CEntityConventionsOneToManyDependentId);
                    table.ForeignKey(
                        name: "FK_EntitiesConventionsOneToManyDependent_EntitiesConventionsOneToManyPrincipal_CEntityConventionsOneToManyPrincipalId",
                        column: x => x.CEntityConventionsOneToManyPrincipalId,
                        principalTable: "EntitiesConventionsOneToManyPrincipal",
                        principalColumn: "CEntityConventionsOneToManyPrincipalId",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesFluentAPIOneToManyDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesFluentAPIOneToManyDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesFluentAPIOneToManyDependent_EntitiesFluentAPIOneToManyPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesFluentAPIOneToManyPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "NamesEntities",
                columns: new[] { "ID", "Age", "FirstName", "LastName", "Sex" },
                values: new object[,]
                {
                    { 1, 12, "Timmy", "Anderson", 1 },
                    { 2, 13, "Jenny", "Thompson", 2 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_DataAnnotationsOneToManyDependent_ForeignKeyEntityPrincipalID",
                table: "DataAnnotationsOneToManyDependent",
                column: "ForeignKeyEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesConventionsOneToManyDependent_CEntityConventionsOneToManyPrincipalId",
                table: "EntitiesConventionsOneToManyDependent",
                column: "CEntityConventionsOneToManyPrincipalId");

            migrationBuilder.CreateIndex(
                name: "IX_EntitieSeparateConfigurations_DateTimeWithSQLTypeDATEAndIndex",
                table: "EntitieSeparateConfigurations",
                column: "DateTimeWithSQLTypeDATEAndIndex");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesFluentAPIOneToManyDependent_EntityPrincipalID",
                table: "EntitiesFluentAPIOneToManyDependent",
                column: "EntityPrincipalID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "DataAnnotationsOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesConventionsOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitieSeparateConfigurations");

            migrationBuilder.DropTable(
                name: "EntitiesFluentAPIOneToManyDependent");

            migrationBuilder.DropTable(
                name: "NamesEntities");

            migrationBuilder.DropTable(
                name: "DataAnnotationsOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesConventionsOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesFluentAPIOneToManyPrincipal");
        }
    }
}
