#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Headers/contactos.h"

extern tnodo raiz;

int action(char * comando){
    if(strcmp(comando,"add") == YES) return ADD;
    if(strcmp(comando,"ls") == YES) return LS;
    if(strcmp(comando,"rm") == YES) return RM;
    if(strcmp(comando,"sh") == YES) return SH;
    if(strcmp(comando,"exit") == YES) return EXIT;
    else return -1;
}

char *leerLinea(void) {
    size_t size = 64, len = 0;
    char *buf = malloc(size);
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            buf = realloc(buf, size);
        }
        buf[len++] = c;
    }

    buf[len] = '\0';
    return buf;
}

static void pedirContacto(char * nombre, char ** number){
    printf("Vamos a ingresar un nuevo contacto\n");
    
    printf("Ingresa el nombre del contacto:");
    fgets(nombre,TNOMBRE,stdin);
    nombre[strcspn(nombre,"\n")] = '\0';
    char buffer[T_MAX_NUMBER];
    while (1)
    {
        printf("Ingresa el numero: ");
        fgets(buffer,sizeof buffer,stdin);

        if(!strchr(buffer,'\n')){
            int c;
            printf("El numero es demasiado largo\n");
            while ((c = getchar()) != '\n' && c != -1)
               continue;
            continue;
        }
        
        buffer[strcspn(buffer,"\n")] = '\0';
        
        if(strlen(buffer) != 10){
            printf("El numero debe de tener 10 digitos\n");
            continue;
        }

        *number = malloc(strlen(buffer) + 1);
        if(*number == NULL) exit(1);
        strcpy(*number,buffer);
        break;
    }
    

}

static void crearArchivo(tnodo * nuevo){
    FILE * arch = fopen("db.dat","wb");
    if(arch == NULL) exit(1);
    
    fwrite((*nuevo) -> nombre, sizeof (*nuevo) -> nombre,1,arch);
    
    size_t len = strlen((*nuevo) -> number) + 1; 
    fwrite(&len, sizeof len,1,arch);
    fwrite((*nuevo) -> number, len,1,arch);

    fclose(arch);
}

static void agregarArchivo(tnodo * nuevo){
    FILE * arch = fopen("db.dat","ab");
    if(!arch)exit(1);

    fwrite((*nuevo) -> nombre,sizeof (*nuevo) -> nombre,1,arch);

    size_t len = strlen((*nuevo) -> number) + 1;
    fwrite(&len,sizeof len,1,arch);
    fwrite((*nuevo) -> number,len,1,arch);

    fclose(arch);
}

static int tamanoBytes(){
    FILE *arch;
    arch=fopen("db.dat","rb");
    if (!arch) exit(1);
    int pos;
    fseek(arch, 0, SEEK_END);
    pos=ftell(arch);
    printf("El tamano en bytes del archivo es de: %i\n",pos);

    fclose(arch);
    return pos;
}

void guardarContacto(){
    tnodo nuevo = malloc(sizeof(* nuevo));
    FILE * arch = fopen("db.dat","a+b");
    if(!nuevo || !arch) exit(1);

    pedirContacto(nuevo -> nombre, &nuevo -> number);
    if(!tamanoBytes()){
        raiz = nuevo;
        crearArchivo(&nuevo);
    }
    else{
        nuevo -> sig = raiz;
        raiz = nuevo;
        agregarArchivo(&nuevo);
    }
}

void listarContactos() {
    FILE *arch = fopen("db.dat", "rb");
    if (!arch) exit(1);

    tnodo pila = malloc(sizeof *pila);

    while (fread(pila->nombre, sizeof pila->nombre, 1, arch) == 1) {

        size_t len;
        fread(&len, sizeof len, 1, arch);

        pila->number = malloc(len);
        fread(pila->number, len, 1, arch);

        printf("\nnombre: %s\nnumero: %s\n", pila->nombre, pila->number);

        free(pila->number);
    }

    free(pila);
    fclose(arch);
}

void buscarContacto(const char * nombre){
    FILE * arch = fopen("db.dat","rb");
    if(!arch) exit(1);
    
    tnodo reco = malloc(sizeof *reco);
    
    while (fread(reco -> nombre,sizeof reco -> nombre, 1, arch) == 1)
    {
        size_t len = 0;
        fread(&len,sizeof len,1,arch);
        
        reco -> number = malloc(len);
        fread(reco -> number,len,1,arch);

        if(strcmp(reco -> nombre,nombre) == 0){
           printf("\nNombre: %s\nNumero: %s\n\n",reco -> nombre, reco -> number); 
        }
        free(reco -> number);
    }
    free(reco);
    fclose(arch);
}

void eliminarContacto(const char * nombre){
    FILE * arch = fopen("db.dat","rb");
    FILE * temp = fopen("temp.dat","w");
    if(!arch || !temp) exit(1);

    tnodo actual = malloc(sizeof *actual);
    
    while (fread(actual -> nombre,sizeof actual -> nombre,1,arch) == 1)
    {
        size_t len = 0;
        fread(&len,sizeof len,1,arch);

        actual -> number = malloc(len);
        fread(actual -> number, len, 1, arch);

        if(strcmp(actual -> nombre,nombre) != 0){

            fwrite(actual -> nombre,sizeof actual -> nombre,1,temp);
            fwrite(&len,sizeof len,1,temp);
            fwrite(actual -> number,len,1,temp);
        }
      free(actual -> number);
    }
    free(actual);
    fclose(arch);
    fclose(temp);
    remove("db.dat");
    rename("temp.dat", "db.dat");
}