using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace DataAccess3SqlServer.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesTimestampsDataAnnotations",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    EntityValue = table.Column<int>(type: "int", nullable: false),
                    Timestamp = table.Column<byte[]>(type: "rowversion", rowVersion: true, nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTimestampsDataAnnotations", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTimestampsFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    EntityValue = table.Column<int>(type: "int", nullable: false),
                    Timestamp = table.Column<byte[]>(type: "rowversion", rowVersion: true, nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTimestampsFluentAPI", x => x.EntityID);
                });

            migrationBuilder.InsertData(
                table: "EntitiesTimestampsDataAnnotations",
                columns: new[] { "EntityID", "EntityValue" },
                values: new object[,]
                {
                    { 1, 100 },
                    { 2, 200 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesTimestampsFluentAPI",
                columns: new[] { "EntityID", "EntityValue" },
                values: new object[,]
                {
                    { 1, 100 },
                    { 2, 200 }
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesTimestampsDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesTimestampsFluentAPI");
        }
    }
}
