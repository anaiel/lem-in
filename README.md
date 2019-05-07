# lem-in

This project was completed in April 2019 as part of the 42 school cursus. The goal was to create a program that can find the most efficient paths from a starting to an end point.
A certain number of ants have to find their way to the exit of the anthill. Each room in the anthill can only contain a single ant. The program must find the most efficient way to send all ants in the various rooms for them to reach the end as quickly as possible. Efficiency is measured as a number of lines of instruction (a single ant can only receive one instruction per line.
The detailed instructions can be found in the *resources* folder.

🍌 This project was completed with [Xeska](http://github.com/anaiel/Xeska).

![path to lem-in](https://i.imgur.com/iHWYv6I.png "Inner circle > Algo branch > ft_printf > push_swap > lem-in")

*Graph course, deep algorithms*

## Solving the problem

The first part of the project consisted in the **parsing** of the maps. 

<p align="center"><img src="https://i.imgur.com/0vjjqIV.png" /></p>
<p align="center"><img height=500 src="https://i.imgur.com/BXDNrdh.png" /></p>

This project also tackles graphs and the **max flow** problem, the specificity being that all vertices (*links*) in our graph have a capacity of one, and the same is true for all the nodes (*rooms*). The question of **algorithmic complexity** was also a main concern and one of the focus was on optimizing the instructions. This for example lead us to give up the use of the ft_strcat function (which performs a ft_strlen, which is very time consuming). 

Our program uses a version of the **Edmonds-Karp algorithm**, where vertices have a flow capacity of 1 and rooms are split into in and out nodes and linked with a vertice to simulate the fact that rooms have a capacity of 1 ant.

As an added bonus, we coded a visualizer which allows to see a representation of the anthill and an animation of the ants' path through the anthill, and a timer script which gives the min, max and mean time for the algorithm. We also added a few options to the lem-in executable which you can see by using the command `./lem-in --help`.

## Getting Started

Run the command `make` to create the lem-in executable.

### Visualizer (BONUS)

The visualizer program uses the SDL2 graphics library. On MacOS, use the command `make brewing` to install the SDL2 dependencies. Run `make visualizer` to create the visualizer executable.

## Examples

```
$> ./lem-in < resources/visualizer_maps/ptt_test
10
##start
start 5 5
##end
end 5 10
1 5 8
2 3 7
3 7 9
4 7 7
start-2
start-1
start-4
2-1
1-end
1-3
4-3
3-end

L1-1 L2-4
L1-end L2-3 L3-1 L4-4
L3-end L2-end L4-3 L5-1 L6-4
L5-end L4-end L6-3 L7-1 L8-4
L7-end L6-end L8-3 L9-1
L9-end L8-end L10-1
L10-end
```
The program repeats the input and adds the movement of the ants after a new line. The first line of the movement can be should be interpreted as so: `L1` corresponds to the first ant, `-1` indicates that it moved to the room called "1", `L2` corresponds to the second ant and `-4` indicates that it moved to the room called "4".
Keep in mind that an ant can only move by one room per line of instructions.

### Testing optimization of the paths

According to the instructions, the program must should find the optimal paths for the given rooms, links, and number of ants. This is measured by the number of lines of instructions. In the resources is provided a `generator` script (which was created by the author of the 42 project) which generates a map including a comment line with the optinal number of lines of instructions. Use the following commands to compare the optimal number of lines of instructions with the output of our lem-in, for big maps with interconnected paths:
```
./resources/generator --big-superposition > test && grep Here test && ./lem-in --line-count --silent < test && rm test
```
Our results are always within -2/+2 of the expected results.

### Testing time complexity

One of the goals of the project was also to keep the time of execution of the program under 3 seconds. I wrote a simple script which uses the generator to generate a number of maps and get the minimum, maximum and average time of execution of the program :
```
usage: ./time_check size_of_map number_of_test
```
Example:
```
$> cd resources
$> ./time_check big 10
[ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ]
big:
	mean:	0.694
	max:	1.668
	min:	0.356
```
```
$> ./time_check big-superposition 10
[ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ✓ ]
big-superposition:
	mean:	1.721
	max:	3.160
	min:	0.309
```

## Authors

🍌 Team Unbananable:
* **[anaiel](https://github.com/anaiel)** - *Edmonds Karp algorithm, parsing base, visulizer base, time script*
* **[Xeska](https://github.com/Xeska)** - *Visualizer, parsing*
