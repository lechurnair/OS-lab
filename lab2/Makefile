all: makedir build 

makedir: 
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p libs
	@echo "Directories made..."


build:makedir libs src/inp.cpp include/inp.h 
	@ g++ src/Matrix.cpp -L./libs  -lmatrix -lscalar -llog -lop -o bin/run -Wl,-rpath=./libs;
	@echo "Build Finished..."

libs:makedir src/Scalar_Op.cpp include/scalar_head.h src/Matrix_Op.cpp include/matrix_head.h buildscalar buildmatrix buildlog buildop
	@ar -rc libs/libscalar.a build/scalar.o; 
	@g++ -fPIC -o libs/libmatrix.so -shared build/matrix.o
	@ar -rc libs/liblog.a build/logger.o
	@ar -rc libs/libop.a build/op.o
	@echo "Linked Libraries..."

buildscalar: 
	@g++ -c src/Scalar_Op.cpp -o build/scalar.o

buildmatrix:
	@g++ -c src/Matrix_Op.cpp -o build/matrix.o

buildop:
	@g++ -c src/inp.cpp -o build/op.o

buildlog:
	@g++ -c src/logger.cpp -o build/logger.o


tests:build test1 test2 test3 test4 test5 test6 test7
test1:
	@ ./bin/run -s < tests/test1.in >> out.out;  ./check.sh 1 out.out;  rm out.out
test2:
	@ ./bin/run -M < tests/test2.in >> out.out;  ./check.sh 2 out.out;  rm out.out
test3:
	@ ./bin/run -X < tests/test3.in >> out.out;  ./check.sh 3 out.out;  rm out.out
test4:
	@ ./bin/run -A < tests/test4.in >> out.out;  ./check.sh 4 out.out;  rm out.out
test5:
	@ ./bin/run -m < tests/test5.in >> out.out;  ./check.sh 5 out.out;  rm out.out
test6:
	@ ./bin/run -d < tests/test6.in >> out.out;  ./check.sh 6 out.out;  rm out.out
test7:
	@ ./bin/run -T < tests/test7.in >> out.out;  ./check.sh 7 out.out;  rm out.out
run: build
	@ ./run.sh
clean:
	@rm -rf bin libs build logger.txt
	@echo "bin,libs,build and logger.txt removed"

.PHONY: build, clean, libs
