#include <stdio.h>
#include <math.h>

int main(void)
{
	char a[8];
	int bin[32];
	int i, j = 0, k = -1;
	int hugo = 0;
    float sisu = 0;
    float kasu = 1;
    float result;
	
	for(i = 0; i < 8; i++){
		a[i] = 0;
	}
    
	printf("8桁の16進数を入力してください：");
	scanf("%s", a);
	
	for(i = 0; i < 29; i += 4){
		if(a[j] == '0'){
			bin[i] = 0;
			bin[i+1] = 0;
			bin[i+2] = 0;
			bin[i+3] = 0;
		}
		else if(a[j] == '1'){
			bin[i] = 0;
			bin[i+1] = 0;
			bin[i+2] = 0;
			bin[i+3] = 1;
		}
		else if(a[j] == '2'){
			bin[i] = 0;
			bin[i+1] = 0;
			bin[i+2] = 1;
			bin[i+3] = 0;
		}
		else if(a[j] == '3'){
			bin[i] = 0;
			bin[i+1] = 0;
			bin[i+2] = 1;
			bin[i+3] = 1;
		}
		else if(a[j] == '4'){
			bin[i] = 0;
			bin[i+1] = 1;
			bin[i+2] = 0;
			bin[i+3] = 0;
		}
		else if(a[j] == '5'){
			bin[i] = 0;
			bin[i+1] = 1;
			bin[i+2] = 0;
			bin[i+3] = 1;
		}
		else if(a[j] == '6'){
			bin[i] = 0;
			bin[i+1] = 1;
			bin[i+2] = 1;
			bin[i+3] = 0;
		}
		else if(a[j] == '7'){
			bin[i] = 0;
			bin[i+1] = 1;
			bin[i+2] = 1;
			bin[i+3] = 1;
		}
		else if(a[j] == '8'){
			bin[i] = 1;
			bin[i+1] = 0;
			bin[i+2] = 0;
			bin[i+3] = 0;
		}
		else if(a[j] == '9'){
			bin[i] = 1;
			bin[i+1] = 0;
			bin[i+2] = 0;
			bin[i+3] = 1;
		}
		else if(a[j] == 'a' || a[j] == 'A'){
			bin[i] = 1;
			bin[i+1] = 0;
			bin[i+2] = 1;
			bin[i+3] = 0;
		}
		else if(a[j] == 'b' || a[j] == 'B'){
			bin[i] = 1;
			bin[i+1] = 0;
			bin[i+2] = 1;
			bin[i+3] = 1;
		}
		else if(a[j] == 'c' || a[j] == 'C'){
			bin[i] = 1;
			bin[i+1] = 1;
			bin[i+2] = 0;
			bin[i+3] = 0;
		}
		else if(a[j] == 'd' || a[j] == 'D'){
			bin[i] = 1;
			bin[i+1] = 1;
			bin[i+2] = 0;
			bin[i+3] = 1;
		}
		else if(a[j] == 'e' || a[j] == 'E'){
			bin[i] = 1;
			bin[i+1] = 1;
			bin[i+2] = 1;
			bin[i+3] = 0;
		}
		else if(a[j] == 'f' || a[j] == 'F'){
			bin[i] = 1;
			bin[i+1] = 1;
			bin[i+2] = 1;
			bin[i+3] = 1;
		}
        
		else {
			printf("error\n");
			return 1;
		}
        
		j++;
	}
	
    printf("2進数：");
	for(i = 0; i < 32; i++){
		printf("%d", bin[i]);
	}
	printf("\n");
	
	if(bin[1] == 0 && bin[2] == 0 && bin[3] == 0 && bin[4] == 0 && bin[5] == 0 && bin[6] == 0 && bin[7] == 0 && bin[8] == 0){
		if(bin[9] == 0 && bin[10] == 0 && bin[11] == 0 && bin[12] == 0 && bin[13] == 0 && bin[14] == 0 && bin[15] == 0 && bin[16] == 0
		   && bin[17] == 0 && bin[18] == 0 && bin[19] == 0 && bin[20] == 0 && bin[21] == 0 && bin[22] == 0 && bin[23] == 0 && bin[24] == 0
		   && bin[25] == 0 && bin[26] == 0 && bin[27] == 0 && bin[28] == 0 && bin[29] == 0 && bin[30] == 0 && bin[31] == 0){
			printf("ゼロです。\n");
			return 0;
		}
		else{
			printf("非正規化数です。\n");
			return 0;
		}
	}
	
	if(bin[1] == 1 && bin[1] == 1 && bin[3] == 1 && bin[4] == 1 && bin[5] == 1 && bin[6] == 1 && bin[7] == 1 && bin[8] == 1){
		if(bin[9] == 0 && bin[10] == 0 && bin[11] == 0 && bin[12] == 0 && bin[13] == 0 && bin[14] == 0 && bin[15] == 0 && bin[16] == 0
		   && bin[17] == 0 && bin[18] == 0 && bin[19] == 0 && bin[20] == 0 && bin[21] == 0 && bin[22] == 0 && bin[23] == 0 && bin[24] == 0
		   && bin[25] == 0 && bin[26] == 0 && bin[27] == 0 && bin[28] == 0 && bin[29] == 0 && bin[30] == 0 && bin[31] == 0){
			printf("無限大です。\n");
			return 0;
		}
		else{
			printf("NaNです。\n");
			return 0;
		}
	}
	
	if(bin[0] == 0){
		hugo = 1;
	}
	if(bin[0] == 1){
		hugo = -1;
	}
    
	if(hugo == 1){
        printf("符号：＋\n");
    }
    else if(hugo == -1){
        printf("符号：ー\n");
    }
    
	for(i = 1; i < 9; i++){
		if(bin[i] == 0){
            sisu += 0;
        }
        else if(bin[i] == 1){
            sisu += pow(2, 8-i);
        }
    }
	sisu -= 127;
	printf("指数部：%f\n", sisu);
    
	for(;i < 32; i++){
		if(bin[i] == 0){
			kasu += 0;
		}
		else if(bin[i] == 1){
			kasu += pow(2, k);
        }
        k--;
    }
    
    printf("仮数部：%f\n", kasu);
    
    result = hugo * pow(2, sisu) * kasu;
    printf("結果：%f\n", result);
    
    return 0;
}