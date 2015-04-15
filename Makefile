EXECUTABLES = omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 
COMPILER = gcc47
CFLAGS = -fopenmp

all: $(EXECUTABLES)

omp_solved2: omp_solved2.c
	$(COMPILER) $(CFLAGS) $^ -o $@
omp_solved3: omp_solved3.c
	$(COMPILER) $(CFLAGS) $^ -o $@
omp_solved4: omp_solved4.c
	$(COMPILER) $(CFLAGS) $^ -o $@
omp_solved5: omp_solved5.c
	$(COMPILER) $(CFLAGS) $^ -o $@
omp_solved6: omp_solved6.c
	$(COMPILER) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(EXECUTABLES) *~