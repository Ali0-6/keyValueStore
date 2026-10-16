# keyValueStore

A small Redis-style in-memory key-value store written in C++. It runs in the terminal: you type commands, and it stores and retrieves values.

I built this to learn C++ fundamentals by making something real, rather than only working through exercises. It is a work in progress (see the roadmap below).

## Build and run

Requires a C++20 compiler (I use g++ via MSYS2 on Windows).

```
g++ -std=c++20 -Wall -Wextra src/main.cpp -o kvstore
./kvstore
```

On Windows PowerShell, run it with `.\kvstore`.

## Commands

| Command | What it does | Output |
|---|---|---|
| `SET key value` | Stores the value under the key (overwrites if it exists) | `OK` |
| `GET key` | Looks up the key | the value, or `(nil)` if missing |
| `DEL key` | Removes the key | `1` if it existed, `0` if not |
| `EXISTS key` | Checks whether the key is present | `1` or `0` |
| `EXIT` | Quits the program | none |

Notes:

- Commands are case-insensitive (`set` works the same as `SET`).
- Keys cannot contain spaces. Values can (`SET greeting hello world` stores `hello world`).
- Wrong usage prints an error and the program keeps running, for example `ERR usage: SET key value`.
- Unknown commands print `ERR unknown command`. Empty lines are ignored.

## Example session

```
> SET city London
OK
> GET city
London
> SET greeting hello world
OK
> GET greeting
hello world
> EXISTS city
1
> DEL city
1
> GET city
(nil)
> FLY away
ERR unknown command
> SET
ERR usage: SET key value
> EXIT
```

## How it works

Each line is read, split into a command word and its arguments (a simple parser), and passed to a handler function for that command. The data lives in a `std::unordered_map<std::string, std::string>`.

## Problems I ran into

- **Values were cut off at the first space.** `SET greeting hello world` stored only `hello`. The cause was that `>>` stops reading at whitespace, so the rest of the line was silently discarded. I fixed it by reading the key with `>>` and the rest of the line with `std::getline` (skipping the leading space with `std::ws`).
- **`SET` with missing arguments stored an empty key.** I was not checking whether the reads had succeeded, so empty strings went straight into the map. I now validate the key and value first and print a usage message instead.
- **Mismatched braces.** A missing closing brace nested the `DEL` handler inside the `GET` handler. I found it by checking that each closing brace lined up with the line that opened it.

## Roadmap

- [x] Basic commands: `SET`, `GET`, `DEL`, `EXISTS`, `EXIT`
- [x] Command handlers split into functions
- [ ] Move the store into a `KeyValueStore` class
- [ ] Save to and load from a file
- [ ] TCP server so other programs can connect
- [ ] Unit tests and CI