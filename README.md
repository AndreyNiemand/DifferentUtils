# numeral-system-converter
The idea of the project is to have ability to convert numbers between different numeral systems.

It can work with int and double types.
  
All the logic was written with C and can be compiled into a static or shared library:

numeral-system-converter/build/$ cmake .. -DNSC_EXECUTABLE=OFF -DBUILD_SHARED_LIBS=OFF/ON
numeral-system-converter/build/$ cmake --build .

There is also C++ interface support. Flag's default value: -DNSC_CXX_INTERFACE_SUPPORT=ON.

To compile as an executable program:

numeral-system-converter/build/$ cmake .. -DNSC_EXECUTABLE=ON
numeral-system-converter/build/$ cmake --build .
