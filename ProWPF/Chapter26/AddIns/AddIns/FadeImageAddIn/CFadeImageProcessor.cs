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
namespace FadeImageAddIn
{
//------------------------------------------------------------------------
	[AddIn("Fade Image Processor", Version = "1.0.0.0", Publisher="SupraImage", Description="Darkens the picture.")]
	public class CFadeImageProcessor : CImageProcessorAddInView
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
			Random			Rand=new Random();
			int				Offset=Rand.Next(0, 10);

			for (int i=0;i<Pixels.Length-1-Offset;i++)
			{
				if (((i+Offset)%5)==0)
					Pixels[i]=0;

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