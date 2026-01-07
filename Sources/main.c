#include "contactos.c"

tnodo raiz = NULL;

int main(){
    unsigned short salir = NO;
    char * comando,* argumento,* opcion;

    while (salir == NO)
    {
        printf("Ingresa el comando para la opcion respectiva\n\n");

        printf("add -> para agregar un contacto nuevo\n");
        printf("ls -> para ver todos los contactos\n");
        printf("rm \"nombre\" -> para eliminar un contacto\n");
        printf("sh \"nombre\" -> para buscar un contacto\n");
        printf("exit -> para salir del menu\n");
        
        opcion = leerLinea();
        opcion[strcspn(opcion,"\n")] = '\0';
        
        comando = strtok(opcion," ");
        argumento = strtok(NULL,"");
        switch (action(comando))
        {
        case ADD:
            guardarContacto();
            continue;
        case LS:
            listarContactos();
            continue;
        case RM:
            eliminarContacto(argumento);
            continue;
        case SH:
            buscarContacto(argumento);
            continue;
        case EXIT:
            salir = YES;
            continue;
        default:
            printf("no se reconocio el comando.");
            salir = YES;
            continue;
        }
    }
    free(comando);
    free(argumento);
    free(opcion);
    return 0;
}
