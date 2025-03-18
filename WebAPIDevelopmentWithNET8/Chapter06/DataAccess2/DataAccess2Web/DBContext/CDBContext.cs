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
			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);

			FillDataOneToMany(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------