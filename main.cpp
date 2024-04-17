#include "functions.h"
double derivative_x(double x, double y, double z){ return y - A*pow(x, 3) + B*pow(x, 2) + GLOBAL_I_ext - z;}
double der_x(double x, double I){ return -A*pow(x, 3) + B*pow(x, 2) + I;}
double derivative_y(double x, double y, double z){ return C - D*pow(x, 2) - y;}
double derivative_z(double x, double y, double z){ return GLOBAL_r*(GLOBAL_s*(x - GLOBAL_x0) - z);}
void* stable_point(double I_ext_beg, double I_step, int num_of_steps, double y, double z){
    //-3A*x^2 + 2B*x = sec der => x(-3Ax + 2B) = 0 => x= 0 and 2B = 3Ax => x = 2B/3A
    double eq_2 = 2*B/(double)3*A;
    int counter = 0;
    while(counter < I_step){
        counter++;
    }
    return 0;

}
double sum(double k[6], int ind, double h){
    double ans = 0;
    int i = 0;
    while(i <= ind){
        ans += Butcher_DP5[ind][i]* k[i];
        i = i + 1;
    }
    return h*ans;
}
void RK(double h){
    K_X[0] = derivative_x(GLOBAL_point[0], GLOBAL_point[1], GLOBAL_point[2]);
    K_Y[0] = derivative_y(GLOBAL_point[0], GLOBAL_point[1], GLOBAL_point[2]);
    K_Z[0] = {derivative_z(GLOBAL_point[0], GLOBAL_point[1], GLOBAL_point[2])};
    int i = 0;
    while(i < 5){
        K_X[i+1] = derivative_x(GLOBAL_point[0] + sum(K_X, i, h),GLOBAL_point[1]+ sum(K_Y, i, h), GLOBAL_point[2]+ sum(K_Z, i, h));
        K_Y[i+1] = derivative_y(GLOBAL_point[0] + sum(K_X, i, h),GLOBAL_point[1]+ sum(K_Y, i, h), GLOBAL_point[2]+ sum(K_Z, i, h));
        K_Z[i+1] = derivative_z(GLOBAL_point[0] + sum(K_X, i, h),GLOBAL_point[1]+ sum(K_Y, i, h), GLOBAL_point[2]+ sum(K_Z, i, h));
        i = i + 1;
    }
    TMP[0] = 0;
    TMP[1] = 0;
    TMP[2] = 0;
    i = 0;
    while(i < 6){
        TMP[0] += Butcher_DP5[5][i] * K_X[i];
        TMP[1] += Butcher_DP5[5][i] * K_Y[i];
        TMP[2] += Butcher_DP5[5][i] * K_Z[i];
        i = i + 1;
    }
    GLOBAL_point[0] += TMP[0] * h;
    GLOBAL_point[1] += TMP[1] * h;
    GLOBAL_point[2] += TMP[2] * h;
}

void merrygoround(double h, int num_of_iter, std::string filename){
    std::ofstream fout;
    fout.open(filename);
    fout << 0 << " " << GLOBAL_point[0] << " " << GLOBAL_point[1] << " " << GLOBAL_point[2] << "\n";
    double time = 0;
    for(int i = 0; i < num_of_iter; i++){
        RK(h);
        time+= h;
        fout << time << " " << GLOBAL_point[0] << " " << GLOBAL_point[1] << " " << GLOBAL_point[2] << "\n";
    }
    fout.close();
}
int main(){
    std::cout << "Enter current which enters neuron: ";
    std::cin >> GLOBAL_I_ext;
    //std::cout << "Enter parametr r , s and x0 : "; 
   // std::cin >> GLOBAL_r >> GLOBAL_s >> GLOBAL_x0;
   GLOBAL_point[0] = 0.1;
   GLOBAL_point[1] = 1;
   GLOBAL_point[2] = 0.2;
   GLOBAL_r = 0.005;
   GLOBAL_s = 4;
   GLOBAL_x0 = -1.6;
    //std::cout << "Enter starting point (x, y, z): "; 
    //std::cin >> GLOBAL_point[0] >> GLOBAL_point[1] >> GLOBAL_point[2];
    merrygoround(0.001, 5000000, "Test");
    printf("Result with initial parametrs I_ext = %f, r = %f\n", GLOBAL_I_ext, GLOBAL_r);
    printf("Starting point: (%f, %f, %f)\n", GLOBAL_point[0], GLOBAL_point[1], GLOBAL_point[2]);
    return 0;
}