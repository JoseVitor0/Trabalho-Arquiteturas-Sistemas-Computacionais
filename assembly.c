/*
Arquiteturas de sistemas computacionais
Nomes: José Vitor Gonçalves, Jonathan Souza Pepi, Yan Benck Baldissera
Interpretador de Assembly MIPS em C
Instruções suportadas: ADD, SUB, MUL, ADDI, BGE, BLE, BGT, NEG, J
*/




#include <stdio.h>
#include <string.h>

#define NUM_INSTRUCOES 100

int PC = 0;

//7 Labels
typedef struct {
    char label[10];
    int endereco;
} Label;

Label labels[NUM_INSTRUCOES];
int label_count = 0;

//7 Labels
void adicionarLabel(char *nome, int endereco) {
    strcpy(labels[label_count].label, nome);
    labels[label_count].endereco = endereco;
    label_count++;
}

//7 Labels
int buscarLabel(char *nome) {
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].label, nome) == 0) {
            return labels[i].endereco;
        }
    }
    return -1;
}

//8 Instruções Branch
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

//6 Instruções de operações
void instrucoesOperacoes(char *comando, int reg0, int reg1, int reg2, int *registradores) {

    if (strcmp(comando, "add") == 0) {
        registradores[reg0] = registradores[reg1] + registradores[reg2];

        printf("\nRegistradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d\n", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);

    } else if (strcmp(comando, "sub") == 0) {
        registradores[reg0] = registradores[reg1] - registradores[reg2];

        printf("\nRegistradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d\n", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);

    } else if (strcmp(comando, "mul") == 0) {
        registradores[reg0] = registradores[reg1] * registradores[reg2];

        printf("\nRegistradores modificados: \n");
        printf("$%d = %d, $%d = %d, $%d = %d\n", reg0, registradores[reg0], reg1, registradores[reg1], reg2, registradores[reg2]);

    } else if (strcmp(comando, "addi") == 0) {
        registradores[reg0] = registradores[reg1] + reg2;

        printf("\nRegistradores modificados: \n");
        printf("$%d = %d, $%d = %d\n", reg0, registradores[reg0], reg1, registradores[reg1]);

    } else {
        printf("\nERRO! Instrucao nao reconhecida\n");
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

//3 Reconhecer comando
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

//5 Validar os registradores
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

    //Sequência
    //1 Registradores
    //2 Menu
    //3 Reconhecer comando
    //4 Separação dos registradores ou valores imediatos

    //5 Validar os registradores
    //6 Instruções de operação
    //7 Labels

    //8 Instruções Branch
    //9 Jump
    //10 Instrução Neg
    //11 Atualização dos registradores

    char instrucao[40];
    char comando[5]; 
    char reg3[3], reg1[3], reg2[3];
    char label[10];

    //7 Labels
    adicionarLabel("init", 4);
    adicionarLabel("if", 24);
    adicionarLabel("else", 28);
    adicionarLabel("loop_for", 16);
    adicionarLabel("fim", 32);

 


    //1 Registradores
    int registradores[32] = {0}; 

    
    for (int i = 0; i < 32; i++){
        registradores[i] = i;
    }

    int continuar = 0;


    //2 Menu
    do{
        printf("Digite o comando da operacao que deseja realizar");
        printf("\nOperacoes disponiveis: Add, Sub, Mul, Addi, Beq, Bgt, Ble, J, Neg\n");
        printf("Para instruções BGT, BEQ, BLE e J, labels disponiveis: 'init', 'loop_for', 'fim'\n");
        scanf("%[^\n]", instrucao); 
        printf("%s\n", instrucao);

        sscanf(instrucao, "%4s", comando);
        comando[4] = '\0';
        printf("%s\n", comando);

        //3 Reconhecer comando
        int cmd = reconhecerComando(comando);
        char *token = strtok(instrucao + strlen(comando) + 1, ", ");

        switch (cmd){
            case 1:

                //4 Separação dos registradores ou valores imediatos
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
                if(strcmp(comando, "addi") == 0){
                    printf("Registrador 1: %s (Valor: %d)\n", reg1, registradores[atoi(reg1 + 1)]);
                    printf("Registrador 2: %s (Valor: %d)\n", reg2, registradores[atoi(reg2 + 1)]);
                    printf("Valor imediatdo: %s\n", reg3);

                    //5 Validar os registradores
                    if (!validar_registrador(reg1) || !validar_registrador(reg2)) {
                        printf("Erro: Registradores não reconhecidos ou fora do formato esperado ($0 a $31).\n");
                    } else{
                        //6 Instruções de operações
                        instrucoesOperacoes(comando, atoi(reg1 + 1), atoi(reg2 + 1), atoi(reg3), registradores);
                    }

                } else {
                    printf("Registrador 1: %s (Valor: %d)\n", reg1, registradores[atoi(reg1 + 1)]);
                    printf("Registrador 2: %s (Valor: %d)\n", reg2, registradores[atoi(reg2 + 1)]);
                    printf("Registrador 3: %s (Valor: %d)\n", reg3, registradores[atoi(reg3 + 1)]);

                    //5 Validar os registradores
                    if (!validar_registrador(reg1) || !validar_registrador(reg2) || !validar_registrador(reg3)) {
                        printf("Erro: Registradores não reconhecidos ou fora do formato esperado ($0 a $31).\n");
                    } else{
                        //6 Instruções de operações
                        instrucoesOperacoes(comando, atoi(reg1 + 1), atoi(reg2 + 1), atoi(reg3 + 1), registradores);
                    }
                }

                PC++;
                printf("PC: %d", PC);


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
                    //8 Instruções Branch
                    instrucoesBranch(comando, registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], label, registradores);
                }
            break;

            case 3:
                if (token != NULL) { 
                    strcpy(label, token); 
                }
                //9 Instrução Jump
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
                    //9 Instrução Neg
                    instrucaoNeg(registradores[atoi(reg1 + 1)], registradores[atoi(reg2 + 1)], registradores);
                }

                PC++;
                printf("PC: %d", PC);
                
                break;

        
        default:
            printf("Erro: Comando não reconhecido\n");
            break;
        }


        //10 Atualização dos registradores
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
