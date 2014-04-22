rm -rf demarcation*in

`g++ -o demingen.e demingen.cpp`
./demingen.e
rm -rf demingen.e

first_case=3
second_case=1
third_case=1

for input in *.in
do
  i=`head -1 $input`
  if [ $i -le 200 ]; then
    mv $input "demarcation1-$(printf %02d $first_case).in";
    first_case=$(($first_case + 1))
  elif [ $i -le 5000 ]; then
    mv $input "demarcation2-$(printf %02d $second_case).in";
    second_case=$(($second_case + 1))
  else
    mv $input "demarcation3-$(printf %02d $third_case).in";
    third_case=$(($third_case + 1))
  fi
done

`cp ex1 demarcation1-01p.in`
`cp ex2 demarcation1-02p.in`
