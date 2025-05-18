all: cpu_usage fork_test
cpu_usage: cpu_usage.c
	gcc -o cpu_usage cpu_usage.c -lpthread
fork_test: fork_test.c
	gcc -o fork_test fork_test.c -lpthread
clean:
	rm -f cpu_usage fork_test