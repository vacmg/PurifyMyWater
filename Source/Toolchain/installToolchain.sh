#!/bin/bash

# Lista de paquetes a comprobar
oldDir=$PWD
packages=("git" "wget" "flex" "bison" "gperf" "python3" "python3-venv" "cmake" "ninja-build" "ccache" "libffi-dev" "libssl-dev" "dfu-util" "libusb-1.0-0")

if [ $# -eq 0 ]; then
  echo "Este script instala la toolchain de esp-idf en el directorio especificado."
  echo "Ejemplo de uso: ./installToolchain.sh /ruta/al/directorio/de/instalacion"
else
  # Comprobar si cada paquete está instalado
  for package in "${packages[@]}"; do
    if ! dpkg -s "$package" &> /dev/null; then
      echo "$package no está instalado. Por favor, instale $package antes de continuar."
      exit
    fi
  done

  # Si se han comprobado todos los paquetes, continuar con la instalación
  directorio="$1"
  if [ ! -d "$directorio" ]; then
    mkdir -p "$directorio"
    echo "El directorio $directorio se ha creado exitosamente."
  else
    echo "El directorio $directorio ya existe."
  fi

  # Descargar el instalador de la toolchain si no está descargado
  cd "$directorio"
  if [ ! -d "esp-idf" ]; then
      git clone --recursive https://github.com/espressif/esp-idf.git
  fi

  # Instalar la toolchain
  cd "esp-idf"
  ./install.sh
  
  cd $oldDir
  pwd
  echo "Presione Enter para continuar"
  read
  clear
  cat nextSteps.txt
fi

