# lem-in

This project was completed in april 2019 as part of the 42 school cursus. The goal was to create a program that can find the most efficient paths from a starting to an end point.
A certain number of ants have to find their way to the exit of the anthill. Each room in the anthill can only contain a single ant. The program must find the most efficient way to send all ants in the various rooms for them to reach the end as quickly as possible. Efficiency is measured as a number of lines of instruction (a single ant can only receive one instruction per line.
The detailed instructions can be found in the **instructions/Subject.pdf** file.

![path to lem-in](https://i.imgur.com/iHWYv6I.png "Inner circle > Algo branch > ft_printf > push_swap > lem-in")

*Graph course, deep algorithms*

Our program uses a version of the Edmonds-Karp algorithm, where vertices have a flow capacity of 1 and rooms are split into in and out nodes and linked with a vertice to simulate the fact that rooms have a capacity of 1 ant.
As an added bonus, we coded a visualizer which allows to see a representation of the anthill and an animation of the ants' path through the anthill.

## Getting Started

Run the command `make` to create the **lem-in** executable.

### Visualizer (BONUS)

The visualizer program uses the SDL2 graphics library. Run `make visualizer` to create the **visualizer** executable.

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

## Improvements

## Authors

* **Anaelle Leclabart** - [anaiel](https://github.com/anaiel)
* **[Xeska](https://github.com/Xeska)**
