# Canny Edge Detection and 4 other filters

#### To compile just run `make` and the Makefile will build all available
#### versions. You will have to provide your own images to test the program.

## Compile OpenMP version
```bash
    Enter OpenMp folder.
make
```

## Compile MPI version
```bash
    Enter MPI folder.
make
```

## Run MPI version -- example
```bash
make run no_threads=1 in=../../jack-russell-blurred-1200x630.png out=outfile.png filter=black-white
```

# Authors
```
Gheoace Mihai
Cezar Craciunoiu
Adrian Stefan
```

## Proiect APP

TODO: de ce accepta filtrul contract?
-- consideram ca intotdeauna se dau filtre bune ca input?
git diff-tree --no-commit-id --name-only -r  9c86bfa964de8c6715cc59394c8061ab8f5a2895