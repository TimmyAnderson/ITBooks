using HotChocolate.Execution.Configuration;
using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//--------------------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
        public static void Main(string[] args)
        {
            WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

            Builder.Services.AddControllers();

            Builder.Services.AddEndpointsApiExplorer();
            Builder.Services.AddSwaggerGen();

			string												ConnectionString=Builder.Configuration.GetConnectionString("MyConnection");

			// !!! DB CONTEXT sa prida DB CONTEXT FACTORY vyuzivajuca DB CONTEXT POOL.
			Builder.Services.AddPooledDbContextFactory<CDBContext>(P => ConfigureDbContext(P,ConnectionString));

			// !!! Zaregistruje sa CUSTOM SERVICE.
			Builder.Services.AddTransient<IMyLoggerService,CMyLoggerService>();

			// !!! Prida sa GRAPH QL SERVER.
			IRequestExecutorBuilder								GraphQLBuilder=Builder.Services.AddGraphQLServer();

			GraphQLBuilder.AddQueryType<CMyQueriesObjectType>();
			GraphQLBuilder.AddMutationType<CMyMutations>();

			// !!! Zaregistruju sa OBJECT TYPES pre TYPES, ktore implementuju INTERFACE.
			GraphQLBuilder.AddType<CObjectTypeInterfacesMyInterface1>();
			GraphQLBuilder.AddType<CObjectTypeInterfacesMyInterface2>();

			// !!! V GRAPH QL sa zaregistruje DB CONTEXT CLASS, aby GRAPH QL vyuzival DB CONTEXT POOL.
			GraphQLBuilder.RegisterDbContextFactory<CDBContext>();

			// !!! Povoli sa FILTERING.
			GraphQLBuilder.AddFiltering();

			// !!! Povoli sa SORTING.
			GraphQLBuilder.AddSorting();

            WebApplication										Application=Builder.Build();

            if (Application.Environment.IsDevelopment()==true)
            {
                Application.UseSwagger();
                Application.UseSwaggerUI();
            }

            Application.UseHttpsRedirection();

            Application.UseAuthorization();

            Application.MapControllers();

			// !!! Prida sa GRAPH QL ENDPOINT.
			Application.MapGraphQL();

			// !!! Prida sa SCHEMA VISUALISER.
			Application.MapGraphQLVoyager("/voyager");

			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
        }
//--------------------------------------------------------------------------------------------------------------------------------
    }
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------