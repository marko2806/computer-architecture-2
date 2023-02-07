#include <iostream>
#include <time.h>

//Procesor: Intel i7 8750H
//Radni takt: 2.20 GHz
//Operacijski sustav: Ubuntu 18.04.5 LTS (64-bit)

//L1 cache: 384KB ukupno (64 KB po jezgri - 32 KB instrukcijski cache, 32KB podatkovni cache), linija: 64B
// 8-way associative cache memory
// s1 = 32 KB
// b1 = 64 B

//L2 cache: 1.5MB ukupno (256 KB po jezgri), linija: 64B
// 4-way associative cache memory
// s2 = 256 KB
// b2 = 64 B

//L3 cache:   9MB, linija: 64B
// 12-way associative cache memory
// s3 = 9 MB
// b3 = 64 B

/*
Ispis:

Vrijeme pristupa A:   0.590073 ns
Propusnost A:         16162MB/s

Vrijeme pristupa B:   15.875 ns
Propusnost B:         600.74MB/s

Vrijeme pristupa C:   26.2811 ns
Propusnost C:         362.874MB/s

Vrijeme pristupa D:   43.6498 ns
Propusnost D:         218.483MB/s

t(L2)/t(L1) = 26.9035
t(RAM)/t(L2) = 2.74959
t(L3)/t(L2) = 1.6555
t(RAM)/t(L3) = 1.66088
*/

const long s1 = 32 * 1024;
const long b1 =  64;

const long s2 =  256 * 1024;
const long b2 =  64;

const long s3 =   9 * 1024 * 1024;
const long b3 =  64;

struct measurement_data{
    double time;
    double bandwidth;
    long result;
};

const long BROJ_IZVODENJA_A = 10000;
const long BROJ_IZVODENJA_B = 5000;
const long BROJ_IZVODENJA_C = 2000;
const long BROJ_IZVODENJA_D = 1000;

void init(char *buff, long length){
    for(long i = 0; i < length; i++){
        *(buff + i) = 0;
    }
}


long end(char *buff, long length){
    long res = 0;
    for(long i = 0; i < length; i++){
        res += *(buff + i);
    }
    return res;
}

measurement_data* A(){
    char* buffA = (char *)malloc(2 * s1 * sizeof(char));
    long brojPristupaA = 2 * s1 * BROJ_IZVODENJA_A;
    init(buffA, 2 * s1);
    clock_t vrijemeAStart = clock();
    for(long i = 0; i < BROJ_IZVODENJA_A; i++){
        for(long j = 0; j < 2 * s1; j++){
            *(buffA + j) += 1;
        }
    }
    clock_t vrijemeAEnd = clock();
    long res = end(buffA, 2 * s1);
    free(buffA);
    double vrijemeA = (double)(vrijemeAEnd - vrijemeAStart)/ CLOCKS_PER_SEC;    
    measurement_data* result = new measurement_data;
    result -> bandwidth = brojPristupaA / (vrijemeA * 1024 * 1024);
    result -> result = res;
    result -> time = vrijemeA / brojPristupaA * 10e9;
    return result;
}

measurement_data* B(){
    char* buffB = (char *)malloc(2 * s1 * sizeof(char));
    long brojPristupaB = (2 * s1) / b1 * BROJ_IZVODENJA_B;
    init(buffB, 2 * s1);
    clock_t vrijemeBStart = clock();
    for(long i = 0; i < BROJ_IZVODENJA_B; i++){
        for(long j = 0; j < 2 * s1; j = j + b1){
            *(buffB + j) += 1;
        }
    }
    clock_t vrijemeBEnd = clock();
    long res = end(buffB, 2 * s1);
    free(buffB);
    double vrijemeB = (double)(vrijemeBEnd - vrijemeBStart)/ CLOCKS_PER_SEC;

    measurement_data* result = new measurement_data;
    result -> bandwidth = brojPristupaB / (vrijemeB * 1024 * 1024);
    result -> result = res;
    result -> time = vrijemeB / brojPristupaB * 10e9;
    return result;
}

measurement_data* C(){
    long brojPristupaC = (2 * s2) / b2 * BROJ_IZVODENJA_C;
    char *buffC = (char *)malloc(2 * s2 * sizeof(char));
    init(buffC, 2 * s2);
    clock_t vrijemeCStart = clock();
    for(long i = 0; i < BROJ_IZVODENJA_C; i++){   
        for(long j = 0; j < 2 * s2; j = j + b2){
            *(buffC + j) += 1;
        }
    }
    clock_t vrijemeCEnd = clock();
    long res = end(buffC, 2 * s2);
    free(buffC);
    double vrijemeC = (double)(vrijemeCEnd - vrijemeCStart)/ CLOCKS_PER_SEC;
    measurement_data* result = new measurement_data;
    result -> bandwidth = brojPristupaC / (vrijemeC * 1024 * 1024);
    result -> result = res;
    result -> time = vrijemeC / brojPristupaC * 10e9;
    return result;
}

measurement_data* D(){
    long brojPristupaD = (2 * s3 ) / b3 * BROJ_IZVODENJA_D;
    char *buffD = (char *)malloc(2 * s3 * sizeof(char));
    init(buffD, 2 * s3);
    clock_t vrijemeDStart = clock();
    for(long i = 0; i < BROJ_IZVODENJA_D; i++){
        for(long j = 0; j < 2 * s3; j = j + b3){
            *(buffD + j) += 1;
        }
    }
    long res = end(buffD, 2 * s3);
    free(buffD);
    clock_t vrijemeDEnd = clock();
    double vrijemeD = (double)(vrijemeDEnd - vrijemeDStart)/ CLOCKS_PER_SEC;
    measurement_data *result = new measurement_data;
    result -> bandwidth = brojPristupaD / (vrijemeD * 1024 * 1024);
    result -> result = res;
    result -> time = vrijemeD / brojPristupaD * 10e9;
    return result;
}




int main(){
    
    measurement_data *mA = A();
    measurement_data *mB = B();
    measurement_data *mC = C();
    measurement_data *mD = D();
    
    std::cout << "Vrijeme pristupa A:   " << mA -> time << " ns" << std::endl;
    std::cout << "Propusnost A:         " << mA -> bandwidth << "MB/s" << std::endl;
    std::cout << std::endl;
    //std::cout << "Rezultat izvodenja A: " << mA -> result << std::endl;

    std::cout << "Vrijeme pristupa B:   " << mB -> time << " ns" << std::endl;
    std::cout << "Propusnost B:         " << mB -> bandwidth << "MB/s" << std::endl;
    std::cout << std::endl;
    //std::cout << "Rezultat izvodenja A: " << mA -> result << std::endl;

    std::cout << "Vrijeme pristupa C:   " << mC -> time << " ns" << std::endl;
    std::cout << "Propusnost C:         " << mC -> bandwidth << "MB/s" << std::endl;
    std::cout << std::endl;
    //std::cout << "Rezultat izvodenja A: " << mA -> result << std::endl;

    std::cout << "Vrijeme pristupa D:   " << mD -> time << " ns" << std::endl;
    std::cout << "Propusnost D:         " << mD -> bandwidth << "MB/s" << std::endl;
    std::cout << std::endl;
    //std::cout << "Rezultat izvodenja A: " << mA -> result << std::endl;

    std::cout << "t(L2)/t(L1) = " << mB -> time / mA -> time << std::endl;
    std::cout << "t(L3)/t(L2) = " << mC -> time / mB -> time << std::endl;
    std::cout << "t(RAM)/t(L3) = " << mD -> time / mC -> time << std::endl; 

    free(mA);
    free(mB);
    free(mC);
    free(mD);
    
    return 0;
}