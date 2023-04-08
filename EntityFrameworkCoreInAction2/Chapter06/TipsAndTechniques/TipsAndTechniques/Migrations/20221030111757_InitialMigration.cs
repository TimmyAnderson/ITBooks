using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace TipsAndTechniques.Migrations
{
    public partial class InitialMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesConstructorsPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConstructorsPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesGroupByFunction",
                columns: table => new
                {
                    NumberID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Number = table.Column<int>(type: "INTEGER", nullable: false),
                    NumberAsText = table.Column<string>(type: "TEXT", nullable: true),
                    NumericValue = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesGroupByFunction", x => x.NumberID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHierarchical",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true),
                    Level = table.Column<int>(type: "INTEGER", nullable: false),
                    ForeignKeyID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHierarchical", x => x.EntityPrincipalID);
                    table.ForeignKey(
                        name: "FK_EntitiesHierarchical_EntitiesHierarchical_ForeignKeyID",
                        column: x => x.ForeignKeyID,
                        principalTable: "EntitiesHierarchical",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesIncludePrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesIncludePrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesLazyLoadingPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesLazyLoadingPrincipal", x => x.EntityPrincipalID);
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
                name: "EntitiesMaxPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesMaxPrincipal", x => x.EntityPrincipalID);
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
                name: "EntitiesConstructorsDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesConstructorsDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesConstructorsDependent_EntitiesConstructorsPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesConstructorsPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesIncludeDependent1",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesIncludeDependent1", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesIncludeDependent1_EntitiesIncludePrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesIncludePrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesIncludeDependent2",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesIncludeDependent2", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesIncludeDependent2_EntitiesIncludePrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesIncludePrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesIncludeDependent3",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesIncludeDependent3", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesIncludeDependent3_EntitiesIncludePrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesIncludePrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesLazyLoadingDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesLazyLoadingDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesLazyLoadingDependent_EntitiesLazyLoadingPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesLazyLoadingPrincipal",
                        principalColumn: "EntityPrincipalID",
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
                name: "EntitiesMaxDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesMaxDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesMaxDependent_EntitiesMaxPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesMaxPrincipal",
                        principalColumn: "EntityPrincipalID",
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

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesConstructorsDependent_EntityPrincipalID",
                table: "EntitiesConstructorsDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesHierarchical_ForeignKeyID",
                table: "EntitiesHierarchical",
                column: "ForeignKeyID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesIncludeDependent1_EntityPrincipalID",
                table: "EntitiesIncludeDependent1",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesIncludeDependent2_EntityPrincipalID",
                table: "EntitiesIncludeDependent2",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesIncludeDependent3_EntityPrincipalID",
                table: "EntitiesIncludeDependent3",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesLazyLoadingDependent_EntityPrincipalID",
                table: "EntitiesLazyLoadingDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToManyMN_EntityNID",
                table: "EntitiesManyToManyMN",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesMaxDependent_EntityPrincipalID",
                table: "EntitiesMaxDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyDependent_EntityPrincipalID",
                table: "EntitiesOneToManyDependent",
                column: "EntityPrincipalID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesConstructorsDependent");

            migrationBuilder.DropTable(
                name: "EntitiesGroupByFunction");

            migrationBuilder.DropTable(
                name: "EntitiesHierarchical");

            migrationBuilder.DropTable(
                name: "EntitiesIncludeDependent1");

            migrationBuilder.DropTable(
                name: "EntitiesIncludeDependent2");

            migrationBuilder.DropTable(
                name: "EntitiesIncludeDependent3");

            migrationBuilder.DropTable(
                name: "EntitiesLazyLoadingDependent");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMN");

            migrationBuilder.DropTable(
                name: "EntitiesMaxDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "TestEntities");

            migrationBuilder.DropTable(
                name: "EntitiesConstructorsPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesIncludePrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesLazyLoadingPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyM");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyN");

            migrationBuilder.DropTable(
                name: "EntitiesMaxPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");
        }
    }
}
