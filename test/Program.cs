using System;
using BulletSharp;

namespace BulletSharpTest
{
    class Program
    {
        static void Main(string[] args)
        {
            BulletTests test1 = new BulletTests();
            test1.Run();

            SoftBodyTests test2 = new SoftBodyTests();
            test2.Run();

            CollisionAlgorithmTests test3 = new CollisionAlgorithmTests();
            test3.Run();

            TriangleMeshTest test4 = new TriangleMeshTest();
            test4.Run();

            Console.WriteLine("Finished");
            Console.ReadKey();
        }
    }
}
