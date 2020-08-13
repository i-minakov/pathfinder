# Pathfinder

A program that helps you find the shortest way to your destination.

Developed as study assignment in the Ucode school.

## Description:
```
Structure of program is based on depth-first search algorithm.
Processes and validates input data taken from a file into matrix form.
It finds the shortest path in the simple graph (collected from all assignable ways).
In case if there is several outcome options: all of them will be showed, according to the FIFO.
```
## Usage:
```
1. git clone
2. make && ./pathfinder [filename]
*(Or you can use script to test all all possible cases)*
2. make && tests_pathfinder/do.sh
```
## Example:

**File content:**
```
4
Greenland-Bananal,8
Fraser-Greenland,10
Bananal-Fraser,3
Java-Fraser,5
```
**Program output:**
```
./pathfinder path
========================================
Path: Greenland -> Bananal
Route: Greenland -> Bananal
Distance: 8
========================================
========================================
Path: Greenland -> Fraser
Route: Greenland -> Fraser
Distance: 10
========================================
========================================
Path: Greenland -> Java
Route: Greenland -> Fraser -> Java
Distance: 10 + 5 = 15
========================================
========================================
Path: Bananal -> Fraser
Route: Bananal -> Fraser
Distance: 3
========================================
========================================
Path: Bananal -> Java
Route: Bananal -> Fraser -> Java
Distance: 3 + 5 = 8
========================================
========================================
Path: Fraser -> Java
Route: Fraser -> Java
Distance: 5
========================================
```

