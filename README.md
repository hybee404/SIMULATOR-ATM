# ATM Simulator

A locally-run ATM simulator built in C++. It models the request/response flow between an ATM machine and a bank server over TCP, backed by a SQLite database for account data.

## How it works

- **ATMmachine** — represents the ATM client. Connects to the bank server, sends requests (e.g. balance check, withdrawal), and reads back the response.
- **ATMserver** — the bank server. Listens for incoming ATM connections and processes requests.
- **ATMsession** — handles an individual client session/connection on the server side.
- **DataBaseHandler** — reads and writes account data to the local SQLite database.
- **main** — entry point that wires everything together and starts the server.

Flow: `ATM machine request -> Bank server responds -> ATM machine reads the response`

## Dependencies

- **C++17** compiler (developed with MinGW-w64 / g++ on Windows)
- **Boost 1.89.0+** — used for Boost.Asio (TCP networking). Header-only for the parts used here, so no separate Boost libraries need to be linked. Download from [boost.org](https://www.boost.org/).
- **SQLite3** — the amalgamation source (`sqlite3.c` / `sqlite3.h`) is vendored directly in this repo, so no separate SQLite install is required.
- **Winsock (`ws2_32`)** — required on Windows for Boost.Asio networking.

## Building

From the project root, with Boost extracted somewhere on your machine:

```bash
g++ -std=c++17 -I"C:\path\to\boost_1_89_0" main.cpp ATMmachine.cpp ATMserver.cpp ATMsession.cpp DataBaseHandler.cpp sqlite3.c -lws2_32 -o ATM_SERVER.exe
```

Replace `C:\path\to\boost_1_89_0` with wherever you've downloaded Boost locally.

## Running

```bash
./ATM_SERVER.exe
```

The server will start listening for ATM client connections. The database file (`Bank_DataBase.db`) is created/used locally and is **not** committed to this repo — see `.gitignore`. If you're setting this up fresh, you may need a small setup script or SQL schema to initialize the tables (add one here once available).

## Notes

- This is a local simulation for learning/demo purposes — not intended for handling real financial data.
- The database file is excluded from version control on purpose, since it may contain test account data.