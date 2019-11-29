using System;

namespace ArrayExample
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] a = new int[8];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = i;
            }
            for (int i = 0; i < a.Length; i++)
            {
                Console.WriteLine("array[{0}]: {1}", i, i);
                Console.WriteLine($"array[{i}] = {a[i]}");
            }
        }
    }
}
