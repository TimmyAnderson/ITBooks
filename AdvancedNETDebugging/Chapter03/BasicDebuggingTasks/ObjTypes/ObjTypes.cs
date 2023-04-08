using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ObjTypes
{
//-------------------------------------------------------------------------------------------------------
	public class ObjTypes
	{
//-------------------------------------------------------------------------------------------------------
        public struct Coordinate
        {
//-------------------------------------------------------------------------------------------------------
            public int											MXCord;
            public int											MYCord;
            public int											MZCord;
//-------------------------------------------------------------------------------------------------------
            public Coordinate(int X, int Y, int Z)
            {
                MXCord=X;
                MYCord=Y;
                MZCord=Z;
            }
//-------------------------------------------------------------------------------------------------------
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private Coordinate										MCoordinate;
        private int[]											MIntArray=new int[] { 1, 2, 3, 4, 5 };
        private string[]										MStrArray=new string[] {"Welcome", "to", "Advanced", ".NET", "Debugging"};
        private CName[]											MNames=new CName[] {new CName("Timmy","Anderson",12),new CName("Jenny","Thompson",13)};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void AddCoordinate(Coordinate Coord)
        {
            MCoordinate.MXCord+=Coord.MXCord;
            MCoordinate.MXCord+=Coord.MYCord;
            MCoordinate.MZCord+=Coord.MZCord;

            Console.WriteLine("Data - X: [{0}], Y: [{1}], Z: [{2}] !", MCoordinate.MXCord, MCoordinate.MYCord, MCoordinate.MZCord);
        }
//-------------------------------------------------------------------------------------------------------
        public void PrintArrays()
        {
            foreach (int I in MIntArray)
                Console.WriteLine("Int: [{0}]", I);

            foreach (string S in MStrArray)
                Console.WriteLine("Str: [{0}] !", S);
        }
//-------------------------------------------------------------------------------------------------------
        public void ThrowException(ObjTypes Obj)
        {
            if (Obj==null)
                throw(new System.ArgumentException("Obj cannot be null !"));
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Coordinate			Point=new Coordinate(100, 100, 100);

            Console.WriteLine("Press any key to continue (AddCoordinate) !");
            Console.ReadKey();

            ObjTypes			Ob=new ObjTypes();

            Ob.AddCoordinate(Point);

            Console.WriteLine("Press any key to continue (Arrays) !");
            Console.ReadKey();

            Ob.PrintArrays();
            
            Console.WriteLine("Press any key to continue (Generics) !");
            Console.ReadKey();

            Comparer<int>		C=new Comparer<int>();

            Console.WriteLine("Greater [{0}] !", C.GreaterThan(5, 10));

            Console.WriteLine("Press any key to continue (Exception) !");
            Console.ReadKey();

			// Generuje UNHANDLED EXCEPTION.
            Ob.ThrowException(null);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------