package Juego.entorno;

import java.util.EnumSet;

import Juego.objetos.ItemTipo;
import Juego.player.Jugador;

public class ZonaVolcanica extends Zona{

    private boolean planoEncontrado;

    public ZonaVolcanica(String nombre, int profundidadMin, int profundidadMax) {
        super(nombre, profundidadMin, profundidadMax);
        this.planoEncontrado = false;
        this.recursos = EnumSet.range(ItemTipo.TITANIO, ItemTipo.URANIO);
        this.nMin = 3;
        this.nMax = 8;
    }

    public double profundidadNormalizada(Jugador jugador) {
        double d = jugador.getProfundidadActual() - this.getProfundidadMin();
        return d/(this.getProfundidadMax() - this.getProfundidadMin());
    }
    @Override
    public void explorar(Jugador jugador){
        /**
         * 15% de encontrar PLANOS_NAVE
         * en caso de no encontrarlo cantidadExplorar(jugador) recursos
         */
        if (Math.random() < 0.15 && !planoEncontrado){
            System.out.println("Has encontrado los planos de la nave!");
            planoEncontrado = true;
            jugador.setTienePlanos(true);
        } else {
            int recursosObtenidos = cantidadExplorar(jugador);
            jugador.recursosAleatorios(recursosObtenidos);
            System.out.println("No has encontrado los planos de la nave. Has conseguido " + recursosObtenidos + " recursos.");
        }
        jugador.getTanqueOxigeno().consumirOxigeno(jugador.getTanqueOxigeno().consumoExplorar(jugador), jugador);
    }

    public double presionZona(Jugador jugador) {
        return Double.POSITIVE_INFINITY; // Presion letal
    }
}

