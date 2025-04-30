using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityConcurrencyTokensDataAnnotations>	MEntitiesConcurrencyTokensDataAnnotations;
		private DbSet<CEntityConcurrencyTokensFluentAPI>		MEntitiesConcurrencyTokensFluentAPI;
		private DbSet<CEntityOneToOnePrincipal>					MEntitiesOneToOnePrincipal;
		private DbSet<CEntityOneToOneDependent>					MEntitiesOneToOneDependent;
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityManyToManyM>						MEntitiesManyToManyM;
		private DbSet<CEntityManyToManyN>						MEntitiesManyToManyN;
		private DbSet<CEntityManyToManyMN>						MEntitiesManyToManyMN;
		private DbSet<CEntityRawSql>							MEntitiesRawSql;
		private DbSet<CEntityBulkOperations>					MEntitiesBulkOperations;
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
		public DbSet<CEntityConcurrencyTokensDataAnnotations>	EntitiesConcurrencyTokensDataAnnotations
		{
			get
			{
				return(MEntitiesConcurrencyTokensDataAnnotations);
			}
			set
			{
				MEntitiesConcurrencyTokensDataAnnotations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityConcurrencyTokensFluentAPI>			EntitiesConcurrencyTokensFluentAPI
		{
			get
			{
				return(MEntitiesConcurrencyTokensFluentAPI);
			}
			set
			{
				MEntitiesConcurrencyTokensFluentAPI=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOnePrincipal>					EntitiesOneToOnePrincipal
		{
			get
			{
				return(MEntitiesOneToOnePrincipal);
			}
			set
			{
				MEntitiesOneToOnePrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependent>					EntitiesOneToOneDependent
		{
			get
			{
				return(MEntitiesOneToOneDependent);
			}
			set
			{
				MEntitiesOneToOneDependent=value;
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
		public DbSet<CEntityManyToManyM>						EntitiesManyToManyM
		{
			get
			{
				return(MEntitiesManyToManyM);
			}
			set
			{
				MEntitiesManyToManyM=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyN>						EntitiesManyToManyN
		{
			get
			{
				return(MEntitiesManyToManyN);
			}
			set
			{
				MEntitiesManyToManyN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMN>						EntitiesManyToManyMN
		{
			get
			{
				return(MEntitiesManyToManyMN);
			}
			set
			{
				MEntitiesManyToManyMN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityRawSql>								EntitiesRawSql
		{
			get
			{
				return(MEntitiesRawSql);
			}
			set
			{
				MEntitiesRawSql=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityBulkOperations>						EntitiesBulkOperations
		{
			get
			{
				return(MEntitiesBulkOperations);
			}
			set
			{
				MEntitiesBulkOperations=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityConcurrencyTokensDataAnnotations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityConcurrencyTokensDataAnnotations>	Entity=ModelBuilder.Entity<CEntityConcurrencyTokensDataAnnotations>();

			Entity.ToTable("EntitiesConcurrencyTokensDataAnnotations");

			Entity.HasKey(P => P.EntityID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityConcurrencyTokensFluentAPI(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityConcurrencyTokensFluentAPI>	Entity=ModelBuilder.Entity<CEntityConcurrencyTokensFluentAPI>();

			Entity.ToTable("EntitiesConcurrencyTokensFluentAPI");

			Entity.HasKey(P => P.EntityID);

			// !!! Ziska sa PROPERTY, ktora bude oznacena ako CONCURRENCY TOKEN.
			PropertyBuilder<int>								ConcurrencyTokenProperty=Entity.Property(P => P.EntityValue);

			// !!! PROPERTY sa nastavi ako CONCURRENCY TOKEN.
			ConcurrencyTokenProperty.IsConcurrencyToken(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableOneToOnePrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToOnePrincipal>().ToTable("EntitiesOneToOnePrincipal");

			ModelBuilder.Entity<CEntityOneToOnePrincipal>().HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableOneToOneDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToOneDependent>().ToTable("EntitiesOneToOneDependent");

			ModelBuilder.Entity<CEntityOneToOneDependent>().HasKey(P => P.EntityDependentID);

			EntityTypeBuilder<CEntityOneToOneDependent>			Entity=ModelBuilder.Entity<CEntityOneToOneDependent>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityOneToOneDependent,CEntityOneToOnePrincipal>	LeftSideRelationship=Entity.HasOne(P => P.EntityPrincipal);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceReferenceBuilder<CEntityOneToOneDependent,CEntityOneToOnePrincipal>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityDependent);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey<CEntityOneToOneDependent>(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyPrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToManyPrincipal>().ToTable("EntitiesOneToManyPrincipal");

			ModelBuilder.Entity<CEntityOneToManyPrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityOneToManyPrincipal>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToManyDependent>().ToTable("EntitiesOneToManyDependent");

			ModelBuilder.Entity<CEntityOneToManyDependent>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyM(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyM>().ToTable("EntitiesManyToManyM");

			ModelBuilder.Entity<CEntityManyToManyM>().HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyN>().ToTable("EntitiesManyToManyN");

			ModelBuilder.Entity<CEntityManyToManyN>().HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableManyToManyMN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyMN>().ToTable("EntitiesManyToManyMN");

			// !!!!! LINK ENTITY v RELATIONSHIP M:N MUSI mat COMPOSITE KEY.
			ModelBuilder.Entity<CEntityManyToManyMN>().HasKey(nameof(CEntityManyToManyMN.EntityMID),nameof(CEntityManyToManyMN.EntityNID));

			EntityTypeBuilder<CEntityManyToManyMN>				Entity=ModelBuilder.Entity<CEntityManyToManyMN>();

			// !!!!! Vytvori sa RELATIONSHIP 1:N medzi LINK ENTITY a ENTITY M.

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityManyToManyMN,CEntityManyToManyM>	RightSideEntityM=Entity.HasOne(P => P.EntityM);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityManyToManyM,CEntityManyToManyMN>	LeftSideEntityM=RightSideEntityM.WithMany(P => P.EntitiesMN);

			// !!!!! Definuje sa FOREIGN KEY.
			LeftSideEntityM.HasForeignKey(P => P.EntityMID);

			// !!!!! Vytvori sa RELATIONSHIP 1:N medzi LINK ENTITY a ENTITY M.

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityManyToManyMN,CEntityManyToManyN>	RightSideEntityN=Entity.HasOne(P => P.EntityN);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityManyToManyN,CEntityManyToManyMN>	LeftSideEntityN=RightSideEntityN.WithMany(P => P.EntitiesMN);

			// !!!!! Definuje sa FOREIGN KEY.
			LeftSideEntityN.HasForeignKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityRawSql(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityRawSql>					Entity=ModelBuilder.Entity<CEntityRawSql>();

			Entity.ToTable("EntitiesRawSql");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityBulkOperations(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityBulkOperations>			Entity=ModelBuilder.Entity<CEntityBulkOperations>();

			Entity.ToTable("EntitiesBulkOperations");

			Entity.HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataConcurrencyTokensDataAnnotations(ModelBuilder ModelBuilder)
		{
			// !!!!! GUIDs pri pouziti METHOD [DataBuilder<TEntity> HasData(params TEntity[] Data)] MUSIA byt CONSTANTS.
			Guid												ID1=Guid.Parse("F5CDC704-2D54-44A7-817B-A4776F12EB26");
			Guid												ID2=Guid.Parse("39CC4026-30E6-4B4E-ABB9-0EAD985B7A1A");

			CEntityConcurrencyTokensDataAnnotations				Entity1=new CEntityConcurrencyTokensDataAnnotations(1,100,ID1);
			CEntityConcurrencyTokensDataAnnotations				Entity2=new CEntityConcurrencyTokensDataAnnotations(2,200,ID2);

			EntityTypeBuilder<CEntityConcurrencyTokensDataAnnotations>	Entities=ModelBuilder.Entity<CEntityConcurrencyTokensDataAnnotations>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataConcurrencyTokensFluentAPI(ModelBuilder ModelBuilder)
		{
			// !!!!! GUIDs pri pouziti METHOD [DataBuilder<TEntity> HasData(params TEntity[] Data)] MUSIA byt CONSTANTS.
			Guid												ID1=Guid.Parse("F5CDC704-2D54-44A7-817B-A4776F12EB26");
			Guid												ID2=Guid.Parse("39CC4026-30E6-4B4E-ABB9-0EAD985B7A1A");

			CEntityConcurrencyTokensFluentAPI					Entity1=new CEntityConcurrencyTokensFluentAPI(1,100,ID1);
			CEntityConcurrencyTokensFluentAPI					Entity2=new CEntityConcurrencyTokensFluentAPI(2,200,ID2);

			EntityTypeBuilder<CEntityConcurrencyTokensFluentAPI>	Entities=ModelBuilder.Entity<CEntityConcurrencyTokensFluentAPI>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOneToOne(ModelBuilder ModelBuilder)
		{
			CEntityOneToOnePrincipal							EntityOneToOnePrincipal1=new CEntityOneToOnePrincipal(1,"PARENT AAA");
			CEntityOneToOnePrincipal							EntityOneToOnePrincipal2=new CEntityOneToOnePrincipal(2,"PARENT BBB");

			CEntityOneToOneDependent							EntityOneToOneDependent1=new CEntityOneToOneDependent(1,"CHILD AAA",1);
			CEntityOneToOneDependent							EntityOneToOneDependent2=new CEntityOneToOneDependent(2,"CHILD BBB",2);

			EntityTypeBuilder<CEntityOneToOnePrincipal>			EntitiesPrincipal=ModelBuilder.Entity<CEntityOneToOnePrincipal>();
			EntityTypeBuilder<CEntityOneToOneDependent>			EntitiesDependent=ModelBuilder.Entity<CEntityOneToOneDependent>();

			EntitiesPrincipal.HasData(EntityOneToOnePrincipal1);
			EntitiesPrincipal.HasData(EntityOneToOnePrincipal2);

			EntitiesDependent.HasData(EntityOneToOneDependent1);
			EntitiesDependent.HasData(EntityOneToOneDependent2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOneToMany(ModelBuilder ModelBuilder)
		{
			CEntityOneToManyPrincipal							EntityOneToManyPrincipal1=new CEntityOneToManyPrincipal(1,"AAA");
			CEntityOneToManyPrincipal							EntityOneToManyPrincipal2=new CEntityOneToManyPrincipal(2,"BBB");

			CEntityOneToManyDependent							EntityOneToManyDependent11=new CEntityOneToManyDependent(1,"AAA 111",1);
			CEntityOneToManyDependent							EntityOneToManyDependent12=new CEntityOneToManyDependent(2,"AAA 222",1);
			CEntityOneToManyDependent							EntityOneToManyDependent21=new CEntityOneToManyDependent(3,"BBB 111",2);
			CEntityOneToManyDependent							EntityOneToManyDependent22=new CEntityOneToManyDependent(4,"BBB 222",2);

			EntityTypeBuilder<CEntityOneToManyPrincipal>		EntitiesPrincipal=ModelBuilder.Entity<CEntityOneToManyPrincipal>();
			EntityTypeBuilder<CEntityOneToManyDependent>		EntitiesDependent=ModelBuilder.Entity<CEntityOneToManyDependent>();

			EntitiesPrincipal.HasData(EntityOneToManyPrincipal1);
			EntitiesPrincipal.HasData(EntityOneToManyPrincipal2);

			EntitiesDependent.HasData(EntityOneToManyDependent11);
			EntitiesDependent.HasData(EntityOneToManyDependent12);
			EntitiesDependent.HasData(EntityOneToManyDependent21);
			EntitiesDependent.HasData(EntityOneToManyDependent22);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataManyToMany(ModelBuilder ModelBuilder)
		{
			CEntityManyToManyM									EntityManyToManyM1=new CEntityManyToManyM(1,"AAA");
			CEntityManyToManyM									EntityManyToManyM2=new CEntityManyToManyM(2,"BBB");

			CEntityManyToManyN									EntityManyToManyN1=new CEntityManyToManyN(1,"111");
			CEntityManyToManyN									EntityManyToManyN2=new CEntityManyToManyN(2,"222");

			CEntityManyToManyMN									EntityManyToManyMN11=new CEntityManyToManyMN(1,1,"LINK 11");
			CEntityManyToManyMN									EntityManyToManyMN12=new CEntityManyToManyMN(1,2,"LINK 12");
			CEntityManyToManyMN									EntityManyToManyMN21=new CEntityManyToManyMN(2,1,"LINK 21");
			CEntityManyToManyMN									EntityManyToManyMN22=new CEntityManyToManyMN(2,2,"LINK 22");

			EntityTypeBuilder<CEntityManyToManyM>				EntitiesM=ModelBuilder.Entity<CEntityManyToManyM>();
			EntityTypeBuilder<CEntityManyToManyN>				EntitiesN=ModelBuilder.Entity<CEntityManyToManyN>();
			EntityTypeBuilder<CEntityManyToManyMN>				EntitiesMN=ModelBuilder.Entity<CEntityManyToManyMN>();

			EntitiesM.HasData(EntityManyToManyM1);
			EntitiesM.HasData(EntityManyToManyM2);

			EntitiesN.HasData(EntityManyToManyN1);
			EntitiesN.HasData(EntityManyToManyN2);

			EntitiesMN.HasData(EntityManyToManyMN11);
			EntitiesMN.HasData(EntityManyToManyMN12);
			EntitiesMN.HasData(EntityManyToManyMN21);
			EntitiesMN.HasData(EntityManyToManyMN22);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataEntityRawSql(ModelBuilder ModelBuilder)
		{
			CEntityRawSql										Entity1=new CEntityRawSql(1,10,11);
			CEntityRawSql										Entity2=new CEntityRawSql(2,10,12);
			CEntityRawSql										Entity3=new CEntityRawSql(3,100,101);
			CEntityRawSql										Entity4=new CEntityRawSql(4,100,102);
			CEntityRawSql										Entity5=new CEntityRawSql(5,1000,1001);
			CEntityRawSql										Entity6=new CEntityRawSql(6,1000,1002);

			EntityTypeBuilder<CEntityRawSql>					Entities=ModelBuilder.Entity<CEntityRawSql>();

			Entities.HasData(Entity1);
			Entities.HasData(Entity2);
			Entities.HasData(Entity3);
			Entities.HasData(Entity4);
			Entities.HasData(Entity5);
			Entities.HasData(Entity6);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataEntityBulkOperations(ModelBuilder ModelBuilder)
		{
			CEntityBulkOperations								Entity1=new CEntityBulkOperations(1,10,11,16);
			CEntityBulkOperations								Entity2=new CEntityBulkOperations(2,10,12,17);
			CEntityBulkOperations								Entity3=new CEntityBulkOperations(3,100,101,106);
			CEntityBulkOperations								Entity4=new CEntityBulkOperations(4,100,102,107);
			CEntityBulkOperations								Entity5=new CEntityBulkOperations(5,1000,1001,1006);
			CEntityBulkOperations								Entity6=new CEntityBulkOperations(6,1000,1002,1007);

			EntityTypeBuilder<CEntityBulkOperations>			Entities=ModelBuilder.Entity<CEntityBulkOperations>();

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
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityConcurrencyTokensDataAnnotations(ModelBuilder);
			ConfigureEntityConcurrencyTokensFluentAPI(ModelBuilder);
			ConfigureTableOneToOnePrincipal(ModelBuilder);
			ConfigureTableOneToOneDependent(ModelBuilder);
			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);
			ConfigureTableManyToManyM(ModelBuilder);
			ConfigureTableManyToManyN(ModelBuilder);
			ConfigureTableManyToManyMN(ModelBuilder);
			ConfigureEntityRawSql(ModelBuilder);
			ConfigureEntityBulkOperations(ModelBuilder);

			FillDataConcurrencyTokensDataAnnotations(ModelBuilder);
			FillDataConcurrencyTokensFluentAPI(ModelBuilder);
			FillDataOneToOne(ModelBuilder);
			FillDataOneToMany(ModelBuilder);
			FillDataManyToMany(ModelBuilder);
			FillDataEntityRawSql(ModelBuilder);
			FillDataEntityBulkOperations(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------