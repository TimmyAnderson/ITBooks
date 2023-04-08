using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Media;
//------------------------------------------------------------------------
// 1. Program demonstruje zitenie Tier danej grafickej karty.
// 2. Tier je ohodnotenie karty podla toho ktore capabilities podporuje. Cim vyssie cislo tym lespie. Momentalne je interval od 0-2.
//------------------------------------------------------------------------
namespace GraphicsCardTier
{
//------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------
		static void Main(string[] args)
		{
			int			RenderingTier=(RenderCapability.Tier>>16);

			Console.WriteLine(string.Format("Tier is: {0} !",RenderingTier));
			Console.ReadLine();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------