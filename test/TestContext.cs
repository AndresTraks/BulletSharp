using System;
using System.Collections.Generic;

namespace BulletSharpTest
{
    abstract class TestContext
    {
        public abstract void Run();

        protected void ClearRefs()
        {
            disposeQueue.Clear();
        }

        protected void ForceGC()
        {
            GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced);
            GC.WaitForPendingFinalizers();
        }

        protected void TestWeakRefs()
        {
            foreach (var r in disposeQueue)
            {
                TestWeakRef(r.Key, r.Value);
            }
        }

        void TestWeakRef(string name, WeakReference wr)
        {
            if (wr.IsAlive)
            {
                Console.Write(name + " GC collection FAILED! ");
                Console.WriteLine("Gen: " + GC.GetGeneration(wr.Target));
            }
            else
            {
                //Console.WriteLine(name + " GC collection OK");
            }
        }

        Dictionary<string, WeakReference> disposeQueue = new Dictionary<string, WeakReference>();
        protected void AddToDisposeQueue(object obj, string name = "")
        {
            var r = new WeakReference(obj);
            if (name.Length == 0)
            {
                name = obj.GetType().Name;
            }
            if (disposeQueue.ContainsKey(name))
            {
                int i = 2;
                var name2 = name + i.ToString();
                while (disposeQueue.ContainsKey(name2))
                {
                    i++;
                    name2 = name + i.ToString();
                }
                name = name2;
            }
            disposeQueue.Add(name, r);
        }
    }
}
