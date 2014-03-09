
#incrementos Neuronas

inicio=1
final=8
incr=1


for i in $(seq $inicio $incr $final)
do
	echo "Ejecutando backpropagationapp con problema_real1, neuronas = $i"
	./backpropagationapp -inputLearn problema_real1.txt -numNeurons $i -part 0.3 -learnrate 0.1 -tolerance 0.05 > outputs/neuron_prob1_$i.out
done


#incrementos Tasa aprendizaje

inicio=0.1
final=0.5
incr=0.1
for i in $(seq $inicio $incr $final)
do
	echo "Ejecutando backpropagationapp con problema_real1, alfa = $i"
	./backpropagationapp -inputLearn problema_real1.txt -numNeurons 2 -part 0.3 -learnrate $i -tolerance 0.05 > outputs/learn_prob1_$i.out
done