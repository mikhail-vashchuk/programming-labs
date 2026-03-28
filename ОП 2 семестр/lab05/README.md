# State File Manager

A simple C++ console program for working with binary files that store information about countries.

## Features

- create a binary file
- add one or several country records
- delete a file
- delete selected country records by name
- show all records
- show countries with more than one official language
- show countries with a low USD exchange rate
- show countries in alphabetical order

## Record structure

Each country record contains:

- country name
- official language count
- language
- currency
- USD exchange rate

## Technologies

- C++
- binary file input/output (`ifstream`, `ofstream`)
- dynamic arrays
- input validation
- `std::sort` for alphabetical ordering