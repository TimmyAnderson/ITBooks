using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace DataAccess2Web.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
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

            migrationBuilder.InsertData(
                table: "EntitiesOneToManyPrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "PRINCIPAL 111" },
                    { 2, "PRINCIPAL 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToManyDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "DEPENDENT 111", 1 },
                    { 2, "DEPENDENT 222", 1 },
                    { 3, "DEPENDENT 333", 2 },
                    { 4, "DEPENDENT 444", 2 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyDependent_EntityPrincipalID",
                table: "EntitiesOneToManyDependent",
                column: "EntityPrincipalID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");
        }
    }
}
