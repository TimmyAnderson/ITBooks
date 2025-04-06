using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMyQueries
	{
//----------------------------------------------------------------------------------------------------------------------
		private CObjectTypeOneToOnePrincipal1[]					MObjectsOneToOnes1;
		private CObjectTypeOneToOnePrincipal1					MObjectOneToOne1;
		private CObjectTypeOneToOnePrincipal2[]					MObjectsOneToOnes2;
		private CObjectTypeOneToOnePrincipal2					MObjectOneToOne2;
		private CObjectTypeOneToManyPrincipal[]					MObjectsOneToMany;
		private CObjectTypeOneToManyPrincipal					MObjectOneToMany;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CMyQueries()
		{
			MObjectsOneToOnes1=null;
			MObjectOneToOne1=null;
			MObjectsOneToOnes2=null;
			MObjectOneToOne2=null;
			MObjectsOneToMany=null;
			MObjectOneToMany=null;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CObjectTypeOneToOnePrincipal1[]					ObjectsOneToOnes1
		{
			get
			{
				return(MObjectsOneToOnes1);
			}
			set
			{
				MObjectsOneToOnes1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CObjectTypeOneToOnePrincipal1					ObjectOneToOne1
		{
			get
			{
				return(MObjectOneToOne1);
			}
			set
			{
				MObjectOneToOne1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CObjectTypeOneToOnePrincipal2[]					ObjectsOneToOnes2
		{
			get
			{
				return(MObjectsOneToOnes2);
			}
			set
			{
				MObjectsOneToOnes2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CObjectTypeOneToOnePrincipal2					ObjectOneToOne2
		{
			get
			{
				return(MObjectOneToOne2);
			}
			set
			{
				MObjectOneToOne2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CObjectTypeOneToManyPrincipal[]					ObjectsOneToMany
		{
			get
			{
				return(MObjectsOneToMany);
			}
			set
			{
				MObjectsOneToMany=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CObjectTypeOneToManyPrincipal					ObjectOneToMany
		{
			get
			{
				return(MObjectOneToMany);
			}
			set
			{
				MObjectOneToMany=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CEntityName[]> MyNames(CDBContext Context)
		{
			CEntityName[]										Result=await Context.EntitiesNames.ToArrayAsync();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CEntityName> MyName(int ID, CDBContext Context)
		{
			CEntityName											Result=await Context.EntitiesNames.Where(P => P.ID==ID).FirstOrDefaultAsync();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CType[] MyTypes()
		{
			CType												Type1=new CType(10,100,1000,10000,100000,111.111,"AAA",DateTime.Now,DateTimeOffset.Now,TimeSpan.FromDays(1),new Uri("https://localhost:1000"),Guid.NewGuid());
			CType												Type2=new CType(20,200,2000,20000,200000,222.222,"BBB",DateTime.Now,DateTimeOffset.Now,TimeSpan.FromDays(2),new Uri("https://localhost:2000"),Guid.NewGuid());
			CType[]												Result=new CType[]{Type1,Type2};

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CRelations11Parent[] MyRelations11()
		{
			CRelations11Child									Child1=new CRelations11Child("CHILD 1 - AAA","CHILD 1 - BBB");
			CRelations11Child									Child2=new CRelations11Child("CHILD 2 - AAA","CHILD 2 - BBB");

			CRelations11Parent									Parent1=new CRelations11Parent("PARENT 1 - AAA","PARENT 1 - BBB",Child1);
			CRelations11Parent									Parent2=new CRelations11Parent("PARENT 2 - AAA","PARENT 2 - BBB",Child2);

			CRelations11Parent[]								Result=new CRelations11Parent[]{Parent1,Parent2};

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CRelations1NParent[] MyRelations1N()
		{
			CRelations1NChild									Child11=new CRelations1NChild("CHILD 11 - AAA","CHILD 11 - BBB");
			CRelations1NChild									Child12=new CRelations1NChild("CHILD 12 - AAA","CHILD 12 - BBB");
			CRelations1NChild									Child21=new CRelations1NChild("CHILD 21 - AAA","CHILD 21 - BBB");
			CRelations1NChild									Child22=new CRelations1NChild("CHILD 22 - AAA","CHILD 22 - BBB");

			CRelations1NParent									Parent1=new CRelations1NParent("PARENT 1 - AAA","PARENT 1 - BBB",new CRelations1NChild[]{Child11,Child12});
			CRelations1NParent									Parent2=new CRelations1NParent("PARENT 2 - AAA","PARENT 2 - BBB",new CRelations1NChild[]{Child21,Child22});

			CRelations1NParent[]								Result=new CRelations1NParent[]{Parent1,Parent2};

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------