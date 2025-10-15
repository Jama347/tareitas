package Juego.objetos;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;


public abstract class Vehiculo {
    
    private List<Item> bodega;

    public Vehiculo() {
        this.bodega = new ArrayList<>();
    }
    
    public void transferirObjetos(ItemTipo tipo, int cantidad, List<Item> origen, List<Item> destino) {
        // 1. Buscar el item en el bodega de origen
        Optional<Item> itemEnOrigenOpt = origen.stream().filter(i -> i.getTipo() == tipo).findFirst();

        if (itemEnOrigenOpt.isPresent()) {
            Item itemEnOrigen = itemEnOrigenOpt.get();

            // 2. Verificar si hay suficiente cantidad para transferir
            if (itemEnOrigen.getCantidad() >= cantidad) {
                // 3. Disminuir la cantidad en el origen
                itemEnOrigen.setCantidad(itemEnOrigen.getCantidad() - cantidad);
                // Si la cantidad llega a 0, eliminar el item del origen
                if (itemEnOrigen.getCantidad() == 0) {
                    origen.remove(itemEnOrigen);
                }

                // 4. Añadir o actualizar la cantidad en el destino
                Optional<Item> itemEnDestinoOpt = destino.stream().filter(i -> i.getTipo() == tipo).findFirst();
                if (itemEnDestinoOpt.isPresent()) {
                    // Si el item ya existe en el destino, solo aumenta la cantidad
                    Item itemEnDestino = itemEnDestinoOpt.get();
                    itemEnDestino.setCantidad(itemEnDestino.getCantidad() + cantidad);
                } else {
                    // Si no existe, se añade como un nuevo item
                    destino.add(new Item(tipo, cantidad));
                }
                System.out.println("Transferencia exitosa: " + cantidad + " de " + tipo.name());
            } else {
                System.out.println("Error: No hay suficiente " + tipo.name() + " en el origen.");
            }
        } else {
            System.out.println("Error: El ítem " + tipo.name() + " no se encuentra en el bodega de origen.");
        }
    }

    /**
     * Obtiene la bodega del vehículo.
     * @return La lista de items en el bodega.
     */
    public List<Item> getInventario() {
        return bodega;
    }
}
