#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR"

echo "Compilando libcontactos..."
gcc -IHeaders -Wall -Wextra -std=c11 -g -c Sources/contactos.c -o Sources/contactos.o
ar rcs libcontactos.a Sources/contactos.o

echo "Construyendo ejecutable main..."
gcc -IHeaders -Wall -Wextra -std=c11 -g Sources/main.c -L. -lcontactos -o Sources/main

if [ "${1-}" = "test" ]; then
  if [ -f tests/test_contactos.c ]; then
    echo "Compilando y ejecutando tests..."
    gcc -IHeaders -Wall -Wextra -std=c11 -g tests/test_contactos.c -L. -lcontactos -o tests/run_tests
    ./tests/run_tests
  else
    echo "No hay tests presentes."
  fi
fi

if [ "${1-}" = "clean" ]; then
  echo "Limpiando artefactos..."
  rm -f Sources/contactos.o libcontactos.a Sources/main tests/run_tests
  exit 0
fi

echo "Hecho. Ejecutable: Sources/main"
