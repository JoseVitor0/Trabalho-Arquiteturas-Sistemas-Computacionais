#include <stdio.h>
#include <string.h>

#define NUM_INSTRUCOES 100
#define MEM_SIZE 1024  // Define o tamanho da memória para simulação

int PC = 0;
int memoria[MEM_SIZE] = {0}; 

typedef struct {
    char label[10];
    int endereco;
} Label;

Label labels[NUM_INSTRUCOES];
int label_count = 0;

void adicionarLabel(char *nome, int endereco) {
    strcpy(labels[label_count].label, nome);
    labels[label_count].endereco = endereco;
    label_count++;
}

int buscarLabel(char *nome) {
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].label, nome) == 0) {
            return labels[i].endereco;
        }
    }
    return -1;
}

void instrucoesBranch(char *tipo, int reg1, int reg2, char *label, int *registradores) {
    int endereco_label = buscarLabel(label);

    if (endereco_label == -1) {
        printf("ERRO! Label %s não encontrada\n", label);
        return;
    }

    if ((strcmp(tipo, "bgt") == 0 && registradores[reg1] > registradores[reg2]) ||
        (strcmp(tipo, "beq") == 0 && registradores[reg1] == registradores[reg2]) ||
        (strcmp(tipo, "ble") == 0 && registradores[reg1] <= registradores[reg2])){
            PC = endereco_label;
            printf("PC apos comparacao: %d\n", PC);
    } else {
        printf("Comparacao nao satisfeita.\n");
        PC++;
    }

    printf("PC apos comparacao: %d\n", PC);
}


void instrucoesOperacoes(char *comando, int reg0, int reg1, int reg2, int *registradores){
    //add $0, $1, $2
    //Instruções do tipo R: Add, Sub, And

    if(strcmp(comando, "add") == 0){
        registradores[reg0] = registradores[reg1] + registradores[reg2];

        printf("\nRegistradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);

    } else if (strcmp(comando, "sub") == 0){

        registradores[reg0] = registradores[reg1] - registradores[reg2];
        printf("Registradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);

    } else if (strcmp(comando, "mul") == 0){
        
        registradores[reg0] = registradores[reg1] * registradores[reg2];
        printf("\nRegistradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);

    } else if(strcmp(comando, "addi")){

        registradores[reg0] = registradores[reg1] + reg2;

        printf("Registradores modificados: \n");
        printf("$%d = %d, $%d = %d", reg0, registradores[reg0], reg1, registradores[reg1]);

    } 
    
    else {
        printf("ERRO! Instrucao nao reconhecida");
    }

}

void instrucaoJump(char *label) {
    int jump_addr = buscarLabel(label);
    if (jump_addr != -1) {
        PC = jump_addr;
        printf("JUMP: PC alterado para %d\n", PC);
    } else {
        printf("ERRO! Label %s não encontrada\n", label);
    }
}

void instrucaoNeg(int reg1, int reg2, int *registradores){
    registradores[reg1] = (registradores[reg2] * -1);
    printf("Registradores modificados: \n");
    printf("$%d = %d, $%d = %d\n", reg1, registradores[reg1], reg2, registradores[reg2]);
}


int reconhecerComando(char *comando){

    if (strcmp(comando, "add") == 0 || strcmp(comando, "sub") == 0 || strcmp(comando, "mul") == 0 || strcmp(comando, "addi") == 0){
        return 1;
    } else if(strcmp(comando, "beq") == 0 || strcmp(comando, "bgt") == 0  || strcmp(comando, "ble") == 0){
        return 2;
    } else if (strcmp(comando, "j") == 0) {
        return 3;
    } else if (strcmp(comando, "neg") == 0){
        return 4;
    }
    return 0;

}


int validar_registrador(const char *reg) {

    if (reg[0] != '$') return 0;

    int numero = atoi(reg + 1);

    for (int i = 1; reg[i] != '\0'; i++) {
        if (!isdigit(reg[i])) return 0;
    }

    if (numero < 0 || numero > 31) return 0;

    return 1;
}

int main()
{

    char instrucao[40];
    char comando[5]; 
    char reg3[3], reg1[3], reg2[3];
    char label[10];
    char addi[5] = "addi";

    adicionarLabel("init", 4);
    adicionarLabel("if", 24);
    adicionarLabel("else", 28);
    adicionarLabel("loop_for", 16);
    adicionarLabel("fim", 32);


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
        printf("\nOperacoes disponiveis: Add, Sub, Mul, Addi, Beq, Bgt, Ble, J, Neg\n");
        printf("Para instruções BGT, BEQ, BLE e J, labels disponiveis: 'init', 'loop_for', 'fim'\n");
        scanf("%[^\n]", instrucao); 
        printf("%s\n", instrucao);

        sscanf(instrucao, "%4s", comando);
        comando[4] = '\0';
        printf("%s\n", comando);

        int cmd = reconhecerComando(comando);
        char *token = strtok(instrucao + strlen(comando) + 1, ", ");

        switch (cmd){
            case 1:
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
                if(strcmp(comando, addi) == 0){
                    printf("Registrador 1: %s (Valor: %d)\n", reg1, registradores[atoi(reg1 + 1)]);
                    printf("Registrador 2: %s (Valor: %d)\n", reg2, registradores[atoi(reg2 + 1)]);
                    printf("Valor imediatdo: %s\n", reg3);
                    if (!validar_registrador(reg1) || !validar_registrador(reg2)) {
                        printf("Erro: Registradores não reconhecidos ou fora do formato esperado ($0 a $31).\n");
                    } else{
                        instrucoesOperacoes(comando, registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], atoi(reg3), registradores);
                    }

                } else {
                    printf("Registrador 1: %s (Valor: %d)\n", reg1, registradores[atoi(reg1 + 1)]);
                    printf("Registrador 2: %s (Valor: %d)\n", reg2, registradores[atoi(reg2 + 1)]);
                    printf("Registrador 3: %s (Valor: %d)\n", reg3, registradores[atoi(reg3 + 1)]);

                    if (!validar_registrador(reg1) || !validar_registrador(reg2) || !validar_registrador(reg3)) {
                        printf("Erro: Registradores não reconhecidos ou fora do formato esperado ($0 a $31).\n");
                    } else{
                        instrucoesOperacoes(comando, registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], registradores[atoi(reg3 + 1)], registradores);
                    }
                }


                break;

            case 2: 

                if (token != NULL) {
                    strcpy(reg1, token); 
                    token = strtok(NULL, ", "); 
                }
                if (token != NULL) {
                    strcpy(reg2, token);
                    token = strtok(NULL, ", "); 
                }
                if (token != NULL) {
                    strcpy(label, token);
                }
                if (!validar_registrador(reg1) || !validar_registrador(reg2)) {
                        printf("Erro: Registradores não reconhecidos ou fora do formato esperado ($0 a $31).\n");
                } else{
                    instrucoesBranch(comando, registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], label, registradores);
                }
            break;

            case 3:
                if (token != NULL) { 
                    strcpy(label, token); 
                }
                instrucaoJump(label);
                break;
            
            case 4:

                if (token != NULL) {
                    strcpy(reg1, token); 
                    token = strtok(NULL, ", "); 
                }
                if (token != NULL) {
                    strcpy(reg2, token);
                    token = strtok(NULL, ", "); 
                }

                if (!validar_registrador(reg1) || !validar_registrador(reg2)) {
                        printf("Erro: Registradores não reconhecidos ou fora do formato esperado ($0 a $31).\n");
                } else{
                    instrucaoNeg(registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], registradores);
                }
                
                break;

        
        default:
            printf("Erro: Comando não reconhecido\n");
            break;
        }


        printf("\n");
        printf("Registradores:");
        for (int i = 0; i < 32; i++){
            if (i % 8 == 0){
                printf("\n");
            }
            printf("%d\t", registradores[i]);
        }

        printf("\nDeseja continuar a fazer operacoes? (0 - Sim, 1 - Nao)\n");
        scanf("%d", &continuar);
        fflush(stdin);

        
    }while(continuar == 0);
    
    return 0;
}
