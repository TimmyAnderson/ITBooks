using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AdvancedFeaturesAndConcurrencySqlServer.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.EnsureSchema(
                name: "TestSchema");

            migrationBuilder.CreateSequence(
                name: "MySequence",
                schema: "TestSchema",
                startValue: 1000L,
                incrementBy: 4);

            migrationBuilder.CreateTable(
                name: "EntitiesTableValuedFunctionResult",
                columns: table => new
                {
                    StringValue = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    IntValue = table.Column<int>(type: "int", nullable: false),
                    DoubleValue = table.Column<double>(type: "float", nullable: false)
                },
                constraints: table =>
                {
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTimestampsDataAnnotations",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Timestamp = table.Column<byte[]>(type: "rowversion", rowVersion: true, nullable: true),
                    EntityValue = table.Column<int>(type: "int", nullable: false)
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
                    Timestamp = table.Column<byte[]>(type: "rowversion", rowVersion: true, nullable: true),
                    EntityValue = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTimestampsFluentAPI", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesUsingSequence",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    SequenceValue = table.Column<int>(type: "int", nullable: false, defaultValueSql: "NEXT VALUE FOR TestSchema.MySequence"),
                    Value = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesUsingSequence", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesUsingUDF",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    StringValue = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    IntValue = table.Column<int>(type: "int", nullable: false),
                    DoubleValue = table.Column<double>(type: "float", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesUsingUDF", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "TestEntities",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Value = table.Column<string>(type: "nvarchar(max)", nullable: true)
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
                name: "EntitiesTableValuedFunctionResult");

            migrationBuilder.DropTable(
                name: "EntitiesTimestampsDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesTimestampsFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesUsingSequence");

            migrationBuilder.DropTable(
                name: "EntitiesUsingUDF");

            migrationBuilder.DropTable(
                name: "TestEntities");

            migrationBuilder.DropSequence(
                name: "MySequence",
                schema: "TestSchema");
        }
    }
}
