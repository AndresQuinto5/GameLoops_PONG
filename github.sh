#!/bin/sh

if [ -z "$1" ]; then
  echo "Error: No commit message provided."
  exit 1
fi

git add *
git commit -m "$1"

# Preguntar al usuario si desea hacer un push
read -p "¿Deseas hacer un push al repositorio remoto? (s/n): " respuesta

case $respuesta in
  [sS]|[yY])
    git push origin master
    ;;
  *)
    echo "Operación de push cancelada."
    ;;
esac
