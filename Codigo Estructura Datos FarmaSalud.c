#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10000
#define tamRut 14
#define tamNombre 50
#define tamDireccion 50
#define tamTelefono 12 
#define tamEmail 50
#define tamCategoria 50
#define tamDescripcion 500



struct FarmaSalud
{
  char *nombre;
  char *rut;
  struct NodoFarmacia *farmacias;
  struct NodoProveedores *proveedores;
};

struct NodoFarmacia
{
  struct Farmacia *datosFarmacia;
  struct NodoFarmacia *sig, *ant;
};

struct Farmacia
{
  int idFarmacia;
  char *nombre;
  char *direccion;
  struct Inventario *inventario;
  struct NodoOrdenDeCompra *ordenDeCompra;
  struct NodoVenta *ventas;             
};

struct Inventario
{
  struct Producto *arregloProductos[TAM];
  int pLibre;
};

struct Producto
{
  int codigo;  //debe de tener 10 digitos
  char *nombre;
  char *descripcion;
  char *categoria;
  int anio;// { 
  int mes;  // {  Fecha de vencimiento
  int dia;  // {
  float precio;
  int requiereReceta; // (0) No, (1) Si
  int cantidadStock; //en la Farmacia;
};

struct NodoOrdenDeCompra
{
  struct OrdenDeCompra *datosOrdenDeCompra;
  struct NodoOrdenDeCompra *sig;
};

struct OrdenDeCompra
{
  int idCompra;
  int anio;
  int mes;
  int dia;
  int cantidadProductos;
  struct Producto *productos; //Accedo a los productos para saber que producto voy a comprar. 
  struct Proveedor *proveedor;
};

struct NodoVenta
{
  struct Venta *datosVenta;
  struct NodoVenta *sig; 
};

struct Venta
{
  int idVenta;
  char *rutCliente;
  int anio;
  int mes;
  int dia;
  float precioFinal;
  struct NodoVentaProducto *productosVendidos;
};

struct NodoVentaProducto{
  struct VentaProducto *datosVentaProducto;
  struct NodoVentaProducto *sig,*ant;
};

struct VentaProducto{
  int idVentaProducto;
  int cantidad;
  struct Producto *producto;
};


struct NodoProveedores
{
  struct Proveedor *datosProveedor;
  struct NodoProveedores *sig;
};

struct Proveedor
{
  int idProveedor;
  char *nombre;
  char *direccion;
  char *correo;
  char *telefono;
  struct NodoLote *lotesEncargados;
};

struct NodoLote
{
  struct Lote *datosLote;
  struct NodoLote *izq, *der;
};

struct Lote
{
  int idLote;
  int cantidad;
  int anio;
  int mes;
  int dia;
  int estado;//0 si esta en proceso de creacion, 1 si se esta enviando, 2 se ha recibido.
  int idFarmacia;//a que farmacia pertenece el lote.
  struct Producto *producto;

};


void menuAdmin(struct FarmaSalud *farmasalud);
void menuPrincipal(struct FarmaSalud *farmasalud);
void menuProveedor(struct FarmaSalud *farmasalud,struct Proveedor *proveedor);
void menuFarmacia(struct FarmaSalud *farmasalud);
void menuProveedores(struct FarmaSalud *farmasalud);

// 0. Inicalizar inventario
struct Inventario *inicializarInventario() 
{
    struct Inventario *inventario = (struct Inventario *)malloc(sizeof(struct Inventario));
    inventario->pLibre = 0;
    return inventario;
}

// 1. Funciones para Crear 

//1.0 CrearFarmaSalud
struct FarmaSalud* crearFarmaSalud(char *nombre, char *rut) {
    struct FarmaSalud *farmasalud = (struct FarmaSalud *)malloc(sizeof(struct FarmaSalud));

    farmasalud->nombre = nombre;
    farmasalud->rut = rut;
    farmasalud->proveedores = NULL;
    farmasalud->farmacias = NULL;
    return farmasalud;
}

// 1.1 Crear Farmacia
struct Farmacia *crearFarmacia(int idFarmacia, char *nombre, char *direccion)
{
  struct Farmacia *nuevaFarmacia = (struct Farmacia *)malloc(sizeof(struct Farmacia));
  nuevaFarmacia->idFarmacia = idFarmacia;
  nuevaFarmacia->nombre = nombre;
  nuevaFarmacia->direccion = direccion;
  nuevaFarmacia->inventario = NULL;
  nuevaFarmacia->ordenDeCompra = NULL;
  nuevaFarmacia->ventas = NULL;
  return nuevaFarmacia;
}

// 1.2 Crear Productos
struct Producto *crearProducto(int codigo, char *nombre, char *descripcion, char *categoria, int dia, int mes, int anio, float precio, int requiereReceta, int cantidadStock)
{
  struct Producto *producto = (struct Producto *) malloc(sizeof(struct Producto));

  producto->codigo = codigo;
  producto->nombre = nombre;
  producto->descripcion = descripcion;
  producto->categoria = categoria;
  producto->dia = dia;
  producto->mes = mes;
  producto->anio = anio;
  producto->precio = precio;
  producto->requiereReceta = requiereReceta;
  producto->cantidadStock = cantidadStock;

  return producto;
}

// 1.3 Crear Orden de Compra
struct OrdenDeCompra *crearOrdenDeCompra(int id, int anio, int month, int day, int totalProductos, struct Producto *producto, struct Proveedor *proveedor)
{
  struct OrdenDeCompra *nuevaOrden = (struct OrdenDeCompra *) malloc(sizeof(struct OrdenDeCompra));

  nuevaOrden->idCompra = id;
  nuevaOrden->anio = anio;
  nuevaOrden->mes = month;
  nuevaOrden->dia = day;
  nuevaOrden->cantidadProductos = totalProductos;
  nuevaOrden->productos = producto; 
  nuevaOrden->proveedor = proveedor;

  return nuevaOrden;
}

// 1.4 Crear Venta producto
struct VentaProducto *crearVentaProducto(int idVentaProducto, int cantidad, struct Producto *producto)
{
  struct VentaProducto *nuevoVentaProducto = (struct VentaProducto *) malloc(sizeof(struct VentaProducto));
  nuevoVentaProducto->idVentaProducto = idVentaProducto;
  nuevoVentaProducto->cantidad = cantidad;
  nuevoVentaProducto->producto = producto;
  return nuevoVentaProducto;
}

// 1.5 Crear Venta
struct Venta *crearVenta(int id, char *rut, int anio, int month, int day, float finalPrice)
{
  struct Venta *nuevaVenta = (struct Venta *) malloc(sizeof(struct Venta));
  nuevaVenta->idVenta = id;
  nuevaVenta->rutCliente = rut;
  nuevaVenta->anio = anio;
  nuevaVenta->mes = month;
  nuevaVenta->dia = day;
  nuevaVenta->precioFinal = finalPrice;
  nuevaVenta->productosVendidos = NULL;

  return nuevaVenta;
}

// 1.6 Crear Proveedor
struct Proveedor *crearProveedor(int idProveedor, char *nombre, char *direccion, char *correo, char *telefono)
{
    struct Proveedor* nuevoProveedor = (struct Proveedor*)malloc(sizeof(struct Proveedor));
    nuevoProveedor->idProveedor = idProveedor;
    nuevoProveedor->nombre = nombre;
    nuevoProveedor->direccion = direccion;
    nuevoProveedor->telefono = telefono;
    nuevoProveedor->correo = correo;
    nuevoProveedor->lotesEncargados = NULL;

    return nuevoProveedor;
}

// 1.7 Crear Lote
struct Lote *crearLote(int idLote, int cantidad, int anio, int mes, int dia,int idFarmacia, struct Producto* producto) 
{
    struct Lote* nuevoLote = (struct Lote*)malloc(sizeof(struct Lote));
    nuevoLote->idLote = idLote;
    nuevoLote->cantidad = cantidad;
    nuevoLote->anio = anio;
    nuevoLote->mes = mes;
    nuevoLote->dia = dia;
    nuevoLote->estado = 0;
    nuevoLote->idFarmacia=idFarmacia;
    nuevoLote->producto = producto;
    return nuevoLote;
}


//2. Funciones para Agregar
int agregarFarmacia(struct NodoFarmacia **head, struct Farmacia *nuevaFarmacia)
{
  struct NodoFarmacia *rec;
  if(*head == NULL)
  {
    (*head) = (struct NodoFarmacia *)malloc(sizeof(struct NodoFarmacia));
    (*head)->datosFarmacia = nuevaFarmacia;
    (*head)->ant = NULL;
    (*head)->sig = NULL;
    return 1;
  }
  else
  {
    rec = (*head);
    while (rec->sig != NULL)
    {
      rec = rec->sig;
    }
    rec->sig = (struct NodoFarmacia *)malloc(sizeof(struct NodoFarmacia));
    rec->sig->datosFarmacia = nuevaFarmacia;
    rec->sig->ant = rec;
    rec->sig->sig = NULL;
    return 1;
  }
}

// 2.2 Agregar Producto
int agregarProductoAlArreglo(struct Lote *loteProducto, struct Inventario *inventario)
{
  int i;
  int cantidadProductos = loteProducto->cantidad;
  struct Producto *nuevoProducto = loteProducto->producto;
  if (inventario->pLibre + cantidadProductos < TAM)
  {
    for (i = 0; i< cantidadProductos; i++)
    {
      //Quiero llenar este arreglo con TODOS LOS PRODUCTOS DEL LOTE
      inventario->arregloProductos[inventario->pLibre] = nuevoProducto;
      inventario->pLibre++;

    }
    nuevoProducto->cantidadStock += cantidadProductos;
    return 1; 
  }
  return 0;
}

/* 2.3 Agregar Orden de Compra
int agregarOrdenDeCompra(struct NodoOrdenDeCompra **head, struct OrdenDeCompra *nuevaOrden)
{
  struct NodoOrdenDeCompra *rec;
  if(*head==NULL)
  {
    (*head)=(struct NodoOrdenDeCompra *) malloc(sizeof(struct NodoOrdenDeCompra));
    (*head)->datosOrdenDeCompra=nuevaOrden;
    (*head)->sig=NULL;
    return 1;
  }
  else
  {
    rec=(*head);
    while(rec->sig!=NULL)
    {
      rec=rec->sig;
    }
    rec->sig=(struct NodoOrdenDeCompra *) malloc(sizeof(struct NodoOrdenDeCompra));
    rec->sig->datosOrdenDeCompra=nuevaOrden;
    rec->sig->sig=NULL;
    return 1;
  }
  return 0;
}


//2.4 Agregar OrdenDeCompraAFarmacia
void asignarOrdenDeCompraAFarmacia(struct NodoFarmacia *listaFarmacias, int idFarmacia, struct OrdenDeCompra *nuevaOrden) 
{
    struct NodoFarmacia *actual = listaFarmacias;
    while (actual != NULL) {
        if (actual->datosFarmacia->idFarmacia == idFarmacia) {
            agregarOrdenDeCompra(&actual->datosFarmacia->ordenDeCompra, nuevaOrden);
            return;
        }
        actual = actual->sig;
    }
}

*/

int agregarVenta(struct NodoVenta **head, struct Venta *nuevaVenta)
{
  struct NodoVenta *rec;
  if(*head==NULL)
  {
    (*head)=(struct NodoVenta *)malloc(sizeof (struct NodoVenta));
    (*head)->datosVenta=nuevaVenta;
    (*head)->sig=NULL;
    return 1;
  }
  else if(*head != NULL)
  {
    rec=(*head);
    while(rec->sig!=NULL)
    {
      rec=rec->sig;
    }
    rec->sig=(struct NodoVenta *) malloc(sizeof(struct NodoVenta));
    rec->sig->datosVenta=nuevaVenta;
    rec->sig->sig=NULL;
    return 1;
  }
  return 0;
}

// 2.6 Agregar Venta Producto
int agregarVentaProducto(struct NodoVentaProducto **lista, struct VentaProducto *nuevo)
{
  struct NodoVentaProducto *rec;
  if(*lista==NULL)
  {
    *lista=(struct NodoVentaProducto *)malloc(sizeof (struct NodoVentaProducto));
    (*lista)->datosVentaProducto=nuevo;
    (*lista)->sig=NULL;
    return 1;
  }
  else if(*lista != NULL)//cambie de else a else if
  {
    rec=(*lista);
    while(rec->sig!=NULL)
    {
      rec=rec->sig;
    }
    rec->sig=((struct NodoVentaProducto *) malloc(sizeof(struct NodoVentaProducto)));
    rec->sig->datosVentaProducto=nuevo;
    rec->sig->sig=NULL;
    return 1;
  }
  return 0;
}

//2.7 Agregar VentaProducto a Venta
void agregarProductoAVenta(struct Venta *venta, struct Producto *producto, int cantidad, int idVentaProducto) {
    struct VentaProducto *nuevoVentaProducto = crearVentaProducto(idVentaProducto, cantidad, producto);
    agregarVentaProducto(&(venta->productosVendidos), nuevoVentaProducto);
}

// 2.8 Agregar Proveedores
int agregarProveedor(struct NodoProveedores **lista, struct Proveedor *nuevo)
{
    struct NodoProveedores *rec;
    /*Caso 1: lista esta vacia*/
    if(*lista==NULL)
    {
        *lista=(struct NodoProveedores *) malloc(sizeof (struct NodoProveedores));
        (*lista)->datosProveedor=nuevo;
        (*lista)->sig=NULL;

        return 1;
    }
    else
    {
      rec=(*lista);
      while(rec->sig!=NULL)
      {
          rec=rec->sig;
      }
      rec->sig=(struct NodoProveedores *) malloc(sizeof(struct NodoProveedores));
      rec->sig->datosProveedor=nuevo;
      rec->sig->sig=NULL;

      return 1;
    }
}

// 2.9 Agregar Lote
void agregarLote(struct NodoLote **abb, struct Lote *nuevo)
{
    if((*abb)==NULL)
    {
        (*abb)=(struct NodoLote *)malloc(sizeof(struct NodoLote));
        (*abb)->datosLote=nuevo;
        (*abb)->izq=(*abb)->der=NULL;
    }
    else
    {
      if(((*abb)->datosLote->idLote) > nuevo->idLote)
          agregarLote(&((*abb)->izq),nuevo);
      else
           agregarLote(&((*abb)->der),nuevo);
    }
}

// 2.10 Agregar Lote a Proveedor
void agregarLoteAProveedor(struct NodoProveedores *listaProveedores, int idProveedor, struct Lote *nuevoLote) 
{
    struct NodoProveedores *actual = listaProveedores;
    while (actual != NULL) {
        if (actual->datosProveedor->idProveedor == idProveedor) {
            agregarLote(&(actual->datosProveedor->lotesEncargados), nuevoLote);
            return;
        }
        actual = actual->sig;
    }
}


///3. Funciones para Buscar

//3.1 Buscar Farmacia
struct Farmacia *buscarFarmacia(struct NodoFarmacia *cabeza, int idFarmacia)
{
  struct NodoFarmacia *actual = cabeza;
  while (actual != NULL)
  {
    if (actual->datosFarmacia->idFarmacia == idFarmacia)
    {
      return actual->datosFarmacia;
    }
    actual = actual->sig;
  }
  return NULL;
}

//3.2 Buscar Producto
struct Producto *buscarProducto(struct Inventario *inventario, int codigoBuscado)
{
  int i; 
  for(i=0; i<inventario->pLibre; i++)
  { // no es necesario revisar si son nulls las celdas
    //del arreglo, ya que hacemos uso de pLibre
    if(inventario->arregloProductos[i]->codigo == codigoBuscado)
      return inventario->arregloProductos[i];
  }
  return NULL;
}

//3.3 Buscar Producto por proveedor
struct Producto *buscarProductoProv(struct NodoFarmacia *farmacias, int codigoBuscado)
{
  struct Inventario *inventario;
  struct NodoFarmacia *recF = farmacias;
  struct Producto *producto;


  while (recF != NULL){ 
    inventario = farmacias->datosFarmacia->inventario;
    producto = buscarProducto(inventario,codigoBuscado);
    if (producto) return producto;
  }  
  return NULL;
}

//3.4 Buscar Orden de Compra
int buscarOrdenDeCompra(struct NodoOrdenDeCompra *head, int idCompraBuscada)
{
  struct NodoOrdenDeCompra *rec=head;
  while(rec!=NULL)
  {
    if(rec->datosOrdenDeCompra->idCompra == idCompraBuscada)
    {
      return 1;
    }
    rec=rec->sig;
  }
  return 0;
}

//3.5 Buscar Venta
int buscarVenta(struct NodoVenta *head, int idVentaBuscado)
{
  struct NodoVenta *rec = head;
  while (rec != NULL)
  {
    if (rec->datosVenta->idVenta == idVentaBuscado)
    {
      return 1;
    }
    rec = rec->sig;
  }
  return 0;
}

// 3.6 Buscar Venta Producto
int buscarVentaProducto(struct NodoVentaProducto *head, int idVentaBuscado)
{
  struct NodoVentaProducto *rec = head;
  while (rec != NULL)
  {
    if (rec->datosVentaProducto->idVentaProducto == idVentaBuscado)
    {
      return 1;
    }
    rec = rec->sig;
  }
  return 0;
}

//3.7 Buscar Proveedor
struct Proveedor *buscarProveedor(struct NodoProveedores *cabeza, int idProveedor)
{
    struct NodoProveedores *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->datosProveedor->idProveedor == idProveedor)
            return actual->datosProveedor;
        actual = actual->sig;
    }
    return NULL;
}

//3.8 Buscar Lote
struct NodoLote* buscarLote(struct NodoLote *raiz, int idLote) 
{
    if (raiz == NULL || raiz->datosLote->idLote == idLote) 
      return raiz;
    if (idLote < raiz->datosLote->idLote) 
      return buscarLote(raiz->izq, idLote); 
    else 
      return buscarLote(raiz->der, idLote);
}


///4. Funciones para contar

//4.1 Contar Productos
int contarProductosTotales(struct Inventario *inventario)
{
  return inventario->pLibre;
}

// 5. Funciones para Eliminar

// 5.1 Eliminar Farmacia
int eliminarFarmacia(struct NodoFarmacia **head, int idFarmacia)
{
  struct NodoFarmacia *rec;
  if(*head != NULL)
  {
    if((*head)->datosFarmacia->idFarmacia == idFarmacia)
    {
      if((*head)->sig != NULL)
      {
        (*head)->sig->ant = NULL;
      }
      *head = (*head)->sig;
      return 1;
    }
    rec = (*head)->sig;
    while(rec != NULL)
    {
      if(rec->datosFarmacia->idFarmacia == idFarmacia)
      {
        if(rec->sig != NULL)
        {
          rec->sig->ant = rec->ant;
        }
        rec->ant->sig = rec->sig;
        return 1;
      }
      rec = rec->sig;
    }
  }
  return 0;
}


// 5.2 Eliminar Producto
int eliminarProductoDelArreglo(struct Producto *productoAEliminar, struct Inventario *inventario, int cantidadAEliminar) 
{
  int i, j;
  int cantidadEliminada = 0;

  for (i = 0; i < inventario->pLibre && cantidadEliminada < cantidadAEliminar; i++) 
  {
    if (inventario->arregloProductos[i] == productoAEliminar) 
    {
      // Mover todos los elementos hacia la izquierda para llenar el hueco
      for (j = i; j < inventario->pLibre ; j++) 
      {
        inventario->arregloProductos[j] = inventario->arregloProductos[j + 1];
      }
      inventario->pLibre--;
      cantidadEliminada++;
      i--; // Para verificar la nueva posicion de i
    }
  }
  if (cantidadEliminada == cantidadAEliminar) 
  {
    productoAEliminar->cantidadStock -= cantidadEliminada;
    return 1;
  }
  return 0;
}

// 5.3 Eliminar Orden de Compra
int eliminarOrdenDeCompra(struct NodoOrdenDeCompra **head, int idCompraBuscada) 
{
  struct NodoOrdenDeCompra *rec = *head;
  struct NodoOrdenDeCompra *ant = NULL;

  if(rec!=NULL) 
  {
    if(rec->datosOrdenDeCompra->idCompra == idCompraBuscada) 
    {
      (*head)=rec->sig;
      return 1; 
    }

    while(rec!=NULL) 
    {
      if(rec->datosOrdenDeCompra->idCompra == idCompraBuscada) 
      {
        ant->sig=rec->sig;
        return 1; 
      }
      ant=rec;
      rec=rec->sig;
    }
  }
  return 0; 
}

// 5.4 Eliminar Venta
int eliminarVenta(struct NodoVenta **head, int idVentaBuscado) 
{
  struct NodoVenta *rec = *head;
  struct NodoVenta *ant = NULL;

  if(rec != NULL) 
  {
    if(rec->datosVenta->idVenta == idVentaBuscado) 
    {
      (*head) = rec->sig;
      return 1; 
    }

    while(rec!=NULL) 
    {
      if(rec->datosVenta->idVenta == idVentaBuscado) 
      {
        ant->sig = rec->sig;
        return 1; 
      }
      ant = rec;
      rec = rec->sig;
    }
  }
  return 0; 
}

// 5.5 Eliminar VentaProducto
int eliminarVentaProducto(struct NodoVentaProducto **head, int idVentaBuscado) 
{
  struct NodoVentaProducto *rec = *head;
  struct NodoVentaProducto *ant = NULL;

  if(rec != NULL) 
  {
    if(rec->datosVentaProducto->idVentaProducto == idVentaBuscado) 
    {
      (*head) = rec->sig;
      return 1; 
    }

    while(rec!=NULL) 
    {
      if(rec->datosVentaProducto->idVentaProducto == idVentaBuscado) 
      {
        ant->sig = rec->sig;
        return 1; 
      }
      ant = rec;
      rec = rec->sig;
    }
  }
  return 0; 
}

// 5.6 Eliminar Proveedor
int eliminarProveedor(struct NodoProveedores **cabeza, int idProveedor) 
{
    struct NodoProveedores *actual = *cabeza;
    struct NodoProveedores *anterior = NULL;

    // Verificar si la lista no esta vacia
    if (actual != NULL) 
    {
        // Si el proveedor a eliminar es el primero de la lista
        if (actual->datosProveedor->idProveedor == idProveedor) 
        {
            (*cabeza) = actual->sig;
            return 1; // Proveedor eliminado exitosamente
        }

        // Recorrer la lista para encontrar el proveedor a eliminar
        while (actual != NULL) 
        {
            if (actual->datosProveedor->idProveedor == idProveedor) 
            {
                anterior->sig = actual->sig;
                return 1; // Proveedor eliminado exitosamente
            }
            anterior = actual;
            actual = actual->sig;
        }
    }
    return 0; // Proveedor no encontrado
}

// 5.7 Eliminar Lote
// (son 2 Reemplazar y elmiminar)

void reemplazarLote(struct NodoLote **abb, struct NodoLote **aux)
{
  if(!((*abb)->der))
  {
    (*aux)->datosLote=(*abb)->datosLote;
    *aux= *abb;
    *abb = (*abb)->izq;
  }
  else
    reemplazarLote(&(*abb)->der, &(*aux));
}


void eliminarLote(struct NodoLote **abb, int idLote)
{
  struct NodoLote *aux = NULL;

  if (!(*abb))
      return;

  if ((*abb)->datosLote->idLote < idLote)
  {
    eliminarLote(&(*abb)->der, idLote);
  }
  else
  {
    if ((*abb)->datosLote->idLote > idLote)
    {
      eliminarLote(&(*abb)->izq, idLote);
    }
    else
    {
      if ((*abb)->datosLote->idLote == idLote)
      {
        aux = *abb;
        if(!((*abb)->izq))
        {
          *abb = (*abb)->der;
        }
        else
        {
          if (!((*abb)->der))
          {
            *abb = (*abb)->izq;
          }
          else
          {
            reemplazarLote(&(*abb)->izq, &aux);
          }
        }
      }
    }
  }
}


// 6. Funciones Modificar

// 6.1 Modificar Farmacia
int modificarFarmacia(struct NodoFarmacia *cabeza, int idFarmacia, char *nuevoNombre, char *nuevaDireccion)
{
  struct NodoFarmacia *nodo = cabeza;
  while(nodo != NULL && nodo->datosFarmacia->idFarmacia != idFarmacia)
  {
    nodo = nodo->sig;
  }
  if(nodo != NULL)
  {
    nodo->datosFarmacia->nombre = nuevoNombre;
    nodo->datosFarmacia->direccion = nuevaDireccion;
    return 1;
  }
  return 0;
}

// 6.2 Modificar Producto
int modificarProducto(struct Inventario *inventario, int codigo, char *nombre, char *descripcion, char *categoria, int anio, int mes, int dia, float precio, int requiereReceta)
{
  struct Producto *productoBuscado = buscarProducto(inventario, codigo);
  if (productoBuscado == NULL)
    return 0;
  else
  {
  productoBuscado->codigo = codigo;
  productoBuscado->nombre = nombre;
  productoBuscado->descripcion = descripcion;
  productoBuscado->categoria = categoria;
  productoBuscado->anio = anio;
  productoBuscado->mes = mes;
  productoBuscado->dia = dia;
  productoBuscado->precio = precio;
  productoBuscado->requiereReceta = requiereReceta;
  return 1;
  }
}

// 6.3 Modificar Orden de Compra
void modificarOrden(struct NodoOrdenDeCompra *head, int idOrdenNuevo, int anio, int month, int day, int totalProductos)
{
  struct NodoOrdenDeCompra *rec=head;
  while(rec!=NULL && rec->datosOrdenDeCompra->idCompra != idOrdenNuevo)
  {
    rec = rec->sig;
  }
  if(rec!=NULL)
  {
    rec->datosOrdenDeCompra->idCompra = idOrdenNuevo;
    rec->datosOrdenDeCompra->anio = anio;
    rec->datosOrdenDeCompra->mes = month;
    rec->datosOrdenDeCompra->dia = day;
    rec->datosOrdenDeCompra->cantidadProductos = totalProductos;
  }
}

// 6.4 Modificar Venta
void modificarVenta(struct NodoVenta *head, int idVentaNueva, char *rut, int anio, int month, int day, float finalPrice)
{
  struct NodoVenta *rec = head;
  while (rec!=NULL && rec->datosVenta->idVenta != idVentaNueva)
  {
    rec = rec->sig;
  }
  if(rec!=NULL)
  {
    rec->datosVenta->idVenta = idVentaNueva;
    rec->datosVenta->rutCliente = rut;
    rec->datosVenta->anio = anio;
    rec->datosVenta->mes = month;
    rec->datosVenta->dia = day;
    rec->datosVenta->precioFinal = finalPrice;
  }
}

// 6.5 Modificar Proveedor
int modificarProveedor(struct NodoProveedores *cabeza, int idProveedor, char *nuevoNombre, char *nuevaDireccion, char *nuevoCorreo, char *nuevoTelefono)
{
  struct NodoProveedores *nodo = cabeza;
  while (nodo != NULL && nodo->datosProveedor->idProveedor != idProveedor)
    nodo = nodo->sig;

  if(nodo != NULL)
  {
    nodo->datosProveedor->nombre = nuevoNombre;
    nodo->datosProveedor->direccion = nuevaDireccion;
    nodo->datosProveedor->correo = nuevoCorreo;
    nodo->datosProveedor->telefono = nuevoTelefono;
    return 1;
  }
  return 0;
}

//6.6 Modificar Lote
int modificarLote(struct NodoLote* raiz, int idLote, int nuevaCantidad, int nuevoAnio, int nuevoMes, int nuevoDia) 
{
    struct NodoLote *nodoLote;
    nodoLote = buscarLote(raiz, idLote);
    if (nodoLote != NULL) 
    {
        nodoLote->datosLote->cantidad = nuevaCantidad;
        nodoLote->datosLote->anio = nuevoAnio;
        nodoLote->datosLote->mes = nuevoMes;
        nodoLote->datosLote->dia = nuevoDia;
        return 1;
    }
    return 0;
}

//6.7 Modificar EstadoLote
int modificarEstadoLote(struct NodoLote* raiz, int idLote, int nuevoEstado)
{
    struct NodoLote *nodoLote;
    nodoLote = buscarLote(raiz, idLote);
    if (nodoLote != NULL){
        nodoLote->datosLote->estado = nuevoEstado;
        return 1;
    }
  return 0;
}

/// 7. Funciones para Mostrar

// 7.1 Mostrar Farmacia
void mostrarFarmacias(struct NodoFarmacia *cabeza)
{
    struct NodoFarmacia *actual = cabeza;
    while (actual != NULL)
    {
      printf("ID Farmacia: %d, Nombre: %s, Direccion: %s\n",
            actual->datosFarmacia->idFarmacia,
            actual->datosFarmacia->nombre,
            actual->datosFarmacia->direccion);
      actual = actual->sig;
    }
}

// 7.2 Mostrar Proveedor
void mostrarProveedores(struct NodoProveedores *cabeza)
{
    struct NodoProveedores *actual = cabeza;
    while (actual != NULL)
    {
      printf("ID Proveedor: %d, Nombre: %s, Direccion: %s, Correo: %s, Telefono: %s\n",
            actual->datosProveedor->idProveedor,
            actual->datosProveedor->nombre,
            actual->datosProveedor->direccion,
            actual->datosProveedor->correo,
            actual->datosProveedor->telefono);
      actual = actual->sig;
    }
}

// 7.3 Mostrar Lotes
void mostrarLotes(struct NodoLote* nodo) 
{ //busqueda preorden
  if (nodo != NULL) 
  {
      mostrarLotes(nodo->izq);
      printf("Nombre del producto: %s, ID Lote: %d, Cantidad: %d, Fecha de caducidad: %d-%d-%d, ",
        nodo->datosLote->producto->nombre, nodo->datosLote->idLote, nodo->datosLote->cantidad, nodo->datosLote->anio, nodo->datosLote->mes, nodo->datosLote->dia);
      switch(nodo->datosLote->estado){
        case 0:
          printf("Estado: Creandose.\n");
        case 1:
          printf("Estado: Enviandose.\n");
        case 3:
          printf("Estado: Agregado a bodega de farmacia.\n");
      }
      mostrarLotes(nodo->der);
  }
}

// 7.4 Mostrar Lotes de Proveedor
void mostrarLotesDeProveedor(struct NodoProveedores *listaProveedores, int idProveedor) {
    struct NodoProveedores *actual = listaProveedores;
    while (actual != NULL) {
        if (actual->datosProveedor->idProveedor == idProveedor) {
            printf("Lotes del proveedor %d (%s):\n", idProveedor, actual->datosProveedor->nombre);
            mostrarLotes(actual->datosProveedor->lotesEncargados);
            return;
        }
        actual = actual->sig;
    }
    printf("Proveedor con ID %d no encontrado.\n", idProveedor);
}

// 7.5 Mostrar Venta
void mostrarVentas(struct NodoVenta *listaVentas){
  struct NodoVenta *actual;
  struct NodoVentaProducto *productos;
  actual = listaVentas;
  while (actual != NULL) 
  {
      printf("Venta ID: %d, RUT: %s, Fecha: %d-%d-%d, Precio Final: %.2f\n", 
          actual->datosVenta->idVenta, actual->datosVenta->rutCliente, 
          actual->datosVenta->anio, actual->datosVenta->mes, actual->datosVenta->dia, 
          actual->datosVenta->precioFinal);

      productos = actual->datosVenta->productosVendidos;
      while (productos != NULL) 
      {
          printf("  Producto ID: %d, Nombre: %s, Cantidad: %d\n", 
              productos->datosVentaProducto->producto->codigo, 
              productos->datosVentaProducto->producto->nombre, 
              productos->datosVentaProducto->cantidad);
          productos = productos->sig;
      }
      actual = actual->sig;
  }
}

// 7.6 Mostrar Orden de Compra
void mostrarOrdenesDeCompra(struct NodoOrdenDeCompra *head) {
    struct NodoOrdenDeCompra *rec = head;
    while (rec != NULL) {
        printf("ID de Compra: %d\n", rec->datosOrdenDeCompra->idCompra);
        printf("Fecha: %d-%02d-%02d\n", rec->datosOrdenDeCompra->anio, rec->datosOrdenDeCompra->mes, rec->datosOrdenDeCompra->dia);
        printf("Cantidad de Producto: %d\n", rec->datosOrdenDeCompra->cantidadProductos);

        if (rec->datosOrdenDeCompra->productos != NULL) {
            printf("Producto: %s\n", rec->datosOrdenDeCompra->productos->nombre); // Asumiendo que struct Producto tiene un campo `nombre`
        }

        if (rec->datosOrdenDeCompra->proveedor != NULL) {
            printf("Proveedor: %s\n", rec->datosOrdenDeCompra->proveedor->nombre);
        }

        printf("\n");
        rec = rec->sig;
    }
}

// 7.7 Mostrar Orden de Compra a Proveedor
// Funcion para mostrar ordenes de compra a un proveedor especifico en una farmacia especifica
void mostrarOrdenesDeCompraAProveedor(struct NodoOrdenDeCompra *listaOrdenes, int idProveedor) {
    struct NodoOrdenDeCompra *nodoOrden = listaOrdenes;
    while (nodoOrden != NULL) {
        if (nodoOrden->datosOrdenDeCompra->proveedor->idProveedor == idProveedor) {
            printf("ID de Compra: %d\n", nodoOrden->datosOrdenDeCompra->idCompra);
            printf("Fecha: %d-%02d-%02d\n", nodoOrden->datosOrdenDeCompra->anio, nodoOrden->datosOrdenDeCompra->mes, nodoOrden->datosOrdenDeCompra->dia);
            printf("Cantidad de Producto: %d\n", nodoOrden->datosOrdenDeCompra->cantidadProductos);
            if (nodoOrden->datosOrdenDeCompra->productos != NULL) {
                printf("Producto: %s\n", nodoOrden->datosOrdenDeCompra->productos->nombre); // Asumiendo que struct Producto tiene un campo `nombre`
            }
            printf("\n");
        }
        nodoOrden = nodoOrden->sig;
    }
}
// 8 Registrar venta
void registrarVenta(struct NodoVenta **listaVentas, struct Inventario *inventario, char *rutCliente, int anio, int month, int day, int idVenta) 
{
    struct Venta *nuevaVenta = crearVenta(idVenta, rutCliente, anio, month, day, 0);
    struct Producto *producto = NULL;
    int continuar = 1;
    while (continuar) {
        int codigoProducto, cantidad;
        printf("Ingrese el codigo del producto: ");
        scanf("%d", &codigoProducto);
        printf("Ingrese la cantidad: ");
        scanf("%d", &cantidad);

        producto = buscarProducto(inventario, codigoProducto);
        if (producto != NULL && producto->cantidadStock >= cantidad) 
        {
            agregarProductoAVenta(nuevaVenta, producto, cantidad,codigoProducto);
            if (eliminarProductoDelArreglo(producto, inventario, cantidad)) 
            {
              nuevaVenta->precioFinal += producto->precio * cantidad;
            } 
            else 
            {
                printf("Error al eliminar el producto del inventario.\n");
            }
        } 
        else 
        {
            printf("Producto no encontrado o cantidad insuficiente.\n");
        }

        printf("¿Desea agregar otro producto? (1: Si, 0: No): ");
        scanf("%d", &continuar);
    }

    agregarVenta(listaVentas, nuevaVenta);
}



// 9 ALERTAS
int esUnMesAntes(int diaActual, int mesActual, int anioActual, int diaVenc, int mesVenc, int anioVenc) {
  if (anioActual == anioVenc)
  {
      if ((mesActual + 1 == mesVenc) && (diaActual == diaVenc))
      {
          return 1;
      }
  }
  else 
      if (anioActual + 1 == anioVenc) {
          if ((mesActual == 12) && (mesVenc == 1) && (diaActual == diaVenc)) 
          {
              return 1;
      }
  }
  return 0;
}

void ingresarFecha(int *dia, int *mes, int *anio) {
  printf("\nIngrese la fecha actual (dia mes anio): ");
  scanf("%d %d %d", dia, mes, anio);
}

void GenerarAlertaBajoStock(struct Producto *producto, int umbral)
{
  if (producto->cantidadStock < umbral){
      printf("ALERTA: El producto %s (ID: %d) tiene un stock bajo el umbral",producto->nombre,producto->codigo);
      return;
  }
  else
  {
      printf("Producto se encuentra en stock suficiente\n");
      return;
  }
}

// Funcion para comparar productos por codigo y fecha de vencimiento
void generarAlertas(struct Inventario *inventario, int diaActual, int mesActual, int anioActual) {
    // Lista dinamica para almacenar productos que vencen
    struct Producto **alertas = (struct Producto **)malloc(inventario->pLibre * sizeof(struct Producto *));
    struct Producto *producto = NULL;
    struct Producto *productoAlerta = NULL;
    int totalAlertas = 0;
    int i, j;

    // Recorrer el inventario
    for (i = 0; i < inventario->pLibre; i++) {
        producto = inventario->arregloProductos[i];

        // Verificar si el producto vence en un mes
        if (esUnMesAntes(diaActual, mesActual, anioActual, producto->dia, producto->mes, producto->anio)) {
            // Buscar si el producto ya esta en la lista de alertas
            for (j = 0; j < totalAlertas; j++) {
                if (alertas[j]->codigo == producto->codigo &&
                    alertas[j]->dia == producto->dia &&
                    alertas[j]->mes == producto->mes &&
                    alertas[j]->anio == producto->anio) {
                    // El producto ya esta en la lista, incrementar la cantidad de vencimiento
                    alertas[j]->cantidadStock++;
                    break;
                }
            }

            // Si el producto no se encuentra en la lista, agregarlo
            if (j == totalAlertas) {
                productoAlerta = crearProducto(producto->codigo, producto->nombre, producto->descripcion, producto->categoria, producto->anio, producto->mes, producto->dia, producto->precio, producto->requiereReceta, producto->cantidadStock);
                alertas[totalAlertas] = productoAlerta;
                alertas[totalAlertas]->cantidadStock = 1; // Iniciar el contador de vencimiento en 1
                totalAlertas++;
            }
        }
    }

    // Imprimir las alertas
    for (i = 0; i < totalAlertas; i++) {
        printf("ALERTA: El producto %s (ID: %d) vence el %d-%d-%d. Requiere Receta: %d Cantidad a vencer: %d.\n",
               alertas[i]->nombre, alertas[i]->codigo, alertas[i]->dia, alertas[i]->mes, alertas[i]->anio,
               alertas[i]->requiereReceta, alertas[i]->cantidadStock);
    }
    alertas = NULL;
}


// 10 INFORMES
struct Producto *productoMasVendido(struct NodoVenta *ventas) {
    struct NodoVenta *ventaActual = ventas;
    struct NodoVentaProducto *productoVentaActual;
    struct Producto *productoMasVendido = NULL;
    struct NodoVenta *tempVenta = NULL;
    struct NodoVentaProducto *tempProducto = NULL;
    int maxCantidadVendida = 0;
    int cantidadVendida;

    while (ventaActual != NULL) {
        productoVentaActual = ventaActual->datosVenta->productosVendidos;
        while (productoVentaActual != NULL) {
            cantidadVendida = 0;
            tempVenta = ventas;
            while (tempVenta != NULL) {
                tempProducto = tempVenta->datosVenta->productosVendidos;
                while (tempProducto != NULL) {
                    if (tempProducto->datosVentaProducto->producto->codigo == productoVentaActual->datosVentaProducto->producto->codigo) {
                        cantidadVendida += tempProducto->datosVentaProducto->cantidad;
                    }
                    tempProducto = tempProducto->sig;
                }
                tempVenta = tempVenta->sig;
            }
            if (cantidadVendida > maxCantidadVendida) {
                maxCantidadVendida = cantidadVendida;
                productoMasVendido = productoVentaActual->datosVentaProducto->producto;
            }
            productoVentaActual = productoVentaActual->sig;
        }
        ventaActual = ventaActual->sig;
    }

    return productoMasVendido;
}



struct Producto *productoMenosVendido(struct NodoVenta *ventas) {
    struct NodoVenta *ventaActual = ventas;
    struct NodoVentaProducto *productoVentaActual = NULL;
    struct Producto *productoMenosVendido = NULL;
    struct NodoVenta *tempVenta = NULL;
    struct NodoVentaProducto *tempProducto = NULL;
    int cantidadVendida;
    int minCantidadVendida = -1;

    while (ventaActual != NULL) {
        productoVentaActual = ventaActual->datosVenta->productosVendidos;
        while (productoVentaActual != NULL) {
            cantidadVendida = 0;
            tempVenta = ventas;
            while (tempVenta != NULL) {
                tempProducto = tempVenta->datosVenta->productosVendidos;
                while (tempProducto != NULL) {
                    if (tempProducto->datosVentaProducto->producto->codigo == productoVentaActual->datosVentaProducto->producto->codigo) {
                        cantidadVendida += tempProducto->datosVentaProducto->cantidad;
                    }
                    tempProducto = tempProducto->sig;
                }
                tempVenta = tempVenta->sig;
            }
            if (minCantidadVendida == -1 || cantidadVendida < minCantidadVendida) {
                minCantidadVendida = cantidadVendida;
                productoMenosVendido = productoVentaActual->datosVentaProducto->producto;
            }
            productoVentaActual = productoVentaActual->sig;
        }
        ventaActual = ventaActual->sig;
    }

    return productoMenosVendido;
}



char *obtenerEstacion2(int mes) 
{
    if (mes == 12 || mes == 1 || mes == 2)
      return "VERANO";
    else if (mes == 3 || mes == 4 || mes == 5)
      return "OTOÑO";
    else if (mes == 6 || mes == 7 || mes == 8)
      return "INVIERNO";
    else
      return "PRIMAVERA";
}

void tendenciasEstacionales(struct NodoVenta *ventas) 
{
  int ventasVerano = 0;
  int ventasOtono = 0;
  int ventasInvierno = 0;
  int ventasPrimavera = 0;
  struct NodoVenta *ventaActual = ventas;
  struct NodoVentaProducto *productoVentaActual;

  while (ventaActual != NULL) {
      char *estacion = obtenerEstacion2(ventaActual->datosVenta->mes);
      productoVentaActual = ventaActual->datosVenta->productosVendidos;

      while (productoVentaActual != NULL) {
          if (strcmp(estacion, "VERANO") == 0) {
              ventasVerano += productoVentaActual->datosVentaProducto->cantidad;
          } else if (strcmp(estacion, "OTOÑO") == 0) {
              ventasOtono += productoVentaActual->datosVentaProducto->cantidad;
          } else if (strcmp(estacion, "INVIERNO") == 0) {
              ventasInvierno += productoVentaActual->datosVentaProducto->cantidad;
          } else if (strcmp(estacion, "PRIMAVERA") == 0) {
              ventasPrimavera += productoVentaActual->datosVentaProducto->cantidad;
          }
          productoVentaActual = productoVentaActual->sig;
      }
      ventaActual = ventaActual->sig;
 }

  printf("Ventas por estacion:\n");
  printf("VERANO: %d\n", ventasVerano);
  printf("OTOÑO: %d\n", ventasOtono);
  printf("INVIERNO: %d\n", ventasInvierno);
  printf("PRIMAVERA: %d\n", ventasPrimavera);


}


void menuAgregarProveedor(struct FarmaSalud *farmasalud)
{
  int idProveedor;
  char nombre[tamNombre], direccion[tamDireccion], correo[tamEmail], telefono[tamTelefono];
  struct Proveedor *nuevoProveedor = NULL;

  printf("Menu de agregar proveedor\n");
  printf("Ingrese el id del proveedor: ");
  scanf("%d",&idProveedor);

  if(buscarProveedor(farmasalud->proveedores,idProveedor)){
    printf("El proveedor con ID %d, ya existe\n",idProveedor);
    printf("Seras redirigido al menu de administrador.\n");
    menuAdmin(farmasalud);
  }
  else
  {
    printf("Proveedor con ID %d, no existe, puede continuar.\n",idProveedor);
    printf("Ingrese el nombre del nuevo proveedor:\n");
    scanf("%s49[^\n]",nombre);
    printf("Ingrese la direccion del nuevo proveedor:\n");
    scanf("%s49[^\n]",direccion);
    printf("Ingrese el correo del nuevo proveedor:\n");
    scanf("%s49[^\n]",correo);
    printf("Ingrese el telefono del nuevo proveedor:\n");
    scanf("%s11[^\n]",telefono);
    nuevoProveedor = crearProveedor(idProveedor, nombre, direccion, correo, telefono);
    agregarProveedor(&farmasalud->proveedores, nuevoProveedor);
    printf("El proveedor ha sido agregado con exito, seras redirigido al menu de administrador.\n");
    menuAdmin(farmasalud);
  }
}

void menuModificarProveedor(struct FarmaSalud *farmasalud, int idProveedor)
{
  int opcion;
  char nuevoNombre[tamNombre], nuevaDireccion[tamDireccion],nuevoCorreo[tamEmail],nuevoTelefono[tamTelefono];
  printf("Estas en el menu de modificar proveedor, selecciona una de las opciones para continuar:\n");
  printf("0. Volver al menu de proveedores\n");
  printf("1. Modificar proveedor\n");

  scanf("%d", &opcion);

  switch (opcion) {
      case 0:
          menuAdmin(farmasalud);
          break;
      case 1:
      {
          printf("Ingresa los siguientes datos para continuar\n");
          printf("1. Ingresa el id del lote que deseas modificar \n");
          scanf("%d", &idProveedor);
          printf("2. Ingresa el nuevo nombre del proveedor\n");
          scanf("%s",nuevoNombre);
          printf("3. Ingrese la nueva direccion del proveedor\n");
          scanf("%s",nuevaDireccion);
          printf("4.Ingrese el nuevo correo del proveedor");
          scanf("%s",nuevoCorreo);
          printf("5. Ingrese el nuevo teledono del proveedor");
          scanf("%s",nuevoTelefono);

          if(modificarProveedor(farmasalud->proveedores,idProveedor,nuevoNombre,nuevaDireccion,nuevoCorreo,nuevoTelefono))
          {
              printf("Proveedor modificado exitosamente, te enviaremos al menu de proveedores.\n");
              menuAdmin(farmasalud);
          }
          else
          {
              printf("Ha ocurrido un error al intentar encontrar el proveedor, por favor intente denuevo y asegurese que el proveedor es correspondiente.\n");
              menuModificarProveedor(farmasalud,idProveedor);
          }
      }
      default: {
          printf("Opcion invalida, intenta denuevo");
          menuModificarProveedor(farmasalud,idProveedor);
          break;
      }
  }
}

void menuEliminarProveedor(struct FarmaSalud *farmasalud, int idProveedor)
{
  int opcion;
  struct Proveedor *proveedor;
  printf("Estas en el menu de eliminar proveedor, selecciona una de las opciones para continuar:\n");
  printf("0. Volver al menu de proveedores\n");
  printf("1. Eliminar proveedor\n");
  scanf("%d",&opcion);
  switch(opcion)
  {
    case 0:
      menuProveedores(farmasalud);
      break;
    case 1:
      {
      proveedor = buscarProveedor(farmasalud->proveedores,idProveedor);
      if (proveedor)
      {
        printf("El proveedor con ID %d, ha sido encontrado, puede continuar.\n",idProveedor);
        if (eliminarProveedor(&(farmasalud->proveedores),idProveedor))
        {
          printf("El proveedor ha sido eliminado exitosamente, seras redirigido al menu de proveedores.\n");
          menuProveedores(farmasalud);
        }
        else
        {
          printf("El proveedor no ha podido ser eliminado correctamente, por favor intente denuevo.\n");
          menuEliminarProveedor(farmasalud,idProveedor);
        }
      }
      break;
      }
    default:{
      printf("Opcion invalida, intenta denuevo");
      menuEliminarProveedor(farmasalud,idProveedor);
      break;
      }  

  }
}

void menuProveedores(struct FarmaSalud *farmasalud){ 
  int opcion, idProv;
  printf("Administrador, te encuentras en el menu de proveedores\n");
  printf("Seleccione una de las siguientes opciones para continuar\n");
  printf("0. Para volver al menu de administrador.\n");
  printf("1. Para agregar un proveedor.\n");
  printf("2. Para eliminar un proveedor.\n");
  printf("3. Para modificar un proveedor.\n");
  printf("4. Para mostrar los proveedores.\n");
  printf("5. Para buscar un proveedor y sus lotes.\n");
  scanf("%d",&opcion);
  switch (opcion)
  {
    case 0:
      menuAdmin(farmasalud);
      break;
    case 1:
      menuAgregarProveedor(farmasalud);
      break;
    case 2:{
      printf("Ingrese el id del proveedor que desea eliminar.\n");
      scanf("%d",&idProv);
      menuEliminarProveedor(farmasalud,idProv); 
      break;
    }
    case 3:{
      printf("Ingrese el id del proveedor que desea buscar\n");
      scanf("%d",&idProv);
      menuModificarProveedor(farmasalud,idProv);
      break;
    }
    case 4:
      {
      mostrarProveedores(farmasalud->proveedores);
      menuAdmin(farmasalud);
      break;
    }

    case 5:{
      printf("Ingrese el id del proveedor que desea buscar\n");
      scanf("%d",&idProv);
      mostrarLotesDeProveedor(farmasalud->proveedores, idProv);
      menuProveedores(farmasalud);
      break;
      }

    default:{
      printf("Opcion invalida, intenta denuevo");
      menuProveedores(farmasalud);
      break;
    }
  }
}



void menuAgregarProducto(struct FarmaSalud *farmasalud, struct Farmacia *farmacia) {
    int codigo, dia, mes, anio, requiereReceta, cantidadProductos, idLote, idProveedor, estado;
    float precio;
    struct Producto *nuevoProducto = NULL;
    struct Proveedor *proveedor = NULL;
    struct Lote *nuevoLote = NULL;
    char nombre[100], descripcion[256], categoria[50];


    printf("Bienvenido al menu AgregarProducto!");
    printf("Ingrese el codigo del producto (10 digitos): ");
    scanf("%d", &codigo);

    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]s", nombre);

    printf("Ingrese la descripcion del producto: ");
    scanf(" %[^\n]s", descripcion);

    printf("Ingrese la categoria del producto: ");
    scanf(" %[^\n]s", categoria);

    printf("Ingrese la fecha de caducidad (dd mm yyyy): ");
    scanf("%d %d %d", &dia, &mes, &anio);

    printf("Ingrese el precio del producto: ");
    scanf("%f", &precio);

    printf("¿Requiere receta? (1 para si, 0 para no): ");
    scanf("%d", &requiereReceta);

    nuevoProducto = crearProducto(codigo, nombre, descripcion, categoria, dia, mes, anio, precio, requiereReceta, 0);

    printf("Ingrese la cantidad de productos para el lote: ");
    scanf("%d", &cantidadProductos);

    printf("Ingrese el ID del lote: ");
    scanf("%d", &idLote);

    printf("Ingrese el ID del proveedor: ");
    scanf("%d", &idProveedor);

    printf("Ingrese el estado del Lote: ");
    scanf("%d", &estado);

    proveedor = buscarProveedor(farmasalud->proveedores, idProveedor);
    if (proveedor == NULL) {
        printf("Proveedor no encontrado. No se puede agregar el lote.\n");
        menuFarmacia(farmasalud);
    }

    nuevoLote = crearLote(idLote, cantidadProductos, anio, mes, dia,estado, nuevoProducto);

    agregarLote(&(proveedor->lotesEncargados), nuevoLote);

    if (agregarProductoAlArreglo(nuevoLote, farmacia->inventario))
        printf("Producto agregado exitosamente al inventario.\n");
    else 
        printf("No se pudo agregar el producto al inventario. Verifique la capacidad disponible.\n");

    menuFarmacia(farmasalud);
}

void menuModificarProducto(struct FarmaSalud *farmasalud, struct Farmacia *farmacia)
{
  int opcion, codigo, requiereReceta, anio, mes, dia;
  float precio;
  char nombre[tamNombre], descripcion[tamDescripcion], categoria[tamCategoria];

  printf("\nMenu de Modificacion de Producto\n");
  printf("1. Modificar producto\n");
  printf("2. Salir\n");
  printf("Seleccione una opcion: ");
  scanf("%d", &opcion);

  switch(opcion)
  {
    case 1:
    printf("Ingrese el codigo del producto a modificar: ");
    scanf("%d", &codigo);
    printf("Ingrese el nuevo nombre del producto: ");
    scanf("%s", nombre);
    printf("Ingrese la nueva descripcion del producto: ");
    scanf("%s", descripcion);
    printf("Ingrese la nueva categoria del producto: ");
    scanf("%s", categoria);
    printf("Ingrese el nuevo año de caducidad: ");
    scanf("%d", &anio);
    printf("Ingrese el nuevo mes de caducidad: ");
    scanf("%d", &mes);
    printf("Ingrese el nuevo dia de caducidad: ");
    scanf("%d", &dia);
    printf("Ingrese el nuevo precio del producto: ");
    scanf("%f", &precio);
    printf("El producto requiere receta? (1 para si, 0 para no): ");
    scanf("%d", &requiereReceta);

    if(modificarProducto(farmacia->inventario, codigo, nombre, descripcion, categoria, anio, mes, dia, precio, requiereReceta))
    {
      printf("Producto modificado exitosamente, te enviaremos al menu de las farmacias.\n");
      menuFarmacia(farmasalud);
      break;
    }
    case 2:
    {
      printf("Ha ocurrido un error al intentar encontrar el producto, por favor intente denuevo\n\n");
      menuModificarProducto(farmasalud,farmacia);
      break;
    }
    default:
    {
      printf("Opcion invalida, intente denuevo\n");
      menuModificarProducto(farmasalud,farmacia);
      break;
    }
  }
}


void menuAgregarFarmacia(struct FarmaSalud *farmasalud){
  int idFarmacia;
  char nombre[tamNombre], direccion[tamDireccion];
  struct Farmacia *nuevaFarmacia = NULL;

  printf("Ingrese el ID de la nueva farmacia: \n");
  scanf("%d",&idFarmacia);

  if (buscarFarmacia(farmasalud->farmacias, idFarmacia)){
    printf("La farmacia con ID %d, ya existe\n",idFarmacia);
    printf("Seras redirigido al menu de administrador.\n");
    menuAdmin(farmasalud);
  }
  else{
    printf("Farmacia con ID %d, no existe, puede continuar.\n",idFarmacia);
    printf("Ingrese el nombre de la nueva farmacia:\n");
    scanf("%s49[^\n]",nombre);
    printf("Ingrese la direccion de la nueva farmacia:\n");
    scanf("%s49[^\n]",direccion);
    nuevaFarmacia = crearFarmacia(idFarmacia, nombre, direccion);
    if(agregarFarmacia(&(farmasalud->farmacias), nuevaFarmacia)){
      printf("La farmacia ha sido agregada con exito, redirigiendo a menu de administrador...\n");
      menuAdmin(farmasalud);
    }
    else{
      printf("No se pudo agregar la farmacia, redirigiendo a menu de administrador...\n");
      menuAdmin(farmasalud);
    }
  }
}


void menuModificarFarmacia(struct FarmaSalud *farmasalud)
{
  int opcion, idFarmacia; 
  char nuevoNombre[tamNombre], nuevadireccion[tamDireccion];

  printf("Estas en el menu de modificar Farmacia, selecciona una de las opciones para continuar:\n");
  printf("0. Volver al menu de Farmacia\n");
  printf("1. Modificar un Farmacia\n");

  scanf("%d", &opcion);

  switch(opcion)
  {
    case 0:
      menuFarmacia(farmasalud);
      break;
    case 1:
    {
        printf("Ingresa los siguientes datos para continuar:\n");
        printf("1. Ingresa el id de la farmacia que deseas modificar \n");
        scanf("%d", &idFarmacia);

        printf("2. Ingresa el nuevo nombre de la farmacia\n");
        scanf("%s", nuevoNombre);

        printf("3. Ingrese la nueva direccion de la farmacia\n");
        scanf("%s", nuevadireccion);
      if (modificarFarmacia(farmasalud->farmacias,idFarmacia,nuevoNombre,nuevadireccion))
      {
        printf("Farmacia modificada exitosamente, te enviaremos al menu de Farmacias.\n");
        menuFarmacia(farmasalud);
        break;
      }
      else
      {
        printf("Ha ocurrido un error al intentar encontrar la farmacia, por favor intente denuevo y asugurese que el id ingresado es el correspondiente.\n");
        menuModificarFarmacia(farmasalud);
        break;
      }
    }
    default:
    {
      printf("Opcion invalida, intenta denuevo");
      menuModificarFarmacia(farmasalud);
      break;
    }
  }
}

void menuEliminarFarmacia(struct FarmaSalud *farmasalud, int idFarmaciaBuscada)
{
  int opcion; 
  int idFarmacia = idFarmaciaBuscada;
  struct Farmacia *farmacia;
  farmacia = buscarFarmacia(farmasalud->farmacias,idFarmacia);
  printf("Estas en el menu de eliminar Farmacia, selecciona una de las opciones para continuar:\n");
  printf("0. Volver al menu de farmacia\n");
  printf("1. Eliminar farmacia\n");
  scanf("%d", &opcion);

  switch(opcion)
  {
    case 0:
      menuFarmacia(farmasalud);
      break;
    case 1:
    {
      if (farmacia)
      {
        printf("La Farmacia con ID %d, ha sido entregado, puede continuar.\n",idFarmacia);
        if (eliminarFarmacia(&(farmasalud->farmacias),idFarmacia))
        {
          printf("La Farmacia ha sido eliminada exitosamente, seras redirigido al menu de farmacias.\n");
          menuFarmacia(farmasalud);
          break;
        }
        else
        {
          printf("La Farmacia no ha podido ser eliminado correctamente, por favor intente denuevo.\n");
          menuEliminarFarmacia(farmasalud,idFarmacia);
          break;
        }
      }
    }
    default:
    {
      printf("Opcion invalida, intenta denuevo\n");
      menuEliminarFarmacia(farmasalud,idFarmacia);
      break;
    }
  }
}

void menuRevisarStock(struct FarmaSalud *farmasalud, struct Farmacia *farmacia)
{
  struct Producto *producto = NULL;
  int idProd, umbral;
  printf("Ingrese el id del producto que desea analizar:\n");
  scanf("%d",&idProd);
  producto = buscarProducto(farmacia->inventario, idProd);
  if (producto)
  {
    printf("Ingrese el umbral de stock que desea analizar (Realizar analisis de venta previo):\n");
    scanf("%d",&umbral);
    GenerarAlertaBajoStock(producto, umbral);
  }
  else
  {
    printf("El producto no existe, seras redirigido al menu de farmacias.\n");
    menuFarmacia(farmasalud);
  }
}

void menuRevisarFecha(struct Farmacia *farmacia)
{
  int diaActual, mesActual, anioActual;

  printf("Bienveniendo al menu de revisar fecha\n");
  printf("Ingrese la fecha actual (dia mes año): ");
  scanf("%d%d%d", &diaActual, &mesActual, &anioActual);
  generarAlertas(farmacia->inventario, diaActual, mesActual, anioActual);
  return;
}


void menuFarmacia(struct FarmaSalud *farmasalud){
  int opcion, idFarmacia;
  struct Farmacia *farmacia;
  printf("Estas en el menu de farmacia, ingrese la id de la farmacia la cual desea utilizar.\n");
  scanf("%d",&idFarmacia);
  farmacia = buscarFarmacia(farmasalud->farmacias,idFarmacia);
  if (farmacia == NULL){
    printf("No se encontro la farmacia, intentelo de nuevo\n");
    menuAdmin(farmasalud);
  }
  printf("Farmacia encontrada, porfavor seleccione una de las siguientes opciones\n");
  printf("0. Para volver al menu Administrador\n");
  printf("1. Agregar producto.\n");
  printf("2. Modificar producto.\n");
  printf("3. Agregar farmacia.\n");
  printf("4. Modificar farmacia.\n");
  printf("5. Eliminar farmacia.\n");
  printf("6. Revisar stock de un producto.\n");
  printf("7. Revisar fecha de vencimiento a productos a un mes de vencer.\n");

  scanf("%d",&opcion);

  switch (opcion){
    case 0:
        menuAdmin(farmasalud);
        break;
    case 1:
        menuAgregarProducto(farmasalud,farmacia);
        break;
    case 2:
        menuModificarProducto(farmasalud,farmacia);
        break;
    case 3:
        menuAgregarFarmacia(farmasalud);
        break;
    case 4:
        menuModificarFarmacia(farmasalud);
        break;
    case 5:
        menuEliminarFarmacia(farmasalud,idFarmacia);
        break;
    case 6:
        menuRevisarStock(farmasalud,farmacia);
        break;
    case 7:
        menuRevisarFecha(farmacia);
        break;
    default:
      {
      printf("Opcion invalida, intenta denuevo");
      menuFarmacia(farmasalud);
      break;
    }
  }
}

void menuVenta(struct FarmaSalud *farmasalud)
{
  int idFarmacia, opcion, dia, mes, anio, idVenta;
  struct Farmacia *farmacia;
  char rutCliente[tamRut];
  printf("Bienvenido al menu de venta.\n");
  printf("Aqui podras realizar una venta dentro de una farmacia, ");
  printf("por favor ingrese el id de la farmacia donde desea realizar el registro de la venta\n");
  scanf("%d",&idFarmacia);
  farmacia = buscarFarmacia(farmasalud->farmacias,idFarmacia);
  if (farmacia)
  { 
    printf("Farmacia encontrada, ");
    printf("Seleccione una de las siguientes opciones para continuar:\n");
    printf("0. Para volver al menu Administrador.\n");
    printf("1. Para realizar una venta.\n");
    printf("2. Para mostrar las ventas realizadas.\n");
    printf("3. Para eliminar una venta.\n");
    scanf("%d",&opcion);
    switch(opcion)
    {
      case 0:
        menuAdmin(farmasalud);
        break;
      case 1:{
        printf("Ingrese el rut del cliente, si no ingresa rut, ingrese 'sin rut'\n");
        scanf("%s",rutCliente);
        printf("Ingrese la fecha de la venta, en formato AAAA-MM-DD, sin escribir los guiones (-)\n");
        scanf("%d%d%d",&anio,&mes,&dia);
        printf("Ingrese el id de la venta\n");
        scanf("%d",&idVenta);
        registrarVenta(&(farmacia->ventas),farmacia->inventario,rutCliente,anio,mes,dia,idVenta);
        printf("Venta realizada existosamente, seras redirigido al menu de adminsitrador\n");
        menuAdmin(farmasalud);
        break;
      }
      case 2:
        mostrarVentas(farmacia->ventas);
        break;
      case 3:{
        printf("Ingrese el id de la venta que desea eliminar\n");
        scanf("%d",&idVenta);
        if (eliminarVenta(&(farmacia->ventas),idVenta)){
          printf("Venta eliminada exitosamente, seras redirigido al menu de adminsitrador\n");
          menuAdmin(farmasalud);
          break;
        }
        else{
          printf("No se pudo eliminar la venta, seras redirigido al menu de administrador\n");
          menuAdmin(farmasalud);
          break;
        }
      }
      default:{
        printf("Opcion invalida.\n");
        menuVenta(farmasalud);
        break;
      }
    }
  }
  else
  {
    printf("La farmacia no existe, por favor ingrese correctamente la id\n");
    menuVenta(farmasalud);
  }
}

void consultaMasVendido(struct FarmaSalud *farmasalud)
{
  struct Farmacia *farmacias;
  struct Producto *MasVendido;

  MasVendido = productoMasVendido(farmacias->ventas);
  if (MasVendido != NULL)
    printf("El producto mas vendido es %s (ID: %d).\n", MasVendido->nombre, MasVendido->codigo); 
  else
    printf("No se encontraron ventas registradas para ese producto, seras redirigido al menu de administrador\n");
    menuAdmin(farmasalud);
}

void consultaMenosVendido(struct FarmaSalud *farmasalud){
  struct Farmacia *farmacias;
  struct Producto *MenosVendido;

  MenosVendido = productoMenosVendido(farmacias->ventas);
  if (MenosVendido != NULL)
    printf("El producto menos vendido es %s (ID: %d).\n", MenosVendido->nombre, MenosVendido->codigo); 
  else
    printf("No se encontraron ventas registradas para ese producto, seras redirigido al menu de administrador\n");
    menuAdmin(farmasalud);
}

void consultaTendenciasEstacionales(struct FarmaSalud *farmasalud)
{
  struct Farmacia *farmacias;
  tendenciasEstacionales(farmacias->ventas);
  menuAdmin(farmasalud);
}

void menuConsultarRegistroVenta(struct FarmaSalud *farmasalud)
{
    int idFarmacia,opcion;
    struct Farmacia *farmacia;
    printf("Bienvenido al menu de Consultar Registro Venta.\n");
    printf("Aqui podras consultar el registro de ventas dentro de la farmacia, ");
    printf("por favor ingrese el id de la farmacia donde desea realizar consultar el registro de la venta\n");
    scanf("%d",&idFarmacia);
    farmacia = buscarFarmacia(farmasalud->farmacias,idFarmacia);
    if (farmacia)
    { 
      printf("Farmacia encontrada. Seleccione una de las siguientes opciones para continuar:\n");
      printf("0. Para volver al menu Administrador.\n");
      printf("1. Consultar el producto mas vendido.\n");
      printf("2. Consultar el producto menos vendido.\n");
      printf("3. Consultar las tendencias estacionales.\n");
      scanf("%d",&opcion);
      switch(opcion)
      {
        case 0:
        menuAdmin(farmasalud);
        break;
        case 1:
        {
          consultaMasVendido(farmasalud);
          break;
        }
        case 2:
        {
          consultaMenosVendido(farmasalud);
          break;
        }
        case 3:
        {
          consultaTendenciasEstacionales(farmasalud);
          break;
        }
        default:
          printf("Opcion invalida.\n");
          menuConsultarRegistroVenta(farmasalud);
          break;
      }
    }
    else
    {
      printf("La farmacia no existe, por favor ingrese correctamente la id de la farmacia\n");
      menuConsultarRegistroVenta(farmasalud);
    }
}


void menuAdmin(struct FarmaSalud *farmasalud){
  int opcion;
  printf("Bienvenido administrador, por favor seleccione una de las siguientes opciones:\n");
  printf("0. Para volver al menu principal.\n");
  printf("1. Consultar por Farmacias.\n");
  printf("2. Consultar por Proveedores.\n");
  printf("3. Realizar una venta.\n");
  printf("4. Consultar registros de productos.\n");

  scanf("%d",&opcion);
  switch(opcion)
  {
    case 0:
      menuPrincipal(farmasalud);
      break;
    case 1:
      menuFarmacia(farmasalud);
      break;
    case 2:
      menuProveedores(farmasalud);
      break;
    case 3:
      menuVenta(farmasalud);
      break;
    case 4:
      menuConsultarRegistroVenta(farmasalud);
      break;
    default:{
      printf("Opcion invalida, intenta denuevo");
      menuAdmin(farmasalud);
      break;
    }
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCIONES PARA CUANDO ACCEDE UN PROVEEDOR

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuInfoLote(struct Proveedor *proveedor)
{
  printf("Proveedor %s aqui tienes la informacion de todos tus lotes:",proveedor->nombre);
  mostrarLotes(proveedor->lotesEncargados);
}

void menuModificarLote(struct FarmaSalud *farmasalud,struct Proveedor *proveedor) //posiblemente hecha
{
  int opcion;
  int idLote, nuevaCantidad, anio, mes, dia;
  printf("Estas en el menu de modificar lote, selecciona una de las opciones para continuar:\n");
  printf("0. Volver al menu de proveedores\n");
  printf("1. Modificar un lote\n");

  scanf("%d", &opcion);

  switch(opcion)
  {
    case 0:
      menuProveedor(farmasalud,proveedor);
      break;
    case 1:
      {
      printf("Ingresa los siguientes datos para continuar\n");
      printf("1. Ingresa el id del lote que deseas modificar \n");
      scanf("%d", &idLote);  
      printf("2. Ingresa la nueva cantidad del producto\n");
      scanf("%d", &nuevaCantidad);  
      printf("3. Nuevo año\n");
      scanf("%d", &anio);  
      printf("4. Nuevo mes\n");
      scanf("%d", &mes);  
      printf("5. Nuevo dia\n");
      scanf("%d", &dia);
      if (modificarLote(proveedor->lotesEncargados,idLote,nuevaCantidad,anio,mes,dia))
      {
        printf("Lote modificado exitosamente, te enviaremos al menu de proveedores.\n");
        menuProveedor(farmasalud,proveedor);
        break;
      }
      else
      {
        printf("Ha ocurrido un error al intentar encontrar el lote, por favor intente denuevo y asegurese que el lote es correspondiente.\n");
        menuModificarLote(farmasalud,proveedor);
        break;
      }
    }
    default:
      {
      printf("Opcion invalida, intenta denuevo");
      menuModificarLote(farmasalud,proveedor);
      break;
    }
  }
}


void menuModificarEstadoLote(struct FarmaSalud *farmasalud,struct Proveedor *proveedor){
  int opcion,idLote,estado;
  printf("Estas en el menu de modificar estado de lote, selecciona una de las siguientes opciones para continuar:\n");
  printf("0. Volver al menu de proveedores\n");
  printf("1. Modificar el estado de un lote\n");
  scanf("%d",&opcion);
  switch(opcion){
    case 1:
      menuProveedor(farmasalud,proveedor);
      break;
    case 2:{
      printf("Ingrese el id del lote:\n");
      scanf("%d",&idLote);
      printf("Recuerde los estados que puede tener un lote:\n");
      printf("0. Si esta creandose (Al crear un lote, se selecciona este estado por defecto.\n");
      printf("1. Si esta listo para enviar.\n");
      printf("2. Si esta enviandose\n");
      printf("3. Si se entrego\n");
      printf("Ingrese el estado que desea asignar al lote:\n");
      scanf("%d",&estado);
      if (modificarEstadoLote(proveedor->lotesEncargados,idLote,estado)){
        printf("Estado modificado exitosamente, te enviaremos al menu de proveedores.\n");
        menuProveedor(farmasalud,proveedor);
        break;
      }
      else{
        printf("Ha ocurrido un error al intentar encontrar el lote, por favor intente denuevo y asegurese que ingresa correctamente la id del lote.\n");
        menuModificarEstadoLote(farmasalud,proveedor);
        break;
      }
    }
    default:{
      printf("Opcion invalida, intenta denuevo");
      menuModificarEstadoLote(farmasalud,proveedor);
      break;
    }
  }
}
/////////
//////////

void menuProveedor(struct FarmaSalud *farmasalud, struct Proveedor *proveedor)
{
  //no quiero que un proveedor maneje toda la informacion de la empresa, solo los productos que administra;
  int opcion;
  printf("Proveedor %s, por favor seleccione una de las siguientes opciones:\n",proveedor->nombre);
  printf("0. Para volver al menu principal.\n");
  printf("1. Modificar un lote.\n");
  printf("2. Si desea saber informacion de un lote.\n");
  printf("3. Modificar estado de un lote.\n");
  scanf("%d",&opcion);

  switch(opcion)
  {
    case 0:
      menuPrincipal(farmasalud);
      break;
    case 1:
    //funcion modificar lote
      menuModificarLote(farmasalud,proveedor); //Listo
      break;
    case 2:
      menuInfoLote(proveedor); //Listo
      break;
    case 3:
      menuModificarEstadoLote(farmasalud,proveedor);
      break;
    default:{
      printf("Opcion invalida, intenta denuevo");
      menuProveedor(farmasalud,proveedor);
      break;
    }
  }
}

//FUNCIONES LOGICAS PARA CUANDO ACCEDE UN USUARIO

struct Proveedor *encontrarprov(struct FarmaSalud *farmasalud,int idProv){

  struct NodoProveedores *rec = NULL;
  if (farmasalud != NULL)
  {
    rec = farmasalud->proveedores;//si esta vacia la coleccion, sera NULL
    while (rec != NULL)
    {
      if (rec->datosProveedor->idProveedor == idProv)
        return rec->datosProveedor;
      rec = rec->sig;
    }
  }
  return NULL;
}

void acceder(int opcion, struct FarmaSalud *farmasalud)
{
  int id;
  struct Proveedor *prov = NULL;

  switch (opcion)
  {
    case 0:
        printf("Saliendo del programa...\n");
        exit(0);
    case 1:
        menuAdmin(farmasalud);
        break;
    case 2:
      {
        printf("Escribe tu id de proveedor.");
        scanf("%d",&id);
        prov = encontrarprov(farmasalud,id);
        if (prov){
          menuProveedor(farmasalud,prov);
          break;
        }
        else
        {
          printf("No existe el proveedor, seras redirigido al menu principal.");
          menuPrincipal(farmasalud);
          break;
          }
      }
    default:
        printf("Opcion invalida, intenta denuevo.");
        menuPrincipal(farmasalud);
        break;
  }
}


void menuPrincipal(struct FarmaSalud *farmasalud)
{ 
  int opcion;
  if (farmasalud == NULL){
    printf("Fallo al iniciar la aplicacion");
    exit(0);//por si hay algun error al iniciar la aplicacion, conectar con la base de datos o reservar memoria, etc. que se yo brou
  }
  printf("Bienvenido al menu principal de FarmaSalud (Tenga en consideracion que tiene que escribir numericamente los numeros a la izquiera de las opciones para continuar), por favor identifiquese:\n");
  printf("0. Salir del programa.\n");
  printf("1. Administrador.\n");
  printf("2. Proveedor.\n");
  scanf("%d",&opcion);
  acceder(opcion,farmasalud);
}



//MAIN
int main() {
    struct FarmaSalud *farmasalud = NULL;
    struct Farmacia *farmacia1 =  NULL;
    struct Proveedor *proveedor1 = NULL;
    farmasalud = crearFarmaSalud("FarmaSalud","72.233.809-0");
    farmacia1 = crearFarmacia(1112, "Farmacia 0", " Brasil 2241 Valparaíso");
    proveedor1 = crearProveedor(0001, "Proveedor 1", "Pedro Montt 2200 Valparaíso", "correoejemplo@gmail.com", "985371890");
    agregarFarmacia(&(farmasalud->farmacias), farmacia1);
    agregarProveedor(&(farmasalud->proveedores), proveedor1);
    menuPrincipal(farmasalud);
    return 0;
}


