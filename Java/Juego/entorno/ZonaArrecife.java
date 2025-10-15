package Juego.entorno;

import Juego.objetos.ItemTipo;
import Juego.player.Jugador;
import java.util.EnumSet;


public class ZonaArrecife extends Zona {

    private int piezasTanque;

    public ZonaArrecife(String nombre, int profundidadMin, int profundidadMax) {
        super(nombre, profundidadMin, profundidadMax);
        this.piezasTanque = 3;
        this.recursos = EnumSet.range(ItemTipo.CUARZO, ItemTipo.COBRE);
        this.nMin = 1;
        this.nMax = 3;
    }
    @Override
    public void explorar(Jugador jugador){
        /**
         * 30% de encontrar una pieza del tanque de oxigeno
         * en caso de no encontrar una pieza, conseguir max(1, floor( 1 + (2 * d) ) ) recursos
         * d = profundidad normalizada
         */
        if (Math.random() < 0.3 && piezasTanque > 0) {
            System.out.println("Has encontrado una pieza del tanque de oxigeno!");
            piezasTanque--;
            jugador.incrementarCantPiezasTanque();
            if (piezasTanque == 0) {
                System.out.println("Has encontrado todas las piezas del tanque de oxigeno!");
            }
    } else {
            int recursosObtenidos = cantidadExplorar(jugador);
            jugador.recursosAleatorios(recursosObtenidos);
            System.out.println("No has encontrado una pieza del tanque de oxigeno. Has conseguido " + recursosObtenidos + " recursos.");
        }
        jugador.getTanqueOxigeno().consumirOxigeno(jugador.getTanqueOxigeno().consumoExplorar(jugador), jugador);
    } 

    public double presionZona(Jugador jugador) {
        return 0; // No hay presion en el arrecife
    }

    

   
}
