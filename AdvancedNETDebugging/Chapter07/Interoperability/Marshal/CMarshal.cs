using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace MyMarshal
{
//-------------------------------------------------------------------------------------------------------
	class CMarshal
	{
//-------------------------------------------------------------------------------------------------------
		public const int										TableSize=50;
//-------------------------------------------------------------------------------------------------------
        [DllImport("MyNative.dll")]
        private static extern void MyFunc(IntPtr Ptr);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void Run()
        {
            CNode[]				Nodes=new CNode[CMarshal.TableSize];

            Nodes[0]=new CNode();
            Nodes[0].First="First Name 1";
            Nodes[0].Last="Last Name 1";
            Nodes[0].Social="Social 1";
            Nodes[0].Age=30;

            Nodes[1]=new CNode();
            Nodes[1].First="First Name 2";
            Nodes[1].Last="Last Name 2";
            Nodes[1].Social="Social 2";
            Nodes[1].Age=31;

            Nodes[2]=new CNode();
            Nodes[2].First="First Name 3";
            Nodes[2].Last="Last Name 3";
            Nodes[2].Social="Social 3";
            Nodes[2].Age=32;

            CTable				T=new CTable();

            T.Aux=IntPtr.Zero;

            T.Nodes=new IntPtr[CMarshal.TableSize];

            for (int i=0;i<CMarshal.TableSize && Nodes[i]!=null;i++)
            {
                int				NodeSize=Marshal.SizeOf(typeof(CNode));

                T.Nodes[i]=Marshal.AllocHGlobal(NodeSize);
                Marshal.StructureToPtr(Nodes[i], T.Nodes[i], false);
            }

            int					TableSize=Marshal.SizeOf(typeof(CTable));
            IntPtr				PTable=Marshal.AllocHGlobal(TableSize);

            Marshal.StructureToPtr(T, PTable, false);

            MyFunc(PTable); 
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

            CMarshal				P=new CMarshal();

            P.Run();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------