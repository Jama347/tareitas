package Juego.objetos;

import Juego.player.Jugador;

public class NaveExploradora extends Vehiculo implements AccesoProfundidad {

    private int profundidadSoportada;
    private int profundidadActual;

    public NaveExploradora(){
        super();
        this.profundidadSoportada = 500;
        this.profundidadActual = 1;
    }
    //getters
    public int getProfundidadSoportada() {
        return profundidadSoportada;
    }
    public int getProfundidadActual() {
        return profundidadActual;
    }
    //setters
    public void setProfundidadActual(int profundidadActual) {
        this.profundidadActual = profundidadActual;
    }

    public boolean puedeAcceder(int profundidad) {
        return profundidad <= profundidadSoportada;
    }

    public void accederProfundidad(Jugador jugador, int nuevaProfundidad) {
        if (jugador.getZonas().getZonaPorProfundidad(nuevaProfundidad) == jugador.getZonas().getZonaPorProfundidad(this.profundidadActual)){ //para evitar bugs de cambios de zona inespreados
            if (puedeAcceder(nuevaProfundidad)) {
                setProfundidadActual(nuevaProfundidad);
                jugador.setProfundidadActual(nuevaProfundidad);
                System.out.println("Nave descendio a una profundidad de " + nuevaProfundidad + " metros.");
            } else {
                System.out.println("La nave no puede acceder a esa profundidad. Profundidad máxima soportada: " + profundidadSoportada + " metros.");
                }
        } else { System.out.println("solo puedes moverte dentro de los limites de la zona, si quieres cambiar de zona usa la opcion cambiar zona");}
    }

    public void mostrarInventario(){
        //muestra por pantalla el inventario de la naveExploradora, de la forma que se ve en verEstadoJugador
        System.out.println("Inventario: ");
        if (super.getInventario().isEmpty()) {
            System.out.println("  (vacío)");
        } else {
            for (Item item : super.getInventario()) {
                System.out.println("  - " + item.getTipo().name() + " (x" + item.getCantidad() + ")");
            }
        }
    }

    //clase anidada ModuloProfundidad
    public class ModuloProfundidad{
        int profundidadExtra;

        public ModuloProfundidad(){
            this.profundidadExtra = 1000; 
        }

        public void aumentarProfundidad(){
            profundidadSoportada += profundidadExtra;
        }
    }

    
}
