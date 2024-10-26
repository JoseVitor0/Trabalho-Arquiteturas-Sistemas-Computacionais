#include <stdio.h>
#include <string.h>

void instrucoesR(char *comando, int reg0, int reg1, int reg2, int *registradores){
    //add $0, $1, $2
    //Instruções do tipo R: Add, Sub, And

    char add[4] = "add";
    char sub[4] = "sub";
    char addu[4] = "addu";
    int retorno = 0;
    retorno = strcmp(comando, add);
    
    if(retorno == 0){
        registradores[reg0] = registradores[reg1] + registradores[reg2];


        printf("Registradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);
    }

    retorno = strcmp(comando, sub);
    if (retorno == 0){
        registradores[reg0] = registradores[reg1] - registradores[reg2];
        printf("Registradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);
    }

    retorno = strcmp(comando, addu);
    if(retorno == 0){
        int temp1 = 0;
        int temp2 = 0;

        if (registradores[reg1] < 0){
            temp1 = registradores[reg1] * (-1);
        } else{
            temp1 = registradores[reg1];
        }

        if (registradores[reg2] < 0){
            temp2 = registradores[reg2] * (-1);
        }else{
            temp2 = registradores[reg2];
        }
        registradores[reg0] = temp1 + temp2;
    }


}

int main()
{

    char instrucao[40];
    char comando[4]; 
    char reg3[3], reg1[3], reg2[3];

    //Instruções do tipo R: Add, Sub, And
    //Instruções do tipo I: Addi, Bgt, Bge,
    //Instruções do tipo J: J,  

    int registradores[32] = {0}; 

    
    for (int i = 0; i < 32; i++){
        registradores[i] = i;
    }

    int continuar = 0;

    do{
        printf("Digite o comando da operacao que deseja realizar");
        printf("\nOperacoes disponiveis: Add, Sub, Addu\n");
        scanf("%[^\n]", instrucao); 
        printf("%s\n", instrucao);

        strncpy(comando, instrucao, 3);
        comando[3] = '\0';
        printf("%s\n", comando);

        char *token = strtok(instrucao + 4, ", "); 

        if (token != NULL) {
            strcpy(reg1, token); 
            token = strtok(NULL, ", "); 
        }
        if (token != NULL) {
            strcpy(reg2, token);
            token = strtok(NULL, ", "); 
        }
        if (token != NULL) {
            strcpy(reg3, token);
        }

        printf("Comando: %s\n", comando);
        printf("Registrador 1: %s (Valor: %d)\n", reg1, registradores[atoi(reg1 + 1)]);
        printf("Registrador 2: %s (Valor: %d)\n", reg2, registradores[atoi(reg2 + 1)]);
        printf("Registrador 3: %s (Valor: %d)\n", reg3, registradores[atoi(reg3 + 1)]);


        instrucoesR(comando, registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], registradores[atoi(reg3 + 1)], registradores);

        printf("\n");
        for (int i = 0; i < 32; i++){
            printf("%d\t", registradores[i]);
        }

        printf("\nDeseja continuar a fazer operacoes? (0 - Sim, 1 - Nao)\n");
        scanf("%d", &continuar);
        fflush(stdin);

        
    }while(continuar == 0);
    
    return 0;
}
