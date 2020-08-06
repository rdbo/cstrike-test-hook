if [ ! -d build ]; then
    mkdir build
fi

gcc -Wall -g -m32 -shared -fPIC cstrike-test-hook/main.c cstrike-test-hook/libmem/libmem.c -o build/libinject.so -ldl -Wall
