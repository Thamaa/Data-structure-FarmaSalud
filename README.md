
# FarmaSalud - Sistema de Gestión de Farmacia

Este proyecto es un sistema de gestión para una cadena de farmacias, diseñado en C. El código utiliza estructuras de datos para manejar inventarios de productos, órdenes de compra, proveedores y ventas.

## Estructuras principales

El sistema se basa en las siguientes estructuras:

- **FarmaSalud**: Representa la cadena de farmacias. Contiene un nombre, un RUT, y listas de farmacias y proveedores asociados.
- **Farmacia**: Representa una farmacia individual. Contiene información como el nombre, dirección, inventario y ventas.
- **Inventario**: Gestiona el inventario de productos dentro de una farmacia. Los productos incluyen información como nombre, descripción, categoría, fecha de vencimiento, precio y stock.
- **Producto**: Contiene detalles de un producto, como su código, nombre, descripción, categoría y si requiere receta médica.
- **Proveedor**: Representa los proveedores que abastecen a las farmacias.

## Requisitos del sistema

Este código está diseñado para ser ejecutado en **C**, cumpliendo con las siguientes restricciones:

- Solo se pueden utilizar las librerías estándar `stdlib.h`, `stdio.h`, y `string.h`.
- No se permiten las instrucciones `switch`, `break`, `typedef`, `default`, ni `case`.

## Estructura del proyecto

El código principal define las estructuras y contiene funciones básicas para gestionar los datos de las farmacias, como agregar productos, gestionar el inventario y registrar ventas.

## Compilación y ejecución

Para compilar y ejecutar el código en un entorno compatible con Turbo C, sigue los siguientes pasos:

1. Abre Tu compilador y carga el archivo `Codigo Estructura Datos FarmaSalud.c`.
2. Compila el código
3. Ejecuta el programa
