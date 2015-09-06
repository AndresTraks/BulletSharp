using System;

namespace BulletSharpTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var tests = new BulletTests();
            tests.Run();

            Console.WriteLine("Finished");
            Console.ReadKey();
        }
    }
}
