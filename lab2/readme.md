1. make -> (``for complilation of code``)

2. make tests -> (`runs all test cases and compare with its corresponding expected output`)

3. make test1/test2/test3/... -> (`run particular test and compare with its corresponding expected output`)

4. make clean -> (`remove all executable, the temporary files, and any files that are generated`)

5. make libs -> (`create two libraries: (i) a static library that contains only the scalar operations in it,`
		and (ii) a dynamically linked library that contains only the matrix operations in the appropriate folder)
		
6. make run
  (followed by operation) -> (`give an input file "run.in" located at the present working directory, and it will runs the executable,`
				and it gives output file "run.out" located in the present working directory)
				(it is working for only one operation weather multiple operation are given)
				
7. ./bin/run -a -m -M -T ..... < run.in > run.out ->(`for multiple operation, it will perform operations one by one in sequence`
							for multiple matrices one by one given in "&run.in",
							with valid sequence of operations and matrices)
							(result of one previos matrices will be input for next matrices)
							(determinent of one matrix will be scalar for next matrices)
