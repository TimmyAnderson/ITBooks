//-------------------------------------------------------------------------------------------------------
// !!! Ak chcem do JQUERY vlozit METHOD, musim ju ulozit ako PROPERTY PROTOTYPE OBJECT 'jQuery.fn'.
jQuery.fn.PrintAllValuesIntoTextBox=function(TextBox)
{
	for(var Index=0;Index<this.length;Index++)
	{
		var														Element=this[Index];

		TextBox.value+="VALUE [" + Element.value + "] !\n";
	}

	// !!! Ak chcem METHOD CHAINING, musim vratit JQUERY OBJECT.
	return(this);
}
//-------------------------------------------------------------------------------------------------------
// !!! Ak chcem do JQUERY vlozit STATIC METHOD, musim ju ulozit ako PROPERTY PROTOTYPE OBJECT 'jQuery'.
jQuery.MyAlert=function()
{
	window.alert("Hello from PLUGIN !");
}
//-------------------------------------------------------------------------------------------------------