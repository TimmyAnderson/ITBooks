using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace UsingGraphQL.Migrations
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
                name: "EntitiesOneToOnePrincipal1",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOnePrincipal1", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOnePrincipal2",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOnePrincipal2", x => x.EntityPrincipalID);
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
                name: "EntitiesOneToOneDependent1",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneDependent1", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneDependent1_EntitiesOneToOnePrincipal1_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToOnePrincipal1",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneDependent2",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneDependent2", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneDependent2_EntitiesOneToOnePrincipal2_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToOnePrincipal2",
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
                table: "EntitiesOneToOnePrincipal1",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "PRINCIPAL 111" },
                    { 2, "PRINCIPAL 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToOnePrincipal2",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "PRINCIPAL 111" },
                    { 2, "PRINCIPAL 222" }
                });

            migrationBuilder.InsertData(
                table: "NamesEntities",
                columns: new[] { "ID", "Age", "FirstName", "LastName", "Sex" },
                values: new object[,]
                {
                    { 1, 12, "Timmy", "Anderson", 1 },
                    { 2, 13, "Jenny", "Thompson", 2 }
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

            migrationBuilder.InsertData(
                table: "EntitiesOneToOneDependent1",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "DEPENDENT 111", 1 },
                    { 2, "DEPENDENT 222", 2 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOneToOneDependent2",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "DEPENDENT 111", 1 },
                    { 2, "DEPENDENT 222", 2 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyDependent_EntityPrincipalID",
                table: "EntitiesOneToManyDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOneDependent1_EntityPrincipalID",
                table: "EntitiesOneToOneDependent1",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOneDependent2_EntityPrincipalID",
                table: "EntitiesOneToOneDependent2",
                column: "EntityPrincipalID",
                unique: true);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent1");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent2");

            migrationBuilder.DropTable(
                name: "NamesEntities");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal1");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal2");
        }
    }
}
