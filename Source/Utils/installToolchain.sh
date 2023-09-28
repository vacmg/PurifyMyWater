#!/bin/bash

# Lista de paquetes a comprobar
oldDir=$PWD
packages=("git" "wget" "unzip" "flex" "bison" "gperf" "python3" "python3-pip" "python3-venv" "python3-setuptools" "cmake" "ninja-build" "ccache" "libffi-dev" "libssl-dev" "dfu-util" "libusb-1.0-0")

if [ $# -eq 0 ]; then
  echo "Este script instala o desinstala la toolchain de esp-idf y sus dependencias en el directorio especificado."
  echo "Uso para instalación:"
  echo "   ./installToolchain.sh install /ruta/al/directorio/de/instalacion [version] [keep]"
  echo "Uso para desinstalación:"
  echo "   ./installToolchain.sh uninstall /ruta/al/directorio/de/instalacion"
  echo "Uso para descarga del archivo ZIP:"
  echo "   ./installToolchain.sh download /ruta/de/descarga [version]"
else
  if [ "$1" == "install" ]; then
    if [ $# -eq 1 ]; then
      echo "Uso para instalación:"
      echo "   ./installToolchain.sh install /ruta/al/directorio/de/instalacion [version] [keep]"
      exit 1
    fi

    # Comprobar si cada paquete está instalado, e instalarlo si no lo está
    for package in "${packages[@]}"; do
      if ! dpkg -s "$package" &> /dev/null; then
        echo "$package no está instalado. Instalando $package..."
        sudo apt-get install -y "$package"
      fi
    done

    # Si se han comprobado todos los paquetes, continuar con la instalación
    directorio="$2"
    if [ ! -d "$directorio" ]; then
      mkdir -p "$directorio"
      echo "El directorio $directorio se ha creado exitosamente."
    else
      echo "El directorio $directorio ya existe."
    fi

    # Ir al directorio de instalación
    cd "$directorio"

    # Comprobar si se especificó una versión personalizada, de lo contrario, utilizar la versión 5.1.1
    if [ $# -ge 3 ]; then
      if [ "$3" == "keep" ]; then
        keep=true
        version="5.1.1"
      else
        version="$3"
        if [ "$4" == "keep" ]; then
          keep=true
        else
          keep=false
        fi
      fi
    else
      version="5.1.1"
      keep=false
    fi

    # Generar el enlace de descarga de esp-idf
    download_link="https://github.com/espressif/esp-idf/releases/download/v$version/esp-idf-v$version.zip"

    # Comprobar si el archivo ZIP de esp-idf ya está descargado
    if [ ! -d "esp-idf" ]; then
      if [ ! -f "esp-idf-v$version.zip" ]; then
        wget "$download_link" -O "esp-idf-v$version.zip"
      fi
      unzip "esp-idf-v$version.zip"
      mv "esp-idf-v$version" esp-idf
      if [ "$keep" = false ]; then
        rm "esp-idf-v$version.zip"
      fi
    else
      echo "El archivo esp-idf ya está descargado."
    fi

    # Ir al directorio de esp-idf
    cd "esp-idf"

    # Instalar la toolchain
    ./install.sh esp32

    cd "$oldDir"
    pwd
    echo "Presione Enter para continuar"
    read
    clear
    less nextSteps.txt
  elif [ "$1" == "uninstall" ]; then
    if [ $# -eq 1 ]; then
      echo "Este comando desinstalará la toolchain esp-idf y eliminará la carpeta '.espressif' en el directorio home del usuario."
      echo "Uso para desinstalación:"
      echo "   ./installToolchain.sh uninstall /ruta/al/directorio/de/instalacion"
    else
      directorio="$2"
      # Eliminar la carpeta "esp-idf" en el directorio de instalación
      if [ -d "$directorio/esp-idf" ]; then
        echo "Desinstalando las librerías de esp-idf..."
        rm -rf "$directorio/esp-idf"
        echo "Las librerías de esp-idf en el directorio $directorio han sido eliminadas."
      else
        echo "No se encontraron librerías de esp-idf en $directorio."
      fi

      # Eliminar la carpeta ".espressif" en el directorio home del usuario
      if [ -d "$HOME/.espressif" ]; then
        echo "Eliminando la instalación de la toolchain esp-idf en la carpeta '.espressif' del directorio home del usuario..."
        rm -rf "$HOME/.espressif"
        echo "La instalación de la toolchain esp-idf en la carpeta '.espressif' ha sido eliminada."
      else
        echo "No se encontró una instalación de la toolchain esp-idf en la carpeta '.espressif' del directorio home del usuario."
      fi
    fi
  elif [ "$1" == "download" ]; then
    if [ $# -lt 3 ]; then
      echo "Uso para descarga del archivo ZIP:"
      echo "   ./installToolchain.sh download /ruta/de/descarga [version]"
      exit 1
    fi

    # Comprobar si se especificó una versión personalizada, de lo contrario, utilizar la versión 5.1.1
    if [ $# -ge 3 ]; then
      version="$3"
    else
      version="5.1.1"
    fi

    # Ruta de descarga personalizada
    download_dir="$2"

    # Comprobar si la ruta de descarga existe, de lo contrario, crearla
    if [ ! -d "$download_dir" ]; then
      mkdir -p "$download_dir"
      echo "El directorio de descarga $download_dir se ha creado exitosamente."
    fi

    # Ir al directorio de descarga
    cd "$download_dir"

    # Generar el enlace de descarga de esp-idf
    download_link="https://github.com/espressif/esp-idf/releases/download/v$version/esp-idf-v$version.zip"

    # Comprobar si el archivo ZIP de esp-idf ya está descargado
    if [ ! -f "esp-idf-v$version.zip" ]; then
      wget "$download_link" -O "esp-idf-v$version.zip"
    else
      echo "El archivo esp-idf ya está descargado."
    fi
  else
    echo "Opción no válida. Utilice 'install' para instalar esp-idf, 'uninstall' para desinstalar o 'download' para descargar el archivo ZIP."
  fi
fi

