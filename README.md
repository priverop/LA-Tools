# RomHackingTools
Little romhacking tools I made for different games

# Games
- My Healthy Cooking Coach: text extractor and inserter.
- Luminous Arc: unpack and pack files from .iear

# Compiling
In the LA folder I've got two *.sh* files so you can compile them with GNU GCC (g++). 

# Usage
## Luminous Arc
### Unpack
```sh
$ la_unpack [file.iear]
```
This will generate a *fileList.txt* and an *extract* folder with all the unpacked files.

### Pack
```sh
$ la_pack [fileList.txt]
```
This will look for all the files in fileList.txt and generate a *TEST.iear*.
