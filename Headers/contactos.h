#define TNOMBRE 51
#define T_MAX_NUMBER 21

enum STATES
{
    YES,
    NO
};
enum COMANDS
{
    ADD,
    LS,
    RM,
    SH,
    EXIT
};

struct nodo
{
    char nombre[TNOMBRE];
    char *number;
    struct nodo *sig;
};

typedef struct nodo *tnodo;

/* API pública */
extern tnodo raiz;

int action(char *comando);
char *leerLinea(void);
void guardarContacto(void);
void listarContactos(void);
void buscarContacto(const char *nombre);
void eliminarContacto(const char *nombre);