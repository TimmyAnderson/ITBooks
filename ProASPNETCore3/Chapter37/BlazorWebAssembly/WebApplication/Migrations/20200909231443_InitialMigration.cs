using Microsoft.EntityFrameworkCore.Migrations;

namespace WebApplication.Migrations
{
    public partial class InitialMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Person",
                columns: table => new
                {
                    ID = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    FirstName = table.Column<string>(nullable: true),
                    LastName = table.Column<string>(nullable: true),
                    Age = table.Column<int>(nullable: false),
                    Sex = table.Column<int>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Person", x => x.ID);
                });

            migrationBuilder.InsertData(
                table: "Person",
                columns: new[] { "ID", "Age", "FirstName", "LastName", "Sex" },
                values: new object[] { 1, 12, "Timmy", "Anderson", 1 });

            migrationBuilder.InsertData(
                table: "Person",
                columns: new[] { "ID", "Age", "FirstName", "LastName", "Sex" },
                values: new object[] { 2, 13, "Jenny", "Thompson", 2 });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Person");
        }
    }
}
