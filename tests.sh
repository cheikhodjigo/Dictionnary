#!/bin/bash
# script écrit par Alexandre Terrasa et modifié par Rachid Kadouche

tests_dir=tests
out_dir=tests_out

# Prepare output directory
rm -rf $out_dir
mkdir $out_dir


for test in `ls tests/*.in`; do
	nom_base_test=$(basename "$test")
	test_name="${nom_base_test%.*}"
	test_in="$tests_dir/$test_name.in"
	test_res="$tests_dir/$test_name.res"
	test_out="$out_dir/$test_name.out"
	test_diff="$out_dir/$test_name.diff"

	# Check res file
	if [ ! -f $test_res ]; then
		echo -ne "[RES] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(no res file for test $test_name)"
		continue
	fi

	# Run the test
	./tp2 < $test_in > $test_out 2>&1
 
	# Check empty output
	if [ ! -f $test_out ]; then
		echo -ne "[\033[31mERR\e[0m] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(no output)"
		continue
	fi

	# Check diff
	diff --ignore-all-space $test_res $test_out > $test_diff
	if [ -s $test_diff ]; then
		echo -ne "[\033[31mKO\e[0m] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(diff $test_res $test_out)"
	else
		echo -ne "[\033[32mOK\e[0m] "
		echo -e "\033[1m$test_name\e[0m"
	fi
done
