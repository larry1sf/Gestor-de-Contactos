# Gestor de Contactos

Descripción
- Aplicación en C para gestionar contactos (guardar, listar, buscar, eliminar) usando un archivo binario (`db.dat`).

Requisitos
- `gcc` (o `clang`), utilidades estándar de Unix.

Uso rápido
1. Abrir la carpeta del proyecto:

```bash
cd "Gestor de Contactos"
```

2. Compilar con el script `build.sh`:

```bash
./build.sh
```

3. Ejecutar el binario resultante:

```bash
./Sources/main
```

Opciones del `build.sh`
- `./build.sh test` — compila y ejecuta tests.
- `./build.sh clean` — limpia artefactos de compilación (`.o`, `libcontactos.a`, binarios).

Notas
- El script crea `libcontactos.a` y el ejecutable `Sources/main` en la raíz del proyecto.
- Antes de ejecutar, revisa o elimina `db.dat` si contiene datos de pruebas.
- Para comprobar fugas de memoria usa `valgrind --leak-check=full ./Sources/main`.

Licencia
- MIT
