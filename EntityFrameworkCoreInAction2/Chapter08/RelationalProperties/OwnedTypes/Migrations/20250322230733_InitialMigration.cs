using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace OwnedTypes.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyM",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: false)
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
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: false)
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
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: false)
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
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOnePrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedOneToManyPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedOneToManyPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedOneToOnePrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedOneToOnePrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMN",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: false),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMN", x => x.EntityMNID);
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
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: false),
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
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: false),
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

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedOneToManyDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: false),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedOneToManyDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOwnedOneToManyDependent_EntitiesOwnedOneToManyPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOwnedOneToManyPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedOneToOneDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedOneToOneDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOwnedOneToOneDependent_EntitiesOwnedOneToOnePrincipal_EntityDependentID",
                        column: x => x.EntityDependentID,
                        principalTable: "EntitiesOwnedOneToOnePrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.InsertData(
                table: "EntitiesManyToManyM",
                columns: new[] { "EntityMID", "EntityMValue" },
                values: new object[,]
                {
                    { 1, "ENTITY M - 111" },
                    { 2, "ENTITY M - 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesManyToManyN",
                columns: new[] { "EntityNID", "EntityNValue" },
                values: new object[,]
                {
                    { 1, "ENTITY N - 111" },
                    { 2, "ENTITY N - 222" }
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
                table: "EntitiesOneToOnePrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "PRINCIPAL 111" },
                    { 2, "PRINCIPAL 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOwnedOneToManyPrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "ENTITY PRINCIPAL 1" },
                    { 2, "ENTITY PRINCIPAL 2" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOwnedOneToOnePrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue" },
                values: new object[,]
                {
                    { 1, "ENTITY PRINCIPAL 1" },
                    { 2, "ENTITY PRINCIPAL 2" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesManyToManyMN",
                columns: new[] { "EntityMNID", "EntityMID", "EntityMNValue", "EntityNID" },
                values: new object[,]
                {
                    { 1, 1, "ENTITY MN - 11", 1 },
                    { 2, 1, "ENTITY MN - 12", 2 },
                    { 3, 2, "ENTITY MN - 21", 1 },
                    { 4, 2, "ENTITY MN - 22", 2 }
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
                table: "EntitiesOneToOneDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "DEPENDENT 111", 1 },
                    { 2, "DEPENDENT 222", 2 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOwnedOneToManyDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "ENTITY DEPENDENT 11", 1 },
                    { 2, "ENTITY DEPENDENT 12", 1 },
                    { 3, "ENTITY DEPENDENT 21", 2 },
                    { 4, "ENTITY DEPENDENT 22", 2 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesOwnedOneToOneDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue" },
                values: new object[,]
                {
                    { 1, "ENTITY DEPENDENT 1" },
                    { 2, "ENTITY DEPENDENT 2" }
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToManyMN_EntityMID",
                table: "EntitiesManyToManyMN",
                column: "EntityMID");

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

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOwnedOneToManyDependent_EntityPrincipalID",
                table: "EntitiesOwnedOneToManyDependent",
                column: "EntityPrincipalID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMN");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedOneToOneDependent");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyM");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyN");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedOneToOnePrincipal");
        }
    }
}
