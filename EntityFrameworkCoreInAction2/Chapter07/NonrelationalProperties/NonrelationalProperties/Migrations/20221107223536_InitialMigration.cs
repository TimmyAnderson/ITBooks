using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace NonrelationalProperties.Migrations
{
    public partial class InitialMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.EnsureSchema(
                name: "My_Schema");

            migrationBuilder.CreateTable(
                name: "EntitiesAutoConfiguration1",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    DoubleValue = table.Column<double>(type: "REAL", precision: 9, scale: 2, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoConfiguration1", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesAutoConfiguration2",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", maxLength: 200, nullable: false),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    DoubleValue = table.Column<double>(type: "REAL", precision: 10, scale: 3, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesAutoConfiguration2", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesBackingFieldsAccessModes",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    My_BackingFieldField = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingFieldFieldDuringConstruction = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingFieldProperty = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingFieldPreferField = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingFieldPreferFieldDuringConstruction = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingFieldPreferProperty = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesBackingFieldsAccessModes", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesBackingFieldsConventions",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    NoBackingField = table.Column<string>(type: "TEXT", nullable: true),
                    BackingField1 = table.Column<string>(type: "TEXT", nullable: true),
                    BackingField2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesBackingFieldsConventions", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesBackingFieldsDataAnnotations",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    NoBackingField = table.Column<string>(type: "TEXT", nullable: true),
                    BackingField1 = table.Column<string>(type: "TEXT", nullable: true),
                    BackingField2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesBackingFieldsDataAnnotations", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesBackingFieldsFluentAPI",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    NoBackingField = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingField1 = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingField2 = table.Column<string>(type: "TEXT", nullable: true),
                    My_BackingField3 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesBackingFieldsFluentAPI", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesColumnPropertiesDataAnnotations",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringNonNull = table.Column<string>(type: "TEXT", nullable: false),
                    StringWithMaxLength = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    DateTimeWithSQLTypeDATE = table.Column<DateTime>(type: "date", nullable: false),
                    My_IntRenamed = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesColumnPropertiesDataAnnotations", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesColumnPropertiesFluentAPI",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringNonNull = table.Column<string>(type: "TEXT", nullable: false),
                    StringWithMaxLength = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    DateTimeWithSQLTypeDATE = table.Column<DateTime>(type: "date", nullable: false),
                    My_IntRenamed = table.Column<int>(type: "INTEGER", nullable: false),
                    StringNonUnicode = table.Column<string>(type: "TEXT", unicode: false, nullable: true),
                    DoubleWithLimitedPrecision = table.Column<double>(type: "REAL", precision: 9, scale: 2, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesColumnPropertiesFluentAPI", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDataForKeylessView",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    StringValue = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDataForKeylessView", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDifferentConfigurations",
                columns: table => new
                {
                    Id = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    IntNonNull = table.Column<int>(type: "INTEGER", nullable: false),
                    IntNull = table.Column<int>(type: "INTEGER", nullable: true),
                    StringWithMaxLength = table.Column<string>(type: "TEXT", maxLength: 50, nullable: true),
                    StringNonNullWithMaxLength = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    StringNonUnicodeWithMaxLength = table.Column<string>(type: "TEXT", unicode: false, maxLength: 50, nullable: true),
                    DateTimeWithSQLTypeDATEAndIndex = table.Column<DateTime>(type: "date", nullable: false),
                    DoubleWithLimitedPrecision = table.Column<double>(type: "REAL", precision: 9, scale: 2, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDifferentConfigurations", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesIndexesDataAnnotations",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    SingleColumnIndex = table.Column<string>(type: "TEXT", nullable: true),
                    MultiColumnIndex1 = table.Column<string>(type: "TEXT", nullable: true),
                    MultiColumnIndex2 = table.Column<string>(type: "TEXT", nullable: true),
                    SingleColumnUniqueIndex = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesIndexesDataAnnotations", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesIndexesFluentAPI",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    SingleColumnIndex = table.Column<string>(type: "TEXT", nullable: true),
                    MultiColumnIndex1 = table.Column<string>(type: "TEXT", nullable: true),
                    MultiColumnIndex2 = table.Column<string>(type: "TEXT", nullable: true),
                    SingleColumnUniqueIndex = table.Column<string>(type: "TEXT", nullable: true),
                    SingleColumnFilteredIndex = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesIndexesFluentAPI", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNotExcluded",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNotExcluded", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesPrimaryKeyConventions",
                columns: table => new
                {
                    Id = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPrimaryKeyConventions", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesPrimaryKeyDataAnnotations",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPrimaryKeyDataAnnotations", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesPrimaryKeyFluentAPI",
                columns: table => new
                {
                    ID1 = table.Column<int>(type: "INTEGER", nullable: false),
                    ID2 = table.Column<int>(type: "INTEGER", nullable: false),
                    Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPrimaryKeyFluentAPI", x => new { x.ID1, x.ID2 });
                });

            migrationBuilder.CreateTable(
                name: "EntitiesQueryFilter",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesQueryFilter", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesShadowProperties",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    NonShadowProperty = table.Column<string>(type: "TEXT", nullable: true),
                    My_ShadowPropertyInt = table.Column<int>(type: "INTEGER", nullable: false),
                    My_ShadowPropertyString = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesShadowProperties", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesUsingValueConversions",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true),
                    EnumTypeNoConversion = table.Column<int>(type: "INTEGER", nullable: false),
                    EnumTypeWithConversion1 = table.Column<string>(type: "TEXT", nullable: false),
                    EnumTypeWithConversion2 = table.Column<string>(type: "TEXT", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesUsingValueConversions", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "My_EntityCustomNamesDataAnnotations",
                schema: "My_Schema",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    My_Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_My_EntityCustomNamesDataAnnotations", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "My_EntityCustomNamesFluentAPI",
                schema: "My_Schema",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    My_Value = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_My_EntityCustomNamesFluentAPI", x => x.ID);
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
                name: "EntitiesNotMappedDataAnnotations",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true),
                    NotExcludedClassValueID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNotMappedDataAnnotations", x => x.ID);
                    table.ForeignKey(
                        name: "FK_EntitiesNotMappedDataAnnotations_EntitiesNotExcluded_NotExcludedClassValueID",
                        column: x => x.NotExcludedClassValueID,
                        principalTable: "EntitiesNotExcluded",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateTable(
                name: "EntitiesNotMappedFluentAPI",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value = table.Column<string>(type: "TEXT", nullable: true),
                    NotExcludedClassValueID = table.Column<int>(type: "INTEGER", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesNotMappedFluentAPI", x => x.ID);
                    table.ForeignKey(
                        name: "FK_EntitiesNotMappedFluentAPI_EntitiesNotExcluded_NotExcludedClassValueID",
                        column: x => x.NotExcludedClassValueID,
                        principalTable: "EntitiesNotExcluded",
                        principalColumn: "ID");
                });

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesDifferentConfigurations_DateTimeWithSQLTypeDATEAndIndex",
                table: "EntitiesDifferentConfigurations",
                column: "DateTimeWithSQLTypeDATEAndIndex");

            migrationBuilder.CreateIndex(
                name: "My_MultiColumnIndex_DataAnnotations",
                table: "EntitiesIndexesDataAnnotations",
                columns: new[] { "MultiColumnIndex1", "MultiColumnIndex2" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "My_SingleColumnIndex_DataAnnotations",
                table: "EntitiesIndexesDataAnnotations",
                column: "SingleColumnIndex");

            migrationBuilder.CreateIndex(
                name: "My_SingleColumnUniqueIndex_DataAnnotations",
                table: "EntitiesIndexesDataAnnotations",
                column: "SingleColumnUniqueIndex",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "My_MultiColumnIndex_FluentAPI",
                table: "EntitiesIndexesFluentAPI",
                columns: new[] { "MultiColumnIndex1", "MultiColumnIndex2" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "My_SingleColumnFilteredIndex_FluentAPI",
                table: "EntitiesIndexesFluentAPI",
                column: "SingleColumnFilteredIndex",
                filter: "SingleColumnFilteredIndex>1");

            migrationBuilder.CreateIndex(
                name: "My_SingleColumnIndex_FluentAPI",
                table: "EntitiesIndexesFluentAPI",
                column: "SingleColumnIndex");

            migrationBuilder.CreateIndex(
                name: "My_SingleColumnUniqueIndex_FluentAPI",
                table: "EntitiesIndexesFluentAPI",
                column: "SingleColumnUniqueIndex",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesNotMappedDataAnnotations_NotExcludedClassValueID",
                table: "EntitiesNotMappedDataAnnotations",
                column: "NotExcludedClassValueID");

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesNotMappedFluentAPI_NotExcludedClassValueID",
                table: "EntitiesNotMappedFluentAPI",
                column: "NotExcludedClassValueID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EntitiesAutoConfiguration1");

            migrationBuilder.DropTable(
                name: "EntitiesAutoConfiguration2");

            migrationBuilder.DropTable(
                name: "EntitiesBackingFieldsAccessModes");

            migrationBuilder.DropTable(
                name: "EntitiesBackingFieldsConventions");

            migrationBuilder.DropTable(
                name: "EntitiesBackingFieldsDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesBackingFieldsFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesColumnPropertiesDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesColumnPropertiesFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesDataForKeylessView");

            migrationBuilder.DropTable(
                name: "EntitiesDifferentConfigurations");

            migrationBuilder.DropTable(
                name: "EntitiesIndexesDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesIndexesFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesNotMappedDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesNotMappedFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesPrimaryKeyConventions");

            migrationBuilder.DropTable(
                name: "EntitiesPrimaryKeyDataAnnotations");

            migrationBuilder.DropTable(
                name: "EntitiesPrimaryKeyFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesQueryFilter");

            migrationBuilder.DropTable(
                name: "EntitiesShadowProperties");

            migrationBuilder.DropTable(
                name: "EntitiesUsingValueConversions");

            migrationBuilder.DropTable(
                name: "My_EntityCustomNamesDataAnnotations",
                schema: "My_Schema");

            migrationBuilder.DropTable(
                name: "My_EntityCustomNamesFluentAPI",
                schema: "My_Schema");

            migrationBuilder.DropTable(
                name: "TestEntities");

            migrationBuilder.DropTable(
                name: "EntitiesNotExcluded");
        }
    }
}
