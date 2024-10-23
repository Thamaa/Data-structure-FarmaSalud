
# FarmaSalud - Sistema de Gestión de Farmacia

Este proyecto es un sistema de gestión para una cadena de farmacias, diseñado en C. El código utiliza estructuras de datos para manejar inventarios de productos, órdenes de compra, proveedores y ventas.

## Estructuras principales

El sistema se basa en las siguientes estructuras:

- **FarmaSalud**: Representa la cadena de farmacias. Contiene un nombre, un RUT, y listas de farmacias y proveedores asociados.
- **Farmacia**: Representa una farmacia individual. Contiene información como el nombre, dirección, inventario y ventas.
- **Inventario**: Gestiona el inventario de productos dentro de una farmacia. Los productos incluyen información como nombre, descripción, categoría, fecha de vencimiento, precio y stock.
- **Producto**: Contiene detalles de un producto, como su código, nombre, descripción, categoría y si requiere receta médica.
- **Proveedor**: (Pendiente de ser desarrollado en el código) Representa los proveedores que abastecen a las farmacias.

## Requisitos del sistema

Este código está diseñado para ser ejecutado en **Turbo C**, cumpliendo con las siguientes restricciones:

- Solo se pueden utilizar las librerías estándar `stdlib.h`, `stdio.h`, y `string.h`.
- No se permiten las instrucciones `switch`, `break`, `typedef`, `default`, ni `case`.

## Estructura del proyecto

El código principal define las estructuras y contiene funciones básicas para gestionar los datos de las farmacias, como agregar productos, gestionar el inventario y registrar ventas.

## Compilación y ejecución

Para compilar y ejecutar el código en un entorno compatible con Turbo C, sigue los siguientes pasos:

1. Abre Turbo C y carga el archivo `Codigo Estructura Datos FarmaSalud.c`.
2. Compila el código (Ctrl + F9).
3. Ejecuta el programa (Ctrl + F10).

## Contribuciones

Las contribuciones son bienvenidas. Si deseas contribuir a este proyecto, por favor sigue estos pasos:

1. Haz un fork de este repositorio.
2. Crea una rama (`git checkout -b feature-nueva-funcionalidad`).
3. Haz tus cambios y realiza un commit (`git commit -m 'Agregar nueva funcionalidad'`).
4. Sube tus cambios (`git push origin feature-nueva-funcionalidad`).
5. Abre un Pull Request.

## Licencia

Este proyecto está bajo la Licencia MIT - mira el archivo [LICENSE](LICENSE) para más detalles.
