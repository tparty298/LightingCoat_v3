#include <iostream>
#define NUMTESTLED 170
#define WIDTH 1280
#define HEIGHT 720

int main(void){
    for(int i=0;i<NUMTESTLED;i++){
        std::cout<<int((WIDTH*i)/NUMTESTLED)<<","<<int((HEIGHT)/2)<<std::endl;
    }
    return 0;
}
