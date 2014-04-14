
#incrementos Neuronas

#inicio=0.05
#final=0.5
#incr=0.05

inicio=4
final=16
incr=4



for i in $(seq $inicio $incr $final)
do
	./backpropagationPart2 -inputLearn asdf -numNeurons $i -part 0.7 -learnrate 0.05 -outputDebug outputs/neuron5_$i.out>  outputs/hits_neuron5_$i.out
done

