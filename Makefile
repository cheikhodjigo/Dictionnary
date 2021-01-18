# Makefile pour INF3105 / TP2

#OPTIONS = -Wall           # option standard
#OPTIONS = -g -O0 -Wall    # pour rouler dans gdb
OPTIONS = -O2 -Wall        # pour optimiser
CC=g++
out_dir=tests_out
EXEC = tp2

$(EXEC): src/main.cpp 
	
	$(CC) $(OPTIONS ) $< -o $@ 


.PHONY: clean, tests

tests: 
	bash ./tests.sh

clean:
	rm -rf $(OBJECTS) $(EXEC) 
	rm -rf $(out_dir)
