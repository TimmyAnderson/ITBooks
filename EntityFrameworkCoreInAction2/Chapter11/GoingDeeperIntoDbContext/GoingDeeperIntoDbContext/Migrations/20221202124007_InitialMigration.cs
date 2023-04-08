using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace GoingDeeperIntoDbContext.Migrations
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
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesSnapshotPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesSnapshotPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesToSqlQuery",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityStringValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityDoubleValue = table.Column<double>(type: "REAL", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesToSqlQuery", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesToSqlQueryBackendData",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityStringValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityDoubleValue = table.Column<double>(type: "REAL", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesToSqlQueryBackendData", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalStringValue = table.Column<string>(type: "TEXT", nullable: true)
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
                name: "EntitiesOneToManyDependent",
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
                    table.PrimaryKey("PK_EntitiesOneToManyDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyDependent_EntitiesOneToManyPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesChangedNotificationsDependent",
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
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesChangedNotificationsDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyTrackingChangesChangedNotificationsDependent_EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent",
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
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent",
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
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyTrackingChangesSnapshotDependent",
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
                    table.PrimaryKey("PK_EntitiesOneToManyTrackingChangesSnapshotDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyTrackingChangesSnapshotDependent_EntitiesOneToManyTrackingChangesSnapshotPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyTrackingChangesSnapshotPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentIntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityDependentStringValue = table.Column<string>(type: "TEXT", nullable: true),
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
                name: "IX_EntitiesOneToManyDependent_EntityPrincipalID",
                table: "EntitiesOneToManyDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyTrackingChangesChangedNotificationsDependent_EntityPrincipalID",
                table: "EntitiesOneToManyTrackingChangesChangedNotificationsDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent_EntityPrincipalID",
                table: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent_EntityPrincipalID",
                table: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyTrackingChangesSnapshotDependent_EntityPrincipalID",
                table: "EntitiesOneToManyTrackingChangesSnapshotDependent",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToManyDependent_EntityPrincipalID",
                table: "EntitiesZeroToManyDependent",
                column: "EntityPrincipalID");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesChangedNotificationsDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesSnapshotDependent");

            migrationBuilder.DropTable(
                name: "EntitiesToSqlQuery");

            migrationBuilder.DropTable(
                name: "EntitiesToSqlQueryBackendData");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyDependent");

            migrationBuilder.DropTable(
                name: "TestEntities");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyTrackingChangesSnapshotPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyPrincipal");
        }
    }
}
