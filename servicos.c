#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 5
#define MAX_PROVIDERS 5
#define MAX_SERVICES 5

typedef struct {
    char nome[50];
    char email[50];
    char telefone[15];
    char UF[3];
} Client;

typedef struct {
    char nome[50];
    char email[50];
    char telefone[15];
    char UF[3];
    char tipo_servico[30];
} ServiceProvider;

typedef struct {
    char cliente[50];
    char prestador_servico[50];
    char tipo[30];
    float valor;
    char UF[3];
    char data[10];
} ServiceProvided;

Client clients[MAX_CLIENTS] = {
    {"João Silva", "joao@example.com", "1111111111", "SP"},
    {"Maria Souza", "maria@example.com", "2222222222", "RJ"},
    {"Carlos Pereira", "carlos@example.com", "3333333333", "MG"},
    {"Ana Oliveira", "ana@example.com", "4444444444", "RS"},
    {"Paulo Mendes", "paulo@example.com", "5555555555", "RS"}
};

int client_count = 5;

ServiceProvider providers[MAX_PROVIDERS] = {
    {"Lucas Martins", "lucas@example.com", "6666666666", "SP", "ELETRICISTA"},
    {"Fernanda Costa", "fernanda@example.com", "7777777777", "RJ", "ENCANADOR"},
    {"Bruno Rocha", "bruno@example.com", "8888888888", "MG", "PINTOR"},
    {"Julia Almeida", "julia@example.com", "9999999999", "BA", "JARDINEIRO"},
    {"Marcos Lima", "marcos@example.com", "1010101010", "RS", "MARCENEIRO"}
};

int provider_count = 5;

ServiceProvided services[MAX_SERVICES] = {
    {"joao@example.com", "lucas@example.com", "ELETRICISTA", 300.0, "SP", "2024-06-01"},
    {"maria@example.com", "fernanda@example.com", "ENCANADOR", 200.0, "RJ", "2024-06-05"},
    {"carlos@example.com", "bruno@example.com", "PINTOR", 150.0, "MG", "2024-06-10"},
    {"ana@example.com", "julia@example.com", "JARDINEIRO", 100.0, "BA", "2024-06-15"},
    {"paulo@example.com", "marcos@example.com", "MARCENEIRO", 250.0, "RS", "2024-06-20"}
};

int service_count = 5;

void list_clients() {
    for (int i = 0; i < client_count; i++) {
        printf("Nome: %s, Email: %s, Telefone: %s, UF: %s\n", clients[i].nome, clients[i].email, clients[i].telefone, clients[i].UF);
    }
}

void list_clients_uf(char *uf) {
    for (int i = 0; i < client_count; i++) {
        if (strcmp(clients[i].UF, uf) == 0) {
            printf("Nome: %s, Email: %s, Telefone: %s, UF: %s\n", clients[i].nome, clients[i].email, clients[i].telefone, clients[i].UF);
        }
    }
}

int compare_clients(const void *a, const void *b) {
    return strcmp(((Client*)a)->nome, ((Client*)b)->nome);
}

void list_clients_nome_asc() {
    qsort(clients, client_count, sizeof(Client), compare_clients);
    list_clients();
}

void list_service_providers() {
    for (int i = 0; i < provider_count; i++) {
        printf("Nome: %s, Email: %s, Telefone: %s, UF: %s, Tipo de Serviço: %s\n", providers[i].nome, providers[i].email, providers[i].telefone, providers[i].UF, providers[i].tipo_servico);
    }
}

void list_service_providers_type(char *type) {
    for (int i = 0; i < provider_count; i++) {
        if (strcmp(providers[i].tipo_servico, type) == 0) {
            printf("Nome: %s, Email: %s, Telefone: %s, UF: %s, Tipo de Serviço: %s\n", providers[i].nome, providers[i].email, providers[i].telefone, providers[i].UF, providers[i].tipo_servico);
        }
    }
}

int compare_services(const void *a, const void *b) {
    float diff = ((ServiceProvided*)a)->valor - ((ServiceProvided*)b)->valor;
    return (diff > 0) - (diff < 0);
}

void list_services_provided() {
    for (int i = 0; i < service_count; i++) {
        printf("Cliente: %s, Prestador: %s, Tipo: %s, Valor: %.2f, UF: %s, Data: %s\n", services[i].cliente, services[i].prestador_servico, services[i].tipo, services[i].valor, services[i].UF, services[i].data);
    }
}

void list_services_provided_valor_asc() {
    qsort(services, service_count, sizeof(ServiceProvided), compare_services);
    for (int i = 0; i < service_count; i++) {
        printf("Cliente: %s, Prestador: %s, Tipo: %s, Valor: %.2f, UF: %s, Data: %s\n", services[i].cliente, services[i].prestador_servico, services[i].tipo, services[i].valor, services[i].UF, services[i].data);
    }
}

void execute_command(char *command) {
    if (strcmp(command, "list clients") == 0) {
        list_clients();
    } else if (strncmp(command, "list clients UF=", 16) == 0) {
        char uf[3];
        sscanf(command, "list clients UF=%2s", uf);
        list_clients_uf(uf);
    } else if (strcmp(command, "list clients nome:asc") == 0) {
        list_clients_nome_asc();
    } else if (strcmp(command, "list service_providers") == 0) {
        list_service_providers();
    } else if (strncmp(command, "list service_providers type=", 28) == 0) {
        char type[50];
        sscanf(command, "list service_providers type=%49s", type);
        list_service_providers_type(type);
    } else if (strcmp(command, "list services_provided") == 0) {
        list_services_provided();
    } else if (strcmp(command, "list services_provided valor:asc") == 0) {
        list_services_provided_valor_asc();
    } else {
        printf("Comando desconhecido: %s\n", command);
    }
}

int main() {

    printf("\nPossiveis comandos: ");
    printf("\n\n  list clients");
    printf("\n  list clients UF=<>");
    printf("\n  list clients nome:asc");
    
    printf("\n\n  list service_providers");
    printf("\n  list service_providers type=<>");
    
    printf("\n\n  list services_provided");
    printf("\n  list services_provided valor:asc\n");
    

    char command[256];
    while (1) {
        printf("\nDigite um comando (ou 'exit' para sair): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(command);
    }

    return 0;
}
