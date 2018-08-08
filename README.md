# lem_in
42 Unit Factory Project

The goal of this project is to find the quickest way to get n ants across the farm.
At the beginning of the game, all the ants are in the room ##start. The goal is
to bring them to the room ##end with as few turns as possible. Each room can
only contain one ant at a time. (except at ##start and ##end which can contain
as many ants as necessary.)

At each turn each ant only move once and through a tube (the room at
the receiving end must be empty).

- Program will receive the data describing the ant farm from the standard output
in the following format:

```
number_of_ants
the_rooms
the_links
```

- The ant farm is defined by the following links:

```
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
```

- There are three parts:
1. The rooms, which are defined by: name coord_x coord_y
2. The links, which are defined by: name1-name2
3. All of it is broken by comments, which start with #

## Visualisation

Need to press **Enter** to start moving ants.
![Doom](https://raw.githubusercontent.com/mtupikov/wolf_3d/master/doom.png)

![Simple map](https://raw.githubusercontent.com/mtupikov/lem_in/blob/master/simple%20map.png)
![More complex map](https://raw.githubusercontent.com/mtupikov/lem_in/blob/master/more%20complex%20map.png)
