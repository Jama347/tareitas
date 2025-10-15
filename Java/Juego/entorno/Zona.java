package Juego.entorno;

import Juego.objetos.ItemTipo;
import Juego.player.Jugador;
//import Juego.objetos.Item;

import java.util.EnumSet;
//import java.util.List;

public abstract class Zona {
    public String nombre;
    private int profundidadMin;
    private int profundidadMax;
    protected EnumSet<ItemTipo> recursos;
    int nMin;
    int nMax;

    //constructor
    public Zona(String nombre, int profundidadMin, int profundidadMax) {
        this.nombre = nombre;
        this.profundidadMin = profundidadMin;
        this.profundidadMax = profundidadMax;
    }
    //getters
    public String getNombre() {
        return nombre;
    }
    public int getProfundidadMin() {
        return profundidadMin;
    }
    public int getProfundidadMax() {
        return profundidadMax;
    }
    public EnumSet<ItemTipo> getRecursos() {
        return recursos;
    }

    //metodos
    public void entrar(Jugador jugador) {
        jugador.setZonaActual(this);
    }

    public double profundidadNormalizada(Jugador jugador) {
        double d = jugador.getProfundidadActual() - this.getProfundidadMin();
        return d/(this.getProfundidadMax() - this.getProfundidadMin());
    }

    public int cantidadRecolectar(Jugador jugador){
        return (int) Math.max(1, Math.floor(nMin + (nMax - nMin) * profundidadNormalizada(jugador)));
    }

    public int cantidadExplorar(Jugador jugador){
        return (int) Math.max( 1, Math.floor(nMin * profundidadNormalizada(jugador)));
    }
    public void recolectarRecursos(Jugador jugador){
        int cantidad = cantidadRecolectar(jugador);
        jugador.getTanqueOxigeno().consumirOxigeno(jugador.getTanqueOxigeno().consumoRecolectar(jugador), jugador);
        jugador.recursosAleatorios(cantidad);
    }

    public void explorar(Jugador jugador){} //cada zona lo implementa a su manera
    
    //metodos abstractos (habian mas pero dejaron de ser abstractos)
    public abstract double presionZona(Jugador jugador);
    
    
}
