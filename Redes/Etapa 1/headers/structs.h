typedef struct roteador{
    int id;
    int porta;
    char ip[15];
} roteador;


typedef struct roteador_link{
    int id_atual;
    int id_proximo;
    int custo;
} roteador_link;


typedef struct pacote{
    int id_origem;
    int id_destino;
    char msg[100];
    int tipo;
} pacote;