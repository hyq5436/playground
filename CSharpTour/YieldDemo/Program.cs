using System;

namespace YieldDemo
{
    class Program
    {
        static System.Collections.Generic.IEnumerable<int> Range(int start, int end)
        {
            for(int i = start; i < end; i++)
            {
                yield return i;
            }
        }
        static void Main(string[] args)
        {
            foreach(int i in Range(-10, 10))
            {
                Console.WriteLine(i);
            }
        }
    }
}
