using System;

namespace Packaging
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            if(args.Length < 1 || args.Length > 2){
                Console.Write("Wrong arguments.");
                Console.WriteLine("Usage: Packaging -unpack <file1>");
                Console.WriteLine("Usage: Packaging -pack");
            } 
            else{

                Packaging p = new Packaging();
                String error = "ok";

                switch(args[0]){
                    case "-unpack":
                        error = p.Unpack(args[1]);
                        break;

                    case "-pack":
                        //error = p.Pack();
                        break;
                }

                if(error != "ok"){
                    Console.Write(error);
                }
            }
        }
    }
}
