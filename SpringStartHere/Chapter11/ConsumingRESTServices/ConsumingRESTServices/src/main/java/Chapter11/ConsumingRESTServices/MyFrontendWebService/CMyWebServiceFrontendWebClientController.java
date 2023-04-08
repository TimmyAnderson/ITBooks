package Chapter11.ConsumingRESTServices.MyFrontendWebService;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Collection;
import java.util.Optional;
import java.util.UUID;
import java.util.concurrent.CompletableFuture;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.reactive.function.client.WebClient;
import org.springframework.web.reactive.function.client.WebClient.RequestBodyUriSpec;
import org.springframework.web.reactive.function.client.WebClient.ResponseSpec;
import reactor.core.publisher.Mono;
import Chapter11.ConsumingRESTServices.Helpers.CHelpers;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendRequest;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendResponse;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONTROLLER implementuje BACKEND SERVICE, ktory je volany z FRONTEND SERVICE pomocou JAVA WEB CLIENT WEB CLIENT.
@RestController
public class CMyWebServiceFrontendWebClientController
{
//----------------------------------------------------------------------------------------------------------------------
	private static String GetHeader(String HeaderName, MultiValueMap<String,String> BackendHeaders)
	{
		Collection<String>										Values=BackendHeaders.get(HeaderName);

		if (Values!=null && Values.isEmpty()==false)
		{
			Optional<String>									Value=Values.stream().findFirst();
			
			if (Value.isPresent()==true)
			{
				return(Value.get());
			}
		}

		return("");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD je spustena ASYNCHRONNE na SEPARATNOM THREAD.
	private static CMyWebServiceFrontendResponse1 AsynchronousMethod(CMyWebServiceFrontendRequest Request)
	{
		System.out.format("TIME [%s] - THREAD [%s] - ASYNCHRONOUS METHOD STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
		
		String													FrontendID="AAA";
		String													BackendID="BBB";
		String													Value1=Request.getValue1().toUpperCase();
		String													Value2=Request.getValue2().toUpperCase();
		CMyWebServiceFrontendResponse1							ResponseBody=new CMyWebServiceFrontendResponse1(FrontendID,BackendID,Value1,Value2);

		try
		{
			Thread.sleep(500);
		}
		catch(InterruptedException E)
		{
			System.out.format("EXCEPTION [%s].",E.getMessage());
		}

		System.out.format("TIME [%s] - THREAD [%s] - ASYNCHRONOUS METHOD FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		return(ResponseBody);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD je spustena ASYNCHRONNE na SEPARATNOM THREAD.
	private static CMyWebServiceBackendRequest AsynchronousMethodCreateBody(CMyWebServiceFrontendRequest Request)
	{
		System.out.format("TIME [%s] - THREAD [%s] - ASYNCHRONOUS METHOD CREATE BODY STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
		
		CMyWebServiceBackendRequest								ResponseBody=new CMyWebServiceBackendRequest(Request.getValue1(),Request.getValue2());

		try
		{
			Thread.sleep(500);
		}
		catch(InterruptedException E)
		{
			System.out.format("EXCEPTION [%s].",E.getMessage());
		}

		System.out.format("TIME [%s] - THREAD [%s] - ASYNCHRONOUS METHOD CREATE BODY FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		return(ResponseBody);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD je spustena ASYNCHRONNE na SEPARATNOM THREAD po vykonani HTTP REQUEST na WEB SERVICE.
	private static Mono<ResponseEntity<CMyWebServiceFrontendResponse2>> AsynchronousMethodProcessResponse(ResponseEntity<CMyWebServiceBackendResponse> BackendResponse)
	{
		System.out.format("TIME [%s] - THREAD [%s] - ASYNCHRONOUS METHOD PROCESS RESPONSE STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
	
		MultiValueMap<String,String>							ResponseHttpHeaders=BackendResponse.getHeaders();
		CMyWebServiceBackendResponse							BackendResponseBody=BackendResponse.getBody();
		
		String													FrontendID=UUID.randomUUID().toString();
		String													BackendResponseMyHeader1=GetHeader("MyHeader1",ResponseHttpHeaders);
		String													BackendResponseMyHeader2=GetHeader("MyHeader2",ResponseHttpHeaders);
		String													BackendID=BackendResponseBody.getBackendID();
		String													Value1=BackendResponseBody.getValue1();
		String													Value2=BackendResponseBody.getValue2();
		CMyWebServiceFrontendResponse2							ResponseBody=new CMyWebServiceFrontendResponse2(FrontendID,BackendResponseMyHeader1,BackendResponseMyHeader2,BackendID,Value1,Value2);
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.OK;
		ResponseEntity<CMyWebServiceFrontendResponse2>			Response=new ResponseEntity<CMyWebServiceFrontendResponse2>(ResponseBody,ResponseHeaders,ResponseStatus);
		Mono<ResponseEntity<CMyWebServiceFrontendResponse2>>	MonoResponse=Mono.just(Response);
	
		try
		{
			Thread.sleep(500);
		}
		catch(InterruptedException E)
		{
			System.out.format("EXCEPTION [%s].",E.getMessage());
		}

		System.out.format("TIME [%s] - THREAD [%s] - ASYNCHRONOUS METHOD PROCESS RESPONSE FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		return(MonoResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! WEB SERICE je REACTIVE, pretoze vracia instanciu CLASS [Mono<T>] co je ANALOGIA .NET TASK.
	// CURL [curl -v -X POST localhost:8080/MyWebServiceFrontendWebClientPost1 -H "Content-Type: application/json" -H "MyHeader1: 123" -H "MyHeader2: 456" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceFrontendWebClientPost1")
	public Mono<CMyWebServiceFrontendResponse1> MyWebServiceFrontendWebClientPost1(@RequestBody CMyWebServiceFrontendRequest Request)
	{
		System.out.format("TIME [%s] - THREAD [%s] - FRONTEND SERVICE 1 STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		String													FrontendID="AAA";
		String													BackendID="BBB";
		String													Value1=Request.getValue1().toUpperCase();
		String													Value2=Request.getValue2().toUpperCase();
		CMyWebServiceFrontendResponse1							ResponseBody=new CMyWebServiceFrontendResponse1(FrontendID,BackendID,Value1,Value2);
		
		// !!!!! CLASS [Mono<T>] je ANALOGIA .NET TASK.
		// !!!!! Instancia CLASS [Mono<T>] sa vytvori z existujuceho OBJECT, ktory je vytvoreny na CURRENT THREAD.
		Mono<CMyWebServiceFrontendResponse1>					Response=Mono.just(ResponseBody);

		System.out.format("TIME [%s] - THREAD [%s] - FRONTEND SERVICE 1 FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
		
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! WEB SERICE je REACTIVE, pretoze vracia instanciu CLASS [Mono<T>] co je ANALOGIA .NET TASK.
	// CURL [curl -v -X POST localhost:8080/MyWebServiceFrontendWebClientPost2 -H "Content-Type: application/json" -H "MyHeader1: 123" -H "MyHeader2: 456" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceFrontendWebClientPost2")
	public Mono<CMyWebServiceFrontendResponse1> MyWebServiceFrontendWebClientPost2(@RequestBody CMyWebServiceFrontendRequest Request)
	{
		System.out.format("TIME [%s] - THREAD [%s] - FRONTEND SERVICE 2 STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		// !!!!! Vytvori instanciu CLASS [CompletableFuture<T>], ktora ASYNCHRONNE spusti instanciu INTERFACE [Supplier<T>].
		// !!!!! Za INTERFACE [Supplier<T>] je mozne dosadit LAMBDA EXPRESSION.
		CompletableFuture<CMyWebServiceFrontendResponse1>		Future=CompletableFuture.supplyAsync(() -> AsynchronousMethod(Request));
		
		// !!!!! CLASS [Mono<T>] je ANALOGIA .NET TASK.
		// !!!!! Instancia CLASS [Mono<T>] sa vytvori pomocou CLASS [CompletableFuture<T>], ktora sa spusta ASYNCHRONNE na INOM THREAD.
		// !!!!! CURRENT THREAD NECAKA na skoncenie CLASS [CompletableFuture<T>], ale okamzite pokracuje dalej v dalsom CODE.
		Mono<CMyWebServiceFrontendResponse1>					Response=Mono.fromFuture(Future);

		System.out.format("TIME [%s] - THREAD [%s] - FRONTEND SERVICE 2 FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
		
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! WEB SERICE je REACTIVE, pretoze vracia instanciu CLASS [Mono<T>] co je ANALOGIA .NET TASK.
	// CURL [curl -v -X POST localhost:8080/MyWebServiceFrontendWebClientPost3 -H "Content-Type: application/json" -H "MyHeader1: 123" -H "MyHeader2: 456" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceFrontendWebClientPost3")
	public Mono<ResponseEntity<CMyWebServiceFrontendResponse2>> MyWebServiceFrontendWebClientPost3(@RequestBody CMyWebServiceFrontendRequest Request)
	{
		System.out.format("TIME [%s] - THREAD [%s] - FRONTEND SERVICE 3 STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
		
		String													MyHeader1="EEE " + UUID.randomUUID().toString();
		String													MyHeader2="FFF " + UUID.randomUUID().toString();
	
		WebClient												Client=WebClient.create();
	
		// URL MUSI obsahovat PROTOCOL.
		String													RequestURL="http://localhost:8080/MyWebServiceBackendPost";
		RequestBodyUriSpec										BodyUriSpec=Client.post();
		
		BodyUriSpec.uri(RequestURL);

		BodyUriSpec.header("MyHeader1",MyHeader1);
		BodyUriSpec.header("MyHeader2",MyHeader2);
	
		// !!!!! Vytvori instanciu CLASS [CompletableFuture<T>], ktora ASYNCHRONNE spusti instanciu INTERFACE [Supplier<T>].
		// !!!!! Za INTERFACE [Supplier<T>] je mozne dosadit LAMBDA EXPRESSION.
		CompletableFuture<CMyWebServiceBackendRequest>			Future=CompletableFuture.supplyAsync(() -> AsynchronousMethodCreateBody(Request));

		// !!!!! CLASS [Mono<T>] je ANALOGIA .NET TASK.
		// !!!!! Instancia CLASS [Mono<T>] sa vytvori pomocou CLASS [CompletableFuture<T>], ktora sa spusta ASYNCHRONNE na INOM THREAD.
		// !!!!! CURRENT THREAD NECAKA na skoncenie CLASS [CompletableFuture<T>], ale okamzite pokracuje dalej v dalsom CODE.
		Mono<CMyWebServiceBackendRequest>						Response=Mono.fromFuture(Future);

		BodyUriSpec.body(Response,CMyWebServiceBackendRequest.class);

		// !!!!! Vykona SCHEDULING TASK, ktory ma vykonat HTTP REQUEST na WEB SERVICE.
		ResponseSpec											SpecResponse=BodyUriSpec.retrieve();

		// !!!!! Vrati INSTANCIU CLASS [Mono<ResponseEntity<T>>], ktora obsahuje MONO OBJECT s HTTP RESPONSE vratenym z WEB SERVICE.
		Mono<ResponseEntity<CMyWebServiceBackendResponse>>		MonoResponseEnity=SpecResponse.toEntity(CMyWebServiceBackendResponse.class);

		// !!!!! POMOCOU METHOD [<R> Mono<R> flatMap(Function<? super T, ? extends Mono<? extends R>> Transformer)] sa definuje novy TASK, ktory transformuje instanciu CLASS [ResponseEntity<CMyWebServiceBackendResponse>] na instanciu CLASS [ResponseEntity<CMyWebServiceFrontendResponse2>].
		Mono<ResponseEntity<CMyWebServiceFrontendResponse2>>	ResponseMono=MonoResponseEnity.flatMap(Result -> AsynchronousMethodProcessResponse(Result));
		
		System.out.format("TIME [%s] - THREAD [%s] - FRONTEND SERVICE 3 FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		// !!!!! METHOD skonci este predtym ako sa zavola skonci TASK vytvarajuci HTTP REQUEST BODY pre BACKEND SERVICE.
		return(ResponseMono);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------