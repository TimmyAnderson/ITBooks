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
                name: "EntitiesDataLoaderBatchPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalValue2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDataLoaderBatchPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDataLoaderGroupPrincipal",
                columns: table => new
                {
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityPrincipalValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalValue2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDataLoaderGroupPrincipal", x => x.EntityPrincipalID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesFilteringByConvention",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", nullable: true),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    LongValue = table.Column<long>(type: "INTEGER", nullable: false),
                    DoubleValue = table.Column<double>(type: "REAL", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesFilteringByConvention", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesFilteringByFluentAPIExplicit",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", nullable: true),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    LongValue = table.Column<long>(type: "INTEGER", nullable: false),
                    DoubleValue = table.Column<double>(type: "REAL", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesFilteringByFluentAPIExplicit", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesFilteringByFluentAPIImplicit",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", nullable: true),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false),
                    LongValue = table.Column<long>(type: "INTEGER", nullable: false),
                    DoubleValue = table.Column<double>(type: "REAL", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesFilteringByFluentAPIImplicit", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesFilteringManually",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    StringValue = table.Column<string>(type: "TEXT", nullable: true),
                    IntValue = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesFilteringManually", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesInterfacesMyInterface1",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    SharedValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    SharedValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    Class1Value1 = table.Column<string>(type: "TEXT", nullable: true),
                    Class1Value2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesInterfacesMyInterface1", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesInterfacesMyInterface2",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    SharedValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    SharedValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    Class2Value1 = table.Column<string>(type: "TEXT", nullable: true),
                    Class2Value2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesInterfacesMyInterface2", x => x.ID);
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
                name: "EntitiesPaginationCursorBased",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value1 = table.Column<int>(type: "INTEGER", nullable: false),
                    Value2 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPaginationCursorBased", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesPaginationOffsetBased",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Value1 = table.Column<int>(type: "INTEGER", nullable: false),
                    Value2 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesPaginationOffsetBased", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesSortingByConvention",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    ValueString = table.Column<string>(type: "TEXT", nullable: true),
                    ValueInt = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesSortingByConvention", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesSortingByFluentAPI",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    ValueString = table.Column<string>(type: "TEXT", nullable: true),
                    ValueInt = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesSortingByFluentAPI", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesSortingManually",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    ValueString = table.Column<string>(type: "TEXT", nullable: true),
                    ValueInt = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesSortingManually", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesUnionsMyClass1",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    SharedValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    SharedValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    Class1Value1 = table.Column<string>(type: "TEXT", nullable: true),
                    Class1Value2 = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesUnionsMyClass1", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesUnionsMyClass2",
                columns: table => new
                {
                    ID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    SharedValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    SharedValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    Class2Value1 = table.Column<int>(type: "INTEGER", nullable: false),
                    Class2Value2 = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesUnionsMyClass2", x => x.ID);
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
                name: "EntitiesDataLoaderBatchDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    EntityDependentValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDataLoaderBatchDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesDataLoaderBatchDependent_EntitiesDataLoaderBatchPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesDataLoaderBatchPrincipal",
                        principalColumn: "EntityPrincipalID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "EntitiesDataLoaderGroupDependent",
                columns: table => new
                {
                    EntityDependentID = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    EntityDependentValue1 = table.Column<string>(type: "TEXT", nullable: true),
                    EntityDependentValue2 = table.Column<string>(type: "TEXT", nullable: true),
                    EntityPrincipalID = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EntitiesDataLoaderGroupDependent", x => x.EntityDependentID);
                    table.ForeignKey(
                        name: "FK_EntitiesDataLoaderGroupDependent_EntitiesDataLoaderGroupPrincipal_EntityPrincipalID",
                        column: x => x.EntityPrincipalID,
                        principalTable: "EntitiesDataLoaderGroupPrincipal",
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
                table: "EntitiesDataLoaderBatchPrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue1", "EntityPrincipalValue2" },
                values: new object[,]
                {
                    { 1, "PRINCIPAL A 111", "PRINCIPAL B 111" },
                    { 2, "PRINCIPAL A 222", "PRINCIPAL B 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesDataLoaderGroupPrincipal",
                columns: new[] { "EntityPrincipalID", "EntityPrincipalValue1", "EntityPrincipalValue2" },
                values: new object[,]
                {
                    { 1, "PRINCIPAL A 111", "PRINCIPAL B 111" },
                    { 2, "PRINCIPAL A 222", "PRINCIPAL B 222" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesFilteringByConvention",
                columns: new[] { "ID", "DoubleValue", "IntValue", "LongValue", "StringValue" },
                values: new object[,]
                {
                    { 1, 111.111, 101, 1001L, "AAA 1" },
                    { 2, 222.22200000000001, 102, 1002L, "AAA 2" },
                    { 3, 333.33300000000003, 103, 1003L, "BBB 1" },
                    { 4, 444.44400000000002, 104, 1004L, "BBB 2" },
                    { 5, 555.55499999999995, 105, 1005L, "CCC 1" },
                    { 6, 666.66600000000005, 106, 1006L, "CCC 2" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesFilteringByFluentAPIExplicit",
                columns: new[] { "ID", "DoubleValue", "IntValue", "LongValue", "StringValue" },
                values: new object[,]
                {
                    { 1, 111.111, 101, 1001L, "AAA 1" },
                    { 2, 222.22200000000001, 102, 1002L, "AAA 2" },
                    { 3, 333.33300000000003, 103, 1003L, "BBB 1" },
                    { 4, 444.44400000000002, 104, 1004L, "BBB 2" },
                    { 5, 555.55499999999995, 105, 1005L, "CCC 1" },
                    { 6, 666.66600000000005, 106, 1006L, "CCC 2" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesFilteringByFluentAPIImplicit",
                columns: new[] { "ID", "DoubleValue", "IntValue", "LongValue", "StringValue" },
                values: new object[,]
                {
                    { 1, 111.111, 101, 1001L, "AAA 1" },
                    { 2, 222.22200000000001, 102, 1002L, "AAA 2" },
                    { 3, 333.33300000000003, 103, 1003L, "BBB 1" },
                    { 4, 444.44400000000002, 104, 1004L, "BBB 2" },
                    { 5, 555.55499999999995, 105, 1005L, "CCC 1" },
                    { 6, 666.66600000000005, 106, 1006L, "CCC 2" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesFilteringManually",
                columns: new[] { "ID", "IntValue", "StringValue" },
                values: new object[,]
                {
                    { 1, 101, "AAA 1" },
                    { 2, 102, "AAA 2" },
                    { 3, 103, "BBB 1" },
                    { 4, 104, "BBB 2" },
                    { 5, 105, "CCC 1" },
                    { 6, 106, "CCC 2" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesInterfacesMyInterface1",
                columns: new[] { "ID", "Class1Value1", "Class1Value2", "SharedValue1", "SharedValue2" },
                values: new object[,]
                {
                    { 1, "CLASS 1 VALUE 1 AAA", "CLASS 1 VALUE 2 AAA", "CLASS 1 SHARED 1 AAA", "CLASS 1 SHARED 2 AAA" },
                    { 2, "CLASS 1 VALUE 1 BBB", "CLASS 1 VALUE 2 BBB", "CLASS 1 SHARED 1 BBB", "CLASS 1 SHARED 2 BBB" },
                    { 3, "CLASS 1 VALUE 1 CCC", "CLASS 1 VALUE 2 CCC", "CLASS 1 SHARED 1 CCC", "CLASS 1 SHARED 2 CCC" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesInterfacesMyInterface2",
                columns: new[] { "ID", "Class2Value1", "Class2Value2", "SharedValue1", "SharedValue2" },
                values: new object[,]
                {
                    { 1, "CLASS 2 VALUE 1 AAA", "CLASS 2 VALUE 2 AAA", "CLASS 2 SHARED 1 AAA", "CLASS 2 SHARED 2 AAA" },
                    { 2, "CLASS 2 VALUE 1 BBB", "CLASS 2 VALUE 2 BBB", "CLASS 2 SHARED 1 BBB", "CLASS 2 SHARED 2 BBB" },
                    { 3, "CLASS 2 VALUE 1 CCC", "CLASS 2 VALUE 2 CCC", "CLASS 2 SHARED 1 CCC", "CLASS 2 SHARED 2 CCC" }
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
                table: "EntitiesPaginationCursorBased",
                columns: new[] { "ID", "Value1", "Value2" },
                values: new object[,]
                {
                    { 1, 101, 1001 },
                    { 2, 102, 1002 },
                    { 3, 103, 1003 },
                    { 4, 104, 1004 },
                    { 5, 105, 1005 },
                    { 6, 106, 1006 },
                    { 7, 107, 1007 },
                    { 8, 108, 1008 },
                    { 9, 109, 1009 },
                    { 10, 110, 1010 },
                    { 11, 111, 1011 },
                    { 12, 112, 1012 },
                    { 13, 113, 1013 },
                    { 14, 114, 1014 },
                    { 15, 115, 1015 },
                    { 16, 116, 1016 },
                    { 17, 117, 1017 },
                    { 18, 118, 1018 },
                    { 19, 119, 1019 },
                    { 20, 120, 1020 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesPaginationOffsetBased",
                columns: new[] { "ID", "Value1", "Value2" },
                values: new object[,]
                {
                    { 1, 101, 1001 },
                    { 2, 102, 1002 },
                    { 3, 103, 1003 },
                    { 4, 104, 1004 },
                    { 5, 105, 1005 },
                    { 6, 106, 1006 },
                    { 7, 107, 1007 },
                    { 8, 108, 1008 },
                    { 9, 109, 1009 },
                    { 10, 110, 1010 },
                    { 11, 111, 1011 },
                    { 12, 112, 1012 },
                    { 13, 113, 1013 },
                    { 14, 114, 1014 },
                    { 15, 115, 1015 },
                    { 16, 116, 1016 },
                    { 17, 117, 1017 },
                    { 18, 118, 1018 },
                    { 19, 119, 1019 },
                    { 20, 120, 1020 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesSortingByConvention",
                columns: new[] { "ID", "ValueInt", "ValueString" },
                values: new object[,]
                {
                    { 1, 8, "VALUE 111" },
                    { 2, 7, "VALUE 222" },
                    { 3, 6, "VALUE 333" },
                    { 4, 5, "VALUE 444" },
                    { 5, 4, "VALUE 111" },
                    { 6, 3, "VALUE 222" },
                    { 7, 2, "VALUE 333" },
                    { 8, 1, "VALUE 444" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesSortingByFluentAPI",
                columns: new[] { "ID", "ValueInt", "ValueString" },
                values: new object[,]
                {
                    { 1, 8, "VALUE 111" },
                    { 2, 7, "VALUE 222" },
                    { 3, 6, "VALUE 333" },
                    { 4, 5, "VALUE 444" },
                    { 5, 4, "VALUE 111" },
                    { 6, 3, "VALUE 222" },
                    { 7, 2, "VALUE 333" },
                    { 8, 1, "VALUE 444" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesSortingManually",
                columns: new[] { "ID", "ValueInt", "ValueString" },
                values: new object[,]
                {
                    { 1, 8, "VALUE 111" },
                    { 2, 7, "VALUE 222" },
                    { 3, 6, "VALUE 333" },
                    { 4, 5, "VALUE 444" },
                    { 5, 4, "VALUE 111" },
                    { 6, 3, "VALUE 222" },
                    { 7, 2, "VALUE 333" },
                    { 8, 1, "VALUE 444" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesUnionsMyClass1",
                columns: new[] { "ID", "Class1Value1", "Class1Value2", "SharedValue1", "SharedValue2" },
                values: new object[,]
                {
                    { 1, "CLASS 1 VALUE 1 AAA", "CLASS 1 VALUE 2 AAA", "CLASS 1 SHARED 1 AAA", "CLASS 1 SHARED 2 AAA" },
                    { 2, "CLASS 1 VALUE 1 BBB", "CLASS 1 VALUE 2 BBB", "CLASS 1 SHARED 1 BBB", "CLASS 1 SHARED 2 BBB" },
                    { 3, "CLASS 1 VALUE 1 CCC", "CLASS 1 VALUE 2 CCC", "CLASS 1 SHARED 1 CCC", "CLASS 1 SHARED 2 CCC" }
                });

            migrationBuilder.InsertData(
                table: "EntitiesUnionsMyClass2",
                columns: new[] { "ID", "Class2Value1", "Class2Value2", "SharedValue1", "SharedValue2" },
                values: new object[,]
                {
                    { 1, 110, 120, "CLASS 1 SHARED 1 AAA", "CLASS 1 SHARED 2 AAA" },
                    { 2, 210, 220, "CLASS 1 SHARED 1 BBB", "CLASS 1 SHARED 2 BBB" },
                    { 3, 310, 320, "CLASS 1 SHARED 1 CCC", "CLASS 1 SHARED 2 CCC" }
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
                table: "EntitiesDataLoaderBatchDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue1", "EntityDependentValue2", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "DEPENDENT A 111", "DEPENDENT B 111", 1 },
                    { 2, "DEPENDENT A 222", "DEPENDENT B 222", 2 }
                });

            migrationBuilder.InsertData(
                table: "EntitiesDataLoaderGroupDependent",
                columns: new[] { "EntityDependentID", "EntityDependentValue1", "EntityDependentValue2", "EntityPrincipalID" },
                values: new object[,]
                {
                    { 1, "DEPENDENT A 111", "DEPENDENT B 111", 1 },
                    { 2, "DEPENDENT A 222", "DEPENDENT B 222", 1 },
                    { 3, "DEPENDENT A 333", "DEPENDENT B 333", 2 },
                    { 4, "DEPENDENT A 444", "DEPENDENT B 444", 2 }
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
                name: "IX_EntitiesDataLoaderBatchDependent_EntityPrincipalID",
                table: "EntitiesDataLoaderBatchDependent",
                column: "EntityPrincipalID",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_EntitiesDataLoaderGroupDependent_EntityPrincipalID",
                table: "EntitiesDataLoaderGroupDependent",
                column: "EntityPrincipalID");

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
                name: "EntitiesDataLoaderBatchDependent");

            migrationBuilder.DropTable(
                name: "EntitiesDataLoaderGroupDependent");

            migrationBuilder.DropTable(
                name: "EntitiesFilteringByConvention");

            migrationBuilder.DropTable(
                name: "EntitiesFilteringByFluentAPIExplicit");

            migrationBuilder.DropTable(
                name: "EntitiesFilteringByFluentAPIImplicit");

            migrationBuilder.DropTable(
                name: "EntitiesFilteringManually");

            migrationBuilder.DropTable(
                name: "EntitiesInterfacesMyInterface1");

            migrationBuilder.DropTable(
                name: "EntitiesInterfacesMyInterface2");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyDependent");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent1");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOneDependent2");

            migrationBuilder.DropTable(
                name: "EntitiesPaginationCursorBased");

            migrationBuilder.DropTable(
                name: "EntitiesPaginationOffsetBased");

            migrationBuilder.DropTable(
                name: "EntitiesSortingByConvention");

            migrationBuilder.DropTable(
                name: "EntitiesSortingByFluentAPI");

            migrationBuilder.DropTable(
                name: "EntitiesSortingManually");

            migrationBuilder.DropTable(
                name: "EntitiesUnionsMyClass1");

            migrationBuilder.DropTable(
                name: "EntitiesUnionsMyClass2");

            migrationBuilder.DropTable(
                name: "NamesEntities");

            migrationBuilder.DropTable(
                name: "EntitiesDataLoaderBatchPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesDataLoaderGroupPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToManyPrincipal");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal1");

            migrationBuilder.DropTable(
                name: "EntitiesOneToOnePrincipal2");
        }
    }
}
