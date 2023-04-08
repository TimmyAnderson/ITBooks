using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.AddIn;
using AddInView;
//------------------------------------------------------------------------
// 1. V projekte je nastavena referencia na AddInView.DLL pricom Copy Local MUSI BYT NASTAVENY NA FALSE.
// 2. Trieda implementuje AddIn.
// 3. Data modifikuje na mieste a nevytvara novy objekt byte[], ale modifikuje existujuci.
//------------------------------------------------------------------------
namespace NegativeImageAddIn
{
//------------------------------------------------------------------------
	[AddIn("Negative Image Processor", Version="1.0.0.0", Publisher="Imaginomics", Description = "Inverts colors to look like a photo negative.")]
	public class CNegativeImageProcessor : CImageProcessorAddInView
	{
//------------------------------------------------------------------------
		private CHostObject					MHost;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override void Initialize(CHostObject HostObj)
		{
			MHost=HostObj;
		}
//------------------------------------------------------------------------
		public override byte[] ProcessImageBytes(byte[] Pixels)
		{
			int				Iteration=Pixels.Length/100;

			for (int i=0;i<Pixels.Length-2;i++)
			{
				// Assuming 24-bit, color, each pixel has three bytes of data.
				Pixels[i]=(byte)(255-Pixels[i]);
				Pixels[i+1]=(byte)(255-Pixels[i+1]);
				Pixels[i+2]=(byte)(255-Pixels[i+2]);

				// !!! Volam Callback aby sa prekresli ProgressBar v klientovi.
				if ((i%Iteration)==0)
				{
					// Umyselne spomalim, aby bolo vidiet progres v ProgressBar.
					// !!!!! Progress vsak nevidiet. Bolo by treba robit v AddIn volanie Callback v INOM THREADE sa samozrejme vsetko synchronizovat cez Dispatcher.
					Thread.Sleep(10);

					MHost.ReportProgress(i/Iteration);
				}
			}

			return(Pixels);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------