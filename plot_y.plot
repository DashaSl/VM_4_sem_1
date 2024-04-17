set term png
set output "plot_y_t.png"

set title "Voltage"


set xlabel "time(seconds)"
set ylabel "current y(ampere)"



plot "Test" using 1:3 with lines 


pause -1