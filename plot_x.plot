set term png
set term png size 3840, 1080
set output "plot_x_t.png"

set title "Voltage"


set xlabel "time(seconds)"
set ylabel "Voltage(idk)"



plot "Test" using 1:2 with lines


pause -1