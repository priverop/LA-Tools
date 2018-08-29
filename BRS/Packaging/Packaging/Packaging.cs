namespace Packaging
{
    using System;
    using System.IO;
    using Yarhl.IO;

    public class Packaging
    {
        private const string HEADER_FILENAME = "0 - Header";
        private const string BLOCK_FILENAME = " - Block";

        public void Unpack(string fileToExtractName)
        {

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

            uint magid = fileToUnpackReader.ReadUInt32();
            ulong numberOfBlocks = fileToUnpackReader.ReadUInt64();

            writerHeader.Write(magid);
            writerHeader.Write(numberOfBlocks);

            // Save the current position
            long currentPosition = fileToUnpackStream.Position;

            // Read first block pointer (where the pointer table ends)
            uint firstBlockPointer = fileToUnpackReader.ReadUInt32();

            // Return to previous position
            fileToUnpackStream.Position = currentPosition;

            long pointerTableSize = firstBlockPointer - currentPosition;

            // Save pointer table 
            byte[] pointerTable = new byte[pointerTableSize];
            fileToUnpackStream.Read(pointerTable, 0, (int)pointerTableSize);
            writerHeader.Write(pointerTable);
            headerStream.Dispose();

            // Return to previous position
            fileToUnpackStream.Position = currentPosition;

            // The loop will finish when we reach the first non-block pointer byte
            long endBlocksPosition = currentPosition + (((int)numberOfBlocks) * sizeof(int));
            fileToUnpackStream.Position = endBlocksPosition;
            uint endBlocks = fileToUnpackReader.ReadUInt32();
            fileToUnpackStream.Position = currentPosition;

            uint blockPointer;
            uint nextBlockPointer = 0x00;
            uint fileSize = (uint)fileToUnpackStream.Length;
            uint i = 1;

            while (nextBlockPointer != fileSize)
            {
                // First iteration
                if (nextBlockPointer == 0x00)
                    blockPointer = fileToUnpackReader.ReadUInt32();
                else
                    blockPointer = nextBlockPointer;
                    
                nextBlockPointer = fileToUnpackReader.ReadUInt32();

                // Last iteration
                if (nextBlockPointer == endBlocks)

                    // Read block until the end of the file
                    nextBlockPointer = fileSize;

                uint blockSize = nextBlockPointer - blockPointer;

                // Save current position, save block and return position
                fileToUnpackStream.PushCurrentPosition();
                fileToUnpackStream.Seek(blockPointer);
                byte[] block = new byte[blockSize];
                fileToUnpackStream.Read(block, 0, checked((int)blockSize));
                fileToUnpackStream.PopPosition();

                DataStream blockStream = new DataStream(i + BLOCK_FILENAME, FileOpenMode.Write);
                DataWriter blockWriter = new DataWriter(blockStream);
                blockWriter.Write(block);
                i++;

            }
        }
    }
}
