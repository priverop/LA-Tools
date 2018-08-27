using System;
using System.IO;
using Yarhl.IO;

namespace Packaging
{
    public class Packaging
    {
        private const string HEADER_FILENAME = "0 - Header";
        private const string BLOCK_FILENAME = " - Block";

        public Packaging()
        {
        }

        /*
         * Return Error
        */

        public string Unpack(string fileToExtractName){

            /*
             * Almaceno el Magid.
             * Almaceno el numero de bloques.
             * Bucle de 1 hasta numero de bloques:
             *      Guardo 4bytes puntero
             *      Guardo 4bytes puntero+1
             *      Saco la diferencia = tamaño
             *      Avanzo hasta el offset
             *      Guardo hasta el tamaño en fichero nuevo
             */

            DataStream fileToUnpackStream = new DataStream(fileToExtractName, FileOpenMode.Read);
            DataReader fileToUnpackReader = new DataReader(fileToUnpackStream);
            DataStream headerStream = new DataStream(HEADER_FILENAME, FileOpenMode.Write);
            DataWriter writerHeader = new DataWriter(headerStream);

            UInt32 magid = fileToUnpackReader.ReadUInt32();
            UInt64 numberOfBlocks = fileToUnpackReader.ReadUInt64();

            writerHeader.Write(magid);
            writerHeader.Write(numberOfBlocks);
            headerStream.Dispose();

            UInt32 blockPointer;
            UInt32 nextBlockPointer = 0x00;

            for (UInt64 i = 1; i <= numberOfBlocks; i++){

                if (i == 1)
                    blockPointer = fileToUnpackReader.ReadUInt32();
                else
                    blockPointer = nextBlockPointer;

                nextBlockPointer = 0x00; // reset 

                if (i == numberOfBlocks - 1)
                    nextBlockPointer = (UInt32)fileToUnpackStream.Length;
                else
                    nextBlockPointer = fileToUnpackReader.ReadUInt32();

                if(nextBlockPointer < blockPointer)
                    nextBlockPointer = fileToUnpackReader.ReadUInt32();

                UInt32 blockSize = nextBlockPointer - blockPointer;

                fileToUnpackStream.PushCurrentPosition();
                fileToUnpackStream.Seek(blockPointer);
                byte[] block = new byte[blockSize];
                fileToUnpackStream.Read(block, 0, checked((int)blockSize));
                fileToUnpackStream.PopPosition();

                DataStream blockStream = new DataStream(i + BLOCK_FILENAME, FileOpenMode.Write);
                DataWriter blockWriter = new DataWriter(blockStream);
                blockWriter.Write(block);
            }


            return "ok";

        }
    }
}
