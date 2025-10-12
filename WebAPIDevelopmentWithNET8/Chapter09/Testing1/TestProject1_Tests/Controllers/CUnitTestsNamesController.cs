using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FluentAssertions;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Moq;
using Testing1;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CUnitTestsNamesController
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task GetNamesOK()
		{
			Mock<ILogger<NamesController>>						MockLogger=new Mock<ILogger<NamesController>>();

			MockLogger.Setup(P => P.Log(It.IsAny<LogLevel>(),It.IsAny<EventId>(), It.IsAny<It.IsAnyType>(),It.IsAny<Exception>(), (Func<It.IsAnyType,Exception,string>)It.IsAny<object>())).Verifiable();

			Mock<IDBOperationsService>							MockDBOperationsService=new Mock<IDBOperationsService>();

			CEntityName[]										InputNames=new CEntityName[]{new CEntityName(1,"Timmy","Anderson",12,ESex.E_MALE),new CEntityName(2,"Jenny","Thompson",13,ESex.E_FEMALE)};

			MockDBOperationsService.Setup(P => P.GetNames()).ReturnsAsync(InputNames).Verifiable();

			ILogger<NamesController>							Logger=MockLogger.Object;
			IDBOperationsService								DBOperationsService=MockDBOperationsService.Object;

			NamesController										Controller=new NamesController(Logger,DBOperationsService);

			ActionResult										Result=await Controller.GetNames();

			Assert.NotNull(Result);

			OkObjectResult										TypedResult=Assert.IsAssignableFrom<OkObjectResult>(Result);

			object												RawValue=TypedResult.Value;

			Assert.NotNull(RawValue);

			CEntityName[]										OutputNames=Assert.IsAssignableFrom<CEntityName[]>(RawValue);

			Assert.Equal(InputNames.Length,OutputNames.Length);

			for(int Index=0;Index<InputNames.Length;Index++)
			{
				CEntityName										InputName=InputNames[Index];
				CEntityName										OutputName=OutputNames[Index];

				Assert.NotNull(OutputName);

				Assert.Equal(InputName.ID,OutputName.ID);
				Assert.Equal(InputName.FirstName,OutputName.FirstName);
				Assert.Equal(InputName.LastName,OutputName.LastName);
				Assert.Equal(InputName.Age,OutputName.Age);
				Assert.Equal(InputName.Sex,OutputName.Sex);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task GetNamesError()
		{
			Mock<ILogger<NamesController>>						MockLogger=new Mock<ILogger<NamesController>>();

			MockLogger.Setup(P => P.Log(It.IsAny<LogLevel>(),It.IsAny<EventId>(),It.IsAny<It.IsAnyType>(),It.IsAny<Exception>(),(Func<It.IsAnyType,Exception,string>)It.IsAny<object>())).Verifiable();

			Mock<IDBOperationsService>							MockDBOperationsService=new Mock<IDBOperationsService>();

			Exception											InputException=new Exception("TEST ERROR.");

			MockDBOperationsService.Setup(P => P.GetNames()).Throws(() => InputException).Verifiable();

			ILogger<NamesController>							Logger=MockLogger.Object;
			IDBOperationsService								DBOperationsService=MockDBOperationsService.Object;

			NamesController										Controller=new NamesController(Logger,DBOperationsService);

			Exception											OutputException=await Assert.ThrowsAsync<Exception>(() => Controller.GetNames());

			Assert.Equal(InputException.Message,OutputException.Message);

			// !!! Vykona sa kontrola ci doslo k zavolaniu LOG METHOD.
			MockLogger.Verify(P => P.Log(It.IsAny<LogLevel>(),It.IsAny<EventId>(),It.IsAny<It.IsAnyType>(),It.Is<Exception>((P1,P2) => P1.ToString().Contains(InputException.Message)),(Func<It.IsAnyType,Exception,string>)It.IsAny<object>()),Times.Once);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task GetNamesOKFluentAssertion()
		{
			Mock<ILogger<NamesController>>						MockLogger=new Mock<ILogger<NamesController>>();

			MockLogger.Setup(P => P.Log(It.IsAny<LogLevel>(),It.IsAny<EventId>(), It.IsAny<It.IsAnyType>(),It.IsAny<Exception>(), (Func<It.IsAnyType,Exception,string>)It.IsAny<object>())).Verifiable();

			Mock<IDBOperationsService>							MockDBOperationsService=new Mock<IDBOperationsService>();

			CEntityName[]										InputNames=new CEntityName[]{new CEntityName(1,"Timmy","Anderson",12,ESex.E_MALE),new CEntityName(2,"Jenny","Thompson",13,ESex.E_FEMALE)};

			MockDBOperationsService.Setup(P => P.GetNames()).ReturnsAsync(InputNames).Verifiable();

			ILogger<NamesController>							Logger=MockLogger.Object;
			IDBOperationsService								DBOperationsService=MockDBOperationsService.Object;

			NamesController										Controller=new NamesController(Logger,DBOperationsService);

			ActionResult										Result=await Controller.GetNames();

			// !!! LIBRARY FLUENT ASSERTIONS umoznuje definovant CUSTOM ERROR MESSAGES.
			Result.Should().NotBeNull("RESULT is NULL.");

			OkObjectResult										TypedResult=Assert.IsAssignableFrom<OkObjectResult>(Result);

			object												RawValue=TypedResult.Value;

			RawValue.Should().NotBeNull("RAW VALUE is NULL.");

			CEntityName[]										OutputNames=Assert.IsAssignableFrom<CEntityName[]>(RawValue);

			OutputNames.Length.Should().Be(InputNames.Length,"NAMES ARRAY doesn't have EXPECTED LENGTH.");

			for(int Index=0;Index<InputNames.Length;Index++)
			{
				CEntityName										InputName=InputNames[Index];
				CEntityName										OutputName=OutputNames[Index];

				OutputName.Should().NotBeNull($"NAMES ARRAY ITEM [{Index}] is NULL.");

				OutputName.ID.Should().Be(InputName.ID,$"NAMES ARRAY ITEM [{Index}] PROPERTY [{nameof(OutputName.ID)}] has UNEXPECTED VALUE.");
				OutputName.FirstName.Should().Be(InputName.FirstName,$"NAMES ARRAY ITEM [{Index}] PROPERTY [{nameof(OutputName.FirstName)}] has UNEXPECTED VALUE.");
				OutputName.LastName.Should().Be(InputName.LastName,$"NAMES ARRAY ITEM [{Index}] PROPERTY [{nameof(OutputName.LastName)}] has UNEXPECTED VALUE.");
				OutputName.Age.Should().Be(InputName.Age,$"NAMES ARRAY ITEM [{Index}] PROPERTY [{nameof(OutputName.Age)}] has UNEXPECTED VALUE.");
				OutputName.Sex.Should().Be(InputName.Sex,$"NAMES ARRAY ITEM [{Index}] PROPERTY [{nameof(OutputName.Sex)}] has UNEXPECTED VALUE.");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task GetNamesErrorFluentAssertion()
		{
			Mock<ILogger<NamesController>>						MockLogger=new Mock<ILogger<NamesController>>();

			MockLogger.Setup(P => P.Log(It.IsAny<LogLevel>(),It.IsAny<EventId>(),It.IsAny<It.IsAnyType>(),It.IsAny<Exception>(),(Func<It.IsAnyType,Exception,string>)It.IsAny<object>())).Verifiable();

			Mock<IDBOperationsService>							MockDBOperationsService=new Mock<IDBOperationsService>();

			Exception											InputException=new Exception("TEST ERROR.");

			MockDBOperationsService.Setup(P => P.GetNames()).Throws(() => InputException).Verifiable();

			ILogger<NamesController>							Logger=MockLogger.Object;
			IDBOperationsService								DBOperationsService=MockDBOperationsService.Object;

			NamesController										Controller=new NamesController(Logger,DBOperationsService);

			Func<Task<ActionResult>>							TestAction=() => Controller.GetNames();

			// !!!!! Pomocou LIBRARY FLUENT ASSERTIONS sa testuje ci METHOD naozaj hodila EXCEPTION s danou MESSAGE.
			await TestAction.Should().ThrowAsync<Exception>().WithMessage(InputException.Message);

			// !!! Vykona sa kontrola ci doslo k zavolaniu LOG METHOD.
			MockLogger.Verify(P => P.Log(It.IsAny<LogLevel>(),It.IsAny<EventId>(),It.IsAny<It.IsAnyType>(),It.Is<Exception>((P1,P2) => P1.ToString().Contains(InputException.Message)),(Func<It.IsAnyType,Exception,string>)It.IsAny<object>()),Times.Once);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------