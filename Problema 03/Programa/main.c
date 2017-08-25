/*******************************************************************************
Autor: Gustavo Henrique
Componente Curricular: MI - Algoritmos
Concluido em: 11/10/2015
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "funcoes.h"



Participante *Lista(){// Função responsável por retornar o inicio da lista.
    static Participante *L = NULL;
    return &L;
}

int main(){

    system("color 4f");
    Participante **L;// Ponteiro responsável por receber a chamada da função e apontar para o ponteiro que aponta para o inicio da lista.
    inserir_data_limite();// Verifica se a data limite foi atingida, se não tiver vai exigir que seja estabelecida uma data.
    if(buscar_arq() == 0){
        ler_arquivo();// Se existir o arquivo de texto com os dados, será lida todas as informações e armazenada na lista.
    }
    L = Lista();
    system("cls");
    int opcao = 0;
    do{
        opcao = menu();
        switch (opcao){
        case 1:
            if(verificar_data()== 1){
                printf("Data Limite Atingido, Nao e Mais Possivel Fazer Cadastros!");
                getchar();
            }
            else
                cadastrar_usuario();
            break;
        case 2:
            editar_cadastro();
            break;
        case 3:
            opcao_administrativa();
            break;
        case 4:
            gravar_dados();
            if(Lista() == NULL){
                system("del Cadastro.txt");// Se a lista for vazia, exclui o arquivo de texto.
            }
            free_lista();
            break;
        default:
            printf("Opcao invalida!\n");
        }
    }while(opcao != 4);
    return 0;
}

int menu(){

    system("cls");
    char opcao;
    printf("\t\tBem - Vindo ao sistema de cadastro do SEMIC\n\n");
    printf("1 - Cadastrar Usuario\n2 - Editar/Remover Cadastro\n3 - Opcoes Administrativas\n4 - Sair\n\n");
    do{
        scanf(" %c", &opcao);
        fflush(stdin);
        switch (opcao){
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        default:
            printf("Opcao Invalida!\n");
        }
    }while(opcao != '1' && opcao != '2' && opcao != '3');
    return 0;
}

void p_lista(char op){

    Participante *aux, **L;
    L = Lista();
    aux = *L;
    if (aux == NULL)
        printf("Lista Vazia!\n");
        getchar();
    while(aux != NULL){
        if(aux->ocupacao != op)
            p_cadastro(aux);
        aux = aux->proximo;
    }
}

void cadastrar_usuario(){

    char ocup;
    system("cls");
    Participante *usuario;
    usuario = (Participante *)malloc(sizeof(Participante));
    printf("\t\t|--> Cadastro do Usuario <--|\n\n");
    printf("Digite o seu CPF (XXX.XXX.XXX-XX)\n");
    scanf("%s", usuario->cpf);
    fflush(stdin);
    printf("Digite seu nome:\n");
    scanf("%[^\n]s", usuario-> nome);
    fflush(stdin);
    printf("Digite a sua matricula:\n");
    scanf("%s", usuario->matricula);
    fflush(stdin);
    printf("Digite a sua data de nascimento: DD/MM/AAAA\n");
    scanf("%s", usuario->nascimento);
    fflush(stdin);
    printf("Digite seu E-mail:\n");
    scanf("%s", usuario->email);
    fflush(stdin);
    printf("Qual a sua ocupacao?\nP - Professor\tA - Aluno\n");
    do{
        scanf(" %c", &ocup);
        fflush(stdin);
    }while(ocup != 'a' && ocup != 'A' && ocup != 'P' && ocup != 'p');
    if(ocup == 'a' || ocup == 'p')// Coloca a opção em caixa alta para melhorar a visualização.
        ocup = ocup - 32;
    usuario->ocupacao = ocup;
    usuario->proximo = NULL;
    add_lista(usuario);
}

void add_lista(Participante *novo){

    system("cls");
    Participante *aux, *aux2, *aux3, **L;
    L = Lista();
    aux = aux2 = aux3 = *L;
    if(*L==NULL)
        *L = novo;
    else{
        while(aux != NULL){
            if (strcmpi(aux->cpf,novo->cpf)==0){
                printf("Atencao usuario ja cadastrado!\nDeseja editar?, acesse a segunda opcao do menu!\n");
                getchar();
                break;
            }
            else if(strcmpi(novo->nome, aux->nome) < 0){
                if (aux2 == *L){
                    novo->proximo = *L;
                    *L=novo;
                    break;
                }
                novo->proximo = aux;
                aux2->proximo = novo;
                break;
            }
            else if (aux->proximo == NULL){
                aux->proximo = novo;
                break;
            }
            aux2=aux;
            aux = aux->proximo;
        }
    }
}

int editar_cadastro(){

    system("cls");
    char op;
    Participante *aux, *aux2, **L;
    aux = (Participante *) malloc( sizeof(Participante));
    L = Lista();
    aux2 = *L;
    if (*L == NULL){
        printf("Lista Vazia!\n");
        getchar();
    }
    else{
        printf("Digite o CPF cadastrado:\n");
        scanf("%s", aux->cpf);
        fflush(stdin);
        while(aux2 != NULL){
            if ((strcmp(aux->cpf, aux2->cpf) == 0)){
                printf("Cadastro Encontrado!\n");
                break;
            }
            else if(aux2->proximo == NULL){
                printf("Cadastro Nao Encontrado!\n");
                getchar();
                fflush(stdin);
                return 0;
            }
            aux2 = aux2->proximo;
        }
            p_cadastro(aux2);
            printf("Oque deseja fazer ?\n1- Editar\t2- Excluir\t3- Nada\n");
            op = getchar();
            fflush(stdin);
            switch (op){
            case '1':
                rm_cadastro(aux2);
                cadastrar_usuario();
                break;
            case '2':
                rm_cadastro(aux2);
                break;
            case '3':
                return 0;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
    }
    return 0;
}

void p_cadastro(Participante *cadastro){

    printf("\nCPF\t\t\t-> %s", cadastro->cpf);
    printf("\nNome\t\t\t-> %s", cadastro->nome);
    printf("\nMatricula\t\t-> %s", cadastro->matricula);
    printf("\nData de Nascimento\t-> %s", cadastro->nascimento);
    printf("\nE-mail\t\t\t-> %s", cadastro->email);
    printf("\nOcupacao\t\t-> %c\n", cadastro->ocupacao);

}

void rm_cadastro(Participante *cadastro){

    Participante *aux, *aux2, **L;
    L = Lista();
    aux = aux2 = *L;
    if (*L==NULL){
        printf("Lista vazia!\n");
    }
    else if(aux != NULL && aux == cadastro){
        *L = aux->proximo;
        free(aux);
    }
    else{
        aux=aux->proximo;
        while(aux!=NULL){
            if(aux == cadastro){
                aux2->proximo = aux->proximo;
                free(aux);
                break;
            }
            aux2=aux;
            aux=aux->proximo;
        }
    }
}

void gravar_dados(){

    Participante **aux = Lista();
    FILE *arq;
    arq = fopen("Cadastro.txt", "w");
    if(arq==NULL){
        printf("Nao foi possivel criar o arquivo!\n");
        getchar();
    }
    else{
        while(*aux != NULL){
            fprintf(arq, "\n%s", (*aux)->cpf);
            fprintf(arq, "\n%s", (*aux)->nome);
            fprintf(arq, "\n%s", (*aux)->matricula);
            fprintf(arq, "\n%s", (*aux)->nascimento);
            fprintf(arq, "\n%s", (*aux)->email);
            fprintf(arq, "\n%c", (*aux)->ocupacao);
            (*aux) = (*aux)->proximo;
        }
    }
    fclose(arq);
}

void ler_arquivo(){

    Participante *aux, *aux2, **L;
    L = Lista();
    aux = aux2 = NULL;
    FILE *arq;
    arq = fopen("Cadastro.txt", "r");
    fgetc(arq);
    while(!feof(arq)){
        aux = (Participante *) malloc(sizeof(Participante));
        fgets(aux->cpf, "%s", arq);
        aux->cpf[strlen(aux->cpf)-1] = '\0';// Como o fgets captura toda a linha inclusive o \n, eu alterei o \n por \0.
        fgets(aux->nome, "%s", arq);
        aux->nome[strlen(aux->nome)-1] = '\0';
        fgets(aux->matricula, "%s", arq);
        aux->matricula[strlen(aux->matricula)-1] = '\0';
        fgets(aux->nascimento, "%s", arq);
        aux->nascimento[strlen(aux->nascimento)-1] = '\0';
        fgets(aux->email, "%s", arq);
        aux->email[strlen(aux->email)-1] = '\0';
        aux->ocupacao = fgetc(arq);
        fgetc(arq);
        if (*L == NULL)
            *L = aux2 = aux;
        else{
            aux2->proximo = aux;
            aux2 = aux2->proximo;
        }
    }
    fclose(arq);
}

int buscar_arq(){

    FILE *arq;
    arq = fopen("Cadastro.txt", "r");
    fclose(arq);
    if (arq == NULL)
        return 1;
    return 0;
}

void opcao_administrativa(){

    char senha[10], pass[10] = "admin", op, op2;// Aqui é definida a senha padrão do administrador, "admin".
    printf("-->AREA ADMINISTRATIVA<--\n");
    printf("\nPara ter acesso digite a senha: ");
    scanf("%[^\n]s", senha);
    fflush(stdin);
    if (strcmp(senha, pass) == 0){// Aqui a senha é comparada com a introduzida pelo usuário.
        system("cls");
        do{
            printf("\t\tBem - Vindo!\n\n");
            printf("Escolha uma das opcoes :\n");
            printf("1- Listar cadastros\n2- Editar/Remover dados cadastrados\n3- Alterar data do evento\n4- Sair\n");
            do{
                op = getchar();
                fflush(stdin);
            }while(op != '1' && op != '2' && op != '3' && op != '4');
            switch(op){
            case '1':
                printf("Escolha oque deseja listar!\n1- Todos\t2- Professores\t3- Alunos\n");
                do{
                    op2 = getchar();
                    if(op2 != '1' && op2 != '2' && op2 != '3')
                        printf("Opcao Invalida!\n");
                }while(op2 != '1' && op2 != '2' && op2 != '3');
                fflush(stdin);
                if(op2 == '1')
                    op2 = 'T';// Aqui eu passo T para poder listar todos os cadastros, pois vou exibir apenas os cadastros diferente de 'T'.
                else if(op2 == '2')
                    op2 = 'A';// Aqui eu passo A para poder listar professores, pois eu vou apenas exibir os cadastros diferente de 'A'.
                else if(op2 == '3')
                    op2 = 'P';// Aqui eu passo P para poder listar alunos, pois eu vou apenas exibir os cadastros diferentes de 'P'.
                p_lista(op2);
                break;
            case '2':
                editar_cadastro();
                break;
            case '3':
                system("del data.txt");
                inserir_data_limite();
                break;
            case '4':
                break;
            default:
                printf("Opcao Invalida!\n");
                break;
            }
        }while(op != '4');
    }
}

int verificar_data(){

    int dia = 0, mes = 0, ano = 0;
    struct tm *ptr;
    time_t timer = time(NULL);
    ptr = localtime(&timer);
    if (buscar_arq() == 1){
        FILE *arq;
        arq = fopen("data.txt", "r");
        fscanf(arq, "%d", &dia);
        fscanf(arq, "%d", &mes);
        fscanf(arq, "%d", &ano);
        fclose(arq);
        if(ano < ptr->tm_year+1900)
            return 1;
        if(ano == ptr->tm_year+1900 && mes < ptr->tm_mon+1)
            return 1;
        if(ano == ptr->tm_year+1900 && mes == ptr->tm_mon+1 && dia < ptr->tm_mday)
            return 1;
        else
            return 0;
    }
    return 0;
}

void inserir_data_limite(){

    int dia = 0, mes = 0, ano = 0;
    FILE *arq;
    arq = fopen("data.txt", "r");
    if (arq == NULL){
        arq = fopen("data.txt", "w");
        printf("[Digite a data limite do evento]\n\n");
        printf("Digite a data (DD) : ");
        scanf("%d", &dia);
        printf("Digite o numero do mes (MM) : ");
        scanf("%d", &mes);
        printf("Digite o ano (AAAA) : ");
        scanf("%d", &ano);
        fprintf(arq, "%d\n%d\n%d", dia, mes, ano);
    }
    fclose(arq);
}

void free_lista(){

    Participante *aux, **L;
    aux = L = Lista();
    while(aux != NULL){
        aux = aux->proximo;
        free(*L);
        *L = aux;
    }
}

