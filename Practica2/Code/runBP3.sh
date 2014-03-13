
#incrementos Neuronas

inicio=4
final=12
incr=1


for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn problema-real4.txt -numNeurons $i -part 0.3 -learnrate 0.05 -outputDebug outputs/neuron_p4$i.out>  outputs/hits_neuron_p4$i.out
done

