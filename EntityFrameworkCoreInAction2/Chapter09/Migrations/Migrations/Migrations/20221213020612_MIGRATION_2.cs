using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Migrations.Migrations
{
    /// <inheritdoc />
    public partial class MIGRATION2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityDependentStringValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesDependent_EntitiesPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "EntitiesPrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalIntValue", "EntityPrincipalStringValue" },
                values: new object[,]
                {
                    { 1, 111, "PRINCIPAL 111" },
                    { 2, 222, "PRINCIPAL 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesDependent",
                columns: new[] { "EntityDependentID", "EntityDependentIntValue", "EntityDependentStringValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, 111, "DEPENDENT 111", 1 },
                    { 2, 222, "DEPENDENT 222", 1 },
                    { 3, 333, "DEPENDENT 333", 2 },
                    { 4, 444, "DEPENDENT 444", 2 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesDependent_EntityPrincipalID",
                table: "EntitiesDependent",
                column: "EntityPrincipalID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesDependent");

            migrationBuilder.DropTable(
                name: "EntitiesPrincipal");
        }
    }
}
