using System;
using System.Threading;
using System.Threading.Tasks;

namespace BarrierExample
{
    class Program
    {
        static void BarrierSample()
        {
            int count = 0;
            Barrier barrier = new Barrier(3, (b) =>
            {
                Console.WriteLine("Post-Phase action: count={0}, phase={1}", count, b.CurrentPhaseNumber);
                if (b.CurrentPhaseNumber == 2) throw new Exception("D'oh!");
            });

            barrier.AddParticipants(2);
            barrier.RemoveParticipant();

            Action action = () =>
            {
                Interlocked.Increment(ref count);
                barrier.SignalAndWait();
                Interlocked.Increment(ref count);
                barrier.SignalAndWait();

                Interlocked.Increment(ref count);
                try
                {
                    barrier.SignalAndWait();
                }
                catch(BarrierPostPhaseException bppe)
                {
                    Console.WriteLine("Catch BarrierPostPhaseException: {0}", bppe.Message);
                }

                Interlocked.Increment(ref count);
                barrier.SignalAndWait();
            };

            Parallel.Invoke(action, action, action, action);
            barrier.Dispose();
        }

        static void Main(string[] args)
        {
            BarrierSample();
        }
    }
}
