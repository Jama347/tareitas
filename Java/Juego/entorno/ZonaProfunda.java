package Juego.entorno;

import java.util.EnumSet;

import Juego.objetos.ItemTipo;
import Juego.player.Jugador;

public class ZonaProfunda extends Zona{

    private int presion;

    public ZonaProfunda(String nombre, int profundidadMin, int profundidadMax) {
        super(nombre, profundidadMin, profundidadMax);
        this.presion = 10;
        this.recursos = EnumSet.range(ItemTipo.PLATA, ItemTipo.MAGNETITA);
        this.nMin = 2;
        this.nMax = 6;
    }

    public double profundidadNormalizada(Jugador jugador) {
        double d = jugador.getProfundidadActual() - this.getProfundidadMin();
        return d/(this.getProfundidadMax() - this.getProfundidadMin());
    }
    @Override
    public void explorar(Jugador jugador){
        // ya que no hay items de progresion, solo entrega cantidadExplorar(jugador) recursos
        int recursosObtenidos = cantidadExplorar(jugador);
        jugador.recursosAleatorios(recursosObtenidos);
        System.out.println("Has explorado la zona profunda y has conseguido " + recursosObtenidos + " recursos.");
        jugador.getTanqueOxigeno().consumirOxigeno(jugador.getTanqueOxigeno().consumoExplorar(jugador), jugador);
        
    }

    public double presionZona(Jugador jugador) {
        return presion + 6 * profundidadNormalizada(jugador);
    }
}

