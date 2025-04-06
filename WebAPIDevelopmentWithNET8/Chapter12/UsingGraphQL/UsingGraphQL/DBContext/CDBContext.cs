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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNames(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityName>().ToTable("NamesEntities");

			ModelBuilder.Entity<CEntityName>().HasKey(P => P.ID);
		}
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

			FillDataOneToOne1(ModelBuilder);
			FillDataOneToOne2(ModelBuilder);
			FillDataOneToMany(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------