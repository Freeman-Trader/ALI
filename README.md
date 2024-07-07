# Artificial Living Intelligence (ALI)
## Contributors
* Freeman Trader - github.com/Freeman-Trader

## Methodology
This project aims to emulate (and possibly simulate) the workings of a human brain in hopes of recreating human intelligence and creativity. We plan on doing this by simulating neurons and the structures they form as closely as possible.

## Design
### Neurons
The core idea of a neuron is that it receives charges from its neighboring neurons through synapses, building up its own charge. Once the charge of a neuron passes a certain threshold, an all-or-nothing reaction occurs, making that same neuron emit its own charge (called an action potential), progressing the chain reaction.

* The neuron has 2 main components, the Dendrite and the Axon. The Dendrite receives the charges while the Axon emits the charge. [1]

![Neuron Architecture](README-data/NeuronArchitecture.jpg)

* Neurons, once fired, enter a refractory period in which subsequent action potentials are harder to obtain due to a lowered natural state. [2]

* There are 3 main types of neurons, all of which are specialized in specific tasks. Sensory neurons carry information from sensory organs to the brain. Motor neurons control muscles, specifically voluntary muscles. All other types are grouped under the interneuron category. [1]

![Neuron Types](README-data/TypesOfNeurons.jpg)

* Neurons can emit neurotransmitters that excite or inhibit the neurons they are connected to. The terms used for this are respectively called excitatory postsynaptic potential (EPSP) and inhibitory postsynaptic potential (IPSP). [3]

![Action Potential](README-data/IPSPsummation.jpg)

### Synapses
Synapses are what connect neurons to other cells such as neurons and muscles. There are 3 components that make up a synapse: A Presynaptic Terminal which is the part of the axon that emits neurotransmitters; A Postsynaptic Membrane which is the membrane  that receives the neurotransmitters; A Synaptic Cleft which is the gap between the aforementioned terminal and membrane.

* Neurotransmitters are chemicals that are released from the presynaptic terminal and bind to the postsynaptic membrane, changing the electrical potential of the postsynaptic cell.

* There are 2 types of synapses, chemical and electrical. Chemical synapses use the above method of communication whereas electrical synapses directly link 2 neurons.

**Sources**
* [1] [NIH](https://www.ninds.nih.gov/health-information/public-education/brain-basics/brain-basics-life-and-death-neuron)
* [2] [NIH](https://www.ncbi.nlm.nih.gov/books/NBK11146/)
* [3] [Wikipedia](https://en.wikipedia.org/wiki/Neuron)
