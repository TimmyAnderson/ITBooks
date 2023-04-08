using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ChangingDBContent.Migrations
{
    public partial class InitialMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyAutoM",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyAutoM", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyAutoN",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyAutoN", x => x.EntityNID);
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
                name: "EntitiesNumber",
                columns: table => new
                {
                    NumberID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Number = table.Column<int>(type: "INTEGER", nullable: false),
                    NumberAsText = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNumber", x => x.NumberID);
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
                name: "EntitiesZeroToManyPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToManyPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "TestEntities",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestEntities", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "CEntityManyToManyAutoMCEntityManyToManyAutoN",
                columns: table => new
                {
                    EntitiesMEntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntitiesNEntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CEntityManyToManyAutoMCEntityManyToManyAutoN", x => new { x.EntitiesMEntityMID, x.EntitiesNEntityNID });
                    table.ForeignKey(
                        name: "FK_CEntityManyToManyAutoMCEntityManyToManyAutoN_EntitiesManyToManyAutoM_EntitiesMEntityMID",
                        column: x => x.EntitiesMEntityMID,
                        principalTable: "EntitiesManyToManyAutoM",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_CEntityManyToManyAutoMCEntityManyToManyAutoN_EntitiesManyToManyAutoN_EntitiesNEntityNID",
                        column: x => x.EntitiesNEntityNID,
                        principalTable: "EntitiesManyToManyAutoN",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
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

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToManyDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToManyDependent_EntitiesZeroToManyPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToManyPrincipal",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_CEntityManyToManyAutoMCEntityManyToManyAutoN_EntitiesNEntityNID",
                table: "CEntityManyToManyAutoMCEntityManyToManyAutoN",
                column: "EntitiesNEntityNID");

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
                name: "IX_EntitiesZeroToManyDependent_EntityPrincipalID",
                table: "EntitiesZeroToManyDependent",
                column: "EntityPrincipalID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "CEntityManyToManyAutoMCEntityManyToManyAutoN");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMN");

            migrationBuilder.DropTable(
                name: "EntitiesNumber");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyDependent");

            migrationBuilder.DropTable(
                name: "TestEntities");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyAutoM");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyAutoN");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyM");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyN");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyPrincipal");
        }
    }
}
