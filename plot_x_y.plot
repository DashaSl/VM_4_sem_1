set term png
set term png size 1920, 1080
set output "plot_y_x.png"

set title "Voltage,current"


set xlabel "current"
set ylabel "voltage"



plot "Test" using 3:2 with lines 


pause -1