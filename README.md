# Traffic Simulation System (C++)

## Overview

This project is a traffic simulation system developed in C++. It models vehicles, roads, and intersections using object-oriented programming principles.

---

## Features

* Object-oriented design (inheritance, polymorphism)
* Vehicle simulation (cars, bicycles)
* Road and intersection system
* Time-based simulation
* Different driving behaviors

---

## Structure

* `Fahrzeug` → base class
* `PKW` → car
* `Fahrrad` → bicycle
* `Weg` → road
* `Kreuzung` → intersection

`SimuClient` and `SimuClientSocket` were provided by the course for visualization and are not my own work.

---

## Technologies

* C++
* STL

---

## Run

Requires the Boost library (Boost.Asio) and the course's visualization
server (SimuServer) to display the simulation.

```bash
g++ *.cpp -o simulation
./simulation
```

---

## What I Learned

* OOP design in C++
* Simulation logic
* Managing complex class structures

## Purpose

This project was developed as part of the C++ programming lab (Praktikum) at RWTH Aachen University.
