namespace Packaging
{
    using System;

    public class MainClass
    {
        public static void Main(string[] args)
        {
            if(args.Length < 1 || args.Length > 2)
            {
                Console.Write("Wrong arguments.");
                Console.WriteLine("Usage: Packaging -unpack <file1>");
                Console.WriteLine("Usage: Packaging -pack");
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
                        Console.WriteLine("Usage: Packaging -unpack <file1>");
                        Console.WriteLine("Usage: Packaging -pack");
                        break;
                }
            }
        }
    }
}
