using System;

namespace RefExample
{
    class Program
    {
        static void Swap(ref int x, ref int y)
        {
            int temp = x;
            x = y;
            y = temp;
        }
        static void Main(string[] args)
        {
            int i = 1;
            int j = 2;
            int k;
            Swap(ref i, ref j);
            Console.WriteLine("{0} {1}", i, j);
            Console.WriteLine(k);
        }
    }
}
