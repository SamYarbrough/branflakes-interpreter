# branflakes-interpreter
a very simple and probably inefficient branflakes interpreter, able to load, parse, and run files

[branflakes wiki](https://en.wikipedia.org/wiki/Brainfuck)

# compilation
from within `branflakes-interpreter`:

`g++ ./src/main.cpp -o branflakes`

# usage
from within `branflakes-interpreter`:

`branflakes` runs default `./programs/helloworld.bf`

`branflakes ./pathToProgram/programName.bf` runs file at specified path
