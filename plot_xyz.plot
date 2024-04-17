set term png
set term png size 640, 480

set output "plot_xyz.png"

set title "Voltage"


set xlabel "voltage x (voltage)"
set ylabel "current y(ampere)"
set zlabel "current z (ampere)"



splot "Test" using 2:3:4 with lines 


pause -1