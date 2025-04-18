using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
    public sealed class CDBContext : DbContext
    {
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityName>								MEntitiesNames;
		private DbSet<CEntityOneToOnePrincipal1>				MEntitiesOneToOnePrincipal1;
		private DbSet<CEntityOneToOneDependent1>				MEntitiesOneToOneDependent1;
		private DbSet<CEntityOneToOnePrincipal2>				MEntitiesOneToOnePrincipal2;
		private DbSet<CEntityOneToOneDependent2>				MEntitiesOneToOneDependent2;
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityDataLoaderBatchPrincipal>			MEntitiesDataLoaderBatchPrincipal;
		private DbSet<CEntityDataLoaderBatchDependent>			MEntitiesDataLoaderBatchDependent;
		private DbSet<CEntityDataLoaderGroupPrincipal>			MEntitiesDataLoaderGroupPrincipal;
		private DbSet<CEntityDataLoaderGroupDependent>			MEntitiesDataLoaderGroupDependent;
		private DbSet<CEntityInterfacesMyInterface1>			MEntitiesInterfacesMyInterface1;
		private DbSet<CEntityInterfacesMyInterface2>			MEntitiesInterfacesMyInterface2;
		private DbSet<CEntityUnionsMyClass1>					MEntitiesUnionsMyClass1;
		private DbSet<CEntityUnionsMyClass2>					MEntitiesUnionsMyClass2;
		private DbSet<CEntityFilteringByConvention>				MEntitiesFilteringByConvention;
		private DbSet<CEntityFilteringByFluentAPIImplicit>		MEntitiesFilteringByFluentAPIImplicit;
		private DbSet<CEntityFilteringByFluentAPIExplicit>		MEntitiesFilteringByFluentAPIExplicit;
		private DbSet<CEntityFilteringManually>					MEntitiesFilteringManually;
		private DbSet<CEntitySortingByConvention>				MEntitiesSortingByConvention;
		private DbSet<CEntitySortingByFluentAPI>				MEntitiesSortingByFluentAPI;
		private DbSet<CEntitySortingManually>					MEntitiesSortingManually;
		private DbSet<CEntityPaginationCursorBased>				MEntitiesPaginationCursorBased;
		private DbSet<CEntityPaginationOffsetBased>				MEntitiesPaginationOffsetBased;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(DbContextOptions<CDBContext> Options)
			: base(Options)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityName>								EntitiesNames
		{
			get
			{
				return(MEntitiesNames);
			}
			set
			{
				MEntitiesNames=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOnePrincipal1>					EntitiesOneToOnePrincipal1
		{
			get
			{
				return(MEntitiesOneToOnePrincipal1);
			}
			set
			{
				MEntitiesOneToOnePrincipal1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependent1>					EntitiesOneToOneDependent1
		{
			get
			{
				return(MEntitiesOneToOneDependent1);
			}
			set
			{
				MEntitiesOneToOneDependent1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOnePrincipal2>					EntitiesOneToOnePrincipal2
		{
			get
			{
				return(MEntitiesOneToOnePrincipal2);
			}
			set
			{
				MEntitiesOneToOnePrincipal2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependent2>					EntitiesOneToOneDependent2
		{
			get
			{
				return(MEntitiesOneToOneDependent2);
			}
			set
			{
				MEntitiesOneToOneDependent2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyPrincipal>					EntitiesOneToManyPrincipal
		{
			get
			{
				return(MEntitiesOneToManyPrincipal);
			}
			set
			{
				MEntitiesOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyDependent>					EntitiesOneToManyDependent
		{
			get
			{
				return(MEntitiesOneToManyDependent);
			}
			set
			{
				MEntitiesOneToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataLoaderBatchPrincipal>			EntitiesDataLoaderBatchPrincipal
		{
			get
			{
				return(MEntitiesDataLoaderBatchPrincipal);
			}
			set
			{
				MEntitiesDataLoaderBatchPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataLoaderBatchDependent>			EntitiesDataLoaderBatchDependent
		{
			get
			{
				return(MEntitiesDataLoaderBatchDependent);
			}
			set
			{
				MEntitiesDataLoaderBatchDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataLoaderGroupPrincipal>			EntitiesDataLoaderGroupPrincipal
		{
			get
			{
				return(MEntitiesDataLoaderGroupPrincipal);
			}
			set
			{
				MEntitiesDataLoaderGroupPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataLoaderGroupDependent>			EntitiesDataLoaderGroupDependent
		{
			get
			{
				return(MEntitiesDataLoaderGroupDependent);
			}
			set
			{
				MEntitiesDataLoaderGroupDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityInterfacesMyInterface1>				EntitiesInterfacesMyInterface1
		{
			get
			{
				return(MEntitiesInterfacesMyInterface1);
			}
			set
			{
				MEntitiesInterfacesMyInterface1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityInterfacesMyInterface2>				EntitiesInterfacesMyInterface2
		{
			get
			{
				return(MEntitiesInterfacesMyInterface2);
			}
			set
			{
				MEntitiesInterfacesMyInterface2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityUnionsMyClass1>						EntitiesUnionsMyClass1
		{
			get
			{
				return(MEntitiesUnionsMyClass1);
			}
			set
			{
				MEntitiesUnionsMyClass1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityUnionsMyClass2>						EntitiesUnionsMyClass2
		{
			get
			{
				return(MEntitiesUnionsMyClass2);
			}
			set
			{
				MEntitiesUnionsMyClass2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityFilteringByConvention>				EntitiesFilteringByConvention
		{
			get
			{
				return(MEntitiesFilteringByConvention);
			}
			set
			{
				MEntitiesFilteringByConvention=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityFilteringByFluentAPIImplicit>		EntitiesFilteringByFluentAPIImplicit
		{
			get
			{
				return(MEntitiesFilteringByFluentAPIImplicit);
			}
			set
			{
				MEntitiesFilteringByFluentAPIImplicit=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityFilteringByFluentAPIExplicit>		EntitiesFilteringByFluentAPIExplicit
		{
			get
			{
				return(MEntitiesFilteringByFluentAPIExplicit);
			}
			set
			{
				MEntitiesFilteringByFluentAPIExplicit=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityFilteringManually>					EntitiesFilteringManually
		{
			get
			{
				return(MEntitiesFilteringManually);
			}
			set
			{
				MEntitiesFilteringManually=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntitySortingByConvention>				EntitiesSortingByConvention
		{
			get
			{
				return(MEntitiesSortingByConvention);
			}
			set
			{
				MEntitiesSortingByConvention=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntitySortingByFluentAPI>					EntitiesSortingByFluentAPI
		{
			get
			{
				return(MEntitiesSortingByFluentAPI);
			}
			set
			{
				MEntitiesSortingByFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntitySortingManually>					EntitiesSortingManually
		{
			get
			{
				return(MEntitiesSortingManually);
			}
			set
			{
				MEntitiesSortingManually=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPaginationCursorBased>				EntitiesPaginationCursorBased
		{
			get
			{
				return(MEntitiesPaginationCursorBased);
			}
			set
			{
				MEntitiesPaginationCursorBased=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityPaginationOffsetBased>				EntitiesPaginationOffsetBased
		{
			get
			{
				return(MEntitiesPaginationOffsetBased);
			}
			set
			{
				MEntitiesPaginationOffsetBased=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNames(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityName>().ToTable("NamesEntities");

			ModelBuilder.Entity<CEntityName>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOnePrincipal1(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOnePrincipal1>		Entity=ModelBuilder.Entity<CEntityOneToOnePrincipal1>();

			Entity.ToTable("EntitiesOneToOnePrincipal1");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOnePrincipal1,CEntityOneToOneDependent1>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOnePrincipal1,CEntityOneToOneDependent1>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityOneToOneDependent1>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneDependent1(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneDependent1>		Entity=ModelBuilder.Entity<CEntityOneToOneDependent1>();

			Entity.ToTable("EntitiesOneToOneDependent1");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOnePrincipal2(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOnePrincipal2>		Entity=ModelBuilder.Entity<CEntityOneToOnePrincipal2>();

			Entity.ToTable("EntitiesOneToOnePrincipal2");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOnePrincipal2,CEntityOneToOneDependent2>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOnePrincipal2,CEntityOneToOneDependent2>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityOneToOneDependent2>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneDependent2(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneDependent2>		Entity=ModelBuilder.Entity<CEntityOneToOneDependent2>();

			Entity.ToTable("EntitiesOneToOneDependent2");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityOneToManyPrincipal>();

			Entity.ToTable("EntitiesOneToManyPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToManyDependent>		Entity=ModelBuilder.Entity<CEntityOneToManyDependent>();

			Entity.ToTable("EntitiesOneToManyDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDataLoaderBatchPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDataLoaderBatchPrincipal>	Entity=ModelBuilder.Entity<CEntityDataLoaderBatchPrincipal>();

			Entity.ToTable("EntitiesDataLoaderBatchPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityDataLoaderBatchPrincipal,CEntityDataLoaderBatchDependent>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityDataLoaderBatchPrincipal,CEntityDataLoaderBatchDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityDataLoaderBatchDependent>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDataLoaderBatchDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDataLoaderBatchDependent>	Entity=ModelBuilder.Entity<CEntityDataLoaderBatchDependent>();

			Entity.ToTable("EntitiesDataLoaderBatchDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDataLoaderGroupPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDataLoaderGroupPrincipal>	Entity=ModelBuilder.Entity<CEntityDataLoaderGroupPrincipal>();

			Entity.ToTable("EntitiesDataLoaderGroupPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityDataLoaderGroupPrincipal,CEntityDataLoaderGroupDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityDataLoaderGroupPrincipal,CEntityDataLoaderGroupDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityDataLoaderGroupDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityDataLoaderGroupDependent>	Entity=ModelBuilder.Entity<CEntityDataLoaderGroupDependent>();

			Entity.ToTable("EntitiesDataLoaderGroupDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureInterfacesMyInterface1(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityInterfacesMyInterface1>	Entity=ModelBuilder.Entity<CEntityInterfacesMyInterface1>();

			Entity.ToTable("EntitiesInterfacesMyInterface1");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureInterfacesMyInterface2(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityInterfacesMyInterface2>	Entity=ModelBuilder.Entity<CEntityInterfacesMyInterface2>();

			Entity.ToTable("EntitiesInterfacesMyInterface2");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureUnionsMyClass1(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityUnionsMyClass1>			Entity=ModelBuilder.Entity<CEntityUnionsMyClass1>();

			Entity.ToTable("EntitiesUnionsMyClass1");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureUnionsMyClass2(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityUnionsMyClass2>			Entity=ModelBuilder.Entity<CEntityUnionsMyClass2>();

			Entity.ToTable("EntitiesUnionsMyClass2");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureFilteringByConvention(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityFilteringByConvention>		Entity=ModelBuilder.Entity<CEntityFilteringByConvention>();

			Entity.ToTable("EntitiesFilteringByConvention");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureFilteringByFluentAPIImplicit(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityFilteringByFluentAPIImplicit>	Entity=ModelBuilder.Entity<CEntityFilteringByFluentAPIImplicit>();

			Entity.ToTable("EntitiesFilteringByFluentAPIImplicit");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureFilteringByFluentAPIExplicit(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityFilteringByFluentAPIExplicit>	Entity=ModelBuilder.Entity<CEntityFilteringByFluentAPIExplicit>();

			Entity.ToTable("EntitiesFilteringByFluentAPIExplicit");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureFilteringManually(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityFilteringManually>			Entity=ModelBuilder.Entity<CEntityFilteringManually>();

			Entity.ToTable("EntitiesFilteringManually");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureSortingByConvention(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntitySortingByConvention>		Entity=ModelBuilder.Entity<CEntitySortingByConvention>();

			Entity.ToTable("EntitiesSortingByConvention");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureSortingByFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntitySortingByFluentAPI>		Entity=ModelBuilder.Entity<CEntitySortingByFluentAPI>();

			Entity.ToTable("EntitiesSortingByFluentAPI");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureSortingManually(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntitySortingManually>			Entity=ModelBuilder.Entity<CEntitySortingManually>();

			Entity.ToTable("EntitiesSortingManually");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigurePaginationCursorBased(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityPaginationCursorBased>		Entity=ModelBuilder.Entity<CEntityPaginationCursorBased>();

			Entity.ToTable("EntitiesPaginationCursorBased");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigurePaginationOffsetBased(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityPaginationOffsetBased>		Entity=ModelBuilder.Entity<CEntityPaginationOffsetBased>();

			Entity.ToTable("EntitiesPaginationOffsetBased");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillEntityNames(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityName>						Entity=ModelBuilder.Entity<CEntityName>();

			List<CEntityName>									Names=new List<CEntityName>();

			Names.Add(new CEntityName(1,"Timmy","Anderson",12,ESex.E_MALE));
			Names.Add(new CEntityName(2,"Jenny","Thompson",13,ESex.E_FEMALE));

			Entity.HasData(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOneToOne1(ModelBuilder ModelBuilder)
		{
			CEntityOneToOnePrincipal1							EntityOneToOnePrincipal1=new CEntityOneToOnePrincipal1(1,"PRINCIPAL 111");
			CEntityOneToOnePrincipal1							EntityOneToOnePrincipal2=new CEntityOneToOnePrincipal1(2,"PRINCIPAL 222");

			EntityTypeBuilder<CEntityOneToOnePrincipal1>		EntityPrincipal=ModelBuilder.Entity<CEntityOneToOnePrincipal1>();

			EntityPrincipal.HasData(EntityOneToOnePrincipal1);
			EntityPrincipal.HasData(EntityOneToOnePrincipal2);

			CEntityOneToOneDependent1							EntityOneToOneDependent11=new CEntityOneToOneDependent1(1,"DEPENDENT 111",EntityOneToOnePrincipal1.EntityPrincipalID);
			CEntityOneToOneDependent1							EntityOneToOneDependent12=new CEntityOneToOneDependent1(2,"DEPENDENT 222",EntityOneToOnePrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToOneDependent1>		EntityDependent=ModelBuilder.Entity<CEntityOneToOneDependent1>();

			EntityDependent.HasData(EntityOneToOneDependent11);
			EntityDependent.HasData(EntityOneToOneDependent12);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOneToOne2(ModelBuilder ModelBuilder)
		{
			CEntityOneToOnePrincipal2							EntityOneToOnePrincipal1=new CEntityOneToOnePrincipal2(1,"PRINCIPAL 111");
			CEntityOneToOnePrincipal2							EntityOneToOnePrincipal2=new CEntityOneToOnePrincipal2(2,"PRINCIPAL 222");

			EntityTypeBuilder<CEntityOneToOnePrincipal2>		EntityPrincipal=ModelBuilder.Entity<CEntityOneToOnePrincipal2>();

			EntityPrincipal.HasData(EntityOneToOnePrincipal1);
			EntityPrincipal.HasData(EntityOneToOnePrincipal2);

			CEntityOneToOneDependent2							EntityOneToOneDependent11=new CEntityOneToOneDependent2(1,"DEPENDENT 111",EntityOneToOnePrincipal1.EntityPrincipalID);
			CEntityOneToOneDependent2							EntityOneToOneDependent12=new CEntityOneToOneDependent2(2,"DEPENDENT 222",EntityOneToOnePrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToOneDependent2>		EntityDependent=ModelBuilder.Entity<CEntityOneToOneDependent2>();

			EntityDependent.HasData(EntityOneToOneDependent11);
			EntityDependent.HasData(EntityOneToOneDependent12);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOneToMany(ModelBuilder ModelBuilder)
		{
			CEntityOneToManyPrincipal							EntityOneToManyPrincipal1=new CEntityOneToManyPrincipal(1,"PRINCIPAL 111");
			CEntityOneToManyPrincipal							EntityOneToManyPrincipal2=new CEntityOneToManyPrincipal(2,"PRINCIPAL 222");

			EntityTypeBuilder<CEntityOneToManyPrincipal>		EntityPrincipal=ModelBuilder.Entity<CEntityOneToManyPrincipal>();

			EntityPrincipal.HasData(EntityOneToManyPrincipal1);
			EntityPrincipal.HasData(EntityOneToManyPrincipal2);

			CEntityOneToManyDependent							EntityOneToManyDependent11=new CEntityOneToManyDependent(1,"DEPENDENT 111",EntityOneToManyPrincipal1.EntityPrincipalID);
			CEntityOneToManyDependent							EntityOneToManyDependent12=new CEntityOneToManyDependent(2,"DEPENDENT 222",EntityOneToManyPrincipal1.EntityPrincipalID);
			CEntityOneToManyDependent							EntityOneToManyDependent21=new CEntityOneToManyDependent(3,"DEPENDENT 333",EntityOneToManyPrincipal2.EntityPrincipalID);
			CEntityOneToManyDependent							EntityOneToManyDependent22=new CEntityOneToManyDependent(4,"DEPENDENT 444",EntityOneToManyPrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToManyDependent>		EntityDependent=ModelBuilder.Entity<CEntityOneToManyDependent>();

			EntityDependent.HasData(EntityOneToManyDependent11);
			EntityDependent.HasData(EntityOneToManyDependent12);
			EntityDependent.HasData(EntityOneToManyDependent21);
			EntityDependent.HasData(EntityOneToManyDependent22);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataDataLoaderBatch(ModelBuilder ModelBuilder)
		{
			CEntityDataLoaderBatchPrincipal						EntityDataLoaderBatchPrincipal1=new CEntityDataLoaderBatchPrincipal(1,"PRINCIPAL A 111","PRINCIPAL B 111");
			CEntityDataLoaderBatchPrincipal						EntityDataLoaderBatchPrincipal2=new CEntityDataLoaderBatchPrincipal(2,"PRINCIPAL A 222","PRINCIPAL B 222");

			EntityTypeBuilder<CEntityDataLoaderBatchPrincipal>	EntityPrincipal=ModelBuilder.Entity<CEntityDataLoaderBatchPrincipal>();

			EntityPrincipal.HasData(EntityDataLoaderBatchPrincipal1);
			EntityPrincipal.HasData(EntityDataLoaderBatchPrincipal2);

			CEntityDataLoaderBatchDependent						EntityDataLoaderBatchDependent1=new CEntityDataLoaderBatchDependent(1,"DEPENDENT A 111","DEPENDENT B 111",EntityDataLoaderBatchPrincipal1.EntityPrincipalID);
			CEntityDataLoaderBatchDependent						EntityDataLoaderBatchDependent2=new CEntityDataLoaderBatchDependent(2,"DEPENDENT A 222","DEPENDENT B 222",EntityDataLoaderBatchPrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityDataLoaderBatchDependent>	EntityDependent=ModelBuilder.Entity<CEntityDataLoaderBatchDependent>();

			EntityDependent.HasData(EntityDataLoaderBatchDependent1);
			EntityDependent.HasData(EntityDataLoaderBatchDependent2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataDataLoaderGroup(ModelBuilder ModelBuilder)
		{
			CEntityDataLoaderGroupPrincipal						EntityDataLoaderGroupPrincipal1=new CEntityDataLoaderGroupPrincipal(1,"PRINCIPAL A 111","PRINCIPAL B 111");
			CEntityDataLoaderGroupPrincipal						EntityDataLoaderGroupPrincipal2=new CEntityDataLoaderGroupPrincipal(2,"PRINCIPAL A 222","PRINCIPAL B 222");

			EntityTypeBuilder<CEntityDataLoaderGroupPrincipal>	EntityPrincipal=ModelBuilder.Entity<CEntityDataLoaderGroupPrincipal>();

			EntityPrincipal.HasData(EntityDataLoaderGroupPrincipal1);
			EntityPrincipal.HasData(EntityDataLoaderGroupPrincipal2);

			CEntityDataLoaderGroupDependent						EntityDataLoaderGroupDependent11=new CEntityDataLoaderGroupDependent(1,"DEPENDENT A 111","DEPENDENT B 111",EntityDataLoaderGroupPrincipal1.EntityPrincipalID);
			CEntityDataLoaderGroupDependent						EntityDataLoaderGroupDependent12=new CEntityDataLoaderGroupDependent(2,"DEPENDENT A 222","DEPENDENT B 222",EntityDataLoaderGroupPrincipal1.EntityPrincipalID);
			CEntityDataLoaderGroupDependent						EntityDataLoaderGroupDependent21=new CEntityDataLoaderGroupDependent(3,"DEPENDENT A 333","DEPENDENT B 333",EntityDataLoaderGroupPrincipal2.EntityPrincipalID);
			CEntityDataLoaderGroupDependent						EntityDataLoaderGroupDependent22=new CEntityDataLoaderGroupDependent(4,"DEPENDENT A 444","DEPENDENT B 444",EntityDataLoaderGroupPrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityDataLoaderGroupDependent>	EntityDependent=ModelBuilder.Entity<CEntityDataLoaderGroupDependent>();

			EntityDependent.HasData(EntityDataLoaderGroupDependent11);
			EntityDependent.HasData(EntityDataLoaderGroupDependent12);
			EntityDependent.HasData(EntityDataLoaderGroupDependent21);
			EntityDependent.HasData(EntityDataLoaderGroupDependent22);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataInterfacesMyInterface1(ModelBuilder ModelBuilder)
		{
			CEntityInterfacesMyInterface1						Entity1=new CEntityInterfacesMyInterface1(1,"CLASS 1 SHARED 1 AAA","CLASS 1 SHARED 2 AAA","CLASS 1 VALUE 1 AAA","CLASS 1 VALUE 2 AAA");
			CEntityInterfacesMyInterface1						Entity2=new CEntityInterfacesMyInterface1(2,"CLASS 1 SHARED 1 BBB","CLASS 1 SHARED 2 BBB","CLASS 1 VALUE 1 BBB","CLASS 1 VALUE 2 BBB");
			CEntityInterfacesMyInterface1						Entity3=new CEntityInterfacesMyInterface1(3,"CLASS 1 SHARED 1 CCC","CLASS 1 SHARED 2 CCC","CLASS 1 VALUE 1 CCC","CLASS 1 VALUE 2 CCC");

			EntityTypeBuilder<CEntityInterfacesMyInterface1>	Entities=ModelBuilder.Entity<CEntityInterfacesMyInterface1>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataInterfacesMyInterface2(ModelBuilder ModelBuilder)
		{
			CEntityInterfacesMyInterface2						Entity1=new CEntityInterfacesMyInterface2(1,"CLASS 2 SHARED 1 AAA","CLASS 2 SHARED 2 AAA","CLASS 2 VALUE 1 AAA","CLASS 2 VALUE 2 AAA");
			CEntityInterfacesMyInterface2						Entity2=new CEntityInterfacesMyInterface2(2,"CLASS 2 SHARED 1 BBB","CLASS 2 SHARED 2 BBB","CLASS 2 VALUE 1 BBB","CLASS 2 VALUE 2 BBB");
			CEntityInterfacesMyInterface2						Entity3=new CEntityInterfacesMyInterface2(3,"CLASS 2 SHARED 1 CCC","CLASS 2 SHARED 2 CCC","CLASS 2 VALUE 1 CCC","CLASS 2 VALUE 2 CCC");

			EntityTypeBuilder<CEntityInterfacesMyInterface2>	Entities=ModelBuilder.Entity<CEntityInterfacesMyInterface2>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataUnionsMyClass1(ModelBuilder ModelBuilder)
		{
			CEntityUnionsMyClass1								Entity1=new CEntityUnionsMyClass1(1,"CLASS 1 SHARED 1 AAA","CLASS 1 SHARED 2 AAA","CLASS 1 VALUE 1 AAA","CLASS 1 VALUE 2 AAA");
			CEntityUnionsMyClass1								Entity2=new CEntityUnionsMyClass1(2,"CLASS 1 SHARED 1 BBB","CLASS 1 SHARED 2 BBB","CLASS 1 VALUE 1 BBB","CLASS 1 VALUE 2 BBB");
			CEntityUnionsMyClass1								Entity3=new CEntityUnionsMyClass1(3,"CLASS 1 SHARED 1 CCC","CLASS 1 SHARED 2 CCC","CLASS 1 VALUE 1 CCC","CLASS 1 VALUE 2 CCC");

			EntityTypeBuilder<CEntityUnionsMyClass1>			Entities=ModelBuilder.Entity<CEntityUnionsMyClass1>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataUnionsMyClass2(ModelBuilder ModelBuilder)
		{
			CEntityUnionsMyClass2								Entity1=new CEntityUnionsMyClass2(1,"CLASS 1 SHARED 1 AAA","CLASS 1 SHARED 2 AAA",110,120);
			CEntityUnionsMyClass2								Entity2=new CEntityUnionsMyClass2(2,"CLASS 1 SHARED 1 BBB","CLASS 1 SHARED 2 BBB",210,220);
			CEntityUnionsMyClass2								Entity3=new CEntityUnionsMyClass2(3,"CLASS 1 SHARED 1 CCC","CLASS 1 SHARED 2 CCC",310,320);

			EntityTypeBuilder<CEntityUnionsMyClass2>			Entities=ModelBuilder.Entity<CEntityUnionsMyClass2>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataFilteringByConvention(ModelBuilder ModelBuilder)
		{
			CEntityFilteringByConvention						Entity1=new CEntityFilteringByConvention(1,"AAA 1",101,1001,111.111);
			CEntityFilteringByConvention						Entity2=new CEntityFilteringByConvention(2,"AAA 2",102,1002,222.222);
			CEntityFilteringByConvention						Entity3=new CEntityFilteringByConvention(3,"BBB 1",103,1003,333.333);
			CEntityFilteringByConvention						Entity4=new CEntityFilteringByConvention(4,"BBB 2",104,1004,444.444);
			CEntityFilteringByConvention						Entity5=new CEntityFilteringByConvention(5,"CCC 1",105,1005,555.555);
			CEntityFilteringByConvention						Entity6=new CEntityFilteringByConvention(6,"CCC 2",106,1006,666.666);

			EntityTypeBuilder<CEntityFilteringByConvention>		Entities=ModelBuilder.Entity<CEntityFilteringByConvention>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataFilteringByFluentAPIImplicit(ModelBuilder ModelBuilder)
		{
			CEntityFilteringByFluentAPIImplicit					Entity1=new CEntityFilteringByFluentAPIImplicit(1,"AAA 1",101,1001,111.111);
			CEntityFilteringByFluentAPIImplicit					Entity2=new CEntityFilteringByFluentAPIImplicit(2,"AAA 2",102,1002,222.222);
			CEntityFilteringByFluentAPIImplicit					Entity3=new CEntityFilteringByFluentAPIImplicit(3,"BBB 1",103,1003,333.333);
			CEntityFilteringByFluentAPIImplicit					Entity4=new CEntityFilteringByFluentAPIImplicit(4,"BBB 2",104,1004,444.444);
			CEntityFilteringByFluentAPIImplicit					Entity5=new CEntityFilteringByFluentAPIImplicit(5,"CCC 1",105,1005,555.555);
			CEntityFilteringByFluentAPIImplicit					Entity6=new CEntityFilteringByFluentAPIImplicit(6,"CCC 2",106,1006,666.666);

			EntityTypeBuilder<CEntityFilteringByFluentAPIImplicit>	Entities=ModelBuilder.Entity<CEntityFilteringByFluentAPIImplicit>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataFilteringByFluentAPIExplicit(ModelBuilder ModelBuilder)
		{
			CEntityFilteringByFluentAPIExplicit					Entity1=new CEntityFilteringByFluentAPIExplicit(1,"AAA 1",101,1001,111.111);
			CEntityFilteringByFluentAPIExplicit					Entity2=new CEntityFilteringByFluentAPIExplicit(2,"AAA 2",102,1002,222.222);
			CEntityFilteringByFluentAPIExplicit					Entity3=new CEntityFilteringByFluentAPIExplicit(3,"BBB 1",103,1003,333.333);
			CEntityFilteringByFluentAPIExplicit					Entity4=new CEntityFilteringByFluentAPIExplicit(4,"BBB 2",104,1004,444.444);
			CEntityFilteringByFluentAPIExplicit					Entity5=new CEntityFilteringByFluentAPIExplicit(5,"CCC 1",105,1005,555.555);
			CEntityFilteringByFluentAPIExplicit					Entity6=new CEntityFilteringByFluentAPIExplicit(6,"CCC 2",106,1006,666.666);

			EntityTypeBuilder<CEntityFilteringByFluentAPIExplicit>	Entities=ModelBuilder.Entity<CEntityFilteringByFluentAPIExplicit>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataFilteringManually(ModelBuilder ModelBuilder)
		{
			CEntityFilteringManually							Entity1=new CEntityFilteringManually(1,"AAA 1",101);
			CEntityFilteringManually							Entity2=new CEntityFilteringManually(2,"AAA 2",102);
			CEntityFilteringManually							Entity3=new CEntityFilteringManually(3,"BBB 1",103);
			CEntityFilteringManually							Entity4=new CEntityFilteringManually(4,"BBB 2",104);
			CEntityFilteringManually							Entity5=new CEntityFilteringManually(5,"CCC 1",105);
			CEntityFilteringManually							Entity6=new CEntityFilteringManually(6,"CCC 2",106);

			EntityTypeBuilder<CEntityFilteringManually>			Entities=ModelBuilder.Entity<CEntityFilteringManually>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataSortingByConvention(ModelBuilder ModelBuilder)
		{
			CEntitySortingByConvention							Entity1=new CEntitySortingByConvention(1,"VALUE 111",8);
			CEntitySortingByConvention							Entity2=new CEntitySortingByConvention(2,"VALUE 222",7);
			CEntitySortingByConvention							Entity3=new CEntitySortingByConvention(3,"VALUE 333",6);
			CEntitySortingByConvention							Entity4=new CEntitySortingByConvention(4,"VALUE 444",5);
			CEntitySortingByConvention							Entity5=new CEntitySortingByConvention(5,"VALUE 111",4);
			CEntitySortingByConvention							Entity6=new CEntitySortingByConvention(6,"VALUE 222",3);
			CEntitySortingByConvention							Entity7=new CEntitySortingByConvention(7,"VALUE 333",2);
			CEntitySortingByConvention							Entity8=new CEntitySortingByConvention(8,"VALUE 444",1);

			EntityTypeBuilder<CEntitySortingByConvention>		Entities=ModelBuilder.Entity<CEntitySortingByConvention>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
			Entities.HasData(Entity7);
			Entities.HasData(Entity8);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataSortingByFluentAPI(ModelBuilder ModelBuilder)
		{
			CEntitySortingByFluentAPI							Entity1=new CEntitySortingByFluentAPI(1,"VALUE 111",8);
			CEntitySortingByFluentAPI							Entity2=new CEntitySortingByFluentAPI(2,"VALUE 222",7);
			CEntitySortingByFluentAPI							Entity3=new CEntitySortingByFluentAPI(3,"VALUE 333",6);
			CEntitySortingByFluentAPI							Entity4=new CEntitySortingByFluentAPI(4,"VALUE 444",5);
			CEntitySortingByFluentAPI							Entity5=new CEntitySortingByFluentAPI(5,"VALUE 111",4);
			CEntitySortingByFluentAPI							Entity6=new CEntitySortingByFluentAPI(6,"VALUE 222",3);
			CEntitySortingByFluentAPI							Entity7=new CEntitySortingByFluentAPI(7,"VALUE 333",2);
			CEntitySortingByFluentAPI							Entity8=new CEntitySortingByFluentAPI(8,"VALUE 444",1);

			EntityTypeBuilder<CEntitySortingByFluentAPI>		Entities=ModelBuilder.Entity<CEntitySortingByFluentAPI>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
			Entities.HasData(Entity7);
			Entities.HasData(Entity8);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataSortingManually(ModelBuilder ModelBuilder)
		{
			CEntitySortingManually								Entity1=new CEntitySortingManually(1,"VALUE 111",8);
			CEntitySortingManually								Entity2=new CEntitySortingManually(2,"VALUE 222",7);
			CEntitySortingManually								Entity3=new CEntitySortingManually(3,"VALUE 333",6);
			CEntitySortingManually								Entity4=new CEntitySortingManually(4,"VALUE 444",5);
			CEntitySortingManually								Entity5=new CEntitySortingManually(5,"VALUE 111",4);
			CEntitySortingManually								Entity6=new CEntitySortingManually(6,"VALUE 222",3);
			CEntitySortingManually								Entity7=new CEntitySortingManually(7,"VALUE 333",2);
			CEntitySortingManually								Entity8=new CEntitySortingManually(8,"VALUE 444",1);

			EntityTypeBuilder<CEntitySortingManually>			Entities=ModelBuilder.Entity<CEntitySortingManually>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
			Entities.HasData(Entity7);
			Entities.HasData(Entity8);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataPaginationCursorBased(ModelBuilder ModelBuilder)
		{
			CEntityPaginationCursorBased						Entity1=new CEntityPaginationCursorBased(1,101,1001);
			CEntityPaginationCursorBased						Entity2=new CEntityPaginationCursorBased(2,102,1002);
			CEntityPaginationCursorBased						Entity3=new CEntityPaginationCursorBased(3,103,1003);
			CEntityPaginationCursorBased						Entity4=new CEntityPaginationCursorBased(4,104,1004);
			CEntityPaginationCursorBased						Entity5=new CEntityPaginationCursorBased(5,105,1005);
			CEntityPaginationCursorBased						Entity6=new CEntityPaginationCursorBased(6,106,1006);
			CEntityPaginationCursorBased						Entity7=new CEntityPaginationCursorBased(7,107,1007);
			CEntityPaginationCursorBased						Entity8=new CEntityPaginationCursorBased(8,108,1008);
			CEntityPaginationCursorBased						Entity9=new CEntityPaginationCursorBased(9,109,1009);
			CEntityPaginationCursorBased						Entity10=new CEntityPaginationCursorBased(10,110,1010);
			CEntityPaginationCursorBased						Entity11=new CEntityPaginationCursorBased(11,111,1011);
			CEntityPaginationCursorBased						Entity12=new CEntityPaginationCursorBased(12,112,1012);
			CEntityPaginationCursorBased						Entity13=new CEntityPaginationCursorBased(13,113,1013);
			CEntityPaginationCursorBased						Entity14=new CEntityPaginationCursorBased(14,114,1014);
			CEntityPaginationCursorBased						Entity15=new CEntityPaginationCursorBased(15,115,1015);
			CEntityPaginationCursorBased						Entity16=new CEntityPaginationCursorBased(16,116,1016);
			CEntityPaginationCursorBased						Entity17=new CEntityPaginationCursorBased(17,117,1017);
			CEntityPaginationCursorBased						Entity18=new CEntityPaginationCursorBased(18,118,1018);
			CEntityPaginationCursorBased						Entity19=new CEntityPaginationCursorBased(19,119,1019);
			CEntityPaginationCursorBased						Entity20=new CEntityPaginationCursorBased(20,120,1020);

			EntityTypeBuilder<CEntityPaginationCursorBased>		Entities=ModelBuilder.Entity<CEntityPaginationCursorBased>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
			Entities.HasData(Entity7);
			Entities.HasData(Entity8);
			Entities.HasData(Entity9);
			Entities.HasData(Entity10);
			Entities.HasData(Entity11);
			Entities.HasData(Entity12);
			Entities.HasData(Entity13);
			Entities.HasData(Entity14);
			Entities.HasData(Entity15);
			Entities.HasData(Entity16);
			Entities.HasData(Entity17);
			Entities.HasData(Entity18);
			Entities.HasData(Entity19);
			Entities.HasData(Entity20);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataPaginationOffsetBased(ModelBuilder ModelBuilder)
		{
			CEntityPaginationOffsetBased						Entity1=new CEntityPaginationOffsetBased(1,101,1001);
			CEntityPaginationOffsetBased						Entity2=new CEntityPaginationOffsetBased(2,102,1002);
			CEntityPaginationOffsetBased						Entity3=new CEntityPaginationOffsetBased(3,103,1003);
			CEntityPaginationOffsetBased						Entity4=new CEntityPaginationOffsetBased(4,104,1004);
			CEntityPaginationOffsetBased						Entity5=new CEntityPaginationOffsetBased(5,105,1005);
			CEntityPaginationOffsetBased						Entity6=new CEntityPaginationOffsetBased(6,106,1006);
			CEntityPaginationOffsetBased						Entity7=new CEntityPaginationOffsetBased(7,107,1007);
			CEntityPaginationOffsetBased						Entity8=new CEntityPaginationOffsetBased(8,108,1008);
			CEntityPaginationOffsetBased						Entity9=new CEntityPaginationOffsetBased(9,109,1009);
			CEntityPaginationOffsetBased						Entity10=new CEntityPaginationOffsetBased(10,110,1010);
			CEntityPaginationOffsetBased						Entity11=new CEntityPaginationOffsetBased(11,111,1011);
			CEntityPaginationOffsetBased						Entity12=new CEntityPaginationOffsetBased(12,112,1012);
			CEntityPaginationOffsetBased						Entity13=new CEntityPaginationOffsetBased(13,113,1013);
			CEntityPaginationOffsetBased						Entity14=new CEntityPaginationOffsetBased(14,114,1014);
			CEntityPaginationOffsetBased						Entity15=new CEntityPaginationOffsetBased(15,115,1015);
			CEntityPaginationOffsetBased						Entity16=new CEntityPaginationOffsetBased(16,116,1016);
			CEntityPaginationOffsetBased						Entity17=new CEntityPaginationOffsetBased(17,117,1017);
			CEntityPaginationOffsetBased						Entity18=new CEntityPaginationOffsetBased(18,118,1018);
			CEntityPaginationOffsetBased						Entity19=new CEntityPaginationOffsetBased(19,119,1019);
			CEntityPaginationOffsetBased						Entity20=new CEntityPaginationOffsetBased(20,120,1020);

			EntityTypeBuilder<CEntityPaginationOffsetBased>		Entities=ModelBuilder.Entity<CEntityPaginationOffsetBased>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
			Entities.HasData(Entity7);
			Entities.HasData(Entity8);
			Entities.HasData(Entity9);
			Entities.HasData(Entity10);
			Entities.HasData(Entity11);
			Entities.HasData(Entity12);
			Entities.HasData(Entity13);
			Entities.HasData(Entity14);
			Entities.HasData(Entity15);
			Entities.HasData(Entity16);
			Entities.HasData(Entity17);
			Entities.HasData(Entity18);
			Entities.HasData(Entity19);
			Entities.HasData(Entity20);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityNames(ModelBuilder);

			FillEntityNames(ModelBuilder);

			ConfigureEntityOneToOnePrincipal1(ModelBuilder);
			ConfigureEntityOneToOneDependent1(ModelBuilder);
			ConfigureEntityOneToOnePrincipal2(ModelBuilder);
			ConfigureEntityOneToOneDependent2(ModelBuilder);

			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);

			ConfigureEntityDataLoaderBatchPrincipal(ModelBuilder);
			ConfigureEntityDataLoaderBatchDependent(ModelBuilder);

			ConfigureEntityDataLoaderGroupPrincipal(ModelBuilder);
			ConfigureEntityDataLoaderGroupDependent(ModelBuilder);

			ConfigureInterfacesMyInterface1(ModelBuilder);
			ConfigureInterfacesMyInterface2(ModelBuilder);

			ConfigureUnionsMyClass1(ModelBuilder);
			ConfigureUnionsMyClass2(ModelBuilder);

			ConfigureFilteringByConvention(ModelBuilder);
			ConfigureFilteringByFluentAPIImplicit(ModelBuilder);
			ConfigureFilteringByFluentAPIExplicit(ModelBuilder);
			ConfigureFilteringManually(ModelBuilder);

			ConfigureSortingByConvention(ModelBuilder);
			ConfigureSortingByFluentAPI(ModelBuilder);
			ConfigureSortingManually(ModelBuilder);

			ConfigurePaginationCursorBased(ModelBuilder);
			ConfigurePaginationOffsetBased(ModelBuilder);

			FillDataOneToOne1(ModelBuilder);
			FillDataOneToOne2(ModelBuilder);
			FillDataOneToMany(ModelBuilder);
			FillDataDataLoaderBatch(ModelBuilder);
			FillDataDataLoaderGroup(ModelBuilder);
			FillDataInterfacesMyInterface1(ModelBuilder);
			FillDataInterfacesMyInterface2(ModelBuilder);
			FillDataUnionsMyClass1(ModelBuilder);
			FillDataUnionsMyClass2(ModelBuilder);
			FillDataFilteringByConvention(ModelBuilder);
			FillDataFilteringByFluentAPIImplicit(ModelBuilder);
			FillDataFilteringByFluentAPIExplicit(ModelBuilder);
			FillDataFilteringManually(ModelBuilder);
			FillDataSortingByConvention(ModelBuilder);
			FillDataSortingByFluentAPI(ModelBuilder);
			FillDataSortingManually(ModelBuilder);
			FillDataPaginationCursorBased(ModelBuilder);
			FillDataPaginationOffsetBased(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------