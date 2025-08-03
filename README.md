# MazeGeneratorInC

Implementing various Minimum Spanning Algorithms to generate mazes using the C programming language!

Built with a `Makefile` for easy compilation.

## Prerequisites

- A gcc compiler for C
- `make` utility
- Currently only suitable for Windows users, which will require MinGW

## Building

Compile the program with:

```sh
make
```

This will create an executable titled "main.exe".

## Running (Windows)

```sh
./main
```

## Updates

1/5/2025 Update: Kruskal's Algorithm has been fully implemented!

8/3/2025 Update: A new Edge struct was added in edge.h. It has helped make the code a lot more readable and eliminated my use of "magic numbers", which will further eliminate technical debt and allow me to add new ideas in the future.
