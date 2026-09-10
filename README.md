# Mini IPL Management System (Terminal, C, File Handling)

This is a simple terminal-based IPL management system written in C using **file handling**.

Each team has its own text file in `teams/` and every operation (add/remove/transfer) **updates the `.txt` files**.

## Web version

The project also includes a browser interface in `index.html`. It loads the same team roster files and supports viewing, searching, adding, removing, and transferring players.

Start a local web server from the project folder:

```bash
python3 -m http.server 8000
```

Then open [http://localhost:8000](http://localhost:8000). Web changes are saved in the browser only (using local storage); they do not overwrite the source roster text files.

## Files

- `ipl_manager.c` - main program
- `Makefile` - build/run helpers
- `teams/*.txt` - one roster file per team (pre-filled with 15 players)

## How to compile & run

```bash
make
./ipl_manager
```

Or:

```bash
make run
```

## Menu options

1. View Teams
2. Search a Team (show players)
3. Add Player to a Team (enter name, jersey number, select roles)
4. Remove Player from a Team (by jersey number)
5. Transfer Player (by jersey number; removes from source and appends to destination)
6. Exit

## Team file format

Example line (from `teams/rcb.txt`):

`Player Name: Virat Kohli | Jersey Number: 18 | Role: Right Handed Batsman`
