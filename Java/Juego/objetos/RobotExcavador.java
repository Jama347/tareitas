package Juego.objetos;

public class RobotExcavador extends Vehiculo{

    private int capacidadCarga; // Capacidad maxima de carga

    public RobotExcavador(){
        super();
        this.capacidadCarga = 1000;
    }

    public int getCapacidadCarga() {
        return capacidadCarga;
    }
    
}
