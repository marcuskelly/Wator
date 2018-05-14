# Wa-Tor

[Wa-Tor](https://en.wikipedia.org/wiki/Wa-Tor) is a population dynamics simulation devised by Alexander Keewatin Dewdney and presented in the December 1984 issue of Scientific American in a 5-page article entitled "Computer Recreations: Sharks and fish wage an ecological war on the toroidal planet Wa-Tor".

## Built With

* Ubuntu 16.04 LTS - The OS used
* [SFML](https://www.sfml-dev.org) - The graphics library
* C++ - The programming language
* g++ - The compiler

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

[SFML](https://www.sfml-dev.org) Simple and Fast Multimedia Library is used to display the simulation.

Instructions on how to install SFML on a Linux system can be found [here](https://www.sfml-dev.org/tutorials/2.4/start-linux.php).

### Installing

Clone the repo

```
git clone https://github.com/marcuskelly/Wator.git
```

Change into Wator directory

```
cd Wator
```

Compile the program

```
make
```

Run the program

```
./start
```

### Up and running

![Alt text](preview.png?raw=true "Title")

## Sequential Benchmarking
Benchmarking was carried out using a HP Notebook:

* System Type- 64-bit OS, x64-based processor
* Processor- Intel(R) Core(TM) i5-6200U, CPU @ 2.30GHz
* RAM- 8.00 GB
         
The speed of the each iteration was measured in contrasting grid sizes. The grid sizes used are 40 x 40, 80 x 80, 160 x 160, 320 x 320. Statistics were collected for 5000 iterations for each grid size. This data is as follows:

![Alt text](sequentialBMTable.png?raw=true "Title")

![Alt text](sequentialBMChart.png?raw=true "Title")

OpenMP was integrated into the application. Using the same machine stated above, the following statistics were observed.

![Alt text](4threads.png?raw=true "Title")


## Authors

* **Mark Kelly** - [GitHub](https://github.com/marcuskelly)
* **Ronan Timmons** - [GitHub](https://github.com/RonanTimmons)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

## Acknowledgments

Thanks to [Karl Redmond](https://github.com/karlosredmond) and [Ger Dobbs](https://github.com/gerdobbs) for their help getting SFML working on the MakeFile.
