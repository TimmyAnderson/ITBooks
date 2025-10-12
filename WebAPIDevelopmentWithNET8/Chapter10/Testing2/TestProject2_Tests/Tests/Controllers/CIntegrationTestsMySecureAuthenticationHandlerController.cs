using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.Extensions.DependencyInjection;
using Newtonsoft.Json;
using Testing2;
//--------------------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CIntegrationTestsMySecureAuthenticationHandlerController : IClassFixture<CWebApplicationFactoryAuthenticationHandler>
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									CONTENT_TYPE_TEXT_JSON="application/json";
		private const string									CONTENT_TYPE_CHARSERT_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										CHAR_SET_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly CWebApplicationFactoryAuthenticationHandler	MFactory;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CIntegrationTestsMySecureAuthenticationHandlerController(CWebApplicationFactoryAuthenticationHandler Factory)
		{
			MFactory=Factory;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestGetClaimsOK()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				Client.DefaultRequestHeaders.Authorization=new AuthenticationHeaderValue(CAuthenticationHandlerTest.AUTHENTICATION_SCHEME);

				// !!!!! Pre jednoduchost sa CLAIMS prenesu v HEADERS do CUSTOM AUTHENTICATION HEADER, kde CUSTOM AUTHENTICATION HEADER spravi s HEADERS CLAIMS.
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_USER_NAME,"Timmy");
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_ROLE_1,CRoles.ROLE_1);
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_ROLE_2,CRoles.ROLE_2);
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_ROLE_3,CRoles.ROLE_3);

				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/GetClaims");

				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CSecureClaims									SecureClaims=JsonConvert.DeserializeObject<CSecureClaims>(Content);
				
				Assert.NotNull(SecureClaims);

				Assert.Equal(CAuthenticationHandlerTest.AUTHENTICATION_SCHEME,SecureClaims.AuthenticationType);
				Assert.Equal("Timmy",SecureClaims.UserName);

				Assert.NotNull(SecureClaims.Claims);

				Assert.Equal(4,SecureClaims.Claims.Length);

				CSecureClaim									SecureClaimName=SecureClaims.Claims.Where(P => P.Value=="Timmy").FirstOrDefault();

				Assert.NotNull(SecureClaimName);
				Assert.Equal(ClaimTypes.Name,SecureClaimName.Type);

				CSecureClaim									SecureClaimRole1=SecureClaims.Claims.Where(P => P.Value==CRoles.ROLE_1).FirstOrDefault();

				Assert.NotNull(SecureClaimRole1);
				Assert.Equal(ClaimTypes.Role,SecureClaimRole1.Type);

				CSecureClaim									SecureClaimRole2=SecureClaims.Claims.Where(P => P.Value==CRoles.ROLE_2).FirstOrDefault();

				Assert.NotNull(SecureClaimRole2);
				Assert.Equal(ClaimTypes.Role,SecureClaimRole2.Type);

				CSecureClaim									SecureClaimRole3=SecureClaims.Claims.Where(P => P.Value==CRoles.ROLE_3).FirstOrDefault();

				Assert.NotNull(SecureClaimRole3);
				Assert.Equal(ClaimTypes.Role,SecureClaimRole3.Type);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestGetClaimsDefaultUserNameOK()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				Client.DefaultRequestHeaders.Authorization=new AuthenticationHeaderValue(CAuthenticationHandlerTest.AUTHENTICATION_SCHEME);

				// !!!!! Pre jednoduchost sa CLAIMS prenesu v HEADERS do CUSTOM AUTHENTICATION HEADER, kde CUSTOM AUTHENTICATION HEADER spravi s HEADERS CLAIMS.
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_ROLE_1,CRoles.ROLE_1);
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_ROLE_2,CRoles.ROLE_2);
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_ROLE_3,CRoles.ROLE_3);

				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/GetClaims");

				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CSecureClaims									SecureClaims=JsonConvert.DeserializeObject<CSecureClaims>(Content);
				
				Assert.NotNull(SecureClaims);

				Assert.Equal(CAuthenticationHandlerTest.AUTHENTICATION_SCHEME,SecureClaims.AuthenticationType);
				Assert.Equal(CWebApplicationFactoryAuthenticationHandler.DEFAULT_USER_NAME,SecureClaims.UserName);

				Assert.NotNull(SecureClaims.Claims);

				Assert.Equal(4,SecureClaims.Claims.Length);

				CSecureClaim									SecureClaimName=SecureClaims.Claims.Where(P => P.Value==CWebApplicationFactoryAuthenticationHandler.DEFAULT_USER_NAME).FirstOrDefault();

				Assert.NotNull(SecureClaimName);
				Assert.Equal(ClaimTypes.Name,SecureClaimName.Type);

				CSecureClaim									SecureClaimRole1=SecureClaims.Claims.Where(P => P.Value==CRoles.ROLE_1).FirstOrDefault();

				Assert.NotNull(SecureClaimRole1);
				Assert.Equal(ClaimTypes.Role,SecureClaimRole1.Type);

				CSecureClaim									SecureClaimRole2=SecureClaims.Claims.Where(P => P.Value==CRoles.ROLE_2).FirstOrDefault();

				Assert.NotNull(SecureClaimRole2);
				Assert.Equal(ClaimTypes.Role,SecureClaimRole2.Type);

				CSecureClaim									SecureClaimRole3=SecureClaims.Claims.Where(P => P.Value==CRoles.ROLE_3).FirstOrDefault();

				Assert.NotNull(SecureClaimRole3);
				Assert.Equal(ClaimTypes.Role,SecureClaimRole3.Type);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestGetClaimsError403()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				Client.DefaultRequestHeaders.Authorization=new AuthenticationHeaderValue(CAuthenticationHandlerTest.AUTHENTICATION_SCHEME);

				// !!!!! Pre jednoduchost sa CLAIMS prenesu v HEADERS do CUSTOM AUTHENTICATION HEADER, kde CUSTOM AUTHENTICATION HEADER spravi s HEADERS CLAIMS.
				Client.DefaultRequestHeaders.Add(CAuthenticationHandlerTest.HEADER_CLAIM_USER_NAME,"Timmy");

				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/GetClaims");

				Assert.True(ResponseMessage.StatusCode==HttpStatusCode.Forbidden);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------