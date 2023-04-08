//-------------------------------------------------------------------------------------------------------
function TestFunction()
{
	// !!! Definujem CLASS.
	var															Name=
	{
		FirstName: "Timmy",
		LastName: "Anderson",
		Age: 12
	};

    document.write("<p>Name: [" + Name.FirstName + " " + Name.LastName + "], Age: [" + Name.Age + "] !</p>");

	// !!! Pridam NOVY FIELD do CLASS.
	Name.FriendName="Jenny Thompson";

    document.write("<p>Friend name: [" + Name.FriendName + "] !</p>");

	// !!! Iny pristup k FIELD.
    document.write("<p>Friend name: [" + Name["FriendName"] + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Spusti sa funkcia TestFunction().
TestFunction();
//-------------------------------------------------------------------------------------------------------