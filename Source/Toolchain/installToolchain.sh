#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Este script instala la toolchain de esp-idf en el directorio especificado."
  echo "Ejemplo de uso: ./installToolchain.sh /ruta/al/directorio/de/instalacion"
else
  directorio="$1"
  if [ ! -d "$directorio" ]; then
    mkdir -p "$directorio"
    echo "El directorio $directorio se ha creado exitosamente."
  else
    echo "El directorio $directorio ya existe."
  fi

  # Verificar si git está instalado
  if ! command -v git &> /dev/null; then
      echo "git no está instalado. Por favor, instale git antes de continuar."
      exit
  fi

  # Descargar el instalador de la toolchain si no está descargado
  cd "$directorio"
  if [ ! -d "esp-idf" ]; then
      git clone --recursive https://github.com/espressif/esp-idf.git
  fi

  # Instalar la toolchain
  cd "esp-idf"
  ./install.sh
  
  cd ../..
  pwd
  echo "Presione Enter para continuar"
  read
  clear
  cat nextSteps.txt
fi