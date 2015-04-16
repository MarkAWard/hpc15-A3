EXECUTABLES = omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi-omp gs-omp
COMPILER = gcc47
CFLAGS = -fopenmp -lm

all: $(EXECUTABLES)
.PHONY: all

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

laplace: jacobi-omp gs-omp
.PHONY: laplace
jacobi-omp: jacobi-omp.c
	$(COMPILER) $(CFLAGS)  $^ -o $@
gs-omp: gs-omp.c
	$(COMPILER) $(CFLAGS)  $^ -o $@

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES) *~ a.out