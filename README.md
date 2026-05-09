# RySQRT

RySQRT is a small hyper-optimized set of 2 sqrt functions written with the goal of beating the
standard library `sqrt` in raw speed while keeping the error easy to measure.

| Function                   | What it does                                                              |
| -------------------------- | ------------------------------------------------------------------------- |
| `RySQRT::fast_sqrt(float)` | Returns a very fast bit-level square-root estimate.                       |
| `RySQRT::acc_sqrt(float)`  | Refines the estimate with two Newton iterations for much better accuracy. |

## Benchmark

The benchmark uses 25 fixed input values and runs each function 1,000,000 times
per value. Error is measured against `std::sqrt`.

Results from a local `make benchmark` run:

| Function    | Inputs | Mean time |  Fastest |  Slowest | Mean error | Worst error |
| ----------- | -----: | --------: | -------: | -------: | ---------: | ----------: |
| `fast_sqrt` |     25 |  0.537 ns | 0.426 ns | 0.985 ns |  1.273997% |   3.228184% |
| `acc_sqrt`  |     25 |  1.559 ns | 1.284 ns | 3.221 ns |  0.000005% |   0.000013% |

Timings depend heavily on the CPU, compiler, and optimization flags, so treat
these as a snapshot rather than portable performance guarantees.

## My Specs

| Part            | Spec                                            |
| --------------- | ----------------------------------------------- |
| OS              | Linux                                           |
| CPU             | 12th Gen Intel Core i7-12700H                   |
| Cores / threads | 14 cores / 20 threads                           |
| Max CPU clock   | 4.7 GHz                                         |
| Memory          | 15 GiB RAM                                      |
| Compiler        | g++ 11.4.0                                      |
| Build flags     | `-Ofast -march=native -Wall -Wextra -std=c++17` |

## Build

```sh
make
make benchmark
```
