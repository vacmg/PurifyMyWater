#!/bin/bash

# List of packages to check
oldDir=$PWD
packages=("git" "wget" "unzip" "flex" "bison" "gperf" "python3" "python3-pip" "python3-venv" "python3-setuptools" "cmake" "ninja-build" "ccache" "libffi-dev" "libssl-dev" "dfu-util" "libusb-1.0-0")

if [ $# -eq 0 ]; then
  echo "This script installs or uninstalls the esp-idf toolchain and its dependencies in the specified directory."
  echo "Usage for installation:"
  echo "   ./installToolchain.sh install /path/to/installation/directory [version] [keep]"
  echo "Usage for uninstallation:"
  echo "   ./installToolchain.sh uninstall /path/to/installation/directory"
  echo "Usage for downloading the ZIP file:"
  echo "   ./installToolchain.sh download /download/path [version]"
else
  if [ "$1" == "install" ]; then
    if [ $# -eq 1 ]; then
      echo "Usage for installation:"
      echo "   ./installToolchain.sh install /path/to/installation/directory [version] [keep]"
      exit 1
    fi

    # Check if each package is installed and install it if not
    sudo apt update
    for package in "${packages[@]}"; do
      if ! dpkg -s "$package" &> /dev/null; then
        echo "$package is not installed. Installing $package..."
        sudo apt-get install -y "$package"
        if [ $? -ne 0 ]; then
          echo "Failed to install $package. Aborting..."
          exit 1
        fi
      fi
    done

    # If all packages have been checked, continue with the installation
    directory="$2"
    if [ ! -d "$directory" ]; then
      mkdir -p "$directory"
      echo "Directory $directory has been created successfully."
    else
      echo "Directory $directory already exists."
    fi

    # Change to the installation directory
    cd "$directory" || exit

    # Check if a custom version is specified, otherwise use version 5.1.1
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

    # Generate the esp-idf download link
    download_link="https://github.com/espressif/esp-idf/releases/download/v$version/esp-idf-v$version.zip"

    # Check if the esp-idf ZIP file is already downloaded
    if [ ! -d "esp-idf" ]; then
      if [ ! -f "esp-idf-v$version.zip" ]; then
        wget "$download_link" -O "esp-idf-v$version.zip"
      fi

      # Verify if the downloaded ZIP file is valid using the "zip" command
      if zip -T "esp-idf-v$version.zip" >/dev/null; then
        unzip "esp-idf-v$version.zip"
        mv "esp-idf-v$version" esp-idf
        if [ "$keep" = false ]; then
          rm "esp-idf-v$version.zip"
        fi
      else
        echo "The downloaded ZIP file is not valid. Downloading again."
        rm -f "esp-idf-v$version.zip"
        wget "$download_link" -O "esp-idf-v$version.zip"
        unzip "esp-idf-v$version.zip"
        mv "esp-idf-v$version" esp-idf
        if [ "$keep" = false ]; then
          rm "esp-idf-v$version.zip"
        fi
      fi
    else
      echo "The esp-idf file is already downloaded."
    fi

    # Change to the esp-idf directory
    cd "esp-idf" || exit

    # Install the toolchain
    ./install.sh esp32
    
    # Give Serial port access to the user
    sudo usermod -a -G dialout $USER || exit

    cd "$oldDir" || exit
    pwd
    echo "Press Enter to continue"
    read
    . $directory/esp-idf/export.sh
    echo "Copy the modified PATH now and press Enter to continue"
    echo $PATH
    read
    clear
    less nextSteps.txt
  elif [ "$1" == "uninstall" ]; then
    if [ $# -eq 1 ]; then
      echo "This command will uninstall the esp-idf toolchain and remove the '.espressif' folder in the user's home directory."
      echo "Usage for uninstallation:"
      echo "   ./installToolchain.sh uninstall /path/to/installation/directory"
    else
      directory="$2"
      # Remove the "esp-idf" folder in the installation directory
      if [ -d "$directory/esp-idf" ]; then
        echo "Uninstalling esp-idf libraries..."
        rm -rf "$directory/esp-idf"
        echo "The esp-idf libraries in the directory $directory have been removed."
      else
        echo "No esp-idf libraries found in $directory."
      fi

      # Remove the ".espressif" folder in the user's home directory
      if [ -d "$HOME/.espressif" ]; then
        echo "Removing the esp-idf toolchain installation in the '.espressif' folder in the user's home directory..."
        rm -rf "$HOME/.espressif"
        echo "The esp-idf toolchain installation in the '.espressif' folder has been removed."
      else
        echo "No esp-idf toolchain installation found in the '.espressif' folder in the user's home directory."
      fi
    fi
  elif [ "$1" == "download" ]; then
    if [ $# -lt 2 ]; then
      echo "Usage for downloading the ZIP file:"
      echo "   ./installToolchain.sh download /download/path [version]"
      exit 1
    fi

    # Check if a custom version is specified, otherwise use version 5.1.1
    if [ $# -ge 3 ]; then
      version="$3"
    else
      version="5.1.1"
    fi

    # Custom download path
    download_dir="$2"

    # Check if the download path exists, otherwise create it
    if [ ! -d "$download_dir" ]; then
      mkdir -p "$download_dir"
      echo "Download directory $download_dir has been created successfully."
    fi

    # Change to the download directory
    cd "$download_dir" || exit

    # Generate the esp-idf download link
    download_link="https://github.com/espressif/esp-idf/releases/download/v$version/esp-idf-v$version.zip"
    
    echo Downloading toolchain from $download_link

    # Check if the esp-idf ZIP file is already downloaded
    if [ ! -f "esp-idf-v$version.zip" ]; then
      wget "$download_link" -O "esp-idf-v$version.zip"
    else
      echo "The esp-idf file is already downloaded."
    fi
  else
    echo "Invalid option. Use 'install' to install esp-idf, 'uninstall' to uninstall, or 'download' to download the ZIP file."
  fi
fi
