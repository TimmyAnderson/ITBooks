using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace RelationalProperties
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			CTestEntity											TestEntity1=new CTestEntity("AAA");
			CTestEntity											TestEntity2=new CTestEntity("BBB");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);

			CEntityOneToOneDependentConventions					EntityOneToOneDependentConventions1=new CEntityOneToOneDependentConventions("DEPENDENT 111");
			CEntityOneToOneDependentConventions					EntityOneToOneDependentConventions2=new CEntityOneToOneDependentConventions("DEPENDENT 222");

			CEntityOneToOnePrincipalConventions					EntityOneToOnePrincipalConventions1=new CEntityOneToOnePrincipalConventions("PRINCIPAL 111");
			CEntityOneToOnePrincipalConventions					EntityOneToOnePrincipalConventions2=new CEntityOneToOnePrincipalConventions("PRINCIPAL 222");

			EntityOneToOnePrincipalConventions1.EntityDependent=EntityOneToOneDependentConventions1;
			EntityOneToOnePrincipalConventions2.EntityDependent=EntityOneToOneDependentConventions2;

			Context.EntitiesOneToOnePrincipalConventions.Add(EntityOneToOnePrincipalConventions1);
			Context.EntitiesOneToOnePrincipalConventions.Add(EntityOneToOnePrincipalConventions2);

			CEntityZeroToOneDependentConventions				EntityZeroToOneDependentConventions1=new CEntityZeroToOneDependentConventions("DEPENDENT 111");
			CEntityZeroToOneDependentConventions				EntityZeroToOneDependentConventions2=new CEntityZeroToOneDependentConventions("DEPENDENT 222");

			CEntityZeroToOnePrincipalConventions				EntityZeroToOnePrincipalConventions1=new CEntityZeroToOnePrincipalConventions("PRINCIPAL 111");
			CEntityZeroToOnePrincipalConventions				EntityZeroToOnePrincipalConventions2=new CEntityZeroToOnePrincipalConventions("PRINCIPAL 222");

			EntityZeroToOnePrincipalConventions1.EntityDependent=EntityZeroToOneDependentConventions1;
			EntityZeroToOnePrincipalConventions2.EntityDependent=EntityZeroToOneDependentConventions2;

			Context.EntitiesZeroToOnePrincipalConventions.Add(EntityZeroToOnePrincipalConventions1);
			Context.EntitiesZeroToOnePrincipalConventions.Add(EntityZeroToOnePrincipalConventions2);

			CEntityOneToManyDependentConventions				EntityOneToManyDependentConventions11=new CEntityOneToManyDependentConventions("DEPENDENT 111");
			CEntityOneToManyDependentConventions				EntityOneToManyDependentConventions12=new CEntityOneToManyDependentConventions("DEPENDENT 222");
			CEntityOneToManyDependentConventions				EntityOneToManyDependentConventions21=new CEntityOneToManyDependentConventions("DEPENDENT 333");
			CEntityOneToManyDependentConventions				EntityOneToManyDependentConventions22=new CEntityOneToManyDependentConventions("DEPENDENT 444");

			CEntityOneToManyPrincipalConventions				EntityOneToManyPrincipalConventions1=new CEntityOneToManyPrincipalConventions("PRINCIPAL 111",new CEntityOneToManyDependentConventions[]{EntityOneToManyDependentConventions11,EntityOneToManyDependentConventions12});
			CEntityOneToManyPrincipalConventions				EntityOneToManyPrincipalConventions2=new CEntityOneToManyPrincipalConventions("PRINCIPAL 222",new CEntityOneToManyDependentConventions[]{EntityOneToManyDependentConventions21,EntityOneToManyDependentConventions22});

			Context.EntitiesOneToManyPrincipalConventions.Add(EntityOneToManyPrincipalConventions1);
			Context.EntitiesOneToManyPrincipalConventions.Add(EntityOneToManyPrincipalConventions2);

			CEntityZeroToManyDependentConventions				EntityZeroToManyDependentConventions11=new CEntityZeroToManyDependentConventions("DEPENDENT 111");
			CEntityZeroToManyDependentConventions				EntityZeroToManyDependentConventions12=new CEntityZeroToManyDependentConventions("DEPENDENT 222");
			CEntityZeroToManyDependentConventions				EntityZeroToManyDependentConventions21=new CEntityZeroToManyDependentConventions("DEPENDENT 333");
			CEntityZeroToManyDependentConventions				EntityZeroToManyDependentConventions22=new CEntityZeroToManyDependentConventions("DEPENDENT 444");

			CEntityZeroToManyPrincipalConventions				EntityZeroToManyPrincipalConventions1=new CEntityZeroToManyPrincipalConventions("PRINCIPAL 111",new CEntityZeroToManyDependentConventions[]{EntityZeroToManyDependentConventions11,EntityZeroToManyDependentConventions12});
			CEntityZeroToManyPrincipalConventions				EntityZeroToManyPrincipalConventions2=new CEntityZeroToManyPrincipalConventions("PRINCIPAL 222",new CEntityZeroToManyDependentConventions[]{EntityZeroToManyDependentConventions21,EntityZeroToManyDependentConventions22});

			Context.EntitiesZeroToManyPrincipalConventions.Add(EntityZeroToManyPrincipalConventions1);
			Context.EntitiesZeroToManyPrincipalConventions.Add(EntityZeroToManyPrincipalConventions2);

			CEntityForeignKeyName1DependentConventions			EntityForeignKeyName1DependentConventions11=new CEntityForeignKeyName1DependentConventions("DEPENDENT 111");
			CEntityForeignKeyName1DependentConventions			EntityForeignKeyName1DependentConventions12=new CEntityForeignKeyName1DependentConventions("DEPENDENT 222");
			CEntityForeignKeyName1DependentConventions			EntityForeignKeyName1DependentConventions21=new CEntityForeignKeyName1DependentConventions("DEPENDENT 333");
			CEntityForeignKeyName1DependentConventions			EntityForeignKeyName1DependentConventions22=new CEntityForeignKeyName1DependentConventions("DEPENDENT 444");

			CEntityForeignKeyName1PrincipalConventions			EntityForeignKeyName1PrincipalConventions1=new CEntityForeignKeyName1PrincipalConventions("PRINCIPAL 111",new CEntityForeignKeyName1DependentConventions[]{EntityForeignKeyName1DependentConventions11,EntityForeignKeyName1DependentConventions12});
			CEntityForeignKeyName1PrincipalConventions			EntityForeignKeyName1PrincipalConventions2=new CEntityForeignKeyName1PrincipalConventions("PRINCIPAL 222",new CEntityForeignKeyName1DependentConventions[]{EntityForeignKeyName1DependentConventions21,EntityForeignKeyName1DependentConventions22});

			Context.EntitiesForeignKeyName1PrincipalConventions.Add(EntityForeignKeyName1PrincipalConventions1);
			Context.EntitiesForeignKeyName1PrincipalConventions.Add(EntityForeignKeyName1PrincipalConventions2);

			CEntityForeignKeyName2DependentConventions			EntityForeignKeyName2DependentConventions11=new CEntityForeignKeyName2DependentConventions("DEPENDENT 111");
			CEntityForeignKeyName2DependentConventions			EntityForeignKeyName2DependentConventions12=new CEntityForeignKeyName2DependentConventions("DEPENDENT 222");
			CEntityForeignKeyName2DependentConventions			EntityForeignKeyName2DependentConventions21=new CEntityForeignKeyName2DependentConventions("DEPENDENT 333");
			CEntityForeignKeyName2DependentConventions			EntityForeignKeyName2DependentConventions22=new CEntityForeignKeyName2DependentConventions("DEPENDENT 444");

			CEntityForeignKeyName2PrincipalConventions			EntityForeignKeyName2PrincipalConventions1=new CEntityForeignKeyName2PrincipalConventions("PRINCIPAL 111",new CEntityForeignKeyName2DependentConventions[]{EntityForeignKeyName2DependentConventions11,EntityForeignKeyName2DependentConventions12});
			CEntityForeignKeyName2PrincipalConventions			EntityForeignKeyName2PrincipalConventions2=new CEntityForeignKeyName2PrincipalConventions("PRINCIPAL 222",new CEntityForeignKeyName2DependentConventions[]{EntityForeignKeyName2DependentConventions21,EntityForeignKeyName2DependentConventions22});

			Context.EntitiesForeignKeyName2PrincipalConventions.Add(EntityForeignKeyName2PrincipalConventions1);
			Context.EntitiesForeignKeyName2PrincipalConventions.Add(EntityForeignKeyName2PrincipalConventions2);

			CEntityForeignKeyName3DependentConventions			EntityForeignKeyName3DependentConventions11=new CEntityForeignKeyName3DependentConventions("DEPENDENT 111");
			CEntityForeignKeyName3DependentConventions			EntityForeignKeyName3DependentConventions12=new CEntityForeignKeyName3DependentConventions("DEPENDENT 222");
			CEntityForeignKeyName3DependentConventions			EntityForeignKeyName3DependentConventions21=new CEntityForeignKeyName3DependentConventions("DEPENDENT 333");
			CEntityForeignKeyName3DependentConventions			EntityForeignKeyName3DependentConventions22=new CEntityForeignKeyName3DependentConventions("DEPENDENT 444");

			CEntityForeignKeyName3PrincipalConventions			EntityForeignKeyName3PrincipalConventions1=new CEntityForeignKeyName3PrincipalConventions("PRINCIPAL 111",new CEntityForeignKeyName3DependentConventions[]{EntityForeignKeyName3DependentConventions11,EntityForeignKeyName3DependentConventions12});
			CEntityForeignKeyName3PrincipalConventions			EntityForeignKeyName3PrincipalConventions2=new CEntityForeignKeyName3PrincipalConventions("PRINCIPAL 222",new CEntityForeignKeyName3DependentConventions[]{EntityForeignKeyName3DependentConventions21,EntityForeignKeyName3DependentConventions22});

			Context.EntitiesForeignKeyName3PrincipalConventions.Add(EntityForeignKeyName3PrincipalConventions1);
			Context.EntitiesForeignKeyName3PrincipalConventions.Add(EntityForeignKeyName3PrincipalConventions2);

			CEntityNoForeignKey1DependentConventions			EntityNoForeignKey1DependentConventions11=new CEntityNoForeignKey1DependentConventions("DEPENDENT 111");
			CEntityNoForeignKey1DependentConventions			EntityNoForeignKey1DependentConventions12=new CEntityNoForeignKey1DependentConventions("DEPENDENT 222");
			CEntityNoForeignKey1DependentConventions			EntityNoForeignKey1DependentConventions21=new CEntityNoForeignKey1DependentConventions("DEPENDENT 333");
			CEntityNoForeignKey1DependentConventions			EntityNoForeignKey1DependentConventions22=new CEntityNoForeignKey1DependentConventions("DEPENDENT 444");

			CEntityNoForeignKey1PrincipalConventions			EntityNoForeignKey1PrincipalConventions1=new CEntityNoForeignKey1PrincipalConventions("PRINCIPAL 111",new CEntityNoForeignKey1DependentConventions[]{EntityNoForeignKey1DependentConventions11,EntityNoForeignKey1DependentConventions12});
			CEntityNoForeignKey1PrincipalConventions			EntityNoForeignKey1PrincipalConventions2=new CEntityNoForeignKey1PrincipalConventions("PRINCIPAL 222",new CEntityNoForeignKey1DependentConventions[]{EntityNoForeignKey1DependentConventions21,EntityNoForeignKey1DependentConventions22});

			Context.EntitiesNoForeignKey1PrincipalConventions.Add(EntityNoForeignKey1PrincipalConventions1);
			Context.EntitiesNoForeignKey1PrincipalConventions.Add(EntityNoForeignKey1PrincipalConventions2);

			CEntityNoForeignKey2DependentConventions			EntityNoForeignKey2DependentConventions11=new CEntityNoForeignKey2DependentConventions("DEPENDENT 111");
			CEntityNoForeignKey2DependentConventions			EntityNoForeignKey2DependentConventions12=new CEntityNoForeignKey2DependentConventions("DEPENDENT 222");
			CEntityNoForeignKey2DependentConventions			EntityNoForeignKey2DependentConventions21=new CEntityNoForeignKey2DependentConventions("DEPENDENT 333");
			CEntityNoForeignKey2DependentConventions			EntityNoForeignKey2DependentConventions22=new CEntityNoForeignKey2DependentConventions("DEPENDENT 444");

			CEntityNoForeignKey2PrincipalConventions			EntityNoForeignKey2PrincipalConventions1=new CEntityNoForeignKey2PrincipalConventions("PRINCIPAL 111",new CEntityNoForeignKey2DependentConventions[]{EntityNoForeignKey2DependentConventions11,EntityNoForeignKey2DependentConventions12});
			CEntityNoForeignKey2PrincipalConventions			EntityNoForeignKey2PrincipalConventions2=new CEntityNoForeignKey2PrincipalConventions("PRINCIPAL 222",new CEntityNoForeignKey2DependentConventions[]{EntityNoForeignKey2DependentConventions21,EntityNoForeignKey2DependentConventions22});

			Context.EntitiesNoForeignKey2PrincipalConventions.Add(EntityNoForeignKey2PrincipalConventions1);
			Context.EntitiesNoForeignKey2PrincipalConventions.Add(EntityNoForeignKey2PrincipalConventions2);

			CEntityNoForeignKey3DependentConventions			EntityNoForeignKey3DependentConventions11=new CEntityNoForeignKey3DependentConventions("DEPENDENT 111");
			CEntityNoForeignKey3DependentConventions			EntityNoForeignKey3DependentConventions12=new CEntityNoForeignKey3DependentConventions("DEPENDENT 222");
			CEntityNoForeignKey3DependentConventions			EntityNoForeignKey3DependentConventions21=new CEntityNoForeignKey3DependentConventions("DEPENDENT 333");
			CEntityNoForeignKey3DependentConventions			EntityNoForeignKey3DependentConventions22=new CEntityNoForeignKey3DependentConventions("DEPENDENT 444");

			CEntityNoForeignKey3PrincipalConventions			EntityNoForeignKey3PrincipalConventions1=new CEntityNoForeignKey3PrincipalConventions("PRINCIPAL 111",new CEntityNoForeignKey3DependentConventions[]{EntityNoForeignKey3DependentConventions11,EntityNoForeignKey3DependentConventions12});
			CEntityNoForeignKey3PrincipalConventions			EntityNoForeignKey3PrincipalConventions2=new CEntityNoForeignKey3PrincipalConventions("PRINCIPAL 222",new CEntityNoForeignKey3DependentConventions[]{EntityNoForeignKey3DependentConventions21,EntityNoForeignKey3DependentConventions22});

			Context.EntitiesNoForeignKey3PrincipalConventions.Add(EntityNoForeignKey3PrincipalConventions1);
			Context.EntitiesNoForeignKey3PrincipalConventions.Add(EntityNoForeignKey3PrincipalConventions2);

			CEntityOneToOneDependentDataAnnotations				EntityOneToOneDependentDataAnnotations1=new CEntityOneToOneDependentDataAnnotations("DEPENDENT 111");
			CEntityOneToOneDependentDataAnnotations				EntityOneToOneDependentDataAnnotations2=new CEntityOneToOneDependentDataAnnotations("DEPENDENT 222");

			CEntityOneToOnePrincipalDataAnnotations				EntityOneToOnePrincipalDataAnnotations1=new CEntityOneToOnePrincipalDataAnnotations("PRINCIPAL 111");
			CEntityOneToOnePrincipalDataAnnotations				EntityOneToOnePrincipalDataAnnotations2=new CEntityOneToOnePrincipalDataAnnotations("PRINCIPAL 222");

			EntityOneToOnePrincipalDataAnnotations1.EntityDependent=EntityOneToOneDependentDataAnnotations1;
			EntityOneToOnePrincipalDataAnnotations2.EntityDependent=EntityOneToOneDependentDataAnnotations2;

			Context.EntitiesOneToOnePrincipalDataAnnotations.Add(EntityOneToOnePrincipalDataAnnotations1);
			Context.EntitiesOneToOnePrincipalDataAnnotations.Add(EntityOneToOnePrincipalDataAnnotations2);

			CEntityZeroToOneDependentDataAnnotations			EntityZeroToOneDependentDataAnnotations1=new CEntityZeroToOneDependentDataAnnotations("DEPENDENT 111");
			CEntityZeroToOneDependentDataAnnotations			EntityZeroToOneDependentDataAnnotations2=new CEntityZeroToOneDependentDataAnnotations("DEPENDENT 222");

			CEntityZeroToOnePrincipalDataAnnotations			EntityZeroToOnePrincipalDataAnnotations1=new CEntityZeroToOnePrincipalDataAnnotations("PRINCIPAL 111");
			CEntityZeroToOnePrincipalDataAnnotations			EntityZeroToOnePrincipalDataAnnotations2=new CEntityZeroToOnePrincipalDataAnnotations("PRINCIPAL 222");

			EntityZeroToOnePrincipalDataAnnotations1.EntityDependent=EntityZeroToOneDependentDataAnnotations1;
			EntityZeroToOnePrincipalDataAnnotations2.EntityDependent=EntityZeroToOneDependentDataAnnotations2;

			Context.EntitiesZeroToOnePrincipalDataAnnotations.Add(EntityZeroToOnePrincipalDataAnnotations1);
			Context.EntitiesZeroToOnePrincipalDataAnnotations.Add(EntityZeroToOnePrincipalDataAnnotations2);

			CEntityOneToManyDependentDataAnnotations			EntityOneToManyDependentDataAnnotations11=new CEntityOneToManyDependentDataAnnotations("DEPENDENT 111");
			CEntityOneToManyDependentDataAnnotations			EntityOneToManyDependentDataAnnotations12=new CEntityOneToManyDependentDataAnnotations("DEPENDENT 222");
			CEntityOneToManyDependentDataAnnotations			EntityOneToManyDependentDataAnnotations21=new CEntityOneToManyDependentDataAnnotations("DEPENDENT 333");
			CEntityOneToManyDependentDataAnnotations			EntityOneToManyDependentDataAnnotations22=new CEntityOneToManyDependentDataAnnotations("DEPENDENT 444");

			CEntityOneToManyPrincipalDataAnnotations			EntityOneToManyPrincipalDataAnnotations1=new CEntityOneToManyPrincipalDataAnnotations("PRINCIPAL 111",new CEntityOneToManyDependentDataAnnotations[]{EntityOneToManyDependentDataAnnotations11,EntityOneToManyDependentDataAnnotations12});
			CEntityOneToManyPrincipalDataAnnotations			EntityOneToManyPrincipalDataAnnotations2=new CEntityOneToManyPrincipalDataAnnotations("PRINCIPAL 222",new CEntityOneToManyDependentDataAnnotations[]{EntityOneToManyDependentDataAnnotations21,EntityOneToManyDependentDataAnnotations22});

			Context.EntitiesOneToManyPrincipalDataAnnotations.Add(EntityOneToManyPrincipalDataAnnotations1);
			Context.EntitiesOneToManyPrincipalDataAnnotations.Add(EntityOneToManyPrincipalDataAnnotations2);

			CEntityZeroToManyDependentDataAnnotations			EntityZeroToManyDependentDataAnnotations11=new CEntityZeroToManyDependentDataAnnotations("DEPENDENT 111");
			CEntityZeroToManyDependentDataAnnotations			EntityZeroToManyDependentDataAnnotations12=new CEntityZeroToManyDependentDataAnnotations("DEPENDENT 222");
			CEntityZeroToManyDependentDataAnnotations			EntityZeroToManyDependentDataAnnotations21=new CEntityZeroToManyDependentDataAnnotations("DEPENDENT 333");
			CEntityZeroToManyDependentDataAnnotations			EntityZeroToManyDependentDataAnnotations22=new CEntityZeroToManyDependentDataAnnotations("DEPENDENT 444");

			CEntityZeroToManyPrincipalDataAnnotations			EntityZeroToManyPrincipalDataAnnotations1=new CEntityZeroToManyPrincipalDataAnnotations("PRINCIPAL 111",new CEntityZeroToManyDependentDataAnnotations[]{EntityZeroToManyDependentDataAnnotations11,EntityZeroToManyDependentDataAnnotations12});
			CEntityZeroToManyPrincipalDataAnnotations			EntityZeroToManyPrincipalDataAnnotations2=new CEntityZeroToManyPrincipalDataAnnotations("PRINCIPAL 222",new CEntityZeroToManyDependentDataAnnotations[]{EntityZeroToManyDependentDataAnnotations21,EntityZeroToManyDependentDataAnnotations22});

			Context.EntitiesZeroToManyPrincipalDataAnnotations.Add(EntityZeroToManyPrincipalDataAnnotations1);
			Context.EntitiesZeroToManyPrincipalDataAnnotations.Add(EntityZeroToManyPrincipalDataAnnotations2);

			CEntityAttributeOnNavigationPropertyDependentDataAnnotations	EntityAttributeOnNavigationPropertyDependentDataAnnotations11=new CEntityAttributeOnNavigationPropertyDependentDataAnnotations("DEPENDENT 111");
			CEntityAttributeOnNavigationPropertyDependentDataAnnotations	EntityAttributeOnNavigationPropertyDependentDataAnnotations12=new CEntityAttributeOnNavigationPropertyDependentDataAnnotations("DEPENDENT 222");
			CEntityAttributeOnNavigationPropertyDependentDataAnnotations	EntityAttributeOnNavigationPropertyDependentDataAnnotations21=new CEntityAttributeOnNavigationPropertyDependentDataAnnotations("DEPENDENT 333");
			CEntityAttributeOnNavigationPropertyDependentDataAnnotations	EntityAttributeOnNavigationPropertyDependentDataAnnotations22=new CEntityAttributeOnNavigationPropertyDependentDataAnnotations("DEPENDENT 444");

			CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations	EntityAttributeOnNavigationPropertyPrincipalDataAnnotations1=new CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations("PRINCIPAL 111",new CEntityAttributeOnNavigationPropertyDependentDataAnnotations[]{EntityAttributeOnNavigationPropertyDependentDataAnnotations11,EntityAttributeOnNavigationPropertyDependentDataAnnotations12});
			CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations	EntityAttributeOnNavigationPropertyPrincipalDataAnnotations2=new CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations("PRINCIPAL 222",new CEntityAttributeOnNavigationPropertyDependentDataAnnotations[]{EntityAttributeOnNavigationPropertyDependentDataAnnotations21,EntityAttributeOnNavigationPropertyDependentDataAnnotations22});

			Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Add(EntityAttributeOnNavigationPropertyPrincipalDataAnnotations1);
			Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Add(EntityAttributeOnNavigationPropertyPrincipalDataAnnotations2);

			CEntityAttributeOnForeignKeyDependentDataAnnotations	EntityAttributeOnForeignKeyDependentDataAnnotations11=new CEntityAttributeOnForeignKeyDependentDataAnnotations("DEPENDENT 111");
			CEntityAttributeOnForeignKeyDependentDataAnnotations	EntityAttributeOnForeignKeyDependentDataAnnotations12=new CEntityAttributeOnForeignKeyDependentDataAnnotations("DEPENDENT 222");
			CEntityAttributeOnForeignKeyDependentDataAnnotations	EntityAttributeOnForeignKeyDependentDataAnnotations21=new CEntityAttributeOnForeignKeyDependentDataAnnotations("DEPENDENT 333");
			CEntityAttributeOnForeignKeyDependentDataAnnotations	EntityAttributeOnForeignKeyDependentDataAnnotations22=new CEntityAttributeOnForeignKeyDependentDataAnnotations("DEPENDENT 444");

			CEntityAttributeOnForeignKeyPrincipalDataAnnotations	EntityAttributeOnForeignKeyPrincipalDataAnnotations1=new CEntityAttributeOnForeignKeyPrincipalDataAnnotations("PRINCIPAL 111",new CEntityAttributeOnForeignKeyDependentDataAnnotations[]{EntityAttributeOnForeignKeyDependentDataAnnotations11,EntityAttributeOnForeignKeyDependentDataAnnotations12});
			CEntityAttributeOnForeignKeyPrincipalDataAnnotations	EntityAttributeOnForeignKeyPrincipalDataAnnotations2=new CEntityAttributeOnForeignKeyPrincipalDataAnnotations("PRINCIPAL 222",new CEntityAttributeOnForeignKeyDependentDataAnnotations[]{EntityAttributeOnForeignKeyDependentDataAnnotations21,EntityAttributeOnForeignKeyDependentDataAnnotations22});

			Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Add(EntityAttributeOnForeignKeyPrincipalDataAnnotations1);
			Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Add(EntityAttributeOnForeignKeyPrincipalDataAnnotations2);

			CEntityCompositeForeignKeyDependentDataAnnotations	EntityCompositeForeignKeyDependentDataAnnotations11=new CEntityCompositeForeignKeyDependentDataAnnotations("DEPENDENT 111");
			CEntityCompositeForeignKeyDependentDataAnnotations	EntityCompositeForeignKeyDependentDataAnnotations12=new CEntityCompositeForeignKeyDependentDataAnnotations("DEPENDENT 222");
			CEntityCompositeForeignKeyDependentDataAnnotations	EntityCompositeForeignKeyDependentDataAnnotations21=new CEntityCompositeForeignKeyDependentDataAnnotations("DEPENDENT 333");
			CEntityCompositeForeignKeyDependentDataAnnotations	EntityCompositeForeignKeyDependentDataAnnotations22=new CEntityCompositeForeignKeyDependentDataAnnotations("DEPENDENT 444");

			CEntityCompositeForeignKeyPrincipalDataAnnotations	EntityCompositeForeignKeyPrincipalDataAnnotations1=new CEntityCompositeForeignKeyPrincipalDataAnnotations(1,101,"PRINCIPAL 111",new CEntityCompositeForeignKeyDependentDataAnnotations[]{EntityCompositeForeignKeyDependentDataAnnotations11,EntityCompositeForeignKeyDependentDataAnnotations12});
			CEntityCompositeForeignKeyPrincipalDataAnnotations	EntityCompositeForeignKeyPrincipalDataAnnotations2=new CEntityCompositeForeignKeyPrincipalDataAnnotations(2,102,"PRINCIPAL 222",new CEntityCompositeForeignKeyDependentDataAnnotations[]{EntityCompositeForeignKeyDependentDataAnnotations21,EntityCompositeForeignKeyDependentDataAnnotations22});

			Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Add(EntityCompositeForeignKeyPrincipalDataAnnotations1);
			Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Add(EntityCompositeForeignKeyPrincipalDataAnnotations2);

			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations11Relationship1=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 111 RELATIONSHIP AAA");
			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations12Relationship1=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 222 RELATIONSHIP AAA");
			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations21Relationship1=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 333 RELATIONSHIP AAA");
			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations22Relationship1=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 444 RELATIONSHIP AAA");

			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations11Relationship2=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 111 RELATIONSHIP BBB");
			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations12Relationship2=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 222 RELATIONSHIP BBB");
			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations21Relationship2=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 333 RELATIONSHIP BBB");
			CEntityInversePropertyDependentDataAnnotations		EntityInversePropertyDependentDataAnnotations22Relationship2=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 444 RELATIONSHIP BBB");

			CEntityInversePropertyPrincipalDataAnnotations		EntityInversePropertyPrincipalDataAnnotations1=new CEntityInversePropertyPrincipalDataAnnotations("PRINCIPAL 111",new CEntityInversePropertyDependentDataAnnotations[]{EntityInversePropertyDependentDataAnnotations11Relationship1,EntityInversePropertyDependentDataAnnotations12Relationship1},new CEntityInversePropertyDependentDataAnnotations[]{EntityInversePropertyDependentDataAnnotations11Relationship2,EntityInversePropertyDependentDataAnnotations12Relationship2});
			CEntityInversePropertyPrincipalDataAnnotations		EntityInversePropertyPrincipalDataAnnotations2=new CEntityInversePropertyPrincipalDataAnnotations("PRINCIPAL 222",new CEntityInversePropertyDependentDataAnnotations[]{EntityInversePropertyDependentDataAnnotations21Relationship1,EntityInversePropertyDependentDataAnnotations22Relationship1},new CEntityInversePropertyDependentDataAnnotations[]{EntityInversePropertyDependentDataAnnotations21Relationship2,EntityInversePropertyDependentDataAnnotations22Relationship2});

			Context.EntitiesInversePropertyPrincipalDataAnnotations.Add(EntityInversePropertyPrincipalDataAnnotations1);
			Context.EntitiesInversePropertyPrincipalDataAnnotations.Add(EntityInversePropertyPrincipalDataAnnotations2);

			CEntityOneToOne1DependentFluentAPI					EntityOneToOne1DependentFluentAPI1=new CEntityOneToOne1DependentFluentAPI("DEPENDENT 111");
			CEntityOneToOne1DependentFluentAPI					EntityOneToOne1DependentFluentAPI2=new CEntityOneToOne1DependentFluentAPI("DEPENDENT 222");

			CEntityOneToOne1PrincipalFluentAPI					EntityOneToOne1PrincipalFluentAPI1=new CEntityOneToOne1PrincipalFluentAPI("PRINCIPAL 111");
			CEntityOneToOne1PrincipalFluentAPI					EntityOneToOne1PrincipalFluentAPI2=new CEntityOneToOne1PrincipalFluentAPI("PRINCIPAL 222");

			EntityOneToOne1PrincipalFluentAPI1.EntityDependent=EntityOneToOne1DependentFluentAPI1;
			EntityOneToOne1PrincipalFluentAPI2.EntityDependent=EntityOneToOne1DependentFluentAPI2;

			Context.EntitiesOneToOne1PrincipalFluentAPI.Add(EntityOneToOne1PrincipalFluentAPI1);
			Context.EntitiesOneToOne1PrincipalFluentAPI.Add(EntityOneToOne1PrincipalFluentAPI2);

			CEntityOneToOne2DependentFluentAPI					EntityOneToOne2DependentFluentAPI1=new CEntityOneToOne2DependentFluentAPI("DEPENDENT 111");
			CEntityOneToOne2DependentFluentAPI					EntityOneToOne2DependentFluentAPI2=new CEntityOneToOne2DependentFluentAPI("DEPENDENT 222");

			CEntityOneToOne2PrincipalFluentAPI					EntityOneToOne2PrincipalFluentAPI1=new CEntityOneToOne2PrincipalFluentAPI("PRINCIPAL 111");
			CEntityOneToOne2PrincipalFluentAPI					EntityOneToOne2PrincipalFluentAPI2=new CEntityOneToOne2PrincipalFluentAPI("PRINCIPAL 222");

			EntityOneToOne2PrincipalFluentAPI1.EntityDependent=EntityOneToOne2DependentFluentAPI1;
			EntityOneToOne2PrincipalFluentAPI2.EntityDependent=EntityOneToOne2DependentFluentAPI2;

			Context.EntitiesOneToOne2PrincipalFluentAPI.Add(EntityOneToOne2PrincipalFluentAPI1);
			Context.EntitiesOneToOne2PrincipalFluentAPI.Add(EntityOneToOne2PrincipalFluentAPI2);

			CEntityZeroToOne1DependentFluentAPI					EntityZeroToOne1DependentFluentAPI1=new CEntityZeroToOne1DependentFluentAPI("DEPENDENT 111");
			CEntityZeroToOne1DependentFluentAPI					EntityZeroToOne1DependentFluentAPI2=new CEntityZeroToOne1DependentFluentAPI("DEPENDENT 222");

			CEntityZeroToOne1PrincipalFluentAPI					EntityZeroToOne1PrincipalFluentAPI1=new CEntityZeroToOne1PrincipalFluentAPI("PRINCIPAL 111");
			CEntityZeroToOne1PrincipalFluentAPI					EntityZeroToOne1PrincipalFluentAPI2=new CEntityZeroToOne1PrincipalFluentAPI("PRINCIPAL 222");

			EntityZeroToOne1PrincipalFluentAPI1.EntityDependent=EntityZeroToOne1DependentFluentAPI1;
			EntityZeroToOne1PrincipalFluentAPI2.EntityDependent=EntityZeroToOne1DependentFluentAPI2;

			Context.EntitiesZeroToOne1PrincipalFluentAPI.Add(EntityZeroToOne1PrincipalFluentAPI1);
			Context.EntitiesZeroToOne1PrincipalFluentAPI.Add(EntityZeroToOne1PrincipalFluentAPI2);

			CEntityZeroToOne2DependentFluentAPI					EntityZeroToOne2DependentFluentAPI1=new CEntityZeroToOne2DependentFluentAPI("DEPENDENT 111");
			CEntityZeroToOne2DependentFluentAPI					EntityZeroToOne2DependentFluentAPI2=new CEntityZeroToOne2DependentFluentAPI("DEPENDENT 222");

			CEntityZeroToOne2PrincipalFluentAPI					EntityZeroToOne2PrincipalFluentAPI1=new CEntityZeroToOne2PrincipalFluentAPI("PRINCIPAL 111");
			CEntityZeroToOne2PrincipalFluentAPI					EntityZeroToOne2PrincipalFluentAPI2=new CEntityZeroToOne2PrincipalFluentAPI("PRINCIPAL 222");

			EntityZeroToOne2PrincipalFluentAPI1.EntityDependent=EntityZeroToOne2DependentFluentAPI1;
			EntityZeroToOne2PrincipalFluentAPI2.EntityDependent=EntityZeroToOne2DependentFluentAPI2;

			Context.EntitiesZeroToOne2PrincipalFluentAPI.Add(EntityZeroToOne2PrincipalFluentAPI1);
			Context.EntitiesZeroToOne2PrincipalFluentAPI.Add(EntityZeroToOne2PrincipalFluentAPI2);

			CEntityOneToOneMixedKeys1DependentFluentAPI			EntityOneToOneMixedKeys1DependentFluentAPI1=new CEntityOneToOneMixedKeys1DependentFluentAPI("DEPENDENT 111");
			CEntityOneToOneMixedKeys1DependentFluentAPI			EntityOneToOneMixedKeys1DependentFluentAPI2=new CEntityOneToOneMixedKeys1DependentFluentAPI("DEPENDENT 222");

			CEntityOneToOneMixedKeys1PrincipalFluentAPI			EntityOneToOneMixedKeys1PrincipalFluentAPI1=new CEntityOneToOneMixedKeys1PrincipalFluentAPI("PRINCIPAL 111");
			CEntityOneToOneMixedKeys1PrincipalFluentAPI			EntityOneToOneMixedKeys1PrincipalFluentAPI2=new CEntityOneToOneMixedKeys1PrincipalFluentAPI("PRINCIPAL 222");

			EntityOneToOneMixedKeys1PrincipalFluentAPI1.EntityDependent=EntityOneToOneMixedKeys1DependentFluentAPI1;
			EntityOneToOneMixedKeys1PrincipalFluentAPI2.EntityDependent=EntityOneToOneMixedKeys1DependentFluentAPI2;

			Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Add(EntityOneToOneMixedKeys1PrincipalFluentAPI1);
			Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Add(EntityOneToOneMixedKeys1PrincipalFluentAPI2);

			CEntityOneToOneMixedKeys2DependentFluentAPI			EntityOneToOneMixedKeys2DependentFluentAPI1=new CEntityOneToOneMixedKeys2DependentFluentAPI("DEPENDENT 111");
			CEntityOneToOneMixedKeys2DependentFluentAPI			EntityOneToOneMixedKeys2DependentFluentAPI2=new CEntityOneToOneMixedKeys2DependentFluentAPI("DEPENDENT 222");

			CEntityOneToOneMixedKeys2PrincipalFluentAPI			EntityOneToOneMixedKeys2PrincipalFluentAPI1=new CEntityOneToOneMixedKeys2PrincipalFluentAPI("PRINCIPAL 111");
			CEntityOneToOneMixedKeys2PrincipalFluentAPI			EntityOneToOneMixedKeys2PrincipalFluentAPI2=new CEntityOneToOneMixedKeys2PrincipalFluentAPI("PRINCIPAL 222");

			EntityOneToOneMixedKeys2PrincipalFluentAPI1.EntityDependent=EntityOneToOneMixedKeys2DependentFluentAPI1;
			EntityOneToOneMixedKeys2PrincipalFluentAPI2.EntityDependent=EntityOneToOneMixedKeys2DependentFluentAPI2;

			Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Add(EntityOneToOneMixedKeys2PrincipalFluentAPI1);
			Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Add(EntityOneToOneMixedKeys2PrincipalFluentAPI2);

			CEntityOneToMany1DependentFluentAPI					EntityOneToMany1DependentFluentAPI11=new CEntityOneToMany1DependentFluentAPI("DEPENDENT 111");
			CEntityOneToMany1DependentFluentAPI					EntityOneToMany1DependentFluentAPI12=new CEntityOneToMany1DependentFluentAPI("DEPENDENT 222");
			CEntityOneToMany1DependentFluentAPI					EntityOneToMany1DependentFluentAPI21=new CEntityOneToMany1DependentFluentAPI("DEPENDENT 333");
			CEntityOneToMany1DependentFluentAPI					EntityOneToMany1DependentFluentAPI22=new CEntityOneToMany1DependentFluentAPI("DEPENDENT 444");

			CEntityOneToMany1PrincipalFluentAPI					EntityOneToMany1PrincipalFluentAPI1=new CEntityOneToMany1PrincipalFluentAPI("PRINCIPAL 111",new CEntityOneToMany1DependentFluentAPI[]{EntityOneToMany1DependentFluentAPI11,EntityOneToMany1DependentFluentAPI12});
			CEntityOneToMany1PrincipalFluentAPI					EntityOneToMany1PrincipalFluentAPI2=new CEntityOneToMany1PrincipalFluentAPI("PRINCIPAL 222",new CEntityOneToMany1DependentFluentAPI[]{EntityOneToMany1DependentFluentAPI21,EntityOneToMany1DependentFluentAPI22});

			Context.EntitiesOneToMany1PrincipalFluentAPI.Add(EntityOneToMany1PrincipalFluentAPI1);
			Context.EntitiesOneToMany1PrincipalFluentAPI.Add(EntityOneToMany1PrincipalFluentAPI2);

			CEntityOneToMany2DependentFluentAPI					EntityOneToMany2DependentFluentAPI11=new CEntityOneToMany2DependentFluentAPI("DEPENDENT 111");
			CEntityOneToMany2DependentFluentAPI					EntityOneToMany2DependentFluentAPI12=new CEntityOneToMany2DependentFluentAPI("DEPENDENT 222");
			CEntityOneToMany2DependentFluentAPI					EntityOneToMany2DependentFluentAPI21=new CEntityOneToMany2DependentFluentAPI("DEPENDENT 333");
			CEntityOneToMany2DependentFluentAPI					EntityOneToMany2DependentFluentAPI22=new CEntityOneToMany2DependentFluentAPI("DEPENDENT 444");

			CEntityOneToMany2PrincipalFluentAPI					EntityOneToMany2PrincipalFluentAPI1=new CEntityOneToMany2PrincipalFluentAPI("PRINCIPAL 111",new CEntityOneToMany2DependentFluentAPI[]{EntityOneToMany2DependentFluentAPI11,EntityOneToMany2DependentFluentAPI12});
			CEntityOneToMany2PrincipalFluentAPI					EntityOneToMany2PrincipalFluentAPI2=new CEntityOneToMany2PrincipalFluentAPI("PRINCIPAL 222",new CEntityOneToMany2DependentFluentAPI[]{EntityOneToMany2DependentFluentAPI21,EntityOneToMany2DependentFluentAPI22});

			Context.EntitiesOneToMany2PrincipalFluentAPI.Add(EntityOneToMany2PrincipalFluentAPI1);
			Context.EntitiesOneToMany2PrincipalFluentAPI.Add(EntityOneToMany2PrincipalFluentAPI2);

			CEntityZeroToMany1DependentFluentAPI				EntityZeroToMany1DependentFluentAPI11=new CEntityZeroToMany1DependentFluentAPI("DEPENDENT 111");
			CEntityZeroToMany1DependentFluentAPI				EntityZeroToMany1DependentFluentAPI12=new CEntityZeroToMany1DependentFluentAPI("DEPENDENT 222");
			CEntityZeroToMany1DependentFluentAPI				EntityZeroToMany1DependentFluentAPI21=new CEntityZeroToMany1DependentFluentAPI("DEPENDENT 333");
			CEntityZeroToMany1DependentFluentAPI				EntityZeroToMany1DependentFluentAPI22=new CEntityZeroToMany1DependentFluentAPI("DEPENDENT 444");

			CEntityZeroToMany1PrincipalFluentAPI				EntityZeroToMany1PrincipalFluentAPI1=new CEntityZeroToMany1PrincipalFluentAPI("PRINCIPAL 111",new CEntityZeroToMany1DependentFluentAPI[]{EntityZeroToMany1DependentFluentAPI11,EntityZeroToMany1DependentFluentAPI12});
			CEntityZeroToMany1PrincipalFluentAPI				EntityZeroToMany1PrincipalFluentAPI2=new CEntityZeroToMany1PrincipalFluentAPI("PRINCIPAL 222",new CEntityZeroToMany1DependentFluentAPI[]{EntityZeroToMany1DependentFluentAPI21,EntityZeroToMany1DependentFluentAPI22});

			Context.EntitiesZeroToMany1PrincipalFluentAPI.Add(EntityZeroToMany1PrincipalFluentAPI1);
			Context.EntitiesZeroToMany1PrincipalFluentAPI.Add(EntityZeroToMany1PrincipalFluentAPI2);

			CEntityZeroToMany2DependentFluentAPI				EntityZeroToMany2DependentFluentAPI11=new CEntityZeroToMany2DependentFluentAPI("DEPENDENT 111");
			CEntityZeroToMany2DependentFluentAPI				EntityZeroToMany2DependentFluentAPI12=new CEntityZeroToMany2DependentFluentAPI("DEPENDENT 222");
			CEntityZeroToMany2DependentFluentAPI				EntityZeroToMany2DependentFluentAPI21=new CEntityZeroToMany2DependentFluentAPI("DEPENDENT 333");
			CEntityZeroToMany2DependentFluentAPI				EntityZeroToMany2DependentFluentAPI22=new CEntityZeroToMany2DependentFluentAPI("DEPENDENT 444");

			CEntityZeroToMany2PrincipalFluentAPI				EntityZeroToMany2PrincipalFluentAPI1=new CEntityZeroToMany2PrincipalFluentAPI("PRINCIPAL 111",new CEntityZeroToMany2DependentFluentAPI[]{EntityZeroToMany2DependentFluentAPI11,EntityZeroToMany2DependentFluentAPI12});
			CEntityZeroToMany2PrincipalFluentAPI				EntityZeroToMany2PrincipalFluentAPI2=new CEntityZeroToMany2PrincipalFluentAPI("PRINCIPAL 222",new CEntityZeroToMany2DependentFluentAPI[]{EntityZeroToMany2DependentFluentAPI21,EntityZeroToMany2DependentFluentAPI22});

			Context.EntitiesZeroToMany2PrincipalFluentAPI.Add(EntityZeroToMany2PrincipalFluentAPI1);
			Context.EntitiesZeroToMany2PrincipalFluentAPI.Add(EntityZeroToMany2PrincipalFluentAPI2);

			CEntityManyToMany1MFluentAPI						EntityManyToMany1MFluentAPI1=new CEntityManyToMany1MFluentAPI("ENTITY M - 111");
			CEntityManyToMany1MFluentAPI						EntityManyToMany1MFluentAPI2=new CEntityManyToMany1MFluentAPI("ENTITY M - 222");

			CEntityManyToMany1NFluentAPI						EntityManyToMany1NFluentAPI1=new CEntityManyToMany1NFluentAPI("ENTITY N - 111");
			CEntityManyToMany1NFluentAPI						EntityManyToMany1NFluentAPI2=new CEntityManyToMany1NFluentAPI("ENTITY N - 222");

			CEntityManyToMany1MNFluentAPI						EntityManyToMany1MNFluentAPI11=new CEntityManyToMany1MNFluentAPI("ENTITY MN - 11");
			CEntityManyToMany1MNFluentAPI						EntityManyToMany1MNFluentAPI12=new CEntityManyToMany1MNFluentAPI("ENTITY MN - 12");
			CEntityManyToMany1MNFluentAPI						EntityManyToMany1MNFluentAPI21=new CEntityManyToMany1MNFluentAPI("ENTITY MN - 21");
			CEntityManyToMany1MNFluentAPI						EntityManyToMany1MNFluentAPI22=new CEntityManyToMany1MNFluentAPI("ENTITY MN - 22");

			EntityManyToMany1MNFluentAPI11.EntityM=EntityManyToMany1MFluentAPI1;
			EntityManyToMany1MNFluentAPI11.EntityN=EntityManyToMany1NFluentAPI1;

			EntityManyToMany1MNFluentAPI12.EntityM=EntityManyToMany1MFluentAPI1;
			EntityManyToMany1MNFluentAPI12.EntityN=EntityManyToMany1NFluentAPI2;

			EntityManyToMany1MNFluentAPI21.EntityM=EntityManyToMany1MFluentAPI2;
			EntityManyToMany1MNFluentAPI21.EntityN=EntityManyToMany1NFluentAPI1;

			EntityManyToMany1MNFluentAPI22.EntityM=EntityManyToMany1MFluentAPI2;
			EntityManyToMany1MNFluentAPI22.EntityN=EntityManyToMany1NFluentAPI2;

			Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI11);
			Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI12);
			Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI21);
			Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI22);

			CEntityManyToMany2MFluentAPI						EntityManyToMany2MFluentAPI1=new CEntityManyToMany2MFluentAPI("ENTITY M - 111");
			CEntityManyToMany2MFluentAPI						EntityManyToMany2MFluentAPI2=new CEntityManyToMany2MFluentAPI("ENTITY M - 222");

			CEntityManyToMany2NFluentAPI						EntityManyToMany2NFluentAPI1=new CEntityManyToMany2NFluentAPI("ENTITY N - 111");
			CEntityManyToMany2NFluentAPI						EntityManyToMany2NFluentAPI2=new CEntityManyToMany2NFluentAPI("ENTITY N - 222");

			CEntityManyToMany2MNFluentAPI						EntityManyToMany2MNFluentAPI11=new CEntityManyToMany2MNFluentAPI("ENTITY MN - 11");
			CEntityManyToMany2MNFluentAPI						EntityManyToMany2MNFluentAPI12=new CEntityManyToMany2MNFluentAPI("ENTITY MN - 12");
			CEntityManyToMany2MNFluentAPI						EntityManyToMany2MNFluentAPI21=new CEntityManyToMany2MNFluentAPI("ENTITY MN - 21");
			CEntityManyToMany2MNFluentAPI						EntityManyToMany2MNFluentAPI22=new CEntityManyToMany2MNFluentAPI("ENTITY MN - 22");

			EntityManyToMany2MNFluentAPI11.EntityM=EntityManyToMany2MFluentAPI1;
			EntityManyToMany2MNFluentAPI11.EntityN=EntityManyToMany2NFluentAPI1;

			EntityManyToMany2MNFluentAPI12.EntityM=EntityManyToMany2MFluentAPI1;
			EntityManyToMany2MNFluentAPI12.EntityN=EntityManyToMany2NFluentAPI2;

			EntityManyToMany2MNFluentAPI21.EntityM=EntityManyToMany2MFluentAPI2;
			EntityManyToMany2MNFluentAPI21.EntityN=EntityManyToMany2NFluentAPI1;

			EntityManyToMany2MNFluentAPI22.EntityM=EntityManyToMany2MFluentAPI2;
			EntityManyToMany2MNFluentAPI22.EntityN=EntityManyToMany2NFluentAPI2;

			Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI11);
			Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI12);
			Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI21);
			Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI22);

			CEntityZeroManyToMany1MFluentAPI					EntityZeroManyToMany1MFluentAPI1=new CEntityZeroManyToMany1MFluentAPI("ENTITY M - 111");
			CEntityZeroManyToMany1MFluentAPI					EntityZeroManyToMany1MFluentAPI2=new CEntityZeroManyToMany1MFluentAPI("ENTITY M - 222");

			CEntityZeroManyToMany1NFluentAPI					EntityZeroManyToMany1NFluentAPI1=new CEntityZeroManyToMany1NFluentAPI("ENTITY N - 111");
			CEntityZeroManyToMany1NFluentAPI					EntityZeroManyToMany1NFluentAPI2=new CEntityZeroManyToMany1NFluentAPI("ENTITY N - 222");

			CEntityZeroManyToMany1MNFluentAPI					EntityZeroManyToMany1MNFluentAPI11=new CEntityZeroManyToMany1MNFluentAPI("ENTITY MN - 11");
			CEntityZeroManyToMany1MNFluentAPI					EntityZeroManyToMany1MNFluentAPI12=new CEntityZeroManyToMany1MNFluentAPI("ENTITY MN - 12");
			CEntityZeroManyToMany1MNFluentAPI					EntityZeroManyToMany1MNFluentAPI21=new CEntityZeroManyToMany1MNFluentAPI("ENTITY MN - 21");
			CEntityZeroManyToMany1MNFluentAPI					EntityZeroManyToMany1MNFluentAPI22=new CEntityZeroManyToMany1MNFluentAPI("ENTITY MN - 22");

			EntityZeroManyToMany1MNFluentAPI11.EntityM=EntityZeroManyToMany1MFluentAPI1;
			EntityZeroManyToMany1MNFluentAPI11.EntityN=EntityZeroManyToMany1NFluentAPI1;

			EntityZeroManyToMany1MNFluentAPI12.EntityM=EntityZeroManyToMany1MFluentAPI1;
			EntityZeroManyToMany1MNFluentAPI12.EntityN=EntityZeroManyToMany1NFluentAPI2;

			EntityZeroManyToMany1MNFluentAPI21.EntityM=EntityZeroManyToMany1MFluentAPI2;
			EntityZeroManyToMany1MNFluentAPI21.EntityN=EntityZeroManyToMany1NFluentAPI1;

			EntityZeroManyToMany1MNFluentAPI22.EntityM=EntityZeroManyToMany1MFluentAPI2;
			EntityZeroManyToMany1MNFluentAPI22.EntityN=EntityZeroManyToMany1NFluentAPI2;

			Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI11);
			Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI12);
			Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI21);
			Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI22);

			CEntityZeroManyToMany2MFluentAPI					EntityZeroManyToMany2MFluentAPI1=new CEntityZeroManyToMany2MFluentAPI("ENTITY M - 111");
			CEntityZeroManyToMany2MFluentAPI					EntityZeroManyToMany2MFluentAPI2=new CEntityZeroManyToMany2MFluentAPI("ENTITY M - 222");

			CEntityZeroManyToMany2NFluentAPI					EntityZeroManyToMany2NFluentAPI1=new CEntityZeroManyToMany2NFluentAPI("ENTITY N - 111");
			CEntityZeroManyToMany2NFluentAPI					EntityZeroManyToMany2NFluentAPI2=new CEntityZeroManyToMany2NFluentAPI("ENTITY N - 222");

			CEntityZeroManyToMany2MNFluentAPI					EntityZeroManyToMany2MNFluentAPI11=new CEntityZeroManyToMany2MNFluentAPI("ENTITY MN - 11");
			CEntityZeroManyToMany2MNFluentAPI					EntityZeroManyToMany2MNFluentAPI12=new CEntityZeroManyToMany2MNFluentAPI("ENTITY MN - 12");
			CEntityZeroManyToMany2MNFluentAPI					EntityZeroManyToMany2MNFluentAPI21=new CEntityZeroManyToMany2MNFluentAPI("ENTITY MN - 21");
			CEntityZeroManyToMany2MNFluentAPI					EntityZeroManyToMany2MNFluentAPI22=new CEntityZeroManyToMany2MNFluentAPI("ENTITY MN - 22");

			EntityZeroManyToMany2MNFluentAPI11.EntityM=EntityZeroManyToMany2MFluentAPI1;
			EntityZeroManyToMany2MNFluentAPI11.EntityN=EntityZeroManyToMany2NFluentAPI1;

			EntityZeroManyToMany2MNFluentAPI12.EntityM=EntityZeroManyToMany2MFluentAPI1;
			EntityZeroManyToMany2MNFluentAPI12.EntityN=EntityZeroManyToMany2NFluentAPI2;

			EntityZeroManyToMany2MNFluentAPI21.EntityM=EntityZeroManyToMany2MFluentAPI2;
			EntityZeroManyToMany2MNFluentAPI21.EntityN=EntityZeroManyToMany2NFluentAPI1;

			EntityZeroManyToMany2MNFluentAPI22.EntityM=EntityZeroManyToMany2MFluentAPI2;
			EntityZeroManyToMany2MNFluentAPI22.EntityN=EntityZeroManyToMany2NFluentAPI2;

			Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI11);
			Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI12);
			Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI21);
			Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI22);

			CEntityManyToManyMixedKeys1MFluentAPI				EntityManyToManyMixedKeys1MFluentAPI1=new CEntityManyToManyMixedKeys1MFluentAPI("ENTITY M - 111");
			CEntityManyToManyMixedKeys1MFluentAPI				EntityManyToManyMixedKeys1MFluentAPI2=new CEntityManyToManyMixedKeys1MFluentAPI("ENTITY M - 222");

			CEntityManyToManyMixedKeys1NFluentAPI				EntityManyToManyMixedKeys1NFluentAPI1=new CEntityManyToManyMixedKeys1NFluentAPI("ENTITY N - 111");
			CEntityManyToManyMixedKeys1NFluentAPI				EntityManyToManyMixedKeys1NFluentAPI2=new CEntityManyToManyMixedKeys1NFluentAPI("ENTITY N - 222");

			CEntityManyToManyMixedKeys1MNFluentAPI				EntityManyToManyMixedKeys1MNFluentAPI11=new CEntityManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 11");
			CEntityManyToManyMixedKeys1MNFluentAPI				EntityManyToManyMixedKeys1MNFluentAPI12=new CEntityManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 12");
			CEntityManyToManyMixedKeys1MNFluentAPI				EntityManyToManyMixedKeys1MNFluentAPI21=new CEntityManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 21");
			CEntityManyToManyMixedKeys1MNFluentAPI				EntityManyToManyMixedKeys1MNFluentAPI22=new CEntityManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 22");

			EntityManyToManyMixedKeys1MNFluentAPI11.EntityM=EntityManyToManyMixedKeys1MFluentAPI1;
			EntityManyToManyMixedKeys1MNFluentAPI11.EntityN=EntityManyToManyMixedKeys1NFluentAPI1;

			EntityManyToManyMixedKeys1MNFluentAPI12.EntityM=EntityManyToManyMixedKeys1MFluentAPI1;
			EntityManyToManyMixedKeys1MNFluentAPI12.EntityN=EntityManyToManyMixedKeys1NFluentAPI2;

			EntityManyToManyMixedKeys1MNFluentAPI21.EntityM=EntityManyToManyMixedKeys1MFluentAPI2;
			EntityManyToManyMixedKeys1MNFluentAPI21.EntityN=EntityManyToManyMixedKeys1NFluentAPI1;

			EntityManyToManyMixedKeys1MNFluentAPI22.EntityM=EntityManyToManyMixedKeys1MFluentAPI2;
			EntityManyToManyMixedKeys1MNFluentAPI22.EntityN=EntityManyToManyMixedKeys1NFluentAPI2;

			Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI11);
			Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI12);
			Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI21);
			Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI22);

			CEntityManyToManyMixedKeys2MFluentAPI				EntityManyToManyMixedKeys2MFluentAPI1=new CEntityManyToManyMixedKeys2MFluentAPI("ENTITY M - 111");
			CEntityManyToManyMixedKeys2MFluentAPI				EntityManyToManyMixedKeys2MFluentAPI2=new CEntityManyToManyMixedKeys2MFluentAPI("ENTITY M - 222");

			CEntityManyToManyMixedKeys2NFluentAPI				EntityManyToManyMixedKeys2NFluentAPI1=new CEntityManyToManyMixedKeys2NFluentAPI("ENTITY N - 111");
			CEntityManyToManyMixedKeys2NFluentAPI				EntityManyToManyMixedKeys2NFluentAPI2=new CEntityManyToManyMixedKeys2NFluentAPI("ENTITY N - 222");

			CEntityManyToManyMixedKeys2MNFluentAPI				EntityManyToManyMixedKeys2MNFluentAPI11=new CEntityManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 11");
			CEntityManyToManyMixedKeys2MNFluentAPI				EntityManyToManyMixedKeys2MNFluentAPI12=new CEntityManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 12");
			CEntityManyToManyMixedKeys2MNFluentAPI				EntityManyToManyMixedKeys2MNFluentAPI21=new CEntityManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 21");
			CEntityManyToManyMixedKeys2MNFluentAPI				EntityManyToManyMixedKeys2MNFluentAPI22=new CEntityManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 22");

			EntityManyToManyMixedKeys2MNFluentAPI11.EntityM=EntityManyToManyMixedKeys2MFluentAPI1;
			EntityManyToManyMixedKeys2MNFluentAPI11.EntityN=EntityManyToManyMixedKeys2NFluentAPI1;

			EntityManyToManyMixedKeys2MNFluentAPI12.EntityM=EntityManyToManyMixedKeys2MFluentAPI1;
			EntityManyToManyMixedKeys2MNFluentAPI12.EntityN=EntityManyToManyMixedKeys2NFluentAPI2;

			EntityManyToManyMixedKeys2MNFluentAPI21.EntityM=EntityManyToManyMixedKeys2MFluentAPI2;
			EntityManyToManyMixedKeys2MNFluentAPI21.EntityN=EntityManyToManyMixedKeys2NFluentAPI1;

			EntityManyToManyMixedKeys2MNFluentAPI22.EntityM=EntityManyToManyMixedKeys2MFluentAPI2;
			EntityManyToManyMixedKeys2MNFluentAPI22.EntityN=EntityManyToManyMixedKeys2NFluentAPI2;

			Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI11);
			Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI12);
			Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI21);
			Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI22);

			CEntityAutoManyToMany1MFluentAPI					EntityAutoManyToMany1MFluentAPI1=new CEntityAutoManyToMany1MFluentAPI("ENTITY M - 111");
			CEntityAutoManyToMany1MFluentAPI					EntityAutoManyToMany1MFluentAPI2=new CEntityAutoManyToMany1MFluentAPI("ENTITY M - 222");

			CEntityAutoManyToMany1NFluentAPI					EntityAutoManyToMany1NFluentAPI1=new CEntityAutoManyToMany1NFluentAPI("ENTITY N - 111");
			CEntityAutoManyToMany1NFluentAPI					EntityAutoManyToMany1NFluentAPI2=new CEntityAutoManyToMany1NFluentAPI("ENTITY N - 222");

			CEntityAutoManyToMany1MNFluentAPI					EntityAutoManyToMany1MNFluentAPI11=new CEntityAutoManyToMany1MNFluentAPI("ENTITY MN - 11");
			CEntityAutoManyToMany1MNFluentAPI					EntityAutoManyToMany1MNFluentAPI12=new CEntityAutoManyToMany1MNFluentAPI("ENTITY MN - 12");
			CEntityAutoManyToMany1MNFluentAPI					EntityAutoManyToMany1MNFluentAPI21=new CEntityAutoManyToMany1MNFluentAPI("ENTITY MN - 21");
			CEntityAutoManyToMany1MNFluentAPI					EntityAutoManyToMany1MNFluentAPI22=new CEntityAutoManyToMany1MNFluentAPI("ENTITY MN - 22");

			EntityAutoManyToMany1MNFluentAPI11.EntityM=EntityAutoManyToMany1MFluentAPI1;
			EntityAutoManyToMany1MNFluentAPI11.EntityN=EntityAutoManyToMany1NFluentAPI1;

			EntityAutoManyToMany1MNFluentAPI12.EntityM=EntityAutoManyToMany1MFluentAPI1;
			EntityAutoManyToMany1MNFluentAPI12.EntityN=EntityAutoManyToMany1NFluentAPI2;

			EntityAutoManyToMany1MNFluentAPI21.EntityM=EntityAutoManyToMany1MFluentAPI2;
			EntityAutoManyToMany1MNFluentAPI21.EntityN=EntityAutoManyToMany1NFluentAPI1;

			EntityAutoManyToMany1MNFluentAPI22.EntityM=EntityAutoManyToMany1MFluentAPI2;
			EntityAutoManyToMany1MNFluentAPI22.EntityN=EntityAutoManyToMany1NFluentAPI2;

			Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI11);
			Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI12);
			Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI21);
			Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI22);

			CEntityAutoManyToMany2MFluentAPI					EntityAutoManyToMany2MFluentAPI1=new CEntityAutoManyToMany2MFluentAPI("ENTITY M - 111");
			CEntityAutoManyToMany2MFluentAPI					EntityAutoManyToMany2MFluentAPI2=new CEntityAutoManyToMany2MFluentAPI("ENTITY M - 222");

			CEntityAutoManyToMany2NFluentAPI					EntityAutoManyToMany2NFluentAPI1=new CEntityAutoManyToMany2NFluentAPI("ENTITY N - 111");
			CEntityAutoManyToMany2NFluentAPI					EntityAutoManyToMany2NFluentAPI2=new CEntityAutoManyToMany2NFluentAPI("ENTITY N - 222");

			CEntityAutoManyToMany2MNFluentAPI					EntityAutoManyToMany2MNFluentAPI11=new CEntityAutoManyToMany2MNFluentAPI("ENTITY MN - 11");
			CEntityAutoManyToMany2MNFluentAPI					EntityAutoManyToMany2MNFluentAPI12=new CEntityAutoManyToMany2MNFluentAPI("ENTITY MN - 12");
			CEntityAutoManyToMany2MNFluentAPI					EntityAutoManyToMany2MNFluentAPI21=new CEntityAutoManyToMany2MNFluentAPI("ENTITY MN - 21");
			CEntityAutoManyToMany2MNFluentAPI					EntityAutoManyToMany2MNFluentAPI22=new CEntityAutoManyToMany2MNFluentAPI("ENTITY MN - 22");

			EntityAutoManyToMany2MNFluentAPI11.EntityM=EntityAutoManyToMany2MFluentAPI1;
			EntityAutoManyToMany2MNFluentAPI11.EntityN=EntityAutoManyToMany2NFluentAPI1;

			EntityAutoManyToMany2MNFluentAPI12.EntityM=EntityAutoManyToMany2MFluentAPI1;
			EntityAutoManyToMany2MNFluentAPI12.EntityN=EntityAutoManyToMany2NFluentAPI2;

			EntityAutoManyToMany2MNFluentAPI21.EntityM=EntityAutoManyToMany2MFluentAPI2;
			EntityAutoManyToMany2MNFluentAPI21.EntityN=EntityAutoManyToMany2NFluentAPI1;

			EntityAutoManyToMany2MNFluentAPI22.EntityM=EntityAutoManyToMany2MFluentAPI2;
			EntityAutoManyToMany2MNFluentAPI22.EntityN=EntityAutoManyToMany2NFluentAPI2;

			Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI11);
			Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI12);
			Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI21);
			Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI22);

			CEntityAutoZeroManyToMany1MFluentAPI				EntityAutoZeroManyToMany1MFluentAPI1=new CEntityAutoZeroManyToMany1MFluentAPI("ENTITY M - 111");
			CEntityAutoZeroManyToMany1MFluentAPI				EntityAutoZeroManyToMany1MFluentAPI2=new CEntityAutoZeroManyToMany1MFluentAPI("ENTITY M - 222");

			CEntityAutoZeroManyToMany1NFluentAPI				EntityAutoZeroManyToMany1NFluentAPI1=new CEntityAutoZeroManyToMany1NFluentAPI("ENTITY N - 111");
			CEntityAutoZeroManyToMany1NFluentAPI				EntityAutoZeroManyToMany1NFluentAPI2=new CEntityAutoZeroManyToMany1NFluentAPI("ENTITY N - 222");

			CEntityAutoZeroManyToMany1MNFluentAPI				EntityAutoZeroManyToMany1MNFluentAPI11=new CEntityAutoZeroManyToMany1MNFluentAPI("ENTITY MN - 11");
			CEntityAutoZeroManyToMany1MNFluentAPI				EntityAutoZeroManyToMany1MNFluentAPI12=new CEntityAutoZeroManyToMany1MNFluentAPI("ENTITY MN - 12");
			CEntityAutoZeroManyToMany1MNFluentAPI				EntityAutoZeroManyToMany1MNFluentAPI21=new CEntityAutoZeroManyToMany1MNFluentAPI("ENTITY MN - 21");
			CEntityAutoZeroManyToMany1MNFluentAPI				EntityAutoZeroManyToMany1MNFluentAPI22=new CEntityAutoZeroManyToMany1MNFluentAPI("ENTITY MN - 22");

			EntityAutoZeroManyToMany1MNFluentAPI11.EntityM=EntityAutoZeroManyToMany1MFluentAPI1;
			EntityAutoZeroManyToMany1MNFluentAPI11.EntityN=EntityAutoZeroManyToMany1NFluentAPI1;

			EntityAutoZeroManyToMany1MNFluentAPI12.EntityM=EntityAutoZeroManyToMany1MFluentAPI1;
			EntityAutoZeroManyToMany1MNFluentAPI12.EntityN=EntityAutoZeroManyToMany1NFluentAPI2;

			EntityAutoZeroManyToMany1MNFluentAPI21.EntityM=EntityAutoZeroManyToMany1MFluentAPI2;
			EntityAutoZeroManyToMany1MNFluentAPI21.EntityN=EntityAutoZeroManyToMany1NFluentAPI1;

			EntityAutoZeroManyToMany1MNFluentAPI22.EntityM=EntityAutoZeroManyToMany1MFluentAPI2;
			EntityAutoZeroManyToMany1MNFluentAPI22.EntityN=EntityAutoZeroManyToMany1NFluentAPI2;

			Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI11);
			Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI12);
			Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI21);
			Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI22);

			CEntityAutoZeroManyToMany2MFluentAPI				EntityAutoZeroManyToMany2MFluentAPI1=new CEntityAutoZeroManyToMany2MFluentAPI("ENTITY M - 111");
			CEntityAutoZeroManyToMany2MFluentAPI				EntityAutoZeroManyToMany2MFluentAPI2=new CEntityAutoZeroManyToMany2MFluentAPI("ENTITY M - 222");

			CEntityAutoZeroManyToMany2NFluentAPI				EntityAutoZeroManyToMany2NFluentAPI1=new CEntityAutoZeroManyToMany2NFluentAPI("ENTITY N - 111");
			CEntityAutoZeroManyToMany2NFluentAPI				EntityAutoZeroManyToMany2NFluentAPI2=new CEntityAutoZeroManyToMany2NFluentAPI("ENTITY N - 222");

			CEntityAutoZeroManyToMany2MNFluentAPI				EntityAutoZeroManyToMany2MNFluentAPI11=new CEntityAutoZeroManyToMany2MNFluentAPI("ENTITY MN - 11");
			CEntityAutoZeroManyToMany2MNFluentAPI				EntityAutoZeroManyToMany2MNFluentAPI12=new CEntityAutoZeroManyToMany2MNFluentAPI("ENTITY MN - 12");
			CEntityAutoZeroManyToMany2MNFluentAPI				EntityAutoZeroManyToMany2MNFluentAPI21=new CEntityAutoZeroManyToMany2MNFluentAPI("ENTITY MN - 21");
			CEntityAutoZeroManyToMany2MNFluentAPI				EntityAutoZeroManyToMany2MNFluentAPI22=new CEntityAutoZeroManyToMany2MNFluentAPI("ENTITY MN - 22");

			EntityAutoZeroManyToMany2MNFluentAPI11.EntityM=EntityAutoZeroManyToMany2MFluentAPI1;
			EntityAutoZeroManyToMany2MNFluentAPI11.EntityN=EntityAutoZeroManyToMany2NFluentAPI1;

			EntityAutoZeroManyToMany2MNFluentAPI12.EntityM=EntityAutoZeroManyToMany2MFluentAPI1;
			EntityAutoZeroManyToMany2MNFluentAPI12.EntityN=EntityAutoZeroManyToMany2NFluentAPI2;

			EntityAutoZeroManyToMany2MNFluentAPI21.EntityM=EntityAutoZeroManyToMany2MFluentAPI2;
			EntityAutoZeroManyToMany2MNFluentAPI21.EntityN=EntityAutoZeroManyToMany2NFluentAPI1;

			EntityAutoZeroManyToMany2MNFluentAPI22.EntityM=EntityAutoZeroManyToMany2MFluentAPI2;
			EntityAutoZeroManyToMany2MNFluentAPI22.EntityN=EntityAutoZeroManyToMany2NFluentAPI2;

			Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI11);
			Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI12);
			Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI21);
			Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI22);

			CEntityAutoManyToManyMixedKeys1MFluentAPI			EntityAutoManyToManyMixedKeys1MFluentAPI1=new CEntityAutoManyToManyMixedKeys1MFluentAPI("ENTITY M - 111");
			CEntityAutoManyToManyMixedKeys1MFluentAPI			EntityAutoManyToManyMixedKeys1MFluentAPI2=new CEntityAutoManyToManyMixedKeys1MFluentAPI("ENTITY M - 222");

			CEntityAutoManyToManyMixedKeys1NFluentAPI			EntityAutoManyToManyMixedKeys1NFluentAPI1=new CEntityAutoManyToManyMixedKeys1NFluentAPI("ENTITY N - 111");
			CEntityAutoManyToManyMixedKeys1NFluentAPI			EntityAutoManyToManyMixedKeys1NFluentAPI2=new CEntityAutoManyToManyMixedKeys1NFluentAPI("ENTITY N - 222");

			CEntityAutoManyToManyMixedKeys1MNFluentAPI			EntityAutoManyToManyMixedKeys1MNFluentAPI11=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 11");
			CEntityAutoManyToManyMixedKeys1MNFluentAPI			EntityAutoManyToManyMixedKeys1MNFluentAPI12=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 12");
			CEntityAutoManyToManyMixedKeys1MNFluentAPI			EntityAutoManyToManyMixedKeys1MNFluentAPI21=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 21");
			CEntityAutoManyToManyMixedKeys1MNFluentAPI			EntityAutoManyToManyMixedKeys1MNFluentAPI22=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("ENTITY MN - 22");

			EntityAutoManyToManyMixedKeys1MNFluentAPI11.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI1;
			EntityAutoManyToManyMixedKeys1MNFluentAPI11.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI1;

			EntityAutoManyToManyMixedKeys1MNFluentAPI12.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI1;
			EntityAutoManyToManyMixedKeys1MNFluentAPI12.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI2;

			EntityAutoManyToManyMixedKeys1MNFluentAPI21.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI2;
			EntityAutoManyToManyMixedKeys1MNFluentAPI21.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI1;

			EntityAutoManyToManyMixedKeys1MNFluentAPI22.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI2;
			EntityAutoManyToManyMixedKeys1MNFluentAPI22.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI2;

			Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI11);
			Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI12);
			Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI21);
			Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI22);

			CEntityAutoManyToManyMixedKeys2MFluentAPI			EntityAutoManyToManyMixedKeys2MFluentAPI1=new CEntityAutoManyToManyMixedKeys2MFluentAPI("ENTITY M - 111");
			CEntityAutoManyToManyMixedKeys2MFluentAPI			EntityAutoManyToManyMixedKeys2MFluentAPI2=new CEntityAutoManyToManyMixedKeys2MFluentAPI("ENTITY M - 222");

			CEntityAutoManyToManyMixedKeys2NFluentAPI			EntityAutoManyToManyMixedKeys2NFluentAPI1=new CEntityAutoManyToManyMixedKeys2NFluentAPI("ENTITY N - 111");
			CEntityAutoManyToManyMixedKeys2NFluentAPI			EntityAutoManyToManyMixedKeys2NFluentAPI2=new CEntityAutoManyToManyMixedKeys2NFluentAPI("ENTITY N - 222");

			CEntityAutoManyToManyMixedKeys2MNFluentAPI			EntityAutoManyToManyMixedKeys2MNFluentAPI11=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 11");
			CEntityAutoManyToManyMixedKeys2MNFluentAPI			EntityAutoManyToManyMixedKeys2MNFluentAPI12=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 12");
			CEntityAutoManyToManyMixedKeys2MNFluentAPI			EntityAutoManyToManyMixedKeys2MNFluentAPI21=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 21");
			CEntityAutoManyToManyMixedKeys2MNFluentAPI			EntityAutoManyToManyMixedKeys2MNFluentAPI22=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("ENTITY MN - 22");

			EntityAutoManyToManyMixedKeys2MNFluentAPI11.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI1;
			EntityAutoManyToManyMixedKeys2MNFluentAPI11.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI1;

			EntityAutoManyToManyMixedKeys2MNFluentAPI12.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI1;
			EntityAutoManyToManyMixedKeys2MNFluentAPI12.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI2;

			EntityAutoManyToManyMixedKeys2MNFluentAPI21.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI2;
			EntityAutoManyToManyMixedKeys2MNFluentAPI21.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI1;

			EntityAutoManyToManyMixedKeys2MNFluentAPI22.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI2;
			EntityAutoManyToManyMixedKeys2MNFluentAPI22.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI2;

			Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI11);
			Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI12);
			Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI21);
			Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI22);

			CEntityOnDeleteNoActionNotNullDependentFluentAPI	EntityOnDeleteNoActionNotNullDependentFluentAPI11=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteNoActionNotNullDependentFluentAPI	EntityOnDeleteNoActionNotNullDependentFluentAPI12=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteNoActionNotNullDependentFluentAPI	EntityOnDeleteNoActionNotNullDependentFluentAPI21=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteNoActionNotNullDependentFluentAPI	EntityOnDeleteNoActionNotNullDependentFluentAPI22=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	EntityOnDeleteNoActionNotNullPrincipalFluentAPI1=new CEntityOnDeleteNoActionNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteNoActionNotNullDependentFluentAPI[]{EntityOnDeleteNoActionNotNullDependentFluentAPI11,EntityOnDeleteNoActionNotNullDependentFluentAPI12});
			CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	EntityOnDeleteNoActionNotNullPrincipalFluentAPI2=new CEntityOnDeleteNoActionNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteNoActionNotNullDependentFluentAPI[]{EntityOnDeleteNoActionNotNullDependentFluentAPI21,EntityOnDeleteNoActionNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Add(EntityOnDeleteNoActionNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Add(EntityOnDeleteNoActionNotNullPrincipalFluentAPI2);

			CEntityOnDeleteNoActionNullDependentFluentAPI		EntityOnDeleteNoActionNullDependentFluentAPI11=new CEntityOnDeleteNoActionNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteNoActionNullDependentFluentAPI		EntityOnDeleteNoActionNullDependentFluentAPI12=new CEntityOnDeleteNoActionNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteNoActionNullDependentFluentAPI		EntityOnDeleteNoActionNullDependentFluentAPI21=new CEntityOnDeleteNoActionNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteNoActionNullDependentFluentAPI		EntityOnDeleteNoActionNullDependentFluentAPI22=new CEntityOnDeleteNoActionNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteNoActionNullPrincipalFluentAPI		EntityOnDeleteNoActionNullPrincipalFluentAPI1=new CEntityOnDeleteNoActionNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteNoActionNullDependentFluentAPI[]{EntityOnDeleteNoActionNullDependentFluentAPI11,EntityOnDeleteNoActionNullDependentFluentAPI12});
			CEntityOnDeleteNoActionNullPrincipalFluentAPI		EntityOnDeleteNoActionNullPrincipalFluentAPI2=new CEntityOnDeleteNoActionNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteNoActionNullDependentFluentAPI[]{EntityOnDeleteNoActionNullDependentFluentAPI21,EntityOnDeleteNoActionNullDependentFluentAPI22});

			Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Add(EntityOnDeleteNoActionNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Add(EntityOnDeleteNoActionNullPrincipalFluentAPI2);

			CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	EntityOnDeleteClientNoActionNotNullDependentFluentAPI11=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	EntityOnDeleteClientNoActionNotNullDependentFluentAPI12=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	EntityOnDeleteClientNoActionNotNullDependentFluentAPI21=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	EntityOnDeleteClientNoActionNotNullDependentFluentAPI22=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	EntityOnDeleteClientNoActionNotNullPrincipalFluentAPI1=new CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]{EntityOnDeleteClientNoActionNotNullDependentFluentAPI11,EntityOnDeleteClientNoActionNotNullDependentFluentAPI12});
			CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	EntityOnDeleteClientNoActionNotNullPrincipalFluentAPI2=new CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]{EntityOnDeleteClientNoActionNotNullDependentFluentAPI21,EntityOnDeleteClientNoActionNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Add(EntityOnDeleteClientNoActionNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Add(EntityOnDeleteClientNoActionNotNullPrincipalFluentAPI2);

			CEntityOnDeleteClientNoActionNullDependentFluentAPI	EntityOnDeleteClientNoActionNullDependentFluentAPI11=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteClientNoActionNullDependentFluentAPI	EntityOnDeleteClientNoActionNullDependentFluentAPI12=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteClientNoActionNullDependentFluentAPI	EntityOnDeleteClientNoActionNullDependentFluentAPI21=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteClientNoActionNullDependentFluentAPI	EntityOnDeleteClientNoActionNullDependentFluentAPI22=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	EntityOnDeleteClientNoActionNullPrincipalFluentAPI1=new CEntityOnDeleteClientNoActionNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteClientNoActionNullDependentFluentAPI[]{EntityOnDeleteClientNoActionNullDependentFluentAPI11,EntityOnDeleteClientNoActionNullDependentFluentAPI12});
			CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	EntityOnDeleteClientNoActionNullPrincipalFluentAPI2=new CEntityOnDeleteClientNoActionNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteClientNoActionNullDependentFluentAPI[]{EntityOnDeleteClientNoActionNullDependentFluentAPI21,EntityOnDeleteClientNoActionNullDependentFluentAPI22});

			Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Add(EntityOnDeleteClientNoActionNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Add(EntityOnDeleteClientNoActionNullPrincipalFluentAPI2);

			CEntityOnDeleteRestrictNotNullDependentFluentAPI	EntityOnDeleteRestrictNotNullDependentFluentAPI11=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteRestrictNotNullDependentFluentAPI	EntityOnDeleteRestrictNotNullDependentFluentAPI12=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteRestrictNotNullDependentFluentAPI	EntityOnDeleteRestrictNotNullDependentFluentAPI21=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteRestrictNotNullDependentFluentAPI	EntityOnDeleteRestrictNotNullDependentFluentAPI22=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	EntityOnDeleteRestrictNotNullPrincipalFluentAPI1=new CEntityOnDeleteRestrictNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteRestrictNotNullDependentFluentAPI[]{EntityOnDeleteRestrictNotNullDependentFluentAPI11,EntityOnDeleteRestrictNotNullDependentFluentAPI12});
			CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	EntityOnDeleteRestrictNotNullPrincipalFluentAPI2=new CEntityOnDeleteRestrictNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteRestrictNotNullDependentFluentAPI[]{EntityOnDeleteRestrictNotNullDependentFluentAPI21,EntityOnDeleteRestrictNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Add(EntityOnDeleteRestrictNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Add(EntityOnDeleteRestrictNotNullPrincipalFluentAPI2);

			CEntityOnDeleteRestrictNullDependentFluentAPI		EntityOnDeleteRestrictNullDependentFluentAPI11=new CEntityOnDeleteRestrictNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteRestrictNullDependentFluentAPI		EntityOnDeleteRestrictNullDependentFluentAPI12=new CEntityOnDeleteRestrictNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteRestrictNullDependentFluentAPI		EntityOnDeleteRestrictNullDependentFluentAPI21=new CEntityOnDeleteRestrictNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteRestrictNullDependentFluentAPI		EntityOnDeleteRestrictNullDependentFluentAPI22=new CEntityOnDeleteRestrictNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteRestrictNullPrincipalFluentAPI		EntityOnDeleteRestrictNullPrincipalFluentAPI1=new CEntityOnDeleteRestrictNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteRestrictNullDependentFluentAPI[]{EntityOnDeleteRestrictNullDependentFluentAPI11,EntityOnDeleteRestrictNullDependentFluentAPI12});
			CEntityOnDeleteRestrictNullPrincipalFluentAPI		EntityOnDeleteRestrictNullPrincipalFluentAPI2=new CEntityOnDeleteRestrictNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteRestrictNullDependentFluentAPI[]{EntityOnDeleteRestrictNullDependentFluentAPI21,EntityOnDeleteRestrictNullDependentFluentAPI22});

			Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Add(EntityOnDeleteRestrictNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Add(EntityOnDeleteRestrictNullPrincipalFluentAPI2);

			CEntityOnDeleteSetNullNotNullDependentFluentAPI		EntityOnDeleteSetNullNotNullDependentFluentAPI11=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteSetNullNotNullDependentFluentAPI		EntityOnDeleteSetNullNotNullDependentFluentAPI12=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteSetNullNotNullDependentFluentAPI		EntityOnDeleteSetNullNotNullDependentFluentAPI21=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteSetNullNotNullDependentFluentAPI		EntityOnDeleteSetNullNotNullDependentFluentAPI22=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteSetNullNotNullPrincipalFluentAPI		EntityOnDeleteSetNullNotNullPrincipalFluentAPI1=new CEntityOnDeleteSetNullNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteSetNullNotNullDependentFluentAPI[]{EntityOnDeleteSetNullNotNullDependentFluentAPI11,EntityOnDeleteSetNullNotNullDependentFluentAPI12});
			CEntityOnDeleteSetNullNotNullPrincipalFluentAPI		EntityOnDeleteSetNullNotNullPrincipalFluentAPI2=new CEntityOnDeleteSetNullNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteSetNullNotNullDependentFluentAPI[]{EntityOnDeleteSetNullNotNullDependentFluentAPI21,EntityOnDeleteSetNullNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Add(EntityOnDeleteSetNullNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Add(EntityOnDeleteSetNullNotNullPrincipalFluentAPI2);

			CEntityOnDeleteSetNullNullDependentFluentAPI		EntityOnDeleteSetNullNullDependentFluentAPI11=new CEntityOnDeleteSetNullNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteSetNullNullDependentFluentAPI		EntityOnDeleteSetNullNullDependentFluentAPI12=new CEntityOnDeleteSetNullNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteSetNullNullDependentFluentAPI		EntityOnDeleteSetNullNullDependentFluentAPI21=new CEntityOnDeleteSetNullNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteSetNullNullDependentFluentAPI		EntityOnDeleteSetNullNullDependentFluentAPI22=new CEntityOnDeleteSetNullNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteSetNullNullPrincipalFluentAPI		EntityOnDeleteSetNullNullPrincipalFluentAPI1=new CEntityOnDeleteSetNullNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteSetNullNullDependentFluentAPI[]{EntityOnDeleteSetNullNullDependentFluentAPI11,EntityOnDeleteSetNullNullDependentFluentAPI12});
			CEntityOnDeleteSetNullNullPrincipalFluentAPI		EntityOnDeleteSetNullNullPrincipalFluentAPI2=new CEntityOnDeleteSetNullNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteSetNullNullDependentFluentAPI[]{EntityOnDeleteSetNullNullDependentFluentAPI21,EntityOnDeleteSetNullNullDependentFluentAPI22});

			Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Add(EntityOnDeleteSetNullNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Add(EntityOnDeleteSetNullNullPrincipalFluentAPI2);

			CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	EntityOnDeleteClientSetNullNotNullDependentFluentAPI11=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	EntityOnDeleteClientSetNullNotNullDependentFluentAPI12=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	EntityOnDeleteClientSetNullNotNullDependentFluentAPI21=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	EntityOnDeleteClientSetNullNotNullDependentFluentAPI22=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	EntityOnDeleteClientSetNullNotNullPrincipalFluentAPI1=new CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]{EntityOnDeleteClientSetNullNotNullDependentFluentAPI11,EntityOnDeleteClientSetNullNotNullDependentFluentAPI12});
			CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	EntityOnDeleteClientSetNullNotNullPrincipalFluentAPI2=new CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]{EntityOnDeleteClientSetNullNotNullDependentFluentAPI21,EntityOnDeleteClientSetNullNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Add(EntityOnDeleteClientSetNullNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Add(EntityOnDeleteClientSetNullNotNullPrincipalFluentAPI2);

			CEntityOnDeleteClientSetNullNullDependentFluentAPI	EntityOnDeleteClientSetNullNullDependentFluentAPI11=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteClientSetNullNullDependentFluentAPI	EntityOnDeleteClientSetNullNullDependentFluentAPI12=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteClientSetNullNullDependentFluentAPI	EntityOnDeleteClientSetNullNullDependentFluentAPI21=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteClientSetNullNullDependentFluentAPI	EntityOnDeleteClientSetNullNullDependentFluentAPI22=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	EntityOnDeleteClientSetNullNullPrincipalFluentAPI1=new CEntityOnDeleteClientSetNullNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteClientSetNullNullDependentFluentAPI[]{EntityOnDeleteClientSetNullNullDependentFluentAPI11,EntityOnDeleteClientSetNullNullDependentFluentAPI12});
			CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	EntityOnDeleteClientSetNullNullPrincipalFluentAPI2=new CEntityOnDeleteClientSetNullNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteClientSetNullNullDependentFluentAPI[]{EntityOnDeleteClientSetNullNullDependentFluentAPI21,EntityOnDeleteClientSetNullNullDependentFluentAPI22});

			Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Add(EntityOnDeleteClientSetNullNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Add(EntityOnDeleteClientSetNullNullPrincipalFluentAPI2);

			CEntityOnDeleteCascadeNotNullDependentFluentAPI		EntityOnDeleteCascadeNotNullDependentFluentAPI11=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteCascadeNotNullDependentFluentAPI		EntityOnDeleteCascadeNotNullDependentFluentAPI12=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteCascadeNotNullDependentFluentAPI		EntityOnDeleteCascadeNotNullDependentFluentAPI21=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteCascadeNotNullDependentFluentAPI		EntityOnDeleteCascadeNotNullDependentFluentAPI22=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteCascadeNotNullPrincipalFluentAPI		EntityOnDeleteCascadeNotNullPrincipalFluentAPI1=new CEntityOnDeleteCascadeNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteCascadeNotNullDependentFluentAPI[]{EntityOnDeleteCascadeNotNullDependentFluentAPI11,EntityOnDeleteCascadeNotNullDependentFluentAPI12});
			CEntityOnDeleteCascadeNotNullPrincipalFluentAPI		EntityOnDeleteCascadeNotNullPrincipalFluentAPI2=new CEntityOnDeleteCascadeNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteCascadeNotNullDependentFluentAPI[]{EntityOnDeleteCascadeNotNullDependentFluentAPI21,EntityOnDeleteCascadeNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Add(EntityOnDeleteCascadeNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Add(EntityOnDeleteCascadeNotNullPrincipalFluentAPI2);

			CEntityOnDeleteCascadeNullDependentFluentAPI		EntityOnDeleteCascadeNullDependentFluentAPI11=new CEntityOnDeleteCascadeNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteCascadeNullDependentFluentAPI		EntityOnDeleteCascadeNullDependentFluentAPI12=new CEntityOnDeleteCascadeNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteCascadeNullDependentFluentAPI		EntityOnDeleteCascadeNullDependentFluentAPI21=new CEntityOnDeleteCascadeNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteCascadeNullDependentFluentAPI		EntityOnDeleteCascadeNullDependentFluentAPI22=new CEntityOnDeleteCascadeNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteCascadeNullPrincipalFluentAPI		EntityOnDeleteCascadeNullPrincipalFluentAPI1=new CEntityOnDeleteCascadeNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteCascadeNullDependentFluentAPI[]{EntityOnDeleteCascadeNullDependentFluentAPI11,EntityOnDeleteCascadeNullDependentFluentAPI12});
			CEntityOnDeleteCascadeNullPrincipalFluentAPI		EntityOnDeleteCascadeNullPrincipalFluentAPI2=new CEntityOnDeleteCascadeNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteCascadeNullDependentFluentAPI[]{EntityOnDeleteCascadeNullDependentFluentAPI21,EntityOnDeleteCascadeNullDependentFluentAPI22});

			Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Add(EntityOnDeleteCascadeNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Add(EntityOnDeleteCascadeNullPrincipalFluentAPI2);

			CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	EntityOnDeleteClientCascadeNotNullDependentFluentAPI11=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	EntityOnDeleteClientCascadeNotNullDependentFluentAPI12=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	EntityOnDeleteClientCascadeNotNullDependentFluentAPI21=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	EntityOnDeleteClientCascadeNotNullDependentFluentAPI22=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	EntityOnDeleteClientCascadeNotNullPrincipalFluentAPI1=new CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]{EntityOnDeleteClientCascadeNotNullDependentFluentAPI11,EntityOnDeleteClientCascadeNotNullDependentFluentAPI12});
			CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	EntityOnDeleteClientCascadeNotNullPrincipalFluentAPI2=new CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]{EntityOnDeleteClientCascadeNotNullDependentFluentAPI21,EntityOnDeleteClientCascadeNotNullDependentFluentAPI22});

			Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Add(EntityOnDeleteClientCascadeNotNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Add(EntityOnDeleteClientCascadeNotNullPrincipalFluentAPI2);

			CEntityOnDeleteClientCascadeNullDependentFluentAPI	EntityOnDeleteClientCascadeNullDependentFluentAPI11=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("DEPENDENT 111");
			CEntityOnDeleteClientCascadeNullDependentFluentAPI	EntityOnDeleteClientCascadeNullDependentFluentAPI12=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("DEPENDENT 222");
			CEntityOnDeleteClientCascadeNullDependentFluentAPI	EntityOnDeleteClientCascadeNullDependentFluentAPI21=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("DEPENDENT 333");
			CEntityOnDeleteClientCascadeNullDependentFluentAPI	EntityOnDeleteClientCascadeNullDependentFluentAPI22=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("DEPENDENT 444");

			CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	EntityOnDeleteClientCascadeNullPrincipalFluentAPI1=new CEntityOnDeleteClientCascadeNullPrincipalFluentAPI("PRINCIPAL 111",new CEntityOnDeleteClientCascadeNullDependentFluentAPI[]{EntityOnDeleteClientCascadeNullDependentFluentAPI11,EntityOnDeleteClientCascadeNullDependentFluentAPI12});
			CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	EntityOnDeleteClientCascadeNullPrincipalFluentAPI2=new CEntityOnDeleteClientCascadeNullPrincipalFluentAPI("PRINCIPAL 222",new CEntityOnDeleteClientCascadeNullDependentFluentAPI[]{EntityOnDeleteClientCascadeNullDependentFluentAPI21,EntityOnDeleteClientCascadeNullDependentFluentAPI22});

			Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Add(EntityOnDeleteClientCascadeNullPrincipalFluentAPI1);
			Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Add(EntityOnDeleteClientCascadeNullPrincipalFluentAPI2);

			CEntityRequiredTrueDependentFluentAPI				EntityRequiredTrueDependentFluentAPI11=new CEntityRequiredTrueDependentFluentAPI("DEPENDENT 111");
			CEntityRequiredTrueDependentFluentAPI				EntityRequiredTrueDependentFluentAPI12=new CEntityRequiredTrueDependentFluentAPI("DEPENDENT 222");
			CEntityRequiredTrueDependentFluentAPI				EntityRequiredTrueDependentFluentAPI21=new CEntityRequiredTrueDependentFluentAPI("DEPENDENT 333");
			CEntityRequiredTrueDependentFluentAPI				EntityRequiredTrueDependentFluentAPI22=new CEntityRequiredTrueDependentFluentAPI("DEPENDENT 444");

			CEntityRequiredTruePrincipalFluentAPI				EntityRequiredTruePrincipalFluentAPI1=new CEntityRequiredTruePrincipalFluentAPI("PRINCIPAL 111",new CEntityRequiredTrueDependentFluentAPI[]{EntityRequiredTrueDependentFluentAPI11,EntityRequiredTrueDependentFluentAPI12});
			CEntityRequiredTruePrincipalFluentAPI				EntityRequiredTruePrincipalFluentAPI2=new CEntityRequiredTruePrincipalFluentAPI("PRINCIPAL 222",new CEntityRequiredTrueDependentFluentAPI[]{EntityRequiredTrueDependentFluentAPI21,EntityRequiredTrueDependentFluentAPI22});

			Context.EntitiesRequiredTruePrincipalFluentAPI.Add(EntityRequiredTruePrincipalFluentAPI1);
			Context.EntitiesRequiredTruePrincipalFluentAPI.Add(EntityRequiredTruePrincipalFluentAPI2);

			CEntityRequiredFalseDependentFluentAPI				EntityRequiredFalseDependentFluentAPI11=new CEntityRequiredFalseDependentFluentAPI("DEPENDENT 111");
			CEntityRequiredFalseDependentFluentAPI				EntityRequiredFalseDependentFluentAPI12=new CEntityRequiredFalseDependentFluentAPI("DEPENDENT 222");
			CEntityRequiredFalseDependentFluentAPI				EntityRequiredFalseDependentFluentAPI21=new CEntityRequiredFalseDependentFluentAPI("DEPENDENT 333");
			CEntityRequiredFalseDependentFluentAPI				EntityRequiredFalseDependentFluentAPI22=new CEntityRequiredFalseDependentFluentAPI("DEPENDENT 444");

			CEntityRequiredFalsePrincipalFluentAPI				EntityRequiredFalsePrincipalFluentAPI1=new CEntityRequiredFalsePrincipalFluentAPI("PRINCIPAL 111",new CEntityRequiredFalseDependentFluentAPI[]{EntityRequiredFalseDependentFluentAPI11,EntityRequiredFalseDependentFluentAPI12});
			CEntityRequiredFalsePrincipalFluentAPI				EntityRequiredFalsePrincipalFluentAPI2=new CEntityRequiredFalsePrincipalFluentAPI("PRINCIPAL 222",new CEntityRequiredFalseDependentFluentAPI[]{EntityRequiredFalseDependentFluentAPI21,EntityRequiredFalseDependentFluentAPI22});

			Context.EntitiesRequiredFalsePrincipalFluentAPI.Add(EntityRequiredFalsePrincipalFluentAPI1);
			Context.EntitiesRequiredFalsePrincipalFluentAPI.Add(EntityRequiredFalsePrincipalFluentAPI2);

			CEntityHasAlternateKeyFluentAPI						EntityHasAlternateKeyFluentAPI1=new CEntityHasAlternateKeyFluentAPI("VALUE 111","KEY 1");
			CEntityHasAlternateKeyFluentAPI						EntityHasAlternateKeyFluentAPI2=new CEntityHasAlternateKeyFluentAPI("VALUE 222","KEY 2");

			Context.EntitiesHasAlternateKeyFluentAPI.Add(EntityHasAlternateKeyFluentAPI1);
			Context.EntitiesHasAlternateKeyFluentAPI.Add(EntityHasAlternateKeyFluentAPI2);

			CEntityHasAlternateKeyCompositeFluentAPI			EntityHasAlternateKeyCompositeFluentAPI1=new CEntityHasAlternateKeyCompositeFluentAPI("VALUE 111","KEY 1","KEY A");
			CEntityHasAlternateKeyCompositeFluentAPI			EntityHasAlternateKeyCompositeFluentAPI2=new CEntityHasAlternateKeyCompositeFluentAPI("VALUE 222","KEY 2","KEY B");

			Context.EntitiesHasAlternateKeyCompositeFluentAPI.Add(EntityHasAlternateKeyCompositeFluentAPI1);
			Context.EntitiesHasAlternateKeyCompositeFluentAPI.Add(EntityHasAlternateKeyCompositeFluentAPI2);

			CEntityHasPrincipalKeyDependentFluentAPI			EntityHasPrincipalKeyDependentFluentAPI11=new CEntityHasPrincipalKeyDependentFluentAPI("DEPENDENT 111","KEY 1");
			CEntityHasPrincipalKeyDependentFluentAPI			EntityHasPrincipalKeyDependentFluentAPI12=new CEntityHasPrincipalKeyDependentFluentAPI("DEPENDENT 222","KEY 1");
			CEntityHasPrincipalKeyDependentFluentAPI			EntityHasPrincipalKeyDependentFluentAPI21=new CEntityHasPrincipalKeyDependentFluentAPI("DEPENDENT 333","KEY 2");
			CEntityHasPrincipalKeyDependentFluentAPI			EntityHasPrincipalKeyDependentFluentAPI22=new CEntityHasPrincipalKeyDependentFluentAPI("DEPENDENT 444","KEY 2");

			CEntityHasPrincipalKeyPrincipalFluentAPI			EntityHasPrincipalKeyPrincipalFluentAPI1=new CEntityHasPrincipalKeyPrincipalFluentAPI("PRINCIPAL 111","KEY 1");
			CEntityHasPrincipalKeyPrincipalFluentAPI			EntityHasPrincipalKeyPrincipalFluentAPI2=new CEntityHasPrincipalKeyPrincipalFluentAPI("PRINCIPAL 222","KEY 2");

			Context.EntitiesHasPrincipalKeyDependentFluentAPI.Add(EntityHasPrincipalKeyDependentFluentAPI11);
			Context.EntitiesHasPrincipalKeyDependentFluentAPI.Add(EntityHasPrincipalKeyDependentFluentAPI12);
			Context.EntitiesHasPrincipalKeyDependentFluentAPI.Add(EntityHasPrincipalKeyDependentFluentAPI21);
			Context.EntitiesHasPrincipalKeyDependentFluentAPI.Add(EntityHasPrincipalKeyDependentFluentAPI22);

			Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Add(EntityHasPrincipalKeyPrincipalFluentAPI1);
			Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Add(EntityHasPrincipalKeyPrincipalFluentAPI2);

			CEntityHasPrincipalKeyCompositeDependentFluentAPI	EntityHasPrincipalKeyCompositeDependentFluentAPI11=new CEntityHasPrincipalKeyCompositeDependentFluentAPI("DEPENDENT 111","KEY AAA 1","KEY BBB 1");
			CEntityHasPrincipalKeyCompositeDependentFluentAPI	EntityHasPrincipalKeyCompositeDependentFluentAPI12=new CEntityHasPrincipalKeyCompositeDependentFluentAPI("DEPENDENT 222","KEY AAA 1","KEY BBB 1");
			CEntityHasPrincipalKeyCompositeDependentFluentAPI	EntityHasPrincipalKeyCompositeDependentFluentAPI21=new CEntityHasPrincipalKeyCompositeDependentFluentAPI("DEPENDENT 333","KEY AAA 2","KEY BBB 2");
			CEntityHasPrincipalKeyCompositeDependentFluentAPI	EntityHasPrincipalKeyCompositeDependentFluentAPI22=new CEntityHasPrincipalKeyCompositeDependentFluentAPI("DEPENDENT 444","KEY AAA 2","KEY BBB 2");

			CEntityHasPrincipalKeyCompositePrincipalFluentAPI	EntityHasPrincipalKeyCompositePrincipalFluentAPI1=new CEntityHasPrincipalKeyCompositePrincipalFluentAPI("PRINCIPAL 111","KEY AAA 1","KEY BBB 1");
			CEntityHasPrincipalKeyCompositePrincipalFluentAPI	EntityHasPrincipalKeyCompositePrincipalFluentAPI2=new CEntityHasPrincipalKeyCompositePrincipalFluentAPI("PRINCIPAL 222","KEY AAA 2","KEY BBB 2");

			Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Add(EntityHasPrincipalKeyCompositeDependentFluentAPI11);
			Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Add(EntityHasPrincipalKeyCompositeDependentFluentAPI12);
			Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Add(EntityHasPrincipalKeyCompositeDependentFluentAPI21);
			Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Add(EntityHasPrincipalKeyCompositeDependentFluentAPI22);

			Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Add(EntityHasPrincipalKeyCompositePrincipalFluentAPI1);
			Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Add(EntityHasPrincipalKeyCompositePrincipalFluentAPI2);

			CEntityHasConstraintNameDependentFluentAPI			EntityHasConstraintNameDependentFluentAPI11=new CEntityHasConstraintNameDependentFluentAPI("DEPENDENT 111");
			CEntityHasConstraintNameDependentFluentAPI			EntityHasConstraintNameDependentFluentAPI12=new CEntityHasConstraintNameDependentFluentAPI("DEPENDENT 222");
			CEntityHasConstraintNameDependentFluentAPI			EntityHasConstraintNameDependentFluentAPI21=new CEntityHasConstraintNameDependentFluentAPI("DEPENDENT 333");
			CEntityHasConstraintNameDependentFluentAPI			EntityHasConstraintNameDependentFluentAPI22=new CEntityHasConstraintNameDependentFluentAPI("DEPENDENT 444");

			CEntityHasConstraintNamePrincipalFluentAPI			EntityHasConstraintNamePrincipalFluentAPI1=new CEntityHasConstraintNamePrincipalFluentAPI("PRINCIPAL 111",new CEntityHasConstraintNameDependentFluentAPI[]{EntityHasConstraintNameDependentFluentAPI11,EntityHasConstraintNameDependentFluentAPI12});
			CEntityHasConstraintNamePrincipalFluentAPI			EntityHasConstraintNamePrincipalFluentAPI2=new CEntityHasConstraintNamePrincipalFluentAPI("PRINCIPAL 222",new CEntityHasConstraintNameDependentFluentAPI[]{EntityHasConstraintNameDependentFluentAPI21,EntityHasConstraintNameDependentFluentAPI22});

			Context.EntitiesHasConstraintNamePrincipalFluentAPI.Add(EntityHasConstraintNamePrincipalFluentAPI1);
			Context.EntitiesHasConstraintNamePrincipalFluentAPI.Add(EntityHasConstraintNamePrincipalFluentAPI2);

			COwnedTypeDataAnnotations							OneTableOwnedTypeDataAnnotations1=new COwnedTypeDataAnnotations(111,"111 DATA ANNOTATIONS","111 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							OneTableOwnedTypeDataAnnotationsRequired1=new COwnedTypeDataAnnotations(222,"222 DATA ANNOTATIONS","222 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							OneTableOwnedTypeDataAnnotations2=new COwnedTypeDataAnnotations(333,"333 DATA ANNOTATIONS","333 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							OneTableOwnedTypeDataAnnotationsRequired2=new COwnedTypeDataAnnotations(444,"444 DATA ANNOTATIONS","444 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							OneTableOwnedTypeDataAnnotations3=null;
			COwnedTypeDataAnnotations							OneTableOwnedTypeDataAnnotationsRequired3=new COwnedTypeDataAnnotations(666,null,"666 DATA ANNOTATIONS REQUIRED");

			COwnedTypeFluentAPI									OneTableOwnedTypeFluentAPI1=new COwnedTypeFluentAPI(111,"111 FLUENT API","111 FLUENT API REQUIRED");
			COwnedTypeFluentAPI									OneTableOwnedTypeFluentAPI2=new COwnedTypeFluentAPI(222,"222 FLUENT API","222 FLUENT API REQUIRED");
			COwnedTypeFluentAPI									OneTableOwnedTypeFluentAPI3=new COwnedTypeFluentAPI(333,null,"333 FLUENT API REQUIRED");

			COwnedTypeDataAnnotations							NestedOwnedTypeDataAnnotations1=new COwnedTypeDataAnnotations(111,"111 NESTED DATA ANNOTATIONS","111 NESTED DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							NestedOwnedTypeDataAnnotationsRequired1=new COwnedTypeDataAnnotations(222,"222 NESTED DATA ANNOTATIONS","222 NESTED DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							NestedOwnedTypeDataAnnotations2=new COwnedTypeDataAnnotations(333,"333 NESTED DATA ANNOTATIONS","333 NESTED DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							NestedOwnedTypeDataAnnotationsRequired2=new COwnedTypeDataAnnotations(444,"444 NESTED DATA ANNOTATIONS","444 NESTED DATA ANNOTATIONS REQUIRED");

			CNestedOwnedType									NestedOwnedType1=new CNestedOwnedType(111,"NESTED 111",NestedOwnedTypeDataAnnotations1,NestedOwnedTypeDataAnnotationsRequired1);
			CNestedOwnedType									NestedOwnedType2=new CNestedOwnedType(222,"NESTED 222",NestedOwnedTypeDataAnnotations2,NestedOwnedTypeDataAnnotationsRequired2);
			CNestedOwnedType									NestedOwnedType3=null;

			CEntityOwnedTypeInOneTable							EntityOwnedTypeInOneTable1=new CEntityOwnedTypeInOneTable("ENTITY 1",OneTableOwnedTypeDataAnnotations1,OneTableOwnedTypeDataAnnotationsRequired1,OneTableOwnedTypeFluentAPI1,NestedOwnedType1);
			CEntityOwnedTypeInOneTable							EntityOwnedTypeInOneTable2=new CEntityOwnedTypeInOneTable("ENTITY 2",OneTableOwnedTypeDataAnnotations2,OneTableOwnedTypeDataAnnotationsRequired2,OneTableOwnedTypeFluentAPI2,NestedOwnedType2);
			CEntityOwnedTypeInOneTable							EntityOwnedTypeInOneTable3=new CEntityOwnedTypeInOneTable("ENTITY 3",OneTableOwnedTypeDataAnnotations3,OneTableOwnedTypeDataAnnotationsRequired3,OneTableOwnedTypeFluentAPI3,NestedOwnedType3);

			Context.EntitiesOwnedTypeInOneTable.Add(EntityOwnedTypeInOneTable1);
			Context.EntitiesOwnedTypeInOneTable.Add(EntityOwnedTypeInOneTable2);
			Context.EntitiesOwnedTypeInOneTable.Add(EntityOwnedTypeInOneTable3);

			COwnedTypeDataAnnotations							MultiTablesOwnedTypeDataAnnotations1=new COwnedTypeDataAnnotations(111,"111 DATA ANNOTATIONS","111 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							MultiTablesOwnedTypeDataAnnotationsRequired1=new COwnedTypeDataAnnotations(222,"222 DATA ANNOTATIONS","222 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							MultiTablesOwnedTypeDataAnnotations2=new COwnedTypeDataAnnotations(333,"333 DATA ANNOTATIONS","333 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							MultiTablesOwnedTypeDataAnnotationsRequired2=new COwnedTypeDataAnnotations(444,"444 DATA ANNOTATIONS","444 DATA ANNOTATIONS REQUIRED");
			COwnedTypeDataAnnotations							MultiTablesOwnedTypeDataAnnotations3=null;
			COwnedTypeDataAnnotations							MultiTablesOwnedTypeDataAnnotationsRequired3=new COwnedTypeDataAnnotations(666,null,"666 DATA ANNOTATIONS REQUIRED");

			CEntityOwnedTypeInMultiTables						EntityOwnedTypeInMultiTables1=new CEntityOwnedTypeInMultiTables("ENTITY 1",MultiTablesOwnedTypeDataAnnotations1,MultiTablesOwnedTypeDataAnnotationsRequired1);
			CEntityOwnedTypeInMultiTables						EntityOwnedTypeInMultiTables2=new CEntityOwnedTypeInMultiTables("ENTITY 2",MultiTablesOwnedTypeDataAnnotations2,MultiTablesOwnedTypeDataAnnotationsRequired2);
			CEntityOwnedTypeInMultiTables						EntityOwnedTypeInMultiTables3=new CEntityOwnedTypeInMultiTables("ENTITY 3",MultiTablesOwnedTypeDataAnnotations3,MultiTablesOwnedTypeDataAnnotationsRequired3);

			Context.EntitiesOwnedTypeInMultiTables.Add(EntityOwnedTypeInMultiTables1);
			Context.EntitiesOwnedTypeInMultiTables.Add(EntityOwnedTypeInMultiTables2);
			Context.EntitiesOwnedTypeInMultiTables.Add(EntityOwnedTypeInMultiTables3);

			COwnedTypeOne										OwnedTypeOne1=new COwnedTypeOne(111,"ONE STRING 111","ONE STRING REQUIRED 111");
			COwnedTypeOne										OwnedTypeOne2=new COwnedTypeOne(222,"ONE STRING 222","ONE STRING REQUIRED 222");
			COwnedTypeOne										OwnedTypeOne3=new COwnedTypeOne(333,"ONE STRING 333","ONE STRING REQUIRED 333");
			
			COwnedTypeMany										OwnedTypesMany11=new COwnedTypeMany(111,"MANY STRING 11","MANY STRING REQUIRED 11");
			COwnedTypeMany										OwnedTypesMany12=new COwnedTypeMany(222,"MANY STRING 12","MANY STRING REQUIRED 12");
			COwnedTypeMany										OwnedTypesMany21=new COwnedTypeMany(333,"MANY STRING 21","MANY STRING REQUIRED 21");
			COwnedTypeMany										OwnedTypesMany22=new COwnedTypeMany(444,"MANY STRING 22","MANY STRING REQUIRED 22");
			COwnedTypeMany										OwnedTypesMany31=new COwnedTypeMany(555,"MANY STRING 31","MANY STRING REQUIRED 31");
			COwnedTypeMany										OwnedTypesMany32=new COwnedTypeMany(666,"MANY STRING 32","MANY STRING REQUIRED 32");

			CEntityOwnedTypeOneAndMany							EntityOwnedTypeOneAndMany1=new CEntityOwnedTypeOneAndMany("ENTITY 1",OwnedTypeOne1,new List<COwnedTypeMany>(new COwnedTypeMany[]{OwnedTypesMany11,OwnedTypesMany12}));
			CEntityOwnedTypeOneAndMany							EntityOwnedTypeOneAndMany2=new CEntityOwnedTypeOneAndMany("ENTITY 2",OwnedTypeOne2,new List<COwnedTypeMany>(new COwnedTypeMany[]{OwnedTypesMany21,OwnedTypesMany22}));
			CEntityOwnedTypeOneAndMany							EntityOwnedTypeOneAndMany3=new CEntityOwnedTypeOneAndMany("ENTITY 3",OwnedTypeOne3,new List<COwnedTypeMany>(new COwnedTypeMany[]{OwnedTypesMany31,OwnedTypesMany32}));

			Context.EntitiesOwnedTypeOneAndMany.Add(EntityOwnedTypeOneAndMany1);
			Context.EntitiesOwnedTypeOneAndMany.Add(EntityOwnedTypeOneAndMany2);
			Context.EntitiesOwnedTypeOneAndMany.Add(EntityOwnedTypeOneAndMany3);

			CEntityTablePerHierarchyBaseConventions				TablePerHierarchyBaseConventions1=new CEntityTablePerHierarchyBaseConventions("BASE - 111");
			CEntityTablePerHierarchyBaseConventions				TablePerHierarchyBaseConventions2=new CEntityTablePerHierarchyBaseConventions("BASE - 222");
			CEntityTablePerHierarchyDerived1Conventions			TablePerHierarchyDerived1Conventions1=new CEntityTablePerHierarchyDerived1Conventions("DERIVED 1 - BASE 111","DERIVED 1 - DERIVED 1 111","DERIVED 1 - DERIVED WITH SAME NAME - 111","DERIVED 1 - DERIVED IN SHARED COLUMN - 111");
			CEntityTablePerHierarchyDerived1Conventions			TablePerHierarchyDerived1Conventions2=new CEntityTablePerHierarchyDerived1Conventions("DERIVED 1 - BASE 222","DERIVED 1 - DERIVED 1 222","DERIVED 1 - DERIVED WITH SAME NAME - 222","DERIVED 1 - DERIVED IN SHARED COLUMN - 222");
			CEntityTablePerHierarchyDerived2Conventions			TablePerHierarchyDerived2Conventions1=new CEntityTablePerHierarchyDerived2Conventions("DERIVED 2 - BASE 111","DERIVED 2 - DERIVED 2 111","DERIVED 2 - DERIVED WITH SAME NAME - 111","DERIVED 2 - DERIVED IN SHARED COLUMN - 111");
			CEntityTablePerHierarchyDerived2Conventions			TablePerHierarchyDerived2Conventions2=new CEntityTablePerHierarchyDerived2Conventions("DERIVED 2 - BASE 222","DERIVED 2 - DERIVED 2 222","DERIVED 2 - DERIVED WITH SAME NAME - 222","DERIVED 2 - DERIVED IN SHARED COLUMN - 222");

			Context.EntitiesTablePerHierarchyBaseConventions.Add(TablePerHierarchyBaseConventions1);
			Context.EntitiesTablePerHierarchyBaseConventions.Add(TablePerHierarchyBaseConventions2);
			Context.EntitiesTablePerHierarchyDerived1Conventions.Add(TablePerHierarchyDerived1Conventions1);
			Context.EntitiesTablePerHierarchyDerived1Conventions.Add(TablePerHierarchyDerived1Conventions2);
			Context.EntitiesTablePerHierarchyDerived2Conventions.Add(TablePerHierarchyDerived2Conventions1);
			Context.EntitiesTablePerHierarchyDerived2Conventions.Add(TablePerHierarchyDerived2Conventions2);

			CEntityTablePerHierarchyDerived1FluentAPI			TablePerHierarchyDerived1FluentAPI1=new CEntityTablePerHierarchyDerived1FluentAPI("DERIVED 1 - BASE 111","DERIVED 1 - DERIVED 1 111","DERIVED 1 - DERIVED WITH SAME NAME - 111","DERIVED 1 - DERIVED IN SHARED COLUMN - 111");
			CEntityTablePerHierarchyDerived1FluentAPI			TablePerHierarchyDerived1FluentAPI2=new CEntityTablePerHierarchyDerived1FluentAPI("DERIVED 1 - BASE 222","DERIVED 1 - DERIVED 1 222","DERIVED 1 - DERIVED WITH SAME NAME - 222","DERIVED 1 - DERIVED IN SHARED COLUMN - 222");
			CEntityTablePerHierarchyDerived2FluentAPI			TablePerHierarchyDerived2FluentAPI1=new CEntityTablePerHierarchyDerived2FluentAPI("DERIVED 2 - BASE 111","DERIVED 2 - DERIVED 2 111","DERIVED 2 - DERIVED WITH SAME NAME - 111","DERIVED 2 - DERIVED IN SHARED COLUMN - 111");
			CEntityTablePerHierarchyDerived2FluentAPI			TablePerHierarchyDerived2FluentAPI2=new CEntityTablePerHierarchyDerived2FluentAPI("DERIVED 2 - BASE 222","DERIVED 2 - DERIVED 2 222","DERIVED 2 - DERIVED WITH SAME NAME - 222","DERIVED 2 - DERIVED IN SHARED COLUMN - 222");

			Context.EntitiesTablePerHierarchyDerived1FluentAPI.Add(TablePerHierarchyDerived1FluentAPI1);
			Context.EntitiesTablePerHierarchyDerived1FluentAPI.Add(TablePerHierarchyDerived1FluentAPI2);
			Context.EntitiesTablePerHierarchyDerived2FluentAPI.Add(TablePerHierarchyDerived2FluentAPI1);
			Context.EntitiesTablePerHierarchyDerived2FluentAPI.Add(TablePerHierarchyDerived2FluentAPI2);

			CEntityTablePerTypeDerived1FluentAPI				TablePerTypeDerived1FluentAPI1=new CEntityTablePerTypeDerived1FluentAPI("DERIVED 1 - BASE 111","DERIVED 1 - DERIVED 1 111");
			CEntityTablePerTypeDerived1FluentAPI				TablePerTypeDerived1FluentAPI2=new CEntityTablePerTypeDerived1FluentAPI("DERIVED 1 - BASE 222","DERIVED 1 - DERIVED 1 222");
			CEntityTablePerTypeDerived2FluentAPI				TablePerTypeDerived2FluentAPI1=new CEntityTablePerTypeDerived2FluentAPI("DERIVED 2 - BASE 111","DERIVED 2 - DERIVED 2 111");
			CEntityTablePerTypeDerived2FluentAPI				TablePerTypeDerived2FluentAPI2=new CEntityTablePerTypeDerived2FluentAPI("DERIVED 2 - BASE 222","DERIVED 2 - DERIVED 2 222");

			Context.EntitiesTablePerTypeBaseFluentAPI.Add(TablePerTypeDerived1FluentAPI1);
			Context.EntitiesTablePerTypeBaseFluentAPI.Add(TablePerTypeDerived1FluentAPI2);
			Context.EntitiesTablePerTypeBaseFluentAPI.Add(TablePerTypeDerived2FluentAPI1);
			Context.EntitiesTablePerTypeBaseFluentAPI.Add(TablePerTypeDerived2FluentAPI2);

			// !!!!! Kedze PROPERTY 'CEntityTableSplittingDependent1FluentAPI.EntitySharedValue' odkazuje do toho isteho COLUMN ako 'CEntityTableSplittingDependent2FluentAPI.EntitySharedValue' MUSIA mat OBE PROPERTIES ROVNAKU VALUE inak INSERT ZLYHA.
			const string										SHARED_VALUE_1="SHARED - 111";
			const string										SHARED_VALUE_2="SHARED - 222";

			CEntityTableSplittingDependent1FluentAPI			EntityTableSplittingDependent1FluentAPI1=new CEntityTableSplittingDependent1FluentAPI("DEPENDENT 1 - 111",SHARED_VALUE_1);
			CEntityTableSplittingDependent1FluentAPI			EntityTableSplittingDependent1FluentAPI2=new CEntityTableSplittingDependent1FluentAPI("DEPENDENT 1 - 222",SHARED_VALUE_2);

			CEntityTableSplittingDependent2FluentAPI			EntityTableSplittingDependent2FluentAPI1=new CEntityTableSplittingDependent2FluentAPI("DEPENDENT 2 - 111",SHARED_VALUE_1);
			CEntityTableSplittingDependent2FluentAPI			EntityTableSplittingDependent2FluentAPI2=new CEntityTableSplittingDependent2FluentAPI("DEPENDENT 2 - 222",SHARED_VALUE_2);

			CEntityTableSplittingPrincipalFluentAPI				EntityTableSplittingPrincipalFluentAPI1=new CEntityTableSplittingPrincipalFluentAPI("PRINCIPAL - 111");
			CEntityTableSplittingPrincipalFluentAPI				EntityTableSplittingPrincipalFluentAPI2=new CEntityTableSplittingPrincipalFluentAPI("PRINCIPAL - 222");

			EntityTableSplittingPrincipalFluentAPI1.EntityDependent1=EntityTableSplittingDependent1FluentAPI1;
			EntityTableSplittingPrincipalFluentAPI1.EntityDependent2=EntityTableSplittingDependent2FluentAPI1;
			EntityTableSplittingPrincipalFluentAPI2.EntityDependent1=EntityTableSplittingDependent1FluentAPI2;
			EntityTableSplittingPrincipalFluentAPI2.EntityDependent2=EntityTableSplittingDependent2FluentAPI2;

			Context.EntitiesTableSplittingPrincipalFluentAPI.Add(EntityTableSplittingPrincipalFluentAPI1);
			Context.EntitiesTableSplittingPrincipalFluentAPI.Add(EntityTableSplittingPrincipalFluentAPI2);

			const int											PRIMARY_KEY_1=11;
			const int											PRIMARY_KEY_2=12;

			CEntityPropertyBagDependentFluentAPI				EntityPropertyBagDependentFluentAPI11=new CEntityPropertyBagDependentFluentAPI("DEPENDENT 111",PRIMARY_KEY_1);
			CEntityPropertyBagDependentFluentAPI				EntityPropertyBagDependentFluentAPI12=new CEntityPropertyBagDependentFluentAPI("DEPENDENT 222",PRIMARY_KEY_1);
			CEntityPropertyBagDependentFluentAPI				EntityPropertyBagDependentFluentAPI21=new CEntityPropertyBagDependentFluentAPI("DEPENDENT 333",PRIMARY_KEY_2);
			CEntityPropertyBagDependentFluentAPI				EntityPropertyBagDependentFluentAPI22=new CEntityPropertyBagDependentFluentAPI("DEPENDENT 444",PRIMARY_KEY_2);

			Context.EntitiesPropertyBagDependentFluentAPI.Add(EntityPropertyBagDependentFluentAPI11);
			Context.EntitiesPropertyBagDependentFluentAPI.Add(EntityPropertyBagDependentFluentAPI12);
			Context.EntitiesPropertyBagDependentFluentAPI.Add(EntityPropertyBagDependentFluentAPI21);
			Context.EntitiesPropertyBagDependentFluentAPI.Add(EntityPropertyBagDependentFluentAPI22);

			Dictionary<string,object>							MyPropertyBagPrincipal1=CMyPropertyBag.ToPropertyBag(PRIMARY_KEY_1,111,"PRINCIPAL STRING 111");
			Dictionary<string,object>							MyPropertyBagPrincipal2=CMyPropertyBag.ToPropertyBag(PRIMARY_KEY_2,222,"PRINCIPAL STRING 222");

			Context.MyPropertyBagPrincipal.Add(MyPropertyBagPrincipal1);
			Context.MyPropertyBagPrincipal.Add(MyPropertyBagPrincipal2);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintProperty(IProperty Property)
		{
			StoreObjectIdentifier?								ObjectIdentifier=StoreObjectIdentifier.Create(Property.DeclaringEntityType,StoreObjectType.Table);

			CConsoleHelpers.WriteLine($"\tPROPERTY NAME [{Property.Name}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tCOLUMN NAME [{Property.GetColumnName(ObjectIdentifier.Value)}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tCOLUMN TYPE [{Property.GetColumnType()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tNULLABLE [{Property.IsNullable}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS KEY [{Property.IsKey()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS PRIMARY KEY [{Property.IsPrimaryKey()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS FOREIGN KEY [{Property.IsForeignKey()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS SHADOW PROPERTY [{Property.IsShadowProperty()}].",ConsoleColor.Magenta);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintNavigation(INavigation Navigation)
		{
			CConsoleHelpers.WriteLine($"\tNAVIGATION NAME [{Navigation.Name}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS COLLECTION [{Navigation.IsCollection}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS ON DEPENDENT [{Navigation.IsOnDependent}].",ConsoleColor.Magenta);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintKey(IKey Key)
		{
			CConsoleHelpers.WriteLine($"\tKEY NAME [{Key.GetName()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS PRIMARY KEY [{Key.IsPrimaryKey()}].",ConsoleColor.Magenta);

			IUniqueConstraint[]									UniqueConstraints=Key.GetMappedConstraints().ToArray();

			foreach(IUniqueConstraint UniqueConstraint in UniqueConstraints)
			{
				CConsoleHelpers.WriteLine($"\t\tUNIQUE CONSTRAINT NAME [{UniqueConstraint.Name}].",ConsoleColor.Magenta);

				IColumn[]										Columns=UniqueConstraint.Columns.ToArray();

				foreach(IColumn Column in Columns)
				{
					CConsoleHelpers.WriteLine($"\t\t\tCOLUMN NAME [{Column.Name}].",ConsoleColor.Magenta);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintForeignKey(IForeignKey ForeignKey)
		{
			CConsoleHelpers.WriteLine($"\tFOREIGN KEY CONSTRAINT NAME [{ForeignKey.GetConstraintName()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tDELETE BEHAVIOR [{ForeignKey.DeleteBehavior}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS REQUIRED [{ForeignKey.IsRequired}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"\t\tIS UNIQUE [{ForeignKey.IsUnique}].",ConsoleColor.Magenta);

			IForeignKeyConstraint[]								ForeignKeyConstraints=ForeignKey.GetMappedConstraints().ToArray();

			foreach(IForeignKeyConstraint ForeignKeyConstraint in ForeignKeyConstraints)
			{
				CConsoleHelpers.WriteLine($"\t\tFOREIGN KEY CONSTRAINT NAME [{ForeignKeyConstraint.Name}].",ConsoleColor.Magenta);

				IColumn[]										Columns=ForeignKeyConstraint.Columns.ToArray();

				foreach(IColumn Column in Columns)
				{
					CConsoleHelpers.WriteLine($"\t\t\tCOLUMN NAME [{Column.Name}].",ConsoleColor.Magenta);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintEntityProperties(IEntityType EntityType)
		{
			CConsoleHelpers.WriteLine($"ENTITY NAME [{EntityType.DisplayName()}].",ConsoleColor.Magenta);

			IProperty[]											Properties=EntityType.GetProperties().ToArray();

			for(int Index=0;Index<Properties.Length;Index++)
			{
				IProperty										Property=Properties[Index];

				PrintProperty(Property);
			}

			INavigation[]										Navigations=EntityType.GetNavigations().ToArray();

			if (Navigations.Length>0)
			{
				Console.WriteLine();
			}

			for(int Index=0;Index<Navigations.Length;Index++)
			{
				INavigation										Navigation=Navigations[Index];

				PrintNavigation(Navigation);
			}

			IKey[]												Keys=EntityType.GetKeys().ToArray();

			if (Keys.Length>0)
			{
				Console.WriteLine();
			}

			for(int Index=0;Index<Keys.Length;Index++)
			{
				IKey											Key=Keys[Index];

				PrintKey(Key);
			}

			IForeignKey[]										ForeignKeys=EntityType.GetForeignKeys().ToArray();

			if (ForeignKeys.Length>0)
			{
				Console.WriteLine();
			}

			for(int Index=0;Index<ForeignKeys.Length;Index++)
			{
				IForeignKey										ForeignKey=ForeignKeys[Index];

				PrintForeignKey(ForeignKey);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void CreateTestDB()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				bool											DatabaseCreated=false;

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						if (Context.Database.CanConnect()==false)
						{
							// !!! Na vytvorenie DB sa pouziva METHOD DatabaseFacade.Migrate().
							Context.Database.Migrate();

							FillData(Context);

							Context.SaveChanges();

							DatabaseCreated=true;
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						DatabaseCreated=false;
					}
				}

				if (DatabaseCreated==true)
				{
					CConsoleHelpers.WriteLine($"DATABASE CREATED !",ConsoleColor.Green);
				}
				else
				{
					CConsoleHelpers.WriteLine($"DATABASE ALREADY EXISTS !",ConsoleColor.Blue);
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestSelectTestEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CTestEntity[]							Entities=Context.TestEntities.ToArray();

						CTestEntity.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToOneConventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipalConventions[]	Entities1=Context.EntitiesOneToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependentConventions[]	Entities2=Context.EntitiesOneToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOnePrincipalConventions		PrincipalEntity=new CEntityOneToOnePrincipalConventions("NEW PRINCIPAL CCC");
						CEntityOneToOneDependentConventions		DependentEntity=new CEntityOneToOneDependentConventions("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesOneToOnePrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipalConventions[]	Entities1=Context.EntitiesOneToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependentConventions[]	Entities2=Context.EntitiesOneToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToOnePrincipalConventions		Entity=Context.EntitiesOneToOnePrincipalConventions.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToOnePrincipalConventions.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipalConventions[]	Entities1=Context.EntitiesOneToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependentConventions[]	Entities2=Context.EntitiesOneToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOnePrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOneDependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToOneConventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalConventions[]	Entities1=Context.EntitiesZeroToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentConventions[]	Entities2=Context.EntitiesZeroToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroToOnePrincipalConventions	PrincipalEntity=new CEntityZeroToOnePrincipalConventions("NEW PRINCIPAL CCC");
						CEntityZeroToOneDependentConventions	DependentEntity=new CEntityZeroToOneDependentConventions("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesZeroToOnePrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID=DependentEntity.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalConventions[]	Entities1=Context.EntitiesZeroToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentConventions[]	Entities2=Context.EntitiesZeroToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalConventions	PrincipalEntity=Context.EntitiesZeroToOnePrincipalConventions.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToOnePrincipalConventions.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalConventions[]	Entities1=Context.EntitiesZeroToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentConventions[]	Entities2=Context.EntitiesZeroToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:1.
						CEntityZeroToOneDependentConventions	DependentEntity=Context.EntitiesZeroToOneDependentConventions.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID).First();

						Context.EntitiesZeroToOneDependentConventions.Remove(DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalConventions[]	Entities1=Context.EntitiesZeroToOnePrincipalConventions.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentConventions[]	Entities2=Context.EntitiesZeroToOneDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOnePrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOneDependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToManyConventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipalConventions[]	Entities1=Context.EntitiesOneToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependentConventions[]	Entities2=Context.EntitiesOneToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOneToManyDependentConventions	DependentEntity1=new CEntityOneToManyDependentConventions("NEW DEPENDENT 555");
						CEntityOneToManyDependentConventions	DependentEntity2=new CEntityOneToManyDependentConventions("NEW DEPENDENT 666");

						CEntityOneToManyPrincipalConventions	PrincipalEntity=new CEntityOneToManyPrincipalConventions("NEW PRINCIPAL 333",new CEntityOneToManyDependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOneToManyPrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipalConventions[]	Entities1=Context.EntitiesOneToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependentConventions[]	Entities2=Context.EntitiesOneToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToManyPrincipalConventions	Entity=Context.EntitiesOneToManyPrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToManyPrincipalConventions.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipalConventions[]	Entities1=Context.EntitiesOneToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependentConventions[]	Entities2=Context.EntitiesOneToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToManyPrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToManyDependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToManyConventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalConventions[]	Entities1=Context.EntitiesZeroToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentConventions[]	Entities2=Context.EntitiesZeroToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityZeroToManyDependentConventions	DependentEntity1=new CEntityZeroToManyDependentConventions("NEW DEPENDENT 555");
						CEntityZeroToManyDependentConventions	DependentEntity2=new CEntityZeroToManyDependentConventions("NEW DEPENDENT 666");

						CEntityZeroToManyPrincipalConventions	PrincipalEntity=new CEntityZeroToManyPrincipalConventions("NEW PRINCIPAL 333",new CEntityZeroToManyDependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesZeroToManyPrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalConventions[]	Entities1=Context.EntitiesZeroToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentConventions[]	Entities2=Context.EntitiesZeroToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalConventions	PrincipalEntity=Context.EntitiesZeroToManyPrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToManyPrincipalConventions.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalConventions[]	Entities1=Context.EntitiesZeroToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentConventions[]	Entities2=Context.EntitiesZeroToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToManyDependentConventions	DependentEntity1=Context.EntitiesZeroToManyDependentConventions.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToManyDependentConventions	DependentEntity2=Context.EntitiesZeroToManyDependentConventions.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesZeroToManyDependentConventions.Remove(DependentEntity1);
						Context.EntitiesZeroToManyDependentConventions.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalConventions[]	Entities1=Context.EntitiesZeroToManyPrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentConventions[]	Entities2=Context.EntitiesZeroToManyDependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToManyPrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToManyDependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestForeignKeyName1Conventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityForeignKeyName1PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName1DependentConventions[]	Entities2=Context.EntitiesForeignKeyName1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityForeignKeyName1DependentConventions	DependentEntity1=new CEntityForeignKeyName1DependentConventions("NEW DEPENDENT 555");
						CEntityForeignKeyName1DependentConventions	DependentEntity2=new CEntityForeignKeyName1DependentConventions("NEW DEPENDENT 666");

						CEntityForeignKeyName1PrincipalConventions	PrincipalEntity=new CEntityForeignKeyName1PrincipalConventions("NEW PRINCIPAL 333",new CEntityForeignKeyName1DependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesForeignKeyName1PrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityForeignKeyName1PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName1DependentConventions[]	Entities2=Context.EntitiesForeignKeyName1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityForeignKeyName1PrincipalConventions	Entity=Context.EntitiesForeignKeyName1PrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesForeignKeyName1PrincipalConventions.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityForeignKeyName1PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName1DependentConventions[]	Entities2=Context.EntitiesForeignKeyName1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityForeignKeyName1PrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityForeignKeyName1DependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestForeignKeyName2Conventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityForeignKeyName2PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName2DependentConventions[]	Entities2=Context.EntitiesForeignKeyName2DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityForeignKeyName2DependentConventions	DependentEntity1=new CEntityForeignKeyName2DependentConventions("NEW DEPENDENT 555");
						CEntityForeignKeyName2DependentConventions	DependentEntity2=new CEntityForeignKeyName2DependentConventions("NEW DEPENDENT 666");

						CEntityForeignKeyName2PrincipalConventions	PrincipalEntity=new CEntityForeignKeyName2PrincipalConventions("NEW PRINCIPAL 333",new CEntityForeignKeyName2DependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesForeignKeyName2PrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityForeignKeyName2PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName2DependentConventions[]	Entities2=Context.EntitiesForeignKeyName2DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityForeignKeyName2PrincipalConventions	Entity=Context.EntitiesForeignKeyName2PrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesForeignKeyName2PrincipalConventions.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityForeignKeyName2PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName2DependentConventions[]	Entities2=Context.EntitiesForeignKeyName2DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityForeignKeyName2PrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityForeignKeyName2DependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestForeignKeyName3Conventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityForeignKeyName3PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName3DependentConventions[]	Entities2=Context.EntitiesForeignKeyName3DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityForeignKeyName3DependentConventions	DependentEntity1=new CEntityForeignKeyName3DependentConventions("NEW DEPENDENT 555");
						CEntityForeignKeyName3DependentConventions	DependentEntity2=new CEntityForeignKeyName3DependentConventions("NEW DEPENDENT 666");

						CEntityForeignKeyName3PrincipalConventions	PrincipalEntity=new CEntityForeignKeyName3PrincipalConventions("NEW PRINCIPAL 333",new CEntityForeignKeyName3DependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesForeignKeyName3PrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityForeignKeyName3PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName3DependentConventions[]	Entities2=Context.EntitiesForeignKeyName3DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityForeignKeyName3PrincipalConventions	Entity=Context.EntitiesForeignKeyName3PrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesForeignKeyName3PrincipalConventions.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityForeignKeyName3PrincipalConventions[]	Entities1=Context.EntitiesForeignKeyName3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityForeignKeyName3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityForeignKeyName3DependentConventions[]	Entities2=Context.EntitiesForeignKeyName3DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityForeignKeyName3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityForeignKeyName3PrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityForeignKeyName3DependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestNoForeignKey1Conventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityNoForeignKey1PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey1DependentConventions[]	Entities2=Context.EntitiesNoForeignKey1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityNoForeignKey1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityNoForeignKey1DependentConventions	DependentEntity1=new CEntityNoForeignKey1DependentConventions("NEW DEPENDENT 555");
						CEntityNoForeignKey1DependentConventions	DependentEntity2=new CEntityNoForeignKey1DependentConventions("NEW DEPENDENT 666");

						CEntityNoForeignKey1PrincipalConventions	PrincipalEntity=new CEntityNoForeignKey1PrincipalConventions("NEW PRINCIPAL 333",new CEntityNoForeignKey1DependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesNoForeignKey1PrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityNoForeignKey1PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey1DependentConventions[]	Entities2=Context.EntitiesNoForeignKey1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityNoForeignKey1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityNoForeignKey1PrincipalConventions	PrincipalEntity=Context.EntitiesNoForeignKey1PrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesNoForeignKey1PrincipalConventions.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityNoForeignKey1PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey1DependentConventions[]	Entities2=Context.EntitiesNoForeignKey1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityNoForeignKey1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! DEPENDENT ENTITY je NUTNE EXPLICITNE ODSTRANIT, lebo SHADOW FOREIGN KEY PROPERTY je NULLABLE a vytvara vazbu 0/1:N.
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityNoForeignKey1DependentConventions	DependentEntity1=Context.EntitiesNoForeignKey1DependentConventions.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityNoForeignKey1DependentConventions	DependentEntity2=Context.EntitiesNoForeignKey1DependentConventions.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesNoForeignKey1DependentConventions.Remove(DependentEntity1);
						Context.EntitiesNoForeignKey1DependentConventions.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityNoForeignKey1PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey1PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey1PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey1DependentConventions[]	Entities2=Context.EntitiesNoForeignKey1DependentConventions.Include(P => P.EntityPrincipal).ToArray();

						CEntityNoForeignKey1DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityNoForeignKey1PrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityNoForeignKey1DependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestNoForeignKey2Conventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityNoForeignKey2PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey2DependentConventions[]	Entities2=Context.EntitiesNoForeignKey2DependentConventions.ToArray();

						CEntityNoForeignKey2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityNoForeignKey2DependentConventions	DependentEntity1=new CEntityNoForeignKey2DependentConventions("NEW DEPENDENT 555");
						CEntityNoForeignKey2DependentConventions	DependentEntity2=new CEntityNoForeignKey2DependentConventions("NEW DEPENDENT 666");

						CEntityNoForeignKey2PrincipalConventions	PrincipalEntity=new CEntityNoForeignKey2PrincipalConventions("NEW PRINCIPAL 333",new CEntityNoForeignKey2DependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesNoForeignKey2PrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityNoForeignKey2PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey2DependentConventions[]	Entities2=Context.EntitiesNoForeignKey2DependentConventions.ToArray();

						CEntityNoForeignKey2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityNoForeignKey2PrincipalConventions	PrincipalEntity=Context.EntitiesNoForeignKey2PrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesNoForeignKey2PrincipalConventions.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityNoForeignKey2PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey2DependentConventions[]	Entities2=Context.EntitiesNoForeignKey2DependentConventions.ToArray();

						CEntityNoForeignKey2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! DEPENDENT ENTITY je NUTNE EXPLICITNE ODSTRANIT, lebo SHADOW FOREIGN KEY PROPERTY je NULLABLE a vytvara vazbu 0/1:N.
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityNoForeignKey2DependentConventions	DependentEntity1=Context.EntitiesNoForeignKey2DependentConventions.Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityNoForeignKey2DependentConventions	DependentEntity2=Context.EntitiesNoForeignKey2DependentConventions.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesNoForeignKey2DependentConventions.Remove(DependentEntity1);
						Context.EntitiesNoForeignKey2DependentConventions.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityNoForeignKey2PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey2PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey2PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey2DependentConventions[]	Entities2=Context.EntitiesNoForeignKey2DependentConventions.ToArray();

						CEntityNoForeignKey2DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityNoForeignKey2PrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityNoForeignKey2DependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestNoForeignKey3Conventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityNoForeignKey3PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey3DependentConventions[]	Entities2=Context.EntitiesNoForeignKey3DependentConventions.ToArray();

						CEntityNoForeignKey3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityNoForeignKey3DependentConventions	DependentEntity1=new CEntityNoForeignKey3DependentConventions("NEW DEPENDENT 555");
						CEntityNoForeignKey3DependentConventions	DependentEntity2=new CEntityNoForeignKey3DependentConventions("NEW DEPENDENT 666");

						CEntityNoForeignKey3PrincipalConventions	PrincipalEntity=new CEntityNoForeignKey3PrincipalConventions("NEW PRINCIPAL 333",new CEntityNoForeignKey3DependentConventions[]{DependentEntity1,DependentEntity2});

						Context.EntitiesNoForeignKey3PrincipalConventions.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityNoForeignKey3PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey3DependentConventions[]	Entities2=Context.EntitiesNoForeignKey3DependentConventions.ToArray();

						CEntityNoForeignKey3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityNoForeignKey3PrincipalConventions	PrincipalEntity=Context.EntitiesNoForeignKey3PrincipalConventions.Include(P => P.EntitiesDependent).Where(P => P.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID==PrincipalID).First();

						Context.EntitiesNoForeignKey3PrincipalConventions.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.CEntityNoForeignKey3PrincipalConventionsEntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityNoForeignKey3PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey3DependentConventions[]	Entities2=Context.EntitiesNoForeignKey3DependentConventions.ToArray();

						CEntityNoForeignKey3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! DEPENDENT ENTITY je NUTNE EXPLICITNE ODSTRANIT, lebo SHADOW FOREIGN KEY PROPERTY je NULLABLE a vytvara vazbu 0/1:N.
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityNoForeignKey3DependentConventions	DependentEntity1=Context.EntitiesNoForeignKey3DependentConventions.Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityNoForeignKey3DependentConventions	DependentEntity2=Context.EntitiesNoForeignKey3DependentConventions.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesNoForeignKey3DependentConventions.Remove(DependentEntity1);
						Context.EntitiesNoForeignKey3DependentConventions.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityNoForeignKey3PrincipalConventions[]	Entities1=Context.EntitiesNoForeignKey3PrincipalConventions.Include(P => P.EntitiesDependent).ToArray();

						CEntityNoForeignKey3PrincipalConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityNoForeignKey3DependentConventions[]	Entities2=Context.EntitiesNoForeignKey3DependentConventions.ToArray();

						CEntityNoForeignKey3DependentConventions.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityNoForeignKey3PrincipalConventions));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityNoForeignKey3DependentConventions));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToOneDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesOneToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependentDataAnnotations[]	Entities2=Context.EntitiesOneToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOnePrincipalDataAnnotations	PrincipalEntity=new CEntityOneToOnePrincipalDataAnnotations("NEW PRINCIPAL CCC");
						CEntityOneToOneDependentDataAnnotations	DependentEntity=new CEntityOneToOneDependentDataAnnotations("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesOneToOnePrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesOneToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependentDataAnnotations[]	Entities2=Context.EntitiesOneToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToOnePrincipalDataAnnotations	Entity=Context.EntitiesOneToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToOnePrincipalDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesOneToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependentDataAnnotations[]	Entities2=Context.EntitiesOneToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOnePrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOneDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToOneDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroToOnePrincipalDataAnnotations	PrincipalEntity=new CEntityZeroToOnePrincipalDataAnnotations("NEW PRINCIPAL CCC");
						CEntityZeroToOneDependentDataAnnotations	DependentEntity=new CEntityZeroToOneDependentDataAnnotations("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesZeroToOnePrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID=DependentEntity.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalDataAnnotations	PrincipalEntity=Context.EntitiesZeroToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToOnePrincipalDataAnnotations.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:1.
						CEntityZeroToOneDependentDataAnnotations	DependentEntity=Context.EntitiesZeroToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID).First();

						Context.EntitiesZeroToOneDependentDataAnnotations.Remove(DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToOnePrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToOnePrincipalDataAnnotations.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOnePrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOneDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToOneDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOneDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOnePrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOneDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToManyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesOneToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependentDataAnnotations[]	Entities2=Context.EntitiesOneToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOneToManyDependentDataAnnotations	DependentEntity1=new CEntityOneToManyDependentDataAnnotations("NEW DEPENDENT 555");
						CEntityOneToManyDependentDataAnnotations	DependentEntity2=new CEntityOneToManyDependentDataAnnotations("NEW DEPENDENT 666");

						CEntityOneToManyPrincipalDataAnnotations	PrincipalEntity=new CEntityOneToManyPrincipalDataAnnotations("NEW PRINCIPAL 333",new CEntityOneToManyDependentDataAnnotations[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOneToManyPrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesOneToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependentDataAnnotations[]	Entities2=Context.EntitiesOneToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToManyPrincipalDataAnnotations	Entity=Context.EntitiesOneToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToManyPrincipalDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesOneToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependentDataAnnotations[]	Entities2=Context.EntitiesOneToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToManyPrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToManyDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToManyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityZeroToManyDependentDataAnnotations	DependentEntity1=new CEntityZeroToManyDependentDataAnnotations("NEW DEPENDENT 555");
						CEntityZeroToManyDependentDataAnnotations	DependentEntity2=new CEntityZeroToManyDependentDataAnnotations("NEW DEPENDENT 666");

						CEntityZeroToManyPrincipalDataAnnotations	PrincipalEntity=new CEntityZeroToManyPrincipalDataAnnotations("NEW PRINCIPAL 333",new CEntityZeroToManyDependentDataAnnotations[]{DependentEntity1,DependentEntity2});

						Context.EntitiesZeroToManyPrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalDataAnnotations	PrincipalEntity=Context.EntitiesZeroToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToManyPrincipalDataAnnotations.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToManyDependentDataAnnotations	DependentEntity1=Context.EntitiesZeroToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToManyDependentDataAnnotations	DependentEntity2=Context.EntitiesZeroToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesZeroToManyDependentDataAnnotations.Remove(DependentEntity1);
						Context.EntitiesZeroToManyDependentDataAnnotations.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipalDataAnnotations[]	Entities1=Context.EntitiesZeroToManyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependentDataAnnotations[]	Entities2=Context.EntitiesZeroToManyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToManyPrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToManyDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAttributeOnNavigationPropertyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations[]	Entities2=Context.EntitiesAttributeOnNavigationPropertyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations	DependentEntity1=new CEntityAttributeOnNavigationPropertyDependentDataAnnotations("NEW DEPENDENT 555");
						CEntityAttributeOnNavigationPropertyDependentDataAnnotations	DependentEntity2=new CEntityAttributeOnNavigationPropertyDependentDataAnnotations("NEW DEPENDENT 666");

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations	PrincipalEntity=new CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations("NEW PRINCIPAL 333",new CEntityAttributeOnNavigationPropertyDependentDataAnnotations[]{DependentEntity1,DependentEntity2});

						Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations[]	Entities2=Context.EntitiesAttributeOnNavigationPropertyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations	Entity=Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesAttributeOnNavigationPropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations[]	Entities2=Context.EntitiesAttributeOnNavigationPropertyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityAttributeOnNavigationPropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityAttributeOnNavigationPropertyPrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityAttributeOnNavigationPropertyDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAttributeOnForeignKeyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations[]	Entities1=Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAttributeOnForeignKeyDependentDataAnnotations[]	Entities2=Context.EntitiesAttributeOnForeignKeyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityAttributeOnForeignKeyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityAttributeOnForeignKeyDependentDataAnnotations	DependentEntity1=new CEntityAttributeOnForeignKeyDependentDataAnnotations("NEW DEPENDENT 555");
						CEntityAttributeOnForeignKeyDependentDataAnnotations	DependentEntity2=new CEntityAttributeOnForeignKeyDependentDataAnnotations("NEW DEPENDENT 666");

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations	PrincipalEntity=new CEntityAttributeOnForeignKeyPrincipalDataAnnotations("NEW PRINCIPAL 333",new CEntityAttributeOnForeignKeyDependentDataAnnotations[]{DependentEntity1,DependentEntity2});

						Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations[]	Entities1=Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAttributeOnForeignKeyDependentDataAnnotations[]	Entities2=Context.EntitiesAttributeOnForeignKeyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityAttributeOnForeignKeyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityAttributeOnForeignKeyPrincipalDataAnnotations	Entity=Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations[]	Entities1=Context.EntitiesAttributeOnForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityAttributeOnForeignKeyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAttributeOnForeignKeyDependentDataAnnotations[]	Entities2=Context.EntitiesAttributeOnForeignKeyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityAttributeOnForeignKeyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityAttributeOnForeignKeyPrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityAttributeOnForeignKeyDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestCompositeForeignKeyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityCompositeForeignKeyPrincipalDataAnnotations[]	Entities1=Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityCompositeForeignKeyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityCompositeForeignKeyDependentDataAnnotations[]	Entities2=Context.EntitiesCompositeForeignKeyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityCompositeForeignKeyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityCompositeForeignKeyDependentDataAnnotations	DependentEntity1=new CEntityCompositeForeignKeyDependentDataAnnotations("NEW DEPENDENT 555");
						CEntityCompositeForeignKeyDependentDataAnnotations	DependentEntity2=new CEntityCompositeForeignKeyDependentDataAnnotations("NEW DEPENDENT 666");

						CEntityCompositeForeignKeyPrincipalDataAnnotations	PrincipalEntity=new CEntityCompositeForeignKeyPrincipalDataAnnotations(3,103,"NEW PRINCIPAL 333",new CEntityCompositeForeignKeyDependentDataAnnotations[]{DependentEntity1,DependentEntity2});

						Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity.EntityPrincipalID1;
							PrincipalID2=PrincipalEntity.EntityPrincipalID2;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID1},{PrincipalEntity.EntityPrincipalID2}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityCompositeForeignKeyPrincipalDataAnnotations[]	Entities1=Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityCompositeForeignKeyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityCompositeForeignKeyDependentDataAnnotations[]	Entities2=Context.EntitiesCompositeForeignKeyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityCompositeForeignKeyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityCompositeForeignKeyPrincipalDataAnnotations	Entity=Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID1==PrincipalID1 && P.EntityPrincipalID2==PrincipalID2).First();

						Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID1},{Entity.EntityPrincipalID2}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityCompositeForeignKeyPrincipalDataAnnotations[]	Entities1=Context.EntitiesCompositeForeignKeyPrincipalDataAnnotations.Include(P => P.EntitiesDependent).ToArray();

						CEntityCompositeForeignKeyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityCompositeForeignKeyDependentDataAnnotations[]	Entities2=Context.EntitiesCompositeForeignKeyDependentDataAnnotations.Include(P => P.EntityPrincipal).ToArray();

						CEntityCompositeForeignKeyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityCompositeForeignKeyPrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityCompositeForeignKeyDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestInversePropertyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;
			int													DependentID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityInversePropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesInversePropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).ToArray();
						
						CEntityInversePropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityInversePropertyDependentDataAnnotations[]	Entities2=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).ToArray();

						CEntityInversePropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityInversePropertyDependentDataAnnotations	DependentEntity1Relationship1=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 555 RELATIONSHIP AAA");
						CEntityInversePropertyDependentDataAnnotations	DependentEntity2Relationship1=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 666 RELATIONSHIP AAA");

						CEntityInversePropertyDependentDataAnnotations	DependentEntity1Relationship2=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 555 RELATIONSHIP BBB");
						CEntityInversePropertyDependentDataAnnotations	DependentEntity2Relationship2=new CEntityInversePropertyDependentDataAnnotations("DEPENDENT 666 RELATIONSHIP BBB");

						CEntityInversePropertyPrincipalDataAnnotations	PrincipalEntity=new CEntityInversePropertyPrincipalDataAnnotations("PRINCIPAL 333",new CEntityInversePropertyDependentDataAnnotations[]{DependentEntity1Relationship1,DependentEntity2Relationship1},new CEntityInversePropertyDependentDataAnnotations[]{DependentEntity1Relationship2,DependentEntity2Relationship2});

						Context.EntitiesInversePropertyPrincipalDataAnnotations.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1Relationship1.EntityDependentID;
							DependentID2=DependentEntity2Relationship1.EntityDependentID;
							DependentID3=DependentEntity1Relationship2.EntityDependentID;
							DependentID4=DependentEntity2Relationship2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1Relationship1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2Relationship1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1Relationship2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2Relationship2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityInversePropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesInversePropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).ToArray();

						CEntityInversePropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityInversePropertyDependentDataAnnotations[]	Entities2=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).ToArray();

						CEntityInversePropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityInversePropertyPrincipalDataAnnotations	Entity=Context.EntitiesInversePropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesInversePropertyPrincipalDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityInversePropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesInversePropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).ToArray();

						CEntityInversePropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityInversePropertyDependentDataAnnotations[]	Entities2=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).ToArray();

						CEntityInversePropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						CEntityInversePropertyDependentDataAnnotations	Entity1=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityInversePropertyDependentDataAnnotations	Entity2=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).Where(P => P.EntityDependentID==DependentID2).First();
						CEntityInversePropertyDependentDataAnnotations	Entity3=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).Where(P => P.EntityDependentID==DependentID3).First();
						CEntityInversePropertyDependentDataAnnotations	Entity4=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).Where(P => P.EntityDependentID==DependentID4).First();

						Context.EntitiesInversePropertyDependentDataAnnotations.Remove(Entity1);
						Context.EntitiesInversePropertyDependentDataAnnotations.Remove(Entity2);
						Context.EntitiesInversePropertyDependentDataAnnotations.Remove(Entity3);
						Context.EntitiesInversePropertyDependentDataAnnotations.Remove(Entity4);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{Entity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{Entity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{Entity3.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{Entity4.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityInversePropertyPrincipalDataAnnotations[]	Entities1=Context.EntitiesInversePropertyPrincipalDataAnnotations.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).ToArray();

						CEntityInversePropertyPrincipalDataAnnotations.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityInversePropertyDependentDataAnnotations[]	Entities2=Context.EntitiesInversePropertyDependentDataAnnotations.Include(P => P.EntityPrincipal1).Include(P => P.EntityPrincipal2).ToArray();

						CEntityInversePropertyDependentDataAnnotations.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityInversePropertyPrincipalDataAnnotations));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityInversePropertyDependentDataAnnotations));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToOne1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOne1DependentFluentAPI[]	Entities2=Context.EntitiesOneToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOne1PrincipalFluentAPI		PrincipalEntity=new CEntityOneToOne1PrincipalFluentAPI("NEW PRINCIPAL CCC");
						CEntityOneToOne1DependentFluentAPI		DependentEntity=new CEntityOneToOne1DependentFluentAPI("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesOneToOne1PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOne1DependentFluentAPI[]	Entities2=Context.EntitiesOneToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToOne1PrincipalFluentAPI		Entity=Context.EntitiesOneToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToOne1PrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOne1DependentFluentAPI[]	Entities2=Context.EntitiesOneToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOne1PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOne1DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToOne2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOne2DependentFluentAPI[]	Entities2=Context.EntitiesOneToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOne2PrincipalFluentAPI		PrincipalEntity=new CEntityOneToOne2PrincipalFluentAPI("NEW PRINCIPAL CCC");
						CEntityOneToOne2DependentFluentAPI		DependentEntity=new CEntityOneToOne2DependentFluentAPI("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesOneToOne2PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOne2DependentFluentAPI[]	Entities2=Context.EntitiesOneToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToOne2PrincipalFluentAPI		Entity=Context.EntitiesOneToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToOne2PrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOne2DependentFluentAPI[]	Entities2=Context.EntitiesOneToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOne2PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOne2DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToOne1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroToOne1PrincipalFluentAPI		PrincipalEntity=new CEntityZeroToOne1PrincipalFluentAPI("NEW PRINCIPAL CCC");
						CEntityZeroToOne1DependentFluentAPI		DependentEntity=new CEntityZeroToOne1DependentFluentAPI("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesZeroToOne1PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID=DependentEntity.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOne1PrincipalFluentAPI		PrincipalEntity=Context.EntitiesZeroToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToOne1PrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:1.
						CEntityZeroToOne1DependentFluentAPI		DependentEntity=Context.EntitiesZeroToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID).First();

						Context.EntitiesZeroToOne1DependentFluentAPI.Remove(DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToOne1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOne1PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOne1DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToOne2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroToOne2PrincipalFluentAPI		PrincipalEntity=new CEntityZeroToOne2PrincipalFluentAPI("NEW PRINCIPAL CCC");
						CEntityZeroToOne2DependentFluentAPI		DependentEntity=new CEntityZeroToOne2DependentFluentAPI("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesZeroToOne2PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID=DependentEntity.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOne2PrincipalFluentAPI		PrincipalEntity=Context.EntitiesZeroToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToOne2PrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:1.
						CEntityZeroToOne2DependentFluentAPI		DependentEntity=Context.EntitiesZeroToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID).First();

						Context.EntitiesZeroToOne2DependentFluentAPI.Remove(DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToOne2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToOne2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityZeroToOne2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToOne2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToOne2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToOne2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOne2PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToOne2DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToOneMixedKeys1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToOneMixedKeys1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOneMixedKeys1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneMixedKeys1DependentFluentAPI[]	Entities2=Context.EntitiesOneToOneMixedKeys1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneMixedKeys1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOneMixedKeys1PrincipalFluentAPI		PrincipalEntity=new CEntityOneToOneMixedKeys1PrincipalFluentAPI("NEW PRINCIPAL CCC");
						CEntityOneToOneMixedKeys1DependentFluentAPI		DependentEntity=new CEntityOneToOneMixedKeys1DependentFluentAPI("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToOneMixedKeys1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOneMixedKeys1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneMixedKeys1DependentFluentAPI[]	Entities2=Context.EntitiesOneToOneMixedKeys1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneMixedKeys1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToOneMixedKeys1PrincipalFluentAPI		Entity=Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToOneMixedKeys1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOneMixedKeys1PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOneMixedKeys1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneMixedKeys1DependentFluentAPI[]	Entities2=Context.EntitiesOneToOneMixedKeys1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneMixedKeys1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOneMixedKeys1PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOneMixedKeys1DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToOneMixedKeys2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToOneMixedKeys2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOneMixedKeys2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneMixedKeys2DependentFluentAPI[]	Entities2=Context.EntitiesOneToOneMixedKeys2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneMixedKeys2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOneMixedKeys2PrincipalFluentAPI		PrincipalEntity=new CEntityOneToOneMixedKeys2PrincipalFluentAPI("NEW PRINCIPAL CCC");
						CEntityOneToOneMixedKeys2DependentFluentAPI		DependentEntity=new CEntityOneToOneMixedKeys2DependentFluentAPI("NEW DEPENDENT CCC");

						PrincipalEntity.EntityDependent=DependentEntity;

						Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToOneMixedKeys2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOneMixedKeys2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneMixedKeys2DependentFluentAPI[]	Entities2=Context.EntitiesOneToOneMixedKeys2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneMixedKeys2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToOneMixedKeys2PrincipalFluentAPI		Entity=Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToOneMixedKeys2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToOneMixedKeys2PrincipalFluentAPI.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOneMixedKeys2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneMixedKeys2DependentFluentAPI[]	Entities2=Context.EntitiesOneToOneMixedKeys2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneMixedKeys2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOneMixedKeys2PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToOneMixedKeys2DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToMany1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToMany1DependentFluentAPI[]	Entities2=Context.EntitiesOneToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOneToMany1DependentFluentAPI		DependentEntity1=new CEntityOneToMany1DependentFluentAPI("NEW DEPENDENT 555");
						CEntityOneToMany1DependentFluentAPI		DependentEntity2=new CEntityOneToMany1DependentFluentAPI("NEW DEPENDENT 666");

						CEntityOneToMany1PrincipalFluentAPI		PrincipalEntity=new CEntityOneToMany1PrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOneToMany1DependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOneToMany1PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToMany1DependentFluentAPI[]	Entities2=Context.EntitiesOneToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToMany1PrincipalFluentAPI		Entity=Context.EntitiesOneToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToMany1PrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToMany1DependentFluentAPI[]	Entities2=Context.EntitiesOneToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToMany1PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToMany1DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOneToMany2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToMany2DependentFluentAPI[]	Entities2=Context.EntitiesOneToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOneToMany2DependentFluentAPI		DependentEntity1=new CEntityOneToMany2DependentFluentAPI("NEW DEPENDENT 555");
						CEntityOneToMany2DependentFluentAPI		DependentEntity2=new CEntityOneToMany2DependentFluentAPI("NEW DEPENDENT 666");

						CEntityOneToMany2PrincipalFluentAPI		PrincipalEntity=new CEntityOneToMany2PrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOneToMany2DependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOneToMany2PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOneToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToMany2DependentFluentAPI[]	Entities2=Context.EntitiesOneToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityOneToMany2PrincipalFluentAPI		Entity=Context.EntitiesOneToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOneToMany2PrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityOneToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesOneToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToMany2DependentFluentAPI[]	Entities2=Context.EntitiesOneToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOneToMany2PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOneToMany2DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToMany1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityZeroToMany1DependentFluentAPI	DependentEntity1=new CEntityZeroToMany1DependentFluentAPI("NEW DEPENDENT 555");
						CEntityZeroToMany1DependentFluentAPI	DependentEntity2=new CEntityZeroToMany1DependentFluentAPI("NEW DEPENDENT 666");

						CEntityZeroToMany1PrincipalFluentAPI	PrincipalEntity=new CEntityZeroToMany1PrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityZeroToMany1DependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesZeroToMany1PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToMany1PrincipalFluentAPI	PrincipalEntity=Context.EntitiesZeroToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToMany1PrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToMany1DependentFluentAPI	DependentEntity1=Context.EntitiesZeroToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToMany1DependentFluentAPI	DependentEntity2=Context.EntitiesZeroToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesZeroToMany1DependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesZeroToMany1DependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToMany1PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany1PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany1PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany1DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany1DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany1DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToMany1PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToMany1DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroToMany2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityZeroToMany2DependentFluentAPI	DependentEntity1=new CEntityZeroToMany2DependentFluentAPI("NEW DEPENDENT 555");
						CEntityZeroToMany2DependentFluentAPI	DependentEntity2=new CEntityZeroToMany2DependentFluentAPI("NEW DEPENDENT 666");

						CEntityZeroToMany2PrincipalFluentAPI	PrincipalEntity=new CEntityZeroToMany2PrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityZeroToMany2DependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesZeroToMany2PrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToMany2PrincipalFluentAPI	PrincipalEntity=Context.EntitiesZeroToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesZeroToMany2PrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToMany2DependentFluentAPI	DependentEntity1=Context.EntitiesZeroToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityZeroToMany2DependentFluentAPI	DependentEntity2=Context.EntitiesZeroToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesZeroToMany2DependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesZeroToMany2DependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroToMany2PrincipalFluentAPI[]	Entities1=Context.EntitiesZeroToMany2PrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToMany2PrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToMany2DependentFluentAPI[]	Entities2=Context.EntitiesZeroToMany2DependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToMany2DependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToMany2PrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityZeroToMany2DependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestManyToMany1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToMany1MFluentAPI[]			Entities1=Context.EntitiesManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany1NFluentAPI[]			Entities2=Context.EntitiesManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany1MNFluentAPI[]			Entities3=Context.EntitiesManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToMany1MFluentAPI			EntityManyToMany1MFluentAPI1=new CEntityManyToMany1MFluentAPI("NEW ENTITY M - 333");
						CEntityManyToMany1MFluentAPI			EntityManyToMany1MFluentAPI2=new CEntityManyToMany1MFluentAPI("NEW ENTITY M - 444");

						CEntityManyToMany1NFluentAPI			EntityManyToMany1NFluentAPI1=new CEntityManyToMany1NFluentAPI("NEW ENTITY N - 333");
						CEntityManyToMany1NFluentAPI			EntityManyToMany1NFluentAPI2=new CEntityManyToMany1NFluentAPI("NEW ENTITY N - 444");

						CEntityManyToMany1MNFluentAPI			EntityManyToMany1MNFluentAPI11=new CEntityManyToMany1MNFluentAPI("NEW ENTITY MN - 33");
						CEntityManyToMany1MNFluentAPI			EntityManyToMany1MNFluentAPI12=new CEntityManyToMany1MNFluentAPI("NEW ENTITY MN - 34");
						CEntityManyToMany1MNFluentAPI			EntityManyToMany1MNFluentAPI21=new CEntityManyToMany1MNFluentAPI("NEW ENTITY MN - 43");
						CEntityManyToMany1MNFluentAPI			EntityManyToMany1MNFluentAPI22=new CEntityManyToMany1MNFluentAPI("NEW ENTITY MN - 44");

						EntityManyToMany1MNFluentAPI11.EntityM=EntityManyToMany1MFluentAPI1;
						EntityManyToMany1MNFluentAPI11.EntityN=EntityManyToMany1NFluentAPI1;

						EntityManyToMany1MNFluentAPI12.EntityM=EntityManyToMany1MFluentAPI1;
						EntityManyToMany1MNFluentAPI12.EntityN=EntityManyToMany1NFluentAPI2;

						EntityManyToMany1MNFluentAPI21.EntityM=EntityManyToMany1MFluentAPI2;
						EntityManyToMany1MNFluentAPI21.EntityN=EntityManyToMany1NFluentAPI1;

						EntityManyToMany1MNFluentAPI22.EntityM=EntityManyToMany1MFluentAPI2;
						EntityManyToMany1MNFluentAPI22.EntityN=EntityManyToMany1NFluentAPI2;

						Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI11);
						Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI12);
						Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI21);
						Context.EntitiesManyToMany1MNFluentAPI.Add(EntityManyToMany1MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityManyToMany1MFluentAPI1.EntityMID;
							ID2=EntityManyToMany1MFluentAPI2.EntityMID;
							ID3=EntityManyToMany1NFluentAPI1.EntityNID;
							ID4=EntityManyToMany1NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityManyToMany1MFluentAPI[]			Entities1=Context.EntitiesManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany1NFluentAPI[]			Entities2=Context.EntitiesManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany1MNFluentAPI[]			Entities3=Context.EntitiesManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityManyToMany1MFluentAPI			EntityM1=Context.EntitiesManyToMany1MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityManyToMany1MFluentAPI			EntityM2=Context.EntitiesManyToMany1MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityManyToMany1NFluentAPI			EntityN1=Context.EntitiesManyToMany1NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityManyToMany1NFluentAPI			EntityN2=Context.EntitiesManyToMany1NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToMany1MFluentAPI.Remove(EntityM1);
						Context.EntitiesManyToMany1MFluentAPI.Remove(EntityM2);
						Context.EntitiesManyToMany1NFluentAPI.Remove(EntityN1);
						Context.EntitiesManyToMany1NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityManyToMany1MFluentAPI[]			Entities1=Context.EntitiesManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany1NFluentAPI[]			Entities2=Context.EntitiesManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany1MNFluentAPI[]			Entities3=Context.EntitiesManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityManyToMany1MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityManyToMany1NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityManyToMany1MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestManyToMany2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToMany2MFluentAPI[]			Entities1=Context.EntitiesManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany2NFluentAPI[]			Entities2=Context.EntitiesManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany2MNFluentAPI[]			Entities3=Context.EntitiesManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToMany2MFluentAPI			EntityManyToMany2MFluentAPI1=new CEntityManyToMany2MFluentAPI("NEW ENTITY M - 333");
						CEntityManyToMany2MFluentAPI			EntityManyToMany2MFluentAPI2=new CEntityManyToMany2MFluentAPI("NEW ENTITY M - 444");

						CEntityManyToMany2NFluentAPI			EntityManyToMany2NFluentAPI1=new CEntityManyToMany2NFluentAPI("NEW ENTITY N - 333");
						CEntityManyToMany2NFluentAPI			EntityManyToMany2NFluentAPI2=new CEntityManyToMany2NFluentAPI("NEW ENTITY N - 444");

						CEntityManyToMany2MNFluentAPI			EntityManyToMany2MNFluentAPI11=new CEntityManyToMany2MNFluentAPI("NEW ENTITY MN - 33");
						CEntityManyToMany2MNFluentAPI			EntityManyToMany2MNFluentAPI12=new CEntityManyToMany2MNFluentAPI("NEW ENTITY MN - 34");
						CEntityManyToMany2MNFluentAPI			EntityManyToMany2MNFluentAPI21=new CEntityManyToMany2MNFluentAPI("NEW ENTITY MN - 43");
						CEntityManyToMany2MNFluentAPI			EntityManyToMany2MNFluentAPI22=new CEntityManyToMany2MNFluentAPI("NEW ENTITY MN - 44");

						EntityManyToMany2MNFluentAPI11.EntityM=EntityManyToMany2MFluentAPI1;
						EntityManyToMany2MNFluentAPI11.EntityN=EntityManyToMany2NFluentAPI1;

						EntityManyToMany2MNFluentAPI12.EntityM=EntityManyToMany2MFluentAPI1;
						EntityManyToMany2MNFluentAPI12.EntityN=EntityManyToMany2NFluentAPI2;

						EntityManyToMany2MNFluentAPI21.EntityM=EntityManyToMany2MFluentAPI2;
						EntityManyToMany2MNFluentAPI21.EntityN=EntityManyToMany2NFluentAPI1;

						EntityManyToMany2MNFluentAPI22.EntityM=EntityManyToMany2MFluentAPI2;
						EntityManyToMany2MNFluentAPI22.EntityN=EntityManyToMany2NFluentAPI2;

						Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI11);
						Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI12);
						Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI21);
						Context.EntitiesManyToMany2MNFluentAPI.Add(EntityManyToMany2MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityManyToMany2MFluentAPI1.EntityMID;
							ID2=EntityManyToMany2MFluentAPI2.EntityMID;
							ID3=EntityManyToMany2NFluentAPI1.EntityNID;
							ID4=EntityManyToMany2NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityManyToMany2MFluentAPI[]			Entities1=Context.EntitiesManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany2NFluentAPI[]			Entities2=Context.EntitiesManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany2MNFluentAPI[]			Entities3=Context.EntitiesManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityManyToMany2MFluentAPI			EntityM1=Context.EntitiesManyToMany2MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityManyToMany2MFluentAPI			EntityM2=Context.EntitiesManyToMany2MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityManyToMany2NFluentAPI			EntityN1=Context.EntitiesManyToMany2NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityManyToMany2NFluentAPI			EntityN2=Context.EntitiesManyToMany2NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToMany2MFluentAPI.Remove(EntityM1);
						Context.EntitiesManyToMany2MFluentAPI.Remove(EntityM2);
						Context.EntitiesManyToMany2NFluentAPI.Remove(EntityN1);
						Context.EntitiesManyToMany2NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityManyToMany2MFluentAPI[]			Entities1=Context.EntitiesManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany2NFluentAPI[]			Entities2=Context.EntitiesManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToMany2MNFluentAPI[]			Entities3=Context.EntitiesManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityManyToMany2MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityManyToMany2NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityManyToMany2MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroManyToMany1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;
			int													PrincipalID3=0;
			int													PrincipalID4=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;
			int													DependentID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany1MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroManyToMany1MFluentAPI		EntityZeroManyToMany1MFluentAPI1=new CEntityZeroManyToMany1MFluentAPI("NEW ENTITY M - 333");
						CEntityZeroManyToMany1MFluentAPI		EntityZeroManyToMany1MFluentAPI2=new CEntityZeroManyToMany1MFluentAPI("NEW ENTITY M - 444");

						CEntityZeroManyToMany1NFluentAPI		EntityZeroManyToMany1NFluentAPI1=new CEntityZeroManyToMany1NFluentAPI("NEW ENTITY N - 333");
						CEntityZeroManyToMany1NFluentAPI		EntityZeroManyToMany1NFluentAPI2=new CEntityZeroManyToMany1NFluentAPI("NEW ENTITY N - 444");

						CEntityZeroManyToMany1MNFluentAPI		EntityZeroManyToMany1MNFluentAPI11=new CEntityZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 33");
						CEntityZeroManyToMany1MNFluentAPI		EntityZeroManyToMany1MNFluentAPI12=new CEntityZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 34");
						CEntityZeroManyToMany1MNFluentAPI		EntityZeroManyToMany1MNFluentAPI21=new CEntityZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 43");
						CEntityZeroManyToMany1MNFluentAPI		EntityZeroManyToMany1MNFluentAPI22=new CEntityZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 44");

						EntityZeroManyToMany1MNFluentAPI11.EntityM=EntityZeroManyToMany1MFluentAPI1;
						EntityZeroManyToMany1MNFluentAPI11.EntityN=EntityZeroManyToMany1NFluentAPI1;

						EntityZeroManyToMany1MNFluentAPI12.EntityM=EntityZeroManyToMany1MFluentAPI1;
						EntityZeroManyToMany1MNFluentAPI12.EntityN=EntityZeroManyToMany1NFluentAPI2;

						EntityZeroManyToMany1MNFluentAPI21.EntityM=EntityZeroManyToMany1MFluentAPI2;
						EntityZeroManyToMany1MNFluentAPI21.EntityN=EntityZeroManyToMany1NFluentAPI1;

						EntityZeroManyToMany1MNFluentAPI22.EntityM=EntityZeroManyToMany1MFluentAPI2;
						EntityZeroManyToMany1MNFluentAPI22.EntityN=EntityZeroManyToMany1NFluentAPI2;

						Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI11);
						Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI12);
						Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI21);
						Context.EntitiesZeroManyToMany1MNFluentAPI.Add(EntityZeroManyToMany1MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=EntityZeroManyToMany1MFluentAPI1.EntityMID;
							PrincipalID2=EntityZeroManyToMany1MFluentAPI2.EntityMID;
							PrincipalID3=EntityZeroManyToMany1NFluentAPI1.EntityNID;
							PrincipalID4=EntityZeroManyToMany1NFluentAPI2.EntityNID;
							DependentID1=EntityZeroManyToMany1MNFluentAPI11.EntityMNID;
							DependentID2=EntityZeroManyToMany1MNFluentAPI12.EntityMNID;
							DependentID3=EntityZeroManyToMany1MNFluentAPI21.EntityMNID;
							DependentID4=EntityZeroManyToMany1MNFluentAPI22.EntityMNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany1MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroManyToMany1MFluentAPI		EntityM1=Context.EntitiesZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID1).First();
						CEntityZeroManyToMany1MFluentAPI		EntityM2=Context.EntitiesZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID2).First();
						CEntityZeroManyToMany1NFluentAPI		EntityN1=Context.EntitiesZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID3).First();
						CEntityZeroManyToMany1NFluentAPI		EntityN2=Context.EntitiesZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID4).First();

						Context.EntitiesZeroManyToMany1MFluentAPI.Remove(EntityM1);
						Context.EntitiesZeroManyToMany1MFluentAPI.Remove(EntityM2);
						Context.EntitiesZeroManyToMany1NFluentAPI.Remove(EntityN1);
						Context.EntitiesZeroManyToMany1NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroManyToMany1MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany1MNFluentAPI		EntityMN1=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID1).First();
						CEntityZeroManyToMany1MNFluentAPI		EntityMN2=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID2).First();
						CEntityZeroManyToMany1MNFluentAPI		EntityMN3=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID3).First();
						CEntityZeroManyToMany1MNFluentAPI		EntityMN4=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID4).First();

						Context.EntitiesZeroManyToMany1MNFluentAPI.Remove(EntityMN1);
						Context.EntitiesZeroManyToMany1MNFluentAPI.Remove(EntityMN2);
						Context.EntitiesZeroManyToMany1MNFluentAPI.Remove(EntityMN3);
						Context.EntitiesZeroManyToMany1MNFluentAPI.Remove(EntityMN4);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany1MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityZeroManyToMany1MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityZeroManyToMany1NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityZeroManyToMany1MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestZeroManyToMany2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;
			int													PrincipalID3=0;
			int													PrincipalID4=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;
			int													DependentID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany2MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroManyToMany2MFluentAPI		EntityZeroManyToMany2MFluentAPI1=new CEntityZeroManyToMany2MFluentAPI("NEW ENTITY M - 333");
						CEntityZeroManyToMany2MFluentAPI		EntityZeroManyToMany2MFluentAPI2=new CEntityZeroManyToMany2MFluentAPI("NEW ENTITY M - 444");

						CEntityZeroManyToMany2NFluentAPI		EntityZeroManyToMany2NFluentAPI1=new CEntityZeroManyToMany2NFluentAPI("NEW ENTITY N - 333");
						CEntityZeroManyToMany2NFluentAPI		EntityZeroManyToMany2NFluentAPI2=new CEntityZeroManyToMany2NFluentAPI("NEW ENTITY N - 444");

						CEntityZeroManyToMany2MNFluentAPI		EntityZeroManyToMany2MNFluentAPI11=new CEntityZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 33");
						CEntityZeroManyToMany2MNFluentAPI		EntityZeroManyToMany2MNFluentAPI12=new CEntityZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 34");
						CEntityZeroManyToMany2MNFluentAPI		EntityZeroManyToMany2MNFluentAPI21=new CEntityZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 43");
						CEntityZeroManyToMany2MNFluentAPI		EntityZeroManyToMany2MNFluentAPI22=new CEntityZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 44");

						EntityZeroManyToMany2MNFluentAPI11.EntityM=EntityZeroManyToMany2MFluentAPI1;
						EntityZeroManyToMany2MNFluentAPI11.EntityN=EntityZeroManyToMany2NFluentAPI1;

						EntityZeroManyToMany2MNFluentAPI12.EntityM=EntityZeroManyToMany2MFluentAPI1;
						EntityZeroManyToMany2MNFluentAPI12.EntityN=EntityZeroManyToMany2NFluentAPI2;

						EntityZeroManyToMany2MNFluentAPI21.EntityM=EntityZeroManyToMany2MFluentAPI2;
						EntityZeroManyToMany2MNFluentAPI21.EntityN=EntityZeroManyToMany2NFluentAPI1;

						EntityZeroManyToMany2MNFluentAPI22.EntityM=EntityZeroManyToMany2MFluentAPI2;
						EntityZeroManyToMany2MNFluentAPI22.EntityN=EntityZeroManyToMany2NFluentAPI2;

						Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI11);
						Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI12);
						Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI21);
						Context.EntitiesZeroManyToMany2MNFluentAPI.Add(EntityZeroManyToMany2MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=EntityZeroManyToMany2MFluentAPI1.EntityMID;
							PrincipalID2=EntityZeroManyToMany2MFluentAPI2.EntityMID;
							PrincipalID3=EntityZeroManyToMany2NFluentAPI1.EntityNID;
							PrincipalID4=EntityZeroManyToMany2NFluentAPI2.EntityNID;
							DependentID1=EntityZeroManyToMany2MNFluentAPI11.EntityMNID;
							DependentID2=EntityZeroManyToMany2MNFluentAPI12.EntityMNID;
							DependentID3=EntityZeroManyToMany2MNFluentAPI21.EntityMNID;
							DependentID4=EntityZeroManyToMany2MNFluentAPI22.EntityMNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany2MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroManyToMany2MFluentAPI		EntityM1=Context.EntitiesZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID1).First();
						CEntityZeroManyToMany2MFluentAPI		EntityM2=Context.EntitiesZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID2).First();
						CEntityZeroManyToMany2NFluentAPI		EntityN1=Context.EntitiesZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID3).First();
						CEntityZeroManyToMany2NFluentAPI		EntityN2=Context.EntitiesZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID4).First();

						Context.EntitiesZeroManyToMany2MFluentAPI.Remove(EntityM1);
						Context.EntitiesZeroManyToMany2MFluentAPI.Remove(EntityM2);
						Context.EntitiesZeroManyToMany2NFluentAPI.Remove(EntityN1);
						Context.EntitiesZeroManyToMany2NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityZeroManyToMany2MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany2MNFluentAPI		EntityMN1=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID1).First();
						CEntityZeroManyToMany2MNFluentAPI		EntityMN2=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID2).First();
						CEntityZeroManyToMany2MNFluentAPI		EntityMN3=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID3).First();
						CEntityZeroManyToMany2MNFluentAPI		EntityMN4=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID4).First();

						Context.EntitiesZeroManyToMany2MNFluentAPI.Remove(EntityMN1);
						Context.EntitiesZeroManyToMany2MNFluentAPI.Remove(EntityMN2);
						Context.EntitiesZeroManyToMany2MNFluentAPI.Remove(EntityMN3);
						Context.EntitiesZeroManyToMany2MNFluentAPI.Remove(EntityMN4);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityZeroManyToMany2MFluentAPI[]		Entities1=Context.EntitiesZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2NFluentAPI[]		Entities2=Context.EntitiesZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityZeroManyToMany2MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityZeroManyToMany2NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityZeroManyToMany2MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestManyToManyMixedKeys1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys1MFluentAPI[]	Entities1=Context.EntitiesManyToManyMixedKeys1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys1NFluentAPI[]	Entities2=Context.EntitiesManyToManyMixedKeys1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyMixedKeys1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys1MNFluentAPI[]	Entities3=Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToManyMixedKeys1MFluentAPI	EntityManyToManyMixedKeys1MFluentAPI1=new CEntityManyToManyMixedKeys1MFluentAPI("NEW ENTITY M - 333");
						CEntityManyToManyMixedKeys1MFluentAPI	EntityManyToManyMixedKeys1MFluentAPI2=new CEntityManyToManyMixedKeys1MFluentAPI("NEW ENTITY M - 444");

						CEntityManyToManyMixedKeys1NFluentAPI	EntityManyToManyMixedKeys1NFluentAPI1=new CEntityManyToManyMixedKeys1NFluentAPI("NEW ENTITY N - 333");
						CEntityManyToManyMixedKeys1NFluentAPI	EntityManyToManyMixedKeys1NFluentAPI2=new CEntityManyToManyMixedKeys1NFluentAPI("NEW ENTITY N - 444");

						CEntityManyToManyMixedKeys1MNFluentAPI	EntityManyToManyMixedKeys1MNFluentAPI11=new CEntityManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 33");
						CEntityManyToManyMixedKeys1MNFluentAPI	EntityManyToManyMixedKeys1MNFluentAPI12=new CEntityManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 34");
						CEntityManyToManyMixedKeys1MNFluentAPI	EntityManyToManyMixedKeys1MNFluentAPI21=new CEntityManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 43");
						CEntityManyToManyMixedKeys1MNFluentAPI	EntityManyToManyMixedKeys1MNFluentAPI22=new CEntityManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 44");

						EntityManyToManyMixedKeys1MNFluentAPI11.EntityM=EntityManyToManyMixedKeys1MFluentAPI1;
						EntityManyToManyMixedKeys1MNFluentAPI11.EntityN=EntityManyToManyMixedKeys1NFluentAPI1;

						EntityManyToManyMixedKeys1MNFluentAPI12.EntityM=EntityManyToManyMixedKeys1MFluentAPI1;
						EntityManyToManyMixedKeys1MNFluentAPI12.EntityN=EntityManyToManyMixedKeys1NFluentAPI2;

						EntityManyToManyMixedKeys1MNFluentAPI21.EntityM=EntityManyToManyMixedKeys1MFluentAPI2;
						EntityManyToManyMixedKeys1MNFluentAPI21.EntityN=EntityManyToManyMixedKeys1NFluentAPI1;

						EntityManyToManyMixedKeys1MNFluentAPI22.EntityM=EntityManyToManyMixedKeys1MFluentAPI2;
						EntityManyToManyMixedKeys1MNFluentAPI22.EntityN=EntityManyToManyMixedKeys1NFluentAPI2;

						Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI11);
						Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI12);
						Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI21);
						Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Add(EntityManyToManyMixedKeys1MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityManyToManyMixedKeys1MFluentAPI1.EntityMID;
							ID2=EntityManyToManyMixedKeys1MFluentAPI2.EntityMID;
							ID3=EntityManyToManyMixedKeys1NFluentAPI1.EntityNID;
							ID4=EntityManyToManyMixedKeys1NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys1MFluentAPI[]	Entities1=Context.EntitiesManyToManyMixedKeys1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys1NFluentAPI[]	Entities2=Context.EntitiesManyToManyMixedKeys1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyMixedKeys1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys1MNFluentAPI[]	Entities3=Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys1MFluentAPI	EntityM1=Context.EntitiesManyToManyMixedKeys1MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyMixedKeys1MFluentAPI	EntityM2=Context.EntitiesManyToManyMixedKeys1MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyMixedKeys1NFluentAPI	EntityN1=Context.EntitiesManyToManyMixedKeys1NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyMixedKeys1NFluentAPI	EntityN2=Context.EntitiesManyToManyMixedKeys1NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToManyMixedKeys1MFluentAPI.Remove(EntityM1);
						Context.EntitiesManyToManyMixedKeys1MFluentAPI.Remove(EntityM2);
						Context.EntitiesManyToManyMixedKeys1NFluentAPI.Remove(EntityN1);
						Context.EntitiesManyToManyMixedKeys1NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys1MFluentAPI[]	Entities1=Context.EntitiesManyToManyMixedKeys1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys1NFluentAPI[]	Entities2=Context.EntitiesManyToManyMixedKeys1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyMixedKeys1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys1MNFluentAPI[]	Entities3=Context.EntitiesManyToManyMixedKeys1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityManyToManyMixedKeys1MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityManyToManyMixedKeys1NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityManyToManyMixedKeys1MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestManyToManyMixedKeys2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys2MFluentAPI[]	Entities1=Context.EntitiesManyToManyMixedKeys2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys2NFluentAPI[]	Entities2=Context.EntitiesManyToManyMixedKeys2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyMixedKeys2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys2MNFluentAPI[]	Entities3=Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToManyMixedKeys2MFluentAPI	EntityManyToManyMixedKeys2MFluentAPI1=new CEntityManyToManyMixedKeys2MFluentAPI("NEW ENTITY M - 333");
						CEntityManyToManyMixedKeys2MFluentAPI	EntityManyToManyMixedKeys2MFluentAPI2=new CEntityManyToManyMixedKeys2MFluentAPI("NEW ENTITY M - 444");

						CEntityManyToManyMixedKeys2NFluentAPI	EntityManyToManyMixedKeys2NFluentAPI1=new CEntityManyToManyMixedKeys2NFluentAPI("NEW ENTITY N - 333");
						CEntityManyToManyMixedKeys2NFluentAPI	EntityManyToManyMixedKeys2NFluentAPI2=new CEntityManyToManyMixedKeys2NFluentAPI("NEW ENTITY N - 444");

						CEntityManyToManyMixedKeys2MNFluentAPI	EntityManyToManyMixedKeys2MNFluentAPI11=new CEntityManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 33");
						CEntityManyToManyMixedKeys2MNFluentAPI	EntityManyToManyMixedKeys2MNFluentAPI12=new CEntityManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 34");
						CEntityManyToManyMixedKeys2MNFluentAPI	EntityManyToManyMixedKeys2MNFluentAPI21=new CEntityManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 43");
						CEntityManyToManyMixedKeys2MNFluentAPI	EntityManyToManyMixedKeys2MNFluentAPI22=new CEntityManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 44");

						EntityManyToManyMixedKeys2MNFluentAPI11.EntityM=EntityManyToManyMixedKeys2MFluentAPI1;
						EntityManyToManyMixedKeys2MNFluentAPI11.EntityN=EntityManyToManyMixedKeys2NFluentAPI1;

						EntityManyToManyMixedKeys2MNFluentAPI12.EntityM=EntityManyToManyMixedKeys2MFluentAPI1;
						EntityManyToManyMixedKeys2MNFluentAPI12.EntityN=EntityManyToManyMixedKeys2NFluentAPI2;

						EntityManyToManyMixedKeys2MNFluentAPI21.EntityM=EntityManyToManyMixedKeys2MFluentAPI2;
						EntityManyToManyMixedKeys2MNFluentAPI21.EntityN=EntityManyToManyMixedKeys2NFluentAPI1;

						EntityManyToManyMixedKeys2MNFluentAPI22.EntityM=EntityManyToManyMixedKeys2MFluentAPI2;
						EntityManyToManyMixedKeys2MNFluentAPI22.EntityN=EntityManyToManyMixedKeys2NFluentAPI2;

						Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI11);
						Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI12);
						Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI21);
						Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Add(EntityManyToManyMixedKeys2MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityManyToManyMixedKeys2MFluentAPI1.EntityMID;
							ID2=EntityManyToManyMixedKeys2MFluentAPI2.EntityMID;
							ID3=EntityManyToManyMixedKeys2NFluentAPI1.EntityNID;
							ID4=EntityManyToManyMixedKeys2NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys2MFluentAPI[]	Entities1=Context.EntitiesManyToManyMixedKeys2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys2NFluentAPI[]	Entities2=Context.EntitiesManyToManyMixedKeys2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyMixedKeys2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys2MNFluentAPI[]	Entities3=Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys2MFluentAPI	EntityM1=Context.EntitiesManyToManyMixedKeys2MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyMixedKeys2MFluentAPI	EntityM2=Context.EntitiesManyToManyMixedKeys2MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyMixedKeys2NFluentAPI	EntityN1=Context.EntitiesManyToManyMixedKeys2NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyMixedKeys2NFluentAPI	EntityN2=Context.EntitiesManyToManyMixedKeys2NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToManyMixedKeys2MFluentAPI.Remove(EntityM1);
						Context.EntitiesManyToManyMixedKeys2MFluentAPI.Remove(EntityM2);
						Context.EntitiesManyToManyMixedKeys2NFluentAPI.Remove(EntityN1);
						Context.EntitiesManyToManyMixedKeys2NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityManyToManyMixedKeys2MFluentAPI[]	Entities1=Context.EntitiesManyToManyMixedKeys2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys2NFluentAPI[]	Entities2=Context.EntitiesManyToManyMixedKeys2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyMixedKeys2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMixedKeys2MNFluentAPI[]	Entities3=Context.EntitiesManyToManyMixedKeys2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMixedKeys2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityManyToManyMixedKeys2MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityManyToManyMixedKeys2NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityManyToManyMixedKeys2MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutoManyToMany1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToMany1MFluentAPI[]		Entities1=Context.EntitiesAutoManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany1NFluentAPI[]		Entities2=Context.EntitiesAutoManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesAutoManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityAutoManyToMany1MFluentAPI		EntityAutoManyToMany1MFluentAPI1=new CEntityAutoManyToMany1MFluentAPI("NEW ENTITY M - 333");
						CEntityAutoManyToMany1MFluentAPI		EntityAutoManyToMany1MFluentAPI2=new CEntityAutoManyToMany1MFluentAPI("NEW ENTITY M - 444");

						CEntityAutoManyToMany1NFluentAPI		EntityAutoManyToMany1NFluentAPI1=new CEntityAutoManyToMany1NFluentAPI("NEW ENTITY N - 333");
						CEntityAutoManyToMany1NFluentAPI		EntityAutoManyToMany1NFluentAPI2=new CEntityAutoManyToMany1NFluentAPI("NEW ENTITY N - 444");

						CEntityAutoManyToMany1MNFluentAPI		EntityAutoManyToMany1MNFluentAPI11=new CEntityAutoManyToMany1MNFluentAPI("NEW ENTITY MN - 33");
						CEntityAutoManyToMany1MNFluentAPI		EntityAutoManyToMany1MNFluentAPI12=new CEntityAutoManyToMany1MNFluentAPI("NEW ENTITY MN - 34");
						CEntityAutoManyToMany1MNFluentAPI		EntityAutoManyToMany1MNFluentAPI21=new CEntityAutoManyToMany1MNFluentAPI("NEW ENTITY MN - 43");
						CEntityAutoManyToMany1MNFluentAPI		EntityAutoManyToMany1MNFluentAPI22=new CEntityAutoManyToMany1MNFluentAPI("NEW ENTITY MN - 44");

						EntityAutoManyToMany1MNFluentAPI11.EntityM=EntityAutoManyToMany1MFluentAPI1;
						EntityAutoManyToMany1MNFluentAPI11.EntityN=EntityAutoManyToMany1NFluentAPI1;

						EntityAutoManyToMany1MNFluentAPI12.EntityM=EntityAutoManyToMany1MFluentAPI1;
						EntityAutoManyToMany1MNFluentAPI12.EntityN=EntityAutoManyToMany1NFluentAPI2;

						EntityAutoManyToMany1MNFluentAPI21.EntityM=EntityAutoManyToMany1MFluentAPI2;
						EntityAutoManyToMany1MNFluentAPI21.EntityN=EntityAutoManyToMany1NFluentAPI1;

						EntityAutoManyToMany1MNFluentAPI22.EntityM=EntityAutoManyToMany1MFluentAPI2;
						EntityAutoManyToMany1MNFluentAPI22.EntityN=EntityAutoManyToMany1NFluentAPI2;

						Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI11);
						Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI12);
						Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI21);
						Context.EntitiesAutoManyToMany1MNFluentAPI.Add(EntityAutoManyToMany1MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityAutoManyToMany1MFluentAPI1.EntityMID;
							ID2=EntityAutoManyToMany1MFluentAPI2.EntityMID;
							ID3=EntityAutoManyToMany1NFluentAPI1.EntityNID;
							ID4=EntityAutoManyToMany1NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToMany1MFluentAPI[]		Entities1=Context.EntitiesAutoManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany1NFluentAPI[]		Entities2=Context.EntitiesAutoManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesAutoManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityAutoManyToMany1MFluentAPI		EntityM1=Context.EntitiesAutoManyToMany1MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityAutoManyToMany1MFluentAPI		EntityM2=Context.EntitiesAutoManyToMany1MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityAutoManyToMany1NFluentAPI		EntityN1=Context.EntitiesAutoManyToMany1NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityAutoManyToMany1NFluentAPI		EntityN2=Context.EntitiesAutoManyToMany1NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesAutoManyToMany1MFluentAPI.Remove(EntityM1);
						Context.EntitiesAutoManyToMany1MFluentAPI.Remove(EntityM2);
						Context.EntitiesAutoManyToMany1NFluentAPI.Remove(EntityN1);
						Context.EntitiesAutoManyToMany1NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityAutoManyToMany1MFluentAPI[]		Entities1=Context.EntitiesAutoManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany1NFluentAPI[]		Entities2=Context.EntitiesAutoManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany1MNFluentAPI[]		Entities3=Context.EntitiesAutoManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityAutoManyToMany1MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToMany1NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToMany1MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutoManyToMany2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToMany2MFluentAPI[]		Entities1=Context.EntitiesAutoManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany2NFluentAPI[]		Entities2=Context.EntitiesAutoManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesAutoManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityAutoManyToMany2MFluentAPI		EntityAutoManyToMany2MFluentAPI1=new CEntityAutoManyToMany2MFluentAPI("NEW ENTITY M - 333");
						CEntityAutoManyToMany2MFluentAPI		EntityAutoManyToMany2MFluentAPI2=new CEntityAutoManyToMany2MFluentAPI("NEW ENTITY M - 444");

						CEntityAutoManyToMany2NFluentAPI		EntityAutoManyToMany2NFluentAPI1=new CEntityAutoManyToMany2NFluentAPI("NEW ENTITY N - 333");
						CEntityAutoManyToMany2NFluentAPI		EntityAutoManyToMany2NFluentAPI2=new CEntityAutoManyToMany2NFluentAPI("NEW ENTITY N - 444");

						CEntityAutoManyToMany2MNFluentAPI		EntityAutoManyToMany2MNFluentAPI11=new CEntityAutoManyToMany2MNFluentAPI("NEW ENTITY MN - 33");
						CEntityAutoManyToMany2MNFluentAPI		EntityAutoManyToMany2MNFluentAPI12=new CEntityAutoManyToMany2MNFluentAPI("NEW ENTITY MN - 34");
						CEntityAutoManyToMany2MNFluentAPI		EntityAutoManyToMany2MNFluentAPI21=new CEntityAutoManyToMany2MNFluentAPI("NEW ENTITY MN - 43");
						CEntityAutoManyToMany2MNFluentAPI		EntityAutoManyToMany2MNFluentAPI22=new CEntityAutoManyToMany2MNFluentAPI("NEW ENTITY MN - 44");

						EntityAutoManyToMany2MNFluentAPI11.EntityM=EntityAutoManyToMany2MFluentAPI1;
						EntityAutoManyToMany2MNFluentAPI11.EntityN=EntityAutoManyToMany2NFluentAPI1;

						EntityAutoManyToMany2MNFluentAPI12.EntityM=EntityAutoManyToMany2MFluentAPI1;
						EntityAutoManyToMany2MNFluentAPI12.EntityN=EntityAutoManyToMany2NFluentAPI2;

						EntityAutoManyToMany2MNFluentAPI21.EntityM=EntityAutoManyToMany2MFluentAPI2;
						EntityAutoManyToMany2MNFluentAPI21.EntityN=EntityAutoManyToMany2NFluentAPI1;

						EntityAutoManyToMany2MNFluentAPI22.EntityM=EntityAutoManyToMany2MFluentAPI2;
						EntityAutoManyToMany2MNFluentAPI22.EntityN=EntityAutoManyToMany2NFluentAPI2;

						Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI11);
						Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI12);
						Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI21);
						Context.EntitiesAutoManyToMany2MNFluentAPI.Add(EntityAutoManyToMany2MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityAutoManyToMany2MFluentAPI1.EntityMID;
							ID2=EntityAutoManyToMany2MFluentAPI2.EntityMID;
							ID3=EntityAutoManyToMany2NFluentAPI1.EntityNID;
							ID4=EntityAutoManyToMany2NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToMany2MFluentAPI[]		Entities1=Context.EntitiesAutoManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany2NFluentAPI[]		Entities2=Context.EntitiesAutoManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesAutoManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityAutoManyToMany2MFluentAPI		EntityM1=Context.EntitiesAutoManyToMany2MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityAutoManyToMany2MFluentAPI		EntityM2=Context.EntitiesAutoManyToMany2MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityAutoManyToMany2NFluentAPI		EntityN1=Context.EntitiesAutoManyToMany2NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityAutoManyToMany2NFluentAPI		EntityN2=Context.EntitiesAutoManyToMany2NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesAutoManyToMany2MFluentAPI.Remove(EntityM1);
						Context.EntitiesAutoManyToMany2MFluentAPI.Remove(EntityM2);
						Context.EntitiesAutoManyToMany2NFluentAPI.Remove(EntityN1);
						Context.EntitiesAutoManyToMany2NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityAutoManyToMany2MFluentAPI[]		Entities1=Context.EntitiesAutoManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany2NFluentAPI[]		Entities2=Context.EntitiesAutoManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToMany2MNFluentAPI[]		Entities3=Context.EntitiesAutoManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityAutoManyToMany2MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToMany2NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToMany2MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutoZeroManyToMany1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;
			int													PrincipalID3=0;
			int													PrincipalID4=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;
			int													DependentID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany1MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityAutoZeroManyToMany1MFluentAPI	EntityAutoZeroManyToMany1MFluentAPI1=new CEntityAutoZeroManyToMany1MFluentAPI("NEW ENTITY M - 333");
						CEntityAutoZeroManyToMany1MFluentAPI	EntityAutoZeroManyToMany1MFluentAPI2=new CEntityAutoZeroManyToMany1MFluentAPI("NEW ENTITY M - 444");

						CEntityAutoZeroManyToMany1NFluentAPI	EntityAutoZeroManyToMany1NFluentAPI1=new CEntityAutoZeroManyToMany1NFluentAPI("NEW ENTITY N - 333");
						CEntityAutoZeroManyToMany1NFluentAPI	EntityAutoZeroManyToMany1NFluentAPI2=new CEntityAutoZeroManyToMany1NFluentAPI("NEW ENTITY N - 444");

						CEntityAutoZeroManyToMany1MNFluentAPI	EntityAutoZeroManyToMany1MNFluentAPI11=new CEntityAutoZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 33");
						CEntityAutoZeroManyToMany1MNFluentAPI	EntityAutoZeroManyToMany1MNFluentAPI12=new CEntityAutoZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 34");
						CEntityAutoZeroManyToMany1MNFluentAPI	EntityAutoZeroManyToMany1MNFluentAPI21=new CEntityAutoZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 43");
						CEntityAutoZeroManyToMany1MNFluentAPI	EntityAutoZeroManyToMany1MNFluentAPI22=new CEntityAutoZeroManyToMany1MNFluentAPI("NEW ENTITY MN - 44");

						EntityAutoZeroManyToMany1MNFluentAPI11.EntityM=EntityAutoZeroManyToMany1MFluentAPI1;
						EntityAutoZeroManyToMany1MNFluentAPI11.EntityN=EntityAutoZeroManyToMany1NFluentAPI1;

						EntityAutoZeroManyToMany1MNFluentAPI12.EntityM=EntityAutoZeroManyToMany1MFluentAPI1;
						EntityAutoZeroManyToMany1MNFluentAPI12.EntityN=EntityAutoZeroManyToMany1NFluentAPI2;

						EntityAutoZeroManyToMany1MNFluentAPI21.EntityM=EntityAutoZeroManyToMany1MFluentAPI2;
						EntityAutoZeroManyToMany1MNFluentAPI21.EntityN=EntityAutoZeroManyToMany1NFluentAPI1;

						EntityAutoZeroManyToMany1MNFluentAPI22.EntityM=EntityAutoZeroManyToMany1MFluentAPI2;
						EntityAutoZeroManyToMany1MNFluentAPI22.EntityN=EntityAutoZeroManyToMany1NFluentAPI2;

						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI11);
						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI12);
						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI21);
						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Add(EntityAutoZeroManyToMany1MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=EntityAutoZeroManyToMany1MFluentAPI1.EntityMID;
							PrincipalID2=EntityAutoZeroManyToMany1MFluentAPI2.EntityMID;
							PrincipalID3=EntityAutoZeroManyToMany1NFluentAPI1.EntityNID;
							PrincipalID4=EntityAutoZeroManyToMany1NFluentAPI2.EntityNID;
							DependentID1=EntityAutoZeroManyToMany1MNFluentAPI11.EntityMNID;
							DependentID2=EntityAutoZeroManyToMany1MNFluentAPI12.EntityMNID;
							DependentID3=EntityAutoZeroManyToMany1MNFluentAPI21.EntityMNID;
							DependentID4=EntityAutoZeroManyToMany1MNFluentAPI22.EntityMNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany1MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany1MFluentAPI	EntityM1=Context.EntitiesAutoZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID1).First();
						CEntityAutoZeroManyToMany1MFluentAPI	EntityM2=Context.EntitiesAutoZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID2).First();
						CEntityAutoZeroManyToMany1NFluentAPI	EntityN1=Context.EntitiesAutoZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID3).First();
						CEntityAutoZeroManyToMany1NFluentAPI	EntityN2=Context.EntitiesAutoZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID4).First();

						Context.EntitiesAutoZeroManyToMany1MFluentAPI.Remove(EntityM1);
						Context.EntitiesAutoZeroManyToMany1MFluentAPI.Remove(EntityM2);
						Context.EntitiesAutoZeroManyToMany1NFluentAPI.Remove(EntityN1);
						Context.EntitiesAutoZeroManyToMany1NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany1MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany1MNFluentAPI	EntityMN1=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID1).First();
						CEntityAutoZeroManyToMany1MNFluentAPI	EntityMN2=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID2).First();
						CEntityAutoZeroManyToMany1MNFluentAPI	EntityMN3=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID3).First();
						CEntityAutoZeroManyToMany1MNFluentAPI	EntityMN4=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID4).First();

						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Remove(EntityMN1);
						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Remove(EntityMN2);
						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Remove(EntityMN3);
						Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Remove(EntityMN4);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany1MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany1MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityAutoZeroManyToMany1MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityAutoZeroManyToMany1NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityAutoZeroManyToMany1MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutoZeroManyToMany2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;
			int													PrincipalID3=0;
			int													PrincipalID4=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;
			int													DependentID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany2MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityAutoZeroManyToMany2MFluentAPI	EntityAutoZeroManyToMany2MFluentAPI1=new CEntityAutoZeroManyToMany2MFluentAPI("NEW ENTITY M - 333");
						CEntityAutoZeroManyToMany2MFluentAPI	EntityAutoZeroManyToMany2MFluentAPI2=new CEntityAutoZeroManyToMany2MFluentAPI("NEW ENTITY M - 444");

						CEntityAutoZeroManyToMany2NFluentAPI	EntityAutoZeroManyToMany2NFluentAPI1=new CEntityAutoZeroManyToMany2NFluentAPI("NEW ENTITY N - 333");
						CEntityAutoZeroManyToMany2NFluentAPI	EntityAutoZeroManyToMany2NFluentAPI2=new CEntityAutoZeroManyToMany2NFluentAPI("NEW ENTITY N - 444");

						CEntityAutoZeroManyToMany2MNFluentAPI	EntityAutoZeroManyToMany2MNFluentAPI11=new CEntityAutoZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 33");
						CEntityAutoZeroManyToMany2MNFluentAPI	EntityAutoZeroManyToMany2MNFluentAPI12=new CEntityAutoZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 34");
						CEntityAutoZeroManyToMany2MNFluentAPI	EntityAutoZeroManyToMany2MNFluentAPI21=new CEntityAutoZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 43");
						CEntityAutoZeroManyToMany2MNFluentAPI	EntityAutoZeroManyToMany2MNFluentAPI22=new CEntityAutoZeroManyToMany2MNFluentAPI("NEW ENTITY MN - 44");

						EntityAutoZeroManyToMany2MNFluentAPI11.EntityM=EntityAutoZeroManyToMany2MFluentAPI1;
						EntityAutoZeroManyToMany2MNFluentAPI11.EntityN=EntityAutoZeroManyToMany2NFluentAPI1;

						EntityAutoZeroManyToMany2MNFluentAPI12.EntityM=EntityAutoZeroManyToMany2MFluentAPI1;
						EntityAutoZeroManyToMany2MNFluentAPI12.EntityN=EntityAutoZeroManyToMany2NFluentAPI2;

						EntityAutoZeroManyToMany2MNFluentAPI21.EntityM=EntityAutoZeroManyToMany2MFluentAPI2;
						EntityAutoZeroManyToMany2MNFluentAPI21.EntityN=EntityAutoZeroManyToMany2NFluentAPI1;

						EntityAutoZeroManyToMany2MNFluentAPI22.EntityM=EntityAutoZeroManyToMany2MFluentAPI2;
						EntityAutoZeroManyToMany2MNFluentAPI22.EntityN=EntityAutoZeroManyToMany2NFluentAPI2;

						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI11);
						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI12);
						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI21);
						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Add(EntityAutoZeroManyToMany2MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=EntityAutoZeroManyToMany2MFluentAPI1.EntityMID;
							PrincipalID2=EntityAutoZeroManyToMany2MFluentAPI2.EntityMID;
							PrincipalID3=EntityAutoZeroManyToMany2NFluentAPI1.EntityNID;
							PrincipalID4=EntityAutoZeroManyToMany2NFluentAPI2.EntityNID;
							DependentID1=EntityAutoZeroManyToMany2MNFluentAPI11.EntityMNID;
							DependentID2=EntityAutoZeroManyToMany2MNFluentAPI12.EntityMNID;
							DependentID3=EntityAutoZeroManyToMany2MNFluentAPI21.EntityMNID;
							DependentID4=EntityAutoZeroManyToMany2MNFluentAPI22.EntityMNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany2MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany2MFluentAPI	EntityM1=Context.EntitiesAutoZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID1).First();
						CEntityAutoZeroManyToMany2MFluentAPI	EntityM2=Context.EntitiesAutoZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==PrincipalID2).First();
						CEntityAutoZeroManyToMany2NFluentAPI	EntityN1=Context.EntitiesAutoZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID3).First();
						CEntityAutoZeroManyToMany2NFluentAPI	EntityN2=Context.EntitiesAutoZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==PrincipalID4).First();

						Context.EntitiesAutoZeroManyToMany2MFluentAPI.Remove(EntityM1);
						Context.EntitiesAutoZeroManyToMany2MFluentAPI.Remove(EntityM2);
						Context.EntitiesAutoZeroManyToMany2NFluentAPI.Remove(EntityN1);
						Context.EntitiesAutoZeroManyToMany2NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany2MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany2MNFluentAPI	EntityMN1=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID1).First();
						CEntityAutoZeroManyToMany2MNFluentAPI	EntityMN2=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID2).First();
						CEntityAutoZeroManyToMany2MNFluentAPI	EntityMN3=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID3).First();
						CEntityAutoZeroManyToMany2MNFluentAPI	EntityMN4=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==DependentID4).First();

						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Remove(EntityMN1);
						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Remove(EntityMN2);
						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Remove(EntityMN3);
						Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Remove(EntityMN4);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityAutoZeroManyToMany2MFluentAPI[]	Entities1=Context.EntitiesAutoZeroManyToMany2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2NFluentAPI[]	Entities2=Context.EntitiesAutoZeroManyToMany2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoZeroManyToMany2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoZeroManyToMany2MNFluentAPI[]	Entities3=Context.EntitiesAutoZeroManyToMany2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoZeroManyToMany2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityAutoZeroManyToMany2MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityAutoZeroManyToMany2NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityAutoZeroManyToMany2MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutoManyToManyMixedKeys1FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys1MFluentAPI[]	Entities1=Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys1NFluentAPI[]	Entities2=Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToManyMixedKeys1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys1MNFluentAPI[]	Entities3=Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityAutoManyToManyMixedKeys1MFluentAPI	EntityAutoManyToManyMixedKeys1MFluentAPI1=new CEntityAutoManyToManyMixedKeys1MFluentAPI("NEW ENTITY M - 333");
						CEntityAutoManyToManyMixedKeys1MFluentAPI	EntityAutoManyToManyMixedKeys1MFluentAPI2=new CEntityAutoManyToManyMixedKeys1MFluentAPI("NEW ENTITY M - 444");

						CEntityAutoManyToManyMixedKeys1NFluentAPI	EntityAutoManyToManyMixedKeys1NFluentAPI1=new CEntityAutoManyToManyMixedKeys1NFluentAPI("NEW ENTITY N - 333");
						CEntityAutoManyToManyMixedKeys1NFluentAPI	EntityAutoManyToManyMixedKeys1NFluentAPI2=new CEntityAutoManyToManyMixedKeys1NFluentAPI("NEW ENTITY N - 444");

						CEntityAutoManyToManyMixedKeys1MNFluentAPI	EntityAutoManyToManyMixedKeys1MNFluentAPI11=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 33");
						CEntityAutoManyToManyMixedKeys1MNFluentAPI	EntityAutoManyToManyMixedKeys1MNFluentAPI12=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 34");
						CEntityAutoManyToManyMixedKeys1MNFluentAPI	EntityAutoManyToManyMixedKeys1MNFluentAPI21=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 43");
						CEntityAutoManyToManyMixedKeys1MNFluentAPI	EntityAutoManyToManyMixedKeys1MNFluentAPI22=new CEntityAutoManyToManyMixedKeys1MNFluentAPI("NEW ENTITY MN - 44");

						EntityAutoManyToManyMixedKeys1MNFluentAPI11.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI1;
						EntityAutoManyToManyMixedKeys1MNFluentAPI11.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI1;

						EntityAutoManyToManyMixedKeys1MNFluentAPI12.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI1;
						EntityAutoManyToManyMixedKeys1MNFluentAPI12.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI2;

						EntityAutoManyToManyMixedKeys1MNFluentAPI21.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI2;
						EntityAutoManyToManyMixedKeys1MNFluentAPI21.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI1;

						EntityAutoManyToManyMixedKeys1MNFluentAPI22.EntityM=EntityAutoManyToManyMixedKeys1MFluentAPI2;
						EntityAutoManyToManyMixedKeys1MNFluentAPI22.EntityN=EntityAutoManyToManyMixedKeys1NFluentAPI2;

						Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI11);
						Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI12);
						Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI21);
						Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Add(EntityAutoManyToManyMixedKeys1MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityAutoManyToManyMixedKeys1MFluentAPI1.EntityMID;
							ID2=EntityAutoManyToManyMixedKeys1MFluentAPI2.EntityMID;
							ID3=EntityAutoManyToManyMixedKeys1NFluentAPI1.EntityNID;
							ID4=EntityAutoManyToManyMixedKeys1NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys1MFluentAPI[]	Entities1=Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys1NFluentAPI[]	Entities2=Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToManyMixedKeys1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys1MNFluentAPI[]	Entities3=Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys1MFluentAPI	EntityM1=Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityAutoManyToManyMixedKeys1MFluentAPI	EntityM2=Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityAutoManyToManyMixedKeys1NFluentAPI	EntityN1=Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityAutoManyToManyMixedKeys1NFluentAPI	EntityN2=Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Remove(EntityM1);
						Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Remove(EntityM2);
						Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Remove(EntityN1);
						Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys1MFluentAPI[]	Entities1=Context.EntitiesAutoManyToManyMixedKeys1MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys1MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys1NFluentAPI[]	Entities2=Context.EntitiesAutoManyToManyMixedKeys1NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToManyMixedKeys1NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys1MNFluentAPI[]	Entities3=Context.EntitiesAutoManyToManyMixedKeys1MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys1MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityAutoManyToManyMixedKeys1MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToManyMixedKeys1NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToManyMixedKeys1MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutoManyToManyMixedKeys2FluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys2MFluentAPI[]	Entities1=Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys2NFluentAPI[]	Entities2=Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToManyMixedKeys2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys2MNFluentAPI[]	Entities3=Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityAutoManyToManyMixedKeys2MFluentAPI	EntityAutoManyToManyMixedKeys2MFluentAPI1=new CEntityAutoManyToManyMixedKeys2MFluentAPI("NEW ENTITY M - 333");
						CEntityAutoManyToManyMixedKeys2MFluentAPI	EntityAutoManyToManyMixedKeys2MFluentAPI2=new CEntityAutoManyToManyMixedKeys2MFluentAPI("NEW ENTITY M - 444");

						CEntityAutoManyToManyMixedKeys2NFluentAPI	EntityAutoManyToManyMixedKeys2NFluentAPI1=new CEntityAutoManyToManyMixedKeys2NFluentAPI("NEW ENTITY N - 333");
						CEntityAutoManyToManyMixedKeys2NFluentAPI	EntityAutoManyToManyMixedKeys2NFluentAPI2=new CEntityAutoManyToManyMixedKeys2NFluentAPI("NEW ENTITY N - 444");

						CEntityAutoManyToManyMixedKeys2MNFluentAPI	EntityAutoManyToManyMixedKeys2MNFluentAPI11=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 33");
						CEntityAutoManyToManyMixedKeys2MNFluentAPI	EntityAutoManyToManyMixedKeys2MNFluentAPI12=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 34");
						CEntityAutoManyToManyMixedKeys2MNFluentAPI	EntityAutoManyToManyMixedKeys2MNFluentAPI21=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 43");
						CEntityAutoManyToManyMixedKeys2MNFluentAPI	EntityAutoManyToManyMixedKeys2MNFluentAPI22=new CEntityAutoManyToManyMixedKeys2MNFluentAPI("NEW ENTITY MN - 44");

						EntityAutoManyToManyMixedKeys2MNFluentAPI11.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI1;
						EntityAutoManyToManyMixedKeys2MNFluentAPI11.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI1;

						EntityAutoManyToManyMixedKeys2MNFluentAPI12.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI1;
						EntityAutoManyToManyMixedKeys2MNFluentAPI12.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI2;

						EntityAutoManyToManyMixedKeys2MNFluentAPI21.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI2;
						EntityAutoManyToManyMixedKeys2MNFluentAPI21.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI1;

						EntityAutoManyToManyMixedKeys2MNFluentAPI22.EntityM=EntityAutoManyToManyMixedKeys2MFluentAPI2;
						EntityAutoManyToManyMixedKeys2MNFluentAPI22.EntityN=EntityAutoManyToManyMixedKeys2NFluentAPI2;

						Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI11);
						Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI12);
						Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI21);
						Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Add(EntityAutoManyToManyMixedKeys2MNFluentAPI22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityAutoManyToManyMixedKeys2MFluentAPI1.EntityMID;
							ID2=EntityAutoManyToManyMixedKeys2MFluentAPI2.EntityMID;
							ID3=EntityAutoManyToManyMixedKeys2NFluentAPI1.EntityNID;
							ID4=EntityAutoManyToManyMixedKeys2NFluentAPI2.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys2MFluentAPI[]	Entities1=Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys2NFluentAPI[]	Entities2=Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToManyMixedKeys2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys2MNFluentAPI[]	Entities3=Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys2MFluentAPI	EntityM1=Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Where(P => P.EntityMID==ID1).First();
						CEntityAutoManyToManyMixedKeys2MFluentAPI	EntityM2=Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Where(P => P.EntityMID==ID2).First();
						CEntityAutoManyToManyMixedKeys2NFluentAPI	EntityN1=Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Where(P => P.EntityNID==ID3).First();
						CEntityAutoManyToManyMixedKeys2NFluentAPI	EntityN2=Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Remove(EntityM1);
						Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Remove(EntityM2);
						Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Remove(EntityN1);
						Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Remove(EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityAutoManyToManyMixedKeys2MFluentAPI[]	Entities1=Context.EntitiesAutoManyToManyMixedKeys2MFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys2MFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys2NFluentAPI[]	Entities2=Context.EntitiesAutoManyToManyMixedKeys2NFluentAPI.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityAutoManyToManyMixedKeys2NFluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityAutoManyToManyMixedKeys2MNFluentAPI[]	Entities3=Context.EntitiesAutoManyToManyMixedKeys2MNFluentAPI.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityAutoManyToManyMixedKeys2MNFluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityAutoManyToManyMixedKeys2MFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToManyMixedKeys2NFluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityAutoManyToManyMixedKeys2MNFluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteNoActionNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteNoActionNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteNoActionNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [NoAction].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a zaroven skusi nastavit FOREIGN KEY DEPENDENT ENTITIES na NULL. Kedze vsak FOREIGN KEY DEPENDENT ENTITIES na NON-NULL, dojde k vzniku EXCEPTION.
						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteNoActionNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteNoActionNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteNoActionNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteNoActionNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [NoAction].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na NO ACTION a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINICPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteNoActionNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteNoActionNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteNoActionNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteNoActionNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteNoActionNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteNoActionNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteNoActionNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [NoAction].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a zaroven nastavi FOREIGN KEYS na DEPENDENT ENTITIES na NULL. DELETE sa uspesne vykona.
						CEntityOnDeleteNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteNoActionNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteNoActionNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteNoActionNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteNoActionNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteNoActionNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteNoActionNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [NoAction].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT,  ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na NO ACTION a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteNoActionNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteNoActionNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientNoActionNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientNoAction].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE skusi vykonat DELETE PRINCIPIAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na NO ACTION a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientNoActionNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientNoAction].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE skusi vykonat DELETE PRINCIPIAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na NO ACTION a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINICPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientNoActionNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientNoActionNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientNoActionNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientNoAction].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE skusi vykonat DELETE PRINCIPIAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na NO ACTION a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientNoActionNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientNoActionNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientNoActionNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientNoActionNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientNoAction].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE skusi vykonat DELETE PRINCIPIAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na NO ACTION a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientNoActionNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientNoActionNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientNoActionNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientNoActionNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientNoActionNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientNoActionNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientNoActionNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteRestrictNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteRestrictNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteRestrictNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Restrict].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a zaroven skusi nastavit FOREIGN KEY DEPENDENT ENTITIES na NULL. Kedze vsak FOREIGN KEY DEPENDENT ENTITIES na NON-NULL, dojde k vzniku EXCEPTION.
						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteRestrictNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteRestrictNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteRestrictNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteRestrictNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Restrict].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na RESTRICT, a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINICPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteRestrictNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteRestrictNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteRestrictNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteRestrictNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteRestrictNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteRestrictNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteRestrictNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Restrict].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a zaroven nastavi FOREIGN KEYS na DEPENDENT ENTITIES na NULL. DELETE PRINCIPAL ENTITY sa uspesne vykona. DEPENDENT ENTITIES ostanu v DB.
						CEntityOnDeleteRestrictNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteRestrictNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteRestrictNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteRestrictNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteRestrictNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteRestrictNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteRestrictNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Restrict].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na RESTRICT, a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteRestrictNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteRestrictNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteRestrictNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteRestrictNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteRestrictNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteRestrictNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteRestrictNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteRestrictNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteRestrictNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteRestrictNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteSetNullNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteSetNullNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteSetNullNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [SetNull].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a zaroven skusi nastavit FOREIGN KEY DEPENDENT ENTITIES na NULL. Kedze vsak FOREIGN KEY DEPENDENT ENTITIES na NON-NULL, dojde k vzniku EXCEPTION.
						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteSetNullNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteSetNullNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteSetNullNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteSetNullNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [SetNull].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. DELETE ZLYHA na urovni DB, pretoze DB je ma nastavenu DELETE ACTION na SET NULL a tak sa pokusi nastavit NULL pre FOREIGN KEYS DEPENDENT ENTITIES. No kedze FOREIGN KEYS DEPENDENT ENTITIES su NOT-NULL, DELETE ZLYHA.
						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINICPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteSetNullNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteSetNullNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteSetNullNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteSetNullNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteSetNullNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteSetNullNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteSetNullNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [SetNull].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a zaroven nastavi FOREIGN KEYS na DEPENDENT ENTITIES na NULL. DELETE PRINCIPAL ENTITY sa uspesne vykona. DEPENDENT ENTITIES ostanu v DB.
						CEntityOnDeleteSetNullNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteSetNullNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteSetNullNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteSetNullNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteSetNullNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteSetNullNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteSetNullNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [SetNull].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na SET NULL, a preto DB nastavi FOREIGN KEYS DEPENDENT ENTITIES nastavi na NULL a PRINCIPAL ENTITIY je DELETED. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteSetNullNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteSetNullNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteSetNullNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteSetNullNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientSetNullNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientSetNull].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! 
						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientSetNullNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientSetNull].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE skusi vykonat DELETE PRINCIPIAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION nie je nastavena, a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINICPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientSetNullNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientSetNullNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientSetNullNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientSetNull].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a zaroven nastavi FOREIGN KEYS na DEPENDENT ENTITIES na NULL. DELETE PRINCIPAL ENTITY sa uspesne vykona. DEPENDENT ENTITIES ostanu v DB.
						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES su v DB CONTEXT.
						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientSetNullNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientSetNullNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientSetNullNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientSetNullNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientSetNull].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION nie je nastavena, a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientSetNullNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientSetNullNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientSetNullNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientSetNullNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientSetNullNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientSetNullNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientSetNullNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteCascadeNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteCascadeNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteCascadeNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteCascadeNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Cascade].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a DEPENDENT ENTITIES.
						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteCascadeNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteCascadeNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteCascadeNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteCascadeNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteCascadeNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Cascade].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na CASCADE, a preto dojde k DELETE DEPENDENT ENTITIES. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteCascadeNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteCascadeNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteCascadeNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteCascadeNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteCascadeNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteCascadeNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteCascadeNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Cascade].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a DEPENDENT ENTITIES.
						CEntityOnDeleteCascadeNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteCascadeNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteCascadeNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteCascadeNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteCascadeNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteCascadeNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteCascadeNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteCascadeNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [Cascade].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION je nastavena na CASCADE, a preto dojde k DELETE DEPENDENT ENTITIES. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteCascadeNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteCascadeNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientCascadeNotNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientCascade].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a DEPENDENT ENTITIES.
						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientCascadeNotNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientCascade].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NOT NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE skusi vykonat DELETE PRINCIPIAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION nie je nastavena, a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINICPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNotNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNotNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNotNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNotNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNotNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientCascadeNullFluentAPIInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientCascadeNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientCascadeNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientCascadeNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientCascade].
						// !!! DEPENDENT ENTITIES su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES su v DB CONTEXT, ENTITY FRAMEWORK CORE vykona DELETE PRINCIPAL ENTITY a DEPENDENT ENTITIES.
						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOnDeleteClientCascadeNullFluentAPINotInclude()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI	DependentEntity1=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("NEW DEPENDENT 555");
						CEntityOnDeleteClientCascadeNullDependentFluentAPI	DependentEntity2=new CEntityOnDeleteClientCascadeNullDependentFluentAPI("NEW DEPENDENT 666");

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	PrincipalEntity=new CEntityOnDeleteClientCascadeNullPrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityOnDeleteClientCascadeNullDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Add(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 1:",ConsoleColor.Cyan);

						// !!! DELETE BEHAVIOR je nastaveny na VALUE [ClientCascade].
						// !!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Ak je FOREIGN KEY NULL a DEPENDENT ENTITIES NIE su v DB CONTEXT, ENTITY FRAMEWORK CORE sa pokusi vykonat DELETE PRINCIPAL ENTITY a nad DEPENDENT ENTITIES nevykona ZIADNU ACTION, kedze DEPENDENT ENTITIES nie su nacitane v DB CONTEXT. Vysledok DELETE zavisi na nastaveni DB. Ak bola DB vytvorena pomocou ENTITY FRAMEWORK CORE, DELETE ACTION nie je nastavena, a preto dojde k vzniku EXCEPTION pretoze doslo k naruseniu FOREIGN KEY CONSTRAINT. Ak DB bola vytvorena inak, DELETE zavisi od nastavenia DB.
						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 1:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!!!! PRINCIPAL ENTITIES NIE su v DB CONTEXT.
						CEntityOnDeleteClientCascadeNullDependentFluentAPI	DependentEntity1=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID1).First();
						CEntityOnDeleteClientCascadeNullDependentFluentAPI	DependentEntity2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL 2:",ConsoleColor.Cyan);

						// !!!!! DEPENDENT ENTITIES NIE su v DB CONTEXT.
						// !!!!! Dojde k DELETE PRINCIPAL ENTITY, lebo ta neobsahuje ziadne DEPENDENT ENTITIES.
						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI	PrincipalEntity=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL 2:",ConsoleColor.Cyan);

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI[]	Entities1=Context.EntitiesOnDeleteClientCascadeNullPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityOnDeleteClientCascadeNullPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOnDeleteClientCascadeNullDependentFluentAPI[]	Entities2=Context.EntitiesOnDeleteClientCascadeNullDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityOnDeleteClientCascadeNullDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNullPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityOnDeleteClientCascadeNullDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestRequiredTrueFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityRequiredTruePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredTruePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredTruePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredTrueDependentFluentAPI[]	Entities2=Context.EntitiesRequiredTrueDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredTrueDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityRequiredTrueDependentFluentAPI	DependentEntity1=new CEntityRequiredTrueDependentFluentAPI("NEW DEPENDENT 555");
						CEntityRequiredTrueDependentFluentAPI	DependentEntity2=new CEntityRequiredTrueDependentFluentAPI("NEW DEPENDENT 666");

						CEntityRequiredTruePrincipalFluentAPI	PrincipalEntity=new CEntityRequiredTruePrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityRequiredTrueDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesRequiredTruePrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityRequiredTruePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredTruePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredTruePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredTrueDependentFluentAPI[]	Entities2=Context.EntitiesRequiredTrueDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredTrueDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityRequiredTruePrincipalFluentAPI	Entity=Context.EntitiesRequiredTruePrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesRequiredTruePrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityRequiredTruePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredTruePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredTruePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredTrueDependentFluentAPI[]	Entities2=Context.EntitiesRequiredTrueDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredTrueDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityRequiredTruePrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityRequiredTrueDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestRequiredFalseFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityRequiredFalsePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredFalsePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredFalsePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredFalseDependentFluentAPI[]	Entities2=Context.EntitiesRequiredFalseDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredFalseDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityRequiredFalseDependentFluentAPI	DependentEntity1=new CEntityRequiredFalseDependentFluentAPI("NEW DEPENDENT 555");
						CEntityRequiredFalseDependentFluentAPI	DependentEntity2=new CEntityRequiredFalseDependentFluentAPI("NEW DEPENDENT 666");

						CEntityRequiredFalsePrincipalFluentAPI	PrincipalEntity=new CEntityRequiredFalsePrincipalFluentAPI("NEW PRINCIPAL 333",new CEntityRequiredFalseDependentFluentAPI[]{DependentEntity1,DependentEntity2});

						Context.EntitiesRequiredFalsePrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityRequiredFalsePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredFalsePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredFalsePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredFalseDependentFluentAPI[]	Entities2=Context.EntitiesRequiredFalseDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredFalseDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityRequiredFalsePrincipalFluentAPI	PrincipalEntity=Context.EntitiesRequiredFalsePrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesRequiredFalsePrincipalFluentAPI.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityRequiredFalsePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredFalsePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredFalsePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredFalseDependentFluentAPI[]	Entities2=Context.EntitiesRequiredFalseDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredFalseDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityRequiredFalseDependentFluentAPI	DependentEntity1=Context.EntitiesRequiredFalseDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityRequiredFalseDependentFluentAPI	DependentEntity2=Context.EntitiesRequiredFalseDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesRequiredFalseDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesRequiredFalseDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityRequiredFalsePrincipalFluentAPI[]	Entities1=Context.EntitiesRequiredFalsePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityRequiredFalsePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityRequiredFalseDependentFluentAPI[]	Entities2=Context.EntitiesRequiredFalseDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityRequiredFalseDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityRequiredFalsePrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityRequiredFalseDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestHasAlternateKeyFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI[]		Entities=Context.EntitiesHasAlternateKeyFluentAPI.ToArray();

						CEntityHasAlternateKeyFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI			Entity=new CEntityHasAlternateKeyFluentAPI("NEW VALUE 333","KEY 3");

						Context.EntitiesHasAlternateKeyFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI[]		Entities=Context.EntitiesHasAlternateKeyFluentAPI.ToArray();

						CEntityHasAlternateKeyFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING DUPLICATE ALTERNATE KEY:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI			Entity=new CEntityHasAlternateKeyFluentAPI("NEW VALUE 333","KEY 3");

						Context.EntitiesHasAlternateKeyFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT DUPLICATE ALTERNATE KEY:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI[]		Entities=Context.EntitiesHasAlternateKeyFluentAPI.ToArray();

						CEntityHasAlternateKeyFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI			Entity=Context.EntitiesHasAlternateKeyFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesHasAlternateKeyFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyFluentAPI[]		Entities=Context.EntitiesHasAlternateKeyFluentAPI.ToArray();

						CEntityHasAlternateKeyFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityHasAlternateKeyFluentAPI));

						PrintEntityProperties(EntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestHasAlternateKeyCompositeFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI[]	Entities=Context.EntitiesHasAlternateKeyCompositeFluentAPI.ToArray();

						CEntityHasAlternateKeyCompositeFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI	Entity=new CEntityHasAlternateKeyCompositeFluentAPI("NEW VALUE 333","KEY 3","KEY C");

						Context.EntitiesHasAlternateKeyCompositeFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI[]	Entities=Context.EntitiesHasAlternateKeyCompositeFluentAPI.ToArray();

						CEntityHasAlternateKeyCompositeFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING DUPLICATE ALTERNATE KEY:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI	Entity=new CEntityHasAlternateKeyCompositeFluentAPI("NEW VALUE 333","KEY 3","KEY C");

						Context.EntitiesHasAlternateKeyCompositeFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						if (E.InnerException==null)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						}
						else
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] INNER EXCEPTION [{E.InnerException.Message}] !",ConsoleColor.Red);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT DUPLICATE ALTERNATE KEY:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI[]	Entities=Context.EntitiesHasAlternateKeyCompositeFluentAPI.ToArray();

						CEntityHasAlternateKeyCompositeFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI	Entity=Context.EntitiesHasAlternateKeyCompositeFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesHasAlternateKeyCompositeFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityHasAlternateKeyCompositeFluentAPI[]	Entities=Context.EntitiesHasAlternateKeyCompositeFluentAPI.ToArray();

						CEntityHasAlternateKeyCompositeFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityHasAlternateKeyCompositeFluentAPI));

						PrintEntityProperties(EntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestHasPrincipalKeyFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyPrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyDependentFluentAPI	DependentEntity1=new CEntityHasPrincipalKeyDependentFluentAPI("NEW DEPENDENT 555","KEY 3");
						CEntityHasPrincipalKeyDependentFluentAPI	DependentEntity2=new CEntityHasPrincipalKeyDependentFluentAPI("NEW DEPENDENT 666","KEY 3");

						CEntityHasPrincipalKeyPrincipalFluentAPI	PrincipalEntity=new CEntityHasPrincipalKeyPrincipalFluentAPI("NEW PRINCIPAL 333","KEY 3");

						Context.EntitiesHasPrincipalKeyDependentFluentAPI.Add(DependentEntity1);
						Context.EntitiesHasPrincipalKeyDependentFluentAPI.Add(DependentEntity2);
						Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyPrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyPrincipalFluentAPI	Entity=Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyPrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityHasPrincipalKeyDependentFluentAPI	DependentEntity1=Context.EntitiesHasPrincipalKeyDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityHasPrincipalKeyDependentFluentAPI	DependentEntity2=Context.EntitiesHasPrincipalKeyDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesHasPrincipalKeyDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesHasPrincipalKeyDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyPrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyPrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityHasPrincipalKeyPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityHasPrincipalKeyDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestHasPrincipalKeyCompositeFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyCompositeDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyCompositeDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyCompositeDependentFluentAPI	DependentEntity1=new CEntityHasPrincipalKeyCompositeDependentFluentAPI("NEW DEPENDENT 555","KEY AAA 3","KEY BBB 3");
						CEntityHasPrincipalKeyCompositeDependentFluentAPI	DependentEntity2=new CEntityHasPrincipalKeyCompositeDependentFluentAPI("NEW DEPENDENT 666","KEY AAA 3","KEY BBB 3");

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI	PrincipalEntity=new CEntityHasPrincipalKeyCompositePrincipalFluentAPI("NEW PRINCIPAL 333","KEY AAA 3","KEY BBB 3");

						Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Add(DependentEntity1);
						Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Add(DependentEntity2);
						Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyCompositeDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyCompositeDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI	Entity=Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyCompositeDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyCompositeDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING DEPENDENT:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityHasPrincipalKeyCompositeDependentFluentAPI	DependentEntity1=Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();

						// !!! DEPENDENT ENTITY je DELETED pomocou EXPLICITLY, lebo sa jedna o RELATIONSHIP 0/1:N.
						CEntityHasPrincipalKeyCompositeDependentFluentAPI	DependentEntity2=Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Remove(DependentEntity1);
						Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Remove(DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT:",ConsoleColor.Cyan);

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI[]	Entities1=Context.EntitiesHasPrincipalKeyCompositePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasPrincipalKeyCompositePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasPrincipalKeyCompositeDependentFluentAPI[]	Entities2=Context.EntitiesHasPrincipalKeyCompositeDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasPrincipalKeyCompositeDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityHasPrincipalKeyCompositePrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityHasPrincipalKeyCompositeDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestHasConstraintNameFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DATA:",ConsoleColor.Cyan);

						CEntityHasConstraintNamePrincipalFluentAPI[]	Entities1=Context.EntitiesHasConstraintNamePrincipalFluentAPI.Include(P => P.EntitiesDependent).ToArray();

						CEntityHasConstraintNamePrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityHasConstraintNameDependentFluentAPI[]	Entities2=Context.EntitiesHasConstraintNameDependentFluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityHasConstraintNameDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityHasConstraintNamePrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntityType=Context.Model.FindEntityType(typeof(CEntityHasConstraintNameDependentFluentAPI));

						PrintEntityProperties(DependentEntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOwnedTypeInOneTable()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DATA:",ConsoleColor.Cyan);

						CEntityOwnedTypeInOneTable[]			Entities=Context.EntitiesOwnedTypeInOneTable.ToArray();

						CEntityOwnedTypeInOneTable.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityOwnedTypeInOneTable));

						PrintEntityProperties(EntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOwnedTypeInMultiTables()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DATA:",ConsoleColor.Cyan);

						CEntityOwnedTypeInMultiTables[]			Entities=Context.EntitiesOwnedTypeInMultiTables.ToArray();

						CEntityOwnedTypeInMultiTables.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityOwnedTypeInMultiTables));

						PrintEntityProperties(EntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOwnedTypeOneAndMany()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DATA:",ConsoleColor.Cyan);

						CEntityOwnedTypeOneAndMany[]			Entities=Context.EntitiesOwnedTypeOneAndMany.ToArray();

						CEntityOwnedTypeOneAndMany.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityOwnedTypeOneAndMany));

						PrintEntityProperties(EntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTablePerHierarchyConventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													BaseID1=0;
			int													Derived1ID=0;
			int													Derived2ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseConventions[]	Entities1=Context.EntitiesTablePerHierarchyBaseConventions.ToArray();

						CEntityTablePerHierarchyBaseConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1Conventions[]	Entities2=Context.EntitiesTablePerHierarchyDerived1Conventions.ToArray();

						CEntityTablePerHierarchyDerived1Conventions.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2Conventions[]	Entities3=Context.EntitiesTablePerHierarchyDerived2Conventions.ToArray();

						CEntityTablePerHierarchyDerived2Conventions.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseConventions	EntityBase=new CEntityTablePerHierarchyBaseConventions("BASE - 333");
						CEntityTablePerHierarchyDerived1Conventions	EntityDerived1=new CEntityTablePerHierarchyDerived1Conventions("DERIVED 1 - BASE 333","DERIVED 1 - DERIVED 1 333","DERIVED 1 - DERIVED WITH SAME NAME - 333","DERIVED 1 - DERIVED IN SHARED COLUMN - 333");
						CEntityTablePerHierarchyDerived2Conventions	EntityDerived2=new CEntityTablePerHierarchyDerived2Conventions("DERIVED 2 - BASE 333","DERIVED 2 - DERIVED 2 333","DERIVED 2 - DERIVED WITH SAME NAME - 333","DERIVED 2 - DERIVED IN SHARED COLUMN - 333");

						Context.EntitiesTablePerHierarchyBaseConventions.Add(EntityBase);
						Context.EntitiesTablePerHierarchyDerived1Conventions.Add(EntityDerived1);
						Context.EntitiesTablePerHierarchyDerived2Conventions.Add(EntityDerived2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							BaseID1=EntityBase.EntityID;
							Derived1ID=EntityDerived1.EntityID;
							Derived2ID=EntityDerived2.EntityID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseConventions[]	Entities1=Context.EntitiesTablePerHierarchyBaseConventions.ToArray();

						CEntityTablePerHierarchyBaseConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1Conventions[]	Entities2=Context.EntitiesTablePerHierarchyDerived1Conventions.ToArray();

						CEntityTablePerHierarchyDerived1Conventions.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2Conventions[]	Entities3=Context.EntitiesTablePerHierarchyDerived2Conventions.ToArray();

						CEntityTablePerHierarchyDerived2Conventions.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseConventions	EntityBase=Context.EntitiesTablePerHierarchyBaseConventions.Where(P => P.EntityID==BaseID1).First();
						CEntityTablePerHierarchyDerived1Conventions	EntityDerived1=Context.EntitiesTablePerHierarchyDerived1Conventions.Where(P => P.EntityID==Derived1ID).First();
						CEntityTablePerHierarchyDerived2Conventions	EntityDerived2=Context.EntitiesTablePerHierarchyDerived2Conventions.Where(P => P.EntityID==Derived2ID).First();

						Context.EntitiesTablePerHierarchyBaseConventions.Remove(EntityBase);
						Context.EntitiesTablePerHierarchyDerived1Conventions.Remove(EntityDerived1);
						Context.EntitiesTablePerHierarchyDerived2Conventions.Remove(EntityDerived2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseConventions[]	Entities1=Context.EntitiesTablePerHierarchyBaseConventions.ToArray();

						CEntityTablePerHierarchyBaseConventions.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1Conventions[]	Entities2=Context.EntitiesTablePerHierarchyDerived1Conventions.ToArray();

						CEntityTablePerHierarchyDerived1Conventions.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2Conventions[]	Entities3=Context.EntitiesTablePerHierarchyDerived2Conventions.ToArray();

						CEntityTablePerHierarchyDerived2Conventions.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityTablePerHierarchyBaseConventions));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityTablePerHierarchyDerived1Conventions));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityTablePerHierarchyDerived2Conventions));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTablePerHierarchyFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													Derived1ID=0;
			int													Derived2ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyDerived1FluentAPI	EntityDerived1=new CEntityTablePerHierarchyDerived1FluentAPI("DERIVED 1 - BASE 333","DERIVED 1 - DERIVED 1 333","DERIVED 1 - DERIVED WITH SAME NAME - 333","DERIVED 1 - DERIVED IN SHARED COLUMN - 333");
						CEntityTablePerHierarchyDerived2FluentAPI	EntityDerived2=new CEntityTablePerHierarchyDerived2FluentAPI("DERIVED 2 - BASE 333","DERIVED 2 - DERIVED 2 333","DERIVED 2 - DERIVED WITH SAME NAME - 333","DERIVED 2 - DERIVED IN SHARED COLUMN - 333");

						Context.EntitiesTablePerHierarchyDerived1FluentAPI.Add(EntityDerived1);
						Context.EntitiesTablePerHierarchyDerived2FluentAPI.Add(EntityDerived2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							Derived1ID=EntityDerived1.EntityID;
							Derived2ID=EntityDerived2.EntityID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyDerived1FluentAPI	EntityDerived1=Context.EntitiesTablePerHierarchyDerived1FluentAPI.Where(P => P.EntityID==Derived1ID).First();
						CEntityTablePerHierarchyDerived2FluentAPI	EntityDerived2=Context.EntitiesTablePerHierarchyDerived2FluentAPI.Where(P => P.EntityID==Derived2ID).First();

						Context.EntitiesTablePerHierarchyDerived1FluentAPI.Remove(EntityDerived1);
						Context.EntitiesTablePerHierarchyDerived2FluentAPI.Remove(EntityDerived2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityTablePerHierarchyBaseFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityTablePerHierarchyDerived1FluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityTablePerHierarchyDerived2FluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTablePerHierarchyChangeEntityType()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyDerived1FluentAPI	EntityDerived=new CEntityTablePerHierarchyDerived1FluentAPI("DERIVED - BASE 333","DERIVED - DERIVED 333","DERIVED - DERIVED WITH SAME NAME - 333","DERIVED - DERIVED IN SHARED COLUMN - 333");

						Context.EntitiesTablePerHierarchyDerived1FluentAPI.Add(EntityDerived);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityDerived.EntityID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("MODIFYING DISCRIMINATOR VALUE:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyDerived1FluentAPI	EntityDerived=Context.EntitiesTablePerHierarchyDerived1FluentAPI.Where(P => P.EntityID==ID).First();

						// !!!!! Modifikuje sa DISCRIMINATOR VALUE.
						EntityDerived.Discriminator=EDiscriminatorFluentAPI.E_DERIVED_2;

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT UPDATED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DISCRIMINATOR VALUE MODIFIED:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("UPDATING MODIFIED ENTITY:",ConsoleColor.Cyan);

						// !!!!! Modifikacia ENTITY, ktore bol zmeneny TYPE sa MUSI urobit v SEPARATNOM DB CONTEXT.
						CEntityTablePerHierarchyDerived2FluentAPI	EntityDerived=Context.EntitiesTablePerHierarchyDerived2FluentAPI.Where(P => P.EntityID==ID).First();

						// !!!!! Modifikuju sa PROPERTIES.
						EntityDerived.DerivedValue2="DERIVED - DERIVED 333";
						EntityDerived.DerivedValueWithSameName="DERIVED - DERIVED WITH SAME NAME - 333";

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT UPDATED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATED MODIFIED ENTITY:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyDerived2FluentAPI	EntityDerived=Context.EntitiesTablePerHierarchyDerived2FluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesTablePerHierarchyDerived2FluentAPI.Remove(EntityDerived);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityTablePerHierarchyBaseFluentAPI[]	Entities1=Context.EntitiesTablePerHierarchyBaseFluentAPI.ToArray();

						CEntityTablePerHierarchyBaseFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived1FluentAPI[]	Entities2=Context.EntitiesTablePerHierarchyDerived1FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerHierarchyDerived2FluentAPI[]	Entities3=Context.EntitiesTablePerHierarchyDerived2FluentAPI.ToArray();

						CEntityTablePerHierarchyDerived2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTablePerTypeFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													Derived1ID=0;
			int													Derived2ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTablePerTypeDerived1FluentAPI[]	Entities1=Context.EntitiesTablePerTypeBaseFluentAPI.OfType<CEntityTablePerTypeDerived1FluentAPI>().ToArray();

						CEntityTablePerTypeDerived1FluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerTypeDerived2FluentAPI[]	Entities2=Context.EntitiesTablePerTypeBaseFluentAPI.OfType<CEntityTablePerTypeDerived2FluentAPI>().ToArray();

						CEntityTablePerTypeDerived2FluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityTablePerTypeDerived1FluentAPI	Entity1=new CEntityTablePerTypeDerived1FluentAPI("DERIVED 1 - BASE 333","DERIVED 1 - DERIVED 1 333");
						CEntityTablePerTypeDerived2FluentAPI	Entity2=new CEntityTablePerTypeDerived2FluentAPI("DERIVED 2 - BASE 333","DERIVED 2 - DERIVED 2 333");

						Context.EntitiesTablePerTypeBaseFluentAPI.Add(Entity1);
						Context.EntitiesTablePerTypeBaseFluentAPI.Add(Entity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							Derived1ID=Entity1.EntityID;
							Derived2ID=Entity2.EntityID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTablePerTypeDerived1FluentAPI[]	Entities1=Context.EntitiesTablePerTypeBaseFluentAPI.OfType<CEntityTablePerTypeDerived1FluentAPI>().ToArray();

						CEntityTablePerTypeDerived1FluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerTypeDerived2FluentAPI[]	Entities2=Context.EntitiesTablePerTypeBaseFluentAPI.OfType<CEntityTablePerTypeDerived2FluentAPI>().ToArray();

						CEntityTablePerTypeDerived2FluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityTablePerTypeBaseFluentAPI		Entity1=Context.EntitiesTablePerTypeBaseFluentAPI.Where(P => P.EntityID==Derived1ID).First();
						CEntityTablePerTypeBaseFluentAPI		Entity2=Context.EntitiesTablePerTypeBaseFluentAPI.Where(P => P.EntityID==Derived2ID).First();

						Context.EntitiesTablePerTypeBaseFluentAPI.Remove(Entity1);
						Context.EntitiesTablePerTypeBaseFluentAPI.Remove(Entity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityTablePerTypeDerived1FluentAPI[]	Entities1=Context.EntitiesTablePerTypeBaseFluentAPI.OfType<CEntityTablePerTypeDerived1FluentAPI>().ToArray();

						CEntityTablePerTypeDerived1FluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerTypeDerived2FluentAPI[]	Entities2=Context.EntitiesTablePerTypeBaseFluentAPI.OfType<CEntityTablePerTypeDerived2FluentAPI>().ToArray();

						CEntityTablePerTypeDerived2FluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityMType=Context.Model.FindEntityType(typeof(CEntityTablePerTypeBaseFluentAPI));

						PrintEntityProperties(EntityMType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityNType=Context.Model.FindEntityType(typeof(CEntityTablePerTypeDerived1FluentAPI));

						PrintEntityProperties(EntityNType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityMNType=Context.Model.FindEntityType(typeof(CEntityTablePerTypeDerived2FluentAPI));

						PrintEntityProperties(EntityMNType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTablePerTypeFluentAPISetSelect()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("SET SELECT:",ConsoleColor.Cyan);

						// !!!!! Pristup k DERIVED ENTITY pomocou DB CONTEXT METHOD [DbSet<TEntity> DbContext.Set<TEntity>()].
						CEntityTablePerTypeDerived1FluentAPI[]	Entities1=Context.Set<CEntityTablePerTypeDerived1FluentAPI>().ToArray();

						CEntityTablePerTypeDerived1FluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTablePerTypeDerived2FluentAPI[]	Entities2=Context.Set<CEntityTablePerTypeDerived2FluentAPI>().ToArray();

						CEntityTablePerTypeDerived2FluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTableSplittingFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTableSplittingPrincipalFluentAPI[]	Entities1=Context.EntitiesTableSplittingPrincipalFluentAPI.Include(P => P.EntityDependent1).Include(P => P.EntityDependent2).ToArray();

						CEntityTableSplittingPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent1FluentAPI[]	Entities2=Context.EntitiesTableSplittingDependent1FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent2FluentAPI[]	Entities3=Context.EntitiesTableSplittingDependent2FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!!!! Kedze PROPERTY 'CEntityTableSplittingDependent1FluentAPI.EntitySharedValue' odkazuje do toho isteho COLUMN ako 'CEntityTableSplittingDependent2FluentAPI.EntitySharedValue' MUSIA mat OBE PROPERTIES ROVNAKU VALUE inak INSERT ZLYHA.
						const string							SHARED_VALUE="SHARED - 333";

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityTableSplittingPrincipalFluentAPI	PrincipalEntity=new CEntityTableSplittingPrincipalFluentAPI("NEW PRINCIPAL - 333");
						CEntityTableSplittingDependent1FluentAPI	DependentEntity1=new CEntityTableSplittingDependent1FluentAPI("NEW DEPENDENT 1 - 333",SHARED_VALUE);
						CEntityTableSplittingDependent2FluentAPI	DependentEntity2=new CEntityTableSplittingDependent2FluentAPI("NEW DEPENDENT 2 - 333",SHARED_VALUE);

						PrincipalEntity.EntityDependent1=DependentEntity1;
						PrincipalEntity.EntityDependent2=DependentEntity2;

						Context.EntitiesTableSplittingPrincipalFluentAPI.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY 1 [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY 2 [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTableSplittingPrincipalFluentAPI[]	Entities1=Context.EntitiesTableSplittingPrincipalFluentAPI.Include(P => P.EntityDependent1).Include(P => P.EntityDependent2).ToArray();

						CEntityTableSplittingPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent1FluentAPI[]	Entities2=Context.EntitiesTableSplittingDependent1FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent2FluentAPI[]	Entities3=Context.EntitiesTableSplittingDependent2FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("UPDATE DEPENDENT 1:",ConsoleColor.Cyan);

						// !!!!! Zo SHARED TABLE sa vyberu COLUMNS, ktore tvoria DEPEDNENT ENTITY 'CEntityTableSplittingDependent1FluentAPI'.
						// !!!!! DEPENDENT ENTITY PRIMARY KEY je zhodny s PRINCIPAL ENTITY PRIMARY KEY.
						CEntityTableSplittingDependent1FluentAPI	Entity=Context.EntitiesTableSplittingDependent1FluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==PrincipalID).First();

						Entity.EntityDependentValue1="MODIFIED VALUE 1";

						// !!!!! Kedze PROPERTY je SHARED s PROPERTY v ENTITY 'CEntityTableSplittingDependent2FluentAPI', zmeni sa aj VALUE PROPERTY v ENTITY 'CEntityTableSplittingDependent2FluentAPI'.
						Entity.EntitySharedValue="MODIFIED SHARED VALUE 1";

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY 1 [{Entity.EntityDependentID}] was UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT UPDATED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE DEPENDENT 1:",ConsoleColor.Cyan);

						CEntityTableSplittingPrincipalFluentAPI[]	Entities1=Context.EntitiesTableSplittingPrincipalFluentAPI.Include(P => P.EntityDependent1).Include(P => P.EntityDependent2).ToArray();

						CEntityTableSplittingPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent1FluentAPI[]	Entities2=Context.EntitiesTableSplittingDependent1FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent2FluentAPI[]	Entities3=Context.EntitiesTableSplittingDependent2FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("UPDATE DEPENDENT 2:",ConsoleColor.Cyan);

						// !!!!! Zo SHARED TABLE sa vyberu COLUMNS, ktore tvoria DEPEDNENT ENTITY 'CEntityTableSplittingDependent2FluentAPI'.
						// !!!!! DEPENDENT ENTITY PRIMARY KEY je zhodny s PRINCIPAL ENTITY PRIMARY KEY.
						CEntityTableSplittingDependent2FluentAPI	Entity=Context.EntitiesTableSplittingDependent2FluentAPI.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==PrincipalID).First();

						Entity.EntityDependentValue2="MODIFIED VALUE 2";

						// !!!!! Kedze PROPERTY je SHARED s PROPERTY v ENTITY 'CEntityTableSplittingDependent1FluentAPI', zmeni sa aj VALUE PROPERTY v ENTITY 'CEntityTableSplittingDependent1FluentAPI'.
						Entity.EntitySharedValue="MODIFIED SHARED VALUE 2";

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY 2 [{Entity.EntityDependentID}] was UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT UPDATED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE DEPENDENT 2:",ConsoleColor.Cyan);

						CEntityTableSplittingPrincipalFluentAPI[]	Entities1=Context.EntitiesTableSplittingPrincipalFluentAPI.Include(P => P.EntityDependent1).Include(P => P.EntityDependent2).ToArray();

						CEntityTableSplittingPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent1FluentAPI[]	Entities2=Context.EntitiesTableSplittingDependent1FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent2FluentAPI[]	Entities3=Context.EntitiesTableSplittingDependent2FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITY je DELETED pomocou CASCADE DELETE.
						CEntityTableSplittingPrincipalFluentAPI		Entity=Context.EntitiesTableSplittingPrincipalFluentAPI.Include(P => P.EntityDependent1).Include(P => P.EntityDependent2).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesTableSplittingPrincipalFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityTableSplittingPrincipalFluentAPI[]	Entities1=Context.EntitiesTableSplittingPrincipalFluentAPI.Include(P => P.EntityDependent1).Include(P => P.EntityDependent2).ToArray();

						CEntityTableSplittingPrincipalFluentAPI.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent1FluentAPI[]	Entities2=Context.EntitiesTableSplittingDependent1FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent1FluentAPI.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityTableSplittingDependent2FluentAPI[]	Entities3=Context.EntitiesTableSplittingDependent2FluentAPI.Include(P => P.EntityPrincipal).ToArray();

						CEntityTableSplittingDependent2FluentAPI.PrintToConsole(Entities3);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								PrincipalEntityType=Context.Model.FindEntityType(typeof(CEntityTableSplittingPrincipalFluentAPI));

						PrintEntityProperties(PrincipalEntityType);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntity1Type=Context.Model.FindEntityType(typeof(CEntityTableSplittingDependent1FluentAPI));

						PrintEntityProperties(DependentEntity1Type);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								DependentEntity2Type=Context.Model.FindEntityType(typeof(CEntityTableSplittingDependent2FluentAPI));

						PrintEntityProperties(DependentEntity2Type);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestPropertyBagFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityPropertyBagDependentFluentAPI[]	Entities2=Context.EntitiesPropertyBagDependentFluentAPI.ToArray();
						Dictionary<string,object>[]				Entities1=Context.MyPropertyBagPrincipal.ToArray();
						List<CMyPropertyBag>					ParsedEntitiesCollection=new List<CMyPropertyBag>();

						foreach(Dictionary<string,object> Entity1 in Entities1)
						{
							int									ID=(int) Entity1[CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID];
							CEntityPropertyBagDependentFluentAPI[]	EntitiesDependent=Entities2.Where(P => P.EntityPrincipalID==ID).ToArray();
							CMyPropertyBag						ParsedEntity=CMyPropertyBag.FromPropertyBag(Entity1,EntitiesDependent);

							ParsedEntitiesCollection.Add(ParsedEntity);
						}

						CMyPropertyBag[]						ParsedEntities=ParsedEntitiesCollection.ToArray();

						CMyPropertyBag.PrintToConsole(ParsedEntities);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityPropertyBagDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						const int									PRIMARY_KEY=13;

						CEntityPropertyBagDependentFluentAPI		DependentEntity1=new CEntityPropertyBagDependentFluentAPI("NEW DEPENDENT 555",PRIMARY_KEY);
						CEntityPropertyBagDependentFluentAPI		DependentEntity2=new CEntityPropertyBagDependentFluentAPI("NEW DEPENDENT 666",PRIMARY_KEY);

						Dictionary<string,object>					PrincipalEntity=CMyPropertyBag.ToPropertyBag(PRIMARY_KEY,333,"PRINCIPAL STRING 333");

						Context.MyPropertyBagPrincipal.Add(PrincipalEntity);
						Context.EntitiesPropertyBagDependentFluentAPI.Add(DependentEntity1);
						Context.EntitiesPropertyBagDependentFluentAPI.Add(DependentEntity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=(int) PrincipalEntity[CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID];

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity[CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID]}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityPropertyBagDependentFluentAPI[]	Entities2=Context.EntitiesPropertyBagDependentFluentAPI.ToArray();
						Dictionary<string,object>[]				Entities1=Context.MyPropertyBagPrincipal.ToArray();
						List<CMyPropertyBag>					ParsedEntitiesCollection=new List<CMyPropertyBag>();

						foreach(Dictionary<string,object> Entity1 in Entities1)
						{
							int									ID=(int) Entity1[CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID];
							CEntityPropertyBagDependentFluentAPI[]	EntitiesDependent=Entities2.Where(P => P.EntityPrincipalID==ID).ToArray();
							CMyPropertyBag						ParsedEntity=CMyPropertyBag.FromPropertyBag(Entity1,EntitiesDependent);

							ParsedEntitiesCollection.Add(ParsedEntity);
						}

						CMyPropertyBag[]						ParsedEntities=ParsedEntitiesCollection.ToArray();

						CMyPropertyBag.PrintToConsole(ParsedEntities);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityPropertyBagDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!! DEPENDENT ENTITIES su DELETED pomocou CASCADE DELETE.
						Dictionary<string,object>				Entity=Context.MyPropertyBagPrincipal.Where(P => ((int)P[CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID])==PrincipalID).First();

						// !!! Z PROPERY BAG sa vyberu PROPERTIES.
						CMyPropertyBag							ParsedEntity=CMyPropertyBag.FromPropertyBag(Entity,null);

						Context.MyPropertyBagPrincipal.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ParsedEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityPropertyBagDependentFluentAPI[]	Entities2=Context.EntitiesPropertyBagDependentFluentAPI.ToArray();
						Dictionary<string,object>[]				Entities1=Context.MyPropertyBagPrincipal.ToArray();
						List<CMyPropertyBag>					ParsedEntitiesCollection=new List<CMyPropertyBag>();

						foreach(Dictionary<string,object> Entity1 in Entities1)
						{
							int									ID=(int) Entity1[CMyPropertyBag.PROPERTY_BAG_PRINCIPAL_COLUMN_ID];
							CEntityPropertyBagDependentFluentAPI[]	EntitiesDependent=Entities2.Where(P => P.EntityPrincipalID==ID).ToArray();
							CMyPropertyBag						ParsedEntity=CMyPropertyBag.FromPropertyBag(Entity1,EntitiesDependent);

							ParsedEntitiesCollection.Add(ParsedEntity);
						}

						CMyPropertyBag[]						ParsedEntities=ParsedEntitiesCollection.ToArray();

						CMyPropertyBag.PrintToConsole(ParsedEntities);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityPropertyBagDependentFluentAPI.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityPropertyBagDependentFluentAPI));

						PrintEntityProperties(EntityType);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			//CreateTestDB();
			//TestSelectTestEntity();
			//TestOneToOneConventions();
			//TestZeroToOneConventions();
			//TestOneToManyConventions();
			//TestZeroToManyConventions();
			//TestForeignKeyName1Conventions();
			//TestForeignKeyName2Conventions();
			//TestForeignKeyName3Conventions();
			//TestNoForeignKey1Conventions();
			//TestNoForeignKey2Conventions();
			//TestNoForeignKey3Conventions();
			//TestOneToOneDataAnnotations();
			//TestZeroToOneDataAnnotations();
			//TestOneToManyDataAnnotations();
			//TestZeroToManyDataAnnotations();
			//TestAttributeOnNavigationPropertyDataAnnotations();
			//TestAttributeOnForeignKeyDataAnnotations();
			//TestCompositeForeignKeyDataAnnotations();
			//TestInversePropertyDataAnnotations();
			//TestOneToOne1FluentAPI();
			//TestOneToOne2FluentAPI();
			//TestZeroToOne1FluentAPI();
			//TestZeroToOne2FluentAPI();
			//TestOneToOneMixedKeys1FluentAPI();
			//TestOneToOneMixedKeys2FluentAPI();
			//TestOneToMany1FluentAPI();
			//TestOneToMany2FluentAPI();
			//TestZeroToMany1FluentAPI();
			//TestZeroToMany2FluentAPI();
			//TestManyToMany1FluentAPI();
			//TestManyToMany2FluentAPI();
			//TestZeroManyToMany1FluentAPI();
			//TestZeroManyToMany2FluentAPI();
			//TestManyToManyMixedKeys1FluentAPI();
			//TestManyToManyMixedKeys2FluentAPI();
			//TestAutoManyToMany1FluentAPI();
			//TestAutoManyToMany2FluentAPI();
			//TestAutoZeroManyToMany1FluentAPI();
			//TestAutoZeroManyToMany2FluentAPI();
			//TestAutoManyToManyMixedKeys1FluentAPI();
			//TestAutoManyToManyMixedKeys2FluentAPI();
			//TestOnDeleteNoActionNotNullFluentAPIInclude();
			//TestOnDeleteNoActionNotNullFluentAPINotInclude();
			//TestOnDeleteNoActionNullFluentAPIInclude();
			//TestOnDeleteNoActionNullFluentAPINotInclude();
			//TestOnDeleteClientNoActionNotNullFluentAPIInclude();
			//TestOnDeleteClientNoActionNotNullFluentAPINotInclude();
			//TestOnDeleteClientNoActionNullFluentAPIInclude();
			//TestOnDeleteClientNoActionNullFluentAPINotInclude();
			//TestOnDeleteRestrictNotNullFluentAPIInclude();
			//TestOnDeleteRestrictNotNullFluentAPINotInclude();
			//TestOnDeleteRestrictNullFluentAPIInclude();
			//TestOnDeleteRestrictNullFluentAPINotInclude();
			//TestOnDeleteSetNullNotNullFluentAPIInclude();
			//TestOnDeleteSetNullNotNullFluentAPINotInclude();
			//TestOnDeleteSetNullNullFluentAPIInclude();
			//TestOnDeleteSetNullNullFluentAPINotInclude();
			//TestOnDeleteClientSetNullNotNullFluentAPIInclude();
			//TestOnDeleteClientSetNullNotNullFluentAPINotInclude();
			//TestOnDeleteClientSetNullNullFluentAPIInclude();
			//TestOnDeleteClientSetNullNullFluentAPINotInclude();
			//TestOnDeleteCascadeNotNullFluentAPIInclude();
			//TestOnDeleteCascadeNotNullFluentAPINotInclude();
			//TestOnDeleteCascadeNullFluentAPIInclude();
			//TestOnDeleteCascadeNullFluentAPINotInclude();
			//TestOnDeleteClientCascadeNotNullFluentAPIInclude();
			//TestOnDeleteClientCascadeNotNullFluentAPINotInclude();
			//TestOnDeleteClientCascadeNullFluentAPIInclude();
			//TestOnDeleteClientCascadeNullFluentAPINotInclude();
			//TestRequiredTrueFluentAPI();
			//TestRequiredFalseFluentAPI();
			//TestHasAlternateKeyFluentAPI();
			//TestHasAlternateKeyCompositeFluentAPI();
			//TestHasPrincipalKeyFluentAPI();
			//TestHasPrincipalKeyCompositeFluentAPI();
			//TestHasConstraintNameFluentAPI();
			//TestOwnedTypeInOneTable();
			//TestOwnedTypeInMultiTables();
			TestOwnedTypeOneAndMany();
			//TestTablePerHierarchyConventions();
			//TestTablePerHierarchyFluentAPI();
			//TestTablePerHierarchyChangeEntityType();
			//TestTablePerTypeFluentAPI();
			//TestTablePerTypeFluentAPISetSelect();
			//TestTableSplittingFluentAPI();
			//TestPropertyBagFluentAPI();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------