g++ -O2 validator.cpp -o validator
for T in tests/*.in; do
	subtasks=$(echo "$T" | sed 's/.*[^0-9]\([0-9]\+\)\.in/\1/')
	for (( i=0; i<${#subtasks}; i++ )); do
	  subtask=${subtasks:$i:1}
	  echo $T \(subtask $subtask\)
	  ./validator $T $subtask
	done
done