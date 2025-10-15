package Juego.objetos;

public class Item {
    
    private ItemTipo tipo;
    private int cantidad;

    //constructor
    public Item(ItemTipo tipo, int cantidad) {
        this.tipo = tipo;
        this.cantidad = cantidad;
    }
    //getters
    public ItemTipo getTipo() {
        return tipo;
    }

    public int getCantidad() {
        return cantidad;
    }
    //setters
    public void setCantidad(int cantidad) {
        this.cantidad = cantidad;
    }
}
