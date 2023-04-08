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

	Name.NameMethod=function()
	{
		// !!! KEYWORD 'this' sa v METHODS pouziva na pristup k OBJECT.
		document.write("<p>Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "] !</p>");

		// !!! Pridam NOVY FIELD do CLASS.
		this.FriendName="Jenny Thompson";

		document.write("<p>Friend name: [" + this.FriendName + "] !</p>");

		// !!! Iny pristup k FIELD.
		document.write("<p>Friend name: [" + this["FriendName"] + "] !</p>");
	}

	Name.NameMethod();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Spusti sa funkcia TestFunction().
TestFunction();
//-------------------------------------------------------------------------------------------------------