neuro
=====

inicio=0.1
 final=0.9
  incr=0.1


for i in $(seq $inicio $incr $final)
do
./mainPerceptron -input problema_real1.txt -output out.out -part $i -threshold 0.2 -learnrate 0.1 > ./outputs/problema_real_part$i.txt
done


for i in $(seq $inicio $incr $final)
do
./mainPerceptron -input problema_real1.txt -output out.out -part 0.3 -threshold 0.2 -learnrate $i > ./outputs/problema_real_learn$i.txt
done

for i in $(seq $inicio $incr $final)
do
./mainPerceptron -input problema_real1.txt -output out.out -part 0.3 -threshold $i -learnrate 0.1 > ./outputs/problema_real_learn$i.txt
done
