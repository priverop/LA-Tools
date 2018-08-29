namespace Packaging
{
    using System;

    public class MainClass
    {
        public static void Main(string[] args)
        {
            if (args.Length < 1 || args.Length > 2)
            {
                Console.Write("Wrong arguments.");
                showUsage();
            } 
            else
            {
                Packaging p = new Packaging();

                switch (args[0])
                {
                    case "-unpack":
                        p.Unpack(args[1]);
                        break;

                    case "-pack":
                        // p.Pack();
                        break;

                    default:
                        Console.WriteLine("Wrong arguments.");
                        showUsage();
                        break;
                }
            }
        }

        private static void showUsage(){
            Console.WriteLine("Usage: Packaging -unpack <file1>");
            Console.WriteLine("Usage: Packaging -pack");
        }

        private static void showCredits(){
            Console.WriteLine("=========================");
            Console.WriteLine("== BRS UNPACKER by Nex ==");
            Console.WriteLine("=========================");
        }
    }
}
