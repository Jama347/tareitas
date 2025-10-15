package Juego.entorno;

import java.util.EnumSet;

import Juego.objetos.ItemTipo;
import Juego.player.Jugador;

public class NaveEstrellada extends Zona{

    private boolean moduloEncontrado;

    public NaveEstrellada(String nombre, int profundidadMin, int profundidadMax) {
        super(nombre, profundidadMin, profundidadMax);
        this.moduloEncontrado = false;
        this.recursos = EnumSet.range(ItemTipo.CABLES, ItemTipo.PIEZAS_METAL);
        this.nMin = 1;
        this.nMax = 4;
    }

    public boolean isModuloEncontrado() {
        return moduloEncontrado;
    }

    @Override
    public void explorar(Jugador jugador ){
        /**
         * 25% de encontrar MODULO_PROFUNDIDAD
         * en caso de no encontrarlo cantidadExplorar(jugador) recursos
         * d = profundidad normalizada
         */
        if (Math.random() < 0.25 && !moduloEncontrado){
            System.out.println("Has encontrado el modulo de acceso a profundidad!");
            moduloEncontrado = true;

        } else {
            int recursosObtenidos = cantidadExplorar(jugador);
            jugador.recursosAleatorios(recursosObtenidos);
            System.out.println("No has encontrado el modulo de acceso a profundidad. Has conseguido " + recursosObtenidos + " recursos.");
        }
        jugador.getTanqueOxigeno().consumirOxigeno(jugador.getTanqueOxigeno().consumoExplorar(jugador), jugador);

    }
    public double presionZona(Jugador jugador) {
        return 0; // No hay presion en la nave estrellada
    }

    @Override
    public double profundidadNormalizada(Jugador jugador) {
        double d = jugador.getProfundidadActual() - this.getProfundidadMin();
        return d;
    }

    
}
