using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace UseTrackingChangesProxies.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesProxiesPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesProxiesPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesProxiesDependent",
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
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesProxiesDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyTrackingChangesProxiesDependent_EntitiesOneToManyTrackingChangesProxiesPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyTrackingChangesProxiesPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyTrackingChangesProxiesDependent_EntityPrincipalID",
                table: "EntitiesOneToManyTrackingChangesProxiesDependent",
                column: "EntityPrincipalID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesProxiesDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesProxiesPrincipal");
        }
    }
}
