
#incrementos Neuronas

inicio=4
final=12
incr=1


for i in $(seq $inicio $incr $final)
do
	echo "Ejecutando backpropagationapp con problema_real1, neuronas = $i"
	./backpropagationapp -inputLearn problema_real1.txt -numNeurons $i -part 0.3 -learnrate 0.05 -outputDebug outputs/neuron_pr$i.out>  outputs/hits_neuron_pr$i.out
done


