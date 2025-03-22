using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2Web
{
//----------------------------------------------------------------------------------------------------------------------
    public sealed class CDBContext : DbContext
    {
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityOneToOnePrincipal>					MEntitiesOneToOnePrincipal;
		private DbSet<CEntityOneToOneDependent>					MEntitiesOneToOneDependent;
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityManyToManyM>						MEntitiesManyToManyM;
		private DbSet<CEntityManyToManyN>						MEntitiesManyToManyN;
		private DbSet<CEntityManyToManyMN>						MEntitiesManyToManyMN;
		private DbSet<CEntityOwnedOneToOnePrincipal>			MEntitiesOwnedOneToOnePrincipal;
		private DbSet<CEntityOwnedOneToManyPrincipal>			MEntitiesOwnedOneToManyPrincipal;
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
		public DbSet<CEntityOwnedOneToOnePrincipal>				EntitiesOwnedOneToOnePrincipal
		{
			get
			{
				return(MEntitiesOwnedOneToOnePrincipal);
			}
			set
			{
				MEntitiesOwnedOneToOnePrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOwnedOneToManyPrincipal>			EntitiesOwnedOneToManyPrincipal
		{
			get
			{
				return(MEntitiesOwnedOneToManyPrincipal);
			}
			set
			{
				MEntitiesOwnedOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOnePrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOnePrincipal>			Entity=ModelBuilder.Entity<CEntityOneToOnePrincipal>();

			Entity.ToTable("EntitiesOneToOnePrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			ReferenceNavigationBuilder<CEntityOneToOnePrincipal,CEntityOneToOneDependent>	LeftSide=Entity.HasOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceReferenceBuilder<CEntityOneToOnePrincipal,CEntityOneToOneDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey<CEntityOneToOneDependent>(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToOneDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOneToOneDependent>			Entity=ModelBuilder.Entity<CEntityOneToOneDependent>();

			Entity.ToTable("EntitiesOneToOneDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
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
		private void ConfigureEntityManyToManyM(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyM>				Entity=ModelBuilder.Entity<CEntityManyToManyM>();

			Entity.ToTable("EntitiesManyToManyM");

			Entity.HasKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityManyToManyM,CEntityManyToManyMN>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToManyM,CEntityManyToManyMN>	RightSide=LeftSide.WithOne(P => P.EntityM);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityMID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyN(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyN>				Entity=ModelBuilder.Entity<CEntityManyToManyN>();

			Entity.ToTable("EntitiesManyToManyN");

			Entity.HasKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityManyToManyN,CEntityManyToManyMN>	LeftSide=Entity.HasMany(P => P.EntitiesMN);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityManyToManyN,CEntityManyToManyMN>	RightSide=LeftSide.WithOne(P => P.EntityN);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityNID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMN(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityManyToManyMN>				Entity=ModelBuilder.Entity<CEntityManyToManyMN>();

			Entity.ToTable("EntitiesManyToManyMN");

			// !!!!! ENTITY MN v RELATIONSHIP M:N ma ARTIFICIAL PRIMARY KEY.
			Entity.HasKey(P => P.EntityMNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeOneToOnePrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedOneToOnePrincipal>	Entity=ModelBuilder.Entity<CEntityOwnedOneToOnePrincipal>();

			Entity.ToTable("EntitiesOwnedOneToOnePrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			OwnedNavigationBuilder<CEntityOwnedOneToOnePrincipal,CEntityOwnedOneToOneDependent>	LeftSide=Entity.OwnsOne(P => P.EntityDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			OwnershipBuilder<CEntityOwnedOneToOnePrincipal,CEntityOwnedOneToOneDependent>	RightSide=LeftSide.WithOwner(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeOneToOneDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedOneToOnePrincipal>	Entity=ModelBuilder.Entity<CEntityOwnedOneToOnePrincipal>();
			
			OwnedNavigationBuilder<CEntityOwnedOneToOnePrincipal,CEntityOwnedOneToOneDependent>	NavigationProperty=Entity.OwnsOne(P => P.EntityDependent);

			// !!!!! OWNED TYPE bude v osobitnej TABLE.
			NavigationProperty.ToTable("EntitiesOwnedOneToOneDependent");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeOneToManyPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedOneToManyPrincipal>	Entity=ModelBuilder.Entity<CEntityOwnedOneToManyPrincipal>();

			Entity.ToTable("EntitiesOwnedOneToManyPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			OwnedNavigationBuilder<CEntityOwnedOneToManyPrincipal,CEntityOwnedOneToManyDependent>	LeftSide=Entity.OwnsMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			OwnershipBuilder<CEntityOwnedOneToManyPrincipal,CEntityOwnedOneToManyDependent>	RightSide=LeftSide.WithOwner(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOwnedTypeOneToManyDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityOwnedOneToManyPrincipal>	Entity=ModelBuilder.Entity<CEntityOwnedOneToManyPrincipal>();
			
			OwnedNavigationBuilder<CEntityOwnedOneToManyPrincipal,CEntityOwnedOneToManyDependent>	NavigationProperty=Entity.OwnsMany(P => P.EntitiesDependent);

			NavigationProperty.HasKey(P => P.EntityDependentID);

			// !!!!! OWNED TYPE bude v osobitnej TABLE.
			NavigationProperty.ToTable("EntitiesOwnedOneToManyDependent");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOneToOne(ModelBuilder ModelBuilder)
		{
			CEntityOneToOnePrincipal							EntityOneToOnePrincipal1=new CEntityOneToOnePrincipal(1,"PRINCIPAL 111");
			CEntityOneToOnePrincipal							EntityOneToOnePrincipal2=new CEntityOneToOnePrincipal(2,"PRINCIPAL 222");

			EntityTypeBuilder<CEntityOneToOnePrincipal>			EntityPrincipal=ModelBuilder.Entity<CEntityOneToOnePrincipal>();

			EntityPrincipal.HasData(EntityOneToOnePrincipal1);
			EntityPrincipal.HasData(EntityOneToOnePrincipal2);

			CEntityOneToOneDependent							EntityOneToOneDependent11=new CEntityOneToOneDependent(1,"DEPENDENT 111",EntityOneToOnePrincipal1.EntityPrincipalID);
			CEntityOneToOneDependent							EntityOneToOneDependent12=new CEntityOneToOneDependent(2,"DEPENDENT 222",EntityOneToOnePrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToOneDependent>			EntityDependent=ModelBuilder.Entity<CEntityOneToOneDependent>();

			EntityDependent.HasData(EntityOneToOneDependent11);
			EntityDependent.HasData(EntityOneToOneDependent12);
		}
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
		private void FillDataManyToMany(ModelBuilder ModelBuilder)
		{
			CEntityManyToManyM									EntityManyToManyM1=new CEntityManyToManyM(1,"ENTITY M - 111");
			CEntityManyToManyM									EntityManyToManyM2=new CEntityManyToManyM(2,"ENTITY M - 222");

			EntityTypeBuilder<CEntityManyToManyM>				EntityManyToManyM=ModelBuilder.Entity<CEntityManyToManyM>();

			EntityManyToManyM.HasData(EntityManyToManyM1);
			EntityManyToManyM.HasData(EntityManyToManyM2);

			CEntityManyToManyN									EntityManyToManyN1=new CEntityManyToManyN(1,"ENTITY N - 111");
			CEntityManyToManyN									EntityManyToManyN2=new CEntityManyToManyN(2,"ENTITY N - 222");

			EntityTypeBuilder<CEntityManyToManyN>				EntityManyToManyN=ModelBuilder.Entity<CEntityManyToManyN>();

			EntityManyToManyN.HasData(EntityManyToManyN1);
			EntityManyToManyN.HasData(EntityManyToManyN2);

			CEntityManyToManyMN									EntityManyToManyMN11=new CEntityManyToManyMN(1,"ENTITY MN - 11",1,1);
			CEntityManyToManyMN									EntityManyToManyMN12=new CEntityManyToManyMN(2,"ENTITY MN - 12",1,2);
			CEntityManyToManyMN									EntityManyToManyMN21=new CEntityManyToManyMN(3,"ENTITY MN - 21",2,1);
			CEntityManyToManyMN									EntityManyToManyMN22=new CEntityManyToManyMN(4,"ENTITY MN - 22",2,2);

			EntityTypeBuilder<CEntityManyToManyMN>				EntityManyToManyNN=ModelBuilder.Entity<CEntityManyToManyMN>();

			EntityManyToManyNN.HasData(EntityManyToManyMN11);
			EntityManyToManyNN.HasData(EntityManyToManyMN12);
			EntityManyToManyNN.HasData(EntityManyToManyMN21);
			EntityManyToManyNN.HasData(EntityManyToManyMN22);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOwnedTypeOneToOne(ModelBuilder ModelBuilder)
		{
			CEntityOwnedOneToOnePrincipal						EntityOneToOnePrincipal1=new CEntityOwnedOneToOnePrincipal(1,"ENTITY PRINCIPAL 1");
			CEntityOwnedOneToOnePrincipal						EntityOneToOnePrincipal2=new CEntityOwnedOneToOnePrincipal(2,"ENTITY PRINCIPAL 2");

			CEntityOwnedOneToOneDependent						EntityOneToOneDependent1=new CEntityOwnedOneToOneDependent(EntityOneToOnePrincipal1.EntityPrincipalID,"ENTITY DEPENDENT 1");
			CEntityOwnedOneToOneDependent						EntityOneToOneDependent2=new CEntityOwnedOneToOneDependent(EntityOneToOnePrincipal2.EntityPrincipalID,"ENTITY DEPENDENT 2");

			EntityTypeBuilder<CEntityOwnedOneToOnePrincipal>	Entity=ModelBuilder.Entity<CEntityOwnedOneToOnePrincipal>();

			Entity.HasData(EntityOneToOnePrincipal1);
			Entity.HasData(EntityOneToOnePrincipal2);

			OwnedNavigationBuilder<CEntityOwnedOneToOnePrincipal,CEntityOwnedOneToOneDependent>	Property=Entity.OwnsOne(P => P.EntityDependent);

			Property.HasData(EntityOneToOneDependent1);
			Property.HasData(EntityOneToOneDependent2);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDataOwnedTypeOneToMany(ModelBuilder ModelBuilder)
		{
			CEntityOwnedOneToManyPrincipal						EntityOneToManyPrincipal1=new CEntityOwnedOneToManyPrincipal(1,"ENTITY PRINCIPAL 1");
			CEntityOwnedOneToManyPrincipal						EntityOneToManyPrincipal2=new CEntityOwnedOneToManyPrincipal(2,"ENTITY PRINCIPAL 2");

			CEntityOwnedOneToManyDependent						EntityOneToManyDependent11=new CEntityOwnedOneToManyDependent(1,"ENTITY DEPENDENT 11",EntityOneToManyPrincipal1.EntityPrincipalID);
			CEntityOwnedOneToManyDependent						EntityOneToManyDependent12=new CEntityOwnedOneToManyDependent(2,"ENTITY DEPENDENT 12",EntityOneToManyPrincipal1.EntityPrincipalID);
			CEntityOwnedOneToManyDependent						EntityOneToManyDependent21=new CEntityOwnedOneToManyDependent(3,"ENTITY DEPENDENT 21",EntityOneToManyPrincipal2.EntityPrincipalID);
			CEntityOwnedOneToManyDependent						EntityOneToManyDependent22=new CEntityOwnedOneToManyDependent(4,"ENTITY DEPENDENT 22",EntityOneToManyPrincipal2.EntityPrincipalID);

			EntityTypeBuilder<CEntityOwnedOneToManyPrincipal>	Entity=ModelBuilder.Entity<CEntityOwnedOneToManyPrincipal>();

			Entity.HasData(EntityOneToManyPrincipal1);
			Entity.HasData(EntityOneToManyPrincipal2);

			OwnedNavigationBuilder<CEntityOwnedOneToManyPrincipal,CEntityOwnedOneToManyDependent>	Property=Entity.OwnsMany(P => P.EntitiesDependent);

			Property.HasData(EntityOneToManyDependent11);
			Property.HasData(EntityOneToManyDependent12);
			Property.HasData(EntityOneToManyDependent21);
			Property.HasData(EntityOneToManyDependent22);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityOneToOnePrincipal(ModelBuilder);
			ConfigureEntityOneToOneDependent(ModelBuilder);

			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);

			ConfigureEntityManyToManyM(ModelBuilder);
			ConfigureEntityManyToManyN(ModelBuilder);
			ConfigureEntityManyToManyMN(ModelBuilder);

			ConfigureEntityOwnedTypeOneToOnePrincipal(ModelBuilder);
			ConfigureEntityOwnedTypeOneToOneDependent(ModelBuilder);

			ConfigureEntityOwnedTypeOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOwnedTypeOneToManyDependent(ModelBuilder);

			FillDataOneToOne(ModelBuilder);
			FillDataOneToMany(ModelBuilder);
			FillDataManyToMany(ModelBuilder);
			FillDataOwnedTypeOneToOne(ModelBuilder);
			FillDataOwnedTypeOneToMany(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------