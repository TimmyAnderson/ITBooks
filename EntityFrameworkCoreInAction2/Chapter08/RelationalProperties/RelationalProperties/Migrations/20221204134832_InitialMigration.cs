using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace RelationalProperties.Migrations
{
    /// <inheritdoc />
    public partial class InitialMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EntitiesAttributeOnForeignKeyPrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAttributeOnForeignKeyPrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToMany1MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToMany1MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToMany1NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToMany1NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToMany2MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToMany2MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToMany2NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToMany2NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToManyMixedKeys1MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToManyMixedKeys1MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToManyMixedKeys1NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToManyMixedKeys1NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToManyMixedKeys2MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToManyMixedKeys2MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToManyMixedKeys2NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToManyMixedKeys2NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoZeroManyToMany1MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoZeroManyToMany1MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoZeroManyToMany1NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoZeroManyToMany1NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoZeroManyToMany2MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoZeroManyToMany2MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoZeroManyToMany2NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoZeroManyToMany2NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesCompositeForeignKeyPrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID1 = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalID2 = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesCompositeForeignKeyPrincipalDataAnnotations", x => new { x.EntityPrincipalID1, x.EntityPrincipalID2 });
                });

            migrationBuilder.CreateTable(
                name: "EntitiesForeignKeyName1PrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesForeignKeyName1PrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesForeignKeyName2PrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesForeignKeyName2PrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesForeignKeyName3PrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesForeignKeyName3PrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasAlternateKeyCompositeFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<string>(type: "TEXT", nullable: true),
                    MyAlternateKey1 = table.Column<string>(type: "TEXT", nullable: false),
                    MyAlternateKey2 = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHasAlternateKeyCompositeFluentAPI", x => x.EntityID);
                    table.UniqueConstraint("AK_EntitiesHasAlternateKeyCompositeFluentAPI_MyAlternateKey1_MyAlternateKey2", x => new { x.MyAlternateKey1, x.MyAlternateKey2 });
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasAlternateKeyFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<string>(type: "TEXT", nullable: true),
                    MyAlternateKey = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHasAlternateKeyFluentAPI", x => x.EntityID);
                    table.UniqueConstraint("AK_EntitiesHasAlternateKeyFluentAPI_MyAlternateKey", x => x.MyAlternateKey);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasConstraintNamePrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("My_PRIMARY_KEY_PRINCIPAL", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasPrincipalKeyCompositePrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true),
                    MyPrincipalKeyInEntityPrincipal1 = table.Column<string>(type: "TEXT", nullable: false),
                    MyPrincipalKeyInEntityPrincipal2 = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHasPrincipalKeyCompositePrincipalFluentAPI", x => x.EntityPrincipalID);
                    table.UniqueConstraint("AK_EntitiesHasPrincipalKeyCompositePrincipalFluentAPI_MyPrincipalKeyInEntityPrincipal1_MyPrincipalKeyInEntityPrincipal2", x => new { x.MyPrincipalKeyInEntityPrincipal1, x.MyPrincipalKeyInEntityPrincipal2 });
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasPrincipalKeyPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true),
                    MyPrincipalKeyInEntityPrincipal = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHasPrincipalKeyPrincipalFluentAPI", x => x.EntityPrincipalID);
                    table.UniqueConstraint("AK_EntitiesHasPrincipalKeyPrincipalFluentAPI_MyPrincipalKeyInEntityPrincipal", x => x.MyPrincipalKeyInEntityPrincipal);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesInversePropertyPrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesInversePropertyPrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToMany1MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToMany1MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToMany1NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToMany1NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToMany2MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToMany2MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToMany2NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToMany2NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMixedKeys1MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMixedKeys1MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMixedKeys1NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMixedKeys1NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMixedKeys2MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMixedKeys2MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMixedKeys2NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMixedKeys2NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNoForeignKey1PrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNoForeignKey1PrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNoForeignKey2PrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNoForeignKey2PrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNoForeignKey3PrincipalConventions",
                columns: table => new
                {
                    CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNoForeignKey3PrincipalConventions", x => x.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteCascadeNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteCascadeNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteNoActionNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteNoActionNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteRestrictNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteRestrictNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteSetNullNullPrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteSetNullNullPrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToMany1PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToMany1PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToMany2PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToMany2PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyPrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyPrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyPrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyPrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOne1PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOne1PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOne2PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOne2PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneMixedKeys1PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneMixedKeys1PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneMixedKeys2PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneMixedKeys2PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOnePrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOnePrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOnePrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOnePrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedTypeInMultiTables",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedTypeInMultiTables", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedTypeInOneTable",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<string>(type: "TEXT", nullable: true),
                    OwnedTypeDataAnnotationsOwnedTypeInt = table.Column<int>(name: "OwnedTypeDataAnnotations_OwnedTypeInt", type: "INTEGER", nullable: true),
                    OwnedTypeDataAnnotationsOwnedTypeString = table.Column<string>(name: "OwnedTypeDataAnnotations_OwnedTypeString", type: "TEXT", nullable: true),
                    OwnedTypeDataAnnotationsOwnedTypeStringRequired = table.Column<string>(name: "OwnedTypeDataAnnotations_OwnedTypeStringRequired", type: "TEXT", nullable: true),
                    OwnedTypeDataAnnotationsRequiredOwnedTypeInt = table.Column<int>(name: "OwnedTypeDataAnnotationsRequired_OwnedTypeInt", type: "INTEGER", nullable: false),
                    OwnedTypeDataAnnotationsRequiredOwnedTypeString = table.Column<string>(name: "OwnedTypeDataAnnotationsRequired_OwnedTypeString", type: "TEXT", nullable: true),
                    OwnedTypeDataAnnotationsRequiredOwnedTypeStringRequired = table.Column<string>(name: "OwnedTypeDataAnnotationsRequired_OwnedTypeStringRequired", type: "TEXT", nullable: false),
                    OwnedTypeFluentAPIOwnedTypeInt = table.Column<int>(name: "OwnedTypeFluentAPI_OwnedTypeInt", type: "INTEGER", nullable: true),
                    OwnedTypeFluentAPIOwnedTypeString = table.Column<string>(name: "OwnedTypeFluentAPI_OwnedTypeString", type: "TEXT", nullable: true),
                    OwnedTypeFluentAPIOwnedTypeStringRequired = table.Column<string>(name: "OwnedTypeFluentAPI_OwnedTypeStringRequired", type: "TEXT", nullable: true),
                    NestedOwnedTypeNestedOwnedTypeInt = table.Column<int>(name: "NestedOwnedType_NestedOwnedTypeInt", type: "INTEGER", nullable: true),
                    NestedOwnedTypeNestedOwnedTypeString = table.Column<string>(name: "NestedOwnedType_NestedOwnedTypeString", type: "TEXT", nullable: true),
                    NestedOwnedTypeOwnedType1OwnedTypeInt = table.Column<int>(name: "NestedOwnedType_OwnedType1_OwnedTypeInt", type: "INTEGER", nullable: true),
                    NestedOwnedTypeOwnedType1OwnedTypeString = table.Column<string>(name: "NestedOwnedType_OwnedType1_OwnedTypeString", type: "TEXT", nullable: true),
                    NestedOwnedTypeOwnedType1OwnedTypeStringRequired = table.Column<string>(name: "NestedOwnedType_OwnedType1_OwnedTypeStringRequired", type: "TEXT", nullable: true),
                    NestedOwnedTypeOwnedType2OwnedTypeInt = table.Column<int>(name: "NestedOwnedType_OwnedType2_OwnedTypeInt", type: "INTEGER", nullable: true),
                    NestedOwnedTypeOwnedType2OwnedTypeString = table.Column<string>(name: "NestedOwnedType_OwnedType2_OwnedTypeString", type: "TEXT", nullable: true),
                    NestedOwnedTypeOwnedType2OwnedTypeStringRequired = table.Column<string>(name: "NestedOwnedType_OwnedType2_OwnedTypeStringRequired", type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedTypeInOneTable", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOwnedTypeOneAndMany",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityValue = table.Column<string>(type: "TEXT", nullable: true),
                    OwnedTypeOneOwnedTypeInt = table.Column<int>(name: "OwnedTypeOne_OwnedTypeInt", type: "INTEGER", nullable: true),
                    OwnedTypeOneOwnedTypeString = table.Column<string>(name: "OwnedTypeOne_OwnedTypeString", type: "TEXT", nullable: true),
                    OwnedTypeOneOwnedTypeStringRequired = table.Column<string>(name: "OwnedTypeOne_OwnedTypeStringRequired", type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOwnedTypeOneAndMany", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesRequiredFalsePrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesRequiredFalsePrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesRequiredTruePrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesRequiredTruePrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTablePerHierarchyBaseConventions",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    BaseValue = table.Column<string>(type: "TEXT", nullable: true),
                    Discriminator = table.Column<string>(type: "TEXT", nullable: false),
                    DerivedValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    MySAMENAME1 = table.Column<string>(name: "My_SAME_NAME_1", type: "TEXT", nullable: true),
                    MySHAREDCOLUMN = table.Column<string>(name: "My_SHARED_COLUMN", type: "TEXT", nullable: true),
                    DerivedValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    MySAMENAME2 = table.Column<string>(name: "My_SAME_NAME_2", type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTablePerHierarchyBaseConventions", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTablePerHierarchyBaseFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Discriminator = table.Column<int>(type: "INTEGER", nullable: false),
                    BaseValue = table.Column<string>(type: "TEXT", nullable: true),
                    DerivedValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    MySAMENAME1 = table.Column<string>(name: "My_SAME_NAME_1", type: "TEXT", nullable: true),
                    MySHAREDCOLUMN = table.Column<string>(name: "My_SHARED_COLUMN", type: "TEXT", nullable: true),
                    DerivedValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    MySAMENAME2 = table.Column<string>(name: "My_SAME_NAME_2", type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTablePerHierarchyBaseFluentAPI", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTablePerTypeBaseFluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    BaseValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTablePerTypeBaseFluentAPI", x => x.EntityID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTableSplittingFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityDependentValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    MySHAREDCOLUMN = table.Column<string>(name: "My_SHARED_COLUMN", type: "TEXT", nullable: true),
                    EntityDependentValue2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTableSplittingFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroManyToMany1MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroManyToMany1MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroManyToMany1NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroManyToMany1NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroManyToMany2MFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroManyToMany2MFluentAPI", x => x.EntityMID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroManyToMany2NFluentAPI",
                columns: table => new
                {
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroManyToMany2NFluentAPI", x => x.EntityNID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToMany1PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToMany1PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToMany2PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToMany2PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyPrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToManyPrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyPrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToManyPrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOne1PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOne1PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOne2PrincipalFluentAPI",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOne2PrincipalFluentAPI", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOnePrincipalConventions",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOnePrincipalConventions", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOnePrincipalDataAnnotations",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOnePrincipalDataAnnotations", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "My_PROPERTY_BAG_PRINCIPAL",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    ValueInt = table.Column<int>(type: "INTEGER", nullable: false),
                    ValueString = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_My_PROPERTY_BAG_PRINCIPAL", x => x.ID);
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
                name: "EntitiesAttributeOnForeignKeyDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAttributeOnForeignKeyDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesAttributeOnForeignKeyDependentDataAnnotations_EntitiesAttributeOnForeignKeyPrincipalDataAnnotations_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "EntitiesAttributeOnForeignKeyPrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAttributeOnNavigationPropertyDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAttributeOnNavigationPropertyDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesAttributeOnNavigationPropertyDependentDataAnnotations_EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToMany1MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToMany1MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToMany1MNFluentAPI_EntitiesAutoManyToMany1MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesAutoManyToMany1MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToMany1MNFluentAPI_EntitiesAutoManyToMany1NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesAutoManyToMany1NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToMany2MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToMany2MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToMany2MNFluentAPI_EntitiesAutoManyToMany2MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesAutoManyToMany2MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToMany2MNFluentAPI_EntitiesAutoManyToMany2NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesAutoManyToMany2NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToManyMixedKeys1MNFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToManyMixedKeys1MNFluentAPI", x => new { x.EntityMID, x.EntityNID });
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToManyMixedKeys1MNFluentAPI_EntitiesAutoManyToManyMixedKeys1MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesAutoManyToManyMixedKeys1MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToManyMixedKeys1MNFluentAPI_EntitiesAutoManyToManyMixedKeys1NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesAutoManyToManyMixedKeys1NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoManyToManyMixedKeys2MNFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoManyToManyMixedKeys2MNFluentAPI", x => new { x.EntityMID, x.EntityNID });
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToManyMixedKeys2MNFluentAPI_EntitiesAutoManyToManyMixedKeys2MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesAutoManyToManyMixedKeys2MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoManyToManyMixedKeys2MNFluentAPI_EntitiesAutoManyToManyMixedKeys2NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesAutoManyToManyMixedKeys2NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoZeroManyToMany1MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: true),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoZeroManyToMany1MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoZeroManyToMany1MNFluentAPI_EntitiesAutoZeroManyToMany1MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesAutoZeroManyToMany1MFluentAPI",
                        principalColumn: "EntityMID");
                    table.ForeignKey(
                        name: "FK_EntitiesAutoZeroManyToMany1MNFluentAPI_EntitiesAutoZeroManyToMany1NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesAutoZeroManyToMany1NFluentAPI",
                        principalColumn: "EntityNID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoZeroManyToMany2MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: true),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoZeroManyToMany2MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesAutoZeroManyToMany2MNFluentAPI_EntitiesAutoZeroManyToMany2MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesAutoZeroManyToMany2MFluentAPI",
                        principalColumn: "EntityMID");
                    table.ForeignKey(
                        name: "FK_EntitiesAutoZeroManyToMany2MNFluentAPI_EntitiesAutoZeroManyToMany2NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesAutoZeroManyToMany2NFluentAPI",
                        principalColumn: "EntityNID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesCompositeForeignKeyDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID1 = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityPrincipalID2 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesCompositeForeignKeyDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesCompositeForeignKeyDependentDataAnnotations_EntitiesCompositeForeignKeyPrincipalDataAnnotations_EntityPrincipalID1_EntityPrincipalID2",
                        columns: x => new { x.EntityPrincipalID1, x.EntityPrincipalID2 },
                        principalTable: "EntitiesCompositeForeignKeyPrincipalDataAnnotations",
                        principalColumns: new[] { "EntityPrincipalID1", "EntityPrincipalID2" },
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesForeignKeyName1DependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesForeignKeyName1DependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesForeignKeyName1DependentConventions_EntitiesForeignKeyName1PrincipalConventions_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesForeignKeyName1PrincipalConventions",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesForeignKeyName2DependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    CEntityForeignKeyName2PrincipalConventionsEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesForeignKeyName2DependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesForeignKeyName2DependentConventions_EntitiesForeignKeyName2PrincipalConventions_CEntityForeignKeyName2PrincipalConventionsEntityPrincipalID",
                        column: x => x.CEntityForeignKeyName2PrincipalConventionsEntityPrincipalID,
                        principalTable: "EntitiesForeignKeyName2PrincipalConventions",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesForeignKeyName3DependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesForeignKeyName3DependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesForeignKeyName3DependentConventions_EntitiesForeignKeyName3PrincipalConventions_EntityPrincipalEntityPrincipalID",
                        column: x => x.EntityPrincipalEntityPrincipalID,
                        principalTable: "EntitiesForeignKeyName3PrincipalConventions",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasConstraintNameDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("My_PRIMARY_KEY_DEPENDENT", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "My_FOREIGN_KEY_CONSTRAINT",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesHasConstraintNamePrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasPrincipalKeyCompositeDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    MyPrincipalKeyInEntityDependent1 = table.Column<string>(type: "TEXT", nullable: true),
                    MyPrincipalKeyInEntityDependent2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHasPrincipalKeyCompositeDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesHasPrincipalKeyCompositeDependentFluentAPI_EntitiesHasPrincipalKeyCompositePrincipalFluentAPI_MyPrincipalKeyInEntityDependent1_MyPrincipalKeyInEntityDependent2",
                        columns: x => new { x.MyPrincipalKeyInEntityDependent1, x.MyPrincipalKeyInEntityDependent2 },
                        principalTable: "EntitiesHasPrincipalKeyCompositePrincipalFluentAPI",
                        principalColumns: new[] { "MyPrincipalKeyInEntityPrincipal1", "MyPrincipalKeyInEntityPrincipal2" });
                });

            migrationBuilder.CreateTable(
                name: "EntitiesHasPrincipalKeyDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    MyPrincipalKeyInEntityDependent = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesHasPrincipalKeyDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesHasPrincipalKeyDependentFluentAPI_EntitiesHasPrincipalKeyPrincipalFluentAPI_MyPrincipalKeyInEntityDependent",
                        column: x => x.MyPrincipalKeyInEntityDependent,
                        principalTable: "EntitiesHasPrincipalKeyPrincipalFluentAPI",
                        principalColumn: "MyPrincipalKeyInEntityPrincipal");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesInversePropertyDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID1 = table.Column<int>(type: "INTEGER", nullable: true),
                    EntityPrincipalID2 = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesInversePropertyDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesInversePropertyDependentDataAnnotations_EntitiesInversePropertyPrincipalDataAnnotations_EntityPrincipalID1",
                        column: x => x.EntityPrincipalID1,
                        principalTable: "EntitiesInversePropertyPrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID");
                    table.ForeignKey(
                        name: "FK_EntitiesInversePropertyDependentDataAnnotations_EntitiesInversePropertyPrincipalDataAnnotations_EntityPrincipalID2",
                        column: x => x.EntityPrincipalID2,
                        principalTable: "EntitiesInversePropertyPrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToMany1MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToMany1MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToMany1MNFluentAPI_EntitiesManyToMany1MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesManyToMany1MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToMany1MNFluentAPI_EntitiesManyToMany1NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesManyToMany1NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToMany2MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToMany2MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToMany2MNFluentAPI_EntitiesManyToMany2MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesManyToMany2MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToMany2MNFluentAPI_EntitiesManyToMany2NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesManyToMany2NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMixedKeys1MNFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMixedKeys1MNFluentAPI", x => new { x.EntityMID, x.EntityNID });
                    table.ForeignKey(
                        name: "FK_EntitiesManyToManyMixedKeys1MNFluentAPI_EntitiesManyToManyMixedKeys1MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesManyToManyMixedKeys1MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToManyMixedKeys1MNFluentAPI_EntitiesManyToManyMixedKeys1NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesManyToManyMixedKeys1NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesManyToManyMixedKeys2MNFluentAPI",
                columns: table => new
                {
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesManyToManyMixedKeys2MNFluentAPI", x => new { x.EntityMID, x.EntityNID });
                    table.ForeignKey(
                        name: "FK_EntitiesManyToManyMixedKeys2MNFluentAPI_EntitiesManyToManyMixedKeys2MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesManyToManyMixedKeys2MFluentAPI",
                        principalColumn: "EntityMID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_EntitiesManyToManyMixedKeys2MNFluentAPI_EntitiesManyToManyMixedKeys2NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesManyToManyMixedKeys2NFluentAPI",
                        principalColumn: "EntityNID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNoForeignKey1DependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNoForeignKey1DependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesNoForeignKey1DependentConventions_EntitiesNoForeignKey1PrincipalConventions_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesNoForeignKey1PrincipalConventions",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNoForeignKey2DependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    CEntityNoForeignKey2PrincipalConventionsEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNoForeignKey2DependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesNoForeignKey2DependentConventions_EntitiesNoForeignKey2PrincipalConventions_CEntityNoForeignKey2PrincipalConventionsEntityPrincipalID",
                        column: x => x.CEntityNoForeignKey2PrincipalConventionsEntityPrincipalID,
                        principalTable: "EntitiesNoForeignKey2PrincipalConventions",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNoForeignKey3DependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNoForeignKey3DependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesNoForeignKey3DependentConventions_EntitiesNoForeignKey3PrincipalConventions_CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID",
                        column: x => x.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID,
                        principalTable: "EntitiesNoForeignKey3PrincipalConventions",
                        principalColumn: "CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteCascadeNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteCascadeNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteCascadeNotNullDependentFluentAPI_EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteCascadeNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteCascadeNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteCascadeNullDependentFluentAPI_EntitiesOnDeleteCascadeNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteCascadeNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI_EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientCascadeNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientCascadeNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteClientCascadeNullDependentFluentAPI_EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI_EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientNoActionNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientNoActionNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteClientNoActionNullDependentFluentAPI_EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI_EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteClientSetNullNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteClientSetNullNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteClientSetNullNullDependentFluentAPI_EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteNoActionNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteNoActionNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteNoActionNotNullDependentFluentAPI_EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteNoActionNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteNoActionNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteNoActionNullDependentFluentAPI_EntitiesOnDeleteNoActionNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteNoActionNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteRestrictNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteRestrictNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteRestrictNotNullDependentFluentAPI_EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteRestrictNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteRestrictNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteRestrictNullDependentFluentAPI_EntitiesOnDeleteRestrictNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteRestrictNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteSetNullNotNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteSetNullNotNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteSetNullNotNullDependentFluentAPI_EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.SetNull);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOnDeleteSetNullNullDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOnDeleteSetNullNullDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOnDeleteSetNullNullDependentFluentAPI_EntitiesOnDeleteSetNullNullPrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOnDeleteSetNullNullPrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.SetNull);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToMany1DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToMany1DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToMany1DependentFluentAPI_EntitiesOneToMany1PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToMany1PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToMany2DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToMany2DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToMany2DependentFluentAPI_EntitiesOneToMany2PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToMany2PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyDependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyDependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyDependentConventions_EntitiesOneToManyPrincipalConventions_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToManyPrincipalConventions",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToManyDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToManyDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToManyDependentDataAnnotations_EntitiesOneToManyPrincipalDataAnnotations_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "EntitiesOneToManyPrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOne1DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOne1DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOne1DependentFluentAPI_EntitiesOneToOne1PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToOne1PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOne2DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOne2DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOne2DependentFluentAPI_EntitiesOneToOne2PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToOne2PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneMixedKeys1DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneMixedKeys1DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneMixedKeys1DependentFluentAPI_EntitiesOneToOneMixedKeys1PrincipalFluentAPI_EntityDependentID",
                        column: x => x.EntityDependentID,
                        principalTable: "EntitiesOneToOneMixedKeys1PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneMixedKeys2DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneMixedKeys2DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneMixedKeys2DependentFluentAPI_EntitiesOneToOneMixedKeys2PrincipalFluentAPI_EntityDependentID",
                        column: x => x.EntityDependentID,
                        principalTable: "EntitiesOneToOneMixedKeys2PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneDependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneDependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneDependentConventions_EntitiesOneToOnePrincipalConventions_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesOneToOnePrincipalConventions",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesOneToOneDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesOneToOneDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesOneToOneDependentDataAnnotations_EntitiesOneToOnePrincipalDataAnnotations_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "EntitiesOneToOnePrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "OwnedType1",
                columns: table => new
                {
                    CEntityOwnedTypeInMultiTablesEntityID = table.Column<int>(type: "INTEGER", nullable: false),
                    OwnedTypeInt = table.Column<int>(type: "INTEGER", nullable: false),
                    OwnedTypeString = table.Column<string>(type: "TEXT", nullable: true),
                    OwnedTypeStringRequired = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_OwnedType1", x => x.CEntityOwnedTypeInMultiTablesEntityID);
                    table.ForeignKey(
                        name: "FK_OwnedType1_EntitiesOwnedTypeInMultiTables_CEntityOwnedTypeInMultiTablesEntityID",
                        column: x => x.CEntityOwnedTypeInMultiTablesEntityID,
                        principalTable: "EntitiesOwnedTypeInMultiTables",
                        principalColumn: "EntityID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "OwnedType2",
                columns: table => new
                {
                    CEntityOwnedTypeInMultiTablesEntityID = table.Column<int>(type: "INTEGER", nullable: false),
                    OwnedTypeInt = table.Column<int>(type: "INTEGER", nullable: false),
                    OwnedTypeString = table.Column<string>(type: "TEXT", nullable: true),
                    OwnedTypeStringRequired = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_OwnedType2", x => x.CEntityOwnedTypeInMultiTablesEntityID);
                    table.ForeignKey(
                        name: "FK_OwnedType2_EntitiesOwnedTypeInMultiTables_CEntityOwnedTypeInMultiTablesEntityID",
                        column: x => x.CEntityOwnedTypeInMultiTablesEntityID,
                        principalTable: "EntitiesOwnedTypeInMultiTables",
                        principalColumn: "EntityID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "COwnedTypeMany",
                columns: table => new
                {
                    OwnedTypeID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    OwnedTypeInt = table.Column<int>(type: "INTEGER", nullable: false),
                    OwnedTypeString = table.Column<string>(type: "TEXT", nullable: true),
                    OwnedTypeStringRequired = table.Column<string>(type: "TEXT", nullable: false),
                    CEntityOwnedTypeOneAndManyEntityID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_COwnedTypeMany", x => x.OwnedTypeID);
                    table.ForeignKey(
                        name: "FK_COwnedTypeMany_EntitiesOwnedTypeOneAndMany_CEntityOwnedTypeOneAndManyEntityID",
                        column: x => x.CEntityOwnedTypeOneAndManyEntityID,
                        principalTable: "EntitiesOwnedTypeOneAndMany",
                        principalColumn: "EntityID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesRequiredFalseDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesRequiredFalseDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesRequiredFalseDependentFluentAPI_EntitiesRequiredFalsePrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesRequiredFalsePrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesRequiredTrueDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesRequiredTrueDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesRequiredTrueDependentFluentAPI_EntitiesRequiredTruePrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesRequiredTruePrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTablePerTypeDerived1FluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    DerivedValue1 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTablePerTypeDerived1FluentAPI", x => x.EntityID);
                    table.ForeignKey(
                        name: "FK_EntitiesTablePerTypeDerived1FluentAPI_EntitiesTablePerTypeBaseFluentAPI_EntityID",
                        column: x => x.EntityID,
                        principalTable: "EntitiesTablePerTypeBaseFluentAPI",
                        principalColumn: "EntityID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesTablePerTypeDerived2FluentAPI",
                columns: table => new
                {
                    EntityID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    DerivedValue2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesTablePerTypeDerived2FluentAPI", x => x.EntityID);
                    table.ForeignKey(
                        name: "FK_EntitiesTablePerTypeDerived2FluentAPI_EntitiesTablePerTypeBaseFluentAPI_EntityID",
                        column: x => x.EntityID,
                        principalTable: "EntitiesTablePerTypeBaseFluentAPI",
                        principalColumn: "EntityID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroManyToMany1MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: true),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroManyToMany1MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroManyToMany1MNFluentAPI_EntitiesZeroManyToMany1MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesZeroManyToMany1MFluentAPI",
                        principalColumn: "EntityMID");
                    table.ForeignKey(
                        name: "FK_EntitiesZeroManyToMany1MNFluentAPI_EntitiesZeroManyToMany1NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesZeroManyToMany1NFluentAPI",
                        principalColumn: "EntityNID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroManyToMany2MNFluentAPI",
                columns: table => new
                {
                    EntityMNID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityMNValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityMID = table.Column<int>(type: "INTEGER", nullable: true),
                    EntityNID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroManyToMany2MNFluentAPI", x => x.EntityMNID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroManyToMany2MNFluentAPI_EntitiesZeroManyToMany2MFluentAPI_EntityMID",
                        column: x => x.EntityMID,
                        principalTable: "EntitiesZeroManyToMany2MFluentAPI",
                        principalColumn: "EntityMID");
                    table.ForeignKey(
                        name: "FK_EntitiesZeroManyToMany2MNFluentAPI_EntitiesZeroManyToMany2NFluentAPI_EntityNID",
                        column: x => x.EntityNID,
                        principalTable: "EntitiesZeroManyToMany2NFluentAPI",
                        principalColumn: "EntityNID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToMany1DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToMany1DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToMany1DependentFluentAPI_EntitiesZeroToMany1PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToMany1PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToMany2DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToMany2DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToMany2DependentFluentAPI_EntitiesZeroToMany2PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToMany2PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyDependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToManyDependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToManyDependentConventions_EntitiesZeroToManyPrincipalConventions_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToManyPrincipalConventions",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToManyDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToManyDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToManyDependentDataAnnotations_EntitiesZeroToManyPrincipalDataAnnotations_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "EntitiesZeroToManyPrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOne1DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOne1DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToOne1DependentFluentAPI_EntitiesZeroToOne1PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToOne1PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOne2DependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOne2DependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToOne2DependentFluentAPI_EntitiesZeroToOne2PrincipalFluentAPI_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToOne2PrincipalFluentAPI",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOneDependentConventions",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOneDependentConventions", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToOneDependentConventions_EntitiesZeroToOnePrincipalConventions_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesZeroToOnePrincipalConventions",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesZeroToOneDependentDataAnnotations",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    ForeignKeyEntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesZeroToOneDependentDataAnnotations", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesZeroToOneDependentDataAnnotations_EntitiesZeroToOnePrincipalDataAnnotations_ForeignKeyEntityPrincipalID",
                        column: x => x.ForeignKeyEntityPrincipalID,
                        principalTable: "EntitiesZeroToOnePrincipalDataAnnotations",
                        principalColumn: "EntityPrincipalID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesPropertyBagDependentFluentAPI",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPropertyBagDependentFluentAPI", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesPropertyBagDependentFluentAPI_My_PROPERTY_BAG_PRINCIPAL_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "My_PROPERTY_BAG_PRINCIPAL",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_COwnedTypeMany_CEntityOwnedTypeOneAndManyEntityID",
                table: "COwnedTypeMany",
                column: "CEntityOwnedTypeOneAndManyEntityID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAttributeOnForeignKeyDependentDataAnnotations_ForeignKeyEntityPrincipalID",
                table: "EntitiesAttributeOnForeignKeyDependentDataAnnotations",
                column: "ForeignKeyEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAttributeOnNavigationPropertyDependentDataAnnotations_ForeignKeyEntityPrincipalID",
                table: "EntitiesAttributeOnNavigationPropertyDependentDataAnnotations",
                column: "ForeignKeyEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoManyToMany1MNFluentAPI_EntityMID",
                table: "EntitiesAutoManyToMany1MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoManyToMany1MNFluentAPI_EntityNID",
                table: "EntitiesAutoManyToMany1MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoManyToMany2MNFluentAPI_EntityMID",
                table: "EntitiesAutoManyToMany2MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoManyToMany2MNFluentAPI_EntityNID",
                table: "EntitiesAutoManyToMany2MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoManyToManyMixedKeys1MNFluentAPI_EntityNID",
                table: "EntitiesAutoManyToManyMixedKeys1MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoManyToManyMixedKeys2MNFluentAPI_EntityNID",
                table: "EntitiesAutoManyToManyMixedKeys2MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoZeroManyToMany1MNFluentAPI_EntityMID",
                table: "EntitiesAutoZeroManyToMany1MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoZeroManyToMany1MNFluentAPI_EntityNID",
                table: "EntitiesAutoZeroManyToMany1MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoZeroManyToMany2MNFluentAPI_EntityMID",
                table: "EntitiesAutoZeroManyToMany2MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesAutoZeroManyToMany2MNFluentAPI_EntityNID",
                table: "EntitiesAutoZeroManyToMany2MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesCompositeForeignKeyDependentDataAnnotations_EntityPrincipalID1_EntityPrincipalID2",
                table: "EntitiesCompositeForeignKeyDependentDataAnnotations",
                columns: new[] { "EntityPrincipalID1", "EntityPrincipalID2" });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesForeignKeyName1DependentConventions_EntityPrincipalID",
                table: "EntitiesForeignKeyName1DependentConventions",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesForeignKeyName2DependentConventions_CEntityForeignKeyName2PrincipalConventionsEntityPrincipalID",
                table: "EntitiesForeignKeyName2DependentConventions",
                column: "CEntityForeignKeyName2PrincipalConventionsEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesForeignKeyName3DependentConventions_EntityPrincipalEntityPrincipalID",
                table: "EntitiesForeignKeyName3DependentConventions",
                column: "EntityPrincipalEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesHasConstraintNameDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesHasConstraintNameDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesHasPrincipalKeyCompositeDependentFluentAPI_MyPrincipalKeyInEntityDependent1_MyPrincipalKeyInEntityDependent2",
                table: "EntitiesHasPrincipalKeyCompositeDependentFluentAPI",
                columns: new[] { "MyPrincipalKeyInEntityDependent1", "MyPrincipalKeyInEntityDependent2" });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesHasPrincipalKeyDependentFluentAPI_MyPrincipalKeyInEntityDependent",
                table: "EntitiesHasPrincipalKeyDependentFluentAPI",
                column: "MyPrincipalKeyInEntityDependent");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesInversePropertyDependentDataAnnotations_EntityPrincipalID1",
                table: "EntitiesInversePropertyDependentDataAnnotations",
                column: "EntityPrincipalID1");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesInversePropertyDependentDataAnnotations_EntityPrincipalID2",
                table: "EntitiesInversePropertyDependentDataAnnotations",
                column: "EntityPrincipalID2");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToMany1MNFluentAPI_EntityMID",
                table: "EntitiesManyToMany1MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToMany1MNFluentAPI_EntityNID",
                table: "EntitiesManyToMany1MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToMany2MNFluentAPI_EntityMID",
                table: "EntitiesManyToMany2MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToMany2MNFluentAPI_EntityNID",
                table: "EntitiesManyToMany2MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToManyMixedKeys1MNFluentAPI_EntityNID",
                table: "EntitiesManyToManyMixedKeys1MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesManyToManyMixedKeys2MNFluentAPI_EntityNID",
                table: "EntitiesManyToManyMixedKeys2MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesNoForeignKey1DependentConventions_EntityPrincipalID",
                table: "EntitiesNoForeignKey1DependentConventions",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesNoForeignKey2DependentConventions_CEntityNoForeignKey2PrincipalConventionsEntityPrincipalID",
                table: "EntitiesNoForeignKey2DependentConventions",
                column: "CEntityNoForeignKey2PrincipalConventionsEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesNoForeignKey3DependentConventions_CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID",
                table: "EntitiesNoForeignKey3DependentConventions",
                column: "CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteCascadeNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteCascadeNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteCascadeNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteCascadeNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteClientCascadeNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteClientCascadeNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteClientNoActionNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteClientNoActionNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteClientSetNullNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteClientSetNullNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteNoActionNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteNoActionNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteNoActionNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteNoActionNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteRestrictNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteRestrictNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteRestrictNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteRestrictNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteSetNullNotNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteSetNullNotNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOnDeleteSetNullNullDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOnDeleteSetNullNullDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToMany1DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOneToMany1DependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToMany2DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOneToMany2DependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyDependentConventions_EntityPrincipalID",
                table: "EntitiesOneToManyDependentConventions",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToManyDependentDataAnnotations_ForeignKeyEntityPrincipalID",
                table: "EntitiesOneToManyDependentDataAnnotations",
                column: "ForeignKeyEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOne1DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOneToOne1DependentFluentAPI",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOne2DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesOneToOne2DependentFluentAPI",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOneDependentConventions_EntityPrincipalID",
                table: "EntitiesOneToOneDependentConventions",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesOneToOneDependentDataAnnotations_ForeignKeyEntityPrincipalID",
                table: "EntitiesOneToOneDependentDataAnnotations",
                column: "ForeignKeyEntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesPropertyBagDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesPropertyBagDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesRequiredFalseDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesRequiredFalseDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesRequiredTrueDependentFluentAPI_EntityPrincipalID",
                table: "EntitiesRequiredTrueDependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroManyToMany1MNFluentAPI_EntityMID",
                table: "EntitiesZeroManyToMany1MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroManyToMany1MNFluentAPI_EntityNID",
                table: "EntitiesZeroManyToMany1MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroManyToMany2MNFluentAPI_EntityMID",
                table: "EntitiesZeroManyToMany2MNFluentAPI",
                column: "EntityMID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroManyToMany2MNFluentAPI_EntityNID",
                table: "EntitiesZeroManyToMany2MNFluentAPI",
                column: "EntityNID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToMany1DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesZeroToMany1DependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToMany2DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesZeroToMany2DependentFluentAPI",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToManyDependentConventions_EntityPrincipalID",
                table: "EntitiesZeroToManyDependentConventions",
                column: "EntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToManyDependentDataAnnotations_ForeignKeyEntityPrincipalID",
                table: "EntitiesZeroToManyDependentDataAnnotations",
                column: "ForeignKeyEntityPrincipalID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToOne1DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesZeroToOne1DependentFluentAPI",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToOne2DependentFluentAPI_EntityPrincipalID",
                table: "EntitiesZeroToOne2DependentFluentAPI",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToOneDependentConventions_EntityPrincipalID",
                table: "EntitiesZeroToOneDependentConventions",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesZeroToOneDependentDataAnnotations_ForeignKeyEntityPrincipalID",
                table: "EntitiesZeroToOneDependentDataAnnotations",
                column: "ForeignKeyEntityPrincipalID",
                unique: true);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "COwnedTypeMany");

            migrationBuilder.DropTable(
                name: "EntitiesAttributeOnForeignKeyDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesAttributeOnNavigationPropertyDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToMany1MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToMany2MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToManyMixedKeys1MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToManyMixedKeys2MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoZeroManyToMany1MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoZeroManyToMany2MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesCompositeForeignKeyDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesForeignKeyName1DependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesForeignKeyName2DependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesForeignKeyName3DependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesHasAlternateKeyCompositeFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesHasAlternateKeyFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesHasConstraintNameDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesHasPrincipalKeyCompositeDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesHasPrincipalKeyDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesInversePropertyDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesManyToMany1MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToMany2MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMixedKeys1MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMixedKeys2MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesNoForeignKey1DependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesNoForeignKey2DependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesNoForeignKey3DependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteCascadeNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteCascadeNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientCascadeNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientNoActionNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientSetNullNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteNoActionNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteNoActionNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteRestrictNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteRestrictNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteSetNullNotNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteSetNullNullDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToMany1DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToMany2DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOne1DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOne2DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneMixedKeys1DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneMixedKeys2DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedTypeInOneTable");

            migrationBuilder.DropTable(
                name: "EntitiesPropertyBagDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesRequiredFalseDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesRequiredTrueDependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesTablePerHierarchyBaseConventions");

            migrationBuilder.DropTable(
                name: "EntitiesTablePerHierarchyBaseFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesTablePerTypeDerived1FluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesTablePerTypeDerived2FluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesTableSplittingFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroManyToMany1MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroManyToMany2MNFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToMany1DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToMany2DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyDependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOne1DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOne2DependentFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOneDependentConventions");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOneDependentDataAnnotations");

            migrationBuilder.DropTable(
                name: "OwnedType1");

            migrationBuilder.DropTable(
                name: "OwnedType2");

            migrationBuilder.DropTable(
                name: "TestEntities");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedTypeOneAndMany");

            migrationBuilder.DropTable(
                name: "EntitiesAttributeOnForeignKeyPrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToMany1MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToMany1NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToMany2MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToMany2NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToManyMixedKeys1MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToManyMixedKeys1NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToManyMixedKeys2MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoManyToManyMixedKeys2NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoZeroManyToMany1MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoZeroManyToMany1NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoZeroManyToMany2MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesAutoZeroManyToMany2NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesCompositeForeignKeyPrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesForeignKeyName1PrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesForeignKeyName2PrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesForeignKeyName3PrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesHasConstraintNamePrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesHasPrincipalKeyCompositePrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesHasPrincipalKeyPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesInversePropertyPrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesManyToMany1MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToMany1NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToMany2MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToMany2NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMixedKeys1MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMixedKeys1NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMixedKeys2MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesManyToManyMixedKeys2NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesNoForeignKey1PrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesNoForeignKey2PrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesNoForeignKey3PrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteCascadeNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteNoActionNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteRestrictNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOnDeleteSetNullNullPrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToMany1PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToMany2PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOne1PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOne2PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneMixedKeys1PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneMixedKeys2PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "My_PROPERTY_BAG_PRINCIPAL");

            migrationBuilder.DropTable(
                name: "EntitiesRequiredFalsePrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesRequiredTruePrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesTablePerTypeBaseFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroManyToMany1MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroManyToMany1NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroManyToMany2MFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroManyToMany2NFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToMany1PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToMany2PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyPrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToManyPrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOne1PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOne2PrincipalFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOnePrincipalConventions");

            migrationBuilder.DropTable(
                name: "EntitiesZeroToOnePrincipalDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesOwnedTypeInMultiTables");
        }
    }
}
