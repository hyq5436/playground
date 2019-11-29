using System;

namespace OutputParameterExample
{
    class Program
    {
        static void Divide(int x, int y, out int result, out int remainder)
        {
            result = x / y;
            remainder = x % y;
        }

        static void Main(string[] args)
        {
            int result;
            int remainder;
            Divide(10, 3, out result, out remainder);
            Console.WriteLine(result);
            Console.WriteLine(remainder);
        }
    }
}
