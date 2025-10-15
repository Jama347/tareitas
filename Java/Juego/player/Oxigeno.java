package Juego.player;

public class Oxigeno {
    int oxigenoRestante;
    int capacidadMaxima;

    public Oxigeno() {
        this.capacidadMaxima = 60;
        this.oxigenoRestante = capacidadMaxima; // inicialmente lleno
    }

    public int getOxigenoRestante() {
        return oxigenoRestante;
    }
    public int getCapacidadMaxima() {
        return capacidadMaxima;
    }
    public void consumirOxigeno(int unidades, Jugador jugador) {
        if (oxigenoRestante - unidades >= 0) {
            oxigenoRestante -= unidades;
        } else {
            oxigenoRestante = 0; // No puede ser negativo
        }
        System.out.println("Has consumido " + unidades + " unidades de oxígeno. Oxígeno restante: " + oxigenoRestante + "/" + capacidadMaxima);
        if (oxigenoRestante == 0) {
            System.out.println("¡Te has quedado sin oxígeno!");
            jugador.matarJugador();

        }
    }

    public void recargarCompleto() {
        this.oxigenoRestante = capacidadMaxima;
    }

    public void aumentarCapacidad(int incremento) {
        this.capacidadMaxima += incremento;
        this.oxigenoRestante = capacidadMaxima; // recarga al maximo
        System.out.println("Capacidad de oxígeno aumentada en " + incremento + ". Nueva capacidad: " + capacidadMaxima);
    }

    public double calculoPresion(Jugador jugador){
        if (!jugador.getMejoraTanque()){ // si el tanque no esta mejorado
            return jugador.getZonaActual().presionZona(jugador);
        } else 
            return 0; // No hay presion si el tanque esta mejorado
    }

    public int consumoExplorar(Jugador jugador){ // 12 + 10*d + presion
        return (int) Math.ceil(12 + 10 * jugador.getZonaActual().profundidadNormalizada(jugador) + calculoPresion(jugador));
    }

    public int consumoRecolectar(Jugador jugador){ // 10 + 6*d + presion
        return (int) Math.ceil(10 + 6 * jugador.getZonaActual().profundidadNormalizada(jugador) + calculoPresion(jugador));
    }

    public int consumoMover(Jugador jugador , int alturaFinal){ // (3 + 3*d)* (|alturaFinal - alturaInicial|/50)
        int alturaInicial = jugador.getProfundidadActual();
        double d = jugador.getZonaActual().profundidadNormalizada(jugador);
        return (int) Math.ceil((3 + 3 * d) * (Math.abs(alturaFinal - alturaInicial) / 50.0));

    }


}
