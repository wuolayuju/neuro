
#incrementos Neuronas

#inicio=0.05
#final=0.5
#incr=0.05

inicio=1
final=8
incr=1



for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn loa -numNeurons $i -part 1 -learnrate 0.1 -outputDebug outputs/neuron_n5_$i.out>  outputs/hits_neuron_n5_$i.out
done

