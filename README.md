# Return Of Monke
## Requirements
* Must have QT5
* Must have QT multimedia5
* Must have Boost

## How to install requirements
~~~bash
sudo apt install qt5-default
sudo apt install qtmultimedia5-dev
sudo apt install libboost-dev
~~~
## How To Run
~~~bash
qmake ReturnOfMonke.pro
make
./ReturnOfMonke
~~~
## How To Test
~~~bash
qmake TestSuite.pro
make
./TestSuite
~~~

The test suite only checks some things, the other things can be verified visually, like the length of something, or its direction of travel.

## How we are building the project

We will be implementing many of the graphics using the Qt library, specifically the QtGraphics classes.

Most of the objects that will be drawn will inherit from Qt objects (e.g. QGraphicsItem) as they already have coordinates, direction, and more data and methods that can be inherited.

