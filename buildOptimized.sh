mkdir -p build_optimized
mkdir -p dist_optimized
cd build_optimized

# compile library files to object files with options -O2 (optimizations) -c (skip linker; for creating object files)
gcc -O2 -c ../linkedlist.c -o linkedlist.o 
gcc -O2 -c ../genericlist.c -o genericlist.o
gcc -O2 -c ../genericArrayList.c -o genericArrayList.o
gcc -O2 -c ../genericHashMap.c -o genericHashMap.o

# create archive file from list of compiled object files using 'ar' with options: r (replacement) u (only new files) v (verbose) s (create index)
ar ruv ../dist_optimized/ds.a linkedlist.o genericlist.o genericArrayList.o genericHashMap.o

cd ..

if [[ $1 != "-t" ]]; then
exit
fi

# compile library tests with archive file and run
gcc -O2 main.c ./dist_optimized/ds.a -o main && chmod 777 ./main && ./main
