echo "TEST1"

cat ./tests/checkSable_input1 | ./output/main 

diff ./tests/output1_v1.txt tests/expectedOutput1_v1.txt

echo "TEST2"

cat ./tests/checkSable_input2 | ./output/main 

diff ./tests/output1_v5.txt tests/expectedOutput1_v5.txt