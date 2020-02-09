# Maze Generator

![CI release][release-action-image]

A few years ago, I had a [maths challenge](https://tfjm.org) for which a question of a given problem was to find all maze conformations such that:
* The maze is maze of m*n square cells.
* The cells can be separated by walls.
* The maze is surrounded by a wall.
* The maze is strictly connected (i.e. each couple of cells can be linked using a path that doesn't cross any wall)
* If we add a single wall, the maze is not connected anymore.

It can be shown that for a m*n cells conformation to be a maze, 

* there are (n-1)m +(m-1)n wall slots ;
* the number of walls has to be (n-1)(m-1) ;

Thus to find a maze we have to find all such conformations that respect the connected constraint.

The approach we use is the following one :

1. we generate ...
2. we filter ...

# Setup

## Javascript

## ReasonML

### Install

* ReasonML

```sh
npm install --global bs-platform@6.2.1
```

## Build

* ReasonML

```sh
npm install
bsb -make-world -clean-world
```

### Run

```sh
npm run server
# in a new tab
npm start
```

Open a new web page to `http://localhost:8000/`.


### Bundle for Production

```sh
npm install webpack webpack-cli
./node_modules/.bin/webpack
open indexProduction.html
```
## Bolero

### Install

Install [Dotnet Core SDK][dotnetcore-url] >= 3.0

[release-action-image]: https://github.com/intv0id/MazeGen/workflows/github%20pages/badge.svg
[dotnetcore-url]: https://dotnet.microsoft.com/download/dotnet-core

### Build

```sh
dotnet build
```