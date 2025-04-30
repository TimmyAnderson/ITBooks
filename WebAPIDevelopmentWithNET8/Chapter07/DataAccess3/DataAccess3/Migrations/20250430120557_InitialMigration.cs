using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace DataAccess3.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesBulkOperations",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Category = table.Column<int>(type: "INTEGER", nullable: false),
                    Value1 = table.Column<int>(type: "INTEGER", nullable: false),
                    Value2 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesBulkOperations", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesConcurrencyTokensDataAnnotations",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<int>(type: "INTEGER", nullable: false),
                    Version = table.Column<Guid>(type: "TEXT", nullable: false)
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
                    EntityValue = table.Column<int>(type: "INTEGER", nullable: false),
                    Version = table.Column<Guid>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConcurrencyTokensFluentAPI", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyM",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyM", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyN",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyN", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOnePrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOnePrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesRawSql",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Category = table.Column<int>(type: "INTEGER", nullable: false),
                    Value = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesRawSql", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMN",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMN", x => new { x.EntityMID, x.EntityNID });
                    table.ForeignKey(
                        name: "FK_EntitiesManyToManyMN_EntitiesManyToManyM_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesManyToManyM",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToManyMN_EntitiesManyToManyN_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesManyToManyN",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyDependent_EntitiesOneToManyPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneDependent_EntitiesOneToOnePrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToOnePrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "EntitiesBulkOperations",
                columns: new[] { "ID", "Category", "Value1", "Value2" },
                values: new object[,]
                {
                    { 1, 10, 11, 16 },
                    { 2, 10, 12, 17 },
                    { 3, 100, 101, 106 },
                    { 4, 100, 102, 107 },
                    { 5, 1000, 1001, 1006 },
                    { 6, 1000, 1002, 1007 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesConcurrencyTokensDataAnnotations",
                columns: new[] { "EntityID", "EntityValue", "Version" },
                values: new object[,]
                {
                    { 1, 100, new Guid("f5cdc704-2d54-44a7-817b-a4776f12eb26") },
                    { 2, 200, new Guid("39cc4026-30e6-4b4e-abb9-0ead985b7a1a") }
                });

            migrationBuilder.InsertData(
                table: "EntitiesConcurrencyTokensFluentAPI",
                columns: new[] { "EntityID", "EntityValue", "Version" },
                values: new object[,]
                {
                    { 1, 100, new Guid("f5cdc704-2d54-44a7-817b-a4776f12eb26") },
                    { 2, 200, new Guid("39cc4026-30e6-4b4e-abb9-0ead985b7a1a") }
                });

            migrationBuilder.InsertData(
                table: "EntitiesManyToManyM",
                columns: new[] { "EntityMID", "EntityMValue" },
                values: new object[,]
                {
                    { 1, "AAA" },
                    { 2, "BBB" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesManyToManyN",
                columns: new[] { "EntityNID", "EntityNValue" },
                values: new object[,]
                {
                    { 1, "111" },
                    { 2, "222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToManyPrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "AAA" },
                    { 2, "BBB" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToOnePrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "PARENT AAA" },
                    { 2, "PARENT BBB" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesRawSql",
                columns: new[] { "ID", "Category", "Value" },
                values: new object[,]
                {
                    { 1, 10, 11 },
                    { 2, 10, 12 },
                    { 3, 100, 101 },
                    { 4, 100, 102 },
                    { 5, 1000, 1001 },
                    { 6, 1000, 1002 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesManyToManyMN",
                columns: new[] { "EntityMID", "EntityNID", "EntityMNValue" },
                values: new object[,]
                {
                    { 1, 1, "LINK 11" },
                    { 1, 2, "LINK 12" },
                    { 2, 1, "LINK 21" },
                    { 2, 2, "LINK 22" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToManyDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "AAA 111", 1 },
                    { 2, "AAA 222", 1 },
                    { 3, "BBB 111", 2 },
                    { 4, "BBB 222", 2 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToOneDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "CHILD AAA", 1 },
                    { 2, "CHILD BBB", 2 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToManyMN_EntityNID",
                table: "EntitiesManyToManyMN",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyDependent_EntityPrincipalID",
                table: "EntitiesOneToManyDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOneDependent_EntityPrincipalID",
                table: "EntitiesOneToOneDependent",
                column: "EntityPrincipalID",
                unique: true);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesBulkOperations");

            migrationBuilder.DropTable(
                name: "EntitiesConcurrencyTokensDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesConcurrencyTokensFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMN");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent");

            migrationBuilder.DropTable(
                name: "EntitiesRawSql");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyM");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyN");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal");
        }
    }
}
