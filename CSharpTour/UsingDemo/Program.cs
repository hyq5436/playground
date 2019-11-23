using System;
using System.IO;

namespace UsingDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            using (TextWriter w = File.CreateText("test.txt"))
            {
                w.WriteLine("Line one");
                w.WriteLine("Line two");
                w.WriteLine("Line three");
            }
        }
    }
}
