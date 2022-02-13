# Formatting-XML
Formatting XML With Qt (C++)

## Introduction 
**Formatting-XML Tool** is a free tool for formatting XML File
### Features
- **Consistency**: Check for errors in the XML file, correct it and display the errors.
- **Convert XML To JSON**: Convert the XML file to JSON after being checked for consistency.
- **Format**: Format the XML File.
- **Compress**: Compress the XML File.
- **Visualization**: Providing graphical visualization for the graph.
## Building
### Dependencies
- Qt5
- CMake >= 3.0
### Linux
#### Build and run
```
git clone https://github.com/AliBastawy/Formatting-XML.git
cd Formatting-XML
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qmake # default path: /usr/bin/qmake
make -j
./Formatting-XML
```

