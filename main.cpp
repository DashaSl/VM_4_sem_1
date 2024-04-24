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
    int k = num_of_iter/10; 
    fout.open(filename);
    fout << 0 << " " << GLOBAL_point[0] << " " << GLOBAL_point[1] << " " << GLOBAL_point[2] << "\n";
    double time = 0;
    for(int i = 0; i < num_of_iter; i++){
        if(!(i % k)){
            printf("%0d out of 10\n", i/k);
        }
        RK(h);
        time+= h;
        fout << time << " " << GLOBAL_point[0] << " " << GLOBAL_point[1] << " " << GLOBAL_point[2] << "\n";
    }
    fout.close();
    printf("\n");
}

void merry_for_ISI(double h, int num_of_iter, double start_I, double delta_I, int num_of_iterations, double** mass){
    GLOBAL_I_ext = start_I;
    int k = num_of_iter/10;
    for(int i = 0; i < num_of_iterations; i++){
        GLOBAL_point[0] = 0.1;
        GLOBAL_point[1] = 1;
        GLOBAL_point[2] = 0.2;
        std::cout << "Calculating for I = " << GLOBAL_I_ext << std::endl;
        int ind_of_spike = 0; // 
        double time = 0;
        for(int j = 0; j < 3; j++){
            RK(h);
            time+=h;
            LOC[j] = GLOBAL_point[0];
        }
        //заполняем первые три значения
        for(int j = 3; j < num_of_iter; j++){
            RK(h);
            time += h;
            LOC[0] = LOC[1];
            LOC[1] = LOC[2];
            LOC[2] = GLOBAL_point[0];

            if(LOC[1] > LOC[0] && LOC[1] > LOC[2]){

                mass[i][ind_of_spike] = time - GLOBAL_CURR_SPIKE;
                //заносим промежуток
                //новое время последнего спайка 
                //но надо будет нафиг выбросить первый интервал, т.к. он некорректен
                GLOBAL_CURR_SPIKE = time;
                ind_of_spike+=1;
            }

            if(ind_of_spike >= 100){
                break;
                //чёт много спайков нашли, тормозим коней
            }
            
        }


        GLOBAL_I_ext += delta_I;
    }
}



void merry_for_ISI_r(double h, int num_of_iter, double start_r, double delta_r, int num_of_iterations, double** mass){
    GLOBAL_I_ext = 3;
    GLOBAL_r = start_r;
    int k = num_of_iter/10;
    for(int i = 0; i < num_of_iterations; i++){
        GLOBAL_point[0] = 0.1;
        GLOBAL_point[1] = 1;
        GLOBAL_point[2] = 0.2;
        std::cout << "Calculating for r = " << GLOBAL_r << std::endl;
        int ind_of_spike = 0; // 
        double time = 0;
        for(int j = 0; j < 3; j++){
            RK(h);
            time+=h;
            LOC[j] = GLOBAL_point[0];
        }
        //заполняем первые три значения
        for(int j = 3; j < num_of_iter; j++){
            RK(h);
            time += h;
            LOC[0] = LOC[1];
            LOC[1] = LOC[2];
            LOC[2] = GLOBAL_point[0];

            if(LOC[1] > LOC[0] && LOC[1] > LOC[2] && time > 300){

                mass[i][ind_of_spike] = time - GLOBAL_CURR_SPIKE;
                //заносим промежуток
                //новое время последнего спайка 
                //но надо будет нафиг выбросить первый интервал, т.к. он некорректен
                GLOBAL_CURR_SPIKE = time;
                ind_of_spike+=1;
            }

            if(ind_of_spike >= 100){
                break;
                //чёт много спайков нашли, тормозим коней
            }
            
        }


        GLOBAL_r += delta_r;
    }
}



int main(){
    std::cout << "Enter current which enters neuron: ";
    std::cin >> GLOBAL_I_ext;

    GLOBAL_point[0] = 0.1;
    GLOBAL_point[1] = 1;
    GLOBAL_point[2] = 0.2;
    GLOBAL_r = 0.005;
    GLOBAL_s = 4;
    GLOBAL_x0 = -1.6;
   
    int delta_I = 0;
    int start_I = 0;
    int num_of_iterations = 30;




    double** ISI_INT = (double**) malloc(sizeof(double*)*num_of_iterations);
    for(int i = 0; i < num_of_iterations; i++){
        ISI_INT[i] = (double*) calloc(100, sizeof(double));
    }
    //100 - максимальное количество, которое хочется учитывать. Т.е. находим первые 100 или менее интервалов
    GLOBAL_CURR_SPIKE = 0;

    merry_for_ISI_r(0.0005, 2000000, 0.0035, 0.0001, num_of_iterations, ISI_INT);



    /*
    merry_for_ISI(0.0005, 2000000, 1.0, 0.1, num_of_iterations, ISI_INT);
    */
    GLOBAL_r = 0.0035;
    std::cout << "{";
    for(int i = 0; i < num_of_iterations; i++){
        std::cout << GLOBAL_r << " : [";
        for(int j = 1; j < 100; j++){
            if(abs(ISI_INT[i][j]) < 0.0001){
                printf("\b\b");
                break;
            }
            printf("%.4f, ", ISI_INT[i][j]);

    
        }
        printf("],\n");
        GLOBAL_r += 0.0001;
    }
    printf("\b\b}");


    for(int i = 0; i < num_of_iterations; i++){
        free(ISI_INT[i]);
    }
    free(ISI_INT);
    //merrygoround(0.0005, 2000000, "Test");
    return 0;
}
