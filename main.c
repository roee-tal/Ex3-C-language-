#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TXT 1024
#define WORD 30

int calc_g_txt(char *word,int start,int end){
    int sum = 0;
    char *ptr = word;
    for(int i=start; i <= end;i++){
        if(ptr[i] >= 'a' && ptr[i] <= 'z'){
            sum = sum + ptr[i] - 'a' + 1;
        }
        if(ptr[i] >= 'A' && ptr[i] <= 'Z'){
            sum = sum + ptr[i] - 'A' + 1;
        }
    }
    return sum;
}

int calc_g(char *word){
    int sum = 0;
    for(int i=0; word[i] != '\0';i++){
        if(word[i] >= 'a' && word[i] <= 'z'){
            sum = sum + word[i] - 'a' + 1;
        }
        if(word[i] >= 'A' && word[i] <= 'Z'){
            sum = sum + word[i] - 'A' + 1;
        }
    }
    return sum;
}

char *extract_k(char *word, int start,int end){
    char *copy;
    copy= (char*)malloc(strlen(word));
    if(copy == NULL){
        exit(1);
    }
    char *ptr = word;
    int k=0;
    for(int i=start; i <= end;i++){
        copy[k] = ptr[i];
        k++;
    }
    return copy;
}

int check_identical(char *txt,char *word, int start,int end){
    int sort_word[128] = {0};
    int sort_txt[128] = {0};
    for(int i=0; i<strlen(word);i++){
        if(word[i] != ' ' && word[i] != '\n' && word[i] != '\t'){
            char c = word[i];
            int ind = (int)(c);
            sort_word[ind]++;
        }
    }
    for(int i=start; i <= end;i++){
        if(txt[i] != ' ' && txt[i] != '\n' && txt[i] != '\t'){
            char c = txt[i];
            int ind = (int)(c);
            sort_txt[ind]++;
        }
    }
    for(int i=0;i<128;i++){
        if(sort_txt[i] != sort_word[i]){
            return 0;
        }
    }
    return 1;
}

char *rev_atbash(char *po){
    char *tem;
    tem= (char*)malloc(strlen(po));
    if(tem == NULL){
        exit(1);
    }
    for(int i=0;i<strlen(po);i++){
        char ch = po[strlen(po)-i-1];
        tem[i]= ch;
    }
    return tem;

}
char *calc_atbash(char word[]){
    char *res;
    res = (char*)malloc(strlen(word));
    if(res == NULL){
        exit(1);
    }
    for(int i=0;i<strlen(word);i++){
        if(word[i] <= 'z' && word[i] >= 'a'){
            int asci = (int)(word[i]);
            int new_c = 'z' - asci + 'a';
            char at = (char)(new_c);
            res[i] = at;
        }
        else if(word[i] <= 'Z' && word[i] >= 'A'){
            int asci = (int)(word[i]);
            int new_c = 'Z' - asci + 'A';
            char at = (char)(new_c);
            res[i] = at;
        }
    }
    return res;
}

int check_identical_atbash(char txt[],char *word,int start,int end){
    int j=0;
    for(int i=start;i<end;i++){
        if(isalpha(txt[i])){
            if(txt[i]!=word[j]){
                return 0;
            }
            else if(txt[i]==word[j]){
                j++;
            }
        else if(!isalpha(txt[i])){
            continue;
        }
    }
    }
    return 1;
}

void atBash(char word[], char txt[]){
    char *atbash = calc_atbash(word);
    char* rev = rev_atbash(atbash);
    int value_of_word = calc_g(atbash);
    int counter = 0;
    for(int i=0,j=0; j<strlen(txt) && i<strlen(txt);){
        int g_of_arr = calc_g_txt(txt,i,j);
        if (g_of_arr == value_of_word){
            if(isalpha(txt[i]) && isalpha(txt[j])){
                if(check_identical_atbash(txt,atbash,i,j) == 1 || check_identical_atbash(txt,rev,i,j) == 1 ){
                    char *res = extract_k(txt,i,j);
                    i++;
                    if(counter == 0){
                        printf("%s",res);
                        counter++;
                    }
                    else{
                        printf("~%s",res);
                    }
                    free(res);
                }
                else {
                    i++;
                }
            }
            else if(!isalpha(txt[i])){
                i++;
            }
            else if(!isalpha(txt[j])){
                j++;
            }
        }
            else if(g_of_arr> value_of_word){
                i++;
            }
            else if(g_of_arr < value_of_word){
                j++;
            }  
    }
    free(atbash);
    free(rev);        
}

void anagram(char word[], char txt[]){
    int value_of_word = calc_g(word);
    int counter = 0;
    for(int i=0,j=0; j<strlen(txt) && i<strlen(txt);){
        int g_of_arr = calc_g_txt(txt,i,j);
        if (g_of_arr == value_of_word){
            if(isalpha(txt[i]) && isalpha(txt[j])){
                if(check_identical(txt,word,i,j) == 1){
                    char *res = extract_k(txt,i,j);
                    i++;
                    if(counter == 0){
                        printf("%s",res);
                        counter++;
                    }
                    else{
                        printf("~%s",res);
                    }
                    free(res);
                }
                else if(check_identical(txt,word,i,j) == 0){
                    i++;
                }
            }
            else if(!isalpha(txt[i])){
                i++;
            }
            else if(!isalpha(txt[j])){
                j++;
            }
        }
            
            else if(g_of_arr> value_of_word){
                i++;
            }
            else if(g_of_arr < value_of_word){
                j++;
            }  
    }
}

void gematria(char word[], char txt[]){
    int value_of_word = calc_g(word);
    int counter = 0;
    for(int i=0,j=0; j<strlen(txt) && i<strlen(txt);){
        int g_of_arr = calc_g_txt(txt,i,j);
        if (g_of_arr == value_of_word){
            if(isalpha(txt[i]) && isalpha(txt[j])){
                char *res = extract_k(txt,i,j);
                i++;
                 if(counter == 0){
                        printf("%s",res);
                        counter++;
                }
                else{
                    printf("~%s",res);
                }
                free(res);
            }
            else if(!isalpha(txt[i])){
            i++;
        }
        else if(!isalpha(txt[j])){
            j++;
        }
        }
        else if(g_of_arr> value_of_word){
            i++;
        }
        else if(g_of_arr < value_of_word){
            j++;
        }
    }
}   

int main(){
    
   char *word_arr = (char*)malloc(WORD);
   if(word_arr==NULL){
        return 0;
    } 
    int cou = 0;
    for(int i=0;WORD ; i++){
        char c = getc(stdin);
        if(c == '\n' || c == ' ' || c == '\t'){
            break;
        }
        else{
            word_arr[i] = c;
            cou++;
        }
    }
    word_arr[cou] = '\0';

    char *txt_arr = (char*)malloc(TXT);
    if(txt_arr == NULL){
        return 0;
        
    } 
    cou = 0;
    for(int i=0;TXT ; i++){
        char c = getc(stdin);
        if(c == '~'){
            break;
        }
        else{
            txt_arr[i] = c;
            cou++;
        }
    }
    txt_arr[cou] = '\0';

    printf("Gematria Sequences: ");
    gematria(word_arr,txt_arr);
    printf("\n");
    printf("Atbash Sequences: ");
    atBash(word_arr,txt_arr);
    printf("\n");
    printf("Anagram Sequences: ");
    anagram(word_arr,txt_arr);
    // printf("\n");

    free(txt_arr);
    free(word_arr);
    return 0;
}
