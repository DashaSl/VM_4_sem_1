# Implementation of the Hindmarsh-Rose neuronal model using Runge-Kutta methods
Describing the dynamics of neuronal membrane potential. The model consists of a system of three coupled ordinary differential equations (ODEs), which govern the time evolution of the membrane potential and associated ionic currents. The equations are numerically solved using Runge-Kutta methods.<br />
![](/HR_model_ODE.png)
* x(t) represents the membrane potential 
* y(t) corresponds to the fast ionic currents (primarily sodium Na+ and potassium K+ fluxes)
* z(t) describes the slow adaptation current, which increases at each spike, introducing long-term modulation of neuronal activity.<br /><br />
This model captures bursting and spiking behaviors of neurons, by incorporating both fast and slow dynamics. The fast variables (x and y) are responsible for the rapid depolarization and repolarization phases of action potentials, while the slow variable (z) modulates the firing rate and adapts to prolonged stimulation.
# 
Hindmarsh-Rose model used in order to investigate:
+ The dependence of interspike intervals (ISIs) on the input current.
+ The dependence of ISIs on the adaptation parameter r, which regulates the slow adaptation current dz/dt.

Results indicate two distinct firing regimes:
+ Regular spiking: For certain parameter values, the neuron fires action potentials with relatively uniform interspike intervals.
+ Bursting behavior: For other parameter values, spikes occur in clusters (bursts), where individual spikes within a burst are separated by short ISIs, while bursts themselves are separated by longer ISIs.
By analyzing these transitions, bifurcation diagrams were constructed, showing how neuronal dynamics change as a function of the input current and the adaptation parameter.
#
Bifurcation diagram for r<br />
![](/r_bif.png)<br />
Bifurcation diagram for I<br />
![](/I_bif.png)<br />
Example of time evolution of the membrane potential with starting point (0, 0, 0) and I = 3, r = 0.005<br />
![](/plot_x_t.png)<br />
#
To run program on your computer, clone repository and run the script<br />
```
./myscript.sh
```
