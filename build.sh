mkdir -p build
mkdir -p dist
ls
cd build

# compile library files to object files with options -Wall (all warnings) -Wextra (extra warnings) -g (enabled debug) -c (skip linker; for creating object files)
gcc -Wall -Wextra -g -c ../linkedlist.c -o linkedlist.o
gcc -Wall -Wextra -g -c ../genericlist.c -o genericlist.o
gcc -Wall -Wextra -g -c ../genericArrayList.c -o genericArrayList.o
gcc -Wall -Wextra -g -c ../genericHashMap.c -o genericHashMap.o

# create archive file from list of compiled object files using 'ar' with options: r (replacement) u (only new files) v (verbose) s (create index)
ar ruv ../dist/ds.a linkedlist.o genericlist.o genericArrayList.o genericHashMap.o

cd ..

if [[ $1 != "-t" ]]; then
exit
fi

# compile library tests with archive file and run
gcc -Wall -Wextra -g main.c ./dist/ds.a -o main && chmod 777 ./main && ./main
